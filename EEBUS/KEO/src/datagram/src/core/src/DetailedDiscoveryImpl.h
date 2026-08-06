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

#ifndef __KEO_DATAGRAM_DETAILEDDISCOVERYIMPL_H_
#define __KEO_DATAGRAM_DETAILEDDISCOVERYIMPL_H_

/** @addtogroup SpineDatagram
 * @{
 */

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

#include <keo_datagram/core/DetailedDiscovery.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  class definition                                                          *
 * ************************************************************************** */

namespace keo_datagram {

class DetailedDiscovery::DetailedDiscoveryImpl {
public:
  DetailedDiscoveryImpl();
  virtual ~DetailedDiscoveryImpl();

  /// copy constructor
  DetailedDiscoveryImpl(const DetailedDiscoveryImpl &that);

  /// assignment operator
  DetailedDiscoveryImpl &operator=(const DetailedDiscoveryImpl &that);

  void clear();

  bool isEmpty() const;

  NodeManagementDetailedDiscoveryDataPtr getDetailedDiscoveryDataPtr() const;

  virtual bool
  setDetailedDiscoveryData(const NodeManagementDetailedDiscoveryData &);

  NodeManagementSpecificationVersionList getSpecificationVersionList() const;
  void
  setSpecificationVersionList(const NodeManagementSpecificationVersionList &);

  NetworkManagementDeviceDescriptionData getDeviceDescription() const;
  void setDeviceDescription(const NetworkManagementDeviceDescriptionData &);

  bool getDeviceNameIsSet() const;
  std::string getDeviceName() const;

  virtual bool addDetailedDiscoveryEntityInformation(
      const NodeManagementDetailedDiscoveryEntityInformation &);

  NodeManagementDetailedDiscoveryEntityInformationPtr
  getDetailedDiscoveryEntityInformation(
      const EntityAddress &entityAddress) const;

  virtual bool addDetailedDiscoveryFeatureInformation(
      const NodeManagementDetailedDiscoveryFeatureInformation &);

  NodeManagementDetailedDiscoveryFeatureInformationPtr
  getDetailedDiscoveryFeatureInformation(const EntityAddress &entityAddress,
                                         xs_unsignedInt featureId) const;

  // Queries
  bool containsEntityAddress(const EntityAddress &entityAddress) const;

  bool containsEntityType(const xs_string &entityType) const;

  bool containsFeatureIdOnEntity(const EntityAddress &entityAddress,
                                 xs_unsignedInt featureId) const;

  bool containsFeatureType(const xs_string &featureType) const;

  bool containsFeatureTypeOnEntity(const EntityAddress &entityAddress,
                                   const xs_string &featureType) const;

  // entity

  /// Returns all entites.
  std::vector<EntityAddress> getEntities() const;

  /// Returns the list of all entities with entity type entityType.
  std::vector<EntityAddress>
  getEntitiesByEntityType(const xs_string &entityType) const;

  /// Returns the list of all entities with feature type featureType.
  std::vector<EntityAddress>
  getEntitiesByFeatureType(const xs_string &featureType) const;

  // feature

  /// Returns all features on entity entityAddress.
  std::vector<xs_unsignedInt>
  getFeatures(const EntityAddress entityAddress) const;

  std::vector<xs_unsignedInt>
  getFeaturesByFeatureType(const EntityAddress &entityAddress,
                           const xs_string &featureType) const;

  std::vector<FunctionProperty>
  getFunctionPropertiesByFeature(const EntityAddress &entityAddress,
                                 xs_unsignedInt feature) const;

  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getFeatureInformation() const;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
  getFeatureInformationByEntity(const EntityAddress &entityAddress) const;

  bool setLastStateChangeOfEntity(
      const EntityAddress &entityAddress,
      const NetworkManagementStateChange::Value &lastStateChange);

  void removeFeature(const EntityAddress &entityAddress,
                     xs_unsignedInt featureId);
  void removeEntityWithFeatures(const EntityAddress &entityAddress);

private:
  bool setDetailedDiscoveryData(const NodeManagementDetailedDiscoveryData &,
                                bool);
  bool addDetailedDiscoveryEntityInformation(
      const NodeManagementDetailedDiscoveryEntityInformation &, bool);
  bool addDetailedDiscoveryFeatureInformation(
      const NodeManagementDetailedDiscoveryFeatureInformation &, bool, bool,
      bool);

private:
  NodeManagementSpecificationVersionList m_SpecificationVersionList;
  NetworkManagementDeviceDescriptionData m_DeviceDescriptionData;

  // the information entity group
  using entityAddress_EntityData_MapType =
      std::map<EntityAddress, NodeManagementDetailedDiscoveryEntityInformation>;
  /// node description data for entities
  entityAddress_EntityData_MapType m_DeviceEntityData;

  // the information feature group
  using featureId_FeatureData_MapType =
      std::map<xs_unsignedInt,
               NodeManagementDetailedDiscoveryFeatureInformation>;
  using entityAddress_featureId_FeatureData_Map_MapType =
      std::map<EntityAddress, featureId_FeatureData_MapType>;
  /// node description data for features  key:featureId
  entityAddress_featureId_FeatureData_Map_MapType m_DeviceFeatureData;

  // entity types
  using entityType_entityAddress_MultiMapType =
      std::multimap<xs_string, EntityAddress>;
  /// entity types
  entityType_entityAddress_MultiMapType m_EntityTypes;

  /// ClassIds by entity
  using featureType_entityAddress_MultiMapType =
      std::multimap<xs_string, EntityAddress>;
  /// FeatureTyppes by entity key:featureTYPE value:entityID
  featureType_entityAddress_MultiMapType m_FeatureTypeByEntity;

  using featureType_featureId_MultiMapType =
      std::multimap<xs_string, xs_unsignedInt>;
  using entityAddress_featureType_featureId_MultiMap_MapType =
      std::map<EntityAddress, featureType_featureId_MultiMapType>;
  /// ContextIds by feature
  entityAddress_featureType_featureId_MultiMap_MapType m_FeatureTypeByFeature;

  bool m_SpecificationVersionListIsSet;
  bool m_DeviceDescriptionDataIsSet;

  friend class DetailedDiscoveryPartial;
};

} // end namespace keo_datagram

/** @}
 * end of file
 */

#endif // __KEO_DATAGRAM_DETAILEDDISCOVERYIMPL_H_