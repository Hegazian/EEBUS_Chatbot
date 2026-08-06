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

#include <keo_datagram/hvac/HvacSystemFunctionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionDataElements::HvacSystemFunctionDataElements()
    : DataElements(), m_systemFunctionIdIsSet(false),
      m_currentOperationModeIdIsSet(false),
      m_isOperationModeIdChangeableIsSet(false),
      m_currentSetpointIdIsSet(false), m_isSetpointIdChangeableIsSet(false),
      m_isOverrunActiveIsSet(false)

{}

bool HvacSystemFunctionDataElements::
operator==(const HvacSystemFunctionDataElements &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet) {
    return false;
  }
  if (m_currentOperationModeIdIsSet !=
      c_classObject.m_currentOperationModeIdIsSet) {
    return false;
  }
  if (m_isOperationModeIdChangeableIsSet !=
      c_classObject.m_isOperationModeIdChangeableIsSet) {
    return false;
  }
  if (m_currentSetpointIdIsSet != c_classObject.m_currentSetpointIdIsSet) {
    return false;
  }
  if (m_isSetpointIdChangeableIsSet !=
      c_classObject.m_isSetpointIdChangeableIsSet) {
    return false;
  }
  if (m_isOverrunActiveIsSet != c_classObject.m_isOverrunActiveIsSet) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionDataElements::
operator!=(const HvacSystemFunctionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionDataElements::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_currentOperationModeIdIsSet &&
         !m_isOperationModeIdChangeableIsSet && !m_currentSetpointIdIsSet &&
         !m_isSetpointIdChangeableIsSet && !m_isOverrunActiveIsSet;
}

DataElements::Type HvacSystemFunctionDataElements::getDataType() const {
  return DataElements::Type::HVAC_SYSTEM_FUNCTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr HvacSystemFunctionDataElements::clone() const {
  return std::make_shared<HvacSystemFunctionDataElements>(*this);
}

void HvacSystemFunctionDataElements::setSystemFunctionId() {
  m_systemFunctionIdIsSet = true;
}

void HvacSystemFunctionDataElements::cleanSystemFunctionId() {
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionDataElements::getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionDataElements::setCurrentOperationModeId() {
  m_currentOperationModeIdIsSet = true;
}

void HvacSystemFunctionDataElements::cleanCurrentOperationModeId() {
  m_currentOperationModeIdIsSet = false;
}

bool HvacSystemFunctionDataElements::getCurrentOperationModeIdIsSet() const {
  return m_currentOperationModeIdIsSet;
}

void HvacSystemFunctionDataElements::setIsOperationModeIdChangeable() {
  m_isOperationModeIdChangeableIsSet = true;
}

void HvacSystemFunctionDataElements::cleanIsOperationModeIdChangeable() {
  m_isOperationModeIdChangeableIsSet = false;
}

bool HvacSystemFunctionDataElements::getIsOperationModeIdChangeableIsSet()
    const {
  return m_isOperationModeIdChangeableIsSet;
}

void HvacSystemFunctionDataElements::setCurrentSetpointId() {
  m_currentSetpointIdIsSet = true;
}

void HvacSystemFunctionDataElements::cleanCurrentSetpointId() {
  m_currentSetpointIdIsSet = false;
}

bool HvacSystemFunctionDataElements::getCurrentSetpointIdIsSet() const {
  return m_currentSetpointIdIsSet;
}

void HvacSystemFunctionDataElements::setIsSetpointIdChangeable() {
  m_isSetpointIdChangeableIsSet = true;
}

void HvacSystemFunctionDataElements::cleanIsSetpointIdChangeable() {
  m_isSetpointIdChangeableIsSet = false;
}

bool HvacSystemFunctionDataElements::getIsSetpointIdChangeableIsSet() const {
  return m_isSetpointIdChangeableIsSet;
}

void HvacSystemFunctionDataElements::setIsOverrunActive() {
  m_isOverrunActiveIsSet = true;
}

void HvacSystemFunctionDataElements::cleanIsOverrunActive() {
  m_isOverrunActiveIsSet = false;
}

bool HvacSystemFunctionDataElements::getIsOverrunActiveIsSet() const {
  return m_isOverrunActiveIsSet;
}

bool HvacSystemFunctionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "currentOperationModeId",
                   "isOperationModeIdChangeable", "currentSetpointId",
                   "isSetpointIdChangeable", "isOverrunActive"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "systemFunctionId")) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currentOperationModeId")) {
      m_currentOperationModeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isOperationModeIdChangeable")) {
      m_isOperationModeIdChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currentSetpointId")) {
      m_currentSetpointIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isSetpointIdChangeable")) {
      m_isSetpointIdChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isOverrunActive")) {
      m_isOverrunActiveIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionDataElements::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("systemFunctionId");
  }
  if (m_currentOperationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currentOperationModeId");
  }
  if (m_isOperationModeIdChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isOperationModeIdChangeable");
  }
  if (m_currentSetpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currentSetpointId");
  }
  if (m_isSetpointIdChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isSetpointIdChangeable");
  }
  if (m_isOverrunActiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isOverrunActive");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram