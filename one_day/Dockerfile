FROM ubuntu:20.04
ENV PATH="/root/miniconda3/bin:${PATH}"
ARG PATH="/root/miniconda3/bin:${PATH}"

LABEL maintainer="koldunovn@gmail.com"

RUN apt-get update
RUN apt-get install -y software-properties-common
RUN apt-add-repository -y universe
RUN apt-get update

RUN apt-get -y install make gfortran gcc g++ libblas-dev libopenmpi-dev
RUN apt-get -y install cmake vim git libnetcdf-dev libnetcdff-dev libpmi2-pmix
RUN apt-get -y install bzip2 curl wget

WORKDIR /fesom

RUN curl https://zenodo.org/record/3783716/files/pi.tar.gz -o pi.tar.gz
RUN curl https://zenodo.org/record/3783720/files/dCORE2.tar -o dCORE2.tar
RUN curl https://zenodo.org/record/3783724/files/phc3.tar.gz -o phc3.tar.gz

RUN tar -zxvf pi.tar.gz
RUN tar -xvf dCORE2.tar
RUN tar -zxvf phc3.tar.gz

RUN rm pi.tar.gz
RUN rm dCORE2.tar
RUN rm phc3.tar.gz

RUN wget \
    https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && mkdir /root/.conda \
    && bash Miniconda3-latest-Linux-x86_64.sh -b \
    && rm -f Miniconda3-latest-Linux-x86_64.sh
RUN conda --version
RUN conda config --add channels conda-forge
RUN conda config --set channel_priority strict
RUN git clone https://github.com/koldunovn/mkfesom.git
RUN cd mkfesom
WORKDIR "/fesom/mkfesom/"
RUN pip install -e .
WORKDIR /fesom/
RUN mkdir results


# COPY ./fesom2_latest/ /fesom/fesom2_indocker/

# RUN wget https://swift.dkrz.de/v1/dkrz_035d8f6ff058403bb42f8302e6badfbc/FESOM2.0_tutorial/FESOM2_minimum_input.tar
# RUN tar xvf FESOM2_minimum_input.tar
# RUN rm FESOM2_minimum_input.tar






