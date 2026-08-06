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

#include <keo_datagram/core/ScaledNumberRangeElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ScaledNumberRangeElements::ScaledNumberRangeElements()
    : m_minIsSet(false), m_min(ScaledNumberElements()), m_maxIsSet(false),
      m_max(ScaledNumberElements())

{}

ScaledNumberRangeElements::ScaledNumberRangeElements(
    const ScaledNumberElements &c_min, const ScaledNumberElements &c_max)
    : m_minIsSet(true), m_min(c_min), m_maxIsSet(true), m_max(c_max)

{}

bool ScaledNumberRangeElements::
operator==(const ScaledNumberRangeElements &c_classObject) const {
  if (m_minIsSet != c_classObject.m_minIsSet ||
      (m_minIsSet && (m_min != c_classObject.m_min))) {
    return false;
  }
  if (m_maxIsSet != c_classObject.m_maxIsSet ||
      (m_maxIsSet && (m_max != c_classObject.m_max))) {
    return false;
  }

  return true;
}

bool ScaledNumberRangeElements::
operator!=(const ScaledNumberRangeElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ScaledNumberRangeElements::isEmpty() const {
  return !m_minIsSet && !m_maxIsSet;
}

void ScaledNumberRangeElements::setMin(const ScaledNumberElements &min) {
  m_min = min;
  m_minIsSet = true;
}

const ScaledNumberElements &ScaledNumberRangeElements::getMin() const {
  return m_min;
}

void ScaledNumberRangeElements::cleanMin() {
  m_min = ScaledNumberElements();
  m_minIsSet = false;
}

bool ScaledNumberRangeElements::getMinIsSet() const { return m_minIsSet; }

void ScaledNumberRangeElements::setMax(const ScaledNumberElements &max) {
  m_max = max;
  m_maxIsSet = true;
}

const ScaledNumberElements &ScaledNumberRangeElements::getMax() const {
  return m_max;
}

void ScaledNumberRangeElements::cleanMax() {
  m_max = ScaledNumberElements();
  m_maxIsSet = false;
}

bool ScaledNumberRangeElements::getMaxIsSet() const { return m_maxIsSet; }

bool ScaledNumberRangeElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"min", "max"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)), "min",
                                   &m_min)) {
      m_minIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)), "max",
                                   &m_max)) {
      m_maxIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ScaledNumberRangeElements::toJson() const {
  std::string result = "[";
  if (m_minIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("min", m_min);
  }
  if (m_maxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("max", m_max);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram