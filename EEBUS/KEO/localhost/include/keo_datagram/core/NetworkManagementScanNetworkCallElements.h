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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTSCANNETWORKCALLELEMENTS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTSCANNETWORKCALLELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementScanNetworkCallElements
 */
class NetworkManagementScanNetworkCallElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementScanNetworkCallElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_scanSetupIsSet the member to set
   * @param c_timeoutIsSet the member to set
   */
  NetworkManagementScanNetworkCallElements(xs_boolean c_scanSetupIsSet,
                                           xs_boolean c_timeoutIsSet);

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
      const NetworkManagementScanNetworkCallElements &c_classObject) const;

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
      const NetworkManagementScanNetworkCallElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member ScanSetup.
   */
  void setScanSetup();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_scanSetupIsSet;

  // ElementTag
  bool m_timeoutIsSet;
};

//! typedef for non-const smart pointer type
//! NetworkManagementScanNetworkCallElements
using NetworkManagementScanNetworkCallElementsPtr =
    std::shared_ptr<NetworkManagementScanNetworkCallElements>;

//! typedef for const type NetworkManagementScanNetworkCallElements
using NetworkManagementScanNetworkCallElementsConst =
    const NetworkManagementScanNetworkCallElements;

//! typedef for const type NetworkManagementScanNetworkCallElements
using NetworkManagementScanNetworkCallElementsConstPtr =
    std::shared_ptr<NetworkManagementScanNetworkCallElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTSCANNETWORKCALLELEMENTS_H_