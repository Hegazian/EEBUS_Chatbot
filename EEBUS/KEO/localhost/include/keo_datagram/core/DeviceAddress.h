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

#ifndef KEO_DATAGRAM_CORE_DEVICEADDRESS_H_
#define KEO_DATAGRAM_CORE_DEVICEADDRESS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DeviceAddressElements.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration DeviceAddress
 */
class DeviceAddress : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  DeviceAddress();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_device the member to set
   */
  explicit DeviceAddress(const xs_string &c_device);

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
  bool operator==(const DeviceAddress &c_classObject) const;

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
  bool operator!=(const DeviceAddress &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Device.
   * @param c_device Value to set
   */
  void setDevice(const xs_string &c_device);

  /**
   * Returns const reference to member Device.
   * @return const reference to member device
   */
  const xs_string &getDevice() const;

  /**
   * Returns if member Device is set.
   * @retval true member Device is set
   * @retval false member Device is not set
   */
  bool getDeviceIsSet() const;

  /**
   * Unsets member Device
   */
  void cleanDevice();

  /**
   * @copydoc CmdData::reduce()
   */
  DeviceAddress reduce(const DeviceAddressElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_deviceIsSet;
  xs_string m_device;
};

//! typedef for non-const smart pointer type DeviceAddress
using DeviceAddressPtr = std::shared_ptr<DeviceAddress>;

//! typedef for const type DeviceAddress
using DeviceAddressConst = const DeviceAddress;

//! typedef for const type DeviceAddress
using DeviceAddressConstPtr = std::shared_ptr<DeviceAddressConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_DEVICEADDRESS_H_