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

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceScheduleDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceScheduleData::PowerSequenceScheduleData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_startTimeIsSet(false),
      m_startTime(AbsoluteOrRelativeTime()), m_endTimeIsSet(false),
      m_endTime(AbsoluteOrRelativeTime())

{}

PowerSequenceScheduleData::PowerSequenceScheduleData(
    const xs_unsignedInt &c_sequenceId,
    const AbsoluteOrRelativeTime &c_startTime,
    const AbsoluteOrRelativeTime &c_endTime)
    : m_sequenceIdIsSet(true), m_sequenceId(c_sequenceId),
      m_startTimeIsSet(true), m_startTime(c_startTime), m_endTimeIsSet(true),
      m_endTime(c_endTime)

{}

bool PowerSequenceScheduleData::
operator==(const PowerSequenceScheduleData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_startTimeIsSet != c_classObject.m_startTimeIsSet ||
      (m_startTimeIsSet && (m_startTime != c_classObject.m_startTime))) {
    return false;
  }
  if (m_endTimeIsSet != c_classObject.m_endTimeIsSet ||
      (m_endTimeIsSet && (m_endTime != c_classObject.m_endTime))) {
    return false;
  }

  return true;
}

bool PowerSequenceScheduleData::
operator!=(const PowerSequenceScheduleData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceScheduleData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_startTimeIsSet && !m_endTimeIsSet;
}

void PowerSequenceScheduleData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &PowerSequenceScheduleData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceScheduleData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceScheduleData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceScheduleData::setStartTime(
    const AbsoluteOrRelativeTime &startTime) {
  m_startTime = startTime;
  m_startTimeIsSet = true;
}

const AbsoluteOrRelativeTime &PowerSequenceScheduleData::getStartTime() const {
  return m_startTime;
}

void PowerSequenceScheduleData::cleanStartTime() {
  m_startTime = AbsoluteOrRelativeTime();
  m_startTimeIsSet = false;
}

bool PowerSequenceScheduleData::getStartTimeIsSet() const {
  return m_startTimeIsSet;
}

void PowerSequenceScheduleData::setEndTime(
    const AbsoluteOrRelativeTime &endTime) {
  m_endTime = endTime;
  m_endTimeIsSet = true;
}

const AbsoluteOrRelativeTime &PowerSequenceScheduleData::getEndTime() const {
  return m_endTime;
}

void PowerSequenceScheduleData::cleanEndTime() {
  m_endTime = AbsoluteOrRelativeTime();
  m_endTimeIsSet = false;
}

bool PowerSequenceScheduleData::getEndTimeIsSet() const {
  return m_endTimeIsSet;
}

PowerSequenceScheduleData PowerSequenceScheduleData::reduce(
    const PowerSequenceScheduleDataElements &elements) const {
  PowerSequenceScheduleData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getStartTimeIsSet() && elements.getStartTimeIsSet()) {
    dataOut.setStartTime(getStartTime());
  }
  if (getEndTimeIsSet() && elements.getEndTimeIsSet()) {
    dataOut.setEndTime(getEndTime());
  }
  return dataOut;
}

bool PowerSequenceScheduleData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "startTime", "endTime"})) {
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
                                   "startTime", &m_startTime)) {
      m_startTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "endTime", &m_endTime)) {
      m_endTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceScheduleData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_startTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("startTime", m_startTime);
  }
  if (m_endTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("endTime", m_endTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram