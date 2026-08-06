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

#ifndef KEO_DATAGRAM_BILL_BILLDATAELEMENTS_H_
#define KEO_DATAGRAM_BILL_BILLDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillPositionElements.h>
#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillDataElements
 */
class BillDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  BillDataElements();

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
  bool operator==(const BillDataElements &c_classObject) const;

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
  bool operator!=(const BillDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member BillId.
   */
  void setBillId();

  /**
   * Returns if member BillId is set.
   * @retval true member BillId is set
   * @retval false member BillId is not set
   */
  bool getBillIdIsSet() const;

  /**
   * Unsets member BillId
   */
  void cleanBillId();

  /**
   * Set member BillType.
   */
  void setBillType();

  /**
   * Returns if member BillType is set.
   * @retval true member BillType is set
   * @retval false member BillType is not set
   */
  bool getBillTypeIsSet() const;

  /**
   * Unsets member BillType
   */
  void cleanBillType();

  /**
   * Set member ScopeType.
   */
  void setScopeType();

  /**
   * Returns if member ScopeType is set.
   * @retval true member ScopeType is set
   * @retval false member ScopeType is not set
   */
  bool getScopeTypeIsSet() const;

  /**
   * Unsets member ScopeType
   */
  void cleanScopeType();

  /**
   * Set member Total.
   * @param c_total Value to set
   */
  void setTotal(const BillPositionElements &c_total);

  /**
   * Returns const reference to member Total.
   * @return const reference to member total
   */
  const BillPositionElements &getTotal() const;

  /**
   * Returns if member Total is set.
   * @retval true member Total is set
   * @retval false member Total is not set
   */
  bool getTotalIsSet() const;

  /**
   * Unsets member Total
   */
  void cleanTotal();

  /**
   * Set member Position.
   * @param c_position Value to set
   */
  void setPosition(const BillPositionElements &c_position);

  /**
   * Returns const reference to member Position.
   * @return const reference to member position
   */
  const BillPositionElements &getPosition() const;

  /**
   * Returns if member Position is set.
   * @retval true member Position is set
   * @retval false member Position is not set
   */
  bool getPositionIsSet() const;

  /**
   * Unsets member Position
   */
  void cleanPosition();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_billIdIsSet;

  // ElementTag
  bool m_billTypeIsSet;

  // ElementTag
  bool m_scopeTypeIsSet;

  bool m_totalIsSet;
  BillPositionElements m_total;

  bool m_positionIsSet;
  BillPositionElements m_position;
};

//! typedef for non-const smart pointer type BillDataElements
using BillDataElementsPtr = std::shared_ptr<BillDataElements>;

//! typedef for const type BillDataElements
using BillDataElementsConst = const BillDataElements;

//! typedef for const type BillDataElements
using BillDataElementsConstPtr = std::shared_ptr<BillDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLDATAELEMENTS_H_