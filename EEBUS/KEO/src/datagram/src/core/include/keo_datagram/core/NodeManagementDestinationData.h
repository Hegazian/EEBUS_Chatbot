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

#ifndef KEO_DATAGRAM_CORE_NODEMANAGEMENTDESTINATIONDATA_H_
#define KEO_DATAGRAM_CORE_NODEMANAGEMENTDESTINATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionData.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NodeManagementDestinationData
 */
class NodeManagementDestinationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  NodeManagementDestinationData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_deviceDescription the member to set
   */
  explicit NodeManagementDestinationData(
      const NetworkManagementDeviceDescriptionData &c_deviceDescription);

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
  bool operator==(const NodeManagementDestinationData &c_classObject) const;

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
  bool operator!=(const NodeManagementDestinationData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member DeviceDescription.
   * @param c_deviceDescription Value to set
   */
  void setDeviceDescription(
      const NetworkManagementDeviceDescriptionData &c_deviceDescription);

  /**
   * Returns const reference to member DeviceDescription.
   * @return const reference to member deviceDescription
   */
  const NetworkManagementDeviceDescriptionData &getDeviceDescription() const;

  /**
   * Returns if member DeviceDescription is set.
   * @retval true member DeviceDescription is set
   * @retval false member DeviceDescription is not set
   */
  bool getDeviceDescriptionIsSet() const;

  /**
   * Unsets member DeviceDescription
   */
  void cleanDeviceDescription();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_deviceDescriptionIsSet;
  NetworkManagementDeviceDescriptionData m_deviceDescription;
};

//! typedef for non-const smart pointer type NodeManagementDestinationData
using NodeManagementDestinationDataPtr =
    std::shared_ptr<NodeManagementDestinationData>;

//! typedef for const type NodeManagementDestinationData
using NodeManagementDestinationDataConst = const NodeManagementDestinationData;

//! typedef for const type NodeManagementDestinationData
using NodeManagementDestinationDataConstPtr =
    std::shared_ptr<NodeManagementDestinationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NODEMANAGEMENTDESTINATIONDATA_H_