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

#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionOperationModeRelationDataElements::
    HvacSystemFunctionOperationModeRelationDataElements()
    : DataElements(), m_systemFunctionIdIsSet(false),
      m_operationModeIdIsSet(false)

{}

HvacSystemFunctionOperationModeRelationDataElements::
    HvacSystemFunctionOperationModeRelationDataElements(
        xs_boolean c_systemFunctionIdIsSet, xs_boolean c_operationModeIdIsSet)
    : DataElements(), m_systemFunctionIdIsSet(c_systemFunctionIdIsSet),
      m_operationModeIdIsSet(c_operationModeIdIsSet)

{}

bool HvacSystemFunctionOperationModeRelationDataElements::operator==(
    const HvacSystemFunctionOperationModeRelationDataElements &c_classObject)
    const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet) {
    return false;
  }
  if (m_operationModeIdIsSet != c_classObject.m_operationModeIdIsSet) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionOperationModeRelationDataElements::operator!=(
    const HvacSystemFunctionOperationModeRelationDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionOperationModeRelationDataElements::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_operationModeIdIsSet;
}

DataElements::Type
HvacSystemFunctionOperationModeRelationDataElements::getDataType() const {
  return DataElements::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
HvacSystemFunctionOperationModeRelationDataElements::clone() const {
  return std::make_shared<HvacSystemFunctionOperationModeRelationDataElements>(
      *this);
}

void HvacSystemFunctionOperationModeRelationDataElements::
    setSystemFunctionId() {
  m_systemFunctionIdIsSet = true;
}

void HvacSystemFunctionOperationModeRelationDataElements::
    cleanSystemFunctionId() {
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionOperationModeRelationDataElements::
    getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionOperationModeRelationDataElements::setOperationModeId() {
  m_operationModeIdIsSet = true;
}

void HvacSystemFunctionOperationModeRelationDataElements::
    cleanOperationModeId() {
  m_operationModeIdIsSet = false;
}

bool HvacSystemFunctionOperationModeRelationDataElements::
    getOperationModeIdIsSet() const {
  return m_operationModeIdIsSet;
}

bool HvacSystemFunctionOperationModeRelationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "operationModeId"})) {
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
  }
  return true;
}

std::string
HvacSystemFunctionOperationModeRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("systemFunctionId");
  }
  if (m_operationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("operationModeId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram