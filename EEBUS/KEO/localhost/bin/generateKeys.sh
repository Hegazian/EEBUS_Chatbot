#!/bin/bash

CURVE=prime256v1
SUBJ="
C=DE
ST=NRW
O=KEO
localityName=Cologne
commonName=${HOSTNAME}.local
organizationalUnitName=Development
emailAddress=devel@kellendonk.de
"


usage()
{
    echo "Usage: $(basename $0) <PREFIX> [ { --force | --batch } ]"
    echo "  <PREFIX> will result in: <PREFIX>_${CURVE}CertDER.bin, <PREFIX>_${CURVE}KeyDER.bin"
    echo "  --force will overwrite existing files"
    echo "  --batch will not ask and not overwrite existing files"
    exit 1
}

function genkey()
{
    echo "Generate cert/key pair: (${1}_${CURVE}CertDER.bin / ${1}_${CURVE}KeyDER.bin)"
    openssl ecparam -out ${1}_${CURVE}params.pem -name ${CURVE} -genkey
    openssl req -new -batch -subj "$(echo -n "${SUBJ}" | tr "\n" "/")" -x509 -newkey ec:${1}_${CURVE}params.pem -keyform PEM -keyout ${1}_${CURVE}Key.pem -out ${1}_${CURVE}Cert.pem -outform PEM -days 3650 -set_serial 1234 -nodes
    openssl x509 -in ${1}_${CURVE}Cert.pem -inform PEM -out ${1}_${CURVE}CertDER.bin -outform DER
    openssl ec -in ${1}_${CURVE}Key.pem -outform DER -out ${1}_${CURVE}KeyDER.bin
    rm -f ${1}_${CURVE}params.pem ${1}_${CURVE}Key.pem ${1}_${CURVE}Cert.pem
}

function genkey_ask()
{
if [ -e  ${1}_${CURVE}CertDER.bin ] || [ -e  ${1}_${CURVE}KeyDER.bin ]
then
    read -p "The cert/key pair, or one part of it, (${1}_${CURVE}CertDER.bin / ${1}_${CURVE}KeyDER.bin) already exists, overwrite? " -n 1 -r
    echo    # (optional) move to a new line
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        genkey $1
    fi
else
    genkey $1
fi
}

function genkey_batch()
{
if [ -e  ${1}_${CURVE}CertDER.bin ] || [ -e  ${1}_${CURVE}KeyDER.bin ]
then
    echo "The cert/key pair, or one part of it, (${1}_${CURVE}CertDER.bin / ${1}_${CURVE}KeyDER.bin) already exists!"
else
    genkey $1
fi
}

[ $# -lt 1 ] && usage

_prefix=$1
shift


if [ $# -eq 1 ] && [ "$1" == "--force" ]
then
    genkey ${_prefix}
else
    if [ $# -eq 1 ] && [ "$1" == "--batch" ]
    then
        genkey_batch ${_prefix}
    else
        if [ $# -eq 0 ]
        then
            genkey_ask ${_prefix}
        else
            usage
        fi
    fi
fi
