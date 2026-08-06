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

#include <keo_datagram/core/UnitOfMeasurement.h>

namespace keo_datagram {

// Strings of the enum data type
const std::string UnitOfMeasurement::enumToString[MAX_ENUM] = {
    "unknown", "1",         "m",          "kg",
    "s",       "A",         "K",          "mol",
    "cd",      "V",         "W",          "Wh",
    "VA",      "VAh",       "var",        "varh",
    "degC",    "degF",      "Lm",         "lx",
    "Ohm",     "Hz",        "dB",         "dBm",
    "pct",     "ppm",       "l",          "l/s",
    "l/h",     "deg",       "rad",        "rad/s",
    "sr",      "Gy",        "Bq",         "Bq/m^3",
    "Sv",      "Rd",        "C",          "F",
    "H",       "J",         "N",          "N_m",
    "N_s",     "Wb",        "T",          "Pa",
    "bar",     "atm",       "psi",        "mmHg",
    "m^2",     "m^3",       "m^3/h",      "m/s",
    "m/s^2",   "m^3/s",     "m/m^3",      "kg/m^3",
    "kg_m",    "m^2/s",     "W/m_K",      "J/K",
    "1/s",     "W/m^2",     "J/m^2",      "S",
    "S/m",     "K/s",       "Pa/s",       "J/kg_K",
    "Vs",      "V/m",       "V/Hz",       "As",
    "A/m",     "Hz/s",      "kg/s",       "kg_m^2",
    "J/Wh",    "W/s",       "ft^3",       "ft^3/h",
    "ccf",     "ccf/h",     "US.liq.gal", "US.liq.gal/h",
    "Imp.gal", "Imp.gal/h", "Btu",        "Btu/h",
    "Ah",      "kg/Wh"};

UnitOfMeasurement::UnitOfMeasurement()
    : ExtendableSpineEnum(), m_data(UnitOfMeasurement::Value::UNDEFINED__) {}

UnitOfMeasurement::UnitOfMeasurement(UnitOfMeasurement::Value c_data)
    : ExtendableSpineEnum(), m_data(UnitOfMeasurement::Value::UNDEFINED__) {
  setFromNumber(static_cast<size_t>(c_data));
}

UnitOfMeasurement::UnitOfMeasurement(const std::string &value)
    : ExtendableSpineEnum() {
  setFromString(value);
}

UnitOfMeasurement UnitOfMeasurement::fromString(const std::string &c_text) {
  for (size_t i = 0; i < MAX_ENUM; i++) {
    if (c_text == UnitOfMeasurement::enumToString[i]) {
      return UnitOfMeasurement(
          static_cast<UnitOfMeasurement::UnitOfMeasurement::Value>(i));
    }
  }
  // The string is not contained in the list of predefined values
  auto result = UnitOfMeasurement();
  result.enumExtend = c_text;
  return result;
}

std::string UnitOfMeasurement::toString() const {
  if (m_data != UnitOfMeasurement::Value::UNDEFINED__) {
    if ((static_cast<int>(m_data) >= 0) &&
        (m_data < static_cast<UnitOfMeasurement::Value>(MAX_ENUM))) {
      return UnitOfMeasurement::enumToString[static_cast<int>(m_data)];
    }
  }
  return enumExtend;
}

UnitOfMeasurement::Value UnitOfMeasurement::getValue() const { return m_data; }

UnitOfMeasurement::Value UnitOfMeasurement::getData() const {
  return getValue();
}

bool UnitOfMeasurement::setFromString(const std::string &c_text) {
  m_data = UnitOfMeasurement::fromString(c_text).getValue();
  if (m_data == UnitOfMeasurement::Value::UNDEFINED__) {
    enumExtend = c_text;
  }
  return true;
}

bool UnitOfMeasurement::operator==(const UnitOfMeasurement &c_struct) const {
  return this->m_data == c_struct.m_data &&
         this->enumExtend == c_struct.enumExtend;
}

bool UnitOfMeasurement::operator!=(const UnitOfMeasurement &c_struct) const {
  return !(*this == c_struct);
}

std::size_t UnitOfMeasurement::toNumber() const {
  return static_cast<size_t>(m_data);
}

bool UnitOfMeasurement::setFromNumber(std::size_t c_number) {
  if (c_number < MAX_ENUM) {
    m_data = static_cast<UnitOfMeasurement::Value>(c_number);
    enumExtend = "";
  } else {
    m_data = UnitOfMeasurement::Value::UNDEFINED__;
  }
  return true;
}

} // namespace keo_datagram