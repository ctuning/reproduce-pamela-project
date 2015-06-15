import ck.kernel as ck
import time
import os
import shutil

# Get tmp address
ii={'action':'update',
    'module_uoa':'tmp',
    'data_uoa':'slambench-output',
    'ignore_update':''}
rx=ck.access(ii)
if rx['return']>0:
   ck.err(rx)

pp=rx['path']
ppt=os.path.join(pp, 'tmp')
if not os.path.isdir(ppt): os.makedirs(ppt)

print ('Starting continuous convert of images - Press Ctrl-C to stop')

files=["tmp/tmp-raw-input-rgb.rgb", "tmp/tmp-raw-depthrender.rgb", "tmp/tmp-raw-trackrender.rgb", "tmp/tmp-raw-volumerender.rgb"]
tfiles=[None,None,None,None]
width=[640,320,320,320]
height=[480,240,240,240]
types=[None,'CMYK','CMYK','CMYK']
output=['jpeg','jpeg','jpeg','jpeg']

js='tmp/tmp-ck-timer.json'
jsh=os.path.join(pp, 'tmp/tmp-ck-timer.json.html')
tjs=None

while True:
   # Record run-time state raw images and convert them to png or jpeg
   for q in range(0, len(files)):
       fn=files[q]
       t=tfiles[q]
       of=output[q]

       if os.path.isfile(fn):
          tt=os.path.getmtime(fn)
          if t==None or t!=tt:
             tfiles[q]=tt

             of1=fn+'.'+of
             of2=os.path.join(pp,fn+'.'+of+'.tmp')
             of3=os.path.join(pp,fn+'.'+of)

             ii={'action':'convert_raw_rgb_image',
                 'module_uoa':'dataset.features',
                 'input_file':fn,
                 'output_file':of2,
                 'width':width[q],
                 'height':height[q],
                 'output_type':of}

             tp=types[q]
             if tp!=None:
                ii['mode']=tp

             r=ck.access(ii)
             if r['return']==0:
                shutil.copy(of2,of3)

             print ' * converted'

   # Record run-time state to html
   if os.path.isfile(js):
      tt=os.path.getmtime(js)
      if tjs==None or tjs!=tt:
         tjs=tt

         r=ck.load_json_file({'json_file':js})
         if r['return']==0:
            d=r['dict']

            rts=d.get('run_time_state',{})

            risx=rts.get("input_size_x",'')
            risy=rts.get("input_size_y",'')
            rfps=rts.get("run_time_fps",'')
            rtt=rts.get("run_time_total",'')
            rf=rts.get("frames",'')

            rocld=rts.get("opencl_device", '')
            roclp=rts.get("opencl_platform",'')

            roclu=rts.get("opencl_device_units",'')
            if roclu=='': roclu='1'
            roclu=int(roclu)

            rompu=rts.get("openmp_max_threads",'')
            if rompu=='': rompu='1'
            rompu=int(rompu)
            if rompu=='-1': rompu=1

            threads=max(roclu, rompu)

            # Prepare html
            h=''
            h+='Average FPS: '+('%.2f' % rfps)+'<br>\n'

            h+='<br>\n'
            h+='FPS per thread: '+('%.2f' % (rfps/threads))+'<br>\n'
            h+='Threads: '+str(threads)+'<br>\n'

            h+='<br>\n'
            h+='Elapsed time: '+('%.2f' % rtt)+'<br>\n'
            h+='Frames: '+str(rf)+'<br>\n'
            h+='<br>\n'
            h+='Image: '+str(risx)+'x'+str(risy)+'<br>\n'
            h+='<br>\n'
            if roclp!='': 
               h+='OpenCL platform: '+roclp+'<br>\n'
            if rocld!='': 
               h+='OpenCL device: '+rocld+'<br>\n'

            r=ck.save_text_file({'text_file':jsh, 'string':h})

   # if html file doesn't exist, create dummy
   if not os.path.isfile(jsh):
      r=ck.save_text_file({'text_file':jsh, 'string':''})

   time.sleep(0.3)
