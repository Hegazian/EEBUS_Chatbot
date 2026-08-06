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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONLISTDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionData.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementDeviceDescriptionListData
 */
class NetworkManagementDeviceDescriptionListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementDeviceDescriptionListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_networkManagementDeviceDescriptionData the member to set
   */
  explicit NetworkManagementDeviceDescriptionListData(
      const std::vector<NetworkManagementDeviceDescriptionData>
          &c_networkManagementDeviceDescriptionData);

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
      const NetworkManagementDeviceDescriptionListData &c_classObject) const;

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
      const NetworkManagementDeviceDescriptionListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member NetworkManagementDeviceDescriptionData.
   * @param c_networkManagementDeviceDescriptionData Value to set
   */
  void setNetworkManagementDeviceDescriptionData(
      const std::vector<NetworkManagementDeviceDescriptionData>
          &c_networkManagementDeviceDescriptionData);

  /**
   * Returns const reference to member NetworkManagementDeviceDescriptionData.
   * @return const reference to member networkManagementDeviceDescriptionData
   */
  const std::vector<NetworkManagementDeviceDescriptionData> &
  getNetworkManagementDeviceDescriptionData() const;

  /**
   * Returns if member NetworkManagementDeviceDescriptionData is set.
   * @retval true member NetworkManagementDeviceDescriptionData is set
   * @retval false member NetworkManagementDeviceDescriptionData is not set
   */
  bool getNetworkManagementDeviceDescriptionDataIsSet() const;

  /**
   * Unsets member NetworkManagementDeviceDescriptionData
   */
  void cleanNetworkManagementDeviceDescriptionData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_networkManagementDeviceDescriptionDataIsSet;
  std::vector<NetworkManagementDeviceDescriptionData>
      m_networkManagementDeviceDescriptionData;
};

//! typedef for non-const smart pointer type
//! NetworkManagementDeviceDescriptionListData
using NetworkManagementDeviceDescriptionListDataPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionListData>;

//! typedef for const type NetworkManagementDeviceDescriptionListData
using NetworkManagementDeviceDescriptionListDataConst =
    const NetworkManagementDeviceDescriptionListData;

//! typedef for const type NetworkManagementDeviceDescriptionListData
using NetworkManagementDeviceDescriptionListDataConstPtr =
    std::shared_ptr<NetworkManagementDeviceDescriptionListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTDEVICEDESCRIPTIONLISTDATA_H_