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

#include <keo_datagram/core/ScaledNumber.h>

#include <keo_datagram/core/ScaledNumberElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ScaledNumber::ScaledNumber()
    : m_numberIsSet(false), m_number(0), m_scaleIsSet(false), m_scale(0)

{}

ScaledNumber::ScaledNumber(const xs_long &c_number, const xs_short &c_scale)
    : m_numberIsSet(true), m_number(c_number), m_scaleIsSet(true),
      m_scale(c_scale)

{}

bool ScaledNumber::operator==(const ScaledNumber &c_classObject) const {
  if (m_numberIsSet != c_classObject.m_numberIsSet ||
      (m_numberIsSet && (m_number != c_classObject.m_number))) {
    return false;
  }
  if (m_scaleIsSet != c_classObject.m_scaleIsSet ||
      (m_scaleIsSet && (m_scale != c_classObject.m_scale))) {
    return false;
  }

  return true;
}

bool ScaledNumber::operator!=(const ScaledNumber &c_classObject) const {
  return !(*this == c_classObject);
}

bool ScaledNumber::isEmpty() const { return !m_numberIsSet && !m_scaleIsSet; }

void ScaledNumber::setNumber(const xs_long &number) {
  m_number = number;
  m_numberIsSet = true;
}

const xs_long &ScaledNumber::getNumber() const { return m_number; }

void ScaledNumber::cleanNumber() {
  m_number = 0;
  m_numberIsSet = false;
}

bool ScaledNumber::getNumberIsSet() const { return m_numberIsSet; }

void ScaledNumber::setScale(const xs_short &scale) {
  m_scale = scale;
  m_scaleIsSet = true;
}

const xs_short &ScaledNumber::getScale() const { return m_scale; }

void ScaledNumber::cleanScale() {
  m_scale = 0;
  m_scaleIsSet = false;
}

bool ScaledNumber::getScaleIsSet() const { return m_scaleIsSet; }

ScaledNumber ScaledNumber::reduce(const ScaledNumberElements &elements) const {
  ScaledNumber dataOut;
  if (getNumberIsSet() && elements.getNumberIsSet()) {
    dataOut.setNumber(getNumber());
  }
  if (getScaleIsSet() && elements.getScaleIsSet()) {
    dataOut.setScale(getScale());
  }
  return dataOut;
}

bool ScaledNumber::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"number", "scale"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "number", &m_number)) {
      m_numberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scale", &m_scale)) {
      m_scaleIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ScaledNumber::toJson() const {
  std::string result = "[";
  if (m_numberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("number", m_number);
  }
  if (m_scaleIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scale", m_scale);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram