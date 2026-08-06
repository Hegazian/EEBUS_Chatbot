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

#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

OperatingConstraintsPowerDescriptionListDataSelectors::
    OperatingConstraintsPowerDescriptionListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0)

{}

OperatingConstraintsPowerDescriptionListDataSelectors::
    OperatingConstraintsPowerDescriptionListDataSelectors(
        const xs_unsignedInt &c_sequenceId) {
  setSequenceId(c_sequenceId);
}

bool OperatingConstraintsPowerDescriptionListDataSelectors::operator==(
    const OperatingConstraintsPowerDescriptionListDataSelectors &c_classObject)
    const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool OperatingConstraintsPowerDescriptionListDataSelectors::operator!=(
    const OperatingConstraintsPowerDescriptionListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool OperatingConstraintsPowerDescriptionListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet;
}

DataSelectors::Type
OperatingConstraintsPowerDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
OperatingConstraintsPowerDescriptionListDataSelectors::clone() const {
  return std::make_shared<
      OperatingConstraintsPowerDescriptionListDataSelectors>(*this);
}

void OperatingConstraintsPowerDescriptionListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
OperatingConstraintsPowerDescriptionListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void OperatingConstraintsPowerDescriptionListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool OperatingConstraintsPowerDescriptionListDataSelectors::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

bool OperatingConstraintsPowerDescriptionListDataSelectors::selects(
    const OperatingConstraintsPowerDescriptionData &data) const {
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() || getSequenceId() != data.getSequenceId())) {
    return false;
  }
  return true;
}

bool OperatingConstraintsPowerDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
OperatingConstraintsPowerDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram