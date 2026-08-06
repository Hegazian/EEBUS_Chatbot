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

#include <keo_datagram/actuator/ActuatorLevelDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorLevelDataElements::ActuatorLevelDataElements()
    : DataElements(), m_functionIsSet(false), m_valueIsSet(false),
      m_value(ScaledNumberElements())

{}

ActuatorLevelDataElements::ActuatorLevelDataElements(
    xs_boolean c_functionIsSet, const ScaledNumberElements &c_value)
    : DataElements(), m_functionIsSet(c_functionIsSet), m_valueIsSet(true),
      m_value(c_value)

{}

bool ActuatorLevelDataElements::
operator==(const ActuatorLevelDataElements &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet) {
    return false;
  }
  if (m_valueIsSet != c_classObject.m_valueIsSet ||
      (m_valueIsSet && (m_value != c_classObject.m_value))) {
    return false;
  }

  return true;
}

bool ActuatorLevelDataElements::
operator!=(const ActuatorLevelDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorLevelDataElements::isEmpty() const {
  return !m_functionIsSet && !m_valueIsSet;
}

DataElements::Type ActuatorLevelDataElements::getDataType() const {
  return DataElements::Type::ACTUATOR_LEVEL_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ActuatorLevelDataElements::clone() const {
  return std::make_shared<ActuatorLevelDataElements>(*this);
}

void ActuatorLevelDataElements::setFunction() { m_functionIsSet = true; }

void ActuatorLevelDataElements::cleanFunction() { m_functionIsSet = false; }

bool ActuatorLevelDataElements::getFunctionIsSet() const {
  return m_functionIsSet;
}

void ActuatorLevelDataElements::setValue(const ScaledNumberElements &value) {
  m_value = value;
  m_valueIsSet = true;
}

const ScaledNumberElements &ActuatorLevelDataElements::getValue() const {
  return m_value;
}

void ActuatorLevelDataElements::cleanValue() {
  m_value = ScaledNumberElements();
  m_valueIsSet = false;
}

bool ActuatorLevelDataElements::getValueIsSet() const { return m_valueIsSet; }

bool ActuatorLevelDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"function", "value"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "function")) {
      m_functionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "value", &m_value)) {
      m_valueIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ActuatorLevelDataElements::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("function");
  }
  if (m_valueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("value", m_value);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram