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
 *  standard header files *
 * ******************************************************************************
 */

#include <chrono>
#include <iomanip>
#include <sstream>

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */

#include <keo_datagram/core/KeoDateTime.h>

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

KeoDateTime::KeoDateTime() : m_date(), m_time() {}

KeoDateTime::KeoDateTime(int32_t year, int32_t month, int32_t day, int32_t hour,
                         int32_t minute, int32_t second, int32_t milli)
    : m_date(year, month, day), m_time(hour, minute, second, milli) {}

KeoDateTime::KeoDateTime(const KeoDate &c_date, const KeoTime &c_time)
    : m_date(c_date), m_time(c_time) {}

bool KeoDateTime::isValid() const {
  return (m_date.isValid() && m_time.isValid());
}

bool KeoDateTime::isZero() const { return m_date.isZero() && m_time.isZero(); }

std::string KeoDateTime::toString() const {
  std::string result = m_date.toString();
  std::string timeString = m_time.toString();
  if (timeString.size()) {
    result += "T" + timeString;
  }
  return result;
}

uint16_t KeoDateTime::getYear() const { return m_date.getYear(); }

uint8_t KeoDateTime::getMonth() const { return m_date.getMonth(); }

uint8_t KeoDateTime::getDay() const { return m_date.getDay(); }

uint8_t KeoDateTime::getHour() const { return m_time.getHour(); }

uint8_t KeoDateTime::getMinute() const { return m_time.getMinute(); }

uint8_t KeoDateTime::getSecond() const { return m_time.getSecond(); }

uint16_t KeoDateTime::getMilliSecond() const { return m_time.getMilliSecond(); }

int64_t KeoDateTime::toSeconds() const {
  return m_date.toSeconds() + m_time.toSeconds();
}

int64_t KeoDateTime::toMilliSeconds() const {
  return toSeconds() * 1000 + m_time.getMilliSecond();
}

KeoDateTime KeoDateTime::addDuration(const KeoDuration &c_duration) const {
  if (!isValid() || !c_duration.isValid()) {
    return KeoDateTime();
  }

  int64_t milliSeconds =
      static_cast<int64_t>(m_time.toSeconds()) * 1000 + m_time.getMilliSecond();
  if (c_duration.isNegative()) {
    milliSeconds -= c_duration.getSeconds() * 1000;
    milliSeconds -= c_duration.getMilliSeconds();
  } else {
    milliSeconds += c_duration.getSeconds() * 1000;
    milliSeconds += c_duration.getMilliSeconds();
  }
  int64_t days = milliSeconds / 86400000;
  KeoDate newDate =
      KeoDate(m_date.getYear(), m_date.getMonth(), m_date.getDay());
  if (c_duration.isNegative()) {
    newDate = newDate.plusYears(-c_duration.getYears())
                  .plusMonths(-c_duration.getMonths())
                  .plusDays(-c_duration.getDays());
  } else {
    newDate = newDate.plusYears(c_duration.getYears())
                  .plusMonths(c_duration.getMonths())
                  .plusDays(c_duration.getDays());
  }
  if (milliSeconds < 0) {
    days--;
    milliSeconds = 86400000 + (milliSeconds % 86400000);
  }
  newDate = newDate.plusDays(days);
  KeoTime newTime = KeoTime::ofMilliSecondOfDay(milliSeconds);
  return KeoDateTime(newDate, newTime);
}

KeoDuration KeoDateTime::getDuration(const KeoDateTime &c_endDate) const {
  if (!isValid() || !c_endDate.isValid()) {
    return KeoDuration();
  }
  bool isNegative = false;
  int64_t durationSeconds = c_endDate.toSeconds() - toSeconds();
  int64_t durationMilliSeconds = c_endDate.getMilliSecond() - getMilliSecond();
  if (durationSeconds < 0) {
    durationSeconds = -durationSeconds;
    isNegative = true;
    if (durationMilliSeconds > 0) {
      durationSeconds--;
      durationMilliSeconds = 1000 - durationMilliSeconds;
    } else {
      durationMilliSeconds = -durationMilliSeconds;
    }
  } else {
    if (durationMilliSeconds < 0) {
      durationSeconds--;
      durationMilliSeconds = 1000 + durationMilliSeconds;
    }
  }
  return KeoDuration(durationSeconds, durationMilliSeconds, isNegative);
}

KeoDateTime KeoDateTime::parse(const std::string &c_value) {
  std::size_t found = c_value.find("T");
  if (found != std::string::npos && (found + 1 < c_value.size())) {
    return KeoDateTime(KeoDate::parse(c_value.substr(0, found)),
                       KeoTime::parse(c_value.substr(found + 1)));
  }
  return KeoDateTime();
}

KeoDateTime KeoDateTime::ofEpochMilliSeconds(int64_t c_totalMilliSeconds) {
  return KeoDateTime(KeoDate::ofEpochSeconds(c_totalMilliSeconds / 1000),
                     KeoTime::ofMilliSecondOfDay(c_totalMilliSeconds));
}

KeoDateTime KeoDateTime::now() {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::chrono::milliseconds milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          now.time_since_epoch());
  time_t tt = std::chrono::system_clock::to_time_t(now);
  std::tm tm;
  gmtime_r(&tt, &tm);

  return KeoDateTime(
      KeoDate(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday),
      KeoTime(tm.tm_hour, tm.tm_min, tm.tm_sec, milliseconds.count() % 1000));
}

bool KeoDateTime::operator==(const KeoDateTime &c_classObject) const {
  return (m_date == c_classObject.m_date) && (m_time == c_classObject.m_time);
}

bool KeoDateTime::operator!=(const KeoDateTime &c_classObject) const {
  return !(*this == c_classObject);
}

bool KeoDateTime::operator>(const KeoDateTime &c_classObject) const {
  if (m_date > c_classObject.m_date)
    return true;
  if (m_date < c_classObject.m_date)
    return false;
  if (m_time > c_classObject.m_time)
    return true;
  return false;
}

bool KeoDateTime::operator<(const KeoDateTime &c_classObject) const {
  return !(*this > c_classObject) && (*this != c_classObject);
}

bool KeoDateTime::operator>=(const KeoDateTime &c_classObject) const {
  return *this == c_classObject || *this > c_classObject;
}

bool KeoDateTime::operator<=(const KeoDateTime &c_classObject) const {
  return *this == c_classObject || *this < c_classObject;
}
}