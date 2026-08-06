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

#ifndef KEO_DATAGRAM_BILL_BILLCONSTRAINTSDATA_H_
#define KEO_DATAGRAM_BILL_BILLCONSTRAINTSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillConstraintsDataElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillConstraintsData
 */
class BillConstraintsData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillConstraintsData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_billId the member to set
   * @param c_positionCountMin the member to set
   * @param c_positionCountMax the member to set
   */
  BillConstraintsData(const xs_unsignedInt &c_billId,
                      const xs_unsignedInt &c_positionCountMin,
                      const xs_unsignedInt &c_positionCountMax);

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
  bool operator==(const BillConstraintsData &c_classObject) const;

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
  bool operator!=(const BillConstraintsData &c_classObject) const;

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
   * Set member PositionCountMin.
   * @param c_positionCountMin Value to set
   */
  void setPositionCountMin(const xs_unsignedInt &c_positionCountMin);

  /**
   * Returns const reference to member PositionCountMin.
   * @return const reference to member positionCountMin
   */
  const xs_unsignedInt &getPositionCountMin() const;

  /**
   * Returns if member PositionCountMin is set.
   * @retval true member PositionCountMin is set
   * @retval false member PositionCountMin is not set
   */
  bool getPositionCountMinIsSet() const;

  /**
   * Unsets member PositionCountMin
   */
  void cleanPositionCountMin();

  /**
   * Set member PositionCountMax.
   * @param c_positionCountMax Value to set
   */
  void setPositionCountMax(const xs_unsignedInt &c_positionCountMax);

  /**
   * Returns const reference to member PositionCountMax.
   * @return const reference to member positionCountMax
   */
  const xs_unsignedInt &getPositionCountMax() const;

  /**
   * Returns if member PositionCountMax is set.
   * @retval true member PositionCountMax is set
   * @retval false member PositionCountMax is not set
   */
  bool getPositionCountMaxIsSet() const;

  /**
   * Unsets member PositionCountMax
   */
  void cleanPositionCountMax();

  /**
   * @copydoc CmdData::reduce()
   */
  BillConstraintsData reduce(const BillConstraintsDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_billIdIsSet;
  xs_unsignedInt m_billId;

  bool m_positionCountMinIsSet;
  xs_unsignedInt m_positionCountMin;

  bool m_positionCountMaxIsSet;
  xs_unsignedInt m_positionCountMax;
};

//! typedef for non-const smart pointer type BillConstraintsData
using BillConstraintsDataPtr = std::shared_ptr<BillConstraintsData>;

//! typedef for const type BillConstraintsData
using BillConstraintsDataConst = const BillConstraintsData;

//! typedef for const type BillConstraintsData
using BillConstraintsDataConstPtr = std::shared_ptr<BillConstraintsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLCONSTRAINTSDATA_H_