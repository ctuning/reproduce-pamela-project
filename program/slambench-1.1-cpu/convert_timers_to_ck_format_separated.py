#
# Converting raw slambench timing to CK universal 
# autotuning and machine learning format
#
# Collective Knowledge (CK)
#
# See CK LICENSE.txt for licensing details.
# See CK COPYRIGHT.txt for copyright details.
#
# Developer: Grigori Fursin
#

import json

d={}

print ('Converting fine-grain timers from slambench to CK format ...')

# Preload tmp-ck-timer.json from OpenME if there
exists=True
try:
  f=open('tmp-ck-timer.json', 'r')
except Exception as e:
  print ('')
  print ('Error: OpenME tmp-ck-timer.json output file was not produced - program execution likely failed!')

  exit(1)

  # originally I wanted it work even if this file from OpenME 
  # is not generated, but then we had a problem detecting
  # OpenCL failures. Hence I now quit with error

  exists=False
  pass

if exists:
   try:
     s=f.read()
     d=json.loads(s)
   except Exception as e:
     exists=False
     pass

   if exists:
      f.close()

# Load kernel info from slambench
f=open('tmp-output.tmp','r')
s=f.read()
f.close()

desc={} # -> should move to meta desc of this program

l=s.split('\n')
ll=len(l)
if ll>0:
   x=l[0].split('\t')
   ch=0
   for q in x:
       qn=q.strip()
       qx='execution_time_kernel_'+str(qn)
       desc[ch]=qx
       d[qx]=[]
       ch+=1

for k in range(1,ll):
    x=l[k].split('\t')
    ch=0
    if len(x)>1:
       for q in x:
           qx=desc[ch]
           qv=q.strip()
           try: qv=float(qv)
           except ValueError: pass
           d[qx].append(qv)
           ch+=1

# Check fps
if ll>2:
   rll=ll-2

   d['frames']=rll
   ket=d.get('execution_time_kernel_total',[])
   if len(ket)>0:
      fs=0.0
      for f in ket:
          fs+=f
      d['total_execution_time_from_kernels']=fs
      if fs>0:
         fps=float(rll)/fs
         d['fps']=fps

# Write CK json
f=open('tmp-ck-timer.json','wt')
f.write(json.dumps(d, indent=2, sort_keys=True)+'\n')
f.close()
