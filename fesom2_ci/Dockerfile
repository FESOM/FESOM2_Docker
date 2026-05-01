# FESOM2 CI build-test image
#
# Provides the toolchain used by FESOM/fesom2's build-test workflow:
#   - GCC + OpenMPI + NetCDF/HDF5 + LAPACK
#   - OASIS3-MCT prebuilt at /oasis (CMake build)
#   - XIOS 2.5 prebuilt at /xios (make_xios with arch-GCC_LINUX, sequential netcdf)
#
# Built and published by .github/workflows/docker-publish.yml in this repo to
# ghcr.io/fesom/fesom2_docker:fesom2_ci-<version>. FESOM/fesom2's
# fesom2_build_tests.yml runs inside this image and copies /oasis and /xios
# into the workspace before configuring CMake.

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    make \
    git \
    wget \
    curl \
    gfortran \
    gcc \
    g++ \
    libopenmpi-dev \
    openmpi-bin \
    libnetcdf-dev \
    libnetcdf-mpi-dev \
    libnetcdff-dev \
    libhdf5-dev \
    libhdf5-openmpi-dev \
    libhdf5-fortran-102 \
    libhdf5-openmpi-fortran-102 \
    liblapack-dev \
    libblas-dev \
    libopenblas-dev \
    pkg-config \
    perl \
    uuid-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ENV OMPI_ALLOW_RUN_AS_ROOT=1
ENV OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1
ENV FC=mpifort
ENV CC=mpicc
ENV CXX=mpicxx
ENV LAPACK_LIBRARIES=/usr/lib/x86_64-linux-gnu/liblapack.so.3
ENV CMAKE_ARGS=-DLAPACK_LIBRARIES=/usr/lib/x86_64-linux-gnu/liblapack.so.3
ENV FESOM_PLATFORM_STRATEGY=ubuntu

# OASIS3-MCT: clone + CMake build to /oasis. The fesom2 workflow then does
# `cp -rf /oasis ../` and FESOM's FindOASIS.cmake picks it up.
RUN git clone --depth 1 https://gitlab.dkrz.de/ec-earth/oasis3-mct.git /oasis \
    && cd /oasis \
    && mkdir -p build \
    && cd build \
    && cmake ../ -DCMAKE_POLICY_VERSION_MINIMUM=3.5 -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    && make -j$(nproc)

# XIOS 2.5: clone + make_xios build to /xios. Sequential NetCDF is sufficient
# for a build/link test of FESOM's __XIOS code path (CI doesn't run XIOS).
ENV NETCDF_INC_DIR=/usr/include
ENV NETCDF_LIB_DIR=/usr/lib/x86_64-linux-gnu
ENV HDF5_INC_DIR=/usr/include/hdf5/serial
ENV HDF5_LIB_DIR=/usr/lib/x86_64-linux-gnu/hdf5/serial
RUN git clone --depth 1 https://gitlab.dkrz.de/ec-earth/xios-2.5-ece.git /xios \
    && cd /xios \
    && ./make_xios --arch GCC_LINUX --netcdf_lib netcdf4_seq --job $(nproc)

WORKDIR /
