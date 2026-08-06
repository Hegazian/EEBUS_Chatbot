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

#include <keo_datagram/measurement/MeasurementValueState.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string MeasurementValueState::enumToString[MAX_ENUM] = {
    "normal", "outOfRange", "error"};

MeasurementValueState::MeasurementValueState()
    : ExtendableSpineEnum(), m_data(MeasurementValueState::Value::UNDEFINED__) {
}

MeasurementValueState::MeasurementValueState(
    MeasurementValueState::Value c_data)
    : ExtendableSpineEnum(), m_data(MeasurementValueState::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

MeasurementValueState::MeasurementValueState(const std::string &value)
    : ExtendableSpineEnum() {
  setFromString(value);
}

MeasurementValueState
MeasurementValueState::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == MeasurementValueState::enumToString[i]) {
      return MeasurementValueState(
          static_cast<MeasurementValueState::MeasurementValueState::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = MeasurementValueState();
  result.enumExtend = c_text;
  return result;
}

std::string MeasurementValueState::toString() const {
  if (m_data != MeasurementValueState::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<MeasurementValueState::Value>(MAX_ENUM))) {
      return MeasurementValueState::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

MeasurementValueState::Value MeasurementValueState::getValue() const {
  return m_data;
}

MeasurementValueState::Value MeasurementValueState::getData() const {
  return getValue();
}

bool MeasurementValueState::setFromString(const std::string &c_text) {
  m_data = MeasurementValueState::fromString(c_text).getValue();
  if (m_data == MeasurementValueState::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool MeasurementValueState::
operator==(const MeasurementValueState &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool MeasurementValueState::
operator!=(const MeasurementValueState &c_struct) const {
  return !(*this == c_struct);
}

std::size_t MeasurementValueState::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool MeasurementValueState::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<MeasurementValueState::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = MeasurementValueState::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram