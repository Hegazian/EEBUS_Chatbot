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

#ifndef KEO_DATAGRAM_BILL_BILLDATA_H_
#define KEO_DATAGRAM_BILL_BILLDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillDataElements.h>
#include <keo_datagram/bill/BillPosition.h>
#include <keo_datagram/core/BillType.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillData
 */
class BillData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillData();

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
  bool operator==(const BillData &c_classObject) const;

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
  bool operator!=(const BillData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member BillId.
   * @param c_billId Value to set
   */
  void setBillId(const xs_unsignedInt &c_billId);

  /**
   * Returns const reference to member BillId.
   * @return const reference to member billId
   */
  const xs_unsignedInt &getBillId() const;

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
   * @param c_billType Value to set
   */
  void setBillType(const BillType &c_billType);

  /**
   * Returns const reference to member BillType.
   * @return const reference to member billType
   */
  const BillType &getBillType() const;

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
   * @param c_scopeType Value to set
   */
  void setScopeType(const ScopeType &c_scopeType);

  /**
   * Returns const reference to member ScopeType.
   * @return const reference to member scopeType
   */
  const ScopeType &getScopeType() const;

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
  void setTotal(const BillPosition &c_total);

  /**
   * Returns const reference to member Total.
   * @return const reference to member total
   */
  const BillPosition &getTotal() const;

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
  void setPosition(const std::vector<BillPosition> &c_position);

  /**
   * Returns const reference to member Position.
   * @return const reference to member position
   */
  const std::vector<BillPosition> &getPosition() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  BillData reduce(const BillDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_billIdIsSet;
  xs_unsignedInt m_billId;

  bool m_billTypeIsSet;
  BillType m_billType;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_totalIsSet;
  BillPosition m_total;

  bool m_positionIsSet;
  std::vector<BillPosition> m_position;
};

//! typedef for non-const smart pointer type BillData
using BillDataPtr = std::shared_ptr<BillData>;

//! typedef for const type BillData
using BillDataConst = const BillData;

//! typedef for const type BillData
using BillDataConstPtr = std::shared_ptr<BillDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLDATA_H_