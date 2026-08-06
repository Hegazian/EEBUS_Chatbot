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

#ifndef KEO_DATAGRAM_CORE_KEODATE_H_
#define KEO_DATAGRAM_CORE_KEODATE_H_

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */

#include <stdint.h>
#include <string>

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

/**
 * @class KeoDate
 * @brief The KeoDate class represents a calendar date.
 *
 * Important: When fetching an instance of this class from a SPINE datagram,
 * make sure
 * to call isValid() on it.
 */
class KeoDate {
public:
  /**
   * Constructor:
   * Constructs an instance with content set to invalidate.
   */
  KeoDate();

  /**
   * Constructor:
   * Constructs an instance with valid content.
   * If the date is not valid, it creates an empty invalid date
   * @param c_year The year
   * @param c_month The mounth
   * @param c_day The day
   *
   */
  KeoDate(uint32_t c_year, uint32_t c_month, uint32_t c_day);

  /**
   * Copy constructor:
   * Constructs an instance of KeoDate with a copy of the content from another
   * KeoDate instance.
   * If date is not valid, it creates an empty instance with invalid content.
   * @param date other instance of KeoDate
   */
  KeoDate(const KeoDate &date);

  /**
   * Destructor
   */
  virtual ~KeoDate();

  /**
   * Check validity of the KeoDate content.
   * Content of this instance is valid if it represents a valid date.
   * @return true if content is valid, else false
   */
  bool isValid() const;

  /**
   * Check if year, mounth and day are all zero
   * @return true if year, month and day are all zero
   */
  bool isZero() const;

  /**
   * Convert the date content to string representation.
   * @return string representation of the instance
   */
  std::string toString() const;

  /**
   * Calculate the seconds since 1.1.1970.
   * Undefined if the instance is invalid.
   * @return seconds since 1.1.1970
   */
  uint64_t toSeconds() const;

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
   * Check for leap year.
   * @return true it is a leap year, else false
   */
  bool isLeapYear() const;

  /**
   * Add years.
   * Returns an invalid instance if the instance is invalid.
   * @param c_yearsToAdd Years to add.
   * @return Instance with the result.
   */
  KeoDate plusYears(int32_t c_yearsToAdd) const;

  /**
   * Add months.
   * Returns an invalid instance if the instance is invalid.
   * @param c_monthsToAdd Mounth to add.
   * @return Instance with the result
   */
  KeoDate plusMonths(int32_t c_monthsToAdd) const;

  /**
   * Add days.
   * Returns an invalid instance if the instance is invalid.
   * @param c_daysToAdd Days to add.
   * @return Instance with the result
   */
  KeoDate plusDays(int32_t c_daysToAdd) const;

  /**
   * Parse a string to retrieve the date.
   * Returns an invalid instance if the parsing failed,
   * e.g. due to invalid format of the argument.
   * @param c_value
   *    string to parse. The expected format is specified by W3C.
   * @return Instance representing the parsed argument
   */
  static KeoDate parse(const std::string &c_value);

  /**
   * Calculate an instance representing 1.1.1970 plus the elapsed seconds.
   * @param c_totalSeconds
   *        Seconds to be calculated with
   * @return instance with the resulting value.
   */
  static KeoDate ofEpochSeconds(uint64_t c_totalSeconds);

  /**
   * Returns an instance of KeoDate with the current date.
   * Invalid if gmtime() returns NULL.
   * @return instance with the resulting date.
   */
  static KeoDate nowUTC();

  /**
   * Assignment operator. Copies the content from another instance.
   * @param rhs the other instance
   * @return Reference to the own instance.
   */
  KeoDate &operator=(const KeoDate &rhs);

  /**
   * Comparison operator ==
   * @param c_classObject instance to compare
   */
  bool operator==(const KeoDate &c_classObject) const;

  /**
   *
   * Comparison operator !=
   * @param c_classObject instance to compare
   */
  bool operator!=(const KeoDate &c_classObject) const;

  /**
   * Relational operator >
   * @param c_classObject instance to compare
   */
  bool operator>(const KeoDate &c_classObject) const;

  /**
   * Relational operator <
   * @param c_classObject instance to compare
   */
  bool operator<(const KeoDate &c_classObject) const;

  /**
   * Relational operator >=
   * @param c_classObject instance to compare
   */
  bool operator>=(const KeoDate &c_classObject) const;

  /**
   * Relational operator <=
   * @param c_classObject instance to compare
   */
  bool operator<=(const KeoDate &c_classObject) const;

private:
  class KeoDatePriv;
  KeoDatePriv *d;
};

/** @}
 */
}

#endif // KEO_DATAGRAM_CORE_KEODATE_H_