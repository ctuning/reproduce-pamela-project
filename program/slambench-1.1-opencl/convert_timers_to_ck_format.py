#
# Converting raw slambench timing to CK universal 
# autotuning and machine learning format
#
# Collective Knowledge (CK)
#
# See CK LICENSE.txt for licensing details.
# See CK Copyright.txt for copyright details.
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
       qx='characteristic_'+str(ch)
       desc[qx]=q.strip()
       d[qx]=[]
       ch+=1

for k in range(1,ll):
    x=l[k].split('\t')
    ch=0
    for q in x:
        qx='characteristic_'+str(ch)
        d[qx].append(q.strip())
        ch+=1

# Check fps
if ll>2:
   rll=ll-2

   d['frames']=rll
   ket=d.get('kernel_execution_time',[])
   if len(ket)>0:
      dket=ket[0]
      fps=float(rll)/dket
      d['fps']=fps

# Write CK json
f=open('tmp-ck-timer.json','wt')
f.write(json.dumps(d, indent=2, sort_keys=True)+'\n')
f.close()