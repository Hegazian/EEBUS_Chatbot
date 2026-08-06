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

#include <keo_datagram/setpoint/SetpointDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointDataElements::SetpointDataElements()
    : DataElements(), m_setpointIdIsSet(false), m_valueIsSet(false),
      m_value(ScaledNumberElements()), m_valueMinIsSet(false),
      m_valueMin(ScaledNumberElements()), m_valueMaxIsSet(false),
      m_valueMax(ScaledNumberElements()), m_valueToleranceAbsoluteIsSet(false),
      m_valueToleranceAbsolute(ScaledNumberElements()),
      m_valueTolerancePercentageIsSet(false),
      m_valueTolerancePercentage(ScaledNumberElements())

{}

bool SetpointDataElements::
operator==(const SetpointDataElements &c_classObject) const {
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet) {
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

bool SetpointDataElements::
operator!=(const SetpointDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointDataElements::isEmpty() const {
  return !m_setpointIdIsSet && !m_valueIsSet && !m_valueMinIsSet &&
         !m_valueMaxIsSet && !m_valueToleranceAbsoluteIsSet &&
         !m_valueTolerancePercentageIsSet;
}

DataElements::Type SetpointDataElements::getDataType() const {
  return DataElements::Type::SETPOINT_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SetpointDataElements::clone() const {
  return std::make_shared<SetpointDataElements>(*this);
}

void SetpointDataElements::setSetpointId() { m_setpointIdIsSet = true; }

void SetpointDataElements::cleanSetpointId() { m_setpointIdIsSet = false; }

bool SetpointDataElements::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

void SetpointDataElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &SetpointDataElements::getValue() const {
  return m_value;
}

void SetpointDataElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool SetpointDataElements::getValueIsSet() const { return m_valueIsSet; }

void SetpointDataElements::setValueMin(const ScaledNumberElements &valueMin) {
  m_valueMin = valueMin;
  m_valueMinIsSet = true;
}

const ScaledNumberElements &SetpointDataElements::getValueMin() const {
  return m_valueMin;
}

void SetpointDataElements::cleanValueMin() {
  m_valueMin = ScaledNumberElements();
  m_valueMinIsSet = false;
}

bool SetpointDataElements::getValueMinIsSet() const { return m_valueMinIsSet; }

void SetpointDataElements::setValueMax(const ScaledNumberElements &valueMax) {
  m_valueMax = valueMax;
  m_valueMaxIsSet = true;
}

const ScaledNumberElements &SetpointDataElements::getValueMax() const {
  return m_valueMax;
}

void SetpointDataElements::cleanValueMax() {
  m_valueMax = ScaledNumberElements();
  m_valueMaxIsSet = false;
}

bool SetpointDataElements::getValueMaxIsSet() const { return m_valueMaxIsSet; }

void SetpointDataElements::setValueToleranceAbsolute(
    const ScaledNumberElements &valueToleranceAbsolute) {
  m_valueToleranceAbsolute = valueToleranceAbsolute;
  m_valueToleranceAbsoluteIsSet = true;
}

const ScaledNumberElements &
SetpointDataElements::getValueToleranceAbsolute() const {
  return m_valueToleranceAbsolute;
}

void SetpointDataElements::cleanValueToleranceAbsolute() {
  m_valueToleranceAbsolute = ScaledNumberElements();
  m_valueToleranceAbsoluteIsSet = false;
}

bool SetpointDataElements::getValueToleranceAbsoluteIsSet() const {
  return m_valueToleranceAbsoluteIsSet;
}

void SetpointDataElements::setValueTolerancePercentage(
    const ScaledNumberElements &valueTolerancePercentage) {
  m_valueTolerancePercentage = valueTolerancePercentage;
  m_valueTolerancePercentageIsSet = true;
}

const ScaledNumberElements &
SetpointDataElements::getValueTolerancePercentage() const {
  return m_valueTolerancePercentage;
}

void SetpointDataElements::cleanValueTolerancePercentage() {
  m_valueTolerancePercentage = ScaledNumberElements();
  m_valueTolerancePercentageIsSet = false;
}

bool SetpointDataElements::getValueTolerancePercentageIsSet() const {
  return m_valueTolerancePercentageIsSet;
}

bool SetpointDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"setpointId", "value", "valueMin", "valueMax",
                   "valueToleranceAbsolute", "valueTolerancePercentage"})) {
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

std::string SetpointDataElements::toJson() const {
  std::string result = "[";
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setpointId");
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