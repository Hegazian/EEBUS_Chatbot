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

#ifndef KEO_SPINE_DATAGRAM_SPINEDATAGRAMLIBRARY_SRC_DETAILEDDISCOVERYPARTIALIMPL_H_
#define KEO_SPINE_DATAGRAM_SPINEDATAGRAMLIBRARY_SRC_DETAILEDDISCOVERYPARTIALIMPL_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */
#include <vector>

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */
#include "DetailedDiscoveryImpl.h"
#include <keo_datagram/core/DetailedDiscoveryPartial.h>

/* ******************************************************************************
 * *
 *  defines *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  types *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  class definition *
 * ******************************************************************************
 */

namespace keo_datagram {

class DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl
    : public DetailedDiscovery::DetailedDiscoveryImpl {
public:
  DetailedDiscoveryPartialImpl();
  ~DetailedDiscoveryPartialImpl();

  bool setByDiffingDetailedDiscoveries(
      const DetailedDiscovery &sourceDetailedDiscovery,
      const DetailedDiscovery &targetDetailedDiscovery);
  DetailedDiscovery
  getMergedDetailedDiscovery(const DetailedDiscovery &sourceDetailedDiscovery,
                             bool *success) const;

  Datagram createPartialDetailedDiscoveryDatagram(const Header &pHeader) const;

  bool setDetailedDiscoveryData(const NodeManagementDetailedDiscoveryData
                                    &detailedDiscoveryData) override;
  bool addDetailedDiscoveryEntityInformation(
      const NodeManagementDetailedDiscoveryEntityInformation &entityInformation)
      override;
  bool addDetailedDiscoveryFeatureInformation(
      const NodeManagementDetailedDiscoveryFeatureInformation
          &featureInformation) override;

  void setDeviceName(const std::string &deviceName);

  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getAddedEntities() const;
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getModifiedEntities() const;
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getRemovedEntities() const;

  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getAddedFeatures() const;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getModifiedFeatures() const;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getRemovedFeatures() const;

  bool isEntityModified(const EntityAddress &entityAddress) const;
  bool isEntityRemoved(const EntityAddress &entityAddress) const;

  bool isFeatureModified(const FeatureAddress &featureAddress) const;
  bool isFeatureRemoved(const FeatureAddress &featureAddress) const;

private:
  static std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getAddedOrRemovedEntities(
      bool getAdded, const DetailedDiscovery::DetailedDiscoveryImpl::
                         entityAddress_EntityData_MapType &entityDataOld,
      const DetailedDiscovery::DetailedDiscoveryImpl::
          entityAddress_EntityData_MapType &entityDataNew);

  static std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getModifiedEntities(const DetailedDiscovery::DetailedDiscoveryImpl::
                          entityAddress_EntityData_MapType &entityDataOld,
                      const DetailedDiscovery::DetailedDiscoveryImpl::
                          entityAddress_EntityData_MapType &entityDataNew);

  static bool isPartialEntityDescriptionMandatorySet(
      const NodeManagementDetailedDiscoveryEntityInformation
          &entityInformationPartial,
      const NetworkManagementStateChange::Value &stateChange);

  static bool containsEntityAddress(
      const EntityAddress &entityAddress,
      const std::vector<NodeManagementDetailedDiscoveryEntityInformation>
          &entityInformationVector);

  std::map<xs_unsignedInt, NodeManagementDetailedDiscoveryFeatureInformation>
  getFeatureDataByEntity(const EntityAddress &entityAddress) const;
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
  getEntitiesByLastStateChange(
      const NetworkManagementStateChange::Value &lastStateChange) const;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getFeaturesByLastStateChange(
      const NetworkManagementStateChange::Value &lastStateChange) const;
  bool isEntityLastStateChange(
      const EntityAddress &entityAddress,
      const NetworkManagementStateChange::Value &lastStateChange) const;
  bool isFeatureLastStateChange(
      const FeatureAddress &featureAddress,
      const NetworkManagementStateChange::Value &lastStateChange) const;

  void cleanLastStateChange(NodeManagementDetailedDiscoveryEntityInformation
                                &entityInformation) const;
};

} /* namespace keo_datagram */

/** @}
 * end of file
 */

#endif // KEO_SPINE_DATAGRAM_SPINEDATAGRAMLIBRARY_SRC_DETAILEDDISCOVERYPARTIALIMPL_H_