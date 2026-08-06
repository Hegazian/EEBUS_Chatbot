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

#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceAlternativesRelationDataElements::
    PowerSequenceAlternativesRelationDataElements()
    : DataElements(), m_alternativesIdIsSet(false), m_sequenceIdIsSet(false)

{}

PowerSequenceAlternativesRelationDataElements::
    PowerSequenceAlternativesRelationDataElements(
        xs_boolean c_alternativesIdIsSet, xs_boolean c_sequenceIdIsSet)
    : DataElements(), m_alternativesIdIsSet(c_alternativesIdIsSet),
      m_sequenceIdIsSet(c_sequenceIdIsSet)

{}

bool PowerSequenceAlternativesRelationDataElements::operator==(
    const PowerSequenceAlternativesRelationDataElements &c_classObject) const {
  if (m_alternativesIdIsSet != c_classObject.m_alternativesIdIsSet) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceAlternativesRelationDataElements::operator!=(
    const PowerSequenceAlternativesRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceAlternativesRelationDataElements::isEmpty() const {
  return !m_alternativesIdIsSet && !m_sequenceIdIsSet;
}

DataElements::Type
PowerSequenceAlternativesRelationDataElements::getDataType() const {
  return DataElements::Type::
      POWER_SEQUENCE_ALTERNATIVES_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequenceAlternativesRelationDataElements::clone() const {
  return std::make_shared<PowerSequenceAlternativesRelationDataElements>(*this);
}

void PowerSequenceAlternativesRelationDataElements::setAlternativesId() {
  m_alternativesIdIsSet = true;
}

void PowerSequenceAlternativesRelationDataElements::cleanAlternativesId() {
  m_alternativesIdIsSet = false;
}

bool PowerSequenceAlternativesRelationDataElements::getAlternativesIdIsSet()
    const {
  return m_alternativesIdIsSet;
}

void PowerSequenceAlternativesRelationDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequenceAlternativesRelationDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequenceAlternativesRelationDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

bool PowerSequenceAlternativesRelationDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"alternativesId", "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "alternativesId")) {
      m_alternativesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceAlternativesRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_alternativesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("alternativesId");
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram