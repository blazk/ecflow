#!/bin/sh
# ==================================================================
# Error handling
set -e # stop the shell on first error
set -u # fail when using an undefined variable

# ====================================================================
show_error_and_exit() {
   echo "install.sh "
   echo " install.sh  [prefix]"
   echo "  "
   echo "   prefix         - prefix directory for install"
   exit 1
}

prefix_arg=/var/tmp/$USER/cmake/ecflow
if  [[ "$#" = 1 ]] ; then
   prefix_arg=$1
fi

set -x # echo script lines as they are executed

#===================================================================
mkdir -p build
cd build

#===================================================================
# cmake
# -DCMAKE_PYTHON_INSTALL_TYPE = [ local | setup ]
# -DCMAKE_PYTHON_INSTALL_PREFIX should *only* used when using python setup.py (CMAKE_PYTHON_INSTALL_TYPE=setup)
#   *AND* for testing python install to local directory
#
# Boost:  
#  By default it looks for environment variable BOOST_ROOT, if not it can specified on the command line. i.e
#  -DBOOST_ROOT=/var/tmp/ma0/boost/boost_1_53_0

cmake .. 
         # -DCMAKE_INSTALL_PREFIX=$prefix_arg  \
         # -DCMAKE_BUILD_TYPE=Release 
         # -DENABLE_GUI=OFF    \
         # -DENABLE_PYTHON=OFF  \
         # -DCMAKE_PYTHON_INSTALL_TYPE=local \
         # -DCMAKE_CXX_FLAGS="-Wall -Wno-unused-local-typedefs" \
         # -DCMAKE_CXX_COMPILER=xlC_r"
         # -DBOOST_ROOT=/var/tmp/$USER/boost/boost_1_53_0
         
make -j8
make install
             