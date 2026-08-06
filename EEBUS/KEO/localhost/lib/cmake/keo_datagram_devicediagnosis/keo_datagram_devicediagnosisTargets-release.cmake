#----------------------------------------------------------------
# Generated CMake target import file for configuration "release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "keo_datagram::keo_datagram_devicediagnosis" for configuration "release"
set_property(TARGET keo_datagram::keo_datagram_devicediagnosis APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(keo_datagram::keo_datagram_devicediagnosis PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkeo_datagram_devicediagnosis.so.12.0.2"
  IMPORTED_SONAME_RELEASE "libkeo_datagram_devicediagnosis.so.12"
  )

list(APPEND _IMPORT_CHECK_TARGETS keo_datagram::keo_datagram_devicediagnosis )
list(APPEND _IMPORT_CHECK_FILES_FOR_keo_datagram::keo_datagram_devicediagnosis "${_IMPORT_PREFIX}/lib/libkeo_datagram_devicediagnosis.so.12.0.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
