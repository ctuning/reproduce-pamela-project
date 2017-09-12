CK repository to reproduce SLAMBench from PAMELA project
========================================================

Shared artifacts and workflows in the [http://github.com/ctuning/ck CK format] 
to simplify installation and execution of SLAMBench algorithms 
across diverse hardware and environments, 
connect it to CK-powered universal and multi-objective autotuning, crowd-tuning,
predictive analytics and run-time adaptation plugins, 
and to reproduce and extend techniques from the UK Pamela project.

This is a part of our long-term [open research initiative](http://cKnowledge.org)
to collaboratively co-design real applications across the whole SW/HW stack:

* https://github.com/dividiti/ck-caffe
* https://github.com/ctuning/ck-tensorflow
* https://github.com/ctuning/ck-caffe2

* https://github.com/ctuning/ck-wa
* https://github.com/ctuning/ck/wiki/Demo-ARM-TechCon'16


* [Related publications](https://github.com/ctuning/ck/wiki/Publications)

```
@inproceedings{ck-date16,
    title = {{Collective Knowledge}: towards {R\&D} sustainability},
    author = {Fursin, Grigori and Lokhmotov, Anton and Plowman, Ed},
    booktitle = {Proceedings of the Conference on Design, Automation and Test in Europe (DATE'16)},
    year = {2016},
    month = {March},
    url = {https://www.researchgate.net/publication/304010295_Collective_Knowledge_Towards_RD_Sustainability}
}
```

* [Open challenges](https://github.com/ctuning/ck/wiki/Research-and-development-challenges)!</b>

Prerequisites
=============
* Collective Knowledge Framework (CK): http://github.com/ctuning/ck

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

Running workflow
================
ck run program:slambench-1.1-cpu
ck run program:slambench-1.1-cpu-openmp
ck run program:slambench-1.1-cuda
ck run program:slambench-1.1-opencl
ck run program:slambench-1.1-opencl-dragon-board

CK should automatically install missing dependencies, build SLAM and run it with plugged in data sets
