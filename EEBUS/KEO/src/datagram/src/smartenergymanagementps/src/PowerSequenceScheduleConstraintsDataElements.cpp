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

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleConstraintsDataElements::
    PowerSequenceScheduleConstraintsDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_earliestStartTimeIsSet(false),
      m_latestStartTimeIsSet(false), m_earliestEndTimeIsSet(false),
      m_latestEndTimeIsSet(false), m_optionalSequenceIsSet(false)

{}

bool PowerSequenceScheduleConstraintsDataElements::operator==(
    const PowerSequenceScheduleConstraintsDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_earliestStartTimeIsSet != c_classObject.m_earliestStartTimeIsSet) {
    return false;
  }
  if (m_latestStartTimeIsSet != c_classObject.m_latestStartTimeIsSet) {
    return false;
  }
  if (m_earliestEndTimeIsSet != c_classObject.m_earliestEndTimeIsSet) {
    return false;
  }
  if (m_latestEndTimeIsSet != c_classObject.m_latestEndTimeIsSet) {
    return false;
  }
  if (m_optionalSequenceIsSet != c_classObject.m_optionalSequenceIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleConstraintsDataElements::operator!=(
    const PowerSequenceScheduleConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleConstraintsDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_earliestStartTimeIsSet &&
         !m_latestStartTimeIsSet && !m_earliestEndTimeIsSet &&
         !m_latestEndTimeIsSet && !m_optionalSequenceIsSet;
}

DataElements::Type
PowerSequenceScheduleConstraintsDataElements::getDataType() const {
  return DataElements::Type::
      POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequenceScheduleConstraintsDataElements::clone() const {
  return std::make_shared<PowerSequenceScheduleConstraintsDataElements>(*this);
}

void PowerSequenceScheduleConstraintsDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequenceScheduleConstraintsDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequenceScheduleConstraintsDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceScheduleConstraintsDataElements::setEarliestStartTime() {
  m_earliestStartTimeIsSet = true;
}

void PowerSequenceScheduleConstraintsDataElements::cleanEarliestStartTime() {
  m_earliestStartTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsDataElements::getEarliestStartTimeIsSet()
    const {
  return m_earliestStartTimeIsSet;
}

void PowerSequenceScheduleConstraintsDataElements::setLatestStartTime() {
  m_latestStartTimeIsSet = true;
}

void PowerSequenceScheduleConstraintsDataElements::cleanLatestStartTime() {
  m_latestStartTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsDataElements::getLatestStartTimeIsSet()
    const {
  return m_latestStartTimeIsSet;
}

void PowerSequenceScheduleConstraintsDataElements::setEarliestEndTime() {
  m_earliestEndTimeIsSet = true;
}

void PowerSequenceScheduleConstraintsDataElements::cleanEarliestEndTime() {
  m_earliestEndTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsDataElements::getEarliestEndTimeIsSet()
    const {
  return m_earliestEndTimeIsSet;
}

void PowerSequenceScheduleConstraintsDataElements::setLatestEndTime() {
  m_latestEndTimeIsSet = true;
}

void PowerSequenceScheduleConstraintsDataElements::cleanLatestEndTime() {
  m_latestEndTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsDataElements::getLatestEndTimeIsSet()
    const {
  return m_latestEndTimeIsSet;
}

void PowerSequenceScheduleConstraintsDataElements::setOptionalSequence() {
  m_optionalSequenceIsSet = true;
}

void PowerSequenceScheduleConstraintsDataElements::cleanOptionalSequence() {
  m_optionalSequenceIsSet = false;
}

bool PowerSequenceScheduleConstraintsDataElements::getOptionalSequenceIsSet()
    const {
  return m_optionalSequenceIsSet;
}

bool PowerSequenceScheduleConstraintsDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "earliestStartTime", "latestStartTime",
                   "earliestEndTime", "latestEndTime", "optionalSequence"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "earliestStartTime")) {
      m_earliestStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "latestStartTime")) {
      m_latestStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "earliestEndTime")) {
      m_earliestEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "latestEndTime")) {
      m_latestEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "optionalSequence")) {
      m_optionalSequenceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_earliestStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("earliestStartTime");
  }
  if (m_latestStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("latestStartTime");
  }
  if (m_earliestEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("earliestEndTime");
  }
  if (m_latestEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("latestEndTime");
  }
  if (m_optionalSequenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("optionalSequence");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram