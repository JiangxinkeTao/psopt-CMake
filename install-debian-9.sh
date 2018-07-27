#!/bin/bash
# Install script for Debian 9. This installation procedure will install all
# the dependeces required under $HOME/local

## Installation directories
prefix=$HOME/local
SRC_DIR=$prefix/src
INC_DIR=$prefix/include
LIB_DIR=$prefix/lib
LIB64_DIR=$prefix/lib64 #TODO try to eliminate the need to include this
                        # directory by changing the prefix in the adolc
                        # installation process

## Packages versions or branches
IPOPT=Ipopt-3.12.3
ADOLC=ADOL-C-2.5.2
COLPACK=ColPack-1.0.9
SUITESPARSE=SuiteSparse-4.4.3
LUSOL=lusol
PSOPT=psopt-debian-9-installer

## Set the compiler search paths
export C_INCLUDE_PATH=$C_INCLUDE_PATH:$INC_DIR
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$INC_DIR
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LIB_PATH:$LIB64_PATH

## Create install dir if it does not exist
if [! -f $prefix]
  mkdir -p $prefix $SRC_DIR $INC_DIR $LIB_DIR $LIB64_DIR
fi

## Required packages available in Debian 9 main repo
## also available in Ubuntu 16.04
sudo apt-get -y install g++ gfortran f2c libf2c2 libf2c2-dev libblas3 \
  libblas-dev libopenblas-base libopenblas-dev libatlas-base-dev \
  liblapack3 liblapack-dev

## Get IPOPT
IPOPT_DIR=$SRC_DIR/$IPOPT
if [! -f $IPOPT_DIR]
  wget -P $SRC_DIR https://www.coin-or.org/download/source/Ipopt/$IPOPT.tgz
  tar  -C $SRC_DIR -xzf $IPOPT_DIR.tgz
  rm -f $IPOPT_DIR.tgz
fi

## Get METIS (IPOPT dependence)
METIS_DIR=$IPOPT_DIR/ThirdParty/Metis
if [! -f $METIS_DIR]
  cd $METIS_DIR
  ./get.Metis
fi

## Get MUMPS (IPOPT dependence)
MUMPS_DIR=$IPOPT_DIR/ThirdParty/Mumps
if [! -f $MUMPS_DIR]
  cd $MUMPS_DIR
  ./get.Mumps
fi

## Build and install IPOPT, METIS AND MUMPS
cd $IPOPT_DIR
./configure --prefix=$prefix --enable-static coin_skip_warn_cxxflags=yes
make -j
make install

## Get ADOL-C
ADOLC_DIR=$SRC_DIR/$ADOLC
if [! -f $ADOLC_DIR]
  wget -P $SRC_DIR https://www.coin-or.org/download/source/ADOL-C/$ADOLC.tgz
  tar  -C $SRC_DIR -xzf $ADOLC_DIR.tgz
  rm -f $ADOLC_DIR.tgz
fi 

## Get ColPack (ADOL-C dependence)
COLPACK_DIR=$ADOLC_DIR/ThirdParty/$COLPACK
if [! -f $COLPACK_DIR]
  wget -P $COLPACK_DIR https://cscapes.cs.purdue.edu/download/ColPack/$COLPACK.tar.gz
  tar  -C $COLPACK_DIR -xzf $COLPACK_DIR.tar.gz
  rm -f $COLPACK_DIR.tar.gz
fi

## Build and compile ColPack
cd $COLPACK_DIR
./configure --prefix=$prefix
make -j
make install

## Build and compile ADOL-C
cd $ADOLC_DIR
./configure --prefix=$prefix --enable-sparse --with-colpack=$COLPACK_DIR
make -j
make install

## PDFlib is non-free, see psopt install instructions if you want to
## install it. This package is optional

## GNUplot is optional, see psopt install isntruction if you want to install from source.
## installing from debian 9 main repo
sudo apt-get -y install libx11-dev libxt-dev libgd2-xpm-dev \
  libreadline6-dev gnuplot libgnuplot-iostream-dev

## Get PSOPT
PSOPT_DIR=$SRC_DIR/$PSOPT
if [! -f $PSOPT_DIR]
  wget -P $SRC_DIR https://github.com/ViniciusALima/psopt/archive/$PSOPT.tar.gz
  tar -C $SRC_DIR -xzf $PSOPT_DIR.tar.gz
  rm -f $PSOPT_DIR.tar.gz
fi

## Get SuiteSparse (PSOPT dependence)
SUITESPARSE_DIR=$PSOPT_DIR/$SUITESPARSE
if [! -f $SUITESPARSE_DIR]
  wget -P $PSOPT_DIR http://faculty.cse.tamu.edu/davis/SuiteSparse/$SUITESPARSE.tar.gz
  tar  -C $PSOPT_DIR -xzf $SUITESPARSE_DIR.tar.gz
  rm -f $SUITESPARSE_DIR.tar.gz
fi

## Get Lusol (PSOPT dependence)
LUSOL_DIR=$PSOPT_DIR/$LUSOL
if [! -f $LUSOL_DIR]
  wget -P $PSOPT_DIR http://stanford.edu/group/SOL/software/lusol/$LUSOL.zip
  unzip $PSOPT_DIR/LUSOL.zip -d $PSOPT_DIR
fi

## Build and install PSOPT, SuiteSparse and Lusol
cd $PSOPT_DIR
make -j all

