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

#include <keo_datagram/core/ScaledNumberSet.h>

#include <keo_datagram/core/ScaledNumberSetElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ScaledNumberSet::ScaledNumberSet()
    : m_valueIsSet(false), m_value(std::vector<ScaledNumber>()),
      m_rangeIsSet(false), m_range(std::vector<ScaledNumberRange>())

{}

ScaledNumberSet::ScaledNumberSet(const std::vector<ScaledNumber> &c_value,
                                 const std::vector<ScaledNumberRange> &c_range)
    : m_valueIsSet(true), m_value(c_value), m_rangeIsSet(true), m_range(c_range)

{}

bool ScaledNumberSet::operator==(const ScaledNumberSet &c_classObject) const {
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

bool ScaledNumberSet::operator!=(const ScaledNumberSet &c_classObject) const {
  return !(*this == c_classObject);
}

bool ScaledNumberSet::isEmpty() const { return !m_valueIsSet && !m_rangeIsSet; }

void ScaledNumberSet::setValue(const std::vector<ScaledNumber> &value) {
  m_value = value;
  m_valueIsSet = true;
}

const std::vector<ScaledNumber> &ScaledNumberSet::getValue() const {
  return m_value;
}

void ScaledNumberSet::cleanValue() {
  m_value.clear();
  m_valueIsSet = false;
}

bool ScaledNumberSet::getValueIsSet() const { return m_valueIsSet; }

void ScaledNumberSet::setRange(const std::vector<ScaledNumberRange> &range) {
  m_range = range;
  m_rangeIsSet = true;
}

const std::vector<ScaledNumberRange> &ScaledNumberSet::getRange() const {
  return m_range;
}

void ScaledNumberSet::cleanRange() {
  m_range.clear();
  m_rangeIsSet = false;
}

bool ScaledNumberSet::getRangeIsSet() const { return m_rangeIsSet; }

ScaledNumberSet
ScaledNumberSet::reduce(const ScaledNumberSetElements &elements) const {
  ScaledNumberSet dataOut;
  if (getValueIsSet() && elements.getValueIsSet()) {
    std::vector<ScaledNumber> values;
    for (const auto &value : getValue()) {
      values.push_back(value.reduce(elements.getValue()));
    }
    dataOut.setValue(values);
  }
  if (getRangeIsSet() && elements.getRangeIsSet()) {
    std::vector<ScaledNumberRange> values;
    for (const auto &value : getRange()) {
      values.push_back(value.reduce(elements.getRange()));
    }
    dataOut.setRange(values);
  }
  return dataOut;
}

bool ScaledNumberSet::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"value", "range"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<ScaledNumber>(
            static_cast<KeoJsonValue *>(&(*iter)), "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<ScaledNumberRange>(
            static_cast<KeoJsonValue *>(&(*iter)), "range", &m_range)) {
      m_rangeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ScaledNumberSet::toJson() const {
  std::string result = "[";
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ScaledNumber>("value", m_value);
  }
  if (m_rangeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<ScaledNumberRange>("range", m_range);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram