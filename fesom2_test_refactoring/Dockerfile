FROM ubuntu:24.04
ENV PATH="/opt/miniconda3/bin:${PATH}"
ARG PATH="/opt/miniconda3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update \
  && apt-get install -y software-properties-common \
  && apt-add-repository -y universe \
  && apt-get update \
  && apt-get -y install make gfortran gcc g++ libblas-dev libopenmpi-dev \
  && apt-get -y install cmake vim git git-lfs libnetcdf-dev libnetcdff-dev libpmix-dev libpmi2-0-dev libpmi2-0t64 \
  && apt-get -y install wget \
  && apt-get -y install nco cdo netcdf-bin \
  && apt-get -y install python3-pip python3-tk libudunits2-dev libproj-dev proj-bin libgeos-dev libcunit1-dev \
  && apt-get -y install libhdf5-dev perl uuid-dev

WORKDIR /fesom/

RUN wget \
  https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
  && bash Miniconda3-latest-Linux-x86_64.sh -b -p /opt/miniconda3 \
  && ln -s /opt/miniconda3/bin/conda /usr/bin/conda \
  && rm -f Miniconda3-latest-Linux-x86_64.sh \
  && conda config --add channels conda-forge \
  && conda config --set channel_priority strict

RUN git clone https://github.com/FESOM/mkfesom.git
WORKDIR /fesom/mkfesom/
# setuptools 80 dropped the bundled pkg_resources module by default, but
# mkfesom's mkrun.py still does `import pkg_resources`. Pin to a version
# that still exposes it until mkfesom is migrated to importlib.resources.
RUN pip install 'setuptools<80' \
  && pip install -e .
WORKDIR /fesom/
RUN mkdir results

# XIOS 2.5: copy source + make_xios build to /xios. Sequential NetCDF is
# sufficient because the run-tests use XIOS in attached mode (no separate
# server ranks). The xios/ directory below is duplicated from
# fesom2_ci/xios/ — keep them in sync if the XIOS source ever needs to be
# refreshed.
#
# Two arch-GCC_LINUX overrides:
#   - .env: upstream hardcodes $HOME/hdf5 and $HOME/netcdf4; rewrite to Ubuntu
#     serial library paths so make_xios's `source arch.env` gives valid roots.
#   - .fcm: upstream BASE_CFLAGS sets -ansi (= C++98) which forbids C++11
#     lambdas as template args. XIOS 2.5 uses those (e.g. distribute_file_server2.cpp).
#     Append -std=c++11 to override -ansi for C++ compilation.
COPY xios /xios
RUN printf '%s\n' \
        'export HDF5_INC_DIR=/usr/include/hdf5/serial' \
        'export HDF5_LIB_DIR=/usr/lib/x86_64-linux-gnu/hdf5/serial' \
        'export NETCDF_INC_DIR=/usr/include' \
        'export NETCDF_LIB_DIR=/usr/lib/x86_64-linux-gnu' \
        > /xios/arch/arch-GCC_LINUX.env \
    && sed -i 's|^%BASE_CFLAGS .*|%BASE_CFLAGS    -ansi -w -fPIC -std=c++11|' \
        /xios/arch/arch-GCC_LINUX.fcm \
    && cd /xios \
    && ./make_xios --arch GCC_LINUX --fcm new \
                   --netcdf_lib netcdf4_seq --job $(nproc)







