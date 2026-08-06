#----- Datagram DeviceDiagnosis Library------
set(datagram_library_target keo_datagram_devicediagnosis)


# Configuration
set(config_install_dir  "lib/cmake")
set(generated_dir       "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(version_config      "${generated_dir}/${datagram_library_target}ConfigVersion.cmake")
set(project_config      "${generated_dir}/${datagram_library_target}Config.cmake")
set(targets_export_name "${datagram_library_target}Targets")
set(namespace           "keo_datagram::")

write_basic_package_version_file(
  "${version_config}"
  VERSION ${BS_VERSION_MAJOR}.${BS_VERSION_MINOR}.${BS_VERSION_REVISION}
  COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/Config.cmake.in"
  "${project_config}"
  INSTALL_DESTINATION "${config_install_dir}/${datagram_library_target}"
)

set(CPACK_COMPONENT_DEV_GROUP "dev")

# Config
install(
  FILES       "${project_config}" "${version_config}"
  DESTINATION "${config_install_dir}/${datagram_library_target}"
  COMPONENT   ${CPACK_COMPONENT_DEV_GROUP}
)

# Config
install(
  EXPORT      "${targets_export_name}"
  NAMESPACE   "${namespace}"
  DESTINATION "${config_install_dir}/${datagram_library_target}"
  COMPONENT   ${CPACK_COMPONENT_DEV_GROUP}
)

set(TARGET_SOURCES
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisHeartbeatData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisHeartbeatDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisOperatingState.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisServiceData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisServiceDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisStateData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceDiagnosisStateDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSupplyCondition.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosis_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisOperatingState.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisServiceData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisServiceDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisStateData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/DeviceDiagnosisStateDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/devicediagnosis/PowerSupplyCondition.h
)

set_source_files_properties(
  ${TARGET_SOURCES}
  ${PUBLIC_HEADERS}
  PROPERTIES GENERATED TRUE
)

keo_library(
  LIBRARY_NAME ${datagram_library_target}
  LIBRARY_TYPE SHARED
  EXPORT_NAME  ${targets_export_name}

  LIST_SRC
  ${TARGET_SOURCES}

  LIST_HDR_PRIVATE
  ${PRIVATE_HEADERS}

  LIST_HDR_PUBLIC
  ${PUBLIC_HEADERS}

  LIST_HDR_INTERFACE

  INCLUDE_DIRECTORIES_PRIVATE
  ${INCLUDES_PRIVATE}

  ${INCLUDES_DATAGRAM_CORE_LIBRARY}


  INCLUDE_DIRECTORIES_PUBLIC
  ${INCLUDES_PUBLIC}
  ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR include/keo_datagram/devicediagnosis

  LINK_LIBRARIES

  keo_datagram_core


)