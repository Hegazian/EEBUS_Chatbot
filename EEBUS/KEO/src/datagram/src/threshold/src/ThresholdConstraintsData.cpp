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

#include <keo_datagram/threshold/ThresholdConstraintsData.h>

#include <keo_datagram/threshold/ThresholdConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdConstraintsData::ThresholdConstraintsData()
    : m_thresholdIdIsSet(false), m_thresholdId(0),
      m_thresholdRangeMinIsSet(false), m_thresholdRangeMin(ScaledNumber()),
      m_thresholdRangeMaxIsSet(false), m_thresholdRangeMax(ScaledNumber()),
      m_thresholdStepSizeIsSet(false), m_thresholdStepSize(ScaledNumber())

{}

bool ThresholdConstraintsData::
operator==(const ThresholdConstraintsData &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }
  if (m_thresholdRangeMinIsSet != c_classObject.m_thresholdRangeMinIsSet ||
      (m_thresholdRangeMinIsSet &&
       (m_thresholdRangeMin != c_classObject.m_thresholdRangeMin))) {
    return false;
  }
  if (m_thresholdRangeMaxIsSet != c_classObject.m_thresholdRangeMaxIsSet ||
      (m_thresholdRangeMaxIsSet &&
       (m_thresholdRangeMax != c_classObject.m_thresholdRangeMax))) {
    return false;
  }
  if (m_thresholdStepSizeIsSet != c_classObject.m_thresholdStepSizeIsSet ||
      (m_thresholdStepSizeIsSet &&
       (m_thresholdStepSize != c_classObject.m_thresholdStepSize))) {
    return false;
  }

  return true;
}

bool ThresholdConstraintsData::
operator!=(const ThresholdConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdConstraintsData::isEmpty() const {
  return !m_thresholdIdIsSet && !m_thresholdRangeMinIsSet &&
         !m_thresholdRangeMaxIsSet && !m_thresholdStepSizeIsSet;
}

void ThresholdConstraintsData::setThresholdId(
    const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &ThresholdConstraintsData::getThresholdId() const {
  return m_thresholdId;
}

void ThresholdConstraintsData::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool ThresholdConstraintsData::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void ThresholdConstraintsData::setThresholdRangeMin(
    const ScaledNumber &thresholdRangeMin) {
  m_thresholdRangeMin = thresholdRangeMin;
  m_thresholdRangeMinIsSet = true;
}

const ScaledNumber &ThresholdConstraintsData::getThresholdRangeMin() const {
  return m_thresholdRangeMin;
}

void ThresholdConstraintsData::cleanThresholdRangeMin() {
  m_thresholdRangeMin = ScaledNumber();
  m_thresholdRangeMinIsSet = false;
}

bool ThresholdConstraintsData::getThresholdRangeMinIsSet() const {
  return m_thresholdRangeMinIsSet;
}

void ThresholdConstraintsData::setThresholdRangeMax(
    const ScaledNumber &thresholdRangeMax) {
  m_thresholdRangeMax = thresholdRangeMax;
  m_thresholdRangeMaxIsSet = true;
}

const ScaledNumber &ThresholdConstraintsData::getThresholdRangeMax() const {
  return m_thresholdRangeMax;
}

void ThresholdConstraintsData::cleanThresholdRangeMax() {
  m_thresholdRangeMax = ScaledNumber();
  m_thresholdRangeMaxIsSet = false;
}

bool ThresholdConstraintsData::getThresholdRangeMaxIsSet() const {
  return m_thresholdRangeMaxIsSet;
}

void ThresholdConstraintsData::setThresholdStepSize(
    const ScaledNumber &thresholdStepSize) {
  m_thresholdStepSize = thresholdStepSize;
  m_thresholdStepSizeIsSet = true;
}

const ScaledNumber &ThresholdConstraintsData::getThresholdStepSize() const {
  return m_thresholdStepSize;
}

void ThresholdConstraintsData::cleanThresholdStepSize() {
  m_thresholdStepSize = ScaledNumber();
  m_thresholdStepSizeIsSet = false;
}

bool ThresholdConstraintsData::getThresholdStepSizeIsSet() const {
  return m_thresholdStepSizeIsSet;
}

ThresholdConstraintsData ThresholdConstraintsData::reduce(
    const ThresholdConstraintsDataElements &elements) const {
  ThresholdConstraintsData dataOut;
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  if (getThresholdRangeMinIsSet() && elements.getThresholdRangeMinIsSet()) {
    dataOut.setThresholdRangeMin(
        getThresholdRangeMin().reduce(elements.getThresholdRangeMin()));
  }
  if (getThresholdRangeMaxIsSet() && elements.getThresholdRangeMaxIsSet()) {
    dataOut.setThresholdRangeMax(
        getThresholdRangeMax().reduce(elements.getThresholdRangeMax()));
  }
  if (getThresholdStepSizeIsSet() && elements.getThresholdStepSizeIsSet()) {
    dataOut.setThresholdStepSize(
        getThresholdStepSize().reduce(elements.getThresholdStepSize()));
  }
  return dataOut;
}

bool ThresholdConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"thresholdId", "thresholdRangeMin", "thresholdRangeMax",
                   "thresholdStepSize"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdRangeMin", &m_thresholdRangeMin)) {
      m_thresholdRangeMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdRangeMax", &m_thresholdRangeMax)) {
      m_thresholdRangeMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdStepSize", &m_thresholdStepSize)) {
      m_thresholdStepSizeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdConstraintsData::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  if (m_thresholdRangeMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("thresholdRangeMin", m_thresholdRangeMin);
  }
  if (m_thresholdRangeMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("thresholdRangeMax", m_thresholdRangeMax);
  }
  if (m_thresholdStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("thresholdStepSize", m_thresholdStepSize);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram