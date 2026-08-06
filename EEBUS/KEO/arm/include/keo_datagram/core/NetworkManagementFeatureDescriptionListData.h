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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONLISTDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionData.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NetworkManagementFeatureDescriptionListData
 */
class NetworkManagementFeatureDescriptionListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementFeatureDescriptionListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_networkManagementFeatureDescriptionData the member to set
   */
  explicit NetworkManagementFeatureDescriptionListData(
      const std::vector<NetworkManagementFeatureDescriptionData>
          &c_networkManagementFeatureDescriptionData);

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
      const NetworkManagementFeatureDescriptionListData &c_classObject) const;

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
      const NetworkManagementFeatureDescriptionListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member NetworkManagementFeatureDescriptionData.
   * @param c_networkManagementFeatureDescriptionData Value to set
   */
  void setNetworkManagementFeatureDescriptionData(
      const std::vector<NetworkManagementFeatureDescriptionData>
          &c_networkManagementFeatureDescriptionData);

  /**
   * Returns const reference to member NetworkManagementFeatureDescriptionData.
   * @return const reference to member networkManagementFeatureDescriptionData
   */
  const std::vector<NetworkManagementFeatureDescriptionData> &
  getNetworkManagementFeatureDescriptionData() const;

  /**
   * Returns if member NetworkManagementFeatureDescriptionData is set.
   * @retval true member NetworkManagementFeatureDescriptionData is set
   * @retval false member NetworkManagementFeatureDescriptionData is not set
   */
  bool getNetworkManagementFeatureDescriptionDataIsSet() const;

  /**
   * Unsets member NetworkManagementFeatureDescriptionData
   */
  void cleanNetworkManagementFeatureDescriptionData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_networkManagementFeatureDescriptionDataIsSet;
  std::vector<NetworkManagementFeatureDescriptionData>
      m_networkManagementFeatureDescriptionData;
};

//! typedef for non-const smart pointer type
//! NetworkManagementFeatureDescriptionListData
using NetworkManagementFeatureDescriptionListDataPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionListData>;

//! typedef for const type NetworkManagementFeatureDescriptionListData
using NetworkManagementFeatureDescriptionListDataConst =
    const NetworkManagementFeatureDescriptionListData;

//! typedef for const type NetworkManagementFeatureDescriptionListData
using NetworkManagementFeatureDescriptionListDataConstPtr =
    std::shared_ptr<NetworkManagementFeatureDescriptionListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTFEATUREDESCRIPTIONLISTDATA_H_