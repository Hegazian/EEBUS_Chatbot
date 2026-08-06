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

#include <keo_datagram/setpoint/SetpointData.h>

#include <keo_datagram/setpoint/SetpointDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointData::SetpointData()
    : m_setpointIdIsSet(false), m_setpointId(0), m_valueIsSet(false),
      m_value(ScaledNumber()), m_valueMinIsSet(false),
      m_valueMin(ScaledNumber()), m_valueMaxIsSet(false),
      m_valueMax(ScaledNumber()), m_valueToleranceAbsoluteIsSet(false),
      m_valueToleranceAbsolute(ScaledNumber()),
      m_valueTolerancePercentageIsSet(false),
      m_valueTolerancePercentage(ScaledNumber())

{}

bool SetpointData::operator==(const SetpointData &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet ||
      (m_setpointIdIsSet && (m_setpointId != c_classObject.m_setpointId))) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }
  if (m_valueMinIsSet != c_classObject.m_valueMinIsSet ||
      (m_valueMinIsSet && (m_valueMin != c_classObject.m_valueMin))) {
    return false;
  }
  if (m_valueMaxIsSet != c_classObject.m_valueMaxIsSet ||
      (m_valueMaxIsSet && (m_valueMax != c_classObject.m_valueMax))) {
    return false;
  }
  if (m_valueToleranceAbsoluteIsSet !=
          c_classObject.m_valueToleranceAbsoluteIsSet ||
      (m_valueToleranceAbsoluteIsSet &&
       (m_valueToleranceAbsolute != c_classObject.m_valueToleranceAbsolute))) {
    return false;
  }
  if (m_valueTolerancePercentageIsSet !=
          c_classObject.m_valueTolerancePercentageIsSet ||
      (m_valueTolerancePercentageIsSet &&
       (m_valueTolerancePercentage !=
        c_classObject.m_valueTolerancePercentage))) {
    return false;
  }

  return true;
}

bool SetpointData::operator!=(const SetpointData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointData::isEmpty() const {
  return !m_setpointIdIsSet && !m_valueIsSet && !m_valueMinIsSet &&
         !m_valueMaxIsSet && !m_valueToleranceAbsoluteIsSet &&
         !m_valueTolerancePercentageIsSet;
}

void SetpointData::setSetpointId(const xs_unsignedInt &setpointId) {
  m_setpointId = setpointId;
  m_setpointIdIsSet = true;
}

const xs_unsignedInt &SetpointData::getSetpointId() const {
  return m_setpointId;
}

void SetpointData::cleanSetpointId() {
  m_setpointId = 0;
  m_setpointIdIsSet = false;
}

bool SetpointData::getSetpointIdIsSet() const { return m_setpointIdIsSet; }

void SetpointData::setValue(const ScaledNumber &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumber &SetpointData::getValue() const { return m_value; }

void SetpointData::cleanValue() {
  m_value = ScaledNumber();
  m_valueIsSet = false;
}

bool SetpointData::getValueIsSet() const { return m_valueIsSet; }

void SetpointData::setValueMin(const ScaledNumber &valueMin) {
  m_valueMin = valueMin;
  m_valueMinIsSet = true;
}

const ScaledNumber &SetpointData::getValueMin() const { return m_valueMin; }

void SetpointData::cleanValueMin() {
  m_valueMin = ScaledNumber();
  m_valueMinIsSet = false;
}

bool SetpointData::getValueMinIsSet() const { return m_valueMinIsSet; }

void SetpointData::setValueMax(const ScaledNumber &valueMax) {
  m_valueMax = valueMax;
  m_valueMaxIsSet = true;
}

const ScaledNumber &SetpointData::getValueMax() const { return m_valueMax; }

void SetpointData::cleanValueMax() {
  m_valueMax = ScaledNumber();
  m_valueMaxIsSet = false;
}

bool SetpointData::getValueMaxIsSet() const { return m_valueMaxIsSet; }

void SetpointData::setValueToleranceAbsolute(
    const ScaledNumber &valueToleranceAbsolute) {
  m_valueToleranceAbsolute = valueToleranceAbsolute;
  m_valueToleranceAbsoluteIsSet = true;
}

const ScaledNumber &SetpointData::getValueToleranceAbsolute() const {
  return m_valueToleranceAbsolute;
}

void SetpointData::cleanValueToleranceAbsolute() {
  m_valueToleranceAbsolute = ScaledNumber();
  m_valueToleranceAbsoluteIsSet = false;
}

bool SetpointData::getValueToleranceAbsoluteIsSet() const {
  return m_valueToleranceAbsoluteIsSet;
}

void SetpointData::setValueTolerancePercentage(
    const ScaledNumber &valueTolerancePercentage) {
  m_valueTolerancePercentage = valueTolerancePercentage;
  m_valueTolerancePercentageIsSet = true;
}

const ScaledNumber &SetpointData::getValueTolerancePercentage() const {
  return m_valueTolerancePercentage;
}

void SetpointData::cleanValueTolerancePercentage() {
  m_valueTolerancePercentage = ScaledNumber();
  m_valueTolerancePercentageIsSet = false;
}

bool SetpointData::getValueTolerancePercentageIsSet() const {
  return m_valueTolerancePercentageIsSet;
}

SetpointData SetpointData::reduce(const SetpointDataElements &elements) const {
  SetpointData dataOut;
  if (getSetpointIdIsSet() && elements.getSetpointIdIsSet()) {
    dataOut.setSetpointId(getSetpointId());
  }
  if (getValueIsSet() && elements.getValueIsSet()) {
    dataOut.setValue(getValue().reduce(elements.getValue()));
  }
  if (getValueMinIsSet() && elements.getValueMinIsSet()) {
    dataOut.setValueMin(getValueMin().reduce(elements.getValueMin()));
  }
  if (getValueMaxIsSet() && elements.getValueMaxIsSet()) {
    dataOut.setValueMax(getValueMax().reduce(elements.getValueMax()));
  }
  if (getValueToleranceAbsoluteIsSet() &&
      elements.getValueToleranceAbsoluteIsSet()) {
    dataOut.setValueToleranceAbsolute(getValueToleranceAbsolute().reduce(
        elements.getValueToleranceAbsolute()));
  }
  if (getValueTolerancePercentageIsSet() &&
      elements.getValueTolerancePercentageIsSet()) {
    dataOut.setValueTolerancePercentage(getValueTolerancePercentage().reduce(
        elements.getValueTolerancePercentage()));
  }
  return dataOut;
}

bool SetpointData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "value", "valueMin", "valueMax",
                   "valueToleranceAbsolute", "valueTolerancePercentage"})) {
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
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueMin", &m_valueMin)) {
      m_valueMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueMax", &m_valueMax)) {
      m_valueMaxIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueToleranceAbsolute",
                                   &m_valueToleranceAbsolute)) {
      m_valueToleranceAbsoluteIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueTolerancePercentage",
                                   &m_valueTolerancePercentage)) {
      m_valueTolerancePercentageIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SetpointData::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("setpointId", m_setpointId);
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  if (m_valueMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueMin", m_valueMin);
  }
  if (m_valueMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueMax", m_valueMax);
  }
  if (m_valueToleranceAbsoluteIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueToleranceAbsolute",
                                           m_valueToleranceAbsolute);
  }
  if (m_valueTolerancePercentageIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueTolerancePercentage",
                                           m_valueTolerancePercentage);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram