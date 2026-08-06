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

#include <keo_datagram/loadcontrol/LoadControlEventAction.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string LoadControlEventAction::enumToString[MAX_ENUM] = {
    "pause", "resume", "reduce", "increase", "emergency", "normal"};

LoadControlEventAction::LoadControlEventAction()
    : ExtendableSpineEnum(),
      m_data(LoadControlEventAction::Value::UNDEFINED__) {}

LoadControlEventAction::LoadControlEventAction(
    LoadControlEventAction::Value c_data)
    : ExtendableSpineEnum(),
      m_data(LoadControlEventAction::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

LoadControlEventAction::LoadControlEventAction(const std::string &value)
    : ExtendableSpineEnum() {
  setFromString(value);
}

LoadControlEventAction
LoadControlEventAction::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == LoadControlEventAction::enumToString[i]) {
      return LoadControlEventAction(
          static_cast<LoadControlEventAction::LoadControlEventAction::Value>(
              i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = LoadControlEventAction();
  result.enumExtend = c_text;
  return result;
}

std::string LoadControlEventAction::toString() const {
  if (m_data != LoadControlEventAction::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<LoadControlEventAction::Value>(MAX_ENUM))) {
      return LoadControlEventAction::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

LoadControlEventAction::Value LoadControlEventAction::getValue() const {
  return m_data;
}

LoadControlEventAction::Value LoadControlEventAction::getData() const {
  return getValue();
}

bool LoadControlEventAction::setFromString(const std::string &c_text) {
  m_data = LoadControlEventAction::fromString(c_text).getValue();
  if (m_data == LoadControlEventAction::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool LoadControlEventAction::
operator==(const LoadControlEventAction &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool LoadControlEventAction::
operator!=(const LoadControlEventAction &c_struct) const {
  return !(*this == c_struct);
}

std::size_t LoadControlEventAction::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool LoadControlEventAction::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<LoadControlEventAction::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = LoadControlEventAction::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram