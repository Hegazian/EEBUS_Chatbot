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

#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationData.h>

#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionSetpointRelationData::HvacSystemFunctionSetpointRelationData()
    : m_systemFunctionIdIsSet(false), m_systemFunctionId(0),
      m_operationModeIdIsSet(false), m_operationModeId(0),
      m_setpointIdIsSet(false), m_setpointId(std::vector<xs_unsignedInt>())

{}

HvacSystemFunctionSetpointRelationData::HvacSystemFunctionSetpointRelationData(
    const xs_unsignedInt &c_systemFunctionId,
    const xs_unsignedInt &c_operationModeId,
    const std::vector<xs_unsignedInt> &c_setpointId)
    : m_systemFunctionIdIsSet(true), m_systemFunctionId(c_systemFunctionId),
      m_operationModeIdIsSet(true), m_operationModeId(c_operationModeId),
      m_setpointIdIsSet(true), m_setpointId(c_setpointId)

{}

bool HvacSystemFunctionSetpointRelationData::
operator==(const HvacSystemFunctionSetpointRelationData &c_classObject) const {
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
  if (m_setpointIdIsSet != c_classObject.m_setpointIdIsSet ||
      (m_setpointIdIsSet && (m_setpointId != c_classObject.m_setpointId))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionSetpointRelationData::
operator!=(const HvacSystemFunctionSetpointRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionSetpointRelationData::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_operationModeIdIsSet &&
         !m_setpointIdIsSet;
}

void HvacSystemFunctionSetpointRelationData::setSystemFunctionId(
    const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionSetpointRelationData::getSystemFunctionId() const {
  return m_systemFunctionId;
}

void HvacSystemFunctionSetpointRelationData::cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationData::getSystemFunctionIdIsSet() const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionSetpointRelationData::setOperationModeId(
    const xs_unsignedInt &operationModeId) {
  m_operationModeId = operationModeId;
  m_operationModeIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionSetpointRelationData::getOperationModeId() const {
  return m_operationModeId;
}

void HvacSystemFunctionSetpointRelationData::cleanOperationModeId() {
  m_operationModeId = 0;
  m_operationModeIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationData::getOperationModeIdIsSet() const {
  return m_operationModeIdIsSet;
}

void HvacSystemFunctionSetpointRelationData::setSetpointId(
    const std::vector<xs_unsignedInt> &setpointId) {
  m_setpointId = setpointId;
  m_setpointIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
HvacSystemFunctionSetpointRelationData::getSetpointId() const {
  return m_setpointId;
}

void HvacSystemFunctionSetpointRelationData::cleanSetpointId() {
  m_setpointId.clear();
  m_setpointIdIsSet = false;
}

bool HvacSystemFunctionSetpointRelationData::getSetpointIdIsSet() const {
  return m_setpointIdIsSet;
}

HvacSystemFunctionSetpointRelationData
HvacSystemFunctionSetpointRelationData::reduce(
    const HvacSystemFunctionSetpointRelationDataElements &elements) const {
  HvacSystemFunctionSetpointRelationData dataOut;
  if (getSystemFunctionIdIsSet() && elements.getSystemFunctionIdIsSet()) {
    dataOut.setSystemFunctionId(getSystemFunctionId());
  }
  if (getOperationModeIdIsSet() && elements.getOperationModeIdIsSet()) {
    dataOut.setOperationModeId(getOperationModeId());
  }
  if (getSetpointIdIsSet() && elements.getSetpointIdIsSet()) {
    dataOut.setSetpointId(getSetpointId());
  }
  return dataOut;
}

bool HvacSystemFunctionSetpointRelationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "operationModeId", "setpointId"})) {
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
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointId", &m_setpointId)) {
      m_setpointIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionSetpointRelationData::toJson() const {
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
  if (m_setpointIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("setpointId",
                                                               m_setpointId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram