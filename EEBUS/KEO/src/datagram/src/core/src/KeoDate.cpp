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

const int32_t arrayDaysInMonth[] = {31, 28, 31, 30, 31, 30,
                                    31, 31, 30, 31, 30, 31};

class KeoDate::KeoDatePriv {
public:
  KeoDatePriv() : m_year(0), m_month(0), m_day(0), m_isValid(false) {}

  KeoDatePriv(uint32_t c_year, uint32_t c_month, uint32_t c_day)
      : m_year(0), m_month(0), m_day(0), m_isValid(false) {
    if (c_year >= 1 && c_year < 2222 && c_month >= 1 && c_month <= 12 &&
        c_day >= 1 && c_day <= 31) {
      int32_t year = static_cast<int32_t>(c_year);
      int32_t month = static_cast<int32_t>(c_month);
      int32_t day = static_cast<int32_t>(c_day);
      if (!correctDate(year, month, day)) {
        // This only creates a valid instance if the date that has been passed
        // in, was not changed (i.e. because
        // of wrap-around or a leap year).
        m_year = static_cast<uint16_t>(year);
        m_month = static_cast<uint8_t>(month);
        m_day = static_cast<uint8_t>(day);
        m_isValid = true;
      }
    }
  }

public:
  uint16_t m_year;
  uint8_t m_month;
  uint8_t m_day;
  bool m_isValid;

  /**
   * Checks whether a date is valid or not. A date is valid if its parts (year,
   * month and day) are within valid ranges
   * considering leap years.
   * @return true, if the date was invalid and has been changed
   */
  bool correctDate(int32_t &r_year, int32_t &r_month, int32_t &r_day) const {
    if (r_year < 1 || r_month < 1 || r_day < 1) {
      r_day = 0;
      r_month = 0;
      r_year = 0;
      return true;
    } else {
      int32_t day = r_day;
      int32_t month = r_month;
      int32_t year = r_year;
      bool needToCorrect = false;
      if (day > 365) {
        int32_t addYear = day / 365;
        int32_t yearCounter = month > 2 ? year + 1 : year;
        while (addYear) {
          day -= isLeapYear(yearCounter) ? 366 : 365;
          if (day < 1) {
            day += isLeapYear(yearCounter) ? 366 : 365;
            break;
          }
          year++;
          yearCounter++;
          addYear--;
        }
        needToCorrect = true;
      }
      int32_t addMonth = 0;
      if (day > 31) {
        addMonth = day / 31;
        needToCorrect = true;
      }
      if (month + addMonth > 12) {
        year += (month - 1 + addMonth) / 12;
        month = ((month - 1) % 12) + 1;
        needToCorrect = true;
      }
      while (addMonth) {
        day -= daysInMonth(month - 1, year);
        month++;
        addMonth--;
      }
      if (day > daysInMonth(month - 1, year)) {
        day -= daysInMonth(month - 1, year);
        month++;
        needToCorrect = true;
      }
      r_year = year;
      r_month = (((month - 1) % 12) + 1);
      r_day = day;
      return needToCorrect;
    }
  }

  int daysInMonth(uint32_t c_month, uint32_t c_year) const {
    if (c_month > 11) {
      return 0;
    }
    if (c_month == 1) {
      return isLeapYear(c_year) ? 29 : 28;
    }
    return arrayDaysInMonth[c_month];
  }

  bool isLeapYear(uint32_t c_year) const {
    return (c_year % 4 == 0) && ((c_year % 100 != 0) || (c_year % 400 == 0));
  }

  KeoDate minusMonths(int c_monthsToSubtract) const {
    int32_t year = m_year - (c_monthsToSubtract / 12);
    int32_t month = m_month - (c_monthsToSubtract % 12);
    if (month < 1) {
      year -= 1;
      month += 12;
    }
    int32_t day = m_day;
    correctDate(year, month, day);
    return KeoDate(year, month, day);
  }

  KeoDate minusDays(int32_t c_daysToSubtract) const {
    int32_t year = m_year - (c_daysToSubtract / 365);
    c_daysToSubtract = (c_daysToSubtract % 365);
    int32_t minusMonth = 0;

    if (c_daysToSubtract > 31) {
      minusMonth = c_daysToSubtract / 31;
    }

    if (m_month - minusMonth < 1) {
      year -= minusMonth / 12;
    }

    int32_t month = m_month;
    while (minusMonth) {
      int32_t monthSub = month - 2;
      if (monthSub < 0)
        monthSub = 11;
      c_daysToSubtract -= daysInMonth(monthSub, year);
      month--;
      minusMonth--;
    }

    if (month < 1) {
      month += 12;
      year -= 1;
    }

    int32_t day = m_day - c_daysToSubtract;

    if (day < 1) {
      month--;
      if (month < 1) {
        month += 12;
        year -= 1;
      }
      day += daysInMonth(month - 1, year);
    }
    correctDate(year, month, day);
    return KeoDate(year, month, day);
  }
};

KeoDate::KeoDate() : d(new KeoDatePriv()) {}

KeoDate::KeoDate(uint32_t c_year, uint32_t c_month, uint32_t c_day)
    : d(new KeoDatePriv(c_year, c_month, c_day)) {}

KeoDate::KeoDate(const KeoDate &date) {
  if (date.isValid()) {
    d = new KeoDatePriv(date.d->m_year, date.d->m_month, date.d->m_day);
  } else {
    d = new KeoDatePriv();
  }
}

KeoDate::~KeoDate() { delete d; }

bool KeoDate::isValid() const { return d->m_isValid; }

bool KeoDate::isZero() const {
  return d->m_year == 0 && d->m_month == 0 && d->m_day == 0;
}

std::string KeoDate::toString() const {
  if (!isValid()) {
    return "";
  }

  std::stringstream result;
  result << d->m_year << (d->m_month < 10 ? "-0" : "-")
         << static_cast<int32_t>(d->m_month) << (d->m_day < 10 ? "-0" : "-")
         << static_cast<int32_t>(d->m_day);
  return result.str();
}

uint64_t KeoDate::toSeconds() const {
  if (!isValid()) {
    return 0;
  }

  int32_t addYear = d->m_year - 1970;
  int32_t year = 1970;
  int32_t days = 0;
  while (addYear > 0) {
    days += d->isLeapYear(year) ? 366 : 365;
    year++;
    addYear--;
  }
  for (int i = 0; i < d->m_month - 1; i++) {
    days += d->daysInMonth(i, d->m_year);
  }
  return (days + d->m_day - 1) * 86400;
}

uint16_t KeoDate::getYear() const { return d->m_year; }

uint8_t KeoDate::getMonth() const { return d->m_month; }

uint8_t KeoDate::getDay() const { return d->m_day; }

bool KeoDate::isLeapYear() const { return d->isLeapYear(d->m_year); }

KeoDate KeoDate::plusYears(int32_t c_yearsToAdd) const {
  if (!isValid()) {
    return KeoDate();
  }

  if (0 == c_yearsToAdd) {
    return KeoDate(d->m_year, d->m_month, d->m_day);
  }
  return KeoDate(d->m_year + c_yearsToAdd, d->m_month, d->m_day);
}

KeoDate KeoDate::plusMonths(int32_t c_monthsToAdd) const {
  if (!isValid()) {
    return KeoDate();
  }

  if (0 == c_monthsToAdd) {
    return KeoDate(d->m_year, d->m_month, d->m_day);
  }

  if (c_monthsToAdd >= 0) {
    int64_t allMonths = static_cast<int64_t>(d->m_year) * 12 +
                        static_cast<int64_t>(d->m_month - 1);
    int64_t addMonths = allMonths + c_monthsToAdd;
    int32_t newYear = static_cast<int32_t>(addMonths / 12);
    int32_t newMonth = static_cast<int32_t>(addMonths % 12) + 1;
    int32_t day = d->m_day;
    d->correctDate(newYear, newMonth, day);

    return KeoDate(newYear, newMonth, day);
  } else {
    return d->minusMonths((-1) * c_monthsToAdd);
  }
}

KeoDate KeoDate::plusDays(int32_t c_daysToAdd) const {
  if (!isValid()) {
    return KeoDate();
  }

  if (0 == c_daysToAdd) {
    return KeoDate(d->m_year, d->m_month, d->m_day);
  }

  if (c_daysToAdd >= 0) {
    int32_t year = d->m_year;
    int32_t month = d->m_month;
    int32_t day = d->m_day + c_daysToAdd;
    d->correctDate(year, month, day);
    return KeoDate(year, month, day);
  } else {
    return d->minusDays((-1) * c_daysToAdd);
  }
}

KeoDate KeoDate::parse(const std::string &c_value) {
  if (c_value.length() == 0) {
    return KeoDate();
  }
  std::size_t start = 0, end = 0;
  int index = 0;
  int32_t year = 0, day = 1, month = 1;
  while ((end = c_value.find('-', start)) != std::string::npos) {
    if (index == 0) {
      try {
        year =
            KeoStringUtil::toUint32(c_value.substr(start, end - start).c_str());
      } catch (std::invalid_argument &e) {
        return KeoDate();
      }
      index++;
      start = end + 1;
      continue;
    }
    if (index == 1) {
      try {
        month =
            KeoStringUtil::toUint32(c_value.substr(start, end - start).c_str());
      } catch (std::invalid_argument &e) {
        return KeoDate();
      }
      index++;
      break;
    }
  }
  if (index != 2) {
    return KeoDate();
  }
  try {
    day = KeoStringUtil::toUint32(c_value.substr(end + 1).c_str());
  } catch (std::invalid_argument &e) {
    return KeoDate();
  }

  return KeoDate(year, month, day);
}

KeoDate KeoDate::ofEpochSeconds(uint64_t c_totalSeconds) {
  uint64_t days = static_cast<uint64_t>(c_totalSeconds / 86400);
  KeoDate returnDate(1970, 1, 1);
  return returnDate.plusDays(days);
}

KeoDate KeoDate::nowUTC() {
  time_t now = time(0);
  tm *gmtm = gmtime(&now);

  if (NULL == gmtm) {
    return KeoDate();
  }

  int32_t day = gmtm->tm_mday;
  int32_t month = gmtm->tm_mon + 1;
  int32_t year = gmtm->tm_year + 1900;

  return KeoDate(year, month, day);
}

KeoDate &KeoDate::operator=(const KeoDate &rhs) {
  if (this != &rhs) {
    *d = *rhs.d;
  }
  return *this;
}

bool KeoDate::operator==(const KeoDate &c_classObject) const {
  if (!isValid() || !c_classObject.isValid()) {
    return false;
  }

  if (d->m_year != c_classObject.d->m_year)
    return false;
  if (d->m_month != c_classObject.d->m_month)
    return false;
  if (d->m_day != c_classObject.d->m_day)
    return false;
  return true;
}

bool KeoDate::operator!=(const KeoDate &c_classObject) const {
  if (!isValid() || !c_classObject.isValid()) {
    return false;
  }

  return !(*this == c_classObject);
}

bool KeoDate::operator>(const KeoDate &c_classObject) const {
  if (!isValid() || !c_classObject.isValid()) {
    return false;
  }

  int comp = d->m_year - c_classObject.d->m_year;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = d->m_month - c_classObject.d->m_month;
  if (comp > 0)
    return true;
  if (comp < 0)
    return false;
  comp = d->m_day - c_classObject.d->m_day;
  if (comp > 0)
    return true;
  return false;
}

bool KeoDate::operator<(const KeoDate &c_classObject) const {
  return !(*this > c_classObject) && (*this != c_classObject);
}

bool KeoDate::operator>=(const KeoDate &c_classObject) const {
  return *this == c_classObject || *this > c_classObject;
}

bool KeoDate::operator<=(const KeoDate &c_classObject) const {
  return *this == c_classObject || *this < c_classObject;
}

} // namespace keo_datagram