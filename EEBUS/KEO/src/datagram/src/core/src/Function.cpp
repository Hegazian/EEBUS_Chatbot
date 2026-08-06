/*
 *     Copyright KEO GmbH 2019 - All rights reserved!
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

#include <keo_datagram/core/Function.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string Function::enumToString[MAX_ENUM] = {
    "actuatorLevelData",
    "actuatorLevelDescriptionData",
    "actuatorSwitchData",
    "actuatorSwitchDescriptionData",
    "alarmListData",
    "bindingManagementDeleteCall",
    "bindingManagementEntryListData",
    "bindingManagementRequestCall",
    "dataTunnelingCall",
    "deviceClassificationManufacturerData",
    "deviceClassificationUserData",
    "deviceDiagnosisHeartbeatData",
    "deviceDiagnosisServiceData",
    "deviceDiagnosisStateData",
    "directControlActivityListData",
    "directControlDescriptionData",
    "electricalConnectionDescriptionListData",
    "electricalConnectionParameterDescriptionListData",
    "electricalConnectionStateListData",
    "hvacOperationModeDescriptionListData",
    "hvacOverrunDescriptionListData",
    "hvacOverrunListData",
    "hvacSystemFunctionDescriptionListData",
    "hvacSystemFunctionListData",
    "hvacSystemFunctionOperationModeRelationListData",
    "hvacSystemFunctionPowerSequenceRelationListData",
    "hvacSystemFunctionSetpointRelationListData",
    "loadControlEventListData",
    "loadControlStateListData",
    "measurementConstraintsListData",
    "measurementDescriptionListData",
    "measurementListData",
    "measurementThresholdRelationListData",
    "messagingListData",
    "networkManagementAbortCall",
    "networkManagementAddNodeCall",
    "networkManagementDeviceDescriptionListData",
    "networkManagementDiscoverCall",
    "networkManagementEntityDescriptionListData",
    "networkManagementFeatureDescriptionListData",
    "networkManagementJoiningModeData",
    "networkManagementModifyNodeCall",
    "networkManagementProcessStateData",
    "networkManagementRemoveNodeCall",
    "networkManagementReportCandidateData",
    "networkManagementScanNetworkCall",
    "nodeManagementBindingData",
    "nodeManagementBindingDeleteCall",
    "nodeManagementBindingRequestCall",
    "nodeManagementDestinationListData",
    "nodeManagementDetailedDiscoveryData",
    "nodeManagementSubscriptionData",
    "nodeManagementSubscriptionDeleteCall",
    "nodeManagementSubscriptionRequestCall",
    "operatingConstraintsDurationListData",
    "operatingConstraintsInterruptListData",
    "operatingConstraintsPowerDescriptionListData",
    "operatingConstraintsPowerLevelListData",
    "operatingConstraintsPowerRangeListData",
    "operatingConstraintsResumeImplicationListData",
    "powerSequenceAlternativesRelationListData",
    "powerSequenceDescriptionListData",
    "powerSequenceNodeScheduleInformationData",
    "powerSequencePriceCalculationRequestCall",
    "powerSequencePriceListData",
    "powerSequenceScheduleConfigurationRequestCall",
    "powerSequenceScheduleConstraintsListData",
    "powerSequenceScheduleListData",
    "powerSequenceSchedulePreferenceListData",
    "powerSequenceStateListData",
    "powerTimeSlotScheduleConstraintsListData",
    "powerTimeSlotScheduleListData",
    "powerTimeSlotValueListData",
    "resultData",
    "sensingDescriptionData",
    "sensingListData",
    "setpointConstraintsListData",
    "setpointDescriptionListData",
    "setpointListData",
    "smartEnergyManagementPsConfigurationRequestCall",
    "smartEnergyManagementPsData",
    "smartEnergyManagementPsPriceCalculationRequestCall",
    "smartEnergyManagementPsPriceData",
    "specificationVersionListData",
    "subscriptionManagementDeleteCall",
    "subscriptionManagementEntryListData",
    "subscriptionManagementRequestCall",
    "supplyConditionDescriptionListData",
    "supplyConditionListData",
    "supplyConditionThresholdRelationListData",
    "taskManagementJobDescriptionListData",
    "taskManagementJobListData",
    "taskManagementJobRelationListData",
    "taskManagementOverviewData",
    "thresholdConstraintsListData",
    "thresholdDescriptionListData",
    "thresholdListData",
    "timeDistributorData",
    "timeDistributorEnquiryCall",
    "timeInformationData",
    "timePrecisionData",
    "timeTableConstraintsListData",
    "timeTableDescriptionListData",
    "timeTableListData",
    "deviceConfigurationKeyValueConstraintsListData",
    "deviceConfigurationKeyValueListData",
    "deviceConfigurationKeyValueDescriptionListData",
    "loadControlLimitConstraintsListData",
    "loadControlLimitDescriptionListData",
    "loadControlLimitListData",
    "loadControlNodeData",
    "timeSeriesConstraintsListData",
    "timeSeriesDescriptionListData",
    "timeSeriesListData",
    "tariffOverallConstraintsData",
    "tariffListData",
    "tariffBoundaryRelationListData",
    "tariffTierRelationListData",
    "tariffDescriptionListData",
    "tierBoundaryListData",
    "tierBoundaryDescriptionListData",
    "commodityListData",
    "tierListData",
    "tierIncentiveRelationListData",
    "tierDescriptionListData",
    "incentiveListData",
    "incentiveDescriptionListData",
    "incentiveTableData",
    "incentiveTableDescriptionData",
    "incentiveTableConstraintsData",
    "electricalConnectionPermittedValueSetListData",
    "useCaseInformationListData",
    "nodeManagementUseCaseData",
    "billConstraintsListData",
    "billDescriptionListData",
    "billListData",
    "identificationListData"};

Function::Function()
    : ExtendableSpineEnum(), m_data(Function::Value::UNDEFINED__) {}

Function::Function(Function::Value c_data)
    : ExtendableSpineEnum(), m_data(Function::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

Function::Function(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

Function Function::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == Function::enumToString[i]) {
      return Function(static_cast<Function::Function::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = Function();
  result.enumExtend = c_text;
  return result;
}

std::string Function::toString() const {
  if (m_data != Function::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<Function::Value>(MAX_ENUM))) {
      return Function::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

Function::Value Function::getValue() const { return m_data; }

Function::Value Function::getData() const { return getValue(); }

bool Function::setFromString(const std::string &c_text) {
  m_data = Function::fromString(c_text).getValue();
  if (m_data == Function::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool Function::operator==(const Function &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool Function::operator!=(const Function &c_struct) const {
  return !(*this == c_struct);
}

std::size_t Function::toNumber() const { return static_cast<size_t>(m_data); }

bool Function::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<Function::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = Function::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram