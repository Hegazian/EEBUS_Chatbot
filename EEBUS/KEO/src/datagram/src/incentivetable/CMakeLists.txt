#----- Datagram IncentiveTable Library------
set(datagram_library_target keo_datagram_incentivetable)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTable.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableConstraints.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableConstraintsDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableConstraintsElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescription.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescriptionDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescriptionElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescriptionTier.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableDescriptionTierElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableIncentiveSlot.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableIncentiveSlotElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableTier.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveTableTierElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/IncentiveValueType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffBoundaryRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffBoundaryRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffBoundaryRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffBoundaryRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffOverallConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffOverallConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffTierRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffTierRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffTierRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TariffTierRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierBoundaryType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierIncentiveRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierIncentiveRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierIncentiveRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierIncentiveRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TierType.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTable_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTable.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableConstraints.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableConstraintsDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableConstraintsElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescription.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescriptionDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescriptionElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescriptionTier.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableDescriptionTierElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableIncentiveSlot.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableIncentiveSlotElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableTier.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveTableTierElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/IncentiveValueType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffBoundaryRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffBoundaryRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffBoundaryRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffBoundaryRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffOverallConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffOverallConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffTierRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffTierRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffTierRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TariffTierRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierBoundaryType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierIncentiveRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierIncentiveRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierIncentiveRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierIncentiveRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/incentivetable/TierType.h
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

  HDR_INSTALL_DIR include/keo_datagram/incentivetable

  LINK_LIBRARIES

  keo_datagram_core

  keo_datagram_timetable

)