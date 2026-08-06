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

#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionSetpointRelationDataElements::
    HvacSystemFunctionSetpointRelationDataElements()
    : DataElements(), m_systemFunctionIdIsSet(false),
      m_operationModeIdIsSet(false), m_setpointIdIsSet(false)

{}

HvacSystemFunctionSetpointRelationDataElements::
    HvacSystemFunctionSetpointRelationDataElements(
        xs_boolean c_systemFunctionIdIsSet, xs_boolean c_operationModeIdIsSet,
        xs_boolean c_setpointIdIsSet)
    : DataElements(), m_systemFunctionIdIsSet(c_systemFunctionIdIsSet),
      m_operationModeIdIsSet(c_operationModeIdIsSet),
      m_setpointIdIsSet(c_setpointIdIsSet)

{}

bool HvacSystemFunctionSetpointRelationDataElements::operator==(
    const HvacSystemFunctionSetpointRelationDataElements &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet) {
    return false;
  }
  if (m_operationModeIdIsSet != c_classObject.m_operationModeIdIsSet) {
    return false;
  }
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionSetpointRelationDataElements::operator!=(
    const HvacSystemFunctionSetpointRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionSetpointRelationDataElements::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_operationModeIdIsSet &&
         !m_setpointIdIsSet;
}

DataElements::Type
HvacSystemFunctionSetpointRelationDataElements::getDataType() const {
  return DataElements::Type::
      HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr HvacSystemFunctionSetpointRelationDataElements::clone() const {
  return std::make_shared<HvacSystemFunctionSetpointRelationDataElements>(
      *this);
}

void HvacSystemFunctionSetpointRelationDataElements::setSystemFunctionId() {
  m_systemFunctionIdIsSet = true;
}

void HvacSystemFunctionSetpointRelationDataElements::cleanSystemFunctionId() {
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationDataElements::getSystemFunctionIdIsSet()
    const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionSetpointRelationDataElements::setOperationModeId() {
  m_operationModeIdIsSet = true;
}

void HvacSystemFunctionSetpointRelationDataElements::cleanOperationModeId() {
  m_operationModeIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationDataElements::getOperationModeIdIsSet()
    const {
  return m_operationModeIdIsSet;
}

void HvacSystemFunctionSetpointRelationDataElements::setSetpointId() {
  m_setpointIdIsSet = true;
}

void HvacSystemFunctionSetpointRelationDataElements::cleanSetpointId() {
  m_setpointIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationDataElements::getSetpointIdIsSet()
    const {
  return m_setpointIdIsSet;
}

bool HvacSystemFunctionSetpointRelationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "operationModeId", "setpointId"})) {
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
                                     "operationModeId")) {
      m_operationModeIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "setpointId")) {
      m_setpointIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionSetpointRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("systemFunctionId");
  }
  if (m_operationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("operationModeId");
  }
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setpointId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram