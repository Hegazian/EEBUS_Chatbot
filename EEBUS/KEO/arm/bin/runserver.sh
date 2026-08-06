#! /bin/sh

cert_file="server_prime256v1CertDER.bin"
key_file="server_prime256v1KeyDER.bin"

if [ ! -f "$cert_file" ] || [ ! -f "$key_file" ]; then
    ./generateKeys.sh server --batch
fi

LD_LIBRARY_PATH=../lib ./keo_framework_example_simple_server
