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

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleConstraintsData::PowerSequenceScheduleConstraintsData()
    : m_sequenceIdIsSet(false), m_sequenceId(0),
      m_earliestStartTimeIsSet(false),
      m_earliestStartTime(AbsoluteOrRelativeTime()),
      m_latestStartTimeIsSet(false),
      m_latestStartTime(AbsoluteOrRelativeTime()),
      m_earliestEndTimeIsSet(false),
      m_earliestEndTime(AbsoluteOrRelativeTime()), m_latestEndTimeIsSet(false),
      m_latestEndTime(AbsoluteOrRelativeTime()), m_optionalSequenceIsSet(false),
      m_optionalSequence(false)

{}

bool PowerSequenceScheduleConstraintsData::
operator==(const PowerSequenceScheduleConstraintsData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_earliestStartTimeIsSet != c_classObject.m_earliestStartTimeIsSet ||
      (m_earliestStartTimeIsSet &&
       (m_earliestStartTime != c_classObject.m_earliestStartTime))) {
    return false;
  }
  if (m_latestStartTimeIsSet != c_classObject.m_latestStartTimeIsSet ||
      (m_latestStartTimeIsSet &&
       (m_latestStartTime != c_classObject.m_latestStartTime))) {
    return false;
  }
  if (m_earliestEndTimeIsSet != c_classObject.m_earliestEndTimeIsSet ||
      (m_earliestEndTimeIsSet &&
       (m_earliestEndTime != c_classObject.m_earliestEndTime))) {
    return false;
  }
  if (m_latestEndTimeIsSet != c_classObject.m_latestEndTimeIsSet ||
      (m_latestEndTimeIsSet &&
       (m_latestEndTime != c_classObject.m_latestEndTime))) {
    return false;
  }
  if (m_optionalSequenceIsSet != c_classObject.m_optionalSequenceIsSet ||
      (m_optionalSequenceIsSet &&
       (m_optionalSequence != c_classObject.m_optionalSequence))) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleConstraintsData::
operator!=(const PowerSequenceScheduleConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleConstraintsData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_earliestStartTimeIsSet &&
         !m_latestStartTimeIsSet && !m_earliestEndTimeIsSet &&
         !m_latestEndTimeIsSet && !m_optionalSequenceIsSet;
}

void PowerSequenceScheduleConstraintsData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &
PowerSequenceScheduleConstraintsData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceScheduleConstraintsData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceScheduleConstraintsData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceScheduleConstraintsData::setEarliestStartTime(
    const AbsoluteOrRelativeTime &earliestStartTime) {
  m_earliestStartTime = earliestStartTime;
  m_earliestStartTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerSequenceScheduleConstraintsData::getEarliestStartTime() const {
  return m_earliestStartTime;
}

void PowerSequenceScheduleConstraintsData::cleanEarliestStartTime() {
  m_earliestStartTime = AbsoluteOrRelativeTime();
  m_earliestStartTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsData::getEarliestStartTimeIsSet() const {
  return m_earliestStartTimeIsSet;
}

void PowerSequenceScheduleConstraintsData::setLatestStartTime(
    const AbsoluteOrRelativeTime &latestStartTime) {
  m_latestStartTime = latestStartTime;
  m_latestStartTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerSequenceScheduleConstraintsData::getLatestStartTime() const {
  return m_latestStartTime;
}

void PowerSequenceScheduleConstraintsData::cleanLatestStartTime() {
  m_latestStartTime = AbsoluteOrRelativeTime();
  m_latestStartTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsData::getLatestStartTimeIsSet() const {
  return m_latestStartTimeIsSet;
}

void PowerSequenceScheduleConstraintsData::setEarliestEndTime(
    const AbsoluteOrRelativeTime &earliestEndTime) {
  m_earliestEndTime = earliestEndTime;
  m_earliestEndTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerSequenceScheduleConstraintsData::getEarliestEndTime() const {
  return m_earliestEndTime;
}

void PowerSequenceScheduleConstraintsData::cleanEarliestEndTime() {
  m_earliestEndTime = AbsoluteOrRelativeTime();
  m_earliestEndTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsData::getEarliestEndTimeIsSet() const {
  return m_earliestEndTimeIsSet;
}

void PowerSequenceScheduleConstraintsData::setLatestEndTime(
    const AbsoluteOrRelativeTime &latestEndTime) {
  m_latestEndTime = latestEndTime;
  m_latestEndTimeIsSet = true;
}

const AbsoluteOrRelativeTime &
PowerSequenceScheduleConstraintsData::getLatestEndTime() const {
  return m_latestEndTime;
}

void PowerSequenceScheduleConstraintsData::cleanLatestEndTime() {
  m_latestEndTime = AbsoluteOrRelativeTime();
  m_latestEndTimeIsSet = false;
}

bool PowerSequenceScheduleConstraintsData::getLatestEndTimeIsSet() const {
  return m_latestEndTimeIsSet;
}

void PowerSequenceScheduleConstraintsData::setOptionalSequence(
    const xs_boolean &optionalSequence) {
  m_optionalSequence = optionalSequence;
  m_optionalSequenceIsSet = true;
}

const xs_boolean &
PowerSequenceScheduleConstraintsData::getOptionalSequence() const {
  return m_optionalSequence;
}

void PowerSequenceScheduleConstraintsData::cleanOptionalSequence() {
  m_optionalSequence = false;
  m_optionalSequenceIsSet = false;
}

bool PowerSequenceScheduleConstraintsData::getOptionalSequenceIsSet() const {
  return m_optionalSequenceIsSet;
}

PowerSequenceScheduleConstraintsData
PowerSequenceScheduleConstraintsData::reduce(
    const PowerSequenceScheduleConstraintsDataElements &elements) const {
  PowerSequenceScheduleConstraintsData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getEarliestStartTimeIsSet() && elements.getEarliestStartTimeIsSet()) {
    dataOut.setEarliestStartTime(getEarliestStartTime());
  }
  if (getLatestStartTimeIsSet() && elements.getLatestStartTimeIsSet()) {
    dataOut.setLatestStartTime(getLatestStartTime());
  }
  if (getEarliestEndTimeIsSet() && elements.getEarliestEndTimeIsSet()) {
    dataOut.setEarliestEndTime(getEarliestEndTime());
  }
  if (getLatestEndTimeIsSet() && elements.getLatestEndTimeIsSet()) {
    dataOut.setLatestEndTime(getLatestEndTime());
  }
  if (getOptionalSequenceIsSet() && elements.getOptionalSequenceIsSet()) {
    dataOut.setOptionalSequence(getOptionalSequence());
  }
  return dataOut;
}

bool PowerSequenceScheduleConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "earliestStartTime", "latestStartTime",
                   "earliestEndTime", "latestEndTime", "optionalSequence"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "earliestStartTime", &m_earliestStartTime)) {
      m_earliestStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "latestStartTime", &m_latestStartTime)) {
      m_latestStartTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "earliestEndTime", &m_earliestEndTime)) {
      m_earliestEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "latestEndTime", &m_latestEndTime)) {
      m_latestEndTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "optionalSequence", &m_optionalSequence)) {
      m_optionalSequenceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleConstraintsData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_earliestStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("earliestStartTime", m_earliestStartTime);
  }
  if (m_latestStartTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("latestStartTime", m_latestStartTime);
  }
  if (m_earliestEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("earliestEndTime", m_earliestEndTime);
  }
  if (m_latestEndTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("latestEndTime", m_latestEndTime);
  }
  if (m_optionalSequenceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("optionalSequence", m_optionalSequence);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram