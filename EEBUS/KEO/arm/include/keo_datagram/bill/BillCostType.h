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

#ifndef KEO_DATAGRAM_BILL_BILLCOSTTYPE_H_
#define KEO_DATAGRAM_BILL_BILLCOSTTYPE_H_

#include <cstdint>
#include <string>

#include <keo_datagram/core/SpineEnumClass.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillCostType
 */
class BillCostType : public ExtendableSpineEnum {
public:
  //! Number of possible enumeration values
  const static std::size_t MAX_ENUM = 5;

  //! Enumeration BillCostType::Value
  enum class Value {
    UNDEFINED__ = -1,
    ABSOLUTE_PRICE,
    RELATIVE_PRICE,
    CO2EMISSION,
    RENEWABLE_ENERGY,
    RADIOACTIVE_WASTE
  };

  /**
   * Constructs an instance with the value "undefined".
   */
  BillCostType();

  /**
   * Constructs an instance and sets its value from enum value.
   * @param value the value of the new instance
   */
  BillCostType(BillCostType::Value value);

  /**
   * Constructs an instance and sets its value from string.
   * @param value the value of the new instance
   */
  BillCostType(const std::string &value);

  /**
   * Constructs the enumeration value from string.
   * @returns An enumeration object created from the string
   */
  static BillCostType fromString(const std::string &c_text);

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
  BillCostType::Value getValue() const;

  /**
   * Return the value of this enumeration object.
   * \deprecated Use getValue() instead.
   * @return enumeration value
   */
  BillCostType::Value getData() const;

  /**
   * Comparison operator ==
   * @param other object to compare
   */
  bool operator==(const BillCostType &other) const;

  /**
   * Comparison operator !=
   * @param other object to compare
   */
  bool operator!=(const BillCostType &other) const;

private:
  std::size_t toNumber() const;

  bool setFromNumber(std::size_t c_number);

  BillCostType::Value m_data;

  // Human-readable strings of the enum data type
  static const std::string enumToString[MAX_ENUM];
};

/**
 * \deprecated Use BillCostType instead.
 */
using BillCostTypeStruct = BillCostType;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLCOSTTYPE_H_