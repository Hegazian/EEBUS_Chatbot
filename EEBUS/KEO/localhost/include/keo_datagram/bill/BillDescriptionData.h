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

#ifndef KEO_DATAGRAM_BILL_BILLDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_BILL_BILLDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/bill/BillDescriptionDataElements.h>
#include <keo_datagram/core/BillType.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramBill
 * @{
 */

/**
 * Declaration BillDescriptionData
 */
class BillDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  BillDescriptionData();

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
  bool operator==(const BillDescriptionData &c_classObject) const;

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
  bool operator!=(const BillDescriptionData &c_classObject) const;

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
   * Set member BillWriteable.
   * @param c_billWriteable Value to set
   */
  void setBillWriteable(const xs_boolean &c_billWriteable);

  /**
   * Returns const reference to member BillWriteable.
   * @return const reference to member billWriteable
   */
  const xs_boolean &getBillWriteable() const;

  /**
   * Returns if member BillWriteable is set.
   * @retval true member BillWriteable is set
   * @retval false member BillWriteable is not set
   */
  bool getBillWriteableIsSet() const;

  /**
   * Unsets member BillWriteable
   */
  void cleanBillWriteable();

  /**
   * Set member UpdateRequired.
   * @param c_updateRequired Value to set
   */
  void setUpdateRequired(const xs_boolean &c_updateRequired);

  /**
   * Returns const reference to member UpdateRequired.
   * @return const reference to member updateRequired
   */
  const xs_boolean &getUpdateRequired() const;

  /**
   * Returns if member UpdateRequired is set.
   * @retval true member UpdateRequired is set
   * @retval false member UpdateRequired is not set
   */
  bool getUpdateRequiredIsSet() const;

  /**
   * Unsets member UpdateRequired
   */
  void cleanUpdateRequired();

  /**
   * Set member SupportedBillType.
   * @param c_supportedBillType Value to set
   */
  void setSupportedBillType(const std::vector<BillType> &c_supportedBillType);

  /**
   * Returns const reference to member SupportedBillType.
   * @return const reference to member supportedBillType
   */
  const std::vector<BillType> &getSupportedBillType() const;

  /**
   * Returns if member SupportedBillType is set.
   * @retval true member SupportedBillType is set
   * @retval false member SupportedBillType is not set
   */
  bool getSupportedBillTypeIsSet() const;

  /**
   * Unsets member SupportedBillType
   */
  void cleanSupportedBillType();

  /**
   * @copydoc CmdData::reduce()
   */
  BillDescriptionData reduce(const BillDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_billIdIsSet;
  xs_unsignedInt m_billId;

  bool m_billWriteableIsSet;
  xs_boolean m_billWriteable;

  bool m_updateRequiredIsSet;
  xs_boolean m_updateRequired;

  bool m_supportedBillTypeIsSet;
  std::vector<BillType> m_supportedBillType;
};

//! typedef for non-const smart pointer type BillDescriptionData
using BillDescriptionDataPtr = std::shared_ptr<BillDescriptionData>;

//! typedef for const type BillDescriptionData
using BillDescriptionDataConst = const BillDescriptionData;

//! typedef for const type BillDescriptionData
using BillDescriptionDataConstPtr = std::shared_ptr<BillDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_BILL_BILLDESCRIPTIONDATA_H_