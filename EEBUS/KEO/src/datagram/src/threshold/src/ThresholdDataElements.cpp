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

#include <keo_datagram/threshold/ThresholdDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdDataElements::ThresholdDataElements()
    : DataElements(), m_thresholdIdIsSet(false), m_thresholdValueIsSet(false),
      m_thresholdValue(ScaledNumberElements())

{}

ThresholdDataElements::ThresholdDataElements(
    xs_boolean c_thresholdIdIsSet, const ScaledNumberElements &c_thresholdValue)
    : DataElements(), m_thresholdIdIsSet(c_thresholdIdIsSet),
      m_thresholdValueIsSet(true), m_thresholdValue(c_thresholdValue)

{}

bool ThresholdDataElements::
operator==(const ThresholdDataElements &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
    return false;
  }
  if (m_thresholdValueIsSet != c_classObject.m_thresholdValueIsSet ||
      (m_thresholdValueIsSet &&
       (m_thresholdValue != c_classObject.m_thresholdValue))) {
    return false;
  }

  return true;
}

bool ThresholdDataElements::
operator!=(const ThresholdDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdDataElements::isEmpty() const {
  return !m_thresholdIdIsSet && !m_thresholdValueIsSet;
}

DataElements::Type ThresholdDataElements::getDataType() const {
  return DataElements::Type::THRESHOLD_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ThresholdDataElements::clone() const {
  return std::make_shared<ThresholdDataElements>(*this);
}

void ThresholdDataElements::setThresholdId() { m_thresholdIdIsSet = true; }

void ThresholdDataElements::cleanThresholdId() { m_thresholdIdIsSet = false; }

bool ThresholdDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void ThresholdDataElements::setThresholdValue(
    const ScaledNumberElements &thresholdValue) {
  m_thresholdValue = thresholdValue;
  m_thresholdValueIsSet = true;
}

const ScaledNumberElements &ThresholdDataElements::getThresholdValue() const {
  return m_thresholdValue;
}

void ThresholdDataElements::cleanThresholdValue() {
  m_thresholdValue = ScaledNumberElements();
  m_thresholdValueIsSet = false;
}

bool ThresholdDataElements::getThresholdValueIsSet() const {
  return m_thresholdValueIsSet;
}

bool ThresholdDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"thresholdId", "thresholdValue"})) {
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
                                   "thresholdValue", &m_thresholdValue)) {
      m_thresholdValueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdDataElements::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
  }
  if (m_thresholdValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdValue", m_thresholdValue);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram