#!/bin/echo docker build . -f
# -*- coding: utf-8 -*-

FROM debian:10
LABEL maintainer "Philippe Coval (rzr@users.sf.net)"

ENV project trako
ENV workdir /usr/local/opt/${project}/src/${project}
WORKDIR ${workdir}/

RUN set -x \
  && apt-get update \
  && apt-get install -y \
    g++ \
    make \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && sync

ADD Makefile ${workdir}/

RUN set -x \
  && make rule/debian/setup \
  && sync

ADD . ${workdir}

RUN set -x \
  && make run \
  && sync
