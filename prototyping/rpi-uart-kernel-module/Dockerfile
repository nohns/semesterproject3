FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8

RUN apt-get update \
    && apt-get -y install \
    locales \
    sudo \
    vim-tiny \
    && sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen \
    && locale-gen \
    && apt-get -y install \
    binutils \
    build-essential \
    chrpath \
    cpio \
    diffstat \
    gawk \
    git \
    lz4 \
    python3 \
    python3-distutils \
    wget \
    zstd \
    && rm -rf /var/lib/apt/lists/*

RUN 

#RUN useradd -m -G sudo --uid=1000 -s /bin/bash yocto
#RUN install -d -o yocto -g yocto /yocto
#USER yocto

