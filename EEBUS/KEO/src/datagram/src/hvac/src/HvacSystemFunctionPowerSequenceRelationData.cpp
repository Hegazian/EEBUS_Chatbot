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

#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationData.h>

#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionPowerSequenceRelationData::
    HvacSystemFunctionPowerSequenceRelationData()
    : m_systemFunctionIdIsSet(false), m_systemFunctionId(0),
      m_sequenceIdIsSet(false), m_sequenceId(std::vector<xs_unsignedInt>())

{}

HvacSystemFunctionPowerSequenceRelationData::
    HvacSystemFunctionPowerSequenceRelationData(
        const xs_unsignedInt &c_systemFunctionId,
        const std::vector<xs_unsignedInt> &c_sequenceId)
    : m_systemFunctionIdIsSet(true), m_systemFunctionId(c_systemFunctionId),
      m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId)

{}

bool HvacSystemFunctionPowerSequenceRelationData::operator==(
    const HvacSystemFunctionPowerSequenceRelationData &c_classObject) const {
  if (m_systemFunctionIdIsSet != c_classObject.m_systemFunctionIdIsSet ||
      (m_systemFunctionIdIsSet &&
       (m_systemFunctionId != c_classObject.m_systemFunctionId))) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionPowerSequenceRelationData::operator!=(
    const HvacSystemFunctionPowerSequenceRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionPowerSequenceRelationData::isEmpty() const {
  return !m_systemFunctionIdIsSet && !m_sequenceIdIsSet;
}

void HvacSystemFunctionPowerSequenceRelationData::setSystemFunctionId(
    const xs_unsignedInt &systemFunctionId) {
  m_systemFunctionId = systemFunctionId;
  m_systemFunctionIdIsSet = true;
}

const xs_unsignedInt &
HvacSystemFunctionPowerSequenceRelationData::getSystemFunctionId() const {
  return m_systemFunctionId;
}

void HvacSystemFunctionPowerSequenceRelationData::cleanSystemFunctionId() {
  m_systemFunctionId = 0;
  m_systemFunctionIdIsSet = false;
}

bool HvacSystemFunctionPowerSequenceRelationData::getSystemFunctionIdIsSet()
    const {
  return m_systemFunctionIdIsSet;
}

void HvacSystemFunctionPowerSequenceRelationData::setSequenceId(
    const std::vector<xs_unsignedInt> &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
HvacSystemFunctionPowerSequenceRelationData::getSequenceId() const {
  return m_sequenceId;
}

void HvacSystemFunctionPowerSequenceRelationData::cleanSequenceId() {
  m_sequenceId.clear();
  m_sequenceIdIsSet = false;
}

bool HvacSystemFunctionPowerSequenceRelationData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

HvacSystemFunctionPowerSequenceRelationData
HvacSystemFunctionPowerSequenceRelationData::reduce(
    const HvacSystemFunctionPowerSequenceRelationDataElements &elements) const {
  HvacSystemFunctionPowerSequenceRelationData dataOut;
  if (getSystemFunctionIdIsSet() && elements.getSystemFunctionIdIsSet()) {
    dataOut.setSystemFunctionId(getSystemFunctionId());
  }
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  return dataOut;
}

bool HvacSystemFunctionPowerSequenceRelationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"systemFunctionId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "systemFunctionId", &m_systemFunctionId)) {
      m_systemFunctionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionPowerSequenceRelationData::toJson() const {
  std::string result = "[";
  if (m_systemFunctionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("systemFunctionId", m_systemFunctionId);
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>("sequenceId",
                                                               m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram