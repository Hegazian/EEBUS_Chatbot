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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTMODIFYNODECALLELEMENTS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTMODIFYNODECALLELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/FeatureAddressElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementModifyNodeCallElements
 */
class NetworkManagementModifyNodeCallElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementModifyNodeCallElements();

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
  bool operator==(
      const NetworkManagementModifyNodeCallElements &c_classObject) const;

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
  bool operator!=(
      const NetworkManagementModifyNodeCallElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member NodeAddress.
   * @param c_nodeAddress Value to set
   */
  void setNodeAddress(const FeatureAddressElements &c_nodeAddress);

  /**
   * Returns const reference to member NodeAddress.
   * @return const reference to member nodeAddress
   */
  const FeatureAddressElements &getNodeAddress() const;

  /**
   * Returns if member NodeAddress is set.
   * @retval true member NodeAddress is set
   * @retval false member NodeAddress is not set
   */
  bool getNodeAddressIsSet() const;

  /**
   * Unsets member NodeAddress
   */
  void cleanNodeAddress();

  /**
   * Set member NativeSetup.
   */
  void setNativeSetup();

  /**
   * Returns if member NativeSetup is set.
   * @retval true member NativeSetup is set
   * @retval false member NativeSetup is not set
   */
  bool getNativeSetupIsSet() const;

  /**
   * Unsets member NativeSetup
   */
  void cleanNativeSetup();

  /**
   * Set member Timeout.
   */
  void setTimeout();

  /**
   * Returns if member Timeout is set.
   * @retval true member Timeout is set
   * @retval false member Timeout is not set
   */
  bool getTimeoutIsSet() const;

  /**
   * Unsets member Timeout
   */
  void cleanTimeout();

  /**
   * Set member Label.
   */
  void setLabel();

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   */
  void setDescription();

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_nodeAddressIsSet;
  FeatureAddressElements m_nodeAddress;

  // ElementTag
  bool m_nativeSetupIsSet;

  // ElementTag
  bool m_timeoutIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! NetworkManagementModifyNodeCallElements
using NetworkManagementModifyNodeCallElementsPtr =
    std::shared_ptr<NetworkManagementModifyNodeCallElements>;

//! typedef for const type NetworkManagementModifyNodeCallElements
using NetworkManagementModifyNodeCallElementsConst =
    const NetworkManagementModifyNodeCallElements;

//! typedef for const type NetworkManagementModifyNodeCallElements
using NetworkManagementModifyNodeCallElementsConstPtr =
    std::shared_ptr<NetworkManagementModifyNodeCallElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTMODIFYNODECALLELEMENTS_H_