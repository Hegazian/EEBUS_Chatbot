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

#include <keo_datagram/setpoint/SetpointConstraintsData.h>

#include <keo_datagram/setpoint/SetpointConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointConstraintsData::SetpointConstraintsData()
    : m_setpointIdIsSet(false), m_setpointId(0), m_setpointRangeMinIsSet(false),
      m_setpointRangeMin(ScaledNumber()), m_setpointRangeMaxIsSet(false),
      m_setpointRangeMax(ScaledNumber()), m_setpointStepSizeIsSet(false),
      m_setpointStepSize(ScaledNumber())

{}

bool SetpointConstraintsData::
operator==(const SetpointConstraintsData &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet ||
      (m_setpointIdIsSet && (m_setpointId != c_classObject.m_setpointId))) {
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

bool SetpointConstraintsData::
operator!=(const SetpointConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointConstraintsData::isEmpty() const {
  return !m_setpointIdIsSet && !m_setpointRangeMinIsSet &&
         !m_setpointRangeMaxIsSet && !m_setpointStepSizeIsSet;
}

void SetpointConstraintsData::setSetpointId(const xs_unsignedInt &setpointId) {
  m_setpointId = setpointId;
  m_setpointIdIsSet = true;
}

const xs_unsignedInt &SetpointConstraintsData::getSetpointId() const {
  return m_setpointId;
}

void SetpointConstraintsData::cleanSetpointId() {
  m_setpointId = 0;
  m_setpointIdIsSet = false;
}

bool SetpointConstraintsData::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

void SetpointConstraintsData::setSetpointRangeMin(
    const ScaledNumber &setpointRangeMin) {
  m_setpointRangeMin = setpointRangeMin;
  m_setpointRangeMinIsSet = true;
}

const ScaledNumber &SetpointConstraintsData::getSetpointRangeMin() const {
  return m_setpointRangeMin;
}

void SetpointConstraintsData::cleanSetpointRangeMin() {
  m_setpointRangeMin = ScaledNumber();
  m_setpointRangeMinIsSet = false;
}

bool SetpointConstraintsData::getSetpointRangeMinIsSet() const {
  return m_setpointRangeMinIsSet;
}

void SetpointConstraintsData::setSetpointRangeMax(
    const ScaledNumber &setpointRangeMax) {
  m_setpointRangeMax = setpointRangeMax;
  m_setpointRangeMaxIsSet = true;
}

const ScaledNumber &SetpointConstraintsData::getSetpointRangeMax() const {
  return m_setpointRangeMax;
}

void SetpointConstraintsData::cleanSetpointRangeMax() {
  m_setpointRangeMax = ScaledNumber();
  m_setpointRangeMaxIsSet = false;
}

bool SetpointConstraintsData::getSetpointRangeMaxIsSet() const {
  return m_setpointRangeMaxIsSet;
}

void SetpointConstraintsData::setSetpointStepSize(
    const ScaledNumber &setpointStepSize) {
  m_setpointStepSize = setpointStepSize;
  m_setpointStepSizeIsSet = true;
}

const ScaledNumber &SetpointConstraintsData::getSetpointStepSize() const {
  return m_setpointStepSize;
}

void SetpointConstraintsData::cleanSetpointStepSize() {
  m_setpointStepSize = ScaledNumber();
  m_setpointStepSizeIsSet = false;
}

bool SetpointConstraintsData::getSetpointStepSizeIsSet() const {
  return m_setpointStepSizeIsSet;
}

SetpointConstraintsData SetpointConstraintsData::reduce(
    const SetpointConstraintsDataElements &elements) const {
  SetpointConstraintsData dataOut;
  if (getSetpointIdIsSet() && elements.getSetpointIdIsSet()) {
    dataOut.setSetpointId(getSetpointId());
  }
  if (getSetpointRangeMinIsSet() && elements.getSetpointRangeMinIsSet()) {
    dataOut.setSetpointRangeMin(
        getSetpointRangeMin().reduce(elements.getSetpointRangeMin()));
  }
  if (getSetpointRangeMaxIsSet() && elements.getSetpointRangeMaxIsSet()) {
    dataOut.setSetpointRangeMax(
        getSetpointRangeMax().reduce(elements.getSetpointRangeMax()));
  }
  if (getSetpointStepSizeIsSet() && elements.getSetpointStepSizeIsSet()) {
    dataOut.setSetpointStepSize(
        getSetpointStepSize().reduce(elements.getSetpointStepSize()));
  }
  return dataOut;
}

bool SetpointConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "setpointRangeMin", "setpointRangeMax",
                   "setpointStepSize"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointId", &m_setpointId)) {
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

std::string SetpointConstraintsData::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("setpointId", m_setpointId);
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