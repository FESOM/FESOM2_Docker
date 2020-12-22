FROM ubuntu:20.04
ENV PATH="/root/miniconda3/bin:${PATH}"
ARG PATH="/root/miniconda3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-add-repository -y universe
RUN apt-get update

RUN apt-get -y install make gfortran gcc g++ libblas-dev libopenmpi-dev
RUN apt-get -y install cmake vim git git-lfs libnetcdf-dev libnetcdff-dev libpmi2-pmix
RUN apt-get -y install wget

WORKDIR /fesom/

RUN wget \
    https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && mkdir /root/.conda \
    && bash Miniconda3-latest-Linux-x86_64.sh -b \
    && rm -f Miniconda3-latest-Linux-x86_64.sh
RUN conda --version
RUN conda config --add channels conda-forge
RUN conda config --set channel_priority strict
RUN git clone https://github.com/koldunovn/mkfesom.git
WORKDIR /fesom/mkfesom/
RUN pip install -e .
WORKDIR /fesom/
RUN mkdir results







