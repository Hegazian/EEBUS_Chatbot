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
#include <keo_datagram/core/KeoDate.h>
#include <keo_datagram/core/KeoDateTime.h>
#include <keo_datagram/core/KeoTime.h>

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

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

class KeoTime::KeoTimePriv {
public:
  KeoTimePriv()
      : m_hour(0), m_minute(0), m_second(0), m_milli(0), m_isValid(false) {}

  KeoTimePriv(int32_t c_hour, int32_t c_minute, int32_t c_second,
              int32_t c_milli)
      : m_hour(c_hour), m_minute(c_minute), m_second(c_second),
        m_milli(c_milli), m_isValid(true) {
    if ((c_hour >= 0 && c_minute >= 0 && c_second >= 0 && c_milli >= 0) &&
        ((c_hour == 24 && c_minute == 0 && c_second == 0 &&
          c_milli == 0) // 24:00:00
         || (c_hour <= 23 && c_minute <= 59 &&
             c_second <= 59))) { // Any other time of day
      m_hour = c_hour;
      m_minute = c_minute;
      m_second = c_second;
      m_milli = c_milli;
    } else {
      m_hour = 0;
      m_minute = 0;
      m_second = 0;
      m_milli = 0;
      m_isValid = false;
    }
  }

public:
  uint8_t m_hour;
  uint8_t m_minute;
  uint8_t m_second;
  uint16_t m_milli;
  bool m_isValid;
};

KeoTime::KeoTime() : d(new KeoTimePriv()) {}

KeoTime::KeoTime(const KeoTime &time) {
  if (time.isValid()) {
    d = new KeoTimePriv(time.d->m_hour, time.d->m_minute, time.d->m_second,
                        time.d->m_milli);
  } else {
    d = new KeoTimePriv();
  }
}

KeoTime::KeoTime(int32_t c_hour, int32_t c_minute, int32_t c_second,
                 int32_t c_milli)
    : d(new KeoTimePriv(c_hour, c_minute, c_second, c_milli)) {}

KeoTime::~KeoTime() { delete d; }

bool KeoTime::isValid() const { return d->m_isValid; }

bool KeoTime::isZero() const {
  return d->m_hour == 0 && d->m_minute == 0 && d->m_second == 0 &&
         d->m_milli == 0;
}

std::string KeoTime::toString() const {
  if (!isValid()) {
    return std::string();
  }

  std::stringstream result;
  result << std::setfill('0') << std::setw(2) << static_cast<int>(d->m_hour)
         << ":" << std::setfill('0') << std::setw(2)
         << static_cast<int>(d->m_minute) << ":" << std::setfill('0')
         << std::setw(2) << static_cast<int>(d->m_second);
  if (d->m_milli > 0) {
    result << "." << std::setfill('0') << std::setw(3)
           << static_cast<int>(d->m_milli % 1000);
  }
  result << "Z";
  return result.str();
}

uint64_t KeoTime::toSeconds() const {
  if (!isValid()) {
    return 0;
  }

  int32_t allSeconds = static_cast<int32_t>(d->m_hour) * 3600;
  allSeconds += static_cast<int32_t>(d->m_minute) * 60;
  return allSeconds + d->m_second;
}

uint8_t KeoTime::getHour() const { return d->m_hour; }

uint8_t KeoTime::getMinute() const { return d->m_minute; }

uint8_t KeoTime::getSecond() const { return d->m_second; }

uint16_t KeoTime::getMilliSecond() const { return d->m_milli; }

KeoTime KeoTime::plusHours(int32_t c_hoursToAdd) const {
  if (!isValid()) {
    return KeoTime();
  }

  if (c_hoursToAdd == 0) {
    return KeoTime(d->m_hour, d->m_minute, d->m_second, d->m_milli);
  }
  return KeoTime((d->m_hour + c_hoursToAdd) % 24, d->m_minute, d->m_second,
                 d->m_milli);
}

KeoTime KeoTime::plusMinutes(int32_t c_minutesToAdd) const {
  if (!isValid()) {
    return KeoTime();
  }

  if (c_minutesToAdd == 0) {
    return KeoTime(d->m_hour, d->m_minute, d->m_second, d->m_milli);
  }
  int32_t allMinutes = static_cast<int32_t>(d->m_hour) * 60 + d->m_minute;
  int32_t addMinutes =
      (static_cast<int32_t>(c_minutesToAdd % 1440) + allMinutes + 1440) % 1440;
  if (allMinutes == addMinutes) {
    return KeoTime(d->m_hour, d->m_minute, d->m_second, d->m_milli);
  }
  int32_t hour = addMinutes / 60;
  int32_t minutes = addMinutes % 60;
  return KeoTime(hour, minutes, d->m_second, d->m_milli);
}

KeoTime KeoTime::plusSeconds(int32_t c_secondsToAdd) const {
  if (!isValid()) {
    return KeoTime();
  }

  if (c_secondsToAdd == 0) {
    return KeoTime(d->m_hour, d->m_minute, d->m_second, d->m_milli);
  }
  int32_t allSeconds = static_cast<int32_t>(d->m_hour) * 3600 +
                       static_cast<int32_t>(d->m_minute) * 60 + d->m_second;
  int32_t addSeconds =
      (static_cast<int32_t>(c_secondsToAdd % 86400) + allSeconds + 86400) %
      86400;
  if (allSeconds == addSeconds) {
    return KeoTime(d->m_hour, d->m_minute, d->m_second, d->m_milli);
  }
  int32_t hour = addSeconds / 3600;
  int32_t minute = addSeconds / 60 % 60;
  int32_t second = addSeconds % 60;
  return KeoTime(hour, minute, second, d->m_milli);
}

KeoTime KeoTime::parse(const std::string &c_value) {
  if (c_value.empty() || c_value.back() != 'Z') {
    return KeoTime();
  }
  std::size_t start = 0, end = 0;
  int index = 0;
  int32_t hour = 0, minute = 0, second = 0, millisecond = 0;
  while ((end = c_value.find(':', start)) != std::string::npos) {
    if (index == 0) {
      try {
        hour =
            KeoStringUtil::toUint32(c_value.substr(start, end - start).c_str());
      } catch (std::invalid_argument &e) {
        return KeoTime();
      }
      index++;
      start = end + 1;
      continue;
    }
    if (index == 1) {
      try {
        minute =
            KeoStringUtil::toUint32(c_value.substr(start, end - start).c_str());
      } catch (std::invalid_argument &e) {
        return KeoTime();
      }
      index++;
      start = end + 1;
      continue;
    }
  }
  if (index != 2) {
    return KeoTime();
  }
  if ((end = c_value.find('.', start)) != std::string::npos) {
    try {
      second =
          KeoStringUtil::toUint32(c_value.substr(start, end - start).c_str());
      millisecond = KeoStringUtil::toUint32(
          c_value.substr(end + 1, c_value.length() - end).c_str());
    } catch (std::invalid_argument &e) {
      return KeoTime();
    }
  } else {
    try {
      second = KeoStringUtil::toUint32(
          c_value.substr(start, c_value.length() - start - 1).c_str());
    } catch (std::invalid_argument &e) {
      return KeoTime();
    }
  }
  // TODO check instead of "." -> "+" or "-" ???
  return KeoTime(hour, minute, second, millisecond);
}

KeoTime KeoTime::ofMilliSecondOfDay(int64_t c_totalMilliSeconds) {
  int64_t totalMilliSeconds = c_totalMilliSeconds % 86400000;
  int32_t hour = static_cast<int32_t>(totalMilliSeconds / 3600000);
  int32_t minute = static_cast<int32_t>(
      (totalMilliSeconds -= static_cast<int64_t>(hour * 3600000)) / 60000);
  int32_t seconds = static_cast<int32_t>(
      (totalMilliSeconds -= static_cast<int64_t>(minute * 60000)) / 1000);
  return KeoTime(hour, minute, seconds,
                 static_cast<int32_t>(totalMilliSeconds -=
                                      static_cast<int64_t>(seconds * 1000)));
}

KeoTime KeoTime::now() {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::chrono::milliseconds milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          now.time_since_epoch());
  time_t tt = std::chrono::system_clock::to_time_t(now);
  std::tm tm;
  gmtime_r(&tt, &tm);

  return KeoTime(tm.tm_hour, tm.tm_min, tm.tm_sec, milliseconds.count() % 1000);
}

KeoTime &KeoTime::operator=(const KeoTime &rhs) {
  if (this != &rhs) {
    *d = *rhs.d;
  }
  return *this;
}

bool KeoTime::operator==(const KeoTime &c_classObject) const {
  if (d->m_hour != c_classObject.d->m_hour)
    return false;
  if (d->m_minute != c_classObject.d->m_minute)
    return false;
  if (d->m_second != c_classObject.d->m_second)
    return false;
  if (d->m_milli != c_classObject.d->m_milli)
    return false;
  return true;
}

bool KeoTime::operator!=(const KeoTime &c_classObject) const {
  return !(*this == c_classObject);
}

bool KeoTime::operator>(const KeoTime &c_classObject) const {
  int comp = d->m_hour - c_classObject.d->m_hour;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = d->m_minute - c_classObject.d->m_minute;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = d->m_second - c_classObject.d->m_second;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = d->m_milli - c_classObject.d->m_milli;
  if (comp > 0)
    return true;
  return false;
}

bool KeoTime::operator<(const KeoTime &c_classObject) const {
  return !(*this > c_classObject) && (*this != c_classObject);
}

bool KeoTime::operator>=(const KeoTime &c_classObject) const {
  return *this == c_classObject || *this > c_classObject;
}

bool KeoTime::operator<=(const KeoTime &c_classObject) const {
  return *this == c_classObject || *this < c_classObject;
}

} // namespace keo_datagram