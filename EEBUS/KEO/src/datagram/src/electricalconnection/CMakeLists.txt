#----- Datagram ElectricalConnection Library------
set(datagram_library_target keo_datagram_electricalconnection)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionAcMeasurementType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionMeasurandVariant.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionParameterDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionParameterDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionParameterDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionParameterDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionPermittedValueSetData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionPermittedValueSetDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionPermittedValueSetListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionPermittedValueSetListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionPhaseName.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionStateData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionStateDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionStateListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionStateListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ElectricalConnectionVoltageType.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnection_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionAcMeasurementType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionMeasurandVariant.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionPhaseName.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionStateData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionStateDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionStateListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionStateListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/electricalconnection/ElectricalConnectionVoltageType.h
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

  HDR_INSTALL_DIR include/keo_datagram/electricalconnection

  LINK_LIBRARIES

  keo_datagram_core


)