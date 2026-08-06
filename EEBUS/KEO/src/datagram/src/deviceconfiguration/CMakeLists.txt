#----- Datagram DeviceConfiguration Library------
set(datagram_library_target keo_datagram_deviceconfiguration)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyName.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueConstraintsListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueConstraintsListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueValue.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationKeyValueValueElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceConfigurationLibraryPlugin.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfiguration_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyName.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValue.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueValueElements.h
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

  HDR_INSTALL_DIR include/keo_datagram/deviceconfiguration

  LINK_LIBRARIES

  keo_datagram_core


)