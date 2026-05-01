FROM ubuntu:22.04
ENV PATH="/opt/miniconda3/bin:${PATH}"
ARG PATH="/opt/miniconda3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update \
    && apt-get -y --allow-unauthenticated install git wget texlive

WORKDIR /pyfesom2/

# pyfesom2's ci/requirements-py37.yml pins fsspec==2021.06.1, scipy<=1.9 and
# python<=3.9, which conda-forge can no longer co-resolve since Python 3.7
# has been EOL since June 2023 and many of those pinned versions have been
# pruned from the channel. Override the cloned file with an unpinned env
# targeting Python 3.11 before running mamba env update; this keeps the
# rest of the image (conda+mamba layout, pip install of pyfesom2 and fdiag
# below) intact.
RUN wget \
    https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && bash Miniconda3-latest-Linux-x86_64.sh -b -p /opt/miniconda3 \
    && ln -s /opt/miniconda3/bin/conda /usr/bin/conda \
    && rm -f Miniconda3-latest-Linux-x86_64.sh \
    && conda config --add channels conda-forge \
    && conda config --set channel_priority strict \
    && conda install -y mamba \
    && ln -s /opt/miniconda3/bin/mamba /usr/bin/mamba \
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
