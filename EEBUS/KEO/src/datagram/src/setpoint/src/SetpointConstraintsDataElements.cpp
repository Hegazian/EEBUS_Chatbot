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

#include <keo_datagram/setpoint/SetpointConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointConstraintsDataElements::SetpointConstraintsDataElements()
    : DataElements(), m_setpointIdIsSet(false), m_setpointRangeMinIsSet(false),
      m_setpointRangeMin(ScaledNumberElements()),
      m_setpointRangeMaxIsSet(false),
      m_setpointRangeMax(ScaledNumberElements()),
      m_setpointStepSizeIsSet(false), m_setpointStepSize(ScaledNumberElements())

{}

bool SetpointConstraintsDataElements::
operator==(const SetpointConstraintsDataElements &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet) {
    return false;
  }
  if (m_setpointRangeMinIsSet != c_classObject.m_setpointRangeMinIsSet ||
      (m_setpointRangeMinIsSet &&
       (m_setpointRangeMin != c_classObject.m_setpointRangeMin))) {
    return false;
  }
  if (m_setpointRangeMaxIsSet != c_classObject.m_setpointRangeMaxIsSet ||
      (m_setpointRangeMaxIsSet &&
       (m_setpointRangeMax != c_classObject.m_setpointRangeMax))) {
    return false;
  }
  if (m_setpointStepSizeIsSet != c_classObject.m_setpointStepSizeIsSet ||
      (m_setpointStepSizeIsSet &&
       (m_setpointStepSize != c_classObject.m_setpointStepSize))) {
    return false;
  }

  return true;
}

bool SetpointConstraintsDataElements::
operator!=(const SetpointConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointConstraintsDataElements::isEmpty() const {
  return !m_setpointIdIsSet && !m_setpointRangeMinIsSet &&
         !m_setpointRangeMaxIsSet && !m_setpointStepSizeIsSet;
}

DataElements::Type SetpointConstraintsDataElements::getDataType() const {
  return DataElements::Type::SETPOINT_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SetpointConstraintsDataElements::clone() const {
  return std::make_shared<SetpointConstraintsDataElements>(*this);
}

void SetpointConstraintsDataElements::setSetpointId() {
  m_setpointIdIsSet = true;
}

void SetpointConstraintsDataElements::cleanSetpointId() {
  m_setpointIdIsSet = false;
}

bool SetpointConstraintsDataElements::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

void SetpointConstraintsDataElements::setSetpointRangeMin(
    const ScaledNumberElements &setpointRangeMin) {
  m_setpointRangeMin = setpointRangeMin;
  m_setpointRangeMinIsSet = true;
}

const ScaledNumberElements &
SetpointConstraintsDataElements::getSetpointRangeMin() const {
  return m_setpointRangeMin;
}

void SetpointConstraintsDataElements::cleanSetpointRangeMin() {
  m_setpointRangeMin = ScaledNumberElements();
  m_setpointRangeMinIsSet = false;
}

bool SetpointConstraintsDataElements::getSetpointRangeMinIsSet() const {
  return m_setpointRangeMinIsSet;
}

void SetpointConstraintsDataElements::setSetpointRangeMax(
    const ScaledNumberElements &setpointRangeMax) {
  m_setpointRangeMax = setpointRangeMax;
  m_setpointRangeMaxIsSet = true;
}

const ScaledNumberElements &
SetpointConstraintsDataElements::getSetpointRangeMax() const {
  return m_setpointRangeMax;
}

void SetpointConstraintsDataElements::cleanSetpointRangeMax() {
  m_setpointRangeMax = ScaledNumberElements();
  m_setpointRangeMaxIsSet = false;
}

bool SetpointConstraintsDataElements::getSetpointRangeMaxIsSet() const {
  return m_setpointRangeMaxIsSet;
}

void SetpointConstraintsDataElements::setSetpointStepSize(
    const ScaledNumberElements &setpointStepSize) {
  m_setpointStepSize = setpointStepSize;
  m_setpointStepSizeIsSet = true;
}

const ScaledNumberElements &
SetpointConstraintsDataElements::getSetpointStepSize() const {
  return m_setpointStepSize;
}

void SetpointConstraintsDataElements::cleanSetpointStepSize() {
  m_setpointStepSize = ScaledNumberElements();
  m_setpointStepSizeIsSet = false;
}

bool SetpointConstraintsDataElements::getSetpointStepSizeIsSet() const {
  return m_setpointStepSizeIsSet;
}

bool SetpointConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "setpointRangeMin", "setpointRangeMax",
                   "setpointStepSize"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "setpointId")) {
      m_setpointIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointRangeMin", &m_setpointRangeMin)) {
      m_setpointRangeMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointRangeMax", &m_setpointRangeMax)) {
      m_setpointRangeMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointStepSize", &m_setpointStepSize)) {
      m_setpointStepSizeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SetpointConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setpointId");
  }
  if (m_setpointRangeMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("setpointRangeMin", m_setpointRangeMin);
  }
  if (m_setpointRangeMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("setpointRangeMax", m_setpointRangeMax);
  }
  if (m_setpointStepSizeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("setpointStepSize", m_setpointStepSize);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram