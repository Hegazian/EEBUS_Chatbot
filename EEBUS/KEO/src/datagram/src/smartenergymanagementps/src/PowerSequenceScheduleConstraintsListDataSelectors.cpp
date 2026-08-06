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

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleConstraintsListDataSelectors::
    PowerSequenceScheduleConstraintsListDataSelectors()
    : DataSelectors(), m_sequenceIdIsSet(false), m_sequenceId(0)

{}

PowerSequenceScheduleConstraintsListDataSelectors::
    PowerSequenceScheduleConstraintsListDataSelectors(
        const xs_unsignedInt &c_sequenceId) {
  setSequenceId(c_sequenceId);
}

bool PowerSequenceScheduleConstraintsListDataSelectors::operator==(
    const PowerSequenceScheduleConstraintsListDataSelectors &c_classObject)
    const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleConstraintsListDataSelectors::operator!=(
    const PowerSequenceScheduleConstraintsListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleConstraintsListDataSelectors::isEmpty() const {
  return !m_sequenceIdIsSet;
}

DataSelectors::Type
PowerSequenceScheduleConstraintsListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
PowerSequenceScheduleConstraintsListDataSelectors::clone() const {
  return std::make_shared<PowerSequenceScheduleConstraintsListDataSelectors>(
      *this);
}

void PowerSequenceScheduleConstraintsListDataSelectors::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceScheduleConstraintsListDataSelectors::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceScheduleConstraintsListDataSelectors::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceScheduleConstraintsListDataSelectors::getSequenceIdIsSet()
    const {
  return m_sequenceIdIsSet;
}

bool PowerSequenceScheduleConstraintsListDataSelectors::selects(
    const PowerSequenceScheduleConstraintsData &data) const {
  if (getSequenceIdIsSet() &&
      (!data.getSequenceIdIsSet() || getSequenceId() != data.getSequenceId())) {
    return false;
  }
  return true;
}

bool PowerSequenceScheduleConstraintsListDataSelectors::fromJson(
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

std::string PowerSequenceScheduleConstraintsListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram