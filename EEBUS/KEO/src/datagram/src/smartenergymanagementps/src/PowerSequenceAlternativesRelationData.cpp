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

#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceAlternativesRelationData::PowerSequenceAlternativesRelationData()
    : m_alternativesIdIsSet(false), m_alternativesId(0),
      m_sequenceIdIsSet(false), m_sequenceId(std::vector<xs_unsignedInt>())

{}

PowerSequenceAlternativesRelationData::PowerSequenceAlternativesRelationData(
    const xs_unsignedInt &c_alternativesId,
    const std::vector<xs_unsignedInt> &c_sequenceId)
    : m_alternativesIdIsSet(true), m_alternativesId(c_alternativesId),
      m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId)

{}

bool PowerSequenceAlternativesRelationData::
operator==(const PowerSequenceAlternativesRelationData &c_classObject) const {
  if (m_alternativesIdIsSet != c_classObject.m_alternativesIdIsSet ||
      (m_alternativesIdIsSet &&
       (m_alternativesId != c_classObject.m_alternativesId))) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool PowerSequenceAlternativesRelationData::
operator!=(const PowerSequenceAlternativesRelationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceAlternativesRelationData::isEmpty() const {
  return !m_alternativesIdIsSet && !m_sequenceIdIsSet;
}

void PowerSequenceAlternativesRelationData::setAlternativesId(
    const xs_unsignedInt &alternativesId) {
  m_alternativesId = alternativesId;
  m_alternativesIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceAlternativesRelationData::getAlternativesId() const {
  return m_alternativesId;
}

void PowerSequenceAlternativesRelationData::cleanAlternativesId() {
  m_alternativesId = 0;
  m_alternativesIdIsSet = false;
}

bool PowerSequenceAlternativesRelationData::getAlternativesIdIsSet() const {
  return m_alternativesIdIsSet;
}

void PowerSequenceAlternativesRelationData::setSequenceId(
    const std::vector<xs_unsignedInt> &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const std::vector<xs_unsignedInt> &
PowerSequenceAlternativesRelationData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceAlternativesRelationData::cleanSequenceId() {
  m_sequenceId.clear();
  m_sequenceIdIsSet = false;
}

bool PowerSequenceAlternativesRelationData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

PowerSequenceAlternativesRelationData
PowerSequenceAlternativesRelationData::reduce(
    const PowerSequenceAlternativesRelationDataElements &elements) const {
  PowerSequenceAlternativesRelationData dataOut;
  if (getAlternativesIdIsSet() && elements.getAlternativesIdIsSet()) {
    dataOut.setAlternativesId(getAlternativesId());
  }
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  return dataOut;
}

bool PowerSequenceAlternativesRelationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alternativesId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "alternativesId", &m_alternativesId)) {
      m_alternativesIdIsSet = true;
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

std::string PowerSequenceAlternativesRelationData::toJson() const {
  std::string result = "[";
  if (m_alternativesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alternativesId", m_alternativesId);
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