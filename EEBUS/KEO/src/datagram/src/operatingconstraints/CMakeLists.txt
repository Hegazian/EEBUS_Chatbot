#----- Datagram OperatingConstraints Library------
set(datagram_library_target keo_datagram_operatingconstraints)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsDurationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsDurationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsDurationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsDurationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsInterruptData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsInterruptDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsInterruptListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsInterruptListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerLevelData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerLevelDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerLevelListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerLevelListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerRangeData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerRangeDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerRangeListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsPowerRangeListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsResumeImplicationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsResumeImplicationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsResumeImplicationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/OperatingConstraintsResumeImplicationListDataSelectors.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraints_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsDurationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsDurationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsDurationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsDurationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsInterruptData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsInterruptDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsInterruptListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsInterruptListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerLevelListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsPowerRangeListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationListDataSelectors.h
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

  HDR_INSTALL_DIR include/keo_datagram/operatingconstraints

  LINK_LIBRARIES

  keo_datagram_core


)