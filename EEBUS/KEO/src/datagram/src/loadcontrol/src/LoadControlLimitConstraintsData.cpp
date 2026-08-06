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

#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsData.h>

#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitConstraintsData::LoadControlLimitConstraintsData()
    : m_limitIdIsSet(false), m_limitId(0), m_valueRangeMinIsSet(false),
      m_valueRangeMin(ScaledNumber()), m_valueRangeMaxIsSet(false),
      m_valueRangeMax(ScaledNumber()), m_valueStepSizeIsSet(false),
      m_valueStepSize(ScaledNumber())

{}

bool LoadControlLimitConstraintsData::
operator==(const LoadControlLimitConstraintsData &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet ||
      (m_limitIdIsSet && (m_limitId != c_classObject.m_limitId))) {
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

bool LoadControlLimitConstraintsData::
operator!=(const LoadControlLimitConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitConstraintsData::isEmpty() const {
  return !m_limitIdIsSet && !m_valueRangeMinIsSet && !m_valueRangeMaxIsSet &&
         !m_valueStepSizeIsSet;
}

void LoadControlLimitConstraintsData::setLimitId(
    const xs_unsignedInt &limitId) {
  m_limitId = limitId;
  m_limitIdIsSet = true;
}

const xs_unsignedInt &LoadControlLimitConstraintsData::getLimitId() const {
  return m_limitId;
}

void LoadControlLimitConstraintsData::cleanLimitId() {
  m_limitId = 0;
  m_limitIdIsSet = false;
}

bool LoadControlLimitConstraintsData::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

void LoadControlLimitConstraintsData::setValueRangeMin(
    const ScaledNumber &valueRangeMin) {
  m_valueRangeMin = valueRangeMin;
  m_valueRangeMinIsSet = true;
}

const ScaledNumber &LoadControlLimitConstraintsData::getValueRangeMin() const {
  return m_valueRangeMin;
}

void LoadControlLimitConstraintsData::cleanValueRangeMin() {
  m_valueRangeMin = ScaledNumber();
  m_valueRangeMinIsSet = false;
}

bool LoadControlLimitConstraintsData::getValueRangeMinIsSet() const {
  return m_valueRangeMinIsSet;
}

void LoadControlLimitConstraintsData::setValueRangeMax(
    const ScaledNumber &valueRangeMax) {
  m_valueRangeMax = valueRangeMax;
  m_valueRangeMaxIsSet = true;
}

const ScaledNumber &LoadControlLimitConstraintsData::getValueRangeMax() const {
  return m_valueRangeMax;
}

void LoadControlLimitConstraintsData::cleanValueRangeMax() {
  m_valueRangeMax = ScaledNumber();
  m_valueRangeMaxIsSet = false;
}

bool LoadControlLimitConstraintsData::getValueRangeMaxIsSet() const {
  return m_valueRangeMaxIsSet;
}

void LoadControlLimitConstraintsData::setValueStepSize(
    const ScaledNumber &valueStepSize) {
  m_valueStepSize = valueStepSize;
  m_valueStepSizeIsSet = true;
}

const ScaledNumber &LoadControlLimitConstraintsData::getValueStepSize() const {
  return m_valueStepSize;
}

void LoadControlLimitConstraintsData::cleanValueStepSize() {
  m_valueStepSize = ScaledNumber();
  m_valueStepSizeIsSet = false;
}

bool LoadControlLimitConstraintsData::getValueStepSizeIsSet() const {
  return m_valueStepSizeIsSet;
}

LoadControlLimitConstraintsData LoadControlLimitConstraintsData::reduce(
    const LoadControlLimitConstraintsDataElements &elements) const {
  LoadControlLimitConstraintsData dataOut;
  if (getLimitIdIsSet() && elements.getLimitIdIsSet()) {
    dataOut.setLimitId(getLimitId());
  }
  if (getValueRangeMinIsSet() && elements.getValueRangeMinIsSet()) {
    dataOut.setValueRangeMin(
        getValueRangeMin().reduce(elements.getValueRangeMin()));
  }
  if (getValueRangeMaxIsSet() && elements.getValueRangeMaxIsSet()) {
    dataOut.setValueRangeMax(
        getValueRangeMax().reduce(elements.getValueRangeMax()));
  }
  if (getValueStepSizeIsSet() && elements.getValueStepSizeIsSet()) {
    dataOut.setValueStepSize(
        getValueStepSize().reduce(elements.getValueStepSize()));
  }
  return dataOut;
}

bool LoadControlLimitConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"limitId", "valueRangeMin", "valueRangeMax", "valueStepSize"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitId", &m_limitId)) {
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

std::string LoadControlLimitConstraintsData::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitId", m_limitId);
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