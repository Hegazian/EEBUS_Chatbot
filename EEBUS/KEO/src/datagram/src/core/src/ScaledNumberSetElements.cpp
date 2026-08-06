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

#include <keo_datagram/core/ScaledNumberSetElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ScaledNumberSetElements::ScaledNumberSetElements()
    : m_valueIsSet(false), m_value(ScaledNumberElements()), m_rangeIsSet(false),
      m_range(ScaledNumberRangeElements())

{}

ScaledNumberSetElements::ScaledNumberSetElements(
    const ScaledNumberElements &c_value,
    const ScaledNumberRangeElements &c_range)
    : m_valueIsSet(true), m_value(c_value), m_rangeIsSet(true), m_range(c_range)

{}

bool ScaledNumberSetElements::
operator==(const ScaledNumberSetElements &c_classObject) const {
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_rangeIsSet != c_classObject.m_rangeIsSet ||
      (m_rangeIsSet && (m_range != c_classObject.m_range))) {
    return false;
  }

  return true;
}

bool ScaledNumberSetElements::
operator!=(const ScaledNumberSetElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ScaledNumberSetElements::isEmpty() const {
  return !m_valueIsSet && !m_rangeIsSet;
}

void ScaledNumberSetElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &ScaledNumberSetElements::getValue() const {
  return m_value;
}

void ScaledNumberSetElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool ScaledNumberSetElements::getValueIsSet() const { return m_valueIsSet; }

void ScaledNumberSetElements::setRange(const ScaledNumberRangeElements &range) {
  m_range = range;
  m_rangeIsSet = true;
}

const ScaledNumberRangeElements &ScaledNumberSetElements::getRange() const {
  return m_range;
}

void ScaledNumberSetElements::cleanRange() {
  m_range = ScaledNumberRangeElements();
  m_rangeIsSet = false;
}

bool ScaledNumberSetElements::getRangeIsSet() const { return m_rangeIsSet; }

bool ScaledNumberSetElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"value", "range"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "range", &m_range)) {
      m_rangeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ScaledNumberSetElements::toJson() const {
  std::string result = "[";
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_rangeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("range", m_range);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram