# Installation {#installation}

Discusses how to download, compile and install the [keo spine](@ref mainpage) for your platform.

### Required packages on UNIX
To compile the source distribution, you need at least the following to build applications:
In order to generate a Makefile for your platform, you need cmake version 2.8.12 or later.
 
### Compiling from source on UNIX
Compilation is now done by performing the following steps:

2. Create a project directory 
   ~~~~~~~~~~~~~~~~~~{.sh}
   mkdir keo_spine
   ~~~~~~~~~~~~~~~~~~
2. Unpack the archives. 
   ~~~~~~~~~~~~~~~~~~{.sh}
   tar xzf keo_spine-<VERSION>-dev.tar.gz -C keo_spine  # unpack the archive
   tar xzf keo_spine-<VERSION>-example.tar.gz -C keo_spine  # unpack the archive
   ~~~~~~~~~~~~~~~~~~
3. Create a build directory and go into. (for instance inside the source tree) 
   ~~~~~~~~~~~~~~~~~~{.sh}
   cd keo_spine/examples
   mkdir build
   cd build
   ~~~~~~~~~~~~~~~~~~
4. Run cmake with the makefile generator 
   ~~~~~~~~~~~~~~~~~~{.sh}
   cmake -G "Unix Makefiles" -DKEO_SPINE_ROOT=/home/.../keo_spine ..
   ~~~~~~~~~~~~~~~~~~
4. Compile the program by running make:
   ~~~~~~~~~~~~~~~~~~{.sh}
   make
   ~~~~~~~~~~~~~~~~~~

### Installing the binaries on UNIX
Installation is now done by performing the following step(s):
1. Install the library.
   ~~~~~~~~~~~~~~~~~~{.sh}
   make install
   ~~~~~~~~~~~~~~~~~~

@note Feel free to edit this description at doc/installation.md
   
