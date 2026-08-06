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

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

#include <algorithm>
#include <iterator>
#include <vector>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

#include "DetailedDiscoveryImpl.h"
#include <keo_spine_datagramVersion.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  definition                                                                *
 * ************************************************************************** */

namespace keo_datagram {

template <typename KEY, typename VALUE>
std::vector<VALUE> getMultiMapValues(const std::multimap<KEY, VALUE> &map,
                                     const KEY &key) {
  std::vector<VALUE> values;
  std::pair<typename std::multimap<KEY, VALUE>::const_iterator,
            typename std::multimap<KEY, VALUE>::const_iterator>
      range = map.equal_range(key);
  typename std::multimap<KEY, VALUE>::const_iterator it;
  for (it = range.first; it != range.second; ++it) {
    values.push_back(it->second);
  }
  return values;
}

struct RetrieveKey {
  template <typename T>
  typename T::first_type operator()(T keyValuePair) const {
    return keyValuePair.first;
  }
};

template <typename _key, typename _Tp>
void erase_if(std::multimap<_key, _Tp> &items, const _key &key,
              const _Tp &value) {
  typedef typename std::multimap<_key, _Tp>::iterator iterator;
  std::pair<iterator, iterator> iterpair = items.equal_range(key);

  typename std::multimap<_key, _Tp>::iterator it = iterpair.first;
  for (; it != iterpair.second;) {
    if (it->second == value) {
      items.erase(it++);
    } else {
      it++;
    }
  }
}

void DetailedDiscovery::DetailedDiscoveryImpl::clear() {
  m_DeviceDescriptionData.cleanCommunicationsTechnologyInformation();
  m_DeviceDescriptionData.cleanDescription();
  m_DeviceDescriptionData.cleanDeviceAddress();
  m_DeviceDescriptionData.cleanDeviceType();
  m_DeviceDescriptionData.cleanLabel();
  m_DeviceDescriptionData.cleanLastStateChange();
  m_DeviceDescriptionData.cleanMinimumTrustLevel();
  m_DeviceDescriptionData.cleanNativeSetup();
  m_DeviceDescriptionData.cleanNetworkFeatureSet();
  m_DeviceDescriptionData.cleanNetworkManagementResponsibleAddress();
  m_DeviceDescriptionData.cleanTechnologyAddress();

  m_SpecificationVersionList.cleanSpecificationVersion();
  m_DeviceEntityData.clear();
  m_DeviceFeatureData.clear();
  m_EntityTypes.clear();
  m_FeatureTypeByEntity.clear();
  m_FeatureTypeByFeature.clear();

  m_SpecificationVersionListIsSet = false;
  m_DeviceDescriptionDataIsSet = false;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::isEmpty() const {
  return !m_DeviceDescriptionData.getDeviceAddressIsSet();
}

DetailedDiscovery::DetailedDiscoveryImpl::DetailedDiscoveryImpl()
    : m_SpecificationVersionListIsSet(false),
      m_DeviceDescriptionDataIsSet(false) {}

/// copy constructor
DetailedDiscovery::DetailedDiscoveryImpl::DetailedDiscoveryImpl(
    const DetailedDiscovery::DetailedDiscoveryImpl &that)
    : m_SpecificationVersionList(that.m_SpecificationVersionList),
      m_DeviceDescriptionData(that.m_DeviceDescriptionData),
      m_DeviceEntityData(that.m_DeviceEntityData),
      m_DeviceFeatureData(that.m_DeviceFeatureData),
      m_EntityTypes(that.m_EntityTypes),
      m_FeatureTypeByEntity(that.m_FeatureTypeByEntity),
      m_FeatureTypeByFeature(that.m_FeatureTypeByFeature),
      m_SpecificationVersionListIsSet(that.m_SpecificationVersionListIsSet),
      m_DeviceDescriptionDataIsSet(that.m_DeviceDescriptionDataIsSet) {}

/// assignment operator
DetailedDiscovery::DetailedDiscoveryImpl &
DetailedDiscovery::DetailedDiscoveryImpl::
operator=(const DetailedDiscovery::DetailedDiscoveryImpl &that) {
  if (this != &that) {
    std::vector<xs_string> versionList;
    versionList.push_back(SPINE_VERSION_STRING);
    m_SpecificationVersionList.setSpecificationVersion(versionList);
    m_DeviceDescriptionData = that.m_DeviceDescriptionData;
    m_DeviceEntityData = that.m_DeviceEntityData;
    m_DeviceFeatureData = that.m_DeviceFeatureData;
    m_EntityTypes = that.m_EntityTypes;
    m_FeatureTypeByEntity = that.m_FeatureTypeByEntity;
    m_FeatureTypeByFeature = that.m_FeatureTypeByFeature;
    m_SpecificationVersionListIsSet = that.m_SpecificationVersionListIsSet;
    m_DeviceDescriptionDataIsSet = that.m_DeviceDescriptionDataIsSet;
  }
  return *this;
}

DetailedDiscovery::DetailedDiscoveryImpl::~DetailedDiscoveryImpl() {}

bool DetailedDiscovery::DetailedDiscoveryImpl::containsEntityAddress(
    const EntityAddress &entityAddress) const {
  return m_DeviceEntityData.find(entityAddress) != m_DeviceEntityData.end();
}

bool DetailedDiscovery::DetailedDiscoveryImpl::containsEntityType(
    const xs_string &entityType) const {
  return m_EntityTypes.find(entityType) != m_EntityTypes.end();
}

bool DetailedDiscovery::DetailedDiscoveryImpl::containsFeatureType(
    const xs_string &featureType) const {
  return m_FeatureTypeByEntity.find(featureType) != m_FeatureTypeByEntity.end();
}

bool DetailedDiscovery::DetailedDiscoveryImpl::containsFeatureIdOnEntity(
    const EntityAddress &entityAddress, xs_unsignedInt featureId) const {
  bool retval = false;

  entityAddress_featureId_FeatureData_Map_MapType::const_iterator entityIt =
      m_DeviceFeatureData.find(entityAddress);
  if (entityIt != m_DeviceFeatureData.end()) {
    featureId_FeatureData_MapType::const_iterator featureIt =
        entityIt->second.find(featureId);
    retval = (featureIt != entityIt->second.end());
  }

  return retval;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::containsFeatureTypeOnEntity(
    const EntityAddress &entityAddress, const xs_string &featureType) const {
  bool retval = false;

  entityAddress_featureType_featureId_MultiMap_MapType::const_iterator it =
      m_FeatureTypeByFeature.find(entityAddress);
  if (it != m_FeatureTypeByFeature.end()) {
    retval = it->second.find(featureType) != it->second.end();
  }

  return retval;
}

NodeManagementSpecificationVersionList
DetailedDiscovery::DetailedDiscoveryImpl::getSpecificationVersionList() const {
  return m_SpecificationVersionList;
}

void DetailedDiscovery::DetailedDiscoveryImpl::setSpecificationVersionList(
    const NodeManagementSpecificationVersionList &specificationVersionList) {
  if (!specificationVersionList.isEmpty()) {
    m_SpecificationVersionList.setSpecificationVersion(
        specificationVersionList.getSpecificationVersion());
    m_SpecificationVersionListIsSet = true;
  } else {
    m_SpecificationVersionList.cleanSpecificationVersion();
    m_SpecificationVersionListIsSet = false;
  }
}

NetworkManagementDeviceDescriptionData
DetailedDiscovery::DetailedDiscoveryImpl::getDeviceDescription() const {
  return m_DeviceDescriptionData;
}

void DetailedDiscovery::DetailedDiscoveryImpl::setDeviceDescription(
    const NetworkManagementDeviceDescriptionData &deviceDescriptionData) {
  if (!deviceDescriptionData.isEmpty()) {
    m_DeviceDescriptionData = deviceDescriptionData;
    m_DeviceDescriptionDataIsSet = true;
  } else {
    m_DeviceDescriptionData.cleanDescription();
    m_DeviceDescriptionDataIsSet = false;
  }
}

bool DetailedDiscovery::DetailedDiscoveryImpl::getDeviceNameIsSet() const {
  bool isSet = false;
  if (m_DeviceDescriptionDataIsSet) {
    isSet = !(getDeviceDescription().getDeviceAddress().getDevice().empty());
  }
  return isSet;
}

std::string DetailedDiscovery::DetailedDiscoveryImpl::getDeviceName() const {
  std::string deviceName;
  if (m_DeviceDescriptionDataIsSet) {
    deviceName = getDeviceDescription().getDeviceAddress().getDevice();
  }
  return deviceName;
}

NodeManagementDetailedDiscoveryDataPtr
DetailedDiscovery::DetailedDiscoveryImpl::getDetailedDiscoveryDataPtr() const {
  NodeManagementDetailedDiscoveryDataPtr informationPtr =
      NodeManagementDetailedDiscoveryDataPtr(
          new NodeManagementDetailedDiscoveryData());

  // attach device information
  if (m_SpecificationVersionListIsSet) {
    informationPtr->setSpecificationVersionList(m_SpecificationVersionList);
  }
  if (m_DeviceDescriptionDataIsSet) {
    informationPtr->setDeviceInformation(
        NodeManagementDetailedDiscoveryDeviceInformation(
            m_DeviceDescriptionData));
  }

  // attach all entities
  entityAddress_EntityData_MapType::const_iterator entityIterator =
      m_DeviceEntityData.begin();
  std::vector<NodeManagementDetailedDiscoveryEntityInformation> entityList;

  for (entityIterator = m_DeviceEntityData.begin();
       entityIterator != m_DeviceEntityData.end(); entityIterator++) {
    entityList.push_back(entityIterator->second);
  }

  if (entityList.size() > 0) {
    informationPtr->setEntityInformation(entityList);
  }

  // attach all features
  entityAddress_featureId_FeatureData_Map_MapType::const_iterator
      entityFeatureIterator;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation> featureList;

  for (entityFeatureIterator = m_DeviceFeatureData.begin();
       entityFeatureIterator != m_DeviceFeatureData.end();
       entityFeatureIterator++) {
    featureId_FeatureData_MapType::const_iterator featureIterator;

    for (featureIterator = entityFeatureIterator->second.begin();
         featureIterator != entityFeatureIterator->second.end();
         featureIterator++) {
      featureList.push_back(featureIterator->second);
    }
  }
  if (featureList.size() > 0) {
    informationPtr->setFeatureInformation(featureList);
  }

  return informationPtr;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::setDetailedDiscoveryData(
    const NodeManagementDetailedDiscoveryData &detailedDiscoveryData,
    bool forceFullMandatory) {
  bool retval = true; // optimistic

  if ((!forceFullMandatory /*&& detailedDiscoveryData.getEntityInformationIsSet()*/) ||
      (detailedDiscoveryData.getSpecificationVersionListIsSet() &&
       detailedDiscoveryData.getDeviceInformationIsSet() &&
       detailedDiscoveryData.getDeviceInformation().getDescriptionIsSet() &&
       detailedDiscoveryData.getDeviceInformation()
           .getDescription()
           .getDeviceAddressIsSet() &&
       detailedDiscoveryData.getEntityInformationIsSet() &&
       detailedDiscoveryData.getFeatureInformationIsSet())) {
    m_SpecificationVersionListIsSet =
        detailedDiscoveryData.getSpecificationVersionListIsSet();
    if (m_SpecificationVersionListIsSet) {
      m_SpecificationVersionList =
          detailedDiscoveryData.getSpecificationVersionList();
    }

    m_DeviceDescriptionDataIsSet =
        (detailedDiscoveryData.getDeviceInformationIsSet() &&
         detailedDiscoveryData.getDeviceInformation().getDescriptionIsSet());
    if (m_DeviceDescriptionDataIsSet) {
      m_DeviceDescriptionData =
          detailedDiscoveryData.getDeviceInformation().getDescription();
    }

    // for all entities
    std::vector<NodeManagementDetailedDiscoveryEntityInformation> entites =
        detailedDiscoveryData.getEntityInformation();

    std::vector<NodeManagementDetailedDiscoveryEntityInformation>::iterator
        entityIterator = entites.begin();

    // TODO check if at least entity 0 exists (only if forceFullMandatory is set
    // to true)
    if (forceFullMandatory &&
        !detailedDiscoveryData.getEntityInformationIsSet()) {
      retval = false;
    } else {
      while (entityIterator != entites.end() && retval) {
        retval &= addDetailedDiscoveryEntityInformation(*entityIterator);
        entityIterator++;
      }
    }

    if (retval) {
      // for all features
      std::vector<NodeManagementDetailedDiscoveryFeatureInformation> features =
          detailedDiscoveryData.getFeatureInformation();

      std::vector<NodeManagementDetailedDiscoveryFeatureInformation>::iterator
          featuresIterator = features.begin();

      while (featuresIterator != features.end() && retval) {
        retval &= addDetailedDiscoveryFeatureInformation(*featuresIterator);

        featuresIterator++;
      }
    }
  } else {
    retval = false;
  }

  return retval;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::setDetailedDiscoveryData(
    const NodeManagementDetailedDiscoveryData &detailedDiscoveryData) {
  return setDetailedDiscoveryData(
      detailedDiscoveryData, true /* enforce full mandatory options set */);
}

std::vector<EntityAddress>
DetailedDiscovery::DetailedDiscoveryImpl::getEntities() const {
  std::vector<EntityAddress> values;

  std::transform(m_DeviceEntityData.begin(), m_DeviceEntityData.end(),
                 back_inserter(values), RetrieveKey());

  return values;
}

std::vector<EntityAddress>
DetailedDiscovery::DetailedDiscoveryImpl::getEntitiesByEntityType(
    const xs_string &entityType) const {
  return getMultiMapValues<xs_string, EntityAddress>(m_EntityTypes, entityType);
}

std::vector<EntityAddress>
DetailedDiscovery::DetailedDiscoveryImpl::getEntitiesByFeatureType(
    const xs_string &featureType) const {
  return getMultiMapValues<xs_string, EntityAddress>(m_FeatureTypeByEntity,
                                                     featureType);
}

std::vector<xs_unsignedInt>
DetailedDiscovery::DetailedDiscoveryImpl::getFeatures(
    const EntityAddress entityAddress) const {
  std::vector<xs_unsignedInt> retval;

  entityAddress_featureId_FeatureData_Map_MapType::const_iterator it =
      m_DeviceFeatureData.find(entityAddress);
  if (it != m_DeviceFeatureData.end()) {
    featureId_FeatureData_MapType::const_iterator featuresIterator =
        it->second.begin();

    while (featuresIterator != it->second.end()) {
      retval.push_back(featuresIterator->first);
      featuresIterator++;
    }
  }

  return retval;
}

std::vector<xs_unsignedInt>
DetailedDiscovery::DetailedDiscoveryImpl::getFeaturesByFeatureType(
    const EntityAddress &entityAddress, const xs_string &featureType) const {
  std::vector<xs_unsignedInt> retval;
  entityAddress_featureType_featureId_MultiMap_MapType::const_iterator it =
      m_FeatureTypeByFeature.find(entityAddress);
  if (it != m_FeatureTypeByFeature.end()) {
    retval =
        getMultiMapValues<xs_string, xs_unsignedInt>(it->second, featureType);
  }

  return retval;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::
    addDetailedDiscoveryEntityInformation(
        const NodeManagementDetailedDiscoveryEntityInformation
            &entityInformation,
        bool forceEntityTypeIsSet) {

  bool retval = false;

  //    std::cout << __PRETTY_FUNCTION__ << std::endl;
  //    std::cout << "entityInformation.getDescriptionIsSet(): " <<
  //    entityInformation.getDescriptionIsSet() << std::endl;
  //    std::cout <<
  //    "entityInformation.getDescription().getEntityAddressIsSet(): " <<
  //    entityInformation.getDescription().getEntityAddressIsSet() << std::endl;
  //    std::cout <<
  //    "entityInformation.getDescription().getEntityAddress().getEntityIsSet():
  //    " <<
  //    entityInformation.getDescription().getEntityAddress().getEntityIsSet()
  //    << std::endl;
  //    std::cout << "entityInformation.getDescription().getEntityTypeIsSet()):
  //    " << entityInformation.getDescription().getEntityTypeIsSet() <<
  //    std::endl;
  //    std::cout << "forceEntityTypeIsSet: " << forceEntityTypeIsSet <<
  //    std::endl;

  if ( // entityInformation.getNodeDescriptionIsSet() && // mandatory?
      entityInformation.getDescriptionIsSet() &&
      entityInformation.getDescription().getEntityAddressIsSet() &&
      entityInformation.getDescription().getEntityAddress().getEntityIsSet() &&
      (forceEntityTypeIsSet
           ? entityInformation.getDescription().getEntityTypeIsSet()
           : true)) {
    EntityAddress entityAddress;
    entityAddress.setEntity(
        entityInformation.getDescription().getEntityAddress().getEntity());

    entityAddress_EntityData_MapType::iterator lb =
        m_DeviceEntityData.lower_bound(entityAddress);

    if (lb != m_DeviceEntityData.end() &&
        !(m_DeviceEntityData.key_comp()(entityAddress, lb->first))) {
      // address already exists -> replace

      // remove from entity type
      if (lb->second.getDescriptionIsSet() &&
          lb->second.getDescription().getEntityTypeIsSet()) {
        erase_if<std::string, EntityAddress>(
            m_EntityTypes,
            lb->second.getDescription().getEntityType().toString(), lb->first);
      }

      // replace entity information
      lb->second = entityInformation;
    } else {
      // address does not exist in map
      // add it to the map
      m_DeviceEntityData.insert(
          lb, entityAddress_EntityData_MapType::value_type(entityAddress,
                                                           entityInformation));
    }

    m_EntityTypes.insert(std::make_pair(
        entityInformation.getDescription().getEntityType().toString(),
        entityAddress));

    retval = true;
  }

  return retval;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::
    addDetailedDiscoveryEntityInformation(
        const NodeManagementDetailedDiscoveryEntityInformation
            &entityInformation) {
  return addDetailedDiscoveryEntityInformation(
      entityInformation, true /* enforce entity type set */);
}

NodeManagementDetailedDiscoveryEntityInformationPtr
DetailedDiscovery::DetailedDiscoveryImpl::getDetailedDiscoveryEntityInformation(
    const EntityAddress &entityAddress) const {
  NodeManagementDetailedDiscoveryEntityInformationPtr detailedInformationPtr;

  entityAddress_EntityData_MapType::const_iterator it =
      m_DeviceEntityData.find(entityAddress);

  if (it != m_DeviceEntityData.end()) {
    detailedInformationPtr =
        NodeManagementDetailedDiscoveryEntityInformationPtr(
            new NodeManagementDetailedDiscoveryEntityInformation(it->second));
  }

  return detailedInformationPtr;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::
    addDetailedDiscoveryFeatureInformation(
        const NodeManagementDetailedDiscoveryFeatureInformation
            &featureInformation,
        bool forceFeatureTypeIsSet, bool forceRoleIsSet,
        bool forceExistingEntity) {
  bool retval = false;

  //    std::cout << __PRETTY_FUNCTION__ << std::endl;
  //    std::cout << "featureInformation.getDescriptionIsSet: " <<
  //    featureInformation.getDescriptionIsSet() << std::endl;
  //    if ( featureInformation.getDescriptionIsSet())
  //    {
  //        std::cout <<
  //        "featureInformation.getDescription().getFeatureAddressIsSet(): " <<
  //        featureInformation.getDescription().getFeatureAddressIsSet() <<
  //        std::endl;
  //        if (featureInformation.getDescription().getFeatureAddressIsSet())
  //        {
  //            std::cout <<
  //            "featureInformation.getDescription().getFeatureAddress().getEntityIsSet():
  //            " <<
  //            featureInformation.getDescription().getFeatureAddress().getEntityIsSet()
  //            << std::endl;
  //            std::cout <<
  //            "featureInformation.getDescription().getFeatureAddress().getFeatureIsSet():
  //            " <<
  //            featureInformation.getDescription().getFeatureAddress().getFeatureIsSet()
  //            << std::endl;
  //            std::cout <<
  //            "featureInformation.getDescription().getFeatureTypeIsSet(): " <<
  //            featureInformation.getDescription().getFeatureTypeIsSet() <<
  //            std::endl;
  //            std::cout <<
  //            "featureInformation.getDescription().getRoleIsSet(): " <<
  //            featureInformation.getDescription().getRoleIsSet() << std::endl;
  //        }
  //    }

  if ( // featureInformation.getNodeDescriptionIsSet() && // mandatory?
      featureInformation.getDescriptionIsSet() &&
      featureInformation.getDescription().getFeatureAddressIsSet() &&
      featureInformation.getDescription()
          .getFeatureAddress()
          .getEntityIsSet() &&
      featureInformation.getDescription()
          .getFeatureAddress()
          .getFeatureIsSet() &&
      (forceFeatureTypeIsSet
           ? featureInformation.getDescription().getFeatureTypeIsSet()
           : true) &&
      (forceRoleIsSet ? featureInformation.getDescription().getRoleIsSet()
                      : true)) {
    // check entity address
    EntityAddress entityAddress;
    entityAddress.setEntity(
        featureInformation.getDescription().getFeatureAddress().getEntity());

    if (!forceExistingEntity || containsEntityAddress(entityAddress)) {
      xs_unsignedInt featureId =
          featureInformation.getDescription().getFeatureAddress().getFeature();

      removeFeature(entityAddress, featureId);

      // get feature map for the entity
      featureId_FeatureData_MapType &features =
          m_DeviceFeatureData[entityAddress];

      if (!features.insert(std::make_pair(featureId, featureInformation))
               .second) {
        //  Element already present
        features[featureId] = featureInformation;
      }
      // m_DeviceFeatureData[entityId] = features;

      if (featureInformation.getDescription().getFeatureTypeIsSet()) {
        // Feature type handling
        featureType_entityAddress_MultiMapType::iterator featureTypeIterator;

        for (featureTypeIterator = m_FeatureTypeByEntity.begin();
             featureTypeIterator != m_FeatureTypeByEntity.end();
             ++featureTypeIterator) {
          if (featureTypeIterator->first ==
                  featureInformation.getDescription()
                      .getFeatureType()
                      .toString() &&
              featureTypeIterator->second == entityAddress) {
            break;
          }
        }

        if (featureTypeIterator == m_FeatureTypeByEntity.end()) {
          m_FeatureTypeByEntity.insert(std::make_pair(
              featureInformation.getDescription().getFeatureType().toString(),
              entityAddress));
        }

        entityAddress_featureType_featureId_MultiMap_MapType::iterator
            featureTypeByFeatureIterator =
                m_FeatureTypeByFeature.find(entityAddress);

        featureType_featureId_MultiMapType featuresFeatureTypes =
            (featureTypeByFeatureIterator != m_FeatureTypeByFeature.end())
                ? featureTypeByFeatureIterator->second
                : featureType_featureId_MultiMapType();

        featuresFeatureTypes.insert(std::make_pair(
            featureInformation.getDescription().getFeatureType().toString(),
            featureId));

        if (!m_FeatureTypeByFeature
                 .insert(std::make_pair(entityAddress, featuresFeatureTypes))
                 .second) {
          //  Element already present
          m_FeatureTypeByFeature[entityAddress] = featuresFeatureTypes;
        }
      }

      retval = true;
    }
  }

  return retval;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::
    addDetailedDiscoveryFeatureInformation(
        const NodeManagementDetailedDiscoveryFeatureInformation
            &featureInformation) {
  return addDetailedDiscoveryFeatureInformation(
      featureInformation, true /* enforce feature type set */,
      true /* enforce role set */, true /* enforce existing entity */);
}

void DetailedDiscovery::DetailedDiscoveryImpl::removeFeature(
    const EntityAddress &entityAddress, xs_unsignedInt featureId) {
  entityAddress_featureId_FeatureData_Map_MapType::iterator entityIt =
      m_DeviceFeatureData.find(entityAddress);
  if (entityIt != m_DeviceFeatureData.end()) {
    featureId_FeatureData_MapType::iterator featureIt =
        entityIt->second.find(featureId);

    if (featureIt != entityIt->second.end()) {
      NodeManagementDetailedDiscoveryFeatureInformation featureInformation =
          featureIt->second;

      if (1 ==
          getFeaturesByFeatureType(
              entityAddress,
              featureInformation.getDescription().getFeatureType().toString())
              .size()) {
        // remove process id for entity address
        erase_if<std::string, EntityAddress>(
            m_FeatureTypeByEntity,
            featureInformation.getDescription().getFeatureType().toString(),
            entityAddress);
      }

      // remove process id for feature id
      entityAddress_featureType_featureId_MultiMap_MapType::iterator
          featureTypeByFeatureIterator =
              m_FeatureTypeByFeature.find(entityAddress);

      erase_if<std::string, xs_unsignedInt>(
          featureTypeByFeatureIterator->second,
          featureInformation.getDescription().getFeatureType().toString(),
          featureId);

      // erase feature
      entityIt->second.erase(featureIt);
    }
  }
}

void DetailedDiscovery::DetailedDiscoveryImpl::removeEntityWithFeatures(
    const EntityAddress &entityAddress) {
  // check for features on entity
  if (m_DeviceFeatureData.find(entityAddress) != m_DeviceFeatureData.end()) {
    // features found (copy because map is changed on removal of features)
    featureId_FeatureData_MapType featureData =
        m_DeviceFeatureData.at(entityAddress);

    // remove features
    for (auto featureDataIter = featureData.begin();
         featureDataIter != featureData.end(); featureDataIter++) {
      removeFeature(entityAddress, featureDataIter->first);
    }
  }

  // remove entity
  entityAddress_EntityData_MapType::iterator deviceEntityIter =
      m_DeviceEntityData.find(entityAddress);
  if (deviceEntityIter != m_DeviceEntityData.end()) {
    if ((deviceEntityIter->second.getDescriptionIsSet()) &&
        deviceEntityIter->second.getDescription().getEntityTypeIsSet()) {
      // remove entity from m_EntityTypes
      erase_if<xs_string, EntityAddress>(
          m_EntityTypes,
          deviceEntityIter->second.getDescription().getEntityType().toString(),
          entityAddress);
    }

    // remove entity from m_DeviceEntityData
    deviceEntityIter = m_DeviceEntityData.erase(deviceEntityIter);
  }
}

NodeManagementDetailedDiscoveryFeatureInformationPtr
DetailedDiscovery::DetailedDiscoveryImpl::
    getDetailedDiscoveryFeatureInformation(const EntityAddress &entityAddress,
                                           xs_unsignedInt featureId) const {
  NodeManagementDetailedDiscoveryFeatureInformationPtr detailedInformationptr;

  entityAddress_featureId_FeatureData_Map_MapType::const_iterator entityIt =
      m_DeviceFeatureData.find(entityAddress);

  if (entityIt != m_DeviceFeatureData.end()) {
    featureId_FeatureData_MapType::const_iterator featureIt =
        entityIt->second.find(featureId);

    if (featureIt != entityIt->second.end()) {
      detailedInformationptr =
          NodeManagementDetailedDiscoveryFeatureInformationPtr(
              new NodeManagementDetailedDiscoveryFeatureInformation(
                  featureIt->second));
    }
  }

  return detailedInformationptr;
}

std::vector<FunctionProperty>
DetailedDiscovery::DetailedDiscoveryImpl::getFunctionPropertiesByFeature(
    const EntityAddress &entityAddress, xs_unsignedInt feature) const {
  std::vector<FunctionProperty> propertyList;
  entityAddress_featureId_FeatureData_Map_MapType::const_iterator iter =
      m_DeviceFeatureData.find(entityAddress);
  if (iter != m_DeviceFeatureData.end()) {
    const featureId_FeatureData_MapType &ref = iter->second;
    featureId_FeatureData_MapType::const_iterator iter2 = ref.find(feature);
    if (iter2 != ref.end()) {
      if (iter2->second.getDescriptionIsSet() &&
          iter2->second.getDescription().getSupportedFunctionIsSet()) {
        const std::vector<FunctionProperty> &sf =
            iter2->second.getDescription().getSupportedFunction();
        propertyList.assign(sf.begin(), sf.end());
      }
    }
  }
  return propertyList;
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscovery::DetailedDiscoveryImpl::getFeatureInformation() const {
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation> features;

  for (auto entityIter = m_DeviceFeatureData.begin();
       entityIter != m_DeviceFeatureData.end(); entityIter++) {
    for (auto featureIter = entityIter->second.begin();
         featureIter != entityIter->second.end(); featureIter++) {
      features.push_back(featureIter->second);
    }
  }

  return features;
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscovery::DetailedDiscoveryImpl::getFeatureInformationByEntity(
    const EntityAddress &entityAddress) const {
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation> retval;

  entityAddress_featureId_FeatureData_Map_MapType::const_iterator it =
      m_DeviceFeatureData.find(entityAddress);
  if (it != m_DeviceFeatureData.end()) {
    featureId_FeatureData_MapType::const_iterator featuresIterator =
        it->second.begin();

    while (featuresIterator != it->second.end()) {
      retval.push_back(featuresIterator->second);
      featuresIterator++;
    }
  }

  return retval;
}

bool DetailedDiscovery::DetailedDiscoveryImpl::setLastStateChangeOfEntity(
    const EntityAddress &entityAddress,
    const NetworkManagementStateChange::Value &lastStateChange) {
  bool ret = false;

  entityAddress_EntityData_MapType::iterator entityIter =
      m_DeviceEntityData.find(entityAddress);
  if (entityIter != m_DeviceEntityData.end()) {
    NetworkManagementEntityDescriptionData entityDescription =
        entityIter->second.getDescription();
    entityDescription.setLastStateChange(lastStateChange);
    entityIter->second.setDescription(entityDescription);
    ret = true;
  }

  return ret;
}

} // end namespace keo_datagram