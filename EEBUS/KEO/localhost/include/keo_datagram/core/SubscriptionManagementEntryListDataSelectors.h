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

#ifndef KEO_DATAGRAM_CORE_SUBSCRIPTIONMANAGEMENTENTRYLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_SUBSCRIPTIONMANAGEMENTENTRYLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/SubscriptionManagementEntryData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration SubscriptionManagementEntryListDataSelectors
 */
class SubscriptionManagementEntryListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  SubscriptionManagementEntryListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_subscriptionId the member to set
   * @param c_clientAddress the member to set
   * @param c_serverAddress the member to set
   */
  SubscriptionManagementEntryListDataSelectors(
      const xs_unsignedInt &c_subscriptionId,
      const FeatureAddress &c_clientAddress,
      const FeatureAddress &c_serverAddress);

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
      const SubscriptionManagementEntryListDataSelectors &c_classObject) const;

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
      const SubscriptionManagementEntryListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member SubscriptionId.
   * @param c_subscriptionId Value to set
   */
  void setSubscriptionId(const xs_unsignedInt &c_subscriptionId);

  /**
   * Returns const reference to member SubscriptionId.
   * @return const reference to member subscriptionId
   */
  const xs_unsignedInt &getSubscriptionId() const;

  /**
   * Returns if member SubscriptionId is set.
   * @retval true member SubscriptionId is set
   * @retval false member SubscriptionId is not set
   */
  bool getSubscriptionIdIsSet() const;

  /**
   * Unsets member SubscriptionId
   */
  void cleanSubscriptionId();

  /**
   * Set member ClientAddress.
   * @param c_clientAddress Value to set
   */
  void setClientAddress(const FeatureAddress &c_clientAddress);

  /**
   * Returns const reference to member ClientAddress.
   * @return const reference to member clientAddress
   */
  const FeatureAddress &getClientAddress() const;

  /**
   * Returns if member ClientAddress is set.
   * @retval true member ClientAddress is set
   * @retval false member ClientAddress is not set
   */
  bool getClientAddressIsSet() const;

  /**
   * Unsets member ClientAddress
   */
  void cleanClientAddress();

  /**
   * Set member ServerAddress.
   * @param c_serverAddress Value to set
   */
  void setServerAddress(const FeatureAddress &c_serverAddress);

  /**
   * Returns const reference to member ServerAddress.
   * @return const reference to member serverAddress
   */
  const FeatureAddress &getServerAddress() const;

  /**
   * Returns if member ServerAddress is set.
   * @retval true member ServerAddress is set
   * @retval false member ServerAddress is not set
   */
  bool getServerAddressIsSet() const;

  /**
   * Unsets member ServerAddress
   */
  void cleanServerAddress();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const SubscriptionManagementEntryData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_subscriptionIdIsSet;
  xs_unsignedInt m_subscriptionId;

  bool m_clientAddressIsSet;
  FeatureAddress m_clientAddress;

  bool m_serverAddressIsSet;
  FeatureAddress m_serverAddress;
};

//! typedef for non-const smart pointer type
//! SubscriptionManagementEntryListDataSelectors
using SubscriptionManagementEntryListDataSelectorsPtr =
    std::shared_ptr<SubscriptionManagementEntryListDataSelectors>;

//! typedef for const type SubscriptionManagementEntryListDataSelectors
using SubscriptionManagementEntryListDataSelectorsConst =
    const SubscriptionManagementEntryListDataSelectors;

//! typedef for const type SubscriptionManagementEntryListDataSelectors
using SubscriptionManagementEntryListDataSelectorsConstPtr =
    std::shared_ptr<SubscriptionManagementEntryListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SUBSCRIPTIONMANAGEMENTENTRYLISTDATASELECTORS_H_