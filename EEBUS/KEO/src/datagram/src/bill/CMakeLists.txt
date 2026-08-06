#----- Datagram Bill Library------
set(datagram_library_target keo_datagram_bill)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/BillConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillConstraintsListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillConstraintsListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillCost.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillCostElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillCostType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillPosition.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillPositionElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillPositionType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillValue.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillValueElements.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/Bill_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillConstraintsListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillConstraintsListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillCost.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillCostElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillCostType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillPosition.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillPositionElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillPositionType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillValue.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/bill/BillValueElements.h
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

  HDR_INSTALL_DIR include/keo_datagram/bill

  LINK_LIBRARIES

  keo_datagram_core


)