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

#ifndef KEO_DATAGRAM_CORE_KESCALEDNUMBER_H_
#define KEO_DATAGRAM_CORE_KESCALEDNUMBER_H_

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

/**
 * Class encapsulating datatype ScaledNumberType handling.@n
 * The datatype ScaledNumberType was introduced to avoid conversion from
 * double to string and vice versa for data transfer between communication
 * partners.@n
 * A floating point number x is represented by the two items:@n
 * [long]  numberType@n
 * [short] scaleType@n
 *
 * The conversion rule is: x = numberType * (10^scaleType)@n
 * With '10^scaleType' being power of 10 - and NOT binary XOR operator.
 * @n
 * Note: This class internally avoids using double (or float) operations.
 *       Only exception is the method fromDouble which is marked as
 *       not recommended.
 */
class KeoScaledNumber {
public:
  //! Datatype to be used for NumberType
  using NumberTypeType = std::int64_t;

  //! Datatype to be used for ScaleType
  using ScaleTypeType = std::int16_t;

  //! maximum number of digits after comma used for conversion from double
  static size_t const MaxNumberOfDigitsAfterComma;

public:
  /**
   * Default constructor (representing the value 0.0)
   */
  KeoScaledNumber();

  /**
   * Constructor, explicitly used to set internal members to
   * the given parameter.
   * @param numberType
   * @param scaleType
   */
  explicit KeoScaledNumber(NumberTypeType numberType,
                           ScaleTypeType scaleType = 0);

  /**
   * Copy Constructor
   * @param rhs bject to be copied
   */
  KeoScaledNumber(KeoScaledNumber const &rhs);

  /**
   * Destructor
   */
  ~KeoScaledNumber();

  /**
   * Retrieve the internal member representing the numberType of this object
   * @return
   */
  NumberTypeType getNumberType() const;

  /**
   * Retrieve the internal member representing the scaleType of this object
   * @return
   */
  ScaleTypeType getScaleType() const;

  /**
   * Set the internal member representing the numberType of this object
   * @param numberType
   */
  void setNumberType(const NumberTypeType &numberType);

  /**
   * Set the internal member representing the scaleType of this object
   * @param scaleType
   */
  void setScaleType(const ScaleTypeType &scaleType);

  /**
   * Assignment operator for KEscaledNumberType.
   * @param rhs
   * @return
   */
  KeoScaledNumber &operator=(const KeoScaledNumber &rhs);

  /**
   * Assignment operator for double.
   * @param rhs
   * @return
   */
  KeoScaledNumber &operator=(double rhs);

  /**
   * Conversion operator for double.
   * @return
   */
  operator double() const;

  /**
   * Comparison operator to another KeoScaledNumber instance.
   * @param rhs
   * @return
   *        true if this equal rhs, else false
   */
  bool operator==(KeoScaledNumber const &rhs) const;

  /**
   * Comparison operator to another KeoScaledNumber instance.
   * @param rhs
   * @return
   *        true if this equal rhs, else false
   */
  bool operator!=(KeoScaledNumber const &rhs) const;

  /**
   * Comparison (greater than) operator to another KeoScaledNumber instance.
   * @param rhs
   * @return
   *        true if this is greater than rhs, else false
   */
  bool operator>(KeoScaledNumber const &rhs) const;

  /**
   * Comparison (less than) operator to another KeoScaledNumber instance.
   * @param rhs
   * @return
   *        true if this is less than rhs, else false
   */
  bool operator<(KeoScaledNumber const &rhs) const;

  /**
   * Comparison (less than or equal to) operator to another KeoScaledNumber
   * instance.
   * @param rhs
   * @return
   *        true if this is less than rhs or equal to, else false
   */
  bool operator<=(KeoScaledNumber const &rhs) const;

  /**
   * Comparison (greater than or equal to) operator to another KeoScaledNumber
   * instance.
   * @param rhs
   * @return
   *        true if this is greater than rhs or equal to, else false
   */
  bool operator>=(KeoScaledNumber const &rhs) const;

  /**
   * NOT RECOMMENDED TO BE USED!!!
   * This method converts from double value. As double cannot be converted to
   * two integer values without losses in most cases, this conversion method
   * is not recommended. However, it might be necessary.
   * The following algorithm applies:
   * 1.  Check value != 0
   * 1a. If value == 0 --> finish
   * 2.  Multiply value by 10 * digitsAfterComma
   * 2.  Loop
   *     If result == 0, multiply result by 10 continue loop
   *     else exit loop
   * 3.  --> finish (numberType and scaleType) calculation
   * @n
   * NOTE: It might be, that the result 'x' after reverse calculation of
   *       x = numberType * (10^scaleType) is not valid with the given
   *       amount of 'digitsAfterComma'.
   *       Means:
   *       The result 'x' does not fit in a long data type.
   *       In this situation the amount of 'digitsAfterComma' is reduced as long
   *       as value fits in the 'long' data type.
   *       please be aware that on amd64 a long is 64bit but on raspi only 32bit
   * @param value
   * @param digitsAfterComma
   *        Maximum number of digits after comma is internally limited to
   * @return
   *        resulting ScaledNumberType object
   */
  static KeoScaledNumber fromDouble(double value, size_t digitsAfterComma);

  /**
   * @brief Check whether the number is negative
   * @return true if negative otherwise false
   */
  bool isNegative() const;

  /**
   * NOT RECOMMENDED TO BE USED!!!
   * This method converts from string. As double cannot be converted to
   * two integer values without losses in most cases, this conversion method
   * is not recommended. However, it might be necessary.
   * The following algorithm applies:
   * 1.  Check value != 0
   * 1a. If value == 0 --> finish
   * 2.  Multiply value by 10 * digitsAfterComma
   * 2.  Loop
   *     If result == 0, multiply result by 10 continue loop
   *     else exit loop
   * 3.  --> finish
   * @param value
   * @param digitsAfterComma
   *        Maximum number of digits after comma is internally limited to
   * @return
   *        resulting ScaledNumberType object
   */
  static KeoScaledNumber fromString(std::string const &value,
                                    size_t digitsAfterComma);

  /**
   * NOT RECOMMENDED TO BE USED!!!
   * This method converts to double value. As double cannot be converted to
   * two integer values without losses in most cases, this conversion method
   * is not recommended. However, it might be necessary.
   * The following algorithm applies:
   * 1.  check m_numberType != 0
   * 2.  check m_scaleType negative
   * 3.  if m_scaleType negative: result = m_numberType / (10 ^
   * abs(m_scaleType))
   *     if m_scaleType positive: result = m_numberType * (10 ^
   * abs(m_scaleType))
   * @return
   *       resulting double value
   */
  double toDouble() const;

  /**
   * This method converts to string.
   * @return
   *       resulting string
   */
  std::string toString() const;

  /**
   * This method normalizes (i.e. smallest scale possible) a scaled number
   * object.
   * @param scaledNumber The scaled number to normalize
   * @return Normalized scaled number
   */
  static KeoScaledNumber normalize(const KeoScaledNumber &scaledNumber);

  /**
   * This method equalizes the scales of two scaled number types.
   * @param snt1       Input of first scaled number object
   * @param snt2       Input of second scaled number object
   * @param equalSnt1  Output of first equalized scaled number object
   * @param equalSnt2  Output of second equalized scaled number object
   */
  static void equalizeScale(const KeoScaledNumber &snt1,
                            const KeoScaledNumber &snt2,
                            KeoScaledNumber &equalSnt1,
                            KeoScaledNumber &equalSnt2);

  /**
   * This method adds two scaled numbers.
   * @param summand1 First scaled number
   * @param summand2 Second scaled number
   * @return The sum of both scaled numbers
   */
  static KeoScaledNumber add(const KeoScaledNumber &summand1,
                             const KeoScaledNumber &summand2);

  /**
   * This method subtracts two scaled numbers.
   * @param minuend The minuend (scaled number to subtract from)
   * @param subtrahend The subtrahend (scaled number to subtract)
   * @return The difference of both scaled numbers
   */
  static KeoScaledNumber subtract(const KeoScaledNumber &minuend,
                                  const KeoScaledNumber &subtrahend);

  /**
   * This methods multiplies two scaled numbers.
   * @param factor1 The first scaled number
   * @param factor2 The second scaled number
   * @return The product of both scaled numbers
   */
  static KeoScaledNumber multiply(const KeoScaledNumber &factor1,
                                  const KeoScaledNumber &factor2);

private:
  enum {
    EQ,
    NEQ,
    GT,
    LT,
  };

  int compare(const KeoScaledNumber &b) const;

private:
  /** @brief Number for the scaled number */
  NumberTypeType m_numberType;
  /** @brief Scale of the scaled number */
  ScaleTypeType m_scaleType;
};

/** @}
 */

} // namespace keo_datagarm

#endif // KEO_DATAGRAM_CORE_KESCALEDNUMBER_H_