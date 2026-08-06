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

#include <keo_datagram/supplycondition/GridCondition.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string GridCondition::enumToString[MAX_ENUM] = {
    "consumptionRed", "consumptionYellow", "good", "productionYellow",
    "productionRed"};

GridCondition::GridCondition()
    : ExtendableSpineEnum(), m_data(GridCondition::Value::UNDEFINED__) {}

GridCondition::GridCondition(GridCondition::Value c_data)
    : ExtendableSpineEnum(), m_data(GridCondition::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

GridCondition::GridCondition(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

GridCondition GridCondition::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == GridCondition::enumToString[i]) {
      return GridCondition(static_cast<GridCondition::GridCondition::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = GridCondition();
  result.enumExtend = c_text;
  return result;
}

std::string GridCondition::toString() const {
  if (m_data != GridCondition::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<GridCondition::Value>(MAX_ENUM))) {
      return GridCondition::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

GridCondition::Value GridCondition::getValue() const { return m_data; }

GridCondition::Value GridCondition::getData() const { return getValue(); }

bool GridCondition::setFromString(const std::string &c_text) {
  m_data = GridCondition::fromString(c_text).getValue();
  if (m_data == GridCondition::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool GridCondition::operator==(const GridCondition &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool GridCondition::operator!=(const GridCondition &c_struct) const {
  return !(*this == c_struct);
}

std::size_t GridCondition::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool GridCondition::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<GridCondition::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = GridCondition::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram