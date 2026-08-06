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

#ifndef KEO_DATAGRAM_BILL_BILLCONSTRAINTSDATAELEMENTS_H_
#define KEO_DATAGRAM_BILL_BILLCONSTRAINTSDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillConstraintsDataElements
 */
class BillConstraintsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  BillConstraintsDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_billIdIsSet the member to set
   * @param c_positionCountMinIsSet the member to set
   * @param c_positionCountMaxIsSet the member to set
   */
  BillConstraintsDataElements(xs_boolean c_billIdIsSet,
                              xs_boolean c_positionCountMinIsSet,
                              xs_boolean c_positionCountMaxIsSet);

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
  bool operator==(const BillConstraintsDataElements &c_classObject) const;

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
  bool operator!=(const BillConstraintsDataElements &c_classObject) const;

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
   * Set member PositionCountMin.
   */
  void setPositionCountMin();

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
   */
  void setPositionCountMax();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_billIdIsSet;

  // ElementTag
  bool m_positionCountMinIsSet;

  // ElementTag
  bool m_positionCountMaxIsSet;
};

//! typedef for non-const smart pointer type BillConstraintsDataElements
using BillConstraintsDataElementsPtr =
    std::shared_ptr<BillConstraintsDataElements>;

//! typedef for const type BillConstraintsDataElements
using BillConstraintsDataElementsConst = const BillConstraintsDataElements;

//! typedef for const type BillConstraintsDataElements
using BillConstraintsDataElementsConstPtr =
    std::shared_ptr<BillConstraintsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLCONSTRAINTSDATAELEMENTS_H_