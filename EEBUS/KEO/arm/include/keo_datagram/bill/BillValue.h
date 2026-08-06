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

#ifndef KEO_DATAGRAM_BILL_BILLVALUE_H_
#define KEO_DATAGRAM_BILL_BILLVALUE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillValueElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillValue
 */
class BillValue : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillValue();

  /**
   * Equality operator
   *
   * Two objects a and b are considered equal if and only if
   *     - all members that are set in a are also set in b
   *     - all members that are set in b are also set in a
   *     - all members that are set in a and b are equal
   *
   * @param c_classObject the object to compare to
   * @return true if the objects are equal
   */
  bool operator==(const BillValue &c_classObject) const;

  /**
   * Inequality operator
   *
   * Two objects a and b are considered not equal if and only if
   *     - at least one member that is set in a is not set in b
   *     - at least one member that is set in b is not set in a
   *     - at least one member that is set in a and b differs
   *
   * @param c_classObject the object to compare to
   * @return true, if the objects are not equal
   */
  bool operator!=(const BillValue &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member ValueId.
   * @param c_valueId Value to set
   */
  void setValueId(const xs_unsignedInt &c_valueId);

  /**
   * Returns const reference to member ValueId.
   * @return const reference to member valueId
   */
  const xs_unsignedInt &getValueId() const;

  /**
   * Returns if member ValueId is set.
   * @retval true member ValueId is set
   * @retval false member ValueId is not set
   */
  bool getValueIdIsSet() const;

  /**
   * Unsets member ValueId
   */
  void cleanValueId();

  /**
   * Set member Unit.
   * @param c_unit Value to set
   */
  void setUnit(const UnitOfMeasurement &c_unit);

  /**
   * Returns const reference to member Unit.
   * @return const reference to member unit
   */
  const UnitOfMeasurement &getUnit() const;

  /**
   * Returns if member Unit is set.
   * @retval true member Unit is set
   * @retval false member Unit is not set
   */
  bool getUnitIsSet() const;

  /**
   * Unsets member Unit
   */
  void cleanUnit();

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumber &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumber &getValue() const;

  /**
   * Returns if member Value is set.
   * @retval true member Value is set
   * @retval false member Value is not set
   */
  bool getValueIsSet() const;

  /**
   * Unsets member Value
   */
  void cleanValue();

  /**
   * Set member ValuePercentage.
   * @param c_valuePercentage Value to set
   */
  void setValuePercentage(const ScaledNumber &c_valuePercentage);

  /**
   * Returns const reference to member ValuePercentage.
   * @return const reference to member valuePercentage
   */
  const ScaledNumber &getValuePercentage() const;

  /**
   * Returns if member ValuePercentage is set.
   * @retval true member ValuePercentage is set
   * @retval false member ValuePercentage is not set
   */
  bool getValuePercentageIsSet() const;

  /**
   * Unsets member ValuePercentage
   */
  void cleanValuePercentage();

  /**
   * @copydoc CmdData::reduce()
   */
  BillValue reduce(const BillValueElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_valueIdIsSet;
  xs_unsignedInt m_valueId;

  bool m_unitIsSet;
  UnitOfMeasurement m_unit;

  bool m_valueIsSet;
  ScaledNumber m_value;

  bool m_valuePercentageIsSet;
  ScaledNumber m_valuePercentage;
};

//! typedef for non-const smart pointer type BillValue
using BillValuePtr = std::shared_ptr<BillValue>;

//! typedef for const type BillValue
using BillValueConst = const BillValue;

//! typedef for const type BillValue
using BillValueConstPtr = std::shared_ptr<BillValueConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLVALUE_H_