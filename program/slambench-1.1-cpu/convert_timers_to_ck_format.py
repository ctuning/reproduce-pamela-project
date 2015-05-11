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

f=open('tmp-output.tmp','r')
s=f.read()
f.close()

desc={}
values={}

l=s.split('\n')
if len(l)>0:
   x=l[0].split('\t')
   ch=0
   for q in x:
       qx='characteristic_'+str(ch)
       desc[qx]=q.strip()
       values[qx]=[]
       ch+=1

for k in range(1,len(l)):
    x=l[k].split('\t')
    ch=0
    for q in x:
        qx='characteristic_'+str(ch)
        values[qx].append(q)
        ch+=1

d['characteristics']=values
d['characteristics_desc']=desc

f=open('tmp-ck-timer.json','wt')
f.write(json.dumps(d, indent=2, sort_keys=True)+'\n')
f.close()
