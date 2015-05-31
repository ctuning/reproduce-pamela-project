@call D:\Work1\CK\ck-repos\fgg-local-win\env\d1cad28a354152b3\env.bat
call D:\Work1\CK\ck-repos\fgg-local-win\env\de433cac44b1c0f7\env.bat
call D:\Work1\CK\ck-repos\fgg-local-win\env\9bbed4f5346adb4e\env.bat
call D:\Work1\CK\ck-repos\fgg-local-win\env\56584503a3d19181\env.bat

@call D:\Work1\CK\ck-repos\fgg-local-win\env\d1cad28a354152b3\env.bat 1

@set KERNEL_TIMINGS=1
@set OPENCL_DEVICE=0
@set OPENCL_KERNEL=D:\Work1\CK\ck-repos\ck-reproduce-project-pamela-2015\program\slambench-1.1-opencl\kernels.cl
@set OPENCL_PLATFORM=0
@set XOPENME_DUMP_MEMORY_DEPTHRENDER=1
@set XOPENME_DUMP_MEMORY_INPUT_RGB=1
@set XOPENME_DUMP_MEMORY_TRACKRENDER=1
@set XOPENME_DUMP_MEMORY_VOLUMERENDER=1


@set OPENCL_DEVICE=1

@a.exe -s 4.8 -p 0.34,0.5,0.24 -z 1 -c 2 -r 1 -k 481.2,480,320,240 -i D:\Work1\CK\ck-repos\ck-reproduce-project-pamela-2015-large-files\dataset\slambench-living-room-traj2-loop-large\living_room_traj2_loop_large.raw -o tmp-output.tmp > tmp-output1.tmp 2> tmp-output2.tmp
