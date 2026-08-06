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

#include <keo_datagram/core/DataSelectors.h>

namespace keo_datagram {

std::map<std::string, DataSelectors::Type> DataSelectors::STRING_TO_TYPE = {
    {"alarmListDataSelectors",
     DataSelectors::Type::ALARM_LIST_DATA_SELECTORS_TYPE},
    {"billConstraintsListDataSelectors",
     DataSelectors::Type::BILL_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"billDescriptionListDataSelectors",
     DataSelectors::Type::BILL_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"billListDataSelectors",
     DataSelectors::Type::BILL_LIST_DATA_SELECTORS_TYPE},
    {"bindingManagementEntryListDataSelectors",
     DataSelectors::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE},
    {"commodityListDataSelectors",
     DataSelectors::Type::COMMODITY_LIST_DATA_SELECTORS_TYPE},
    {"deviceConfigurationKeyValueConstraintsListDataSelectors",
     DataSelectors::Type::
         DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"deviceConfigurationKeyValueDescriptionListDataSelectors",
     DataSelectors::Type::
         DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"deviceConfigurationKeyValueListDataSelectors",
     DataSelectors::Type::
         DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_SELECTORS_TYPE},
    {"directControlActivityListDataSelectors",
     DataSelectors::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_SELECTORS_TYPE},
    {"electricalConnectionDescriptionListDataSelectors",
     DataSelectors::Type::
         ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"electricalConnectionParameterDescriptionListDataSelectors",
     DataSelectors::Type::
         ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"electricalConnectionPermittedValueSetListDataSelectors",
     DataSelectors::Type::
         ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_SELECTORS_TYPE},
    {"electricalConnectionStateListDataSelectors",
     DataSelectors::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_SELECTORS_TYPE},
    {"hvacOperationModeDescriptionListDataSelectors",
     DataSelectors::Type::
         HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"hvacOverrunDescriptionListDataSelectors",
     DataSelectors::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"hvacOverrunListDataSelectors",
     DataSelectors::Type::HVAC_OVERRUN_LIST_DATA_SELECTORS_TYPE},
    {"hvacSystemFunctionDescriptionListDataSelectors",
     DataSelectors::Type::
         HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"hvacSystemFunctionListDataSelectors",
     DataSelectors::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_SELECTORS_TYPE},
    {"hvacSystemFunctionOperationModeRelationListDataSelectors",
     DataSelectors::Type::
         HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"hvacSystemFunctionPowerSequenceRelationListDataSelectors",
     DataSelectors::Type::
         HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"hvacSystemFunctionSetpointRelationListDataSelectors",
     DataSelectors::Type::
         HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"identificationListDataSelectors",
     DataSelectors::Type::IDENTIFICATION_LIST_DATA_SELECTORS_TYPE},
    {"incentiveDescriptionListDataSelectors",
     DataSelectors::Type::INCENTIVE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"incentiveListDataSelectors",
     DataSelectors::Type::INCENTIVE_LIST_DATA_SELECTORS_TYPE},
    {"incentiveTableConstraintsDataSelectors",
     DataSelectors::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_SELECTORS_TYPE},
    {"incentiveTableDataSelectors",
     DataSelectors::Type::INCENTIVE_TABLE_DATA_SELECTORS_TYPE},
    {"incentiveTableDescriptionDataSelectors",
     DataSelectors::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_SELECTORS_TYPE},
    {"loadControlEventListDataSelectors",
     DataSelectors::Type::LOAD_CONTROL_EVENT_LIST_DATA_SELECTORS_TYPE},
    {"loadControlLimitConstraintsListDataSelectors",
     DataSelectors::Type::
         LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"loadControlLimitDescriptionListDataSelectors",
     DataSelectors::Type::
         LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"loadControlLimitListDataSelectors",
     DataSelectors::Type::LOAD_CONTROL_LIMIT_LIST_DATA_SELECTORS_TYPE},
    {"loadControlStateListDataSelectors",
     DataSelectors::Type::LOAD_CONTROL_STATE_LIST_DATA_SELECTORS_TYPE},
    {"measurementConstraintsListDataSelectors",
     DataSelectors::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"measurementDescriptionListDataSelectors",
     DataSelectors::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"measurementListDataSelectors",
     DataSelectors::Type::MEASUREMENT_LIST_DATA_SELECTORS_TYPE},
    {"measurementThresholdRelationListDataSelectors",
     DataSelectors::Type::
         MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"messagingListDataSelectors",
     DataSelectors::Type::MESSAGING_LIST_DATA_SELECTORS_TYPE},
    {"networkManagementDeviceDescriptionListDataSelectors",
     DataSelectors::Type::
         NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"networkManagementEntityDescriptionListDataSelectors",
     DataSelectors::Type::
         NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"networkManagementFeatureDescriptionListDataSelectors",
     DataSelectors::Type::
         NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"nodeManagementBindingDataSelectors",
     DataSelectors::Type::NODE_MANAGEMENT_BINDING_DATA_SELECTORS_TYPE},
    {"nodeManagementDestinationListDataSelectors",
     DataSelectors::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_SELECTORS_TYPE},
    {"nodeManagementDetailedDiscoveryDataSelectors",
     DataSelectors::Type::
         NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_SELECTORS_TYPE},
    {"nodeManagementSubscriptionDataSelectors",
     DataSelectors::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_SELECTORS_TYPE},
    {"nodeManagementUseCaseDataSelectors",
     DataSelectors::Type::NODE_MANAGEMENT_USE_CASE_DATA_SELECTORS_TYPE},
    {"operatingConstraintsDurationListDataSelectors",
     DataSelectors::Type::
         OPERATING_CONSTRAINTS_DURATION_LIST_DATA_SELECTORS_TYPE},
    {"operatingConstraintsInterruptListDataSelectors",
     DataSelectors::Type::
         OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_SELECTORS_TYPE},
    {"operatingConstraintsPowerDescriptionListDataSelectors",
     DataSelectors::Type::
         OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"operatingConstraintsPowerLevelListDataSelectors",
     DataSelectors::Type::
         OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_SELECTORS_TYPE},
    {"operatingConstraintsPowerRangeListDataSelectors",
     DataSelectors::Type::
         OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_SELECTORS_TYPE},
    {"operatingConstraintsResumeImplicationListDataSelectors",
     DataSelectors::Type::
         OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_SELECTORS_TYPE},
    {"powerSequenceAlternativesRelationListDataSelectors",
     DataSelectors::Type::
         POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"powerSequenceDescriptionListDataSelectors",
     DataSelectors::Type::POWER_SEQUENCE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"powerSequencePriceListDataSelectors",
     DataSelectors::Type::POWER_SEQUENCE_PRICE_LIST_DATA_SELECTORS_TYPE},
    {"powerSequenceScheduleConstraintsListDataSelectors",
     DataSelectors::Type::
         POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"powerSequenceScheduleListDataSelectors",
     DataSelectors::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_SELECTORS_TYPE},
    {"powerSequenceSchedulePreferenceListDataSelectors",
     DataSelectors::Type::
         POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_SELECTORS_TYPE},
    {"powerSequenceStateListDataSelectors",
     DataSelectors::Type::POWER_SEQUENCE_STATE_LIST_DATA_SELECTORS_TYPE},
    {"powerTimeSlotScheduleConstraintsListDataSelectors",
     DataSelectors::Type::
         POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"powerTimeSlotScheduleListDataSelectors",
     DataSelectors::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_SELECTORS_TYPE},
    {"powerTimeSlotValueListDataSelectors",
     DataSelectors::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_SELECTORS_TYPE},
    {"sensingListDataSelectors",
     DataSelectors::Type::SENSING_LIST_DATA_SELECTORS_TYPE},
    {"setpointConstraintsListDataSelectors",
     DataSelectors::Type::SETPOINT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"setpointDescriptionListDataSelectors",
     DataSelectors::Type::SETPOINT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"setpointListDataSelectors",
     DataSelectors::Type::SETPOINT_LIST_DATA_SELECTORS_TYPE},
    {"smartEnergyManagementPsDataSelectors",
     DataSelectors::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_SELECTORS_TYPE},
    {"smartEnergyManagementPsPriceDataSelectors",
     DataSelectors::Type::SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_SELECTORS_TYPE},
    {"specificationVersionListDataSelectors",
     DataSelectors::Type::SPECIFICATION_VERSION_LIST_DATA_SELECTORS_TYPE},
    {"subscriptionManagementEntryListDataSelectors",
     DataSelectors::Type::
         SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE},
    {"supplyConditionDescriptionListDataSelectors",
     DataSelectors::Type::
         SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"supplyConditionListDataSelectors",
     DataSelectors::Type::SUPPLY_CONDITION_LIST_DATA_SELECTORS_TYPE},
    {"supplyConditionThresholdRelationListDataSelectors",
     DataSelectors::Type::
         SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"tariffBoundaryRelationListDataSelectors",
     DataSelectors::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"tariffDescriptionListDataSelectors",
     DataSelectors::Type::TARIFF_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"tariffListDataSelectors",
     DataSelectors::Type::TARIFF_LIST_DATA_SELECTORS_TYPE},
    {"tariffTierRelationListDataSelectors",
     DataSelectors::Type::TARIFF_TIER_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"taskManagementJobDescriptionListDataSelectors",
     DataSelectors::Type::
         TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"taskManagementJobListDataSelectors",
     DataSelectors::Type::TASK_MANAGEMENT_JOB_LIST_DATA_SELECTORS_TYPE},
    {"taskManagementJobRelationListDataSelectors",
     DataSelectors::Type::
         TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"thresholdConstraintsListDataSelectors",
     DataSelectors::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"thresholdDescriptionListDataSelectors",
     DataSelectors::Type::THRESHOLD_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"thresholdListDataSelectors",
     DataSelectors::Type::THRESHOLD_LIST_DATA_SELECTORS_TYPE},
    {"tierBoundaryDescriptionListDataSelectors",
     DataSelectors::Type::TIER_BOUNDARY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"tierBoundaryListDataSelectors",
     DataSelectors::Type::TIER_BOUNDARY_LIST_DATA_SELECTORS_TYPE},
    {"tierDescriptionListDataSelectors",
     DataSelectors::Type::TIER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"tierIncentiveRelationListDataSelectors",
     DataSelectors::Type::TIER_INCENTIVE_RELATION_LIST_DATA_SELECTORS_TYPE},
    {"tierListDataSelectors",
     DataSelectors::Type::TIER_LIST_DATA_SELECTORS_TYPE},
    {"timeSeriesConstraintsListDataSelectors",
     DataSelectors::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"timeSeriesDescriptionListDataSelectors",
     DataSelectors::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"timeSeriesListDataSelectors",
     DataSelectors::Type::TIME_SERIES_LIST_DATA_SELECTORS_TYPE},
    {"timeTableConstraintsListDataSelectors",
     DataSelectors::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE},
    {"timeTableDescriptionListDataSelectors",
     DataSelectors::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE},
    {"timeTableListDataSelectors",
     DataSelectors::Type::TIME_TABLE_LIST_DATA_SELECTORS_TYPE},
    {"useCaseInformationListDataSelectors",
     DataSelectors::Type::USE_CASE_INFORMATION_LIST_DATA_SELECTORS_TYPE}};

std::string DataSelectors::getStringFromType(DataSelectors::Type type) {
  switch (type) {
  case DataSelectors::Type::ALARM_LIST_DATA_SELECTORS_TYPE: {
    return "alarmListDataSelectors";
  }
  case DataSelectors::Type::BILL_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "billConstraintsListDataSelectors";
  }
  case DataSelectors::Type::BILL_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "billDescriptionListDataSelectors";
  }
  case DataSelectors::Type::BILL_LIST_DATA_SELECTORS_TYPE: {
    return "billListDataSelectors";
  }
  case DataSelectors::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE: {
    return "bindingManagementEntryListDataSelectors";
  }
  case DataSelectors::Type::COMMODITY_LIST_DATA_SELECTORS_TYPE: {
    return "commodityListDataSelectors";
  }
  case DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "deviceConfigurationKeyValueConstraintsListDataSelectors";
  }
  case DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "deviceConfigurationKeyValueDescriptionListDataSelectors";
  }
  case DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_SELECTORS_TYPE: {
    return "deviceConfigurationKeyValueListDataSelectors";
  }
  case DataSelectors::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_SELECTORS_TYPE: {
    return "directControlActivityListDataSelectors";
  }
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "electricalConnectionDescriptionListDataSelectors";
  }
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "electricalConnectionParameterDescriptionListDataSelectors";
  }
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_SELECTORS_TYPE: {
    return "electricalConnectionPermittedValueSetListDataSelectors";
  }
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_STATE_LIST_DATA_SELECTORS_TYPE: {
    return "electricalConnectionStateListDataSelectors";
  }
  case DataSelectors::Type::
      HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacOperationModeDescriptionListDataSelectors";
  }
  case DataSelectors::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacOverrunDescriptionListDataSelectors";
  }
  case DataSelectors::Type::HVAC_OVERRUN_LIST_DATA_SELECTORS_TYPE: {
    return "hvacOverrunListDataSelectors";
  }
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacSystemFunctionDescriptionListDataSelectors";
  }
  case DataSelectors::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacSystemFunctionListDataSelectors";
  }
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacSystemFunctionOperationModeRelationListDataSelectors";
  }
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacSystemFunctionPowerSequenceRelationListDataSelectors";
  }
  case DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "hvacSystemFunctionSetpointRelationListDataSelectors";
  }
  case DataSelectors::Type::IDENTIFICATION_LIST_DATA_SELECTORS_TYPE: {
    return "identificationListDataSelectors";
  }
  case DataSelectors::Type::INCENTIVE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "incentiveDescriptionListDataSelectors";
  }
  case DataSelectors::Type::INCENTIVE_LIST_DATA_SELECTORS_TYPE: {
    return "incentiveListDataSelectors";
  }
  case DataSelectors::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_SELECTORS_TYPE: {
    return "incentiveTableConstraintsDataSelectors";
  }
  case DataSelectors::Type::INCENTIVE_TABLE_DATA_SELECTORS_TYPE: {
    return "incentiveTableDataSelectors";
  }
  case DataSelectors::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_SELECTORS_TYPE: {
    return "incentiveTableDescriptionDataSelectors";
  }
  case DataSelectors::Type::LOAD_CONTROL_EVENT_LIST_DATA_SELECTORS_TYPE: {
    return "loadControlEventListDataSelectors";
  }
  case DataSelectors::Type::
      LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "loadControlLimitConstraintsListDataSelectors";
  }
  case DataSelectors::Type::
      LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "loadControlLimitDescriptionListDataSelectors";
  }
  case DataSelectors::Type::LOAD_CONTROL_LIMIT_LIST_DATA_SELECTORS_TYPE: {
    return "loadControlLimitListDataSelectors";
  }
  case DataSelectors::Type::LOAD_CONTROL_STATE_LIST_DATA_SELECTORS_TYPE: {
    return "loadControlStateListDataSelectors";
  }
  case DataSelectors::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "measurementConstraintsListDataSelectors";
  }
  case DataSelectors::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "measurementDescriptionListDataSelectors";
  }
  case DataSelectors::Type::MEASUREMENT_LIST_DATA_SELECTORS_TYPE: {
    return "measurementListDataSelectors";
  }
  case DataSelectors::Type::
      MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "measurementThresholdRelationListDataSelectors";
  }
  case DataSelectors::Type::MESSAGING_LIST_DATA_SELECTORS_TYPE: {
    return "messagingListDataSelectors";
  }
  case DataSelectors::Type::
      NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "networkManagementDeviceDescriptionListDataSelectors";
  }
  case DataSelectors::Type::
      NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "networkManagementEntityDescriptionListDataSelectors";
  }
  case DataSelectors::Type::
      NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "networkManagementFeatureDescriptionListDataSelectors";
  }
  case DataSelectors::Type::NODE_MANAGEMENT_BINDING_DATA_SELECTORS_TYPE: {
    return "nodeManagementBindingDataSelectors";
  }
  case DataSelectors::Type::
      NODE_MANAGEMENT_DESTINATION_LIST_DATA_SELECTORS_TYPE: {
    return "nodeManagementDestinationListDataSelectors";
  }
  case DataSelectors::Type::
      NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_SELECTORS_TYPE: {
    return "nodeManagementDetailedDiscoveryDataSelectors";
  }
  case DataSelectors::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_SELECTORS_TYPE: {
    return "nodeManagementSubscriptionDataSelectors";
  }
  case DataSelectors::Type::NODE_MANAGEMENT_USE_CASE_DATA_SELECTORS_TYPE: {
    return "nodeManagementUseCaseDataSelectors";
  }
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_DURATION_LIST_DATA_SELECTORS_TYPE: {
    return "operatingConstraintsDurationListDataSelectors";
  }
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_SELECTORS_TYPE: {
    return "operatingConstraintsInterruptListDataSelectors";
  }
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "operatingConstraintsPowerDescriptionListDataSelectors";
  }
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_SELECTORS_TYPE: {
    return "operatingConstraintsPowerLevelListDataSelectors";
  }
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_SELECTORS_TYPE: {
    return "operatingConstraintsPowerRangeListDataSelectors";
  }
  case DataSelectors::Type::
      OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_SELECTORS_TYPE: {
    return "operatingConstraintsResumeImplicationListDataSelectors";
  }
  case DataSelectors::Type::
      POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequenceAlternativesRelationListDataSelectors";
  }
  case DataSelectors::Type::
      POWER_SEQUENCE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequenceDescriptionListDataSelectors";
  }
  case DataSelectors::Type::POWER_SEQUENCE_PRICE_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequencePriceListDataSelectors";
  }
  case DataSelectors::Type::
      POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequenceScheduleConstraintsListDataSelectors";
  }
  case DataSelectors::Type::POWER_SEQUENCE_SCHEDULE_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequenceScheduleListDataSelectors";
  }
  case DataSelectors::Type::
      POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequenceSchedulePreferenceListDataSelectors";
  }
  case DataSelectors::Type::POWER_SEQUENCE_STATE_LIST_DATA_SELECTORS_TYPE: {
    return "powerSequenceStateListDataSelectors";
  }
  case DataSelectors::Type::
      POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "powerTimeSlotScheduleConstraintsListDataSelectors";
  }
  case DataSelectors::Type::POWER_TIME_SLOT_SCHEDULE_LIST_DATA_SELECTORS_TYPE: {
    return "powerTimeSlotScheduleListDataSelectors";
  }
  case DataSelectors::Type::POWER_TIME_SLOT_VALUE_LIST_DATA_SELECTORS_TYPE: {
    return "powerTimeSlotValueListDataSelectors";
  }
  case DataSelectors::Type::SENSING_LIST_DATA_SELECTORS_TYPE: {
    return "sensingListDataSelectors";
  }
  case DataSelectors::Type::SETPOINT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "setpointConstraintsListDataSelectors";
  }
  case DataSelectors::Type::SETPOINT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "setpointDescriptionListDataSelectors";
  }
  case DataSelectors::Type::SETPOINT_LIST_DATA_SELECTORS_TYPE: {
    return "setpointListDataSelectors";
  }
  case DataSelectors::Type::SMART_ENERGY_MANAGEMENT_PS_DATA_SELECTORS_TYPE: {
    return "smartEnergyManagementPsDataSelectors";
  }
  case DataSelectors::Type::
      SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_SELECTORS_TYPE: {
    return "smartEnergyManagementPsPriceDataSelectors";
  }
  case DataSelectors::Type::SPECIFICATION_VERSION_LIST_DATA_SELECTORS_TYPE: {
    return "specificationVersionListDataSelectors";
  }
  case DataSelectors::Type::
      SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE: {
    return "subscriptionManagementEntryListDataSelectors";
  }
  case DataSelectors::Type::
      SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "supplyConditionDescriptionListDataSelectors";
  }
  case DataSelectors::Type::SUPPLY_CONDITION_LIST_DATA_SELECTORS_TYPE: {
    return "supplyConditionListDataSelectors";
  }
  case DataSelectors::Type::
      SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "supplyConditionThresholdRelationListDataSelectors";
  }
  case DataSelectors::Type::TARIFF_BOUNDARY_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "tariffBoundaryRelationListDataSelectors";
  }
  case DataSelectors::Type::TARIFF_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "tariffDescriptionListDataSelectors";
  }
  case DataSelectors::Type::TARIFF_LIST_DATA_SELECTORS_TYPE: {
    return "tariffListDataSelectors";
  }
  case DataSelectors::Type::TARIFF_TIER_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "tariffTierRelationListDataSelectors";
  }
  case DataSelectors::Type::
      TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "taskManagementJobDescriptionListDataSelectors";
  }
  case DataSelectors::Type::TASK_MANAGEMENT_JOB_LIST_DATA_SELECTORS_TYPE: {
    return "taskManagementJobListDataSelectors";
  }
  case DataSelectors::Type::
      TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "taskManagementJobRelationListDataSelectors";
  }
  case DataSelectors::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "thresholdConstraintsListDataSelectors";
  }
  case DataSelectors::Type::THRESHOLD_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "thresholdDescriptionListDataSelectors";
  }
  case DataSelectors::Type::THRESHOLD_LIST_DATA_SELECTORS_TYPE: {
    return "thresholdListDataSelectors";
  }
  case DataSelectors::Type::
      TIER_BOUNDARY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "tierBoundaryDescriptionListDataSelectors";
  }
  case DataSelectors::Type::TIER_BOUNDARY_LIST_DATA_SELECTORS_TYPE: {
    return "tierBoundaryListDataSelectors";
  }
  case DataSelectors::Type::TIER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "tierDescriptionListDataSelectors";
  }
  case DataSelectors::Type::TIER_INCENTIVE_RELATION_LIST_DATA_SELECTORS_TYPE: {
    return "tierIncentiveRelationListDataSelectors";
  }
  case DataSelectors::Type::TIER_LIST_DATA_SELECTORS_TYPE: {
    return "tierListDataSelectors";
  }
  case DataSelectors::Type::TIME_SERIES_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "timeSeriesConstraintsListDataSelectors";
  }
  case DataSelectors::Type::TIME_SERIES_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "timeSeriesDescriptionListDataSelectors";
  }
  case DataSelectors::Type::TIME_SERIES_LIST_DATA_SELECTORS_TYPE: {
    return "timeSeriesListDataSelectors";
  }
  case DataSelectors::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE: {
    return "timeTableConstraintsListDataSelectors";
  }
  case DataSelectors::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE: {
    return "timeTableDescriptionListDataSelectors";
  }
  case DataSelectors::Type::TIME_TABLE_LIST_DATA_SELECTORS_TYPE: {
    return "timeTableListDataSelectors";
  }
  case DataSelectors::Type::USE_CASE_INFORMATION_LIST_DATA_SELECTORS_TYPE: {
    return "useCaseInformationListDataSelectors";
  }
  default: { return ""; }
  }
}

DataSelectors::Type DataSelectors::getTypeFromString(const std::string &type) {
  auto it = STRING_TO_TYPE.find(type);
  if (it != STRING_TO_TYPE.end()) {
    return it->second;
  } else {
    return DataSelectors::Type::UNDEFINED;
  }
}

} // namespace keo_datagram