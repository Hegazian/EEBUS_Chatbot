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

#include <keo_datagram/threshold/ThresholdConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdConstraintsDataElements::ThresholdConstraintsDataElements()
    : DataElements(), m_thresholdIdIsSet(false),
      m_thresholdRangeMinIsSet(false),
      m_thresholdRangeMin(ScaledNumberElements()),
      m_thresholdRangeMaxIsSet(false),
      m_thresholdRangeMax(ScaledNumberElements()),
      m_thresholdStepSizeIsSet(false),
      m_thresholdStepSize(ScaledNumberElements())

{}

bool ThresholdConstraintsDataElements::
operator==(const ThresholdConstraintsDataElements &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
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

bool ThresholdConstraintsDataElements::
operator!=(const ThresholdConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdConstraintsDataElements::isEmpty() const {
  return !m_thresholdIdIsSet && !m_thresholdRangeMinIsSet &&
         !m_thresholdRangeMaxIsSet && !m_thresholdStepSizeIsSet;
}

DataElements::Type ThresholdConstraintsDataElements::getDataType() const {
  return DataElements::Type::THRESHOLD_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ThresholdConstraintsDataElements::clone() const {
  return std::make_shared<ThresholdConstraintsDataElements>(*this);
}

void ThresholdConstraintsDataElements::setThresholdId() {
  m_thresholdIdIsSet = true;
}

void ThresholdConstraintsDataElements::cleanThresholdId() {
  m_thresholdIdIsSet = false;
}

bool ThresholdConstraintsDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void ThresholdConstraintsDataElements::setThresholdRangeMin(
    const ScaledNumberElements &thresholdRangeMin) {
  m_thresholdRangeMin = thresholdRangeMin;
  m_thresholdRangeMinIsSet = true;
}

const ScaledNumberElements &
ThresholdConstraintsDataElements::getThresholdRangeMin() const {
  return m_thresholdRangeMin;
}

void ThresholdConstraintsDataElements::cleanThresholdRangeMin() {
  m_thresholdRangeMin = ScaledNumberElements();
  m_thresholdRangeMinIsSet = false;
}

bool ThresholdConstraintsDataElements::getThresholdRangeMinIsSet() const {
  return m_thresholdRangeMinIsSet;
}

void ThresholdConstraintsDataElements::setThresholdRangeMax(
    const ScaledNumberElements &thresholdRangeMax) {
  m_thresholdRangeMax = thresholdRangeMax;
  m_thresholdRangeMaxIsSet = true;
}

const ScaledNumberElements &
ThresholdConstraintsDataElements::getThresholdRangeMax() const {
  return m_thresholdRangeMax;
}

void ThresholdConstraintsDataElements::cleanThresholdRangeMax() {
  m_thresholdRangeMax = ScaledNumberElements();
  m_thresholdRangeMaxIsSet = false;
}

bool ThresholdConstraintsDataElements::getThresholdRangeMaxIsSet() const {
  return m_thresholdRangeMaxIsSet;
}

void ThresholdConstraintsDataElements::setThresholdStepSize(
    const ScaledNumberElements &thresholdStepSize) {
  m_thresholdStepSize = thresholdStepSize;
  m_thresholdStepSizeIsSet = true;
}

const ScaledNumberElements &
ThresholdConstraintsDataElements::getThresholdStepSize() const {
  return m_thresholdStepSize;
}

void ThresholdConstraintsDataElements::cleanThresholdStepSize() {
  m_thresholdStepSize = ScaledNumberElements();
  m_thresholdStepSizeIsSet = false;
}

bool ThresholdConstraintsDataElements::getThresholdStepSizeIsSet() const {
  return m_thresholdStepSizeIsSet;
}

bool ThresholdConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"thresholdId", "thresholdRangeMin", "thresholdRangeMax",
                   "thresholdStepSize"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thresholdId")) {
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

std::string ThresholdConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
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