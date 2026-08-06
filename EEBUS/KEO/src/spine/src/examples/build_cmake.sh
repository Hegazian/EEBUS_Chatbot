#!/bin/bash

PRJ_TOP_DIR=`pwd`/..

mkdir -p ../build

pushd ../build

cmake \
    -DKEO_SPINE_ROOT=${PRJ_TOP_DIR} \
    -DCMAKE_BUILD_TYPE=DEBUG \
    -DCMAKE_ECLIPSE_VERSION=4.5 \
    -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
    -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 \
    -G "Eclipse CDT4 - Unix Makefiles" \
    ../examples

rc=$?
if [[ $rc != 0 ]] ; then
    echo "Configure failed. Aborting ..."
    exit $rc
fi

cmake --build . -- -j $(getconf _NPROCESSORS_ONLN)

popd
