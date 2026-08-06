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

#include <keo_datagram/hvac/HvacSystemFunctionData.h>

#include <keo_datagram/hvac/HvacSystemFunctionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionData::HvacSystemFunctionData()
    : m_systemFunctionIdIsSet(false), m_systemFunctionId(0),
      m_currentOperationModeIdIsSet(false), m_currentOperationModeId(0),
      m_isOperationModeIdChangeableIsSet(false),
      m_isOperationModeIdChangeable(false), m_currentSetpointIdIsSet(false),
      m_currentSetpointId(0), m_isSetpointIdChangeableIsSet(false),
      m_isSetpointIdChangeable(false), m_isOverrunActiveIsSet(false),
      m_isOverrunActive(false)

{}

bool HvacSystemFunctionData::
operator==(const HvacSystemFunctionData &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }
  if (m_currentOperationModeIdIsSet !=
          c_classObject.m_currentOperationModeIdIsSet ||
      (m_currentOperationModeIdIsSet &&
       (m_currentOperationModeId != c_classObject.m_currentOperationModeId))) {
    return false;
  }
  if (m_isOperationModeIdChangeableIsSet !=
          c_classObject.m_isOperationModeIdChangeableIsSet ||
      (m_isOperationModeIdChangeableIsSet &&
       (m_isOperationModeIdChangeable !=
        c_classObject.m_isOperationModeIdChangeable))) {
    return false;
  }
  if (m_currentSetpointIdIsSet != c_classObject.m_currentSetpointIdIsSet ||
      (m_currentSetpointIdIsSet &&
       (m_currentSetpointId != c_classObject.m_currentSetpointId))) {
    return false;
  }
  if (m_isSetpointIdChangeableIsSet !=
          c_classObject.m_isSetpointIdChangeableIsSet ||
      (m_isSetpointIdChangeableIsSet &&
       (m_isSetpointIdChangeable != c_classObject.m_isSetpointIdChangeable))) {
    return false;
  }
  if (m_isOverrunActiveIsSet != c_classObject.m_isOverrunActiveIsSet ||
      (m_isOverrunActiveIsSet &&
       (m_isOverrunActive != c_classObject.m_isOverrunActive))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionData::
operator!=(const HvacSystemFunctionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionData::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_currentOperationModeIdIsSet &&
         !m_isOperationModeIdChangeableIsSet && !m_currentSetpointIdIsSet &&
         !m_isSetpointIdChangeableIsSet && !m_isOverrunActiveIsSet;
}

void HvacSystemFunctionData::setSystemFunctionId(
    const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &HvacSystemFunctionData::getSystemFunctionId() const {
  return m_systemFunctionId;
}

void HvacSystemFunctionData::cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionData::getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionData::setCurrentOperationModeId(
    const xs_unsignedInt &currentOperationModeId) {
  m_currentOperationModeId = currentOperationModeId;
  m_currentOperationModeIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionData::getCurrentOperationModeId() const {
  return m_currentOperationModeId;
}

void HvacSystemFunctionData::cleanCurrentOperationModeId() {
  m_currentOperationModeId = 0;
  m_currentOperationModeIdIsSet = false;
}

bool HvacSystemFunctionData::getCurrentOperationModeIdIsSet() const {
  return m_currentOperationModeIdIsSet;
}

void HvacSystemFunctionData::setIsOperationModeIdChangeable(
    const xs_boolean &isOperationModeIdChangeable) {
  m_isOperationModeIdChangeable = isOperationModeIdChangeable;
  m_isOperationModeIdChangeableIsSet = true;
}

const xs_boolean &
HvacSystemFunctionData::getIsOperationModeIdChangeable() const {
  return m_isOperationModeIdChangeable;
}

void HvacSystemFunctionData::cleanIsOperationModeIdChangeable() {
  m_isOperationModeIdChangeable = false;
  m_isOperationModeIdChangeableIsSet = false;
}

bool HvacSystemFunctionData::getIsOperationModeIdChangeableIsSet() const {
  return m_isOperationModeIdChangeableIsSet;
}

void HvacSystemFunctionData::setCurrentSetpointId(
    const xs_unsignedInt &currentSetpointId) {
  m_currentSetpointId = currentSetpointId;
  m_currentSetpointIdIsSet = true;
}

const xs_unsignedInt &HvacSystemFunctionData::getCurrentSetpointId() const {
  return m_currentSetpointId;
}

void HvacSystemFunctionData::cleanCurrentSetpointId() {
  m_currentSetpointId = 0;
  m_currentSetpointIdIsSet = false;
}

bool HvacSystemFunctionData::getCurrentSetpointIdIsSet() const {
  return m_currentSetpointIdIsSet;
}

void HvacSystemFunctionData::setIsSetpointIdChangeable(
    const xs_boolean &isSetpointIdChangeable) {
  m_isSetpointIdChangeable = isSetpointIdChangeable;
  m_isSetpointIdChangeableIsSet = true;
}

const xs_boolean &HvacSystemFunctionData::getIsSetpointIdChangeable() const {
  return m_isSetpointIdChangeable;
}

void HvacSystemFunctionData::cleanIsSetpointIdChangeable() {
  m_isSetpointIdChangeable = false;
  m_isSetpointIdChangeableIsSet = false;
}

bool HvacSystemFunctionData::getIsSetpointIdChangeableIsSet() const {
  return m_isSetpointIdChangeableIsSet;
}

void HvacSystemFunctionData::setIsOverrunActive(
    const xs_boolean &isOverrunActive) {
  m_isOverrunActive = isOverrunActive;
  m_isOverrunActiveIsSet = true;
}

const xs_boolean &HvacSystemFunctionData::getIsOverrunActive() const {
  return m_isOverrunActive;
}

void HvacSystemFunctionData::cleanIsOverrunActive() {
  m_isOverrunActive = false;
  m_isOverrunActiveIsSet = false;
}

bool HvacSystemFunctionData::getIsOverrunActiveIsSet() const {
  return m_isOverrunActiveIsSet;
}

HvacSystemFunctionData HvacSystemFunctionData::reduce(
    const HvacSystemFunctionDataElements &elements) const {
  HvacSystemFunctionData dataOut;
  if (getSystemFunctionIdIsSet() && elements.getSystemFunctionIdIsSet()) {
    dataOut.setSystemFunctionId(getSystemFunctionId());
  }
  if (getCurrentOperationModeIdIsSet() &&
      elements.getCurrentOperationModeIdIsSet()) {
    dataOut.setCurrentOperationModeId(getCurrentOperationModeId());
  }
  if (getIsOperationModeIdChangeableIsSet() &&
      elements.getIsOperationModeIdChangeableIsSet()) {
    dataOut.setIsOperationModeIdChangeable(getIsOperationModeIdChangeable());
  }
  if (getCurrentSetpointIdIsSet() && elements.getCurrentSetpointIdIsSet()) {
    dataOut.setCurrentSetpointId(getCurrentSetpointId());
  }
  if (getIsSetpointIdChangeableIsSet() &&
      elements.getIsSetpointIdChangeableIsSet()) {
    dataOut.setIsSetpointIdChangeable(getIsSetpointIdChangeable());
  }
  if (getIsOverrunActiveIsSet() && elements.getIsOverrunActiveIsSet()) {
    dataOut.setIsOverrunActive(getIsOverrunActive());
  }
  return dataOut;
}

bool HvacSystemFunctionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "currentOperationModeId",
                   "isOperationModeIdChangeable", "currentSetpointId",
                   "isSetpointIdChangeable", "isOverrunActive"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "systemFunctionId", &m_systemFunctionId)) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currentOperationModeId",
                                   &m_currentOperationModeId)) {
      m_currentOperationModeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isOperationModeIdChangeable",
                                   &m_isOperationModeIdChangeable)) {
      m_isOperationModeIdChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currentSetpointId", &m_currentSetpointId)) {
      m_currentSetpointIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isSetpointIdChangeable",
                                   &m_isSetpointIdChangeable)) {
      m_isSetpointIdChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isOverrunActive", &m_isOverrunActive)) {
      m_isOverrunActiveIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionData::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("systemFunctionId", m_systemFunctionId);
  }
  if (m_currentOperationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("currentOperationModeId",
                                           m_currentOperationModeId);
  }
  if (m_isOperationModeIdChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isOperationModeIdChangeable",
                                           m_isOperationModeIdChangeable);
  }
  if (m_currentSetpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("currentSetpointId", m_currentSetpointId);
  }
  if (m_isSetpointIdChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isSetpointIdChangeable",
                                           m_isSetpointIdChangeable);
  }
  if (m_isOverrunActiveIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("isOverrunActive", m_isOverrunActive);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram