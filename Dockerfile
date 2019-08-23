# Copyright 2019 Qwant Research. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

FROM ubuntu:18.04

LABEL authors="Christophe Servan"

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

ENV TZ=Europe/Paris
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get -y update && \
    apt-get -y install \
        cmake \
        g++ \
        libboost-locale1.65-dev \
        libboost-regex1.65-dev \
        libyaml-cpp-dev \
        git \
        cmake

COPY . /opt/dbpl-util

WORKDIR /opt/dbpl-util

RUN git submodule update --init --recursive

# RUN mkdir build -pv && cd build && cmake .. && make -j install
RUN bash ./install.sh

RUN groupadd -r qnlp && useradd --system -s /bin/bash -g qnlp qnlp

USER qnlp 

ENTRYPOINT ["/usr/local/bin/dblp-extractor"]
