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

#include <keo_datagram/electricalconnection/ElectricalConnectionMeasurandVariant.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string ElectricalConnectionMeasurandVariant::enumToString[MAX_ENUM] =
    {"amplitude", "rms", "instantaneous", "angle", "cosPhi"};

ElectricalConnectionMeasurandVariant::ElectricalConnectionMeasurandVariant()
    : ExtendableSpineEnum(),
      m_data(ElectricalConnectionMeasurandVariant::Value::UNDEFINED__) {}

ElectricalConnectionMeasurandVariant::ElectricalConnectionMeasurandVariant(
    ElectricalConnectionMeasurandVariant::Value c_data)
    : ExtendableSpineEnum(),
      m_data(ElectricalConnectionMeasurandVariant::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

ElectricalConnectionMeasurandVariant::ElectricalConnectionMeasurandVariant(
    const std::string &value)
    : ExtendableSpineEnum() {
  setFromString(value);
}

ElectricalConnectionMeasurandVariant
ElectricalConnectionMeasurandVariant::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == ElectricalConnectionMeasurandVariant::enumToString[i]) {
      return ElectricalConnectionMeasurandVariant(
          static_cast<ElectricalConnectionMeasurandVariant::
                          ElectricalConnectionMeasurandVariant::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = ElectricalConnectionMeasurandVariant();
  result.enumExtend = c_text;
  return result;
}

std::string ElectricalConnectionMeasurandVariant::toString() const {
  if (m_data != ElectricalConnectionMeasurandVariant::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data <
         static_cast<ElectricalConnectionMeasurandVariant::Value>(MAX_ENUM))) {
      return ElectricalConnectionMeasurandVariant::enumToString[static_cast<
          int>(m_data)];
    }
  }
  return enumExtend;
}

ElectricalConnectionMeasurandVariant::Value
ElectricalConnectionMeasurandVariant::getValue() const {
  return m_data;
}

ElectricalConnectionMeasurandVariant::Value
ElectricalConnectionMeasurandVariant::getData() const {
  return getValue();
}

bool ElectricalConnectionMeasurandVariant::setFromString(
    const std::string &c_text) {
  m_data = ElectricalConnectionMeasurandVariant::fromString(c_text).getValue();
  if (m_data == ElectricalConnectionMeasurandVariant::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool ElectricalConnectionMeasurandVariant::
operator==(const ElectricalConnectionMeasurandVariant &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool ElectricalConnectionMeasurandVariant::
operator!=(const ElectricalConnectionMeasurandVariant &c_struct) const {
  return !(*this == c_struct);
}

std::size_t ElectricalConnectionMeasurandVariant::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool ElectricalConnectionMeasurandVariant::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<ElectricalConnectionMeasurandVariant::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = ElectricalConnectionMeasurandVariant::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram