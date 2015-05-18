/*

 Copyright (c) 2014 University of Edinburgh, Imperial College, University of Manchester.
 Developed in the PAMELA project, EPSRC Programme Grant EP/K008730/1

 This code is licensed under the MIT License.

 This code has been updated by Grigori Fursin to support Windows
 and universal autotuning/machine learning CK framework

 */

#include <kernels.h>
#include <interface.h>
#include <stdint.h>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>
#include <csignal>

#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>

#ifdef OPENME
#include <openme.h>
#endif
#ifdef XOPENME
#include <ctuning.h>
#endif

inline double tock() {
	synchroniseDevices();
#ifndef WINDOWS
#include <getopt.h>
#ifdef __APPLE__
		clock_serv_t cclock;
		mach_timespec_t clockData;
		host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
		clock_get_time(cclock, &clockData);
		mach_port_deallocate(mach_task_self(), cclock);
#else
		struct timespec clockData;
		clock_gettime(CLOCK_MONOTONIC, &clockData);
#endif
		return (double) clockData.tv_sec + clockData.tv_nsec / 1000000000.0;
#else
# include <getoptwin.h>
# include <winmisc.h>

  return win_tock();
#endif

}	


/***
 * This program loop over a scene recording
 */

int main(int argc, char ** argv) {

char tmp[256];
char tmp1[256];

#ifdef OPENME
  openme_init(NULL,NULL,NULL,0);
  openme_callback("PROGRAM_START", NULL);
#endif
#ifdef XOPENME
  program_start();
#endif

	Configuration config(argc, argv);

	// ========= CHECK ARGS =====================

	std::ostream* logstream = &std::cout;
	std::ofstream logfilestream;
	assert(config.compute_size_ratio > 0);
	assert(config.integration_rate > 0);
	assert(config.volume_size.x > 0);
	assert(config.volume_resolution.x > 0);

	if (config.log_file != "") {
		logfilestream.open(config.log_file.c_str());
		logstream = &logfilestream;
	}
	if (config.input_file == "") {
		std::cerr << "No input found." << std::endl;
		config.print_arguments();
		exit(1);
	}

	// ========= READER INITIALIZATION  =========

	DepthReader * reader;

	if (is_file(config.input_file)) {
		reader = new RawDepthReader(config.input_file, config.fps,
				config.blocking_read);

	} else {
		reader = new SceneDepthReader(config.input_file, config.fps,
				config.blocking_read);
	}

	std::cout.precision(10);
	std::cerr.precision(10);

	float3 init_pose = config.initial_pos_factor * config.volume_size;
	const uint2 inputSize = reader->getinputSize();
	std::cerr << "input Size is = " << inputSize.x << "," << inputSize.y
			<< std::endl;

	//  =========  BASIC PARAMETERS  (input size / computation size )  =========

	const uint2 computationSize = make_uint2(
			inputSize.x / config.compute_size_ratio,
			inputSize.y / config.compute_size_ratio);
	float4 camera = reader->getK() / config.compute_size_ratio;

	if (config.camera_overrided)
		camera = config.camera / config.compute_size_ratio;
	//  =========  BASIC BUFFERS  (input / output )  =========

	// Construction Scene reader and input buffer
	uint64_t sInputRGB = sizeof(uchar3) * inputSize.x * inputSize.y;
	uint64_t sInputDepth = sizeof(uint16_t) * inputSize.x * inputSize.y;
	uint64_t sDepthRender = sizeof(uchar4) * computationSize.x * computationSize.y;
	uint64_t sTrackRender = sizeof(uchar4) * computationSize.x * computationSize.y;
	uint64_t sVolumeRender = sizeof(uchar4) * computationSize.x * computationSize.y;
 
	uchar3* inputRGB = (uchar3*) malloc(sInputRGB);
	uint16_t* inputDepth = (uint16_t*) malloc(sInputDepth);
	uchar4* depthRender = (uchar4*) malloc(sDepthRender);
	uchar4* trackRender = (uchar4*) malloc(sTrackRender);
	uchar4* volumeRender = (uchar4*) malloc(sVolumeRender);

	uint frame = 0;

	Kfusion kfusion(computationSize, config.volume_resolution,
			config.volume_size, init_pose, config.pyramid);

	double delay;
	double timings[7];
	timings[0] = tock();

	*logstream
			<< "frame\tacquisition\tpreprocessing\ttracking\tintegration\traycasting\trendering\tcomputation\ttotal    \tX          \tY          \tZ         \ttracked   \tintegrated"
			<< std::endl;
	logstream->setf(std::ios::fixed, std::ios::floatfield);



#ifdef OPENME
  openme_callback("ACC_KERNEL_START", NULL);
#endif
#ifdef XOPENME
  clock_start(0);
#endif

delay=tock();

	while (reader->readNextDepthFrame(inputRGB,inputDepth)) {


		Matrix4 pose = kfusion.getPose();

		float xt = pose.data[0].w - init_pose.x;
		float yt = pose.data[1].w - init_pose.y;
		float zt = pose.data[2].w - init_pose.z;

		timings[1] = tock();

//		printf("xyz= %u %u\n", inputDepth, inputSize);
//                exit(1);

		kfusion.preprocessing(inputDepth, inputSize);

		timings[2] = tock();

		bool tracked = kfusion.tracking(camera, config.icp_threshold,
				config.tracking_rate, frame);

		timings[3] = tock();

		bool integrated = kfusion.integration(camera, config.integration_rate,
				config.mu, frame);

		timings[4] = tock();

		bool raycast = kfusion.raycasting(camera, config.mu, frame);

		timings[5] = tock();

		kfusion.renderDepth(depthRender, computationSize);
		kfusion.renderTrack(trackRender, computationSize);
		kfusion.renderVolume(volumeRender, computationSize, frame,
				config.rendering_rate, camera, 0.75 * config.mu);

		timings[6] = tock();

		*logstream << frame << "\t" << timings[1] - timings[0] << "\t" //  acquisition
				<< timings[2] - timings[1] << "\t"     //  preprocessing
				<< timings[3] - timings[2] << "\t"     //  tracking
				<< timings[4] - timings[3] << "\t"     //  integration
				<< timings[5] - timings[4] << "\t"     //  raycasting
				<< timings[6] - timings[5] << "\t"     //  rendering
				<< timings[5] - timings[1] << "\t"     //  computation
				<< timings[6] - timings[0] << "\t"     //  total
				<< xt << "\t" << yt << "\t" << zt << "\t"     //  X,Y,Z
				<< tracked << "        \t" << integrated // tracked and integrated flags
				<< std::endl;

		frame++;

		timings[0] = tock();

		if ((tock()-delay)>1)
                {
                   printf("ping\n");

sprintf(tmp, "tmp-raw-input-rgb-%u.rgb", frame);

FILE *fx=fopen( tmp , "wb" );
//fwrite(inputRGB, sInputRGB, 1, fx);
//sprintf(tmp1, "ck convert_raw_rgb_image dataset.features input_file=%s output_file=tmp-raw-input.png width=640 height=480 output_type=png", tmp);

//fwrite(depthRender, sDepthRender, 1, fx);
//sprintf(tmp1, "ck convert_raw_rgb_image dataset.features input_file=%s output_file=tmp-raw-output.jpg width=320 height=240 mode=CMYK output_type=jpeg", tmp);

//fwrite(trackRender, sTrackRender, 1, fx);
//sprintf(tmp1, "ck convert_raw_rgb_image dataset.features input_file=%s output_file=tmp-raw-output.jpg width=320 height=240 mode=CMYK output_type=jpeg", tmp);

fwrite(volumeRender, sVolumeRender, 1, fx);
sprintf(tmp1, "ck convert_raw_rgb_image dataset.features input_file=%s output_file=tmp-raw-output.jpg width=320 height=240 mode=CMYK output_type=jpeg", tmp);

fclose(fx);


system(tmp1);

                   delay=tock();

                }
	}

#ifdef XOPENME
  clock_end(0);
#endif
#ifdef OPENME
  openme_callback("ACC_KERNEL_END", NULL);
#endif

	// ==========     DUMP VOLUME      =========

	if (config.dump_volume_file != "") {
		kfusion.dumpVolume(config.dump_volume_file);
	}

	//  =========  FREE BASIC BUFFERS  =========

	free(inputDepth);
	free(depthRender);
	free(trackRender);
	free(volumeRender);

#ifdef XOPENME
  program_end();
#endif
#ifdef OPENME
  openme_callback("PROGRAM_END", NULL);
#endif

	return 0;
}
