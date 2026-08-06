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

#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitConstraintsDataElements::
    LoadControlLimitConstraintsDataElements()
    : DataElements(), m_limitIdIsSet(false), m_valueRangeMinIsSet(false),
      m_valueRangeMin(ScaledNumberElements()), m_valueRangeMaxIsSet(false),
      m_valueRangeMax(ScaledNumberElements()), m_valueStepSizeIsSet(false),
      m_valueStepSize(ScaledNumberElements())

{}

bool LoadControlLimitConstraintsDataElements::
operator==(const LoadControlLimitConstraintsDataElements &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet) {
    return false;
  }
  if (m_valueRangeMinIsSet != c_classObject.m_valueRangeMinIsSet ||
      (m_valueRangeMinIsSet &&
       (m_valueRangeMin != c_classObject.m_valueRangeMin))) {
    return false;
  }
  if (m_valueRangeMaxIsSet != c_classObject.m_valueRangeMaxIsSet ||
      (m_valueRangeMaxIsSet &&
       (m_valueRangeMax != c_classObject.m_valueRangeMax))) {
    return false;
  }
  if (m_valueStepSizeIsSet != c_classObject.m_valueStepSizeIsSet ||
      (m_valueStepSizeIsSet &&
       (m_valueStepSize != c_classObject.m_valueStepSize))) {
    return false;
  }

  return true;
}

bool LoadControlLimitConstraintsDataElements::
operator!=(const LoadControlLimitConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitConstraintsDataElements::isEmpty() const {
  return !m_limitIdIsSet && !m_valueRangeMinIsSet && !m_valueRangeMaxIsSet &&
         !m_valueStepSizeIsSet;
}

DataElements::Type
LoadControlLimitConstraintsDataElements::getDataType() const {
  return DataElements::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr LoadControlLimitConstraintsDataElements::clone() const {
  return std::make_shared<LoadControlLimitConstraintsDataElements>(*this);
}

void LoadControlLimitConstraintsDataElements::setLimitId() {
  m_limitIdIsSet = true;
}

void LoadControlLimitConstraintsDataElements::cleanLimitId() {
  m_limitIdIsSet = false;
}

bool LoadControlLimitConstraintsDataElements::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

void LoadControlLimitConstraintsDataElements::setValueRangeMin(
    const ScaledNumberElements &valueRangeMin) {
  m_valueRangeMin = valueRangeMin;
  m_valueRangeMinIsSet = true;
}

const ScaledNumberElements &
LoadControlLimitConstraintsDataElements::getValueRangeMin() const {
  return m_valueRangeMin;
}

void LoadControlLimitConstraintsDataElements::cleanValueRangeMin() {
  m_valueRangeMin = ScaledNumberElements();
  m_valueRangeMinIsSet = false;
}

bool LoadControlLimitConstraintsDataElements::getValueRangeMinIsSet() const {
  return m_valueRangeMinIsSet;
}

void LoadControlLimitConstraintsDataElements::setValueRangeMax(
    const ScaledNumberElements &valueRangeMax) {
  m_valueRangeMax = valueRangeMax;
  m_valueRangeMaxIsSet = true;
}

const ScaledNumberElements &
LoadControlLimitConstraintsDataElements::getValueRangeMax() const {
  return m_valueRangeMax;
}

void LoadControlLimitConstraintsDataElements::cleanValueRangeMax() {
  m_valueRangeMax = ScaledNumberElements();
  m_valueRangeMaxIsSet = false;
}

bool LoadControlLimitConstraintsDataElements::getValueRangeMaxIsSet() const {
  return m_valueRangeMaxIsSet;
}

void LoadControlLimitConstraintsDataElements::setValueStepSize(
    const ScaledNumberElements &valueStepSize) {
  m_valueStepSize = valueStepSize;
  m_valueStepSizeIsSet = true;
}

const ScaledNumberElements &
LoadControlLimitConstraintsDataElements::getValueStepSize() const {
  return m_valueStepSize;
}

void LoadControlLimitConstraintsDataElements::cleanValueStepSize() {
  m_valueStepSize = ScaledNumberElements();
  m_valueStepSizeIsSet = false;
}

bool LoadControlLimitConstraintsDataElements::getValueStepSizeIsSet() const {
  return m_valueStepSizeIsSet;
}

bool LoadControlLimitConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"limitId", "valueRangeMin", "valueRangeMax", "valueStepSize"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "limitId")) {
      m_limitIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueRangeMin", &m_valueRangeMin)) {
      m_valueRangeMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueRangeMax", &m_valueRangeMax)) {
      m_valueRangeMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueStepSize", &m_valueStepSize)) {
      m_valueStepSizeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlLimitConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("limitId");
  }
  if (m_valueRangeMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueRangeMin", m_valueRangeMin);
  }
  if (m_valueRangeMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueRangeMax", m_valueRangeMax);
  }
  if (m_valueStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueStepSize", m_valueStepSize);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram