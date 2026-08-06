/*
 *     Copyright KEO GmbH  - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright
 * notice.
 *     This software may not be provided or otherwise made available to, or used
 *     by, any other person. No title to or ownership of the software is hereby
 *     transferred. The information contained in this document is considered the
 *     @b confidential and @b proprietary information of KEO GmbH
 *     and may not be disclosed or discussed with anyone who is not employed by
 *     KEO GmbH, unless the individual or company
 *     - has an express need to know such information, and
 *     - disclosure of information is subject to the terms of a duly
 *     executed "Confidentiality and Non-Disclosure Agreement" between
 *     KEO GmbH and the individual or company.
 */

#include <keo_datagram/core/CmdData.h>

namespace keo_datagram {

std::map<std::string, CmdData::Type> CmdData::STRING_TO_TYPE = {
    {"actuatorLevelData", CmdData::Type::ACTUATOR_LEVEL_DATA_TYPE},
    {"actuatorLevelDescriptionData",
     CmdData::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_TYPE},
    {"actuatorSwitchData", CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE},
    {"actuatorSwitchDescriptionData",
     CmdData::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_TYPE},
    {"alarmListData", CmdData::Type::ALARM_LIST_DATA_TYPE},
    {"billConstraintsListData", CmdData::Type::BILL_CONSTRAINTS_LIST_DATA_TYPE},
    {"billDescriptionListData", CmdData::Type::BILL_DESCRIPTION_LIST_DATA_TYPE},
    {"billListData", CmdData::Type::BILL_LIST_DATA_TYPE},
    {"bindingManagementDeleteCall",
     CmdData::Type::BINDING_MANAGEMENT_DELETE_CALL_TYPE},
    {"bindingManagementEntryListData",
     CmdData::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE},
    {"bindingManagementRequestCall",
     CmdData::Type::BINDING_MANAGEMENT_REQUEST_CALL_TYPE},
    {"commodityListData", CmdData::Type::COMMODITY_LIST_DATA_TYPE},
    {"dataTunnelingCall", CmdData::Type::DATA_TUNNELING_CALL_TYPE},
    {"deviceClassificationManufacturerData",
     CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE},
    {"deviceClassificationUserData",
     CmdData::Type::DEVICE_CLASSIFICATION_USER_DATA_TYPE},
    {"deviceConfigurationKeyValueConstraintsListData",
     CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE},
    {"deviceConfigurationKeyValueDescriptionListData",
     CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE},
    {"deviceConfigurationKeyValueListData",
     CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_TYPE},
    {"deviceDiagnosisHeartbeatData",
     CmdData::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE},
    {"deviceDiagnosisServiceData",
     CmdData::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE},
    {"deviceDiagnosisStateData",
     CmdData::Type::DEVICE_DIAGNOSIS_STATE_DATA_TYPE},
    {"directControlActivityListData",
     CmdData::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE},
    {"directControlDescriptionData",
     CmdData::Type::DIRECT_CONTROL_DESCRIPTION_DATA_TYPE},
    {"electricalConnectionDescriptionListData",
     CmdData::Type::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE},
    {"electricalConnectionParameterDescriptionListData",
     CmdData::Type::ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE},
    {"electricalConnectionPermittedValueSetListData",
     CmdData::Type::ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE},
    {"electricalConnectionStateListData",
     CmdData::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE},
    {"hvacOperationModeDescriptionListData",
     CmdData::Type::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE},
    {"hvacOverrunDescriptionListData",
     CmdData::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE},
    {"hvacOverrunListData", CmdData::Type::HVAC_OVERRUN_LIST_DATA_TYPE},
    {"hvacSystemFunctionDescriptionListData",
     CmdData::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE},
    {"hvacSystemFunctionListData",
     CmdData::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE},
    {"hvacSystemFunctionOperationModeRelationListData",
     CmdData::Type::
         HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE},
    {"hvacSystemFunctionPowerSequenceRelationListData",
     CmdData::Type::
         HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE},
    {"hvacSystemFunctionSetpointRelationListData",
     CmdData::Type::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE},
    {"identificationListData", CmdData::Type::IDENTIFICATION_LIST_DATA_TYPE},
    {"incentiveDescriptionListData",
     CmdData::Type::INCENTIVE_DESCRIPTION_LIST_DATA_TYPE},
    {"incentiveListData", CmdData::Type::INCENTIVE_LIST_DATA_TYPE},
    {"incentiveTableConstraintsData",
     CmdData::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE},
    {"incentiveTableData", CmdData::Type::INCENTIVE_TABLE_DATA_TYPE},
    {"incentiveTableDescriptionData",
     CmdData::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_TYPE},
    {"loadControlEventListData",
     CmdData::Type::LOAD_CONTROL_EVENT_LIST_DATA_TYPE},
    {"loadControlLimitConstraintsListData",
     CmdData::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE},
    {"loadControlLimitDescriptionListData",
     CmdData::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE},
    {"loadControlLimitListData",
     CmdData::Type::LOAD_CONTROL_LIMIT_LIST_DATA_TYPE},
    {"loadControlNodeData", CmdData::Type::LOAD_CONTROL_NODE_DATA_TYPE},
    {"loadControlStateListData",
     CmdData::Type::LOAD_CONTROL_STATE_LIST_DATA_TYPE},
    {"measurementConstraintsListData",
     CmdData::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE},
    {"measurementDescriptionListData",
     CmdData::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE},
    {"measurementListData", CmdData::Type::MEASUREMENT_LIST_DATA_TYPE},
    {"measurementThresholdRelationListData",
     CmdData::Type::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE},
    {"messagingListData", CmdData::Type::MESSAGING_LIST_DATA_TYPE},
    {"networkManagementAbortCall",
     CmdData::Type::NETWORK_MANAGEMENT_ABORT_CALL_TYPE},
    {"networkManagementAddNodeCall",
     CmdData::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE},
    {"networkManagementDeviceDescriptionListData",
     CmdData::Type::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE},
    {"networkManagementDiscoverCall",
     CmdData::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE},
    {"networkManagementEntityDescriptionListData",
     CmdData::Type::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE},
    {"networkManagementFeatureDescriptionListData",
     CmdData::Type::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE},
    {"networkManagementJoiningModeData",
     CmdData::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE},
    {"networkManagementModifyNodeCall",
     CmdData::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE},
    {"networkManagementProcessStateData",
     CmdData::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE},
    {"networkManagementRemoveNodeCall",
     CmdData::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE},
    {"networkManagementReportCandidateData",
     CmdData::Type::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE},
    {"networkManagementScanNetworkCall",
     CmdData::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE},
    {"nodeManagementBindingData",
     CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE},
    {"nodeManagementBindingDeleteCall",
     CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE},
    {"nodeManagementBindingRequestCall",
     CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE},
    {"nodeManagementDestinationListData",
     CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE},
    {"nodeManagementDetailedDiscoveryData",
     CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE},
    {"nodeManagementSubscriptionData",
     CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE},
    {"nodeManagementSubscriptionDeleteCall",
     CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE},
    {"nodeManagementSubscriptionRequestCall",
     CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE},
    {"nodeManagementUseCaseData",
     CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE},
    {"operatingConstraintsDurationListData",
     CmdData::Type::OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE},
    {"operatingConstraintsInterruptListData",
     CmdData::Type::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE},
    {"operatingConstraintsPowerDescriptionListData",
     CmdData::Type::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE},
    {"operatingConstraintsPowerLevelListData",
     CmdData::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE},
    {"operatingConstraintsPowerRangeListData",
     CmdData::Type::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE},
    {"operatingConstraintsResumeImplicationListData",
     CmdData::Type::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE},
    {"powerSequenceAlternativesRelationListData",
     CmdData::Type::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE},
    {"powerSequenceDescriptionListData",
     CmdData::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE},
    {"powerSequenceNodeScheduleInformationData",
     CmdData::Type::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE},
    {"powerSequencePriceCalculationRequestCall",
     CmdData::Type::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE},
    {"powerSequencePriceListData",
     CmdData::Type::POWER_SEQUENCE_PRICE_LIST_DATA_TYPE},
    {"powerSequenceScheduleConfigurationRequestCall",
     CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE},
    {"powerSequenceScheduleConstraintsListData",
     CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE},
    {"powerSequenceScheduleListData",
     CmdData::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE},
    {"powerSequenceSchedulePreferenceListData",
     CmdData::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE},
    {"powerSequenceStateListData",
     CmdData::Type::POWER_SEQUENCE_STATE_LIST_DATA_TYPE},
    {"powerTimeSlotScheduleConstraintsListData",
     CmdData::Type::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE},
    {"powerTimeSlotScheduleListData",
     CmdData::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE},
    {"powerTimeSlotValueListData",
     CmdData::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE},
    {"resultData", CmdData::Type::RESULT_DATA_TYPE},
    {"sensingDescriptionData", CmdData::Type::SENSING_DESCRIPTION_DATA_TYPE},
    {"sensingListData", CmdData::Type::SENSING_LIST_DATA_TYPE},
    {"setpointConstraintsListData",
     CmdData::Type::SETPOINT_CONSTRAINTS_LIST_DATA_TYPE},
    {"setpointDescriptionListData",
     CmdData::Type::SETPOINT_DESCRIPTION_LIST_DATA_TYPE},
    {"setpointListData", CmdData::Type::SETPOINT_LIST_DATA_TYPE},
    {"smartEnergyManagementPsConfigurationRequestCall",
     CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE},
    {"smartEnergyManagementPsData",
     CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE},
    {"smartEnergyManagementPsPriceCalculationRequestCall",
     CmdData::Type::
         SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE},
    {"smartEnergyManagementPsPriceData",
     CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_TYPE},
    {"specificationVersionListData",
     CmdData::Type::SPECIFICATION_VERSION_LIST_DATA_TYPE},
    {"subscriptionManagementDeleteCall",
     CmdData::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE},
    {"subscriptionManagementEntryListData",
     CmdData::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE},
    {"subscriptionManagementRequestCall",
     CmdData::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_TYPE},
    {"supplyConditionDescriptionListData",
     CmdData::Type::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_TYPE},
    {"supplyConditionListData", CmdData::Type::SUPPLY_CONDITION_LIST_DATA_TYPE},
    {"supplyConditionThresholdRelationListData",
     CmdData::Type::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE},
    {"tariffBoundaryRelationListData",
     CmdData::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE},
    {"tariffDescriptionListData",
     CmdData::Type::TARIFF_DESCRIPTION_LIST_DATA_TYPE},
    {"tariffListData", CmdData::Type::TARIFF_LIST_DATA_TYPE},
    {"tariffOverallConstraintsData",
     CmdData::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE},
    {"tariffTierRelationListData",
     CmdData::Type::TARIFF_TIER_RELATION_LIST_DATA_TYPE},
    {"taskManagementJobDescriptionListData",
     CmdData::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE},
    {"taskManagementJobListData",
     CmdData::Type::TASK_MANAGEMENT_JOB_LIST_DATA_TYPE},
    {"taskManagementJobRelationListData",
     CmdData::Type::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE},
    {"taskManagementOverviewData",
     CmdData::Type::TASK_MANAGEMENT_OVERVIEW_DATA_TYPE},
    {"thresholdConstraintsListData",
     CmdData::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE},
    {"thresholdDescriptionListData",
     CmdData::Type::THRESHOLD_DESCRIPTION_LIST_DATA_TYPE},
    {"thresholdListData", CmdData::Type::THRESHOLD_LIST_DATA_TYPE},
    {"tierBoundaryDescriptionListData",
     CmdData::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE},
    {"tierBoundaryListData", CmdData::Type::TIER_BOUNDARY_LIST_DATA_TYPE},
    {"tierDescriptionListData", CmdData::Type::TIER_DESCRIPTION_LIST_DATA_TYPE},
    {"tierIncentiveRelationListData",
     CmdData::Type::TIER_INCENTIVE_RELATION_LIST_DATA_TYPE},
    {"tierListData", CmdData::Type::TIER_LIST_DATA_TYPE},
    {"timeDistributorData", CmdData::Type::TIME_DISTRIBUTOR_DATA_TYPE},
    {"timeDistributorEnquiryCall",
     CmdData::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE},
    {"timeInformationData", CmdData::Type::TIME_INFORMATION_DATA_TYPE},
    {"timePrecisionData", CmdData::Type::TIME_PRECISION_DATA_TYPE},
    {"timeSeriesConstraintsListData",
     CmdData::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_TYPE},
    {"timeSeriesDescriptionListData",
     CmdData::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_TYPE},
    {"timeSeriesListData", CmdData::Type::TIME_SERIES_LIST_DATA_TYPE},
    {"timeTableConstraintsListData",
     CmdData::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE},
    {"timeTableDescriptionListData",
     CmdData::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE},
    {"timeTableListData", CmdData::Type::TIME_TABLE_LIST_DATA_TYPE},
    {"useCaseInformationListData",
     CmdData::Type::USE_CASE_INFORMATION_LIST_DATA_TYPE}};

std::string CmdData::getStringFromType(CmdData::Type type) {
  switch (type) {
  case CmdData::Type::ACTUATOR_LEVEL_DATA_TYPE: {
    return "actuatorLevelData";
  }
  case CmdData::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_TYPE: {
    return "actuatorLevelDescriptionData";
  }
  case CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE: {
    return "actuatorSwitchData";
  }
  case CmdData::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_TYPE: {
    return "actuatorSwitchDescriptionData";
  }
  case CmdData::Type::ALARM_LIST_DATA_TYPE: {
    return "alarmListData";
  }
  case CmdData::Type::BILL_CONSTRAINTS_LIST_DATA_TYPE: {
    return "billConstraintsListData";
  }
  case CmdData::Type::BILL_DESCRIPTION_LIST_DATA_TYPE: {
    return "billDescriptionListData";
  }
  case CmdData::Type::BILL_LIST_DATA_TYPE: {
    return "billListData";
  }
  case CmdData::Type::BINDING_MANAGEMENT_DELETE_CALL_TYPE: {
    return "bindingManagementDeleteCall";
  }
  case CmdData::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE: {
    return "bindingManagementEntryListData";
  }
  case CmdData::Type::BINDING_MANAGEMENT_REQUEST_CALL_TYPE: {
    return "bindingManagementRequestCall";
  }
  case CmdData::Type::COMMODITY_LIST_DATA_TYPE: {
    return "commodityListData";
  }
  case CmdData::Type::DATA_TUNNELING_CALL_TYPE: {
    return "dataTunnelingCall";
  }
  case CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE: {
    return "deviceClassificationManufacturerData";
  }
  case CmdData::Type::DEVICE_CLASSIFICATION_USER_DATA_TYPE: {
    return "deviceClassificationUserData";
  }
  case CmdData::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE: {
    return "deviceConfigurationKeyValueConstraintsListData";
  }
  case CmdData::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE: {
    return "deviceConfigurationKeyValueDescriptionListData";
  }
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_TYPE: {
    return "deviceConfigurationKeyValueListData";
  }
  case CmdData::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE: {
    return "deviceDiagnosisHeartbeatData";
  }
  case CmdData::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE: {
    return "deviceDiagnosisServiceData";
  }
  case CmdData::Type::DEVICE_DIAGNOSIS_STATE_DATA_TYPE: {
    return "deviceDiagnosisStateData";
  }
  case CmdData::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE: {
    return "directControlActivityListData";
  }
  case CmdData::Type::DIRECT_CONTROL_DESCRIPTION_DATA_TYPE: {
    return "directControlDescriptionData";
  }
  case CmdData::Type::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE: {
    return "electricalConnectionDescriptionListData";
  }
  case CmdData::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE: {
    return "electricalConnectionParameterDescriptionListData";
  }
  case CmdData::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE: {
    return "electricalConnectionPermittedValueSetListData";
  }
  case CmdData::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE: {
    return "electricalConnectionStateListData";
  }
  case CmdData::Type::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE: {
    return "hvacOperationModeDescriptionListData";
  }
  case CmdData::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE: {
    return "hvacOverrunDescriptionListData";
  }
  case CmdData::Type::HVAC_OVERRUN_LIST_DATA_TYPE: {
    return "hvacOverrunListData";
  }
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE: {
    return "hvacSystemFunctionDescriptionListData";
  }
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE: {
    return "hvacSystemFunctionListData";
  }
  case CmdData::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE: {
    return "hvacSystemFunctionOperationModeRelationListData";
  }
  case CmdData::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE: {
    return "hvacSystemFunctionPowerSequenceRelationListData";
  }
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE: {
    return "hvacSystemFunctionSetpointRelationListData";
  }
  case CmdData::Type::IDENTIFICATION_LIST_DATA_TYPE: {
    return "identificationListData";
  }
  case CmdData::Type::INCENTIVE_DESCRIPTION_LIST_DATA_TYPE: {
    return "incentiveDescriptionListData";
  }
  case CmdData::Type::INCENTIVE_LIST_DATA_TYPE: {
    return "incentiveListData";
  }
  case CmdData::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE: {
    return "incentiveTableConstraintsData";
  }
  case CmdData::Type::INCENTIVE_TABLE_DATA_TYPE: {
    return "incentiveTableData";
  }
  case CmdData::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_TYPE: {
    return "incentiveTableDescriptionData";
  }
  case CmdData::Type::LOAD_CONTROL_EVENT_LIST_DATA_TYPE: {
    return "loadControlEventListData";
  }
  case CmdData::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE: {
    return "loadControlLimitConstraintsListData";
  }
  case CmdData::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE: {
    return "loadControlLimitDescriptionListData";
  }
  case CmdData::Type::LOAD_CONTROL_LIMIT_LIST_DATA_TYPE: {
    return "loadControlLimitListData";
  }
  case CmdData::Type::LOAD_CONTROL_NODE_DATA_TYPE: {
    return "loadControlNodeData";
  }
  case CmdData::Type::LOAD_CONTROL_STATE_LIST_DATA_TYPE: {
    return "loadControlStateListData";
  }
  case CmdData::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE: {
    return "measurementConstraintsListData";
  }
  case CmdData::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE: {
    return "measurementDescriptionListData";
  }
  case CmdData::Type::MEASUREMENT_LIST_DATA_TYPE: {
    return "measurementListData";
  }
  case CmdData::Type::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE: {
    return "measurementThresholdRelationListData";
  }
  case CmdData::Type::MESSAGING_LIST_DATA_TYPE: {
    return "messagingListData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_ABORT_CALL_TYPE: {
    return "networkManagementAbortCall";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE: {
    return "networkManagementAddNodeCall";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE: {
    return "networkManagementDeviceDescriptionListData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE: {
    return "networkManagementDiscoverCall";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE: {
    return "networkManagementEntityDescriptionListData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE: {
    return "networkManagementFeatureDescriptionListData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE: {
    return "networkManagementJoiningModeData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE: {
    return "networkManagementModifyNodeCall";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE: {
    return "networkManagementProcessStateData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE: {
    return "networkManagementRemoveNodeCall";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE: {
    return "networkManagementReportCandidateData";
  }
  case CmdData::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE: {
    return "networkManagementScanNetworkCall";
  }
  case CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE: {
    return "nodeManagementBindingData";
  }
  case CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE: {
    return "nodeManagementBindingDeleteCall";
  }
  case CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE: {
    return "nodeManagementBindingRequestCall";
  }
  case CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE: {
    return "nodeManagementDestinationListData";
  }
  case CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE: {
    return "nodeManagementDetailedDiscoveryData";
  }
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE: {
    return "nodeManagementSubscriptionData";
  }
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE: {
    return "nodeManagementSubscriptionDeleteCall";
  }
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE: {
    return "nodeManagementSubscriptionRequestCall";
  }
  case CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE: {
    return "nodeManagementUseCaseData";
  }
  case CmdData::Type::OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE: {
    return "operatingConstraintsDurationListData";
  }
  case CmdData::Type::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE: {
    return "operatingConstraintsInterruptListData";
  }
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE: {
    return "operatingConstraintsPowerDescriptionListData";
  }
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE: {
    return "operatingConstraintsPowerLevelListData";
  }
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE: {
    return "operatingConstraintsPowerRangeListData";
  }
  case CmdData::Type::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE: {
    return "operatingConstraintsResumeImplicationListData";
  }
  case CmdData::Type::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE: {
    return "powerSequenceAlternativesRelationListData";
  }
  case CmdData::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE: {
    return "powerSequenceDescriptionListData";
  }
  case CmdData::Type::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE: {
    return "powerSequenceNodeScheduleInformationData";
  }
  case CmdData::Type::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE: {
    return "powerSequencePriceCalculationRequestCall";
  }
  case CmdData::Type::POWER_SEQUENCE_PRICE_LIST_DATA_TYPE: {
    return "powerSequencePriceListData";
  }
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE: {
    return "powerSequenceScheduleConfigurationRequestCall";
  }
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE: {
    return "powerSequenceScheduleConstraintsListData";
  }
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE: {
    return "powerSequenceScheduleListData";
  }
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE: {
    return "powerSequenceSchedulePreferenceListData";
  }
  case CmdData::Type::POWER_SEQUENCE_STATE_LIST_DATA_TYPE: {
    return "powerSequenceStateListData";
  }
  case CmdData::Type::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE: {
    return "powerTimeSlotScheduleConstraintsListData";
  }
  case CmdData::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE: {
    return "powerTimeSlotScheduleListData";
  }
  case CmdData::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE: {
    return "powerTimeSlotValueListData";
  }
  case CmdData::Type::RESULT_DATA_TYPE: {
    return "resultData";
  }
  case CmdData::Type::SENSING_DESCRIPTION_DATA_TYPE: {
    return "sensingDescriptionData";
  }
  case CmdData::Type::SENSING_LIST_DATA_TYPE: {
    return "sensingListData";
  }
  case CmdData::Type::SETPOINT_CONSTRAINTS_LIST_DATA_TYPE: {
    return "setpointConstraintsListData";
  }
  case CmdData::Type::SETPOINT_DESCRIPTION_LIST_DATA_TYPE: {
    return "setpointDescriptionListData";
  }
  case CmdData::Type::SETPOINT_LIST_DATA_TYPE: {
    return "setpointListData";
  }
  case CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE: {
    return "smartEnergyManagementPsConfigurationRequestCall";
  }
  case CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE: {
    return "smartEnergyManagementPsData";
  }
  case CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE: {
    return "smartEnergyManagementPsPriceCalculationRequestCall";
  }
  case CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_TYPE: {
    return "smartEnergyManagementPsPriceData";
  }
  case CmdData::Type::SPECIFICATION_VERSION_LIST_DATA_TYPE: {
    return "specificationVersionListData";
  }
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE: {
    return "subscriptionManagementDeleteCall";
  }
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE: {
    return "subscriptionManagementEntryListData";
  }
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_TYPE: {
    return "subscriptionManagementRequestCall";
  }
  case CmdData::Type::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_TYPE: {
    return "supplyConditionDescriptionListData";
  }
  case CmdData::Type::SUPPLY_CONDITION_LIST_DATA_TYPE: {
    return "supplyConditionListData";
  }
  case CmdData::Type::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE: {
    return "supplyConditionThresholdRelationListData";
  }
  case CmdData::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE: {
    return "tariffBoundaryRelationListData";
  }
  case CmdData::Type::TARIFF_DESCRIPTION_LIST_DATA_TYPE: {
    return "tariffDescriptionListData";
  }
  case CmdData::Type::TARIFF_LIST_DATA_TYPE: {
    return "tariffListData";
  }
  case CmdData::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE: {
    return "tariffOverallConstraintsData";
  }
  case CmdData::Type::TARIFF_TIER_RELATION_LIST_DATA_TYPE: {
    return "tariffTierRelationListData";
  }
  case CmdData::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE: {
    return "taskManagementJobDescriptionListData";
  }
  case CmdData::Type::TASK_MANAGEMENT_JOB_LIST_DATA_TYPE: {
    return "taskManagementJobListData";
  }
  case CmdData::Type::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE: {
    return "taskManagementJobRelationListData";
  }
  case CmdData::Type::TASK_MANAGEMENT_OVERVIEW_DATA_TYPE: {
    return "taskManagementOverviewData";
  }
  case CmdData::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE: {
    return "thresholdConstraintsListData";
  }
  case CmdData::Type::THRESHOLD_DESCRIPTION_LIST_DATA_TYPE: {
    return "thresholdDescriptionListData";
  }
  case CmdData::Type::THRESHOLD_LIST_DATA_TYPE: {
    return "thresholdListData";
  }
  case CmdData::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE: {
    return "tierBoundaryDescriptionListData";
  }
  case CmdData::Type::TIER_BOUNDARY_LIST_DATA_TYPE: {
    return "tierBoundaryListData";
  }
  case CmdData::Type::TIER_DESCRIPTION_LIST_DATA_TYPE: {
    return "tierDescriptionListData";
  }
  case CmdData::Type::TIER_INCENTIVE_RELATION_LIST_DATA_TYPE: {
    return "tierIncentiveRelationListData";
  }
  case CmdData::Type::TIER_LIST_DATA_TYPE: {
    return "tierListData";
  }
  case CmdData::Type::TIME_DISTRIBUTOR_DATA_TYPE: {
    return "timeDistributorData";
  }
  case CmdData::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE: {
    return "timeDistributorEnquiryCall";
  }
  case CmdData::Type::TIME_INFORMATION_DATA_TYPE: {
    return "timeInformationData";
  }
  case CmdData::Type::TIME_PRECISION_DATA_TYPE: {
    return "timePrecisionData";
  }
  case CmdData::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_TYPE: {
    return "timeSeriesConstraintsListData";
  }
  case CmdData::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_TYPE: {
    return "timeSeriesDescriptionListData";
  }
  case CmdData::Type::TIME_SERIES_LIST_DATA_TYPE: {
    return "timeSeriesListData";
  }
  case CmdData::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE: {
    return "timeTableConstraintsListData";
  }
  case CmdData::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE: {
    return "timeTableDescriptionListData";
  }
  case CmdData::Type::TIME_TABLE_LIST_DATA_TYPE: {
    return "timeTableListData";
  }
  case CmdData::Type::USE_CASE_INFORMATION_LIST_DATA_TYPE: {
    return "useCaseInformationListData";
  }
  default: { return ""; }
  }
}

CmdData::Type CmdData::getTypeFromString(const std::string &type) {
  auto it = STRING_TO_TYPE.find(type);
  if (it != STRING_TO_TYPE.end()) {
    return it->second;
  } else {
    return CmdData::Type::UNDEFINED;
  }
}

Function::Value CmdData::getFunctionFromType(CmdData::Type type) {
  switch (type) {
  case CmdData::Type::UNDEFINED:
    return Function::Value::UNDEFINED__;
  case CmdData::Type::ACTUATOR_LEVEL_DATA_TYPE:
    return Function::Value::ACTUATOR_LEVEL_DATA;
  case CmdData::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_TYPE:
    return Function::Value::ACTUATOR_LEVEL_DESCRIPTION_DATA;
  case CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE:
    return Function::Value::ACTUATOR_SWITCH_DATA;
  case CmdData::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_TYPE:
    return Function::Value::ACTUATOR_SWITCH_DESCRIPTION_DATA;
  case CmdData::Type::ALARM_LIST_DATA_TYPE:
    return Function::Value::ALARM_LIST_DATA;
  case CmdData::Type::BILL_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::BILL_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::BILL_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::BILL_DESCRIPTION_LIST_DATA;
  case CmdData::Type::BILL_LIST_DATA_TYPE:
    return Function::Value::BILL_LIST_DATA;
  case CmdData::Type::BINDING_MANAGEMENT_DELETE_CALL_TYPE:
    return Function::Value::BINDING_MANAGEMENT_DELETE_CALL;
  case CmdData::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE:
    return Function::Value::BINDING_MANAGEMENT_ENTRY_LIST_DATA;
  case CmdData::Type::BINDING_MANAGEMENT_REQUEST_CALL_TYPE:
    return Function::Value::BINDING_MANAGEMENT_REQUEST_CALL;
  case CmdData::Type::COMMODITY_LIST_DATA_TYPE:
    return Function::Value::COMMODITY_LIST_DATA;
  case CmdData::Type::DATA_TUNNELING_CALL_TYPE:
    return Function::Value::DATA_TUNNELING_CALL;
  case CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE:
    return Function::Value::DEVICE_CLASSIFICATION_MANUFACTURER_DATA;
  case CmdData::Type::DEVICE_CLASSIFICATION_USER_DATA_TYPE:
    return Function::Value::DEVICE_CLASSIFICATION_USER_DATA;
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::
        DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::
        DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_TYPE:
    return Function::Value::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA;
  case CmdData::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE:
    return Function::Value::DEVICE_DIAGNOSIS_HEARTBEAT_DATA;
  case CmdData::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE:
    return Function::Value::DEVICE_DIAGNOSIS_SERVICE_DATA;
  case CmdData::Type::DEVICE_DIAGNOSIS_STATE_DATA_TYPE:
    return Function::Value::DEVICE_DIAGNOSIS_STATE_DATA;
  case CmdData::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE:
    return Function::Value::DIRECT_CONTROL_ACTIVITY_LIST_DATA;
  case CmdData::Type::DIRECT_CONTROL_DESCRIPTION_DATA_TYPE:
    return Function::Value::DIRECT_CONTROL_DESCRIPTION_DATA;
  case CmdData::Type::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA;
  case CmdData::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::
        ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA;
  case CmdData::Type::ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE:
    return Function::Value::ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA;
  case CmdData::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE:
    return Function::Value::ELECTRICAL_CONNECTION_STATE_LIST_DATA;
  case CmdData::Type::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::HVAC_OVERRUN_DESCRIPTION_LIST_DATA;
  case CmdData::Type::HVAC_OVERRUN_LIST_DATA_TYPE:
    return Function::Value::HVAC_OVERRUN_LIST_DATA;
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA;
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE:
    return Function::Value::HVAC_SYSTEM_FUNCTION_LIST_DATA;
  case CmdData::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE:
    return Function::Value::
        HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA;
  case CmdData::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE:
    return Function::Value::
        HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA;
  case CmdData::Type::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE:
    return Function::Value::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA;
  case CmdData::Type::IDENTIFICATION_LIST_DATA_TYPE:
    return Function::Value::IDENTIFICATION_LIST_DATA;
  case CmdData::Type::INCENTIVE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::INCENTIVE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::INCENTIVE_LIST_DATA_TYPE:
    return Function::Value::INCENTIVE_LIST_DATA;
  case CmdData::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE:
    return Function::Value::INCENTIVE_TABLE_CONSTRAINTS_DATA;
  case CmdData::Type::INCENTIVE_TABLE_DATA_TYPE:
    return Function::Value::INCENTIVE_TABLE_DATA;
  case CmdData::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_TYPE:
    return Function::Value::INCENTIVE_TABLE_DESCRIPTION_DATA;
  case CmdData::Type::LOAD_CONTROL_EVENT_LIST_DATA_TYPE:
    return Function::Value::LOAD_CONTROL_EVENT_LIST_DATA;
  case CmdData::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA;
  case CmdData::Type::LOAD_CONTROL_LIMIT_LIST_DATA_TYPE:
    return Function::Value::LOAD_CONTROL_LIMIT_LIST_DATA;
  case CmdData::Type::LOAD_CONTROL_NODE_DATA_TYPE:
    return Function::Value::LOAD_CONTROL_NODE_DATA;
  case CmdData::Type::LOAD_CONTROL_STATE_LIST_DATA_TYPE:
    return Function::Value::LOAD_CONTROL_STATE_LIST_DATA;
  case CmdData::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::MEASUREMENT_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::MEASUREMENT_DESCRIPTION_LIST_DATA;
  case CmdData::Type::MEASUREMENT_LIST_DATA_TYPE:
    return Function::Value::MEASUREMENT_LIST_DATA;
  case CmdData::Type::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE:
    return Function::Value::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA;
  case CmdData::Type::MESSAGING_LIST_DATA_TYPE:
    return Function::Value::MESSAGING_LIST_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_ABORT_CALL_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_ABORT_CALL;
  case CmdData::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_ADD_NODE_CALL;
  case CmdData::Type::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_DISCOVER_CALL;
  case CmdData::Type::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_JOINING_MODE_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_MODIFY_NODE_CALL;
  case CmdData::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_PROCESS_STATE_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_REMOVE_NODE_CALL;
  case CmdData::Type::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA;
  case CmdData::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE:
    return Function::Value::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL;
  case CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE:
    return Function::Value::NODE_MANAGEMENT_BINDING_DATA;
  case CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE:
    return Function::Value::NODE_MANAGEMENT_BINDING_DELETE_CALL;
  case CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE:
    return Function::Value::NODE_MANAGEMENT_BINDING_REQUEST_CALL;
  case CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE:
    return Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA;
  case CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE:
    return Function::Value::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA;
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE:
    return Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DATA;
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE:
    return Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL;
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE:
    return Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL;
  case CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE:
    return Function::Value::NODE_MANAGEMENT_USE_CASE_DATA;
  case CmdData::Type::OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE:
    return Function::Value::OPERATING_CONSTRAINTS_DURATION_LIST_DATA;
  case CmdData::Type::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE:
    return Function::Value::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA;
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA;
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE:
    return Function::Value::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA;
  case CmdData::Type::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE:
    return Function::Value::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA;
  case CmdData::Type::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE:
    return Function::Value::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA;
  case CmdData::Type::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE:
    return Function::Value::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL;
  case CmdData::Type::POWER_SEQUENCE_PRICE_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_PRICE_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE:
    return Function::Value::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL;
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_SCHEDULE_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA;
  case CmdData::Type::POWER_SEQUENCE_STATE_LIST_DATA_TYPE:
    return Function::Value::POWER_SEQUENCE_STATE_LIST_DATA;
  case CmdData::Type::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE:
    return Function::Value::POWER_TIME_SLOT_SCHEDULE_LIST_DATA;
  case CmdData::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE:
    return Function::Value::POWER_TIME_SLOT_VALUE_LIST_DATA;
  case CmdData::Type::RESULT_DATA_TYPE:
    return Function::Value::RESULT_DATA;
  case CmdData::Type::SENSING_DESCRIPTION_DATA_TYPE:
    return Function::Value::SENSING_DESCRIPTION_DATA;
  case CmdData::Type::SENSING_LIST_DATA_TYPE:
    return Function::Value::SENSING_LIST_DATA;
  case CmdData::Type::SETPOINT_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::SETPOINT_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::SETPOINT_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::SETPOINT_DESCRIPTION_LIST_DATA;
  case CmdData::Type::SETPOINT_LIST_DATA_TYPE:
    return Function::Value::SETPOINT_LIST_DATA;
  case CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE:
    return Function::Value::
        SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL;
  case CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE:
    return Function::Value::SMART_ENERGY_MANAGEMENT_PS_DATA;
  case CmdData::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE:
    return Function::Value::
        SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL;
  case CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_TYPE:
    return Function::Value::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA;
  case CmdData::Type::SPECIFICATION_VERSION_LIST_DATA_TYPE:
    return Function::Value::SPECIFICATION_VERSION_LIST_DATA;
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE:
    return Function::Value::SUBSCRIPTION_MANAGEMENT_DELETE_CALL;
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE:
    return Function::Value::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA;
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_TYPE:
    return Function::Value::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL;
  case CmdData::Type::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA;
  case CmdData::Type::SUPPLY_CONDITION_LIST_DATA_TYPE:
    return Function::Value::SUPPLY_CONDITION_LIST_DATA;
  case CmdData::Type::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE:
    return Function::Value::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA;
  case CmdData::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE:
    return Function::Value::TARIFF_BOUNDARY_RELATION_LIST_DATA;
  case CmdData::Type::TARIFF_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::TARIFF_DESCRIPTION_LIST_DATA;
  case CmdData::Type::TARIFF_LIST_DATA_TYPE:
    return Function::Value::TARIFF_LIST_DATA;
  case CmdData::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE:
    return Function::Value::TARIFF_OVERALL_CONSTRAINTS_DATA;
  case CmdData::Type::TARIFF_TIER_RELATION_LIST_DATA_TYPE:
    return Function::Value::TARIFF_TIER_RELATION_LIST_DATA;
  case CmdData::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA;
  case CmdData::Type::TASK_MANAGEMENT_JOB_LIST_DATA_TYPE:
    return Function::Value::TASK_MANAGEMENT_JOB_LIST_DATA;
  case CmdData::Type::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE:
    return Function::Value::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA;
  case CmdData::Type::TASK_MANAGEMENT_OVERVIEW_DATA_TYPE:
    return Function::Value::TASK_MANAGEMENT_OVERVIEW_DATA;
  case CmdData::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::THRESHOLD_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::THRESHOLD_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::THRESHOLD_DESCRIPTION_LIST_DATA;
  case CmdData::Type::THRESHOLD_LIST_DATA_TYPE:
    return Function::Value::THRESHOLD_LIST_DATA;
  case CmdData::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::TIER_BOUNDARY_DESCRIPTION_LIST_DATA;
  case CmdData::Type::TIER_BOUNDARY_LIST_DATA_TYPE:
    return Function::Value::TIER_BOUNDARY_LIST_DATA;
  case CmdData::Type::TIER_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::TIER_DESCRIPTION_LIST_DATA;
  case CmdData::Type::TIER_INCENTIVE_RELATION_LIST_DATA_TYPE:
    return Function::Value::TIER_INCENTIVE_RELATION_LIST_DATA;
  case CmdData::Type::TIER_LIST_DATA_TYPE:
    return Function::Value::TIER_LIST_DATA;
  case CmdData::Type::TIME_DISTRIBUTOR_DATA_TYPE:
    return Function::Value::TIME_DISTRIBUTOR_DATA;
  case CmdData::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE:
    return Function::Value::TIME_DISTRIBUTOR_ENQUIRY_CALL;
  case CmdData::Type::TIME_INFORMATION_DATA_TYPE:
    return Function::Value::TIME_INFORMATION_DATA;
  case CmdData::Type::TIME_PRECISION_DATA_TYPE:
    return Function::Value::TIME_PRECISION_DATA;
  case CmdData::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::TIME_SERIES_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::TIME_SERIES_DESCRIPTION_LIST_DATA;
  case CmdData::Type::TIME_SERIES_LIST_DATA_TYPE:
    return Function::Value::TIME_SERIES_LIST_DATA;
  case CmdData::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE:
    return Function::Value::TIME_TABLE_CONSTRAINTS_LIST_DATA;
  case CmdData::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE:
    return Function::Value::TIME_TABLE_DESCRIPTION_LIST_DATA;
  case CmdData::Type::TIME_TABLE_LIST_DATA_TYPE:
    return Function::Value::TIME_TABLE_LIST_DATA;
  case CmdData::Type::USE_CASE_INFORMATION_LIST_DATA_TYPE:
    return Function::Value::USE_CASE_INFORMATION_LIST_DATA;

  default:
    return Function::Value::UNDEFINED__;
  }
}

CmdData::Type CmdData::getTypeFromFunction(Function::Value value) {
  switch (value) {
  case Function::Value::UNDEFINED__:
    return CmdData::Type::UNDEFINED;
  case Function::Value::ACTUATOR_LEVEL_DATA:
    return CmdData::Type::ACTUATOR_LEVEL_DATA_TYPE;
  case Function::Value::ACTUATOR_LEVEL_DESCRIPTION_DATA:
    return CmdData::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_TYPE;
  case Function::Value::ACTUATOR_SWITCH_DATA:
    return CmdData::Type::ACTUATOR_SWITCH_DATA_TYPE;
  case Function::Value::ACTUATOR_SWITCH_DESCRIPTION_DATA:
    return CmdData::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_TYPE;
  case Function::Value::ALARM_LIST_DATA:
    return CmdData::Type::ALARM_LIST_DATA_TYPE;
  case Function::Value::BILL_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::BILL_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::BILL_DESCRIPTION_LIST_DATA:
    return CmdData::Type::BILL_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::BILL_LIST_DATA:
    return CmdData::Type::BILL_LIST_DATA_TYPE;
  case Function::Value::BINDING_MANAGEMENT_DELETE_CALL:
    return CmdData::Type::BINDING_MANAGEMENT_DELETE_CALL_TYPE;
  case Function::Value::BINDING_MANAGEMENT_ENTRY_LIST_DATA:
    return CmdData::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE;
  case Function::Value::BINDING_MANAGEMENT_REQUEST_CALL:
    return CmdData::Type::BINDING_MANAGEMENT_REQUEST_CALL_TYPE;
  case Function::Value::COMMODITY_LIST_DATA:
    return CmdData::Type::COMMODITY_LIST_DATA_TYPE;
  case Function::Value::DATA_TUNNELING_CALL:
    return CmdData::Type::DATA_TUNNELING_CALL_TYPE;
  case Function::Value::DEVICE_CLASSIFICATION_MANUFACTURER_DATA:
    return CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE;
  case Function::Value::DEVICE_CLASSIFICATION_USER_DATA:
    return CmdData::Type::DEVICE_CLASSIFICATION_USER_DATA_TYPE;
  case Function::Value::DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::
        DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::
        DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA:
    return CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_TYPE;
  case Function::Value::DEVICE_DIAGNOSIS_HEARTBEAT_DATA:
    return CmdData::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE;
  case Function::Value::DEVICE_DIAGNOSIS_SERVICE_DATA:
    return CmdData::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE;
  case Function::Value::DEVICE_DIAGNOSIS_STATE_DATA:
    return CmdData::Type::DEVICE_DIAGNOSIS_STATE_DATA_TYPE;
  case Function::Value::DIRECT_CONTROL_ACTIVITY_LIST_DATA:
    return CmdData::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE;
  case Function::Value::DIRECT_CONTROL_DESCRIPTION_DATA:
    return CmdData::Type::DIRECT_CONTROL_DESCRIPTION_DATA_TYPE;
  case Function::Value::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA:
    return CmdData::Type::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA:
    return CmdData::Type::
        ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA:
    return CmdData::Type::
        ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE;
  case Function::Value::ELECTRICAL_CONNECTION_STATE_LIST_DATA:
    return CmdData::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE;
  case Function::Value::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::HVAC_OVERRUN_DESCRIPTION_LIST_DATA:
    return CmdData::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::HVAC_OVERRUN_LIST_DATA:
    return CmdData::Type::HVAC_OVERRUN_LIST_DATA_TYPE;
  case Function::Value::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA:
    return CmdData::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::HVAC_SYSTEM_FUNCTION_LIST_DATA:
    return CmdData::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE;
  case Function::Value::HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA:
    return CmdData::Type::
        HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE;
  case Function::Value::HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA:
    return CmdData::Type::
        HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE;
  case Function::Value::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA:
    return CmdData::Type::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE;
  case Function::Value::IDENTIFICATION_LIST_DATA:
    return CmdData::Type::IDENTIFICATION_LIST_DATA_TYPE;
  case Function::Value::INCENTIVE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::INCENTIVE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::INCENTIVE_LIST_DATA:
    return CmdData::Type::INCENTIVE_LIST_DATA_TYPE;
  case Function::Value::INCENTIVE_TABLE_CONSTRAINTS_DATA:
    return CmdData::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE;
  case Function::Value::INCENTIVE_TABLE_DATA:
    return CmdData::Type::INCENTIVE_TABLE_DATA_TYPE;
  case Function::Value::INCENTIVE_TABLE_DESCRIPTION_DATA:
    return CmdData::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_TYPE;
  case Function::Value::LOAD_CONTROL_EVENT_LIST_DATA:
    return CmdData::Type::LOAD_CONTROL_EVENT_LIST_DATA_TYPE;
  case Function::Value::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA:
    return CmdData::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::LOAD_CONTROL_LIMIT_LIST_DATA:
    return CmdData::Type::LOAD_CONTROL_LIMIT_LIST_DATA_TYPE;
  case Function::Value::LOAD_CONTROL_NODE_DATA:
    return CmdData::Type::LOAD_CONTROL_NODE_DATA_TYPE;
  case Function::Value::LOAD_CONTROL_STATE_LIST_DATA:
    return CmdData::Type::LOAD_CONTROL_STATE_LIST_DATA_TYPE;
  case Function::Value::MEASUREMENT_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::MEASUREMENT_DESCRIPTION_LIST_DATA:
    return CmdData::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::MEASUREMENT_LIST_DATA:
    return CmdData::Type::MEASUREMENT_LIST_DATA_TYPE;
  case Function::Value::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA:
    return CmdData::Type::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE;
  case Function::Value::MESSAGING_LIST_DATA:
    return CmdData::Type::MESSAGING_LIST_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_ABORT_CALL:
    return CmdData::Type::NETWORK_MANAGEMENT_ABORT_CALL_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_ADD_NODE_CALL:
    return CmdData::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_DISCOVER_CALL:
    return CmdData::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA:
    return CmdData::Type::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_JOINING_MODE_DATA:
    return CmdData::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_MODIFY_NODE_CALL:
    return CmdData::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_PROCESS_STATE_DATA:
    return CmdData::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_REMOVE_NODE_CALL:
    return CmdData::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA:
    return CmdData::Type::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE;
  case Function::Value::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL:
    return CmdData::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE;
  case Function::Value::NODE_MANAGEMENT_BINDING_DATA:
    return CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE;
  case Function::Value::NODE_MANAGEMENT_BINDING_DELETE_CALL:
    return CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE;
  case Function::Value::NODE_MANAGEMENT_BINDING_REQUEST_CALL:
    return CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE;
  case Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA:
    return CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE;
  case Function::Value::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA:
    return CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE;
  case Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DATA:
    return CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE;
  case Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL:
    return CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE;
  case Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL:
    return CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE;
  case Function::Value::NODE_MANAGEMENT_USE_CASE_DATA:
    return CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE;
  case Function::Value::OPERATING_CONSTRAINTS_DURATION_LIST_DATA:
    return CmdData::Type::OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE;
  case Function::Value::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA:
    return CmdData::Type::OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE;
  case Function::Value::OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA:
    return CmdData::Type::
        OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA:
    return CmdData::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE;
  case Function::Value::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA:
    return CmdData::Type::OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE;
  case Function::Value::OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA:
    return CmdData::Type::
        OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA:
    return CmdData::Type::POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL:
    return CmdData::Type::POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE;
  case Function::Value::POWER_SEQUENCE_PRICE_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_PRICE_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL:
    return CmdData::Type::
        POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE;
  case Function::Value::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_SCHEDULE_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE;
  case Function::Value::POWER_SEQUENCE_STATE_LIST_DATA:
    return CmdData::Type::POWER_SEQUENCE_STATE_LIST_DATA_TYPE;
  case Function::Value::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::POWER_TIME_SLOT_SCHEDULE_LIST_DATA:
    return CmdData::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE;
  case Function::Value::POWER_TIME_SLOT_VALUE_LIST_DATA:
    return CmdData::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE;
  case Function::Value::RESULT_DATA:
    return CmdData::Type::RESULT_DATA_TYPE;
  case Function::Value::SENSING_DESCRIPTION_DATA:
    return CmdData::Type::SENSING_DESCRIPTION_DATA_TYPE;
  case Function::Value::SENSING_LIST_DATA:
    return CmdData::Type::SENSING_LIST_DATA_TYPE;
  case Function::Value::SETPOINT_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::SETPOINT_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::SETPOINT_DESCRIPTION_LIST_DATA:
    return CmdData::Type::SETPOINT_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::SETPOINT_LIST_DATA:
    return CmdData::Type::SETPOINT_LIST_DATA_TYPE;
  case Function::Value::SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL:
    return CmdData::Type::
        SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE;
  case Function::Value::SMART_ENERGY_MANAGEMENT_PS_DATA:
    return CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE;
  case Function::Value::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL:
    return CmdData::Type::
        SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE;
  case Function::Value::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA:
    return CmdData::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_TYPE;
  case Function::Value::SPECIFICATION_VERSION_LIST_DATA:
    return CmdData::Type::SPECIFICATION_VERSION_LIST_DATA_TYPE;
  case Function::Value::SUBSCRIPTION_MANAGEMENT_DELETE_CALL:
    return CmdData::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE;
  case Function::Value::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA:
    return CmdData::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE;
  case Function::Value::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL:
    return CmdData::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_TYPE;
  case Function::Value::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA:
    return CmdData::Type::SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::SUPPLY_CONDITION_LIST_DATA:
    return CmdData::Type::SUPPLY_CONDITION_LIST_DATA_TYPE;
  case Function::Value::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA:
    return CmdData::Type::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE;
  case Function::Value::TARIFF_BOUNDARY_RELATION_LIST_DATA:
    return CmdData::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE;
  case Function::Value::TARIFF_DESCRIPTION_LIST_DATA:
    return CmdData::Type::TARIFF_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::TARIFF_LIST_DATA:
    return CmdData::Type::TARIFF_LIST_DATA_TYPE;
  case Function::Value::TARIFF_OVERALL_CONSTRAINTS_DATA:
    return CmdData::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE;
  case Function::Value::TARIFF_TIER_RELATION_LIST_DATA:
    return CmdData::Type::TARIFF_TIER_RELATION_LIST_DATA_TYPE;
  case Function::Value::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA:
    return CmdData::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::TASK_MANAGEMENT_JOB_LIST_DATA:
    return CmdData::Type::TASK_MANAGEMENT_JOB_LIST_DATA_TYPE;
  case Function::Value::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA:
    return CmdData::Type::TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE;
  case Function::Value::TASK_MANAGEMENT_OVERVIEW_DATA:
    return CmdData::Type::TASK_MANAGEMENT_OVERVIEW_DATA_TYPE;
  case Function::Value::THRESHOLD_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::THRESHOLD_DESCRIPTION_LIST_DATA:
    return CmdData::Type::THRESHOLD_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::THRESHOLD_LIST_DATA:
    return CmdData::Type::THRESHOLD_LIST_DATA_TYPE;
  case Function::Value::TIER_BOUNDARY_DESCRIPTION_LIST_DATA:
    return CmdData::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::TIER_BOUNDARY_LIST_DATA:
    return CmdData::Type::TIER_BOUNDARY_LIST_DATA_TYPE;
  case Function::Value::TIER_DESCRIPTION_LIST_DATA:
    return CmdData::Type::TIER_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::TIER_INCENTIVE_RELATION_LIST_DATA:
    return CmdData::Type::TIER_INCENTIVE_RELATION_LIST_DATA_TYPE;
  case Function::Value::TIER_LIST_DATA:
    return CmdData::Type::TIER_LIST_DATA_TYPE;
  case Function::Value::TIME_DISTRIBUTOR_DATA:
    return CmdData::Type::TIME_DISTRIBUTOR_DATA_TYPE;
  case Function::Value::TIME_DISTRIBUTOR_ENQUIRY_CALL:
    return CmdData::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE;
  case Function::Value::TIME_INFORMATION_DATA:
    return CmdData::Type::TIME_INFORMATION_DATA_TYPE;
  case Function::Value::TIME_PRECISION_DATA:
    return CmdData::Type::TIME_PRECISION_DATA_TYPE;
  case Function::Value::TIME_SERIES_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::TIME_SERIES_DESCRIPTION_LIST_DATA:
    return CmdData::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::TIME_SERIES_LIST_DATA:
    return CmdData::Type::TIME_SERIES_LIST_DATA_TYPE;
  case Function::Value::TIME_TABLE_CONSTRAINTS_LIST_DATA:
    return CmdData::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE;
  case Function::Value::TIME_TABLE_DESCRIPTION_LIST_DATA:
    return CmdData::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE;
  case Function::Value::TIME_TABLE_LIST_DATA:
    return CmdData::Type::TIME_TABLE_LIST_DATA_TYPE;
  case Function::Value::USE_CASE_INFORMATION_LIST_DATA:
    return CmdData::Type::USE_CASE_INFORMATION_LIST_DATA_TYPE;

  default:
    return CmdData::Type::UNDEFINED;
  }
}

} // namespace keo_datagram