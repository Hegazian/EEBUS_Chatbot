#----- Datagram Core Library------
set(datagram_library_target keo_datagram_core)


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
 ${CMAKE_CURRENT_LIST_DIR}/src/AbsoluteOrRecurringTime.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/AbsoluteOrRecurringTimeElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/AbsoluteOrRelativeTime.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BillType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementDeleteCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementDeleteCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementEntryData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementEntryDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementEntryListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementEntryListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/BindingManagementRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Cmd.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CmdClassifier.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CmdControl.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CmdData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CommodityData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CommodityDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CommodityListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CommodityListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/CommodityType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Currency.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Datagram.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DatagramParserException.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DayOfWeek.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DaysOfWeek.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DestinationList.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DestinationListImpl.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DestinationListImpl.h
 ${CMAKE_CURRENT_LIST_DIR}/src/DetailedDiscovery.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DetailedDiscoveryImpl.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DetailedDiscoveryPartial.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DetailedDiscoveryPartialImpl.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceAddress.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceAddressElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceClassificationManufacturerData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceClassificationManufacturerDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceClassificationUserData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceClassificationUserDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/DeviceType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/EnergyDirection.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/EnergyMode.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/EntityAddress.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/EntityAddressElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/EntityType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/FeatureAddress.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/FeatureAddressElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/FeatureSpecificUsage.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/FeatureType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Filter.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Function.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/FunctionProperty.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/FunctionPropertyElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Header.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoByteArray.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoDate.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoDateTime.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoDuration.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoJsonTransformation.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoJsonTransformation.h
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoScaledNumber.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoSpineDeviceAddress.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoStringUtil.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/KeoTime.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Month.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementAbortCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementAbortCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementAddNodeCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementAddNodeCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementDeviceDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementDeviceDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementDeviceDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementDeviceDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementDiscoverCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementDiscoverCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementEntityDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementEntityDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementEntityDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementEntityDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementFeatureDescriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementFeatureDescriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementFeatureDescriptionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementFeatureDescriptionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementFeatureSet.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementJoiningModeData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementJoiningModeDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementModifyNodeCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementModifyNodeCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementProcessStateData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementProcessStateDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementProcessStateState.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementRemoveNodeCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementRemoveNodeCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementReportCandidateData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementReportCandidateDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementScanNetworkCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementScanNetworkCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NetworkManagementStateChange.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingDeleteCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingDeleteCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementBindingRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDestinationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDestinationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDestinationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDestinationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryDeviceInformation.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryDeviceInformationElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryEntityInformation.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryEntityInformationElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryFeatureInformation.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementDetailedDiscoveryFeatureInformationElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSpecificationVersionList.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSpecificationVersionListElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionDeleteCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionDeleteCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementSubscriptionRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementUseCaseData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementUseCaseDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/NodeManagementUseCaseDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Occurrence.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Payload.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PluginLoader.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PossibleOperations.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PossibleOperationsElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PossibleOperationsRead.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PossibleOperationsWrite.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/PowerSource.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/RecurrenceInformation.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/RecurrenceInformationElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/RecurringInterval.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ResultData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/Role.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScaledNumber.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScaledNumberElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScaledNumberRange.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScaledNumberRangeElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScaledNumberSet.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScaledNumberSetElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/ScopeType.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SpecificationVersionDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SpecificationVersionListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SpecificationVersionListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SpineDatagramJson.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SpineResultErrors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementDeleteCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementDeleteCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementEntryData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementEntryDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementEntryListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementEntryListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementRequestCall.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/SubscriptionManagementRequestCallElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TimePeriod.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TimePeriodElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/TimestampInterval.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UnitOfMeasurement.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseDiscovery.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseDiscoveryImpl.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseInformationData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseInformationDataElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseInformationListData.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseInformationListDataSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseSupport.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseSupportElements.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/UseCaseSupportSelectors.cpp
 ${CMAKE_CURRENT_LIST_DIR}/src/json.cpp
)

