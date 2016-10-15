CK repository to reproduce SLAMBench from PAMELA project
========================================================

Shared artifacts and workflows in the [http://github.com/ctuning/ck CK format] 
to simplify execution of SLAMBench across diverse hardware and environments, 
connect it to CK-powered universal and multi-objective autotuning, crowd-tuning,
predictive analytics and run-time adaptation plugins, 
and to reproduce and extend techniques from the UK Pamela project.

<b>Note that we gradually discontinue support for such ad-hoc benchmarks. 
Instead we have switched to a community-driven optimization of real applications 
such as DNN and BLAS together with General Motors ([CK-Caffe](https://github.com/dividiti/ck-caffe )), 
ARM ([CK-WA project](https://github.com/ctuning/ck-wa)) and others. 
Check [1](http://schedule.armtechcon.com/session/know-your-workloads-design-more-efficient-systems), 
[2](http://bit.ly/ck-date16), [3](http://arxiv.org/abs/1506.06256) 
and [4](http://hal.inria.fr/hal-01054763) for our long-term vision. 
You are very welcome to join our collaborative optimization effort 
and participate in our [open challenges](https://github.com/ctuning/ck/wiki/Research-and-development-challenges)!</b>

Status
======
<i>Should work but support discontinued in favour [CK-Caffe](http://github.com/dividiti/ck-caffe) 
and [CK-WA](https://github.com/ctuning/ck-wa) community-driven projects.</i>

Prerequisites
=============
* Collective Knowledge Framework (CK): http://github.com/ctuning/ck . 

CK will automatically install SLAMBench with all dependencies and prepare
experimental workflows.

Installation
============

$ ck pull repo:reproduce-pamela-project

Data set repositories
=====================

$ ck pull repo:reproduce-pamela-project-small-dataset

To obtain very large data set (4Gb), download it as zip
from our shared Google drive:

* https://drive.google.com/open?id=0B-wXENVfIO82S0lMQUZfVDVmc2c

and then install it via

$ ck add repo:reproduce-pamela-project-large-files --zip=ck-reproduce-pamela-2015-large-dataset.zip --quiet
