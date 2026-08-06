#! /bin/sh

./generateKeys.sh client --batch
LD_LIBRARY_PATH=../lib ./keo_framework_example_simple_client
