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

#ifndef KEO_DATAGRAM_CORE_KEOTIME_H_
#define KEO_DATAGRAM_CORE_KEOTIME_H_

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <stdint.h>
#include <string>

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

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

class KeoDateTime;
class KeoDate;

/**
 * @class KeoTime
 * @brief Time class
 */
class KeoTime {
public:
  /**
   * Constructor:
   * Constructs an instance containing invalid data
   */
  KeoTime();

  /**
   * Constructor:
   * Constructs an instance with preinitialized content.
   * The time in valid.
   * @param c_hour the hour
   * @param c_minute the minute
   * @param c_second the second
   * @param c_milli the milli
   */
  KeoTime(int32_t c_hour, int32_t c_minute, int32_t c_second, int32_t c_milli);

  /**
   * Constructor:
   * Constructs an instance with a copy from other KETime instance.
   * @param time the time
   */
  KeoTime(const KeoTime &time);

  /**
   * Virtual destructor
   */
  virtual ~KeoTime();

  /**
   * Check validity of this instance.
   * An instance is invalid if it represents a valid time.
   * @return true if valid, else false
   */
  bool isValid() const;

  /**
   * Check if time is set to zero.
   * @return true if hour, minute, second and milli are zero
   */
  bool isZero() const;

  /**
   * Convert content to string representation.
   * @return string representation of the instance
   */
  std::string toString() const;

  /**
   * Calculate the seconds since midnight.
   * Undefined if the instance is invalid.
   * @return the seconds
   */
  uint64_t toSeconds() const;

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
   * Getter for the millisecond.
   * Undefined if the instance is invalid.
   * @return the millisecond
   */
  uint16_t getMilliSecond() const;

  /**
   * Add hours.
   * Returns an invalid instance if the instance is invalid.
   * @param c_hoursToAdd hours to add
   * @return Instance with the result
   */
  KeoTime plusHours(int32_t c_hoursToAdd) const;

  /**
   * Add minutes.
   * Returns an invalid instance if the instance is invalid.
   * @param c_minutesToAdd minutes to add
   * @return Instance with the result
   */
  KeoTime plusMinutes(int32_t c_minutesToAdd) const;

  /**
   * Add seconds.
   * Returns an invalid instance if the instance is invalid.
   * @param c_secondsToAdd seconds to add
   * @return Instance with the result
   */
  KeoTime plusSeconds(int32_t c_secondsToAdd) const;

  /**
   * Composes a KEDateTime instance from this instance and the argument.
   * Returns an invalid instance if the instance or the argument are invalid.
   * @param c_date the date instance
   * @return Instance with the result
   */
  KeoDateTime atDate(const KeoTime &c_date);

  /**
   * Parse a KeoTime from a string. Note that in SPINE absolute times are always
   * stated as UTC ("Z" at the end).
   * Returns an invalid instance if the parsing failed,
   * e.g. due to invalid format of the argument.
   * @param c_value
   *    string to parse. The expected format is specified by W3C.
   * @return Instance representing the parsed argument
   */
  static KeoTime parse(const std::string &c_value);

  /**
   * Calculate an instance representing midnight plus the elapsed milliseconds.
   * @param c_totalMilliSeconds
   *        milliseconds to be calculated with
   * @return instance with the resulting value.
   */
  static KeoTime ofMilliSecondOfDay(int64_t c_totalMilliSeconds);

  /**
   * Returns an instance with the current time (UTC).
   * @return instance with the resulting value.
   */
  static KeoTime now();

  /**
   * Assignment operator. Copies the content
   * @param rhs the other instance
   * @return
   */
  KeoTime &operator=(const KeoTime &rhs);

  /**
   * Comparison operator ==
   * @param c_classObject instance to compare
   */
  bool operator==(const KeoTime &c_classObject) const;

  /**
   * Comparison operator !=
   * @param c_classObject instance to compare
   */
  bool operator!=(const KeoTime &c_classObject) const;

  /**
   * Relational operator >
   * @param c_classObject instance to compare
   */
  bool operator>(const KeoTime &c_classObject) const;

  /**
   * Relational operator <
   * @param c_classObject instance to compare
   */
  bool operator<(const KeoTime &c_classObject) const;

  /**
   * Relational operator >=
   * @param c_classObject instance to compare
   */
  bool operator>=(const KeoTime &c_classObject) const;

  /**
   * Relational operator <=
   * @param c_classObject instance to compare
   */
  bool operator<=(const KeoTime &c_classObject) const;

private:
  class KeoTimePriv;
  KeoTimePriv *d;
};

/** @}
 */
}

#endif // KEO_DATAGRAM_CORE_KEOTIME_H_