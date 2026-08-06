#----- Datagram Measurement Library------
set(datagram_library_target keo_datagram_measurement)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementConstraintsListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementConstraintsListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementThresholdRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementThresholdRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementThresholdRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementThresholdRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementValueSource.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementValueState.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementValueTendency.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/MeasurementValueType.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/Measurement_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementConstraintsListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementConstraintsListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementThresholdRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementThresholdRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementThresholdRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementThresholdRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementValueSource.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementValueState.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementValueTendency.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/measurement/MeasurementValueType.h
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

  HDR_INSTALL_DIR include/keo_datagram/measurement

  LINK_LIBRARIES

  keo_datagram_core


)