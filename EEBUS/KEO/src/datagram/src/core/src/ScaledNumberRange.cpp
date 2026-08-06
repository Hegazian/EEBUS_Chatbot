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

#include <keo_datagram/core/ScaledNumberRange.h>

#include <keo_datagram/core/ScaledNumberRangeElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ScaledNumberRange::ScaledNumberRange()
    : m_minIsSet(false), m_min(ScaledNumber()), m_maxIsSet(false),
      m_max(ScaledNumber())

{}

ScaledNumberRange::ScaledNumberRange(const ScaledNumber &c_min,
                                     const ScaledNumber &c_max)
    : m_minIsSet(true), m_min(c_min), m_maxIsSet(true), m_max(c_max)

{}

bool ScaledNumberRange::
operator==(const ScaledNumberRange &c_classObject) const {
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

bool ScaledNumberRange::
operator!=(const ScaledNumberRange &c_classObject) const {
  return !(*this == c_classObject);
}

bool ScaledNumberRange::isEmpty() const { return !m_minIsSet && !m_maxIsSet; }

void ScaledNumberRange::setMin(const ScaledNumber &min) {
  m_min = min;
  m_minIsSet = true;
}

const ScaledNumber &ScaledNumberRange::getMin() const { return m_min; }

void ScaledNumberRange::cleanMin() {
  m_min = ScaledNumber();
  m_minIsSet = false;
}

bool ScaledNumberRange::getMinIsSet() const { return m_minIsSet; }

void ScaledNumberRange::setMax(const ScaledNumber &max) {
  m_max = max;
  m_maxIsSet = true;
}

const ScaledNumber &ScaledNumberRange::getMax() const { return m_max; }

void ScaledNumberRange::cleanMax() {
  m_max = ScaledNumber();
  m_maxIsSet = false;
}

bool ScaledNumberRange::getMaxIsSet() const { return m_maxIsSet; }

ScaledNumberRange
ScaledNumberRange::reduce(const ScaledNumberRangeElements &elements) const {
  ScaledNumberRange dataOut;
  if (getMinIsSet() && elements.getMinIsSet()) {
    dataOut.setMin(getMin().reduce(elements.getMin()));
  }
  if (getMaxIsSet() && elements.getMaxIsSet()) {
    dataOut.setMax(getMax().reduce(elements.getMax()));
  }
  return dataOut;
}

bool ScaledNumberRange::fromJson(KeoJsonValue *json) {
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

std::string ScaledNumberRange::toJson() const {
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