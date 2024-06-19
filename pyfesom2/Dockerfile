FROM ubuntu:24.04
ENV PATH="/opt/miniconda3/bin:${PATH}"
ARG PATH="/opt/miniconda3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update \
    && apt-get -y --allow-unauthenticated install git wget texlive

WORKDIR /pyfesom2/

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
    && mamba env update -n base --file ./pyfesom2/ci/requirements-py37.yml

WORKDIR /pyfesom2/pyfesom2/
RUN pip install .
WORKDIR /pyfesom2/
RUN git clone https://github.com/FESOM/fdiag.git 
WORKDIR /pyfesom2/fdiag/
RUN pip install .
WORKDIR /pyfesom2/
