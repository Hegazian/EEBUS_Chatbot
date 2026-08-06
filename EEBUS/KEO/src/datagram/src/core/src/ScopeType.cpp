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

#include <keo_datagram/core/ScopeType.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string ScopeType::enumToString[MAX_ENUM] = {"ac",
                                                       "acCosPhiGrid",
                                                       "acCurrentA",
                                                       "acCurrentB",
                                                       "acCurrentC",
                                                       "acFrequencyGrid",
                                                       "acPowerA",
                                                       "acPowerB",
                                                       "acPowerC",
                                                       "acPowerLimitPct",
                                                       "acPowerTotal",
                                                       "acVoltageA",
                                                       "acVoltageB",
                                                       "acVoltageC",
                                                       "acYieldDay",
                                                       "acYieldTotal",
                                                       "dcCurrent",
                                                       "dcPower",
                                                       "dcString1",
                                                       "dcString2",
                                                       "dcString3",
                                                       "dcString4",
                                                       "dcString5",
                                                       "dcString6",
                                                       "dcTotal",
                                                       "dcVoltage",
                                                       "dhwTemperature",
                                                       "flowTemperature",
                                                       "outsideAirTemperature",
                                                       "returnTemperature",
                                                       "roomAirTemperature",
                                                       "charge",
                                                       "stateOfCharge",
                                                       "discharge",
                                                       "gridConsumption",
                                                       "gridFeedIn",
                                                       "selfConsumption",
                                                       "overloadProtection",
                                                       "acPower",
                                                       "acEnergy",
                                                       "acCurrent",
                                                       "acVoltage",
                                                       "batteryControl",
                                                       "simpleIncentiveTable"};

ScopeType::ScopeType()
    : ExtendableSpineEnum(), m_data(ScopeType::Value::UNDEFINED__) {}

ScopeType::ScopeType(ScopeType::Value c_data)
    : ExtendableSpineEnum(), m_data(ScopeType::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

ScopeType::ScopeType(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

ScopeType ScopeType::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == ScopeType::enumToString[i]) {
      return ScopeType(static_cast<ScopeType::ScopeType::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = ScopeType();
  result.enumExtend = c_text;
  return result;
}

std::string ScopeType::toString() const {
  if (m_data != ScopeType::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<ScopeType::Value>(MAX_ENUM))) {
      return ScopeType::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

ScopeType::Value ScopeType::getValue() const { return m_data; }

ScopeType::Value ScopeType::getData() const { return getValue(); }

bool ScopeType::setFromString(const std::string &c_text) {
  m_data = ScopeType::fromString(c_text).getValue();
  if (m_data == ScopeType::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool ScopeType::operator==(const ScopeType &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool ScopeType::operator!=(const ScopeType &c_struct) const {
  return !(*this == c_struct);
}

std::size_t ScopeType::toNumber() const { return static_cast<size_t>(m_data); }

bool ScopeType::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<ScopeType::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = ScopeType::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram