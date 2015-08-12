# Copyright (c) 2015 Grigori Fursin
# CK License (standard 3 clause BSD)

import json

d={}

print ('Converting checkPos output to CK format ...')

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
f=open('tmp-output-check-pos.tmp','r')
s=f.read()
f.close()

desc={} # -> should move to meta desc of this program

ate_min=''
ate_max=''
ate_mean=''

# Detect:
#                  ATE 	Min : 0.000000 	Max : 0.007339 	Mean : 0.004198 	Total : 0.08395142

l=s.split('\n')
ll=len(l)
for k in range(1,ll):
    x=l[k].strip()

    i1=x.find('ATE')
    i2=x.find('Min : ')
    i3=x.find('Max : ')
    i4=x.find('Mean : ')

    if i1>=0 and i2>0 and i3>0 and i4>0:
       j2=x.find(' ', i2+6)
       j3=x.find(' ', i3+6)
       j4=x.find(' ', i4+7)
 
       if j2>0 and j3>0 and j4>0:
          ate_min=x[i2+6:j2]
          ate_max=x[i3+6:j3]
          ate_mean=x[i4+7:j4]

          d['accuracy_ate_min']=float(ate_min)
          d['accuracy_ate_max']=float(ate_max)
          d['accuracy_ate_mean']=float(ate_mean)

          break

# Write CK json
f=open('tmp-ck-timer.json','wt')
f.write(json.dumps(d, indent=2, sort_keys=True)+'\n')
f.close()
