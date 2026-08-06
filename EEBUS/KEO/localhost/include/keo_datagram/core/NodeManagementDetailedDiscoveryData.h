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

#ifndef KEO_DATAGRAM_CORE_NODEMANAGEMENTDETAILEDDISCOVERYDATA_H_
#define KEO_DATAGRAM_CORE_NODEMANAGEMENTDETAILEDDISCOVERYDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryDeviceInformation.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryEntityInformation.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryFeatureInformation.h>
#include <keo_datagram/core/NodeManagementSpecificationVersionList.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration NodeManagementDetailedDiscoveryData
 */
class NodeManagementDetailedDiscoveryData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NodeManagementDetailedDiscoveryData();

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
  bool
  operator==(const NodeManagementDetailedDiscoveryData &c_classObject) const;

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
  bool
  operator!=(const NodeManagementDetailedDiscoveryData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member SpecificationVersionList.
   * @param c_specificationVersionList Value to set
   */
  void setSpecificationVersionList(
      const NodeManagementSpecificationVersionList &c_specificationVersionList);

  /**
   * Returns const reference to member SpecificationVersionList.
   * @return const reference to member specificationVersionList
   */
  const NodeManagementSpecificationVersionList &
  getSpecificationVersionList() const;

  /**
   * Returns if member SpecificationVersionList is set.
   * @retval true member SpecificationVersionList is set
   * @retval false member SpecificationVersionList is not set
   */
  bool getSpecificationVersionListIsSet() const;

  /**
   * Unsets member SpecificationVersionList
   */
  void cleanSpecificationVersionList();

  /**
   * Set member DeviceInformation.
   * @param c_deviceInformation Value to set
   */
  void
  setDeviceInformation(const NodeManagementDetailedDiscoveryDeviceInformation
                           &c_deviceInformation);

  /**
   * Returns const reference to member DeviceInformation.
   * @return const reference to member deviceInformation
   */
  const NodeManagementDetailedDiscoveryDeviceInformation &
  getDeviceInformation() const;

  /**
   * Returns if member DeviceInformation is set.
   * @retval true member DeviceInformation is set
   * @retval false member DeviceInformation is not set
   */
  bool getDeviceInformationIsSet() const;

  /**
   * Unsets member DeviceInformation
   */
  void cleanDeviceInformation();

  /**
   * Set member EntityInformation.
   * @param c_entityInformation Value to set
   */
  void setEntityInformation(
      const std::vector<NodeManagementDetailedDiscoveryEntityInformation>
          &c_entityInformation);

  /**
   * Returns const reference to member EntityInformation.
   * @return const reference to member entityInformation
   */
  const std::vector<NodeManagementDetailedDiscoveryEntityInformation> &
  getEntityInformation() const;

  /**
   * Returns if member EntityInformation is set.
   * @retval true member EntityInformation is set
   * @retval false member EntityInformation is not set
   */
  bool getEntityInformationIsSet() const;

  /**
   * Unsets member EntityInformation
   */
  void cleanEntityInformation();

  /**
   * Set member FeatureInformation.
   * @param c_featureInformation Value to set
   */
  void setFeatureInformation(
      const std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
          &c_featureInformation);

  /**
   * Returns const reference to member FeatureInformation.
   * @return const reference to member featureInformation
   */
  const std::vector<NodeManagementDetailedDiscoveryFeatureInformation> &
  getFeatureInformation() const;

  /**
   * Returns if member FeatureInformation is set.
   * @retval true member FeatureInformation is set
   * @retval false member FeatureInformation is not set
   */
  bool getFeatureInformationIsSet() const;

  /**
   * Unsets member FeatureInformation
   */
  void cleanFeatureInformation();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_specificationVersionListIsSet;
  NodeManagementSpecificationVersionList m_specificationVersionList;

  bool m_deviceInformationIsSet;
  NodeManagementDetailedDiscoveryDeviceInformation m_deviceInformation;

  bool m_entityInformationIsSet;
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
      m_entityInformation;

  bool m_featureInformationIsSet;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
      m_featureInformation;
};

//! typedef for non-const smart pointer type NodeManagementDetailedDiscoveryData
using NodeManagementDetailedDiscoveryDataPtr =
    std::shared_ptr<NodeManagementDetailedDiscoveryData>;

//! typedef for const type NodeManagementDetailedDiscoveryData
using NodeManagementDetailedDiscoveryDataConst =
    const NodeManagementDetailedDiscoveryData;

//! typedef for const type NodeManagementDetailedDiscoveryData
using NodeManagementDetailedDiscoveryDataConstPtr =
    std::shared_ptr<NodeManagementDetailedDiscoveryDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NODEMANAGEMENTDETAILEDDISCOVERYDATA_H_