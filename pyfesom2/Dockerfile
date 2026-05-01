FROM ubuntu:22.04
ENV PATH="/opt/miniforge3/bin:${PATH}"
ARG PATH="/opt/miniforge3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update \
    && apt-get -y --allow-unauthenticated install git wget texlive

WORKDIR /pyfesom2/

# Two changes vs. the original recipe:
#   1. Use miniforge instead of Miniconda3. Recent conda releases gate
#      repo.anaconda.com/pkgs/{main,r} behind an interactive Terms-of-Service
#      acceptance, which fails non-interactively in docker build (see issue
#      "CondaToSNonInteractiveError"). Miniforge is the community installer
#      that defaults to conda-forge, ships mamba, and has no Anaconda TOS gate.
#   2. pyfesom2's ci/requirements-py37.yml pins fsspec==2021.06.1, scipy<=1.9
#      and python<=3.9, which conda-forge can no longer co-resolve since
#      Python 3.7 has been EOL since June 2023. Overwrite that file in place
#      with an unpinned env targeting Python 3.11 before mamba env update.
RUN wget \
    https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-Linux-x86_64.sh \
    && bash Miniforge3-Linux-x86_64.sh -b -p /opt/miniforge3 \
    && ln -s /opt/miniforge3/bin/conda /usr/bin/conda \
    && ln -s /opt/miniforge3/bin/mamba /usr/bin/mamba \
    && rm -f Miniforge3-Linux-x86_64.sh \
    && git clone https://github.com/FESOM/pyfesom2.git \
    && printf '%s\n' \
        'name: pyfesom2' \
        'channels:' \
        '  - conda-forge' \
        'dependencies:' \
        '  - python=3.11' \
        '  - pandas' \
        '  - numpy' \
        '  - netCDF4' \
        '  - joblib' \
        '  - pyresample' \
        '  - seawater' \
        '  - numba' \
        '  - scipy' \
        '  - cartopy' \
        '  - matplotlib' \
        '  - shapely' \
        '  - jupyter' \
        '  - ipython' \
        '  - pytest' \
        '  - cmocean' \
        '  - zarr' \
        '  - fsspec' \
        '  - requests' \
        '  - aiohttp' \
        '  - dask' \
        '  - xarray' \
        '  - pyproj' \
        '  - pymap3d' \
        '  - tqdm' \
        > ./pyfesom2/ci/requirements-py37.yml \
    && mamba env update -n base --file ./pyfesom2/ci/requirements-py37.yml

WORKDIR /pyfesom2/pyfesom2/
RUN pip install .
WORKDIR /pyfesom2/
RUN git clone https://github.com/FESOM/fdiag.git
WORKDIR /pyfesom2/fdiag/
RUN pip install .
WORKDIR /pyfesom2/
