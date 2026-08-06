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

#include <keo_datagram/threshold/ThresholdData.h>

#include <keo_datagram/threshold/ThresholdDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdData::ThresholdData()
    : m_thresholdIdIsSet(false), m_thresholdId(0), m_thresholdValueIsSet(false),
      m_thresholdValue(ScaledNumber())

{}

ThresholdData::ThresholdData(const xs_unsignedInt &c_thresholdId,
                             const ScaledNumber &c_thresholdValue)
    : m_thresholdIdIsSet(true), m_thresholdId(c_thresholdId),
      m_thresholdValueIsSet(true), m_thresholdValue(c_thresholdValue)

{}

bool ThresholdData::operator==(const ThresholdData &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }
  if (m_thresholdValueIsSet != c_classObject.m_thresholdValueIsSet ||
      (m_thresholdValueIsSet &&
       (m_thresholdValue != c_classObject.m_thresholdValue))) {
    return false;
  }

  return true;
}

bool ThresholdData::operator!=(const ThresholdData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdData::isEmpty() const {
  return !m_thresholdIdIsSet && !m_thresholdValueIsSet;
}

void ThresholdData::setThresholdId(const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &ThresholdData::getThresholdId() const {
  return m_thresholdId;
}

void ThresholdData::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool ThresholdData::getThresholdIdIsSet() const { return m_thresholdIdIsSet; }

void ThresholdData::setThresholdValue(const ScaledNumber &thresholdValue) {
  m_thresholdValue = thresholdValue;
  m_thresholdValueIsSet = true;
}

const ScaledNumber &ThresholdData::getThresholdValue() const {
  return m_thresholdValue;
}

void ThresholdData::cleanThresholdValue() {
  m_thresholdValue = ScaledNumber();
  m_thresholdValueIsSet = false;
}

bool ThresholdData::getThresholdValueIsSet() const {
  return m_thresholdValueIsSet;
}

ThresholdData
ThresholdData::reduce(const ThresholdDataElements &elements) const {
  ThresholdData dataOut;
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  if (getThresholdValueIsSet() && elements.getThresholdValueIsSet()) {
    dataOut.setThresholdValue(
        getThresholdValue().reduce(elements.getThresholdValue()));
  }
  return dataOut;
}

bool ThresholdData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"thresholdId", "thresholdValue"})) {
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
                                   "thresholdValue", &m_thresholdValue)) {
      m_thresholdValueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdData::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  if (m_thresholdValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdValue", m_thresholdValue);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram