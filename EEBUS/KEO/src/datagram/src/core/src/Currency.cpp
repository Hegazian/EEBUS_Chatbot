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

#include <keo_datagram/core/Currency.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string Currency::enumToString[MAX_ENUM] = {
    "AED", "AFN", "ALL", "AMD", "ANG", "AOA", "ARS", "AUD", "AWG", "AZN", "BAM",
    "BBD", "BDT", "BGN", "BHD", "BIF", "BMD", "BND", "BOB", "BOV", "BRL", "BSD",
    "BTN", "BWP", "BYR", "BZD", "CAD", "CDF", "CHE", "CHF", "CHW", "CLF", "CLP",
    "CNY", "COP", "COU", "CRC", "CUC", "CUP", "CVE", "CZK", "DJF", "DKK", "DOP",
    "DZD", "EGP", "ERN", "ETB", "EUR", "FJD", "FKP", "GBP", "GEL", "GHS", "GIP",
    "GMD", "GNF", "GTQ", "GYD", "HKD", "HNL", "HRK", "HTG", "HUF", "IDR", "ILS",
    "INR", "IQD", "IRR", "ISK", "JMD", "JOD", "JPY", "KES", "KGS", "KHR", "KMF",
    "KPW", "KRW", "KWD", "KYD", "KZT", "LAK", "LBP", "LKR", "LRD", "LSL", "LYD",
    "MAD", "MDL", "MGA", "MKD", "MMK", "MNT", "MOP", "MRO", "MUR", "MVR", "MWK",
    "MXN", "MXV", "MYR", "MZN", "NAD", "NGN", "NIO", "NOK", "NPR", "NZD", "OMR",
    "PAB", "PEN", "PGK", "PHP", "PKR", "PLN", "PYG", "QAR", "RON", "RSD", "RUB",
    "RWF", "SAR", "SBD", "SCR", "SDG", "SEK", "SGD", "SHP", "SLL", "SOS", "SRD",
    "SSP", "STD", "SVC", "SYP", "SZL", "THB", "TJS", "TMT", "TND", "TOP", "TRY",
    "TTD", "TWD", "TZS", "UAH", "UGX", "USD", "USN", "UYI", "UYU", "UZS", "VEF",
    "VND", "VUV", "WST", "XAF", "XAG", "XAU", "XBA", "XBB", "XBC", "XBD", "XCD",
    "XDR", "XOF", "XPD", "XPF", "XPT", "XSU", "XTS", "XUA", "XXX", "YER", "ZAR",
    "ZMW", "ZWL"};

Currency::Currency()
    : ExtendableSpineEnum(), m_data(Currency::Value::UNDEFINED__) {}

Currency::Currency(Currency::Value c_data)
    : ExtendableSpineEnum(), m_data(Currency::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

Currency::Currency(const std::string &value) : ExtendableSpineEnum() {
  setFromString(value);
}

Currency Currency::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == Currency::enumToString[i]) {
      return Currency(static_cast<Currency::Currency::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = Currency();
  result.enumExtend = c_text;
  return result;
}

std::string Currency::toString() const {
  if (m_data != Currency::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<Currency::Value>(MAX_ENUM))) {
      return Currency::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

Currency::Value Currency::getValue() const { return m_data; }

Currency::Value Currency::getData() const { return getValue(); }

bool Currency::setFromString(const std::string &c_text) {
  m_data = Currency::fromString(c_text).getValue();
  if (m_data == Currency::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool Currency::operator==(const Currency &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool Currency::operator!=(const Currency &c_struct) const {
  return !(*this == c_struct);
}

std::size_t Currency::toNumber() const { return static_cast<size_t>(m_data); }

bool Currency::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<Currency::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = Currency::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram