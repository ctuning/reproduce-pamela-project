CK repository to reproduce SLAMBench from PAMELA project
========================================================

Shared research artifacts and workflows 
in the [Collective Knowledge format (CK)](http://cKnowledge.org)
to unify installation and execution of SLAMBench algorithms 
from the [EPSRC Pamela project](http://apt.cs.manchester.ac.uk/projects/PAMELA)
across diverse hardware, environments and data sets, 
perform SW/HW co-design, crowdsource and reproduce experiments.

Vision publication about how Collective Knowledge
can assist scientists to develop sustainable research software 
and help research projects to survive in a Cambrian AI/SW/HW chaos
or when leading developers leave:


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

* [Open challenges powered by CK](https://github.com/ctuning/ck/wiki/Research-and-development-challenges)

Support
=======
The [non-profit cTuning foundation (France)](http://cTuning.org)
and [dividiti Ltd (UK/US)](http://dividiti.com)
help academic and industrial projects to use
[Collective Knowledge framework (CK)](http://cKnowledge.org) and implement sustainable
and portable research software, share artifacts and workflows as reusable and
customizable components, crowdsource and reproduce experiments,
enable [collaborative AI/SW/HW co-design from IoT to supercomputers](http://cKnowledge.org/ai)
to trade-off speed, accuracy, energy, size and costs,
accelerate knowledge discovery, and facilitate technology transfer.
Contact [them](mailto:grigori.fursin@ctuning.org;anton@dividiti.com) 
for further details.

Prerequisites
=============
* Collective Knowledge Framework (CK): http://github.com/ctuning/ck

Installation
============

```
$ (sudo) pip install ck
$ ck pull repo:reproduce-pamela-project
```

Data set repositories
=====================

```
$ ck pull repo:reproduce-pamela-project-small-dataset
```

To obtain very large data set (4Gb), download it as zip
from our shared Google drive:

```
* https://drive.google.com/open?id=0B-wXENVfIO82S0lMQUZfVDVmc2c
```

and then install it via

```
$ ck add repo:reproduce-pamela-project-large-files --zip=ck-reproduce-pamela-2015-large-dataset.zip --quiet
```

Running workflow
================

```
$ ck compile program:slambench-1.1-cpu
$ ck run program:slambench-1.1-cpu

$ ck compile program:slambench-1.1-cpu-openmp
$ ck run program:slambench-1.1-cpu-openmp

$ ck compile program:slambench-1.1-cuda
$ ck run program:slambench-1.1-cuda

$ ck compile program:slambench-1.1-opencl
$ ck run program:slambench-1.1-opencl

$ ck compile program:slambench-1.1-opencl --target_os=android21-arm64
$ ck run program:slambench-1.1-opencl-dragon-board --target_os=android21-arm64
```

CK should automatically install missing dependencies, build SLAM and run it with plugged in data sets.
