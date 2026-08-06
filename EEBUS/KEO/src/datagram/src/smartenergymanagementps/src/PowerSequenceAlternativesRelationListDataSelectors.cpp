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

#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceAlternativesRelationListDataSelectors::
    PowerSequenceAlternativesRelationListDataSelectors()
    : DataSelectors(), m_alternativesIdIsSet(false), m_alternativesId(0),
      m_sequenceIdIsSet(false), m_sequenceId(0)

{}

PowerSequenceAlternativesRelationListDataSelectors::
    PowerSequenceAlternativesRelationListDataSelectors(
        const xs_unsignedInt &c_alternativesId,
        const xs_unsignedInt &c_sequenceId)
    : DataSelectors(), m_alternativesIdIsSet(true),
      m_alternativesId(c_alternativesId), m_sequenceIdIsSet(true),
      m_sequenceId(c_sequenceId)

{}

bool PowerSequenceAlternativesRelationListDataSelectors::operator==(
    const PowerSequenceAlternativesRelationListDataSelectors &c_classObject)
    const {
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

bool PowerSequenceAlternativesRelationListDataSelectors::operator!=(
    const PowerSequenceAlternativesRelationListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool PowerSequenceAlternativesRelationListDataSelectors::isEmpty() const {
  return !m_alternativesIdIsSet && !m_sequenceIdIsSet;
}

DataSelectors::Type
PowerSequenceAlternativesRelationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
PowerSequenceAlternativesRelationListDataSelectors::clone() const {
  return std::make_shared<PowerSequenceAlternativesRelationListDataSelectors>(
      *this);
}

void PowerSequenceAlternativesRelationListDataSelectors::setAlternativesId(
    const xs_unsignedInt &alternativesId) {
  m_alternativesId = alternativesId;
  m_alternativesIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceAlternativesRelationListDataSelectors::getAlternativesId() const {
  return m_alternativesId;
}

void PowerSequenceAlternativesRelationListDataSelectors::cleanAlternativesId() {
  m_alternativesId = 0;
  m_alternativesIdIsSet = false;
}

bool PowerSequenceAlternativesRelationListDataSelectors::
    getAlternativesIdIsSet() const {
  return m_alternativesIdIsSet;
}

void PowerSequenceAlternativesRelationListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceAlternativesRelationListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceAlternativesRelationListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceAlternativesRelationListDataSelectors::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

bool PowerSequenceAlternativesRelationListDataSelectors::selects(
    const PowerSequenceAlternativesRelationData &data) const {
  if (getAlternativesIdIsSet() &&
      (!data.getAlternativesIdIsSet() ||
       getAlternativesId() != data.getAlternativesId())) {
    return false;
  }
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() ||
       std::find(std::begin(data.getSequenceId()),
                 std::end(data.getSequenceId()),
                 getSequenceId()) == std::end(data.getSequenceId()))) {
    return false;
  }
  return true;
}

bool PowerSequenceAlternativesRelationListDataSelectors::fromJson(
    KeoJsonValue *json) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceAlternativesRelationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_alternativesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("alternativesId", m_alternativesId);
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram