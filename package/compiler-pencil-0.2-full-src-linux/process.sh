#! /bin/bash

#
# Installation script for CK packages.
#
# See CK LICENSE.txt for licensing details.
# See CK Copyright.txt for copyright details.
#
# Developer(s): Grigori Fursin, 2015
#

# PACKAGE_DIR
# INSTALL_DIR

export PACKAGE_NAME=pencil-driver-0.2
export PACKAGE_NAME_ORIG=$PACKAGE_NAME

cd ${INSTALL_DIR}

cp ${PACKAGE_DIR}/${PACKAGE_NAME}.tar.bz2 .
bzip2 -d ${PACKAGE_NAME}.tar.bz2
tar xvf ${PACKAGE_NAME}.tar
rm ${PACKAGE_NAME}.tar

cd ${PACKAGE_NAME}

mkdir _build
cd _build

cd $PACKAGE_NAME
../configure --prefix=$INSTALL_DIR/_install
 if [ "${?}" != "0" ] ; then
  echo "Error: Compilation failed in $PWD!" 
  exit 1
 fi

make
 if [ "${?}" != "0" ] ; then
  echo "Error: Compilation failed in $PWD!" 
  exit 1
 fi

make install
 if [ "${?}" != "0" ] ; then
  echo "Error: Compilation failed in $PWD!" 
  exit 1
 fi
