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

#ifndef KEO_DATAGRAM_CORE_SCOPETYPE_H_
#define KEO_DATAGRAM_CORE_SCOPETYPE_H_

#include <cstdint>
#include <string>

#include <keo_datagram/core/SpineEnumClass.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration ScopeType
 */
class ScopeType : public ExtendableSpineEnum {
public:
  //! Number of possible enumeration values
  const static std::size_t MAX_ENUM = 44;

  //! Enumeration ScopeType::Value
  enum class Value {
    UNDEFINED__ = -1,
    AC,
    AC_COS_PHI_GRID,
    AC_CURRENT_A,
    AC_CURRENT_B,
    AC_CURRENT_C,
    AC_FREQUENCY_GRID,
    AC_POWER_A,
    AC_POWER_B,
    AC_POWER_C,
    AC_POWER_LIMIT_PCT,
    AC_POWER_TOTAL,
    AC_VOLTAGE_A,
    AC_VOLTAGE_B,
    AC_VOLTAGE_C,
    AC_YIELD_DAY,
    AC_YIELD_TOTAL,
    DC_CURRENT,
    DC_POWER,
    DC_STRING1,
    DC_STRING2,
    DC_STRING3,
    DC_STRING4,
    DC_STRING5,
    DC_STRING6,
    DC_TOTAL,
    DC_VOLTAGE,
    DHW_TEMPERATURE,
    FLOW_TEMPERATURE,
    OUTSIDE_AIR_TEMPERATURE,
    RETURN_TEMPERATURE,
    ROOM_AIR_TEMPERATURE,
    CHARGE,
    STATE_OF_CHARGE,
    DISCHARGE,
    GRID_CONSUMPTION,
    GRID_FEED_IN,
    SELF_CONSUMPTION,
    OVERLOAD_PROTECTION,
    AC_POWER,
    AC_ENERGY,
    AC_CURRENT,
    AC_VOLTAGE,
    BATTERY_CONTROL,
    SIMPLE_INCENTIVE_TABLE
  };

  /**
   * Constructs an instance with the value "undefined".
   */
  ScopeType();

  /**
   * Constructs an instance and sets its value from enum value.
   * @param value the value of the new instance
   */
  ScopeType(ScopeType::Value value);

  /**
   * Constructs an instance and sets its value from string.
   * @param value the value of the new instance
   */
  ScopeType(const std::string &value);

  /**
   * Constructs the enumeration value from string.
   * @returns An enumeration object created from the string
   */
  static ScopeType fromString(const std::string &c_text);

  /**
   * Return struct object as string
   * @return enumeration object as string
   */
  std::string toString() const;

  /**
   * Set this enum object from string
   * @param c_text the string to set
   */
  bool setFromString(const std::string &c_text);

  /**
   * Return the value of this enumeration object.
   * @return enumeration value
   */
  ScopeType::Value getValue() const;

  /**
   * Return the value of this enumeration object.
   * \deprecated Use getValue() instead.
   * @return enumeration value
   */
  ScopeType::Value getData() const;

  /**
   * Comparison operator ==
   * @param other object to compare
   */
  bool operator==(const ScopeType &other) const;

  /**
   * Comparison operator !=
   * @param other object to compare
   */
  bool operator!=(const ScopeType &other) const;

private:
  std::size_t toNumber() const;

  bool setFromNumber(std::size_t c_number);

  ScopeType::Value m_data;

  // Human-readable strings of the enum data type
  static const std::string enumToString[MAX_ENUM];
};

/**
 * \deprecated Use ScopeType instead.
 */
using ScopeTypeStruct = ScopeType;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SCOPETYPE_H_