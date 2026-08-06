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

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

AbsoluteOrRelativeTime::AbsoluteOrRelativeTime()
    : m_durationIsSet(false), m_duration(xs_duration()), m_dateTimeIsSet(false),
      m_dateTime(xs_dateTime())

{}

AbsoluteOrRelativeTime::AbsoluteOrRelativeTime(const xs_duration &c_duration)
    : AbsoluteOrRelativeTime() {
  m_durationIsSet = true;
  m_duration = c_duration;
}

AbsoluteOrRelativeTime::AbsoluteOrRelativeTime(const xs_dateTime &c_dateTime)
    : AbsoluteOrRelativeTime() {
  m_dateTimeIsSet = true;
  m_dateTime = c_dateTime;
}

bool AbsoluteOrRelativeTime::
operator==(const AbsoluteOrRelativeTime &c_classObject) const {
  if (m_durationIsSet != c_classObject.m_durationIsSet ||
      (m_durationIsSet && (m_duration != c_classObject.m_duration))) {
    return false;
  }
  if (m_dateTimeIsSet != c_classObject.m_dateTimeIsSet ||
      (m_dateTimeIsSet && (m_dateTime != c_classObject.m_dateTime))) {
    return false;
  }

  return true;
}

bool AbsoluteOrRelativeTime::
operator!=(const AbsoluteOrRelativeTime &c_classObject) const {
  return !(*this == c_classObject);
}

bool AbsoluteOrRelativeTime::isEmpty() const {
  return !m_durationIsSet && !m_dateTimeIsSet;
}

void AbsoluteOrRelativeTime::setDuration(const xs_duration &duration) {
  m_duration = duration;
  m_durationIsSet = true;
}

const xs_duration &AbsoluteOrRelativeTime::getDuration() const {
  return m_duration;
}

void AbsoluteOrRelativeTime::cleanDuration() {
  m_duration = xs_duration();
  m_durationIsSet = false;
}

bool AbsoluteOrRelativeTime::getDurationIsSet() const {
  return m_durationIsSet;
}

void AbsoluteOrRelativeTime::setDateTime(const xs_dateTime &dateTime) {
  m_dateTime = dateTime;
  m_dateTimeIsSet = true;
}

const xs_dateTime &AbsoluteOrRelativeTime::getDateTime() const {
  return m_dateTime;
}

void AbsoluteOrRelativeTime::cleanDateTime() {
  m_dateTime = xs_dateTime();
  m_dateTimeIsSet = false;
}

bool AbsoluteOrRelativeTime::getDateTimeIsSet() const {
  return m_dateTimeIsSet;
}

bool AbsoluteOrRelativeTime::isValid() const {
  return m_duration.isValid() || m_dateTime.isValid();
}

std::string AbsoluteOrRelativeTime::toString() const {
  if (m_duration.isValid()) {
    return m_duration.toString();
  }
  if (m_dateTime.isValid()) {
    return m_dateTime.toString();
  }
  return "";
}

AbsoluteOrRelativeTime
AbsoluteOrRelativeTime::fromString(const std::string &str) {
  KeoDuration duration = KeoDuration::parse(str);
  if (duration.isValid()) {
    return AbsoluteOrRelativeTime(duration);
  } else {
    KeoDateTime dateTime = KeoDateTime::parse(str);
    if (dateTime.isValid()) {
      return AbsoluteOrRelativeTime(dateTime);
    }
  }
  return AbsoluteOrRelativeTime();
}

bool AbsoluteOrRelativeTime::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"duration", "dateTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "duration", &m_duration)) {
      m_durationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "dateTime", &m_dateTime)) {
      m_dateTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string AbsoluteOrRelativeTime::toJson() const {
  std::string result = "[";
  if (m_durationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("duration", m_duration);
  }
  if (m_dateTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("dateTime", m_dateTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram