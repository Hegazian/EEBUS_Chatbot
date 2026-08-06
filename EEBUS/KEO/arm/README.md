# KEO Spine Source Development Package

## Introduction

The KEO SPINE development package helps with the creation of SPINE applications.
In order to make use of it, the SHIP specifiation as well as the SPINE specification
need to be read and understood.

## Features

* SHIP Stack implementation
* SPINE datagram libary
* SPINE application library

## Package Content


    |-- bin                    Precompiled examples with configuration files
    |-- cmakemodules           CMake modules to build the examples
    |-- examples
    |   `-- spine              Simple client/server example
    |       |-- client
    |       `-- server
    |-- include                Development headers
    |   |-- keo_datagram       SPINE datagram library
    |   |-- keo_example        Example headers
    |   |-- keo_ship           SHIP headers
    |   |-- keo_spine          SPINE application library headers
    |   `-- keo_util           Utility headers
    `-- lib                    Libraries

# Getting Started

## Running the example
Open a terminal in the 'bin' directory and launch the 'runserver.sh' script.
Then open another terminal in the 'bin' directory and launch the 'runclient.sh' script.

# Building the example
## Prerequisites
Building the examples has been tested on Ubuntu 16.04.
Required packages are (dependencies not listed):
 * build-essential
 * cmake
 * libavahi-client-dev
 * libavahi-common-dev
 * libavahi-core-dev
 * libssl-dev

## Building
In the 'examples' directory launch the script 'build_cmake.sh'.
The binaries will be generated in the subdirectory 'build/bin'.
The easiest way to use them is to replace the precompiled examples in the root 'bin' directory.
