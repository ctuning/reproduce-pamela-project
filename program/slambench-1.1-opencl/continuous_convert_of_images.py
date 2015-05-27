import ck.kernel as ck
import time
import os
import shutil

print ('Starting continuous convert of images - Press Ctrl-C to stop')

files=["tmp/tmp-raw-input-rgb.rgb", "tmp/tmp-raw-depthrender.rgb", "tmp/tmp-raw-trackrender.rgb", "tmp/tmp-raw-volumerender.rgb"]
tfiles=[None,None,None,None]
width=[640,320,320,320]
height=[480,240,240,240]
types=[None,'CMYK','CMYK','CMYK']
output=['png','jpeg','jpeg','jpeg']

js='tmp/tmp-ck-timer.json'
jsh='tmp/tmp-ck-timer.json.html'
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
             of2=fn+'.'+of+'.tmp'

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
                shutil.copy(of2,of1)

             print ' * converted'

   # Record run-time state to html
   if os.path.isfile(js):
      tt=os.path.getmtime(js)
      if tjs==None or tjs!=tt:
         tjs=tt

         r=ck.load_json_file({'json_file':js})
         if r['return']==0:
            d=r['dict']

            h='Total FPS='+str(d.get('features',{}).get('run_time_fps',''))+'\n'

            r=ck.save_text_file({'text_file':jsh, 'string':h})

   # if html file doesn't exist, creat dummy
   if not os.path.isfile(jsh):
      r=ck.save_text_file({'text_file':jsh, 'string':''})

   time.sleep(0.3)
