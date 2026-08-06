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

#include <keo_datagram/core/DataElements.h>

namespace keo_datagram {

std::map<std::string, DataElements::Type> DataElements::STRING_TO_TYPE = {
    {"actuatorLevelDataElements",
     DataElements::Type::ACTUATOR_LEVEL_DATA_ELEMENTS_TYPE},
    {"actuatorLevelDescriptionDataElements",
     DataElements::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"actuatorSwitchDataElements",
     DataElements::Type::ACTUATOR_SWITCH_DATA_ELEMENTS_TYPE},
    {"actuatorSwitchDescriptionDataElements",
     DataElements::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"alarmDataElements", DataElements::Type::ALARM_DATA_ELEMENTS_TYPE},
    {"billConstraintsDataElements",
     DataElements::Type::BILL_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"billDataElements", DataElements::Type::BILL_DATA_ELEMENTS_TYPE},
    {"billDescriptionDataElements",
     DataElements::Type::BILL_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"bindingManagementDeleteCallElements",
     DataElements::Type::BINDING_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE},
    {"bindingManagementEntryDataElements",
     DataElements::Type::BINDING_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE},
    {"bindingManagementRequestCallElements",
     DataElements::Type::BINDING_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE},
    {"commodityDataElements", DataElements::Type::COMMODITY_DATA_ELEMENTS_TYPE},
    {"dataTunnelingCallElements",
     DataElements::Type::DATA_TUNNELING_CALL_ELEMENTS_TYPE},
    {"deviceClassificationManufacturerDataElements",
     DataElements::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_ELEMENTS_TYPE},
    {"deviceClassificationUserDataElements",
     DataElements::Type::DEVICE_CLASSIFICATION_USER_DATA_ELEMENTS_TYPE},
    {"deviceConfigurationKeyValueConstraintsDataElements",
     DataElements::Type::
         DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"deviceConfigurationKeyValueDataElements",
     DataElements::Type::DEVICE_CONFIGURATION_KEY_VALUE_DATA_ELEMENTS_TYPE},
    {"deviceConfigurationKeyValueDescriptionDataElements",
     DataElements::Type::
         DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"deviceDiagnosisHeartbeatDataElements",
     DataElements::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_ELEMENTS_TYPE},
    {"deviceDiagnosisServiceDataElements",
     DataElements::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_ELEMENTS_TYPE},
    {"deviceDiagnosisStateDataElements",
     DataElements::Type::DEVICE_DIAGNOSIS_STATE_DATA_ELEMENTS_TYPE},
    {"directControlActivityDataElements",
     DataElements::Type::DIRECT_CONTROL_ACTIVITY_DATA_ELEMENTS_TYPE},
    {"directControlDescriptionDataElements",
     DataElements::Type::DIRECT_CONTROL_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"electricalConnectionDescriptionDataElements",
     DataElements::Type::ELECTRICAL_CONNECTION_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"electricalConnectionParameterDescriptionDataElements",
     DataElements::Type::
         ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"electricalConnectionPermittedValueSetDataElements",
     DataElements::Type::
         ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_DATA_ELEMENTS_TYPE},
    {"electricalConnectionStateDataElements",
     DataElements::Type::ELECTRICAL_CONNECTION_STATE_DATA_ELEMENTS_TYPE},
    {"hvacOperationModeDescriptionDataElements",
     DataElements::Type::HVAC_OPERATION_MODE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"hvacOverrunDataElements",
     DataElements::Type::HVAC_OVERRUN_DATA_ELEMENTS_TYPE},
    {"hvacOverrunDescriptionDataElements",
     DataElements::Type::HVAC_OVERRUN_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"hvacSystemFunctionDataElements",
     DataElements::Type::HVAC_SYSTEM_FUNCTION_DATA_ELEMENTS_TYPE},
    {"hvacSystemFunctionDescriptionDataElements",
     DataElements::Type::HVAC_SYSTEM_FUNCTION_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"hvacSystemFunctionOperationModeRelationDataElements",
     DataElements::Type::
         HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_DATA_ELEMENTS_TYPE},
    {"hvacSystemFunctionPowerSequenceRelationDataElements",
     DataElements::Type::
         HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_DATA_ELEMENTS_TYPE},
    {"hvacSystemFunctionSetpointRelationDataElements",
     DataElements::Type::
         HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_DATA_ELEMENTS_TYPE},
    {"identificationDataElements",
     DataElements::Type::IDENTIFICATION_DATA_ELEMENTS_TYPE},
    {"incentiveDataElements", DataElements::Type::INCENTIVE_DATA_ELEMENTS_TYPE},
    {"incentiveDescriptionDataElements",
     DataElements::Type::INCENTIVE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"incentiveTableConstraintsDataElements",
     DataElements::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"incentiveTableDataElements",
     DataElements::Type::INCENTIVE_TABLE_DATA_ELEMENTS_TYPE},
    {"incentiveTableDescriptionDataElements",
     DataElements::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"loadControlEventDataElements",
     DataElements::Type::LOAD_CONTROL_EVENT_DATA_ELEMENTS_TYPE},
    {"loadControlLimitConstraintsDataElements",
     DataElements::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"loadControlLimitDataElements",
     DataElements::Type::LOAD_CONTROL_LIMIT_DATA_ELEMENTS_TYPE},
    {"loadControlLimitDescriptionDataElements",
     DataElements::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"loadControlNodeDataElements",
     DataElements::Type::LOAD_CONTROL_NODE_DATA_ELEMENTS_TYPE},
    {"loadControlStateDataElements",
     DataElements::Type::LOAD_CONTROL_STATE_DATA_ELEMENTS_TYPE},
    {"measurementConstraintsDataElements",
     DataElements::Type::MEASUREMENT_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"measurementDataElements",
     DataElements::Type::MEASUREMENT_DATA_ELEMENTS_TYPE},
    {"measurementDescriptionDataElements",
     DataElements::Type::MEASUREMENT_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"measurementThresholdRelationDataElements",
     DataElements::Type::MEASUREMENT_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE},
    {"messagingDataElements", DataElements::Type::MESSAGING_DATA_ELEMENTS_TYPE},
    {"networkManagementAbortCallElements",
     DataElements::Type::NETWORK_MANAGEMENT_ABORT_CALL_ELEMENTS_TYPE},
    {"networkManagementAddNodeCallElements",
     DataElements::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_ELEMENTS_TYPE},
    {"networkManagementDeviceDescriptionDataElements",
     DataElements::Type::
         NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"networkManagementDiscoverCallElements",
     DataElements::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_ELEMENTS_TYPE},
    {"networkManagementEntityDescriptionDataElements",
     DataElements::Type::
         NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"networkManagementFeatureDescriptionDataElements",
     DataElements::Type::
         NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"networkManagementJoiningModeDataElements",
     DataElements::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_ELEMENTS_TYPE},
    {"networkManagementModifyNodeCallElements",
     DataElements::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_ELEMENTS_TYPE},
    {"networkManagementProcessStateDataElements",
     DataElements::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_ELEMENTS_TYPE},
    {"networkManagementRemoveNodeCallElements",
     DataElements::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_ELEMENTS_TYPE},
    {"networkManagementReportCandidateDataElements",
     DataElements::Type::
         NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_ELEMENTS_TYPE},
    {"networkManagementScanNetworkCallElements",
     DataElements::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_ELEMENTS_TYPE},
    {"nodeManagementBindingDataElements",
     DataElements::Type::NODE_MANAGEMENT_BINDING_DATA_ELEMENTS_TYPE},
    {"nodeManagementBindingDeleteCallElements",
     DataElements::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_ELEMENTS_TYPE},
    {"nodeManagementBindingRequestCallElements",
     DataElements::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_ELEMENTS_TYPE},
    {"nodeManagementDestinationDataElements",
     DataElements::Type::NODE_MANAGEMENT_DESTINATION_DATA_ELEMENTS_TYPE},
    {"nodeManagementDetailedDiscoveryDataElements",
     DataElements::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_ELEMENTS_TYPE},
    {"nodeManagementSubscriptionDataElements",
     DataElements::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_ELEMENTS_TYPE},
    {"nodeManagementSubscriptionDeleteCallElements",
     DataElements::Type::
         NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_ELEMENTS_TYPE},
    {"nodeManagementSubscriptionRequestCallElements",
     DataElements::Type::
         NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_ELEMENTS_TYPE},
    {"nodeManagementUseCaseDataElements",
     DataElements::Type::NODE_MANAGEMENT_USE_CASE_DATA_ELEMENTS_TYPE},
    {"operatingConstraintsDurationDataElements",
     DataElements::Type::OPERATING_CONSTRAINTS_DURATION_DATA_ELEMENTS_TYPE},
    {"operatingConstraintsInterruptDataElements",
     DataElements::Type::OPERATING_CONSTRAINTS_INTERRUPT_DATA_ELEMENTS_TYPE},
    {"operatingConstraintsPowerDescriptionDataElements",
     DataElements::Type::
         OPERATING_CONSTRAINTS_POWER_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"operatingConstraintsPowerLevelDataElements",
     DataElements::Type::OPERATING_CONSTRAINTS_POWER_LEVEL_DATA_ELEMENTS_TYPE},
    {"operatingConstraintsPowerRangeDataElements",
     DataElements::Type::OPERATING_CONSTRAINTS_POWER_RANGE_DATA_ELEMENTS_TYPE},
    {"operatingConstraintsResumeImplicationDataElements",
     DataElements::Type::
         OPERATING_CONSTRAINTS_RESUME_IMPLICATION_DATA_ELEMENTS_TYPE},
    {"powerSequenceAlternativesRelationDataElements",
     DataElements::Type::
         POWER_SEQUENCE_ALTERNATIVES_RELATION_DATA_ELEMENTS_TYPE},
    {"powerSequenceDescriptionDataElements",
     DataElements::Type::POWER_SEQUENCE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"powerSequenceNodeScheduleInformationDataElements",
     DataElements::Type::
         POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_ELEMENTS_TYPE},
    {"powerSequencePriceCalculationRequestCallElements",
     DataElements::Type::
         POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE},
    {"powerSequencePriceDataElements",
     DataElements::Type::POWER_SEQUENCE_PRICE_DATA_ELEMENTS_TYPE},
    {"powerSequenceScheduleConfigurationRequestCallElements",
     DataElements::Type::
         POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE},
    {"powerSequenceScheduleConstraintsDataElements",
     DataElements::Type::
         POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"powerSequenceScheduleDataElements",
     DataElements::Type::POWER_SEQUENCE_SCHEDULE_DATA_ELEMENTS_TYPE},
    {"powerSequenceSchedulePreferenceDataElements",
     DataElements::Type::POWER_SEQUENCE_SCHEDULE_PREFERENCE_DATA_ELEMENTS_TYPE},
    {"powerSequenceStateDataElements",
     DataElements::Type::POWER_SEQUENCE_STATE_DATA_ELEMENTS_TYPE},
    {"powerTimeSlotScheduleConstraintsDataElements",
     DataElements::Type::
         POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"powerTimeSlotScheduleDataElements",
     DataElements::Type::POWER_TIME_SLOT_SCHEDULE_DATA_ELEMENTS_TYPE},
    {"powerTimeSlotValueDataElements",
     DataElements::Type::POWER_TIME_SLOT_VALUE_DATA_ELEMENTS_TYPE},
    {"sensingDataElements", DataElements::Type::SENSING_DATA_ELEMENTS_TYPE},
    {"sensingDescriptionDataElements",
     DataElements::Type::SENSING_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"setpointConstraintsDataElements",
     DataElements::Type::SETPOINT_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"setpointDataElements", DataElements::Type::SETPOINT_DATA_ELEMENTS_TYPE},
    {"setpointDescriptionDataElements",
     DataElements::Type::SETPOINT_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"smartEnergyManagementPsConfigurationRequestCallElements",
     DataElements::Type::
         SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE},
    {"smartEnergyManagementPsDataElements",
     DataElements::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_ELEMENTS_TYPE},
    {"smartEnergyManagementPsPriceCalculationRequestCallElements",
     DataElements::Type::
         SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE},
    {"smartEnergyManagementPsPriceDataElements",
     DataElements::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_ELEMENTS_TYPE},
    {"specificationVersionDataElements",
     DataElements::Type::SPECIFICATION_VERSION_DATA_ELEMENTS_TYPE},
    {"subscriptionManagementDeleteCallElements",
     DataElements::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE},
    {"subscriptionManagementEntryDataElements",
     DataElements::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE},
    {"subscriptionManagementRequestCallElements",
     DataElements::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE},
    {"supplyConditionDataElements",
     DataElements::Type::SUPPLY_CONDITION_DATA_ELEMENTS_TYPE},
    {"supplyConditionDescriptionDataElements",
     DataElements::Type::SUPPLY_CONDITION_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"supplyConditionThresholdRelationDataElements",
     DataElements::Type::
         SUPPLY_CONDITION_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE},
    {"tariffBoundaryRelationDataElements",
     DataElements::Type::TARIFF_BOUNDARY_RELATION_DATA_ELEMENTS_TYPE},
    {"tariffDataElements", DataElements::Type::TARIFF_DATA_ELEMENTS_TYPE},
    {"tariffDescriptionDataElements",
     DataElements::Type::TARIFF_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"tariffOverallConstraintsDataElements",
     DataElements::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"tariffTierRelationDataElements",
     DataElements::Type::TARIFF_TIER_RELATION_DATA_ELEMENTS_TYPE},
    {"taskManagementJobDataElements",
     DataElements::Type::TASK_MANAGEMENT_JOB_DATA_ELEMENTS_TYPE},
    {"taskManagementJobDescriptionDataElements",
     DataElements::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"taskManagementJobRelationDataElements",
     DataElements::Type::TASK_MANAGEMENT_JOB_RELATION_DATA_ELEMENTS_TYPE},
    {"taskManagementOverviewDataElements",
     DataElements::Type::TASK_MANAGEMENT_OVERVIEW_DATA_ELEMENTS_TYPE},
    {"thresholdConstraintsDataElements",
     DataElements::Type::THRESHOLD_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"thresholdDataElements", DataElements::Type::THRESHOLD_DATA_ELEMENTS_TYPE},
    {"thresholdDescriptionDataElements",
     DataElements::Type::THRESHOLD_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"tierBoundaryDataElements",
     DataElements::Type::TIER_BOUNDARY_DATA_ELEMENTS_TYPE},
    {"tierBoundaryDescriptionDataElements",
     DataElements::Type::TIER_BOUNDARY_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"tierDataElements", DataElements::Type::TIER_DATA_ELEMENTS_TYPE},
    {"tierDescriptionDataElements",
     DataElements::Type::TIER_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"tierIncentiveRelationDataElements",
     DataElements::Type::TIER_INCENTIVE_RELATION_DATA_ELEMENTS_TYPE},
    {"timeDistributorDataElements",
     DataElements::Type::TIME_DISTRIBUTOR_DATA_ELEMENTS_TYPE},
    {"timeDistributorEnquiryCallElements",
     DataElements::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_ELEMENTS_TYPE},
    {"timeInformationDataElements",
     DataElements::Type::TIME_INFORMATION_DATA_ELEMENTS_TYPE},
    {"timePrecisionDataElements",
     DataElements::Type::TIME_PRECISION_DATA_ELEMENTS_TYPE},
    {"timeSeriesConstraintsDataElements",
     DataElements::Type::TIME_SERIES_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"timeSeriesDataElements",
     DataElements::Type::TIME_SERIES_DATA_ELEMENTS_TYPE},
    {"timeSeriesDescriptionDataElements",
     DataElements::Type::TIME_SERIES_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"timeTableConstraintsDataElements",
     DataElements::Type::TIME_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE},
    {"timeTableDataElements",
     DataElements::Type::TIME_TABLE_DATA_ELEMENTS_TYPE},
    {"timeTableDescriptionDataElements",
     DataElements::Type::TIME_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE},
    {"useCaseInformationDataElements",
     DataElements::Type::USE_CASE_INFORMATION_DATA_ELEMENTS_TYPE}};

std::string DataElements::getStringFromType(DataElements::Type type) {
  switch (type) {
  case DataElements::Type::ACTUATOR_LEVEL_DATA_ELEMENTS_TYPE: {
    return "actuatorLevelDataElements";
  }
  case DataElements::Type::ACTUATOR_LEVEL_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "actuatorLevelDescriptionDataElements";
  }
  case DataElements::Type::ACTUATOR_SWITCH_DATA_ELEMENTS_TYPE: {
    return "actuatorSwitchDataElements";
  }
  case DataElements::Type::ACTUATOR_SWITCH_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "actuatorSwitchDescriptionDataElements";
  }
  case DataElements::Type::ALARM_DATA_ELEMENTS_TYPE: {
    return "alarmDataElements";
  }
  case DataElements::Type::BILL_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "billConstraintsDataElements";
  }
  case DataElements::Type::BILL_DATA_ELEMENTS_TYPE: {
    return "billDataElements";
  }
  case DataElements::Type::BILL_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "billDescriptionDataElements";
  }
  case DataElements::Type::BINDING_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE: {
    return "bindingManagementDeleteCallElements";
  }
  case DataElements::Type::BINDING_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE: {
    return "bindingManagementEntryDataElements";
  }
  case DataElements::Type::BINDING_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE: {
    return "bindingManagementRequestCallElements";
  }
  case DataElements::Type::COMMODITY_DATA_ELEMENTS_TYPE: {
    return "commodityDataElements";
  }
  case DataElements::Type::DATA_TUNNELING_CALL_ELEMENTS_TYPE: {
    return "dataTunnelingCallElements";
  }
  case DataElements::Type::
      DEVICE_CLASSIFICATION_MANUFACTURER_DATA_ELEMENTS_TYPE: {
    return "deviceClassificationManufacturerDataElements";
  }
  case DataElements::Type::DEVICE_CLASSIFICATION_USER_DATA_ELEMENTS_TYPE: {
    return "deviceClassificationUserDataElements";
  }
  case DataElements::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "deviceConfigurationKeyValueConstraintsDataElements";
  }
  case DataElements::Type::DEVICE_CONFIGURATION_KEY_VALUE_DATA_ELEMENTS_TYPE: {
    return "deviceConfigurationKeyValueDataElements";
  }
  case DataElements::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "deviceConfigurationKeyValueDescriptionDataElements";
  }
  case DataElements::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_ELEMENTS_TYPE: {
    return "deviceDiagnosisHeartbeatDataElements";
  }
  case DataElements::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_ELEMENTS_TYPE: {
    return "deviceDiagnosisServiceDataElements";
  }
  case DataElements::Type::DEVICE_DIAGNOSIS_STATE_DATA_ELEMENTS_TYPE: {
    return "deviceDiagnosisStateDataElements";
  }
  case DataElements::Type::DIRECT_CONTROL_ACTIVITY_DATA_ELEMENTS_TYPE: {
    return "directControlActivityDataElements";
  }
  case DataElements::Type::DIRECT_CONTROL_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "directControlDescriptionDataElements";
  }
  case DataElements::Type::
      ELECTRICAL_CONNECTION_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "electricalConnectionDescriptionDataElements";
  }
  case DataElements::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "electricalConnectionParameterDescriptionDataElements";
  }
  case DataElements::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_DATA_ELEMENTS_TYPE: {
    return "electricalConnectionPermittedValueSetDataElements";
  }
  case DataElements::Type::ELECTRICAL_CONNECTION_STATE_DATA_ELEMENTS_TYPE: {
    return "electricalConnectionStateDataElements";
  }
  case DataElements::Type::HVAC_OPERATION_MODE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "hvacOperationModeDescriptionDataElements";
  }
  case DataElements::Type::HVAC_OVERRUN_DATA_ELEMENTS_TYPE: {
    return "hvacOverrunDataElements";
  }
  case DataElements::Type::HVAC_OVERRUN_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "hvacOverrunDescriptionDataElements";
  }
  case DataElements::Type::HVAC_SYSTEM_FUNCTION_DATA_ELEMENTS_TYPE: {
    return "hvacSystemFunctionDataElements";
  }
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "hvacSystemFunctionDescriptionDataElements";
  }
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_DATA_ELEMENTS_TYPE: {
    return "hvacSystemFunctionOperationModeRelationDataElements";
  }
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_DATA_ELEMENTS_TYPE: {
    return "hvacSystemFunctionPowerSequenceRelationDataElements";
  }
  case DataElements::Type::
      HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_DATA_ELEMENTS_TYPE: {
    return "hvacSystemFunctionSetpointRelationDataElements";
  }
  case DataElements::Type::IDENTIFICATION_DATA_ELEMENTS_TYPE: {
    return "identificationDataElements";
  }
  case DataElements::Type::INCENTIVE_DATA_ELEMENTS_TYPE: {
    return "incentiveDataElements";
  }
  case DataElements::Type::INCENTIVE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "incentiveDescriptionDataElements";
  }
  case DataElements::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "incentiveTableConstraintsDataElements";
  }
  case DataElements::Type::INCENTIVE_TABLE_DATA_ELEMENTS_TYPE: {
    return "incentiveTableDataElements";
  }
  case DataElements::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "incentiveTableDescriptionDataElements";
  }
  case DataElements::Type::LOAD_CONTROL_EVENT_DATA_ELEMENTS_TYPE: {
    return "loadControlEventDataElements";
  }
  case DataElements::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "loadControlLimitConstraintsDataElements";
  }
  case DataElements::Type::LOAD_CONTROL_LIMIT_DATA_ELEMENTS_TYPE: {
    return "loadControlLimitDataElements";
  }
  case DataElements::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "loadControlLimitDescriptionDataElements";
  }
  case DataElements::Type::LOAD_CONTROL_NODE_DATA_ELEMENTS_TYPE: {
    return "loadControlNodeDataElements";
  }
  case DataElements::Type::LOAD_CONTROL_STATE_DATA_ELEMENTS_TYPE: {
    return "loadControlStateDataElements";
  }
  case DataElements::Type::MEASUREMENT_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "measurementConstraintsDataElements";
  }
  case DataElements::Type::MEASUREMENT_DATA_ELEMENTS_TYPE: {
    return "measurementDataElements";
  }
  case DataElements::Type::MEASUREMENT_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "measurementDescriptionDataElements";
  }
  case DataElements::Type::MEASUREMENT_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE: {
    return "measurementThresholdRelationDataElements";
  }
  case DataElements::Type::MESSAGING_DATA_ELEMENTS_TYPE: {
    return "messagingDataElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_ABORT_CALL_ELEMENTS_TYPE: {
    return "networkManagementAbortCallElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_ELEMENTS_TYPE: {
    return "networkManagementAddNodeCallElements";
  }
  case DataElements::Type::
      NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "networkManagementDeviceDescriptionDataElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_ELEMENTS_TYPE: {
    return "networkManagementDiscoverCallElements";
  }
  case DataElements::Type::
      NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "networkManagementEntityDescriptionDataElements";
  }
  case DataElements::Type::
      NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "networkManagementFeatureDescriptionDataElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_ELEMENTS_TYPE: {
    return "networkManagementJoiningModeDataElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_ELEMENTS_TYPE: {
    return "networkManagementModifyNodeCallElements";
  }
  case DataElements::Type::
      NETWORK_MANAGEMENT_PROCESS_STATE_DATA_ELEMENTS_TYPE: {
    return "networkManagementProcessStateDataElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_ELEMENTS_TYPE: {
    return "networkManagementRemoveNodeCallElements";
  }
  case DataElements::Type::
      NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_ELEMENTS_TYPE: {
    return "networkManagementReportCandidateDataElements";
  }
  case DataElements::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_ELEMENTS_TYPE: {
    return "networkManagementScanNetworkCallElements";
  }
  case DataElements::Type::NODE_MANAGEMENT_BINDING_DATA_ELEMENTS_TYPE: {
    return "nodeManagementBindingDataElements";
  }
  case DataElements::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_ELEMENTS_TYPE: {
    return "nodeManagementBindingDeleteCallElements";
  }
  case DataElements::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_ELEMENTS_TYPE: {
    return "nodeManagementBindingRequestCallElements";
  }
  case DataElements::Type::NODE_MANAGEMENT_DESTINATION_DATA_ELEMENTS_TYPE: {
    return "nodeManagementDestinationDataElements";
  }
  case DataElements::Type::
      NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_ELEMENTS_TYPE: {
    return "nodeManagementDetailedDiscoveryDataElements";
  }
  case DataElements::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_ELEMENTS_TYPE: {
    return "nodeManagementSubscriptionDataElements";
  }
  case DataElements::Type::
      NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_ELEMENTS_TYPE: {
    return "nodeManagementSubscriptionDeleteCallElements";
  }
  case DataElements::Type::
      NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_ELEMENTS_TYPE: {
    return "nodeManagementSubscriptionRequestCallElements";
  }
  case DataElements::Type::NODE_MANAGEMENT_USE_CASE_DATA_ELEMENTS_TYPE: {
    return "nodeManagementUseCaseDataElements";
  }
  case DataElements::Type::OPERATING_CONSTRAINTS_DURATION_DATA_ELEMENTS_TYPE: {
    return "operatingConstraintsDurationDataElements";
  }
  case DataElements::Type::OPERATING_CONSTRAINTS_INTERRUPT_DATA_ELEMENTS_TYPE: {
    return "operatingConstraintsInterruptDataElements";
  }
  case DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "operatingConstraintsPowerDescriptionDataElements";
  }
  case DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_LEVEL_DATA_ELEMENTS_TYPE: {
    return "operatingConstraintsPowerLevelDataElements";
  }
  case DataElements::Type::
      OPERATING_CONSTRAINTS_POWER_RANGE_DATA_ELEMENTS_TYPE: {
    return "operatingConstraintsPowerRangeDataElements";
  }
  case DataElements::Type::
      OPERATING_CONSTRAINTS_RESUME_IMPLICATION_DATA_ELEMENTS_TYPE: {
    return "operatingConstraintsResumeImplicationDataElements";
  }
  case DataElements::Type::
      POWER_SEQUENCE_ALTERNATIVES_RELATION_DATA_ELEMENTS_TYPE: {
    return "powerSequenceAlternativesRelationDataElements";
  }
  case DataElements::Type::POWER_SEQUENCE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "powerSequenceDescriptionDataElements";
  }
  case DataElements::Type::
      POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_ELEMENTS_TYPE: {
    return "powerSequenceNodeScheduleInformationDataElements";
  }
  case DataElements::Type::
      POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE: {
    return "powerSequencePriceCalculationRequestCallElements";
  }
  case DataElements::Type::POWER_SEQUENCE_PRICE_DATA_ELEMENTS_TYPE: {
    return "powerSequencePriceDataElements";
  }
  case DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE: {
    return "powerSequenceScheduleConfigurationRequestCallElements";
  }
  case DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "powerSequenceScheduleConstraintsDataElements";
  }
  case DataElements::Type::POWER_SEQUENCE_SCHEDULE_DATA_ELEMENTS_TYPE: {
    return "powerSequenceScheduleDataElements";
  }
  case DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_PREFERENCE_DATA_ELEMENTS_TYPE: {
    return "powerSequenceSchedulePreferenceDataElements";
  }
  case DataElements::Type::POWER_SEQUENCE_STATE_DATA_ELEMENTS_TYPE: {
    return "powerSequenceStateDataElements";
  }
  case DataElements::Type::
      POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "powerTimeSlotScheduleConstraintsDataElements";
  }
  case DataElements::Type::POWER_TIME_SLOT_SCHEDULE_DATA_ELEMENTS_TYPE: {
    return "powerTimeSlotScheduleDataElements";
  }
  case DataElements::Type::POWER_TIME_SLOT_VALUE_DATA_ELEMENTS_TYPE: {
    return "powerTimeSlotValueDataElements";
  }
  case DataElements::Type::SENSING_DATA_ELEMENTS_TYPE: {
    return "sensingDataElements";
  }
  case DataElements::Type::SENSING_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "sensingDescriptionDataElements";
  }
  case DataElements::Type::SETPOINT_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "setpointConstraintsDataElements";
  }
  case DataElements::Type::SETPOINT_DATA_ELEMENTS_TYPE: {
    return "setpointDataElements";
  }
  case DataElements::Type::SETPOINT_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "setpointDescriptionDataElements";
  }
  case DataElements::Type::
      SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_ELEMENTS_TYPE: {
    return "smartEnergyManagementPsConfigurationRequestCallElements";
  }
  case DataElements::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_ELEMENTS_TYPE: {
    return "smartEnergyManagementPsDataElements";
  }
  case DataElements::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_ELEMENTS_TYPE: {
    return "smartEnergyManagementPsPriceCalculationRequestCallElements";
  }
  case DataElements::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_ELEMENTS_TYPE: {
    return "smartEnergyManagementPsPriceDataElements";
  }
  case DataElements::Type::SPECIFICATION_VERSION_DATA_ELEMENTS_TYPE: {
    return "specificationVersionDataElements";
  }
  case DataElements::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE: {
    return "subscriptionManagementDeleteCallElements";
  }
  case DataElements::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE: {
    return "subscriptionManagementEntryDataElements";
  }
  case DataElements::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE: {
    return "subscriptionManagementRequestCallElements";
  }
  case DataElements::Type::SUPPLY_CONDITION_DATA_ELEMENTS_TYPE: {
    return "supplyConditionDataElements";
  }
  case DataElements::Type::SUPPLY_CONDITION_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "supplyConditionDescriptionDataElements";
  }
  case DataElements::Type::
      SUPPLY_CONDITION_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE: {
    return "supplyConditionThresholdRelationDataElements";
  }
  case DataElements::Type::TARIFF_BOUNDARY_RELATION_DATA_ELEMENTS_TYPE: {
    return "tariffBoundaryRelationDataElements";
  }
  case DataElements::Type::TARIFF_DATA_ELEMENTS_TYPE: {
    return "tariffDataElements";
  }
  case DataElements::Type::TARIFF_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "tariffDescriptionDataElements";
  }
  case DataElements::Type::TARIFF_OVERALL_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "tariffOverallConstraintsDataElements";
  }
  case DataElements::Type::TARIFF_TIER_RELATION_DATA_ELEMENTS_TYPE: {
    return "tariffTierRelationDataElements";
  }
  case DataElements::Type::TASK_MANAGEMENT_JOB_DATA_ELEMENTS_TYPE: {
    return "taskManagementJobDataElements";
  }
  case DataElements::Type::TASK_MANAGEMENT_JOB_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "taskManagementJobDescriptionDataElements";
  }
  case DataElements::Type::TASK_MANAGEMENT_JOB_RELATION_DATA_ELEMENTS_TYPE: {
    return "taskManagementJobRelationDataElements";
  }
  case DataElements::Type::TASK_MANAGEMENT_OVERVIEW_DATA_ELEMENTS_TYPE: {
    return "taskManagementOverviewDataElements";
  }
  case DataElements::Type::THRESHOLD_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "thresholdConstraintsDataElements";
  }
  case DataElements::Type::THRESHOLD_DATA_ELEMENTS_TYPE: {
    return "thresholdDataElements";
  }
  case DataElements::Type::THRESHOLD_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "thresholdDescriptionDataElements";
  }
  case DataElements::Type::TIER_BOUNDARY_DATA_ELEMENTS_TYPE: {
    return "tierBoundaryDataElements";
  }
  case DataElements::Type::TIER_BOUNDARY_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "tierBoundaryDescriptionDataElements";
  }
  case DataElements::Type::TIER_DATA_ELEMENTS_TYPE: {
    return "tierDataElements";
  }
  case DataElements::Type::TIER_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "tierDescriptionDataElements";
  }
  case DataElements::Type::TIER_INCENTIVE_RELATION_DATA_ELEMENTS_TYPE: {
    return "tierIncentiveRelationDataElements";
  }
  case DataElements::Type::TIME_DISTRIBUTOR_DATA_ELEMENTS_TYPE: {
    return "timeDistributorDataElements";
  }
  case DataElements::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_ELEMENTS_TYPE: {
    return "timeDistributorEnquiryCallElements";
  }
  case DataElements::Type::TIME_INFORMATION_DATA_ELEMENTS_TYPE: {
    return "timeInformationDataElements";
  }
  case DataElements::Type::TIME_PRECISION_DATA_ELEMENTS_TYPE: {
    return "timePrecisionDataElements";
  }
  case DataElements::Type::TIME_SERIES_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "timeSeriesConstraintsDataElements";
  }
  case DataElements::Type::TIME_SERIES_DATA_ELEMENTS_TYPE: {
    return "timeSeriesDataElements";
  }
  case DataElements::Type::TIME_SERIES_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "timeSeriesDescriptionDataElements";
  }
  case DataElements::Type::TIME_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE: {
    return "timeTableConstraintsDataElements";
  }
  case DataElements::Type::TIME_TABLE_DATA_ELEMENTS_TYPE: {
    return "timeTableDataElements";
  }
  case DataElements::Type::TIME_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE: {
    return "timeTableDescriptionDataElements";
  }
  case DataElements::Type::USE_CASE_INFORMATION_DATA_ELEMENTS_TYPE: {
    return "useCaseInformationDataElements";
  }
  default: { return ""; }
  }
}

DataElements::Type DataElements::getTypeFromString(const std::string &type) {
  auto it = STRING_TO_TYPE.find(type);
  if (it != STRING_TO_TYPE.end()) {
    return it->second;
  } else {
    return DataElements::Type::UNDEFINED;
  }
}

} // namespace keo_datagram