#! /bin/sh

./generateKeys.sh server --batch
LD_LIBRARY_PATH=../lib ./keo_framework_example_simple_server
