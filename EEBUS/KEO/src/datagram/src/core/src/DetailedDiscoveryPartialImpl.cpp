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

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */
#include <algorithm>
#include <assert.h>

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */
#include "DetailedDiscoveryPartialImpl.h"

#include <keo_datagram/core/CmdControl.h>
#include <keo_datagram/core/Filter.h>
#include <keo_datagram/core/Function.h>

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
 *  definition *
 * ******************************************************************************
 */

namespace keo_datagram {

DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    DetailedDiscoveryPartialImpl() {}

DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    ~DetailedDiscoveryPartialImpl() {}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    setByDiffingDetailedDiscoveries(
        const DetailedDiscovery &sourceDetailedDiscovery,
        const DetailedDiscovery &targetDetailedDiscovery) {
  bool success = false;

  // do not diff if device names differ
  if (sourceDetailedDiscovery.getDeviceNameIsSet() &&
      targetDetailedDiscovery.getDeviceNameIsSet() &&
      (sourceDetailedDiscovery.getDeviceName() ==
       targetDetailedDiscovery.getDeviceName())) {

    DetailedDiscovery::DetailedDiscoveryImpl::entityAddress_EntityData_MapType
        ddSourceDeviceEntityData;
    ddSourceDeviceEntityData = sourceDetailedDiscovery.d->m_DeviceEntityData;

    DetailedDiscovery::DetailedDiscoveryImpl::entityAddress_EntityData_MapType
        ddTargetDeviceEntityData;
    ddTargetDeviceEntityData = targetDetailedDiscovery.d->m_DeviceEntityData;

    NodeManagementDetailedDiscoveryData ddPartial;
    std::vector<NodeManagementDetailedDiscoveryEntityInformation>
        ddPartialEntityInformationList;

    // get added entities
    std::vector<NodeManagementDetailedDiscoveryEntityInformation>
        addedEntities = getAddedOrRemovedEntities(
            true, ddSourceDeviceEntityData, ddTargetDeviceEntityData);
    ddPartialEntityInformationList.insert(ddPartialEntityInformationList.end(),
                                          addedEntities.begin(),
                                          addedEntities.end());

    // get modified entities
    std::vector<NodeManagementDetailedDiscoveryEntityInformation>
        modifiedEntities = getModifiedEntities(ddSourceDeviceEntityData,
                                               ddTargetDeviceEntityData);
    ddPartialEntityInformationList.insert(ddPartialEntityInformationList.end(),
                                          modifiedEntities.begin(),
                                          modifiedEntities.end());

    // get removed entities
    std::vector<NodeManagementDetailedDiscoveryEntityInformation>
        removedEntities = getAddedOrRemovedEntities(
            false, ddSourceDeviceEntityData, ddTargetDeviceEntityData);
    ddPartialEntityInformationList.insert(ddPartialEntityInformationList.end(),
                                          removedEntities.begin(),
                                          removedEntities.end());
    // check for added features
    DetailedDiscovery::DetailedDiscoveryImpl::
        entityAddress_featureId_FeatureData_Map_MapType
            ddSourceDeviceFeatureData;
    ddSourceDeviceFeatureData = sourceDetailedDiscovery.d->m_DeviceFeatureData;

    DetailedDiscovery::DetailedDiscoveryImpl::
        entityAddress_featureId_FeatureData_Map_MapType
            ddTargetDeviceFeatureData;
    ddTargetDeviceFeatureData = targetDetailedDiscovery.d->m_DeviceFeatureData;

    std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
        featureInformationVector;

    // add features (if there are any) added by Target entity
    for (auto entityIter = addedEntities.begin();
         entityIter != addedEntities.end(); entityIter++) {
      assert(entityIter->getDescriptionIsSet());
      assert(entityIter->getDescription().getEntityAddressIsSet());
      EntityAddress entityAddress =
          entityIter->getDescription().getEntityAddress();
      {
        auto iter = ddTargetDeviceFeatureData.find(entityAddress);
        if (iter != ddTargetDeviceFeatureData.end()) {
          assert(iter->second.size() >= 1);

          DetailedDiscovery::DetailedDiscoveryImpl::
              featureId_FeatureData_MapType featureMap;
          featureMap = iter->second;

          for (auto featureMapIter = featureMap.begin();
               featureMapIter != featureMap.end(); featureMapIter++) {
            featureInformationVector.push_back(featureMapIter->second);
          }
        }
      }
    }

    // check for added features (in existing entities)
    {
      std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
          featureInformationVectorAdded;

      for (auto entityIterTarget = ddTargetDeviceFeatureData.begin();
           entityIterTarget != ddTargetDeviceFeatureData.end();
           entityIterTarget++) {
        // check if feature has not been added by Target added entity
        if (!containsEntityAddress(entityIterTarget->first, addedEntities)) {
          for (auto featureMapIterTarget = entityIterTarget->second.begin();
               featureMapIterTarget != entityIterTarget->second.end();
               featureMapIterTarget++) {
            if (!sourceDetailedDiscovery.containsFeatureIdOnEntity(
                    entityIterTarget->first.getEntity(),
                    featureMapIterTarget->first)) {
              // not existing in source dd: added
              NodeManagementDetailedDiscoveryFeatureInformation
                  featureInformation = featureMapIterTarget->second;
              assert(featureInformation.getDescriptionIsSet());
              NetworkManagementFeatureDescriptionData featureDescriptionData;
              featureDescriptionData = featureInformation.getDescription();
              featureDescriptionData.setLastStateChange(
                  NetworkManagementStateChange::Value::ADDED);
              featureInformation.setDescription(featureDescriptionData);
              featureInformationVector.push_back(featureInformation);
            }
          }
        }
      }
    }

    // check for removed features (in existing entities)
    {
      std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
          featureInformationVectorRemoved;

      for (auto entityIterSource = ddSourceDeviceFeatureData.begin();
           entityIterSource != ddSourceDeviceFeatureData.end();
           entityIterSource++) {
        for (auto featureMapIterSource = entityIterSource->second.begin();
             featureMapIterSource != entityIterSource->second.end();
             featureMapIterSource++) {
          if (!targetDetailedDiscovery.containsFeatureIdOnEntity(
                  entityIterSource->first.getEntity(),
                  featureMapIterSource->first) &&
              targetDetailedDiscovery.containsEntityAddress(
                  entityIterSource->first.getEntity())) {
            // not existing in target dd and parent entity has not been
            // removed-> mark feature as removed

            // add feature information
            NodeManagementDetailedDiscoveryFeatureInformation
                featureInformation = featureMapIterSource->second;
            NetworkManagementFeatureDescriptionData featureDescriptionData;
            featureDescriptionData = featureInformation.getDescription();
            assert(featureDescriptionData.getFeatureAddressIsSet());

            NetworkManagementFeatureDescriptionData
                featureDescriptionDataTarget;
            featureDescriptionDataTarget.setFeatureAddress(
                featureDescriptionData.getFeatureAddress());

            featureDescriptionDataTarget.setLastStateChange(
                NetworkManagementStateChange::Value::REMOVED);
            featureInformation.setDescription(featureDescriptionDataTarget);
            featureInformationVector.push_back(featureInformation);
          }
        }
      }
    }

    // check for modifies features
    {
      // get features from source and target
      std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
          featuresSource = sourceDetailedDiscovery.d->getFeatureInformation();
      std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
          featuresTarget = targetDetailedDiscovery.d->getFeatureInformation();

      for (auto featureSourceIter = featuresSource.begin();
           featureSourceIter != featuresSource.end(); featureSourceIter++) {
        assert(featureSourceIter->getDescriptionIsSet());
        assert(featureSourceIter->getDescription().getFeatureAddressIsSet());

        for (auto featureTargetIter = featuresTarget.begin();
             featureTargetIter != featuresTarget.end(); featureTargetIter++) {
          assert(featureTargetIter->getDescriptionIsSet());
          assert(featureTargetIter->getDescription().getFeatureAddressIsSet());

          // compare feature addresses to find feature for comparing
          if (featureTargetIter->getDescription().getFeatureAddress() ==
              featureSourceIter->getDescription().getFeatureAddress()) {
            if (*featureTargetIter != *featureSourceIter) {
              // feature is not equal: modified
              NodeManagementDetailedDiscoveryFeatureInformation
                  featureInformation = *featureTargetIter;
              NetworkManagementFeatureDescriptionData description =
                  featureInformation.getDescription();
              description.setLastStateChange(
                  NetworkManagementStateChange::Value::MODIFIED);
              featureInformation.setDescription(description);
              featureInformationVector.push_back(featureInformation);
            }
          }
        }
      }
    }

    // set entity information
    if (!ddPartialEntityInformationList.empty()) {
      ddPartial.setEntityInformation(ddPartialEntityInformationList);
    }

    // set feature information
    if (!featureInformationVector.empty()) {
      ddPartial.setFeatureInformation(featureInformationVector);
    }

    if (setDetailedDiscoveryData(ddPartial)) {
      setDeviceName(sourceDetailedDiscovery.getDeviceName());
      success = true;
    }
  }

  return success;
}

DetailedDiscovery DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    getMergedDetailedDiscovery(const DetailedDiscovery &sourceDetailedDiscovery,
                               bool *success) const {
  DetailedDiscovery detailedDiscoveryRet = sourceDetailedDiscovery;
  bool retSuccess = false;

  assert(getDeviceNameIsSet());
  if (getDeviceNameIsSet() && sourceDetailedDiscovery.getDeviceNameIsSet() &&
      (getDeviceName() == sourceDetailedDiscovery.getDeviceName())) {
    retSuccess = true; // will be set to false on first error

    // merge newly added entities
    std::map<EntityAddress, NodeManagementDetailedDiscoveryEntityInformation>
        entityInformationPartial = m_DeviceEntityData;
    for (auto entityIterPartial = entityInformationPartial.begin();
         entityIterPartial != entityInformationPartial.end();
         entityIterPartial++) {
      // added entity
      if (isPartialEntityDescriptionMandatorySet(
              entityIterPartial->second,
              NetworkManagementStateChange::Value::ADDED)) {
        if (entityIterPartial->second.getDescription().getLastStateChange() ==
            NetworkManagementStateChange::Value::ADDED) {
          // check if entity address is not already known
          if (!sourceDetailedDiscovery.containsEntityAddress(
                  entityIterPartial->first.getEntity())) {
            // add entity
            cleanLastStateChange(entityIterPartial->second);
            retSuccess &=
                detailedDiscoveryRet.addDetailedDiscoveryEntityInformation(
                    entityIterPartial->second);
            assert(retSuccess);
            if (!retSuccess) {
              break;
            }
          } else {
            retSuccess = false; // entity address already known
            break;
          }
        }
      }

      // removed entity
      if (retSuccess && isPartialEntityDescriptionMandatorySet(
                            entityIterPartial->second,
                            NetworkManagementStateChange::Value::REMOVED)) {
        if (entityIterPartial->second.getDescription().getLastStateChange() ==
            NetworkManagementStateChange::Value::REMOVED) {
          // check if entity exists
          retSuccess &= detailedDiscoveryRet.containsEntityAddress(
              entityIterPartial->first.getEntity());
          assert(retSuccess);
          if (retSuccess) {
            // remove entity (including its features)
            detailedDiscoveryRet.d->removeEntityWithFeatures(
                entityIterPartial->first);
          } else {
            retSuccess = false; // cannot remove non existing entity
            break;
          }
        }
      }

      // modified entity
      if (retSuccess && isPartialEntityDescriptionMandatorySet(
                            entityIterPartial->second,
                            NetworkManagementStateChange::Value::MODIFIED)) {
        if (entityIterPartial->second.getDescription().getLastStateChange() ==
            NetworkManagementStateChange::Value::MODIFIED) {
          // check if entity exists
          if (detailedDiscoveryRet.containsEntityAddress(
                  entityIterPartial->first.getEntity())) {
            cleanLastStateChange(entityIterPartial->second);
            retSuccess &=
                detailedDiscoveryRet.addDetailedDiscoveryEntityInformation(
                    entityIterPartial->second);
            assert(retSuccess);
            if (!retSuccess) {
              break;
            }
          } else {
            retSuccess = false; // cannot modify non existing entity
            break;
          }
        }
      }
    }

    // merge added features (only for existing entities)
    if (retSuccess) {
      for (auto entityIterPartial =
               detailedDiscoveryRet.d->m_DeviceEntityData.begin();
           entityIterPartial !=
           detailedDiscoveryRet.d->m_DeviceEntityData.end();
           entityIterPartial++) {
        {
          std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
              features =
                  getFeatureInformationByEntity(entityIterPartial->first);

          // merge added or modified features
          for (auto featureIter = features.begin();
               featureIter != features.end(); featureIter++) {
            if (!featureIter->getDescription().getLastStateChangeIsSet() ||
                featureIter->getDescription().getLastStateChange() !=
                    NetworkManagementStateChange::Value::REMOVED) {
              // add feature (will be replaced if already existing)
              // filter out lastStateChange
              NetworkManagementFeatureDescriptionData descriptionStateCleaned;
              descriptionStateCleaned = featureIter->getDescription();
              descriptionStateCleaned.cleanLastStateChange();
              featureIter->setDescription(descriptionStateCleaned);
              detailedDiscoveryRet.addDetailedDiscoveryFeatureInformation(
                  *featureIter);
            } else if (featureIter->getDescription().getLastStateChange() ==
                       NetworkManagementStateChange::Value::REMOVED) {
              // remove feature
              detailedDiscoveryRet.d->removeFeature(
                  entityIterPartial->first, featureIter->getDescription()
                                                .getFeatureAddress()
                                                .getFeature());
            }
          }
        }
      }
    }
  }

  if (success != nullptr) {
    *success = retSuccess;
  }
  return detailedDiscoveryRet;
}

Datagram DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    createPartialDetailedDiscoveryDatagram(const Header &header) const {
  Cmd cmd = Cmd(getDetailedDiscoveryDataPtr());
  Filter filterType;
  CmdControl cmdControl;
  cmdControl.setPartial();
  filterType.setCmdControl(cmdControl);
  std::vector<Filter> filterList;
  filterList.push_back(filterType);
  cmd.setFilter(filterList);
  cmd.setFunction(Function::Value::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA);
  return Datagram(header, cmd);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    setDetailedDiscoveryData(
        const NodeManagementDetailedDiscoveryData &detailedDiscoveryData) {
  return DetailedDiscovery::DetailedDiscoveryImpl::setDetailedDiscoveryData(
      detailedDiscoveryData, false /* do not enforce full mandatory */);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    addDetailedDiscoveryEntityInformation(
        const NodeManagementDetailedDiscoveryEntityInformation
            &entityInformation) {
  return DetailedDiscovery::DetailedDiscoveryImpl::
      addDetailedDiscoveryEntityInformation(
          entityInformation, false /* do not enforce entity type */);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    addDetailedDiscoveryFeatureInformation(
        const NodeManagementDetailedDiscoveryFeatureInformation
            &featureInformation) {
  return DetailedDiscovery::DetailedDiscoveryImpl::
      addDetailedDiscoveryFeatureInformation(
          featureInformation, false /* do not enforce feature type */,
          false /* do not enforce role */,
          false /* do not enforce existing entity */);
}

void DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::setDeviceName(
    const std::string &deviceName) {
  m_DeviceDescriptionData.setDeviceAddress(DeviceAddress(deviceName));
  m_DeviceDescriptionDataIsSet = true;
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getAddedEntities()
    const {
  return getEntitiesByLastStateChange(
      NetworkManagementStateChange::Value::ADDED);
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getModifiedEntities()
    const {
  return getEntitiesByLastStateChange(
      NetworkManagementStateChange::Value::MODIFIED);
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getRemovedEntities()
    const {
  return getEntitiesByLastStateChange(
      NetworkManagementStateChange::Value::REMOVED);
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getAddedFeatures()
    const {
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
      featureInformationVectorRet;

  // add features with lastStateChange ADDED
  featureInformationVectorRet =
      getFeaturesByLastStateChange(NetworkManagementStateChange::Value::ADDED);

  // add features which are added by new entities
  std::vector<NodeManagementDetailedDiscoveryEntityInformation> addedEntities =
      getAddedEntities();
  for (auto entityIter = addedEntities.begin();
       entityIter != addedEntities.end(); entityIter++) {
    assert(entityIter->getDescriptionIsSet());
    assert(entityIter->getDescription().getEntityAddressIsSet());
    if (entityIter->getDescriptionIsSet() &&
        entityIter->getDescription().getEntityAddressIsSet()) {
      std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
          featuresAddedByEntity;
      featuresAddedByEntity = getFeatureInformationByEntity(
          entityIter->getDescription().getEntityAddress());
      featureInformationVectorRet.insert(featureInformationVectorRet.end(),
                                         featuresAddedByEntity.begin(),
                                         featuresAddedByEntity.end());
    }
  }
  return featureInformationVectorRet;
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getModifiedFeatures()
    const {
  return getFeaturesByLastStateChange(
      NetworkManagementStateChange::Value::MODIFIED);
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getRemovedFeatures()
    const {
  return getFeaturesByLastStateChange(
      NetworkManagementStateChange::Value::REMOVED);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::isEntityModified(
    const EntityAddress &entityAddress) const {
  return isEntityLastStateChange(entityAddress,
                                 NetworkManagementStateChange::Value::MODIFIED);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::isEntityRemoved(
    const EntityAddress &entityAddress) const {
  return isEntityLastStateChange(entityAddress,
                                 NetworkManagementStateChange::Value::REMOVED);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::isFeatureModified(
    const FeatureAddress &featureAddress) const {
  return isFeatureLastStateChange(
      featureAddress, NetworkManagementStateChange::Value::MODIFIED);
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::isFeatureRemoved(
    const FeatureAddress &featureAddress) const {
  bool retVal = false;

  // check if feature is removed by entity
  if (featureAddress.getEntityIsSet()) {
    retVal = isEntityRemoved(EntityAddress(featureAddress.getEntity()));
  }

  // check if feature is removed by lastStateChange REMOVED
  if (!retVal) {
    retVal = isFeatureLastStateChange(
        featureAddress, NetworkManagementStateChange::Value::REMOVED);
  }

  return retVal;
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    getAddedOrRemovedEntities(
        bool getAdded, const DetailedDiscovery::DetailedDiscoveryImpl::
                           entityAddress_EntityData_MapType &entityDataOld,
        const DetailedDiscovery::DetailedDiscoveryImpl::
            entityAddress_EntityData_MapType &entityDataNew) {
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
      entityInformationList;

  const DetailedDiscovery::DetailedDiscoveryImpl::
      entityAddress_EntityData_MapType *entityDataSrc;
  const DetailedDiscovery::DetailedDiscoveryImpl::
      entityAddress_EntityData_MapType *entityDataDest;

  if (getAdded) {
    entityDataSrc = &entityDataNew;
    entityDataDest = &entityDataOld;
  } else {
    entityDataSrc = &entityDataOld;
    entityDataDest = &entityDataNew;
  }

  for (auto entityIter = entityDataSrc->begin();
       entityIter != entityDataSrc->end(); entityIter++) {
    if (entityDataDest->find(entityIter->first) == entityDataDest->end()) {
      assert(entityIter->second.getDescriptionIsSet());
      assert(entityIter->second.getDescription().getEntityAddressIsSet());

      NetworkManagementEntityDescriptionData entityDescription;
      if (getAdded) {
        entityDescription = entityIter->second.getDescription();
        entityDescription.setLastStateChange(
            NetworkManagementStateChange::Value::ADDED);
      } else {
        entityDescription.setEntityAddress(
            entityIter->second.getDescription().getEntityAddress());
        entityDescription.setLastStateChange(
            NetworkManagementStateChange::Value::REMOVED);
      }

      NodeManagementDetailedDiscoveryEntityInformation entityInformation;
      entityInformation = entityIter->second;
      entityInformation.setDescription(entityDescription);

      entityInformationList.push_back(entityInformation);
    }
  }

  return entityInformationList;
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getModifiedEntities(
    const DetailedDiscovery::DetailedDiscoveryImpl::
        entityAddress_EntityData_MapType &entityDataOld,
    const DetailedDiscovery::DetailedDiscoveryImpl::
        entityAddress_EntityData_MapType &entityDataNew) {
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
      entityInformationList;

  for (auto entityNewIter = entityDataNew.begin();
       entityNewIter != entityDataNew.end(); entityNewIter++) {
    auto entityOldIter = entityDataOld.find(entityNewIter->first);
    if (entityOldIter != entityDataOld.end()) {
      if (entityNewIter->second != entityOldIter->second) {
        NodeManagementDetailedDiscoveryEntityInformation entityInformation;
        entityInformation = entityNewIter->second;

        NetworkManagementEntityDescriptionData entityDescription;
        entityDescription = entityInformation.getDescription();
        entityDescription.setLastStateChange(
            NetworkManagementStateChange::Value::MODIFIED);
        entityInformation.setDescription(entityDescription);

        entityInformationList.push_back(entityInformation);
      }
    }
  }

  return entityInformationList;
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    isPartialEntityDescriptionMandatorySet(
        const NodeManagementDetailedDiscoveryEntityInformation
            &entityInformationPartial,
        const NetworkManagementStateChange::Value &stateChange) {
  bool ret = true;

  NetworkManagementEntityDescriptionData entityDescription;

  ret &= entityInformationPartial.getDescriptionIsSet();
  if (ret) {
    entityDescription = entityInformationPartial.getDescription();
    ret &= entityDescription.getEntityAddressIsSet();
    ret &= entityDescription.getLastStateChangeIsSet();
  }

  if (ret && stateChange == NetworkManagementStateChange::Value::ADDED) {
    ret &= entityDescription.getEntityTypeIsSet();
  }

  return ret;
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    containsEntityAddress(
        const EntityAddress &entityAddress,
        const std::vector<NodeManagementDetailedDiscoveryEntityInformation>
            &entityInformationVector) {
  bool found = false;
  for (auto entityInformationIter = entityInformationVector.begin();
       entityInformationIter != entityInformationVector.end();
       entityInformationIter++) {
    if (entityInformationIter->getDescriptionIsSet()) {
      NetworkManagementEntityDescriptionData entityDescriptionData =
          entityInformationIter->getDescription();
      if (entityDescriptionData.getEntityAddressIsSet() &&
          (entityDescriptionData.getEntityAddress() == entityAddress)) {
        found = true;
        break;
      }
    }
  }
  return found;
}

std::map<xs_unsignedInt, NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::getFeatureDataByEntity(
    const EntityAddress &entityAddress) const {
  return ((m_DeviceFeatureData.find(entityAddress) != m_DeviceFeatureData.end())
              ? m_DeviceFeatureData.at(entityAddress)
              : std::map<xs_unsignedInt,
                         NodeManagementDetailedDiscoveryFeatureInformation>());
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    getEntitiesByLastStateChange(
        const NetworkManagementStateChange::Value &lastStateChange) const {
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
      entityInformationVector;
  for (auto entityIter = m_DeviceEntityData.begin();
       entityIter != m_DeviceEntityData.end(); entityIter++) {
    assert(entityIter->second.getDescriptionIsSet());
    assert(entityIter->second.getDescription().getLastStateChangeIsSet());

    if (entityIter->second.getDescriptionIsSet()) {
      if (entityIter->second.getDescription().getLastStateChangeIsSet() &&
          entityIter->second.getDescription().getLastStateChange() ==
              lastStateChange) {
        entityInformationVector.push_back(entityIter->second);
      }
    }
  }
  return entityInformationVector;
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    getFeaturesByLastStateChange(
        const NetworkManagementStateChange::Value &lastStateChange) const {
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
      featuresRetVector;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
      featureInformationVector = getFeatureInformation();
  for (auto featureIter = featureInformationVector.begin();
       featureIter != featureInformationVector.end(); featureIter++) {
    if (featureIter->getDescriptionIsSet() &&
        featureIter->getDescription().getLastStateChangeIsSet() &&
        featureIter->getDescription().getLastStateChange() == lastStateChange) {
      featuresRetVector.push_back(*featureIter);
    }
  }
  return featuresRetVector;
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    isEntityLastStateChange(
        const EntityAddress &entityAddress,
        const NetworkManagementStateChange::Value &lastStateChange) const {
  bool retVal = false;
  std::vector<NodeManagementDetailedDiscoveryEntityInformation>
      entityInformationVector = getEntitiesByLastStateChange(lastStateChange);
  for (auto entityIter = entityInformationVector.begin();
       entityIter != entityInformationVector.end(); entityIter++) {
    assert(entityIter->getDescriptionIsSet());
    if (entityIter->getDescriptionIsSet()) {
      NetworkManagementEntityDescriptionData descriptionData =
          entityIter->getDescription();
      assert(descriptionData.getEntityAddressIsSet());
      if (descriptionData.getEntityAddressIsSet() &&
          descriptionData.getEntityAddress() == entityAddress) {
        retVal = true;
        break;
      }
    }
  }
  return retVal;
}

bool DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    isFeatureLastStateChange(
        const FeatureAddress &featureAddress,
        const NetworkManagementStateChange::Value &lastStateChange) const {
  bool retVal = false;
  std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
      featureInformationVector = getFeaturesByLastStateChange(lastStateChange);
  for (auto featureIter = featureInformationVector.begin();
       featureIter != featureInformationVector.end(); featureIter++) {
    assert(featureIter->getDescriptionIsSet());
    if (featureIter->getDescriptionIsSet()) {
      NetworkManagementFeatureDescriptionData descriptionData =
          featureIter->getDescription();
      assert(descriptionData.getFeatureAddressIsSet());
      if (descriptionData.getFeatureAddressIsSet() &&
          descriptionData.getFeatureAddress() == featureAddress) {
        retVal = true;
        break;
      }
    }
  }
  return retVal;
}

void DetailedDiscoveryPartial::DetailedDiscoveryPartialImpl::
    cleanLastStateChange(NodeManagementDetailedDiscoveryEntityInformation
                             &entityInformation) const {
  NetworkManagementEntityDescriptionData stateCleanedDescription =
      entityInformation.getDescription();
  stateCleanedDescription.cleanLastStateChange();
  entityInformation.setDescription(stateCleanedDescription);
}

} // namespace keo_datagram