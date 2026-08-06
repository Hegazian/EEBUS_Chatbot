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

#include <keo_datagram/timeseries/TimeSeriesType.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string TimeSeriesType::enumToString[MAX_ENUM] = {
    "plan", "singleDemand", "constraints"};

TimeSeriesType::TimeSeriesType()
    : ExtendableSpineEnum(), m_data(TimeSeriesType::Value::UNDEFINED__) {}

TimeSeriesType::TimeSeriesType(TimeSeriesType::Value c_data)
    : ExtendableSpineEnum(), m_data(TimeSeriesType::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

TimeSeriesType::TimeSeriesType(const std::string &value)
    : ExtendableSpineEnum() {
  setFromString(value);
}

TimeSeriesType TimeSeriesType::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == TimeSeriesType::enumToString[i]) {
      return TimeSeriesType(
          static_cast<TimeSeriesType::TimeSeriesType::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = TimeSeriesType();
  result.enumExtend = c_text;
  return result;
}

std::string TimeSeriesType::toString() const {
  if (m_data != TimeSeriesType::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<TimeSeriesType::Value>(MAX_ENUM))) {
      return TimeSeriesType::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

TimeSeriesType::Value TimeSeriesType::getValue() const { return m_data; }

TimeSeriesType::Value TimeSeriesType::getData() const { return getValue(); }

bool TimeSeriesType::setFromString(const std::string &c_text) {
  m_data = TimeSeriesType::fromString(c_text).getValue();
  if (m_data == TimeSeriesType::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool TimeSeriesType::operator==(const TimeSeriesType &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool TimeSeriesType::operator!=(const TimeSeriesType &c_struct) const {
  return !(*this == c_struct);
}

std::size_t TimeSeriesType::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool TimeSeriesType::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<TimeSeriesType::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = TimeSeriesType::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram