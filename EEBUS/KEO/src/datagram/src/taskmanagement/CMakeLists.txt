#----- Datagram TaskManagement Library------
set(datagram_library_target keo_datagram_taskmanagement)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementDirectControlRelated.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementDirectControlRelatedElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementHvacRelated.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementHvacRelatedElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobSource.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementJobState.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementLoadControlReleated.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementLoadControlReleatedElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementOverviewData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementOverviewDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementPowerSequencesRelated.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementPowerSequencesRelatedElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementSmartEnergyManagementPsRelated.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TaskManagementSmartEnergyManagementPsRelatedElements.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagement_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementDirectControlRelated.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementDirectControlRelatedElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementHvacRelated.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementHvacRelatedElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobSource.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementJobState.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementLoadControlReleated.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementLoadControlReleatedElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementOverviewData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementOverviewDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementPowerSequencesRelated.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementPowerSequencesRelatedElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementSmartEnergyManagementPsRelated.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/taskmanagement/TaskManagementSmartEnergyManagementPsRelatedElements.h
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

  HDR_INSTALL_DIR include/keo_datagram/taskmanagement

  LINK_LIBRARIES

  keo_datagram_core


)