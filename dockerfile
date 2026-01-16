FROM ubuntu:24.04

WORKDIR /home/ubuntu/

RUN apt-get update && apt-get install -y \
    build-essential git make nano \
    pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
    libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
    libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
    libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
    libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev \
    libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev

RUN git clone https://github.com/KushalP17/Render3DSDL.git \
    && cd Render3DSDL \
    && git submodule update --init --recursive \
    && cmake -S . -B build \
    && cmake --build build
