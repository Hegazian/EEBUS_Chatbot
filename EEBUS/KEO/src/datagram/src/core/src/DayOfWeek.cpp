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

#include <keo_datagram/core/DayOfWeek.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string DayOfWeek::enumToString[MAX_ENUM] = {
    "monday", "tuesday",  "wednesday", "thursday",
    "friday", "saturday", "sunday"};

DayOfWeek::DayOfWeek() : SpineEnum(), m_data(DayOfWeek::Value::UNDEFINED__) {}

DayOfWeek::DayOfWeek(DayOfWeek::Value c_data)
    : SpineEnum(), m_data(DayOfWeek::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

DayOfWeek::DayOfWeek(const std::string &c_text) { setFromString(c_text); }

DayOfWeek::Value DayOfWeek::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == DayOfWeek::enumToString[i]) {
      return static_cast<DayOfWeek::Value>(i);
    }
  }
  return DayOfWeek::Value::UNDEFINED__;
}

DayOfWeek::Value DayOfWeek::getValue() const { return m_data; }

DayOfWeek::Value DayOfWeek::getData() const { return getValue(); }

std::string DayOfWeek::toString() const {
  if ((static_cast<int>(m_data) >= 0) &&
      (m_data < static_cast<DayOfWeek::Value>(MAX_ENUM))) {
    return DayOfWeek::enumToString[static_cast<int>(m_data)];
  }
  return "";
}

bool DayOfWeek::operator==(const DayOfWeek &c_classObject) const {
  return this->m_data == c_classObject.m_data;
}

bool DayOfWeek::operator!=(const DayOfWeek &c_classObject) const {
  return !(*this == c_classObject);
}

size_t DayOfWeek::toNumber() const { return static_cast<size_t>(m_data); }

bool DayOfWeek::setFromNumber(size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<DayOfWeek::Value>(c_number);
    return true;
  } else {
    m_data = DayOfWeek::Value::UNDEFINED__;
    return false;
  }
}

bool DayOfWeek::setFromString(const std::string &c_text) {
  m_data = DayOfWeek::fromString(c_text);
  return (m_data != DayOfWeek::Value::UNDEFINED__);
}
} // namespace keo_datagram