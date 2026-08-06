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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/DeviceAddress.h>
#include <keo_datagram/core/DeviceType.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementDeviceDescriptionListDataSelectors
 */
class NetworkManagementDeviceDescriptionListDataSelectors
    : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementDeviceDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_deviceAddress the member to set
   * @param c_deviceType the member to set
   */
  NetworkManagementDeviceDescriptionListDataSelectors(
      const DeviceAddress &c_deviceAddress, const DeviceType &c_deviceType);

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
  bool operator==(const NetworkManagementDeviceDescriptionListDataSelectors
                      &c_classObject) const;

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
  bool operator!=(const NetworkManagementDeviceDescriptionListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member DeviceAddress.
   * @param c_deviceAddress Value to set
   */
  void setDeviceAddress(const DeviceAddress &c_deviceAddress);

  /**
   * Returns const reference to member DeviceAddress.
   * @return const reference to member deviceAddress
   */
  const DeviceAddress &getDeviceAddress() const;

  /**
   * Returns if member DeviceAddress is set.
   * @retval true member DeviceAddress is set
   * @retval false member DeviceAddress is not set
   */
  bool getDeviceAddressIsSet() const;

  /**
   * Unsets member DeviceAddress
   */
  void cleanDeviceAddress();

  /**
   * Set member DeviceType.
   * @param c_deviceType Value to set
   */
  void setDeviceType(const DeviceType &c_deviceType);

  /**
   * Returns const reference to member DeviceType.
   * @return const reference to member deviceType
   */
  const DeviceType &getDeviceType() const;

  /**
   * Returns if member DeviceType is set.
   * @retval true member DeviceType is set
   * @retval false member DeviceType is not set
   */
  bool getDeviceTypeIsSet() const;

  /**
   * Unsets member DeviceType
   */
  void cleanDeviceType();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_deviceAddressIsSet;
  DeviceAddress m_deviceAddress;

  bool m_deviceTypeIsSet;
  DeviceType m_deviceType;
};

//! typedef for non-const smart pointer type
//! NetworkManagementDeviceDescriptionListDataSelectors
using NetworkManagementDeviceDescriptionListDataSelectorsPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionListDataSelectors>;

//! typedef for const type NetworkManagementDeviceDescriptionListDataSelectors
using NetworkManagementDeviceDescriptionListDataSelectorsConst =
    const NetworkManagementDeviceDescriptionListDataSelectors;

//! typedef for const type NetworkManagementDeviceDescriptionListDataSelectors
using NetworkManagementDeviceDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONLISTDATASELECTORS_H_