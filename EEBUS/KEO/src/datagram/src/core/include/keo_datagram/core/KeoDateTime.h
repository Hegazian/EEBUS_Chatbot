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

#ifndef KEO_DATAGRAM_CORE_KEODATETIME_H_
#define KEO_DATAGRAM_CORE_KEODATETIME_H_

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <keo_datagram/core/KeoDate.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoTime.h>
#include <stdint.h>
#include <string>

namespace keo_datagram {

/**
 * @addtogroup SpineDatagramCore
 * @{
 */

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */

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
 *  class definition *
 * ******************************************************************************
 */

/**
 * @class KeoDateTime
 * @brief KeoDateTime object contains a calendar date and a clock time.
 *
 * It has methods for different transformation and arithmetic functions.
 *
 * Important: When fetching an instance of this class from a SPINE datagram,
 * make sure
 * to call isValid() on it.
 */
class KeoDateTime {
public:
  /**
   * Constructor:
   * Constructs an instance with invalid content.
   */
  KeoDateTime();

  /**
   * Constructor:
   * Constructs an instance with values.
   * @param year the year
   * @param month the month
   * @param day the day
   * @param hour the hour
   * @param minute the minute
   * @param second the second
   * @param milli the milli seconds
   */
  KeoDateTime(int32_t year, int32_t month, int32_t day, int32_t hour,
              int32_t minute, int32_t second, int32_t milli);

  /**
   * Constructor:
   * Constructs an instance with a copy from other KEDate and KETime instances.
   * The date part and the time part, are valid.
   * @param c_date the date
   * @param c_time the time
   */
  KeoDateTime(const KeoDate &c_date, const KeoTime &c_time);

  /**
   * Check validity of this instance.
   * @return true if date and time are both valid, otherwise false
   */
  bool isValid() const;

  /**
   * Check if date and time are both set to zero.
   * @return true if the date and time are both zero, otherwise false
   */
  bool isZero() const;

  /**
   * Convert content to string representation.
   * Format is:
   * if timeStr is empty: dateStr
   * else: dateStr+ "T" + timeStr
   * @return string representation
   */
  std::string toString() const;

  /**
   * Getter for the year.
   * Undefined if the instance is invalid.
   * @return the year
   */
  uint16_t getYear() const;

  /**
   * Getter for the month.
   * Undefined if the instance is invalid.
   * @return the month
   */
  uint8_t getMonth() const;

  /**
   * Getter for the day.
   * Undefined if the instance is invalid.
   * @return the day
   */
  uint8_t getDay() const;

  /**
   * Getter for the hour.
   * Undefined if the instance is invalid.
   * @return the hour
   */
  uint8_t getHour() const;

  /**
   * Getter for the minute.
   * Undefined if the instance is invalid.
   * @return the minute
   */
  uint8_t getMinute() const;

  /**
   * Getter for the second.
   * Undefined if the instance is invalid.
   * @return the second
   */
  uint8_t getSecond() const;

  /**
   * getMillisecond
   * Getter for the millisecond.
   * Undefined if the instance is invalid.
   * @return the milliseconds
   */
  uint16_t getMilliSecond() const;

  /**
   * Calculate the seconds since 1.1.1970.
   * Undefined if the instance is invalid.
   * @return the seconds since 1.1.1970.
   */
  int64_t toSeconds() const;

  /**
   * Calculate the milli seconds since 1.1.1970.
   * Undefined if the instance is invalid.
   * @return the milli seconds since 1.1.1970.
   */
  int64_t toMilliSeconds() const;

  /**
   * Add a duration.
   * Invalid if the instance or the duration are invalid.
   * @param c_duration
   *        Duration to add
   * @return instance representing the sum.
   */
  KeoDateTime addDuration(const KeoDuration &c_duration) const;

  /**
   * Get the duration to another instance.
   * Invalid if the instance or the endDate are invalid.
   * @param c_endDate
   *        Date to which the duration is calculated
   * @return KEDuration instance with the result.
   */
  KeoDuration getDuration(const KeoDateTime &c_endDate) const;

  /**
   * Parse a string to convert it to a KeoDateTime instance.
   * Invalid if the either the "T" separator is missing or
   * if date part or time part cannot be parsed successfully.
   * @param c_value
   *    string to parse. The expected format is specified by W3C.
   * @return instance with the resulting value.
   */
  static KeoDateTime parse(const std::string &c_value);

  /**
   * Calculate an instance representing 1.1.1970 plus the elapsed milliseconds.
   * @param c_totalMilliSeconds
   *        Milliseconds to be calculated with
   * @return instance with the resulting value.
   */
  static KeoDateTime ofEpochMilliSeconds(int64_t c_totalMilliSeconds);

  /**
   * Returns an instance of KeoDateTime representing the current date and time.
   * @return instance with the resulting date and time.
   */
  static KeoDateTime now();

  /**
   * Comparison operator ==
   * @param c_classObject instance to compare
   */
  bool operator==(const KeoDateTime &c_classObject) const;

  /**
   * Comparison operator !=
   * @param c_classObject instance to compare
   */
  bool operator!=(const KeoDateTime &c_classObject) const;

  /**
   * Relational operator >
   * @param c_classObject instance to compare
   */
  bool operator>(const KeoDateTime &c_classObject) const;

  /**
   * Relational operator <
   * @param c_classObject instance to compare
   */
  bool operator<(const KeoDateTime &c_classObject) const;

  /**
   * Relational operator >=
   * @param c_classObject instance to compare
   */
  bool operator>=(const KeoDateTime &c_classObject) const;

  /**
   * Relational operator <=
   * @param c_classObject instance to compare
   */
  bool operator<=(const KeoDateTime &c_classObject) const;

private:
  KeoDate m_date;
  KeoTime m_time;
};

/** @}
 */
}

#endif // KEO_DATAGRAM_CORE_KEODATETIME_H_