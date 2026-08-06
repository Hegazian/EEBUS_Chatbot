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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTREMOVENODECALL_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTREMOVENODECALL_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementRemoveNodeCall
 */
class NetworkManagementRemoveNodeCall : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementRemoveNodeCall();

  /**
   * Construct an instance of this class and set its member.
   * @param c_nodeAddress the member to set
   * @param c_timeout the member to set
   */
  NetworkManagementRemoveNodeCall(const FeatureAddress &c_nodeAddress,
                                  const xs_duration &c_timeout);

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
  bool operator==(const NetworkManagementRemoveNodeCall &c_classObject) const;

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
  bool operator!=(const NetworkManagementRemoveNodeCall &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member NodeAddress.
   * @param c_nodeAddress Value to set
   */
  void setNodeAddress(const FeatureAddress &c_nodeAddress);

  /**
   * Returns const reference to member NodeAddress.
   * @return const reference to member nodeAddress
   */
  const FeatureAddress &getNodeAddress() const;

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
   * Set member Timeout.
   * @param c_timeout Value to set
   */
  void setTimeout(const xs_duration &c_timeout);

  /**
   * Returns const reference to member Timeout.
   * @return const reference to member timeout
   */
  const xs_duration &getTimeout() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_nodeAddressIsSet;
  FeatureAddress m_nodeAddress;

  bool m_timeoutIsSet;
  xs_duration m_timeout;
};

//! typedef for non-const smart pointer type NetworkManagementRemoveNodeCall
using NetworkManagementRemoveNodeCallPtr =
    std::shared_ptr<NetworkManagementRemoveNodeCall>;

//! typedef for const type NetworkManagementRemoveNodeCall
using NetworkManagementRemoveNodeCallConst =
    const NetworkManagementRemoveNodeCall;

//! typedef for const type NetworkManagementRemoveNodeCall
using NetworkManagementRemoveNodeCallConstPtr =
    std::shared_ptr<NetworkManagementRemoveNodeCallConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTREMOVENODECALL_H_