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

#include <keo_datagram/actuator/ActuatorSwitchDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ActuatorSwitchDataElements::ActuatorSwitchDataElements()
    : DataElements(), m_functionIsSet(false)

{}

ActuatorSwitchDataElements::ActuatorSwitchDataElements(
    const xs_boolean &c_functionIsSet) {
  if (c_functionIsSet) {
    setFunction();
  }
}

bool ActuatorSwitchDataElements::
operator==(const ActuatorSwitchDataElements &c_classObject) const {
  if (m_functionIsSet != c_classObject.m_functionIsSet) {
    return false;
  }

  return true;
}

bool ActuatorSwitchDataElements::
operator!=(const ActuatorSwitchDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ActuatorSwitchDataElements::isEmpty() const { return !m_functionIsSet; }

DataElements::Type ActuatorSwitchDataElements::getDataType() const {
  return DataElements::Type::ACTUATOR_SWITCH_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ActuatorSwitchDataElements::clone() const {
  return std::make_shared<ActuatorSwitchDataElements>(*this);
}

void ActuatorSwitchDataElements::setFunction() { m_functionIsSet = true; }

void ActuatorSwitchDataElements::cleanFunction() { m_functionIsSet = false; }

bool ActuatorSwitchDataElements::getFunctionIsSet() const {
  return m_functionIsSet;
}

bool ActuatorSwitchDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"function"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "function")) {
      m_functionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ActuatorSwitchDataElements::toJson() const {
  std::string result = "[";
  if (m_functionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("function");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram