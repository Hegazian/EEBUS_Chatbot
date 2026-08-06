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

#include <keo_datagram/alarm/AlarmType.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string AlarmType::enumToString[MAX_ENUM] = {
    "alarmCancelled", "underThreshold", "overThreshold"};

AlarmType::AlarmType()
    : ExtendableSpineEnum(), m_data(AlarmType::Value::UNDEFINED__) {}

AlarmType::AlarmType(AlarmType::Value c_data)
    : ExtendableSpineEnum(), m_data(AlarmType::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

AlarmType::AlarmType(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

AlarmType AlarmType::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == AlarmType::enumToString[i]) {
      return AlarmType(static_cast<AlarmType::AlarmType::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = AlarmType();
  result.enumExtend = c_text;
  return result;
}

std::string AlarmType::toString() const {
  if (m_data != AlarmType::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<AlarmType::Value>(MAX_ENUM))) {
      return AlarmType::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

AlarmType::Value AlarmType::getValue() const { return m_data; }

AlarmType::Value AlarmType::getData() const { return getValue(); }

bool AlarmType::setFromString(const std::string &c_text) {
  m_data = AlarmType::fromString(c_text).getValue();
  if (m_data == AlarmType::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool AlarmType::operator==(const AlarmType &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool AlarmType::operator!=(const AlarmType &c_struct) const {
  return !(*this == c_struct);
}

std::size_t AlarmType::toNumber() const { return static_cast<size_t>(m_data); }

bool AlarmType::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<AlarmType::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = AlarmType::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram