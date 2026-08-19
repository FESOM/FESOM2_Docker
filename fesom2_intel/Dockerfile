# FESOM2 Intel compiler CI image
#
# Provides the toolchain used by FESOM/fesom2's fesom2_intel_tests.yml:
#   - Intel Fortran (ifx) + Intel MPI, with gcc/g++ underneath for C/C++
#   - HDF5 1.14.3, netCDF-C 4.9.2, netCDF-Fortran 4.6.1 built from source
#     against ifx, because Ubuntu's netCDF-Fortran is gcc-built and its
#     module files cannot be consumed by ifx
#
# Replaces ghcr.io/suvarchal/fesom2-ci-intel. That image is 4.27 GB
# compressed, of which one layer is 4141 MB (97%), because it installs the
# whole intel-hpckit meta package plus the Intel GPU runtime. FESOM uses
# neither: env/ubuntu/shell.intel asks for ifx and mpiifx and sets
# I_MPI_CC=gcc / I_MPI_CXX=g++, so DPC++, MKL, VTune, Advisor, TBB, IPP,
# DAL, CCL and the debugger are dead weight, and GitHub runners have no
# Intel GPU for the OpenCL / Level Zero packages to drive.
#
# Built and published by .github/workflows/docker-publish.yml to
# ghcr.io/fesom/fesom2_docker:fesom2_intel-<version>.

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# ---------------------------------------------------------------- oneAPI ---
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates curl gpg-agent \
    && curl -fsSL https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB \
       | gpg --dearmor > /usr/share/keyrings/intel-oneapi-archive-keyring.gpg \
    && echo "deb [signed-by=/usr/share/keyrings/intel-oneapi-archive-keyring.gpg] https://apt.repos.intel.com/oneapi all main" \
       > /etc/apt/sources.list.d/oneAPI.list \
    && rm -rf /var/lib/apt/lists/*

# Only the two components FESOM actually calls. intel-hpckit would pull in
# DPC++, MKL, VTune, Advisor, Inspector, TBB, IPP, DAL, CCL and the debugger
# for no benefit - that meta package is the entire size problem.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        intel-oneapi-compiler-fortran \
        intel-oneapi-mpi \
        intel-oneapi-mpi-devel \
    && rm -rf /var/lib/apt/lists/*

# ------------------------------------------------------- build toolchain ---
# gcc/g++ are not incidental: shell.intel sets I_MPI_CC=gcc and I_MPI_CXX=g++,
# so C and C++ are compiled by GCC even in the Intel build. Ubuntu 24.04's
# cmake is 3.28 and FESOM requires 3.16, so no Kitware repository is needed.
# lapack/blas are the system ones and are tiny; MKL is deliberately absent,
# as LAPACK is only linked when YAC is enabled, which this image does not do.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential gcc g++ \
        cmake make git wget pkg-config m4 \
        zlib1g-dev libcurl4-openssl-dev libssl-dev libxml2-dev \
        liblapack-dev libblas-dev \
    && rm -rf /var/lib/apt/lists/*

# ------------------------------------------------- HDF5 / netCDF for ifx ---
# Serial builds throughout: FESOM's Intel CI job compiles only, and the
# parallel stack is what makes these libraries painful to build against ifx.
WORKDIR /tmp

RUN /bin/bash -c "set -e \
    && . /opt/intel/oneapi/setvars.sh --force \
    && wget -q https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.14/hdf5-1.14.3/src/hdf5-1.14.3.tar.gz \
    && tar -xzf hdf5-1.14.3.tar.gz && cd hdf5-1.14.3 \
    && CC=gcc FC=ifx CFLAGS='-O2 -fPIC' FCFLAGS='-O2 -fPIC' ./configure \
         --prefix=/usr/local --enable-fortran --disable-parallel \
         --enable-shared --disable-static --enable-threadsafe --enable-unsupported \
    && make -j\$(nproc) && make install \
    && cd .. && rm -rf hdf5-1.14.3*"

RUN /bin/bash -c "set -e \
    && . /opt/intel/oneapi/setvars.sh --force \
    && wget -q https://downloads.unidata.ucar.edu/netcdf-c/4.9.2/netcdf-c-4.9.2.tar.gz \
    && tar -xzf netcdf-c-4.9.2.tar.gz && cd netcdf-c-4.9.2 \
    && CC=gcc CFLAGS='-O2 -fPIC' CPPFLAGS='-I/usr/local/include' LDFLAGS='-L/usr/local/lib' ./configure \
         --prefix=/usr/local --enable-shared --disable-static --enable-netcdf-4 \
         --disable-parallel-tests --disable-pnetcdf --disable-byterange --disable-dap \
    && make -j\$(nproc) && make install \
    && cd .. && rm -rf netcdf-c-4.9.2*"

# -assume byterecl is what makes the Fortran bindings usable from ifx; without
# it record lengths are counted in words and integer I/O comes back wrong.
RUN /bin/bash -c "set -e \
    && . /opt/intel/oneapi/setvars.sh --force \
    && wget -q https://downloads.unidata.ucar.edu/netcdf-fortran/4.6.1/netcdf-fortran-4.6.1.tar.gz \
    && tar -xzf netcdf-fortran-4.6.1.tar.gz && cd netcdf-fortran-4.6.1 \
    && FC=ifx CC=gcc FCFLAGS='-O2 -fPIC -assume byterecl' CFLAGS='-O2 -fPIC' \
       CPPFLAGS='-I/usr/local/include' LDFLAGS='-L/usr/local/lib' \
       LIBS='-lnetcdf -lhdf5_hl -lhdf5 -lz -lcurl' ./configure \
         --prefix=/usr/local --enable-shared --disable-static \
    && make -j\$(nproc) && make install \
    && cd .. && rm -rf netcdf-fortran-4.6.1*"

RUN echo "/usr/local/lib" >> /etc/ld.so.conf.d/local.conf && ldconfig

ENV NETCDF_ROOT=/usr/local
ENV NETCDF_Fortran_ROOT=/usr/local
ENV HDF5_ROOT=/usr/local

# Serial-netCDF-safe runtime settings, carried over from the image this
# replaces. HDF5 file locking in particular breaks on some CI filesystems.
ENV HDF5_USE_FILE_LOCKING=FALSE
ENV NETCDF_ASYNC_DISABLE=1
ENV FOR_COARRAY_NUM_IMAGES=1
ENV KMP_STACKSIZE=64m
ENV OMP_STACKSIZE=64m
ENV I_MPI_ASYNC_PROGRESS=0
ENV I_MPI_THREAD_LEVEL=single

WORKDIR /workspace

# FESOM's env/ubuntu/shell.intel sources setvars.sh itself, so the entrypoint
# only has to make an interactive shell usable.
RUN printf '%s\n' \
      '#!/bin/bash' \
      '. /opt/intel/oneapi/setvars.sh --force >/dev/null' \
      'ulimit -s unlimited' \
      'exec "$@"' \
      > /entrypoint.sh \
    && chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
CMD ["/bin/bash"]
