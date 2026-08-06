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

#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionSetpointRelationListDataSelectors::
    HvacSystemFunctionSetpointRelationListDataSelectors()
    : DataSelectors(), m_systemFunctionIdIsSet(false), m_systemFunctionId(0),
      m_operationModeIdIsSet(false), m_operationModeId(0)

{}

HvacSystemFunctionSetpointRelationListDataSelectors::
    HvacSystemFunctionSetpointRelationListDataSelectors(
        const xs_unsignedInt &c_systemFunctionId,
        const xs_unsignedInt &c_operationModeId)
    : DataSelectors(), m_systemFunctionIdIsSet(true),
      m_systemFunctionId(c_systemFunctionId), m_operationModeIdIsSet(true),
      m_operationModeId(c_operationModeId)

{}

bool HvacSystemFunctionSetpointRelationListDataSelectors::operator==(
    const HvacSystemFunctionSetpointRelationListDataSelectors &c_classObject)
    const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }
  if (m_operationModeIdIsSet != c_classObject.m_operationModeIdIsSet ||
      (m_operationModeIdIsSet &&
       (m_operationModeId != c_classObject.m_operationModeId))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionSetpointRelationListDataSelectors::operator!=(
    const HvacSystemFunctionSetpointRelationListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionSetpointRelationListDataSelectors::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_operationModeIdIsSet;
}

DataSelectors::Type
HvacSystemFunctionSetpointRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
HvacSystemFunctionSetpointRelationListDataSelectors::clone() const {
  return std::make_shared<HvacSystemFunctionSetpointRelationListDataSelectors>(
      *this);
}

void HvacSystemFunctionSetpointRelationListDataSelectors::setSystemFunctionId(
    const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionSetpointRelationListDataSelectors::getSystemFunctionId()
    const {
  return m_systemFunctionId;
}

void HvacSystemFunctionSetpointRelationListDataSelectors::
    cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationListDataSelectors::
    getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionSetpointRelationListDataSelectors::setOperationModeId(
    const xs_unsignedInt &operationModeId) {
  m_operationModeId = operationModeId;
  m_operationModeIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionSetpointRelationListDataSelectors::getOperationModeId()
    const {
  return m_operationModeId;
}

void HvacSystemFunctionSetpointRelationListDataSelectors::
    cleanOperationModeId() {
  m_operationModeId = 0;
  m_operationModeIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationListDataSelectors::
    getOperationModeIdIsSet() const {
  return m_operationModeIdIsSet;
}

bool HvacSystemFunctionSetpointRelationListDataSelectors::selects(
    const HvacSystemFunctionSetpointRelationData &data) const {
  if (getSystemFunctionIdIsSet() &&
      (!data.getSystemFunctionIdIsSet() ||
       getSystemFunctionId() != data.getSystemFunctionId())) {
    return false;
  }
  if (getOperationModeIdIsSet() &&
      (!data.getOperationModeIdIsSet() ||
       getOperationModeId() != data.getOperationModeId())) {
    return false;
  }
  return true;
}

bool HvacSystemFunctionSetpointRelationListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "operationModeId"})) {
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
                                   "operationModeId", &m_operationModeId)) {
      m_operationModeIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
HvacSystemFunctionSetpointRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("systemFunctionId", m_systemFunctionId);
  }
  if (m_operationModeIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("operationModeId", m_operationModeId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram