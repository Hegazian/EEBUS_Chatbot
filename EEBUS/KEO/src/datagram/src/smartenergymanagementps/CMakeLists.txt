#----- Datagram SmartEnergyManagementPs Library------
set(datagram_library_target keo_datagram_smartenergymanagementps)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceAlternativesRelationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceAlternativesRelationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceAlternativesRelationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceAlternativesRelationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceNodeScheduleInformationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceNodeScheduleInformationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequencePriceCalculationRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequencePriceCalculationRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequencePriceData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequencePriceDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequencePriceListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequencePriceListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleConfigurationRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleConfigurationRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleConstraintsListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleConstraintsListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScheduleListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceSchedulePreferenceData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceSchedulePreferenceDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceSchedulePreferenceListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceSchedulePreferenceListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceScope.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceState.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceStateData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceStateDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceStateListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSequenceStateListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleConstraintsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleConstraintsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleConstraintsListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleConstraintsListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotScheduleListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotValueData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotValueDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotValueListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotValueListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerTimeSlotValueType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsAlternatives.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsAlternativesElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsAlternativesRelation.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsAlternativesRelationElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsConfigurationRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsConfigurationRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsLibraryPlugin.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPowerSequence.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPowerSequenceElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPowerTimeSlot.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPowerTimeSlotElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPowerTimeSlotValueList.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPowerTimeSlotValueListElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPriceCalculationRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPriceCalculationRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPriceData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPriceDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SmartEnergyManagementPsPriceDataSelectors.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPs_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequencePriceCalculationRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequencePriceCalculationRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequencePriceData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequencePriceDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequencePriceListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequencePriceListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleConfigurationRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleConfigurationRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScheduleListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceScope.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceState.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceStateData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceStateDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceStateListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerSequenceStateListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleConstraintsListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotValueData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotValueDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotValueListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotValueListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/PowerTimeSlotValueType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternatives.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesRelation.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesRelationElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsConfigurationRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsConfigurationRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerSequence.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerSequenceElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlot.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlotElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlotValueList.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerTimeSlotValueListElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceCalculationRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceCalculationRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPriceDataSelectors.h
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

  HDR_INSTALL_DIR include/keo_datagram/smartenergymanagementps

  LINK_LIBRARIES

  keo_datagram_core

  keo_datagram_measurement
  keo_datagram_operatingconstraints

)