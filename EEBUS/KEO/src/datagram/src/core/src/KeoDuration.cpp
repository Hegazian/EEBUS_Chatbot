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

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */

#include "KeoStringUtil.h"
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoDuration.h>

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>

/* ******************************************************************************
 * *
 *  defines *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  types *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  definition *
 * ******************************************************************************
 */
namespace keo_datagram {

KeoDuration::KeoDuration()
    : m_year(0), m_month(0), m_day(0), m_seconds(0), m_millis(0),
      m_isValid(false), m_isNegative(false), m_absoluteUTCSeconds(0) {}

KeoDuration::KeoDuration(std::string const &duration)
    : m_absoluteUTCSeconds(0) {
  KeoDuration temp = parse(duration);
  *this = temp;
}

KeoDuration::KeoDuration(uint64_t c_seconds, uint64_t c_millis,
                         bool c_isNegative)
    : m_year(0), m_month(0), m_day(0), m_isNegative(c_isNegative),
      m_absoluteUTCSeconds(0) {
  m_millis = c_millis % 1000;
  uint64_t allSeconds = c_seconds + (c_millis - m_millis) / 1000;
  m_seconds = allSeconds % 86400;
  m_day = static_cast<uint64_t>((allSeconds - m_seconds) / 86400);
  m_isValid = true;
}

KeoDuration::KeoDuration(uint32_t c_years, uint32_t c_months, uint64_t c_days,
                         uint64_t c_hours, uint64_t c_minutes,
                         uint64_t c_seconds, uint64_t c_millis,
                         bool c_isNegative)
    : m_year(c_years), m_month(c_months), m_isNegative(c_isNegative),
      m_absoluteUTCSeconds(0) {
  m_millis = c_millis % 1000;
  uint64_t allSeconds = c_hours * 3600 + c_minutes * 60 + c_seconds +
                        (c_millis - m_millis) / 1000;
  m_seconds = allSeconds % 86400;
  m_day = static_cast<uint64_t>(c_days + (allSeconds - m_seconds) / 86400);
  m_isValid = true;
}

bool KeoDuration::isValid() const { return m_isValid; }

bool KeoDuration::isZero() const {
  return m_year == 0 && m_month == 0 && m_day == 0 && m_seconds == 0 &&
         m_millis == 0;
}

bool KeoDuration::isNegative() const { return m_isNegative; }

void KeoDuration::setNegative(bool c_isNegative) {
  m_isNegative = c_isNegative;
}

uint32_t KeoDuration::getYears() const { return m_year; }

uint32_t KeoDuration::getMonths() const { return m_month; }

uint64_t KeoDuration::getDays() const { return m_day; }

uint64_t KeoDuration::getHours() const { return m_seconds / 3600; }

uint64_t KeoDuration::getMinutes() const { return m_seconds / 60; }

uint64_t KeoDuration::getSeconds() const { return m_seconds; }

uint64_t KeoDuration::getMilliSeconds() const { return m_millis; }

int64_t
KeoDuration::getAbsoluteMilliSeconds(const KeoDateTime &timestamp) const {
  KeoDateTime addedDurationTimestamp = timestamp.addDuration(*this);
  return addedDurationTimestamp.toMilliSeconds() - timestamp.toMilliSeconds();
}

int64_t KeoDuration::getAbsoluteSeconds(const KeoDateTime &timestamp) const {
  return getAbsoluteMilliSeconds(timestamp) / 1000;
}

int64_t KeoDuration::getAbsoluteSecondsSinceInternalTimestamp() const {
  return getAbsoluteSeconds(KeoDateTime::ofEpochMilliSeconds(
      static_cast<int64_t>(m_absoluteUTCSeconds) * 1000));
}

KeoDuration KeoDuration::ofSeconds(int32_t c_seconds) {
  bool isNegative = false;
  uint32_t seconds;
  if (c_seconds >= 0) {
    seconds = static_cast<uint32_t>(c_seconds);
  } else {
    seconds = static_cast<uint32_t>(-c_seconds);
    isNegative = true;
  }
  return KeoDuration(seconds, 0, isNegative);
}

KeoDuration KeoDuration::ofSeconds(uint32_t c_seconds, uint32_t c_millis) {
  return KeoDuration(c_seconds, c_millis);
}

KeoDuration KeoDuration::plus(const KeoDuration &c_duration) const {
  if (c_duration.getMonths() > 0 || c_duration.getYears() > 0) {
    return KeoDuration();
  }
  uint64_t seconds = c_duration.getDays() * 86400 + c_duration.getSeconds();
  KeoDuration result(*this);
  if (c_duration.isNegative()) {
    return result.plus(-seconds, -c_duration.getMilliSeconds());
  }
  return result.plus(seconds, c_duration.getMilliSeconds());
}

KeoDuration KeoDuration::plusDays(int32_t c_daysToAdd) const {
  int32_t daysToAdd = m_isNegative ? -c_daysToAdd : c_daysToAdd;
  return plus(static_cast<int64_t>(daysToAdd) * 86400, 0);
}

KeoDuration KeoDuration::plusHours(int32_t c_hoursToAdd) const {
  int32_t hoursToAdd = m_isNegative ? -c_hoursToAdd : c_hoursToAdd;
  return plus(hoursToAdd * 3600, 0);
}

KeoDuration KeoDuration::plusMinutes(int32_t c_minutesToAdd) const {
  int32_t minutesToAdd = m_isNegative ? -c_minutesToAdd : c_minutesToAdd;
  return plus(minutesToAdd * 60, 0);
}

KeoDuration KeoDuration::plusSeconds(int32_t c_secondsToAdd) const {
  int32_t secondsToAdd = m_isNegative ? -c_secondsToAdd : c_secondsToAdd;
  return plus(secondsToAdd, 0);
}

KeoDuration KeoDuration::plusMilliSeconds(int32_t c_millisToAdd) const {
  int32_t millisToAdd = m_isNegative ? -c_millisToAdd : c_millisToAdd;
  return plus(millisToAdd / 1000, millisToAdd % 1000);
}

KeoDuration KeoDuration::plus(int64_t c_secondsToAdd,
                              int32_t c_millisToAdd) const {
  if (!isValid()) {
    return KeoDuration();
  }
  int64_t secondsToAdd = m_isNegative ? -c_secondsToAdd : c_secondsToAdd;
  int32_t millisToAdd = m_isNegative ? -c_millisToAdd : c_millisToAdd;

  int32_t millis = m_millis + millisToAdd;
  int64_t seconds = m_day * 86400 + m_seconds + secondsToAdd;
  seconds += (millis / 1000);
  millis = millis % 1000;
  if (millis < 0) {
    seconds--;
    millis = 1000 + millis;
  }

  int64_t day = seconds / 86400;
  seconds = seconds % 86400;
  bool bIsNegative = m_isNegative;
  if (seconds < 0) {
    if (m_month > 0 || m_year > 0) {
      return KeoDuration();
    }
    bIsNegative = !m_isNegative;
    seconds = -seconds;
  }
  return KeoDuration(m_year, m_month, day, 0, 0, seconds, millis, bIsNegative);
}

KeoDuration KeoDuration::minus(const KeoDuration &c_duration) const {
  KeoDuration changedDuration(c_duration);
  changedDuration.setNegative(!changedDuration.isNegative());
  return plus(changedDuration);
}

KeoDuration KeoDuration::minusHours(int32_t c_hoursToSubtract) const {
  int32_t hoursToSubtract =
      m_isNegative ? c_hoursToSubtract : -c_hoursToSubtract;
  return plusHours(hoursToSubtract);
}

KeoDuration KeoDuration::minusMinutes(int32_t c_minutesToSubtract) const {
  int32_t minutesToSubtract =
      m_isNegative ? c_minutesToSubtract : -c_minutesToSubtract;
  return plusMinutes(minutesToSubtract);
}

KeoDuration KeoDuration::minusSeconds(int32_t c_secondsToSubtract) const {
  int32_t secondsToSubtract =
      m_isNegative ? c_secondsToSubtract : -c_secondsToSubtract;
  return plusSeconds(secondsToSubtract);
}

KeoDuration KeoDuration::minusMilliSeconds(int32_t c_millisToSubtract) const {
  int32_t millisToSubtract =
      m_isNegative ? c_millisToSubtract : -c_millisToSubtract;
  return plusMilliSeconds(millisToSubtract);
}

KeoDuration KeoDuration::minus(int64_t c_secondsToSubtract,
                               int32_t c_millisToSubtract) const {
  return plus(-c_secondsToSubtract, -c_millisToSubtract);
}

time_t KeoDuration::getAbsoluteUTCTimestamp() const {
  return m_absoluteUTCSeconds;
}

void KeoDuration::setAbsoluteUTCTimestamp(time_t c_absoluteTimestamp) {
  m_absoluteUTCSeconds = c_absoluteTimestamp;
}

KeoDuration KeoDuration::parse(const std::string &c_value) {
  if (c_value.length() < 2) {
    return KeoDuration();
  }

  bool isNegative = false;
  std::size_t start = 0;
  if (c_value.at(0) != 'P') {
    if (c_value.at(0) != '-' || c_value.at(1) != 'P') {
      return KeoDuration();
    }
    isNegative = true;
    start = 1;
  }
  int32_t year = 0;
  int32_t month = 0;
  int32_t day = 0;
  int64_t second = 0;
  int32_t milli = 0;

  std::string datePart;
  std::size_t end = 0;
  if ((end = c_value.find('T')) == std::string::npos) {
    datePart = c_value;
  } else {
    datePart = c_value.substr(start, end);
  }
  size_t oldIndex = 1;
  bool hasDate = false;
  size_t index = datePart.find('Y');

  if (index != std::string::npos) {
    try {
      year = KeoStringUtil::toInt32(datePart.substr(oldIndex, index).c_str());
    } catch (std::invalid_argument &e) {
      return KeoDuration();
    }
    oldIndex = index + 1;
    hasDate = true;
  }

  index = datePart.find('M', oldIndex);
  if (index != std::string::npos) {
    try {
      month = KeoStringUtil::toInt32(datePart.substr(oldIndex, index).c_str());
    } catch (std::invalid_argument &e) {
      return KeoDuration();
    }
    oldIndex = index + 1;
    hasDate = true;
  }

  index = datePart.find('D', oldIndex);
  if (index != std::string::npos) {
    try {
      day = KeoStringUtil::toInt32(datePart.substr(oldIndex, index).c_str());
    } catch (std::invalid_argument &e) {
      return KeoDuration();
    }
    oldIndex = index + 1;
    hasDate = true;
  }

  if (end == std::string::npos) {
    if (hasDate) {
      return KeoDuration(year, month, day, 0, 0, 0, 0);
    } else {
      return KeoDuration();
    }
  }
  std::string timePart = c_value.substr(end + 1);
  bool hasTime = false;
  if (timePart.length() > 0) {
    oldIndex = 0;

    index = timePart.find('H');
    if (index != std::string::npos) {
      try {
        second =
            KeoStringUtil::toInt32(timePart.substr(oldIndex, index).c_str()) *
            3600;
      } catch (std::invalid_argument &e) {
        return KeoDuration();
      }
      oldIndex = index + 1;
      hasTime = true;
    }

    index = timePart.find('M', oldIndex);
    if (index != std::string::npos) {
      try {
        second +=
            KeoStringUtil::toInt32(timePart.substr(oldIndex, index).c_str()) *
            60;
      } catch (std::invalid_argument &e) {
        return KeoDuration();
      }
      oldIndex = index + 1;
      hasTime = true;
    }

    index = timePart.find('.', oldIndex);
    if (index != std::string::npos) {
      size_t milliIndex = timePart.find('S', index);
      try {
        milli = KeoStringUtil::toUint32(
            timePart.substr(index + 1, milliIndex - index - 1).c_str());
      } catch (std::invalid_argument &e) {
        return KeoDuration();
      }
      for (size_t i = 1; i < 5 - milliIndex + index; i++) {
        milli *= 10;
      }
      hasTime = true;
    } else {
      index = timePart.find('S', oldIndex);
    }

    if (index != std::string::npos) {
      try {
        second += KeoStringUtil::toInt32(
            timePart.substr(oldIndex, index - oldIndex).c_str());
      } catch (std::invalid_argument &e) {
        return KeoDuration();
      }
      hasTime = true;
    }
  }
  if (hasDate || hasTime) {
    return KeoDuration(year, month, day, 0, 0, second, milli, isNegative);
  }
  return KeoDuration();
}

bool KeoDuration::operator==(const KeoDuration &c_classObject) const {
  // Assumption: invalid instances cannot be equal to anything
  if (!this->isValid() || !c_classObject.isValid())
    return false;
  if (this->m_isNegative != c_classObject.m_isNegative)
    return false;

  if (this->m_year != c_classObject.m_year)
    return false;
  if (this->m_month != c_classObject.m_month)
    return false;
  if (this->m_day != c_classObject.m_day)
    return false;
  if (this->m_seconds != c_classObject.m_seconds)
    return false;
  if (this->m_millis != c_classObject.m_millis)
    return false;
  return true;
}

bool KeoDuration::operator!=(const KeoDuration &c_classObject) const {
  return !(*this == c_classObject);
}

bool KeoDuration::operator>(const KeoDuration &c_classObject) const {
  if (this->m_isNegative != c_classObject.m_isNegative)
    return c_classObject.m_isNegative;
  int comp = this->m_year - c_classObject.m_year;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = this->m_month - c_classObject.m_month;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = this->m_day - c_classObject.m_day;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = this->m_seconds - c_classObject.m_seconds;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = this->m_millis - c_classObject.m_millis;
  if (comp > 0)
    return true;
  return false;
}

bool KeoDuration::operator<(const KeoDuration &c_classObject) const {
  return !(*this > c_classObject) && (*this != c_classObject);
}

std::string KeoDuration::toString() const {
  if (!isValid()) {
    return "";
  }
  if (isZero()) {
    return "PT0S";
  }
  std::stringstream result;
  if (isNegative()) {
    result << "-";
  }
  result << "P";
  if (m_year != 0) {
    result << m_year << "Y";
  }
  if (m_month != 0) {
    result << m_month << "M";
  }
  if (m_day != 0) {
    result << m_day << "D";
  }
  if (m_seconds == 0 && m_millis == 0) {
    std::string resultStr = result.str();
    if (resultStr.length() > 2) {
      return resultStr;
    }
    return "PT0S";
  }
  result << "T";

  int32_t hours = static_cast<int32_t>(m_seconds % 86400L / 3600L);
  if (hours != 0L) {
    result << hours << 'H';
  }
  int32_t minutes = static_cast<int32_t>(m_seconds % 3600L / 60L);
  if (minutes != 0L) {
    result << minutes << 'M';
  }
  int32_t sec = static_cast<int32_t>(m_seconds % 60L);
  if (sec == 0 && m_millis == 0) {
    std::string resultStr = result.str();
    if (resultStr.length() > 2) {
      return resultStr;
    }
    return "PT0S";
  }
  if ((sec < 0) && (m_millis > 0)) {
    if (sec == -1) {
      result << "-0";
    } else {
      result << (sec + 1);
    }
  } else {
    result << sec;
  }
  if (m_millis > 0) {
    std::stringstream milliResult;
    if (sec < 0) {
      milliResult << (2000 - m_millis);
    } else {
      milliResult << (m_millis + 1000);
    }
    std::string milliResultStr = milliResult.str();
    std::string::reverse_iterator iterZero = milliResultStr.rbegin();
    std::string::reverse_iterator iterZeroEnd = milliResultStr.rend();
    size_t length = iterZeroEnd - iterZero - 1;
    for (; iterZero != iterZeroEnd; iterZero++) {
      if (*iterZero != '0') {
        length = iterZeroEnd - iterZero - 1;
        break;
      }
    }
    result << '.' << milliResultStr.substr(1, length);
  }
  result << 'S';
  return result.str();
}
}