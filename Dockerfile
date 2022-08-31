FROM ubuntu:focal-20220801

ENV DEBIAN_FRONTEND noninteractive
ENV LANG en_US.UTF-8

# Note: 'set -x' enables a mode of shell where all executed commands are printed to the terminal for debugging

RUN set -x \
  && apt-get update -y \
  && apt-get install -y locales \
  && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8 \
  && apt-get --no-install-recommends install -fy \
    sudo \
    git \
    make \
    cmake \
    automake \
    g++ \
    libtool \
    lsb-release \
    ninja-build \
    shellcheck \
    wget \
    ca-certificates \
  && update-ca-certificates \
  && (cd /tmp \
    && wget --tries 4 --no-check-certificate --quiet -c https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2017q2/gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 \
    && sudo tar xjf gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 -C /opt \
    && rm gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 \
    && sudo ln -s -f /opt/gcc-arm-none-eabi-6-2017-q2-update/bin/* /usr/local/bin/.)

WORKDIR /app
COPY . .

CMD set -x && make
