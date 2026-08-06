#----------------------------------------------------------------
# Generated CMake target import file for configuration "release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "keo_spine::keo_util" for configuration "release"
set_property(TARGET keo_spine::keo_util APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_util PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_util.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_util.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_util )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_util "${_IMPORT_PREFIX}/lib/libkeo_util.so.12.0.3" )

# Import target "keo_spine::keo_ship_discovery" for configuration "release"
set_property(TARGET keo_spine::keo_ship_discovery APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_ship_discovery PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "keo_spine::keo_util"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_ship_discovery.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_ship_discovery.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_ship_discovery )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_ship_discovery "${_IMPORT_PREFIX}/lib/libkeo_ship_discovery.so.12.0.3" )

# Import target "keo_spine::keo_ship" for configuration "release"
set_property(TARGET keo_spine::keo_ship APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_ship PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_ship.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_ship.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_ship )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_ship "${_IMPORT_PREFIX}/lib/libkeo_ship.so.12.0.3" )

# Import target "keo_spine::keo_framework" for configuration "release"
set_property(TARGET keo_spine::keo_framework APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_framework PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_framework.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_framework.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_framework )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_framework "${_IMPORT_PREFIX}/lib/libkeo_framework.so.12.0.3" )

# Import target "keo_spine::keo_default_ship_transport" for configuration "release"
set_property(TARGET keo_spine::keo_default_ship_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_default_ship_transport PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_default_ship_transport.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_default_ship_transport.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_default_ship_transport )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_default_ship_transport "${_IMPORT_PREFIX}/lib/libkeo_default_ship_transport.so.12.0.3" )

# Import target "keo_spine::keo_simple_ship_transport" for configuration "release"
set_property(TARGET keo_spine::keo_simple_ship_transport APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_simple_ship_transport PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_simple_ship_transport.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_simple_ship_transport.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_simple_ship_transport )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_simple_ship_transport "${_IMPORT_PREFIX}/lib/libkeo_simple_ship_transport.so.12.0.3" )

# Import target "keo_spine::keo_json_security_handler" for configuration "release"
set_property(TARGET keo_spine::keo_json_security_handler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_spine::keo_json_security_handler PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_json_security_handler.so.12.0.3"
  IMPORTED_SONAME_RELEASE "libkeo_json_security_handler.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_spine::keo_json_security_handler )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_spine::keo_json_security_handler "${_IMPORT_PREFIX}/lib/libkeo_json_security_handler.so.12.0.3" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
