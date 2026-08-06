#----- Datagram HVAC Library------
set(datagram_library_target keo_datagram_hvac)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/HVACLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOperationModeDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOperationModeDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOperationModeDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOperationModeDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOperationModeType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunStatus.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacOverrunType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionOperationModeRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionOperationModeRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionOperationModeRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionOperationModeRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionPowerSequenceRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionPowerSequenceRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionPowerSequenceRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionPowerSequenceRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionSetpointRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionSetpointRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionSetpointRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionSetpointRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/HvacSystemFunctionType.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HVAC_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOperationModeDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOperationModeDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOperationModeDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOperationModeDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOperationModeType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunStatus.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacOverrunType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionOperationModeRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionOperationModeRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionSetpointRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionSetpointRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionSetpointRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionSetpointRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/hvac/HvacSystemFunctionType.h
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

  HDR_INSTALL_DIR include/keo_datagram/hvac

  LINK_LIBRARIES

  keo_datagram_core


)