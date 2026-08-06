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

#include <keo_datagram/core/BillType.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string BillType::enumToString[MAX_ENUM] = {"chargingSummary"};

BillType::BillType()
    : ExtendableSpineEnum(), m_data(BillType::Value::UNDEFINED__) {}

BillType::BillType(BillType::Value c_data)
    : ExtendableSpineEnum(), m_data(BillType::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

BillType::BillType(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

BillType BillType::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == BillType::enumToString[i]) {
      return BillType(static_cast<BillType::BillType::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = BillType();
  result.enumExtend = c_text;
  return result;
}

std::string BillType::toString() const {
  if (m_data != BillType::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<BillType::Value>(MAX_ENUM))) {
      return BillType::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

BillType::Value BillType::getValue() const { return m_data; }

BillType::Value BillType::getData() const { return getValue(); }

bool BillType::setFromString(const std::string &c_text) {
  m_data = BillType::fromString(c_text).getValue();
  if (m_data == BillType::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool BillType::operator==(const BillType &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool BillType::operator!=(const BillType &c_struct) const {
  return !(*this == c_struct);
}

std::size_t BillType::toNumber() const { return static_cast<size_t>(m_data); }

bool BillType::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<BillType::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = BillType::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram