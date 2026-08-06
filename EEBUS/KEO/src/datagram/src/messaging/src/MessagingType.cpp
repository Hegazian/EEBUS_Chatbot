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

#include <keo_datagram/messaging/MessagingType.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string MessagingType::enumToString[MAX_ENUM] = {
    "logging", "information", "warning", "alarm", "emergency", "obsolete"};

MessagingType::MessagingType()
    : ExtendableSpineEnum(), m_data(MessagingType::Value::UNDEFINED__) {}

MessagingType::MessagingType(MessagingType::Value c_data)
    : ExtendableSpineEnum(), m_data(MessagingType::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

MessagingType::MessagingType(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

MessagingType MessagingType::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == MessagingType::enumToString[i]) {
      return MessagingType(static_cast<MessagingType::MessagingType::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = MessagingType();
  result.enumExtend = c_text;
  return result;
}

std::string MessagingType::toString() const {
  if (m_data != MessagingType::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<MessagingType::Value>(MAX_ENUM))) {
      return MessagingType::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

MessagingType::Value MessagingType::getValue() const { return m_data; }

MessagingType::Value MessagingType::getData() const { return getValue(); }

bool MessagingType::setFromString(const std::string &c_text) {
  m_data = MessagingType::fromString(c_text).getValue();
  if (m_data == MessagingType::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool MessagingType::operator==(const MessagingType &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool MessagingType::operator!=(const MessagingType &c_struct) const {
  return !(*this == c_struct);
}

std::size_t MessagingType::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool MessagingType::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<MessagingType::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = MessagingType::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram