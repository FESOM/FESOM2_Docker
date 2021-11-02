FROM ubuntu:20.04
ENV PATH="/opt/miniconda3/bin:${PATH}"
ARG PATH="/opt/miniconda3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update \
    && apt-get install -y software-properties-common \
    && apt-add-repository -y universe \
    && apt-get update \
    && apt-get -y install make gfortran gcc g++ libblas-dev libopenmpi-dev \
    && apt-get -y install cmake vim git git-lfs libnetcdf-dev libnetcdff-dev libpmi2-pmix \
    && apt-get -y install wget

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
RUN pip install -e .
WORKDIR /fesom/
RUN mkdir results







