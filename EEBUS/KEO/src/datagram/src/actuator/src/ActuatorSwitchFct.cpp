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

#include <keo_datagram/actuator/ActuatorSwitchFct.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string ActuatorSwitchFct::enumToString[MAX_ENUM] = {"on", "off",
                                                               "toggle"};

ActuatorSwitchFct::ActuatorSwitchFct()
    : ExtendableSpineEnum(), m_data(ActuatorSwitchFct::Value::UNDEFINED__) {}

ActuatorSwitchFct::ActuatorSwitchFct(ActuatorSwitchFct::Value c_data)
    : ExtendableSpineEnum(), m_data(ActuatorSwitchFct::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

ActuatorSwitchFct::ActuatorSwitchFct(const std::string &value)
    : ExtendableSpineEnum() {
  setFromString(value);
}

ActuatorSwitchFct ActuatorSwitchFct::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == ActuatorSwitchFct::enumToString[i]) {
      return ActuatorSwitchFct(
          static_cast<ActuatorSwitchFct::ActuatorSwitchFct::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = ActuatorSwitchFct();
  result.enumExtend = c_text;
  return result;
}

std::string ActuatorSwitchFct::toString() const {
  if (m_data != ActuatorSwitchFct::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<ActuatorSwitchFct::Value>(MAX_ENUM))) {
      return ActuatorSwitchFct::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

ActuatorSwitchFct::Value ActuatorSwitchFct::getValue() const { return m_data; }

ActuatorSwitchFct::Value ActuatorSwitchFct::getData() const {
  return getValue();
}

bool ActuatorSwitchFct::setFromString(const std::string &c_text) {
  m_data = ActuatorSwitchFct::fromString(c_text).getValue();
  if (m_data == ActuatorSwitchFct::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool ActuatorSwitchFct::operator==(const ActuatorSwitchFct &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool ActuatorSwitchFct::operator!=(const ActuatorSwitchFct &c_struct) const {
  return !(*this == c_struct);
}

std::size_t ActuatorSwitchFct::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool ActuatorSwitchFct::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<ActuatorSwitchFct::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = ActuatorSwitchFct::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram