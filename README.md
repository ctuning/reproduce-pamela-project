CK repository to reproduce Pamela project
=========================================

Shared artifacts to reproduce and extend techniques from 
the UK Pamela project, and to connect them to CK-powered 
universal autotuning, predictive analytics and run-time 
adaptation.

It is used in several CK Getting Started Guide examples:
https://github.com/ctuning/ck/wiki

Prerequisites
=============
* Collective Knowledge Framework: http://github.com/ctuning/ck

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
