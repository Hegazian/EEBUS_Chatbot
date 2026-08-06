#----- Datagram LoadControl Library------
set(datagram_library_target keo_datagram_loadcontrol)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlCategory.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlEventAction.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlEventData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlEventDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlEventListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlEventListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlEventState.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitConstraintsListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitConstraintsListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlLimitType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlNodeData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlNodeDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlStateData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlStateDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlStateListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/LoadControlStateListDataSelectors.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControl_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlCategory.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlEventAction.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlEventData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlEventDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlEventListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlEventListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlEventState.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitConstraintsListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitConstraintsListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlLimitType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlNodeData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlNodeDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlStateData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlStateDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlStateListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/loadcontrol/LoadControlStateListDataSelectors.h
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

  HDR_INSTALL_DIR include/keo_datagram/loadcontrol

  LINK_LIBRARIES

  keo_datagram_core


)