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

#ifndef KEO_DATAGRAM_CORE_KEODURATION_H_
#define KEO_DATAGRAM_CORE_KEODURATION_H_

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <stdint.h>
#include <string>
#include <time.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
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
class KeoDateTime;

/**
 * @class KeoDuration
 * @brief KeoDuration represents a time interval.
 *
 * It has different methods for DateTime transformation and some arithmetic
 * functions.
 *
 * Important: When fetching an instance of this class from a SPINE datagram,
 * make sure
 * to call isValid() on it.
 */
class KeoDuration {
public:
  /**
   * constructs an invalid instance
   *
   */
  KeoDuration();

  /**
   * constructs a valid instance
   * if the argument can be parsed successfully.
   * @param duration String representation of a duration.
   */
  KeoDuration(std::string const &duration);

  /**
   * Constructs a valid instance using seconds and milliseconds.
   * @param c_seconds the seconds
   * @param c_millis the milliseconds
   * @param c_isNegative negative duration
   */
  KeoDuration(uint64_t c_seconds, uint64_t c_millis = 0,
              bool c_isNegative = false);

  /**
   * Constructs a valid instance using years, months, days, seconds, and
   * milliseconds
   * @param c_years the years
   * @param c_months the months
   * @param c_days the days
   * @param c_hours the hours
   * @param c_minutes the minutes
   * @param c_seconds the seconds
   * @param c_millis the milliseconds
   * @param c_isNegative negative duration
   */
  KeoDuration(uint32_t c_years, uint32_t c_months, uint64_t c_days,
              uint64_t c_hours, uint64_t c_minutes, uint64_t c_seconds,
              uint64_t c_millis = 0, bool c_isNegative = false);

  /**
   * An instance is valid if it represents a valid duration.
   * @return true if valid, otherwise false
   */
  bool isValid() const;

  /**
   * Check if the value of the duration is 0
   * The behaviour is undefined if the instance is invalid
   * @return true if 0 otherwise false
   */
  bool isZero() const;

  /**
   * Check if the value of the duration is negative
   * @return true if negative otherwise false
   */
  bool isNegative() const;

  /**
   * Set the duration to negative or positive
   * @param c_isNegative negative duration
   */
  void setNegative(bool c_isNegative);

  /**
   * Convert the duration to a string representation
   * if invalid to an empty string.
   * @return the string representation
   */
  std::string toString() const;

  /**
   * Get the year
   * Undefined if the instance is invalid.
   * @return the year
   */
  uint32_t getYears() const;

  /**
   * Get the month
   * Undefined if the instance is invalid.
   * @return the month
   */
  uint32_t getMonths() const;

  /**
   * Get the day
   * Undefined if the instance is invalid.
   * @return the day
   */
  uint64_t getDays() const;

  /**
   * Get the hours
   * Undefined if the instance is invalid.
   * @return the hours
   */
  uint64_t getHours() const;

  /**
   * Get the minutes
   * Undefined if the instance is invalid.
   * @return the minutes
   */
  uint64_t getMinutes() const;

  /**
   * Get the seconds
   * Undefined if the instance is invalid.
   * @return the seconds
   */
  uint64_t getSeconds() const;

  /**
   * Get the milliseconds
   * Undefined if the instance is invalid.
   * @return the milliseconds
   */
  uint64_t getMilliSeconds() const;

  /**
   * Get duration in milliseconds absolute to a time stamp
   * @param c_timestamp absolute time stamp
   * Undefined if the instance is invalid.
   * @return the absolute milliseconds
   */
  int64_t getAbsoluteMilliSeconds(const KeoDateTime &c_timestamp) const;

  /**
   * Get duration in seconds absolute to a time stamp
   * @param c_timestamp absolute time stamp
   * Undefined if the instance is invalid.
   *
   * Note that this method only considers full seconds (rounded down).
   *
   * @return the absolute seconds
   */
  int64_t getAbsoluteSeconds(const KeoDateTime &c_timestamp) const;

  /**
   * Get duration in seconds absolute to the internal time stamp
   * Undefined if the instance is invalid.
   * @return the absolute seconds
   */
  int64_t getAbsoluteSecondsSinceInternalTimestamp() const;

  /**
   * Add another duration to the duration of this instance and return a new
   * instance.
   * Returns an invalid instance if the instance is invalid.
   * Returns an invalid instance if the duration to add contains months or
   * years.
   *
   * @param c_duration the duration to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plus(const KeoDuration &c_duration) const;

  /**
   * Add days to this duration and return a new instance
   * Returns an invalid instance if the instance is invalid.
   *
   * @param c_daysToAdd the days to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plusDays(int32_t c_daysToAdd) const;

  /**
   * Add hours to this duration and return a new instance
   * Returns an invalid instance if the instance is invalid.
   *
   * @param c_hoursToAdd the hours to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plusHours(int32_t c_hoursToAdd) const;

  /**
   * Add minutes to this duration and return a new instance
   * Returns an invalid instance if the instance is invalid.
   *
   * @param c_minutesToAdd the minutes to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plusMinutes(int32_t c_minutesToAdd) const;

  /**
   * Add seconds to this duration and return a new instance
   * Returns an invalid instance if the instance is invalid.
   *
   * @param c_secondsToAdd the seconds to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plusSeconds(int32_t c_secondsToAdd) const;

  /**
   * Add milliseconds to this duration and return a new instance
   * Returns an invalid instance if the instance is invalid.
   *
   * @param c_millisToAdd the milliseconds to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plusMilliSeconds(int32_t c_millisToAdd) const;

  /**
   * Add seconds and milliseconds to this duration and return a new instance.
   * Returns an invalid instance if the instance is invalid.
   *
   * @param c_secondsToAdd the seconds to add
   * @param c_millisToAdd the milliseconds to add
   *
   * @return a new instance containing the added values
   */
  KeoDuration plus(int64_t c_secondsToAdd, int32_t c_millisToAdd) const;

  /**
   * Subtract another duration from this duration and return a new instance
   * Returns an invalid instance if the instance is invalid.
   * Returns an invalid instance if the duration to subtract contains months or
   * years.
   *
   * @param c_duration the duration to subtract
   *
   * @return a new instance containing the added values
   */
  KeoDuration minus(const KeoDuration &c_duration) const;

  /**
   * Subtract days.
   * Returns an invalid instance if the instance is invalid.
   * @param c_daysToSubtract
   * @return Instance with the result
   */
  KeoDuration minusDays(int32_t c_daysToSubtract) const;

  /**
   * Subtract hours.
   * Returns an invalid instance if the instance is invalid.
   * @param c_hoursToSubtract
   * @return Instance with the result
   */
  KeoDuration minusHours(int32_t c_hoursToSubtract) const;

  /**
   * Subtract minutes.
   * Returns an invalid instance if the instance is invalid.
   * @param c_minutesToSubtract
   * @return Instance with the result
   */
  KeoDuration minusMinutes(int32_t c_minutesToSubtract) const;

  /**
   * Subtract seconds.
   * Returns an invalid instance if the instance is invalid.
   * @param c_secondsToSubtract
   * @return Instance with the result
   */
  KeoDuration minusSeconds(int32_t c_secondsToSubtract) const;

  /**
   * Subtract milliseconds.
   * Returns an invalid instance if the instance is invalid.
   * @param c_millisToSubtract
   * @return Instance with the result
   */
  KeoDuration minusMilliSeconds(int32_t c_millisToSubtract) const;

  /**
   * Subtracts seconds and milliseconds.
   * Returns an invalid instance if the instance is invalid.
   * @param c_secondsToSubtract
   * @param c_millisToSubtract
   * @return Instance with the result
   */
  KeoDuration minus(int64_t c_secondsToSubtract,
                    int32_t c_millisToSubtract) const;

  /**
   * Get the absolute time stamp for this duration in seconds.
   */
  time_t getAbsoluteUTCTimestamp() const;

  /**
   * Set an absolute time stamp for this duration in seconds.
   * @param c_absoluteTimestamp
   */
  void setAbsoluteUTCTimestamp(time_t c_absoluteTimestamp);

  /**
   * Parse a string to retrieve a duration.
   * Returns an invalid instance if the parsing failed,
   * e.g. due to invalid format of the argument.
   * @param c_value
   *    string to parse. The expected format is specified in W3C.
   * @return Instance representing the parsed argument
   */
  static KeoDuration parse(const std::string &c_value);

  /**
   * Calculate an instance representing the duration of the argument.
   * @param c_seconds
   *        Seconds to be calculated with
   * @return instance with the resulting value.
   */
  static KeoDuration ofSeconds(int32_t c_seconds);

  /**
   * Calculate an instance representing the duration of the arguments.
   * @param c_seconds
   *        Seconds to be calculated with
   * @param c_millis
   *        Milliseconds to be calculated with
   * @return instance with the resulting value.
   */
  static KeoDuration ofSeconds(uint32_t c_seconds, uint32_t c_millis);

  /**
   * Comparison operator ==
   * @param c_classObject object to compare
   */
  bool operator==(const KeoDuration &c_classObject) const;

  /**
   * Comparison operator !=
   * @param c_classObject object to compare
   */
  bool operator!=(const KeoDuration &c_classObject) const;

  /**
   * Relational operator >
   * @param c_classObject object to compare
   */
  bool operator>(const KeoDuration &c_classObject) const;

  /**
   * Relational operator <
   * @param c_classObject object to compare
   */
  bool operator<(const KeoDuration &c_classObject) const;

private:
  uint32_t m_year;
  uint32_t m_month;
  uint64_t m_day;
  uint64_t m_seconds;
  uint64_t m_millis;
  bool m_isValid;
  bool m_isNegative;
  time_t m_absoluteUTCSeconds;
};

/** @}
 */
}

#endif // KEO_DATAGRAM_CORE_KEODURATION_H_