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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTSCANNETWORKCALL_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTSCANNETWORKCALL_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementScanNetworkCall
 */
class NetworkManagementScanNetworkCall : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementScanNetworkCall();

  /**
   * Construct an instance of this class and set its member.
   * @param c_scanSetup the member to set
   * @param c_timeout the member to set
   */
  NetworkManagementScanNetworkCall(const xs_string &c_scanSetup,
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
  bool operator==(const NetworkManagementScanNetworkCall &c_classObject) const;

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
  bool operator!=(const NetworkManagementScanNetworkCall &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member ScanSetup.
   * @param c_scanSetup Value to set
   */
  void setScanSetup(const xs_string &c_scanSetup);

  /**
   * Returns const reference to member ScanSetup.
   * @return const reference to member scanSetup
   */
  const xs_string &getScanSetup() const;

  /**
   * Returns if member ScanSetup is set.
   * @retval true member ScanSetup is set
   * @retval false member ScanSetup is not set
   */
  bool getScanSetupIsSet() const;

  /**
   * Unsets member ScanSetup
   */
  void cleanScanSetup();

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

  bool m_scanSetupIsSet;
  xs_string m_scanSetup;

  bool m_timeoutIsSet;
  xs_duration m_timeout;
};

//! typedef for non-const smart pointer type NetworkManagementScanNetworkCall
using NetworkManagementScanNetworkCallPtr =
    std::shared_ptr<NetworkManagementScanNetworkCall>;

//! typedef for const type NetworkManagementScanNetworkCall
using NetworkManagementScanNetworkCallConst =
    const NetworkManagementScanNetworkCall;

//! typedef for const type NetworkManagementScanNetworkCall
using NetworkManagementScanNetworkCallConstPtr =
    std::shared_ptr<NetworkManagementScanNetworkCallConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTSCANNETWORKCALL_H_