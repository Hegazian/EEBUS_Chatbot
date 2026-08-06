
Copyright KEO GmbH 2018 - All rights reserved!

This software is protected by the inclusion of the above copyright notice.
This software may not be provided or otherwise made available to, or used
by, any other person. No title to or ownership of the software is hereby
transferred. The information contained in this document is considered the
confidential and proprietary information of KEO GmbH
and may not be disclosed or discussed with anyone who is not employed by
KEO GmbH, unless the individual or company
- has an express need to know such information, and
- disclosure of information is subject to the terms of a duly
executed "Confidentiality and Non-Disclosure Agreement" between
KEO GmbH and the individual or company.


Package content
---------------
KEO SPINE Implementation Source Code


Prerequisites
-------------

The build has been tested with Ubuntu 16.04.

Required packages:

ii  build-essential                             11.6ubuntu6                                         amd64        Informational list of build-essential packages
ii  openssl                                     1.0.1f-1ubuntu2.19                                  amd64        Secure Sockets Layer toolkit - cryptographic utility
ii  libavahi-client-dev                         0.6.32~rc+dfsg-1ubuntu2                             amd64        Development files for the Avahi client library
ii  libavahi-common-dev                         0.6.32~rc+dfsg-1ubuntu2                             amd64        Development files for the Avahi common library
ii  libavahi-core-dev                           0.6.32~rc+dfsg-1ubuntu2                             amd64        Development files for Avahi's embeddable mDNS/DNS-SD library

cmake 3.9 or above


How to build
------------
- unpack the tar ball
- in order to find the KEO SPINE datagram library the installation path needs to be set on the command line.
  when the datagram library has been built from source this is usually the CMAKE_INSTALL_PREFIX that has been used there.
- run "cmake -DCMAKE_INSTALL_PREFIX=./install -DKEO_SPINE_DATAGRAM_ROOT=<path_to_keo_spine_datagram_installation> . && make install"