set(PUBLIC_HEADERS
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Core_All.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/AbsoluteOrRecurringTime.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/AbsoluteOrRecurringTimeElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/AbsoluteOrRelativeTime.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/AbsoluteOrRelativeTimeStruct.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BillType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementDeleteCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementDeleteCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementEntryData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementEntryDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementEntryListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementEntryListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/BindingManagementRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Cmd.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CmdClassifier.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CmdControl.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CmdControlType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CmdData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CmdFilterType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CommodityData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CommodityDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CommodityListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CommodityListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/CommodityType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Currency.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Datagram.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DatagramParserException.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DayOfWeek.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DaysOfWeek.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DestinationList.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DetailedDiscovery.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DetailedDiscoveryPartial.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceAddress.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceAddressElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceClassificationManufacturerData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceClassificationManufacturerDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceClassificationUserData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceClassificationUserDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/DeviceType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/EnergyDirection.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/EnergyMode.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/EntityAddress.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/EntityAddressElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/EntityType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/FeatureAddress.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/FeatureAddressElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/FeatureSpecificUsage.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/FeatureType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Filter.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Function.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/FunctionProperty.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/FunctionPropertyElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Header.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoByteArray.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoDate.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoDateTime.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoDuration.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoJsonTransformable.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoScaledNumber.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoSpineDeviceAddress.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/KeoTime.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Month.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementAbortCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementAbortCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementAddNodeCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementAddNodeCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementDeviceDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementDeviceDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementDeviceDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementDeviceDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementDiscoverCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementDiscoverCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementEntityDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementEntityDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementEntityDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementEntityDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementFeatureDescriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementFeatureDescriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementFeatureDescriptionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementFeatureDescriptionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementFeatureSet.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementJoiningModeData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementJoiningModeDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementModifyNodeCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementModifyNodeCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementProcessStateData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementProcessStateDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementProcessStateState.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementRemoveNodeCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementRemoveNodeCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementReportCandidateData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementReportCandidateDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementScanNetworkCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementScanNetworkCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NetworkManagementStateChange.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingDeleteCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingDeleteCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementBindingRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDestinationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDestinationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDestinationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDestinationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryDeviceInformation.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryDeviceInformationElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryEntityInformation.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryEntityInformationElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryFeatureInformation.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementDetailedDiscoveryFeatureInformationElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSpecificationVersionList.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSpecificationVersionListElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionDeleteCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionDeleteCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementSubscriptionRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementUseCaseData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementUseCaseDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/NodeManagementUseCaseDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Occurrence.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Payload.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/PossibleOperations.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/PossibleOperationsElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/PossibleOperationsRead.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/PossibleOperationsWrite.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/PowerSource.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/RecurrenceInformation.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/RecurrenceInformationElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/RecurringInterval.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ResultData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/Role.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScaledNumber.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScaledNumberElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScaledNumberRange.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScaledNumberRangeElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScaledNumberSet.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScaledNumberSetElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/ScopeType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpecificationVersionDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpecificationVersionListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpecificationVersionListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpineDataType.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpineDatagram.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpineDatagramJson.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpineEnumClass.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SpineResultErrors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementDeleteCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementDeleteCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementEntryData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementEntryDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementEntryListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementEntryListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementRequestCall.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/SubscriptionManagementRequestCallElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/TimePeriod.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/TimePeriodElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/TimestampInterval.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UnitOfMeasurement.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseDiscovery.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseInformationData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseInformationDataElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseInformationListData.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseInformationListDataSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseSupport.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseSupportElements.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/UseCaseSupportSelectors.h
 ${CMAKE_CURRENT_LIST_DIR}/include/keo_datagram/core/xs_types.h
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


  INCLUDE_DIRECTORIES_PUBLIC
  ${INCLUDES_PUBLIC}
  ${CMAKE_CURRENT_LIST_DIR}/include

  INCLUDE_DIRECTORIES_INTERFACE

  HDR_INSTALL_DIR include/keo_datagram/core

  LINK_LIBRARIES

  ${CMAKE_DL_LIBS}


)