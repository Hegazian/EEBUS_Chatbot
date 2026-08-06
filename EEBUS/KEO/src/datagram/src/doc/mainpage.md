

# API Reference {#mainpage}

## Introduction
KEO provides a collection of libraries, headers and example applications to ease development of SPINE applications.

This module contains the SPINE datagram library, the implementation of the SPINE data model.

The SPINE data model defines a modular approach to combine different SPINE data model elements.
Additionally, the SPINE protocol specification defines mandatory, recommended and optional elements.
This results in numerous possible combinations and opportunities for future extensions.
However, this flexibility is achieved at the expense of an easy and quick understanding of SPINE fundamentals, especially for beginners.

To create and implement SPINE applications the KEO SPINE API provides, besides other things,
the SPINE data model (see [SpineDatagram](@ref keo_datagram)).

## Usage
The KEO Spine datagram library is split into a core and several class libraries. Therewith it is possible to install the core library
and only those class libraries which are actually used.

The core library contains all 'base' functionality that every SPINE application needs, like Network-, Node-, Binding- and SubscriptionManagement and most of the 
enumeration data types. The class libraries are specific to one ore more SPINE class definition like Measurement, 
Sensing or SmartEnergyManagement. For further information about the class concept please refer to the EEBus SPINE Technical Specification.

While the class libraries are linked to the core library to access the basic data types, the core library tries to load the class libraries
during startup to gather informormation about the supported classes. The core library searches the class libraries only inside the directory 
of the core library itself.

For each library a CMake-Package configuration is provided. Use this package configuration to find and load the settings of the datagram libraries.

Inside your CMakeLists.txt (KEO_SPINE_DATAGRAM_ROOT points to the installation path of the KEO SPINE datagram libraries):

    # find keo spine datagram measurement library
    find_package(keo_datagram_measurement
      CONFIG
      REQUIRED
      PATHS ${KEO_SPINE_DATAGRAM_ROOT}
      )
 
 Afterwards link your application to keo_datagram::keo_datagram_measurement:
 
     add_executable (MyApp module1.cpp module2.cpp)
 
     target_link_libraries (MyApp LINK_PUBLIC keo_datagram::keo_datagram_measurement)
