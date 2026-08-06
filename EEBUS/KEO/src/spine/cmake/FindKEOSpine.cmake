# - Try to find KEO SPINE SDK include dir and library
# Usage of this module as follows:
#
#  KEO_SPINE_INCLUDE_DIR         - where to find the headers.
#  KEO_SPINE_LIBRARIES           - KEO_SPINE libraries using the deprecated device library.
#  KEO_SPINE_FRAMEWORK_LIBRARIES - KEO_SPINE libraries using the framework library.
#  KEO_SPINE_FOUND               - True if KEO_SPINE found.
#
# Variables used by this module which you may want to set.
#
#                                       The preferred installation prefix for searching for
#   KEO_SPINE_ROOT                      KEO_SPINE.  Set this if the module has problems finding
#                                       the proper KEO_SPINE installation.
#
#
#   KEO_SPINE_INCLUDEDIR                Set this to the include directory of KEO_SPINE, if the
#                                       module has problems finding the proper KEO_SPINE installation
#
#   KEO_SPINE_LIBRARYDIR                Set this to the lib directory of KEO_SPINE, if the
#                                       module has problems finding the proper KEO_SPINE installation
#

#=============================================================================
# Copyright 2016 KEO GmbH

# If KEO_SPINE_ROOT was defined in the environment, use it.
if (NOT KEO_SPINE_ROOT AND NOT $ENV{KEO_SPINE_ROOT} STREQUAL "")
  set(KEO_SPINE_ROOT $ENV{KEO_SPINE_ROOT})
endif()

# If KEO_SPINE_INCLUDEDIR was defined in the environment, use it.
if( NOT KEO_SPINE_INCLUDEDIR AND NOT $ENV{KEO_SPINE_INCLUDEDIR} STREQUAL "" )
  set(KEO_SPINE_INCLUDEDIR $ENV{KEO_SPINE_INCLUDEDIR})
endif()

# If KEO_SPINE_INCLUDEDIR was defined in the environment, use it.
if( NOT KEO_SPINE_LIBRARYDIR AND NOT $ENV{KEO_SPINE_LIBRARYDIR} STREQUAL "" )
  set(KEO_SPINE_LIBRARYDIR $ENV{KEO_SPINE_LIBRARYDIR})
endif()

set(keo_spine_INCLUDE_SEARCH_DIR)
set(keo_spine_LIBRARY_SEARCH_DIR)

if (KEO_SPINE_ROOT)
  list(APPEND keo_spine_INCLUDE_SEARCH_DIR "${KEO_SPINE_ROOT}/include")
  list(APPEND keo_spine_LIBRARY_SEARCH_DIR "${KEO_SPINE_ROOT}/lib")
endif()

if (KEO_SPINE_INCLUDEDIR)
  list(APPEND keo_spine_INCLUDE_SEARCH_DIR "${KEO_SPINE_INCLUDEDIR}")
endif()

if (KEO_SPINE_LIBRARYDIR)
  list(APPEND keo_spine_LIBRARY_SEARCH_DIR "${KEO_SPINE_LIBRARYDIR}")
endif()

# Look for the header file.
find_path(keo_spine_INCLUDE_DIR
  NAMES keo_spineVersion.h
  HINTS ${keo_spine_INCLUDE_SEARCH_DIR}
  )

# Look for the libraries.
find_library(keo_util_LIBRARY
  NAMES keo_util keo_utild
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_datagram_core_LIBRARY
  NAMES keo_datagram_core keo_datagram_cored
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_datagram_measurement_LIBRARY
  NAMES keo_datagram_measurement keo_datagram_measurementd
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_ship_LIBRARY
  NAMES keo_ship keo_shipd
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_ship_discovery_LIBRARY
  NAMES keo_ship_discovery keo_ship_discoveryd
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_device_LIBRARY
  NAMES keo_device keo_deviced
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

# deprecated module is not required
if (${keo_device_LIBRARY} STREQUAL "keo_device_LIBRARY-NOTFOUND")
  unset(keo_device_LIBRARY CACHE)
endif()

find_library(keo_framework_LIBRARY
  NAMES keo_framework keo_frameworkd
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_json_security_handler_LIBRARY
  NAMES keo_json_security_handler keo_json_security_handlerd
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

find_library(keo_default_ship_transport_LIBRARY
  NAMES keo_default_ship_transport keo_default_ship_transportd
  HINTS ${keo_spine_LIBRARY_SEARCH_DIR}
  )

# handle the QUIETLY and REQUIRED arguments and set KEO_SPINE_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(KEO_SPINE
  REQUIRED_VARS keo_spine_INCLUDE_DIR
  REQUIRED_VARS keo_util_LIBRARY
  REQUIRED_VARS keo_datagram_core_LIBRARY
  REQUIRED_VARS keo_datagram_measurement_LIBRARY
  REQUIRED_VARS keo_ship_LIBRARY
  REQUIRED_VARS keo_ship_discovery_LIBRARY
  REQUIRED_VARS keo_framework_LIBRARY
  REQUIRED_VARS keo_json_security_handler_LIBRARY
  REQUIRED_VARS keo_default_ship_transport_LIBRARY
  )

# Copy the results to the output variables.
if(KEO_SPINE_FOUND)

  set(KEO_UTIL_LIBRARY                  ${keo_util_LIBRARY})
  set(KEO_DATAGRAM_CORE_LIBRARY         ${keo_datagram_core_LIBRARY})
  set(KEO_DATAGRAM_MEASUREMENT_LIBRARY  ${keo_datagram_measurement_LIBRARY})
  set(KEO_SHIP_LIBRARY                  ${keo_ship_LIBRARY})
  set(KEO_SHIP_DISCOVERY_LIBRARY        ${keo_ship_discovery_LIBRARY})
  set(KEO_FRAMEWORK_LIBRARY             ${keo_framework_LIBRARY})
  set(KEO_JSSECHANDLER_LIBRARY          ${keo_json_security_handler_LIBRARY})
  set(KEO_DEFSHIPTRANS_LIBRARY          ${keo_default_ship_transport_LIBRARY})

  set(KEO_SPINE_INCLUDE_DIR ${keo_spine_INCLUDE_DIR})

  set(KEO_SPINE_LIBRARIES
    ${KEO_DATAGRAM_CORE_LIBRARY}
    ${KEO_DATAGRAM_MEASUREMENT_LIBRARY}
    ${KEO_SHIP_LIBRARY}
    ${KEO_SHIP_DISCOVERY_LIBRARY}
    ${KEO_UTIL_LIBRARY}
    ${KEO_FRAMEWORK_LIBRARY}
    ${KEO_JSSECHANDLER_LIBRARY}
    ${KEO_DEFSHIPTRANS_LIBRARY}
    )

endif(KEO_SPINE_FOUND)

mark_as_advanced(keo_spine_INCLUDEDIR keo_spine_LIBRARYDIR)
