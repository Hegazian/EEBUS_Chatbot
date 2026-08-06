#!/bin/bash

pushd ./KEO/src/spine
rm ../../arm/lib/libkeo_s*
rm ../../arm/lib/libkeo_framework.so*
rm -r ./install/

cmake -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_TOOLCHAIN_FILE=./bebro-2.2.3.cmake -DKEO_SPINE_DATAGRAM_ROOT=../../arm/ . && make install
cp -r ./install/* ../../arm/
