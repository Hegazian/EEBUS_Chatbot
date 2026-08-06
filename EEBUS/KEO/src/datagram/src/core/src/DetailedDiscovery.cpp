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

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */
#include "DetailedDiscoveryImpl.h"
#include <keo_datagram/core/DetailedDiscovery.h>

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

static std::vector<std::vector<xs_unsignedInt>>
entityAddressListToVectorList(const std::vector<EntityAddress> &list) {
  std::vector<std::vector<xs_unsignedInt>> retval;

  std::vector<EntityAddress>::const_iterator iter = list.begin();

  while (iter != list.end()) {
    retval.push_back(iter->getEntity());

    iter++;
  }

  return retval;
}

DetailedDiscovery::DetailedDiscovery() : d(new DetailedDiscoveryImpl()) {}

DetailedDiscovery::~DetailedDiscovery() { delete d; }

/// copy constructor
DetailedDiscovery::DetailedDiscovery(const DetailedDiscovery &that)
    : d(new DetailedDiscoveryImpl(*(that.d))) {}

/// assignment operator
DetailedDiscovery &DetailedDiscovery::operator=(const DetailedDiscovery &that) {
  if (this != &that) {
    *d = *(that.d);
  }
  return *this;
}

void DetailedDiscovery::clear() { d->clear(); }

bool DetailedDiscovery::isEmpty() const { return d->isEmpty(); }

bool DetailedDiscovery::setDiscoveryInformationFromCmd(const Cmd &cmd) {
  bool retval = false;
  if (!cmd.isEmpty() &&
      cmd.getDataType() ==
          CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE) {
    NodeManagementDetailedDiscoveryDataPtr classPtr =
        std::dynamic_pointer_cast<NodeManagementDetailedDiscoveryData>(
            cmd.getCmdData());
    if (classPtr) {
      retval = d->setDetailedDiscoveryData(*classPtr);
    }
  }
  return retval;
}

NodeManagementSpecificationVersionList
DetailedDiscovery::getSpecificationVersionList() const {
  return d->getSpecificationVersionList();
}

void DetailedDiscovery::setSpecificationVersionList(
    const NodeManagementSpecificationVersionList &specificationVersionList) {
  d->setSpecificationVersionList(specificationVersionList);
}

NetworkManagementDeviceDescriptionData
DetailedDiscovery::getDeviceDescription() const {
  return d->getDeviceDescription();
}
void DetailedDiscovery::setDeviceDescription(
    const NetworkManagementDeviceDescriptionData &deviceDescriptionData) {
  d->setDeviceDescription(deviceDescriptionData);
}

bool DetailedDiscovery::getDeviceNameIsSet() const {
  return d->getDeviceNameIsSet();
}

std::string DetailedDiscovery::getDeviceName() const {
  return d->getDeviceName();
}

bool DetailedDiscovery::hasFunction(const Function &function) const {
  bool functionFound = false;
  std::vector<keo_datagram::FunctionProperty> functionProperties =
      this->getFunctionPropertiesByFeature(EntityAddress(std::string(), 0LL),
                                           0LL);
  for (std::vector<keo_datagram::FunctionProperty>::const_iterator iter =
           functionProperties.begin();
       iter != functionProperties.end(); iter++) {
    if (iter->getFunctionIsSet() && iter->getFunction() == function) {
      functionFound = true;
      break;
    }
  }

  return functionFound;
}

bool DetailedDiscovery::containsEntityAddress(
    const std::vector<xs_unsignedInt> &entityAddress) const {
  return d->containsEntityAddress(EntityAddress(entityAddress));
}

bool DetailedDiscovery::containsEntityType(const EntityType &entityType) const {
  return d->containsEntityType(entityType.toString());
}

bool DetailedDiscovery::containsEntityType(
    const std::string &entityType) const {
  return d->containsEntityType(entityType);
}

bool DetailedDiscovery::containsFeatureIdOnEntity(
    const std::vector<xs_unsignedInt> &entityAddress,
    xs_unsignedInt featureId) const {
  return d->containsFeatureIdOnEntity(EntityAddress(entityAddress), featureId);
}

bool DetailedDiscovery::containsFeatureType(
    const FeatureType &featureType) const {
  return d->containsFeatureType(featureType.toString());
}

bool DetailedDiscovery::containsFeatureType(
    const xs_string &featureType) const {
  return d->containsFeatureType(featureType);
}

bool DetailedDiscovery::containsFeatureTypeOnEntity(
    const std::vector<xs_unsignedInt> &entityAddress,
    const FeatureType &featureType) const {
  return d->containsFeatureTypeOnEntity(EntityAddress(entityAddress),
                                        featureType.toString());
}

bool DetailedDiscovery::containsFeatureTypeOnEntity(
    const std::vector<xs_unsignedInt> &entityAddress,
    const xs_string &featureType) const {
  return d->containsFeatureTypeOnEntity(EntityAddress(entityAddress),
                                        featureType);
}

std::vector<std::vector<xs_unsignedInt>>
DetailedDiscovery::getEntities() const {
  return entityAddressListToVectorList(d->getEntities());
}

std::vector<std::vector<xs_unsignedInt>>
DetailedDiscovery::getEntitiesByEntityType(const EntityType &entityType) const {
  return entityAddressListToVectorList(
      d->getEntitiesByEntityType(entityType.toString()));
}

std::vector<std::vector<xs_unsignedInt>>
DetailedDiscovery::getEntitiesByEntityType(const xs_string &entityType) const {
  return entityAddressListToVectorList(d->getEntitiesByEntityType(entityType));
}

std::vector<std::vector<xs_unsignedInt>>
DetailedDiscovery::getEntitiesByFeatureType(
    const FeatureType &featureType) const {
  return entityAddressListToVectorList(
      d->getEntitiesByFeatureType(featureType.toString()));
}

std::vector<std::vector<xs_unsignedInt>>
DetailedDiscovery::getEntitiesByFeatureType(
    const xs_string &featureType) const {
  return entityAddressListToVectorList(
      d->getEntitiesByFeatureType(featureType));
}

std::vector<xs_unsignedInt> DetailedDiscovery::getFeatures(
    const std::vector<xs_unsignedInt> &entityAddress) const {
  return d->getFeatures(EntityAddress(entityAddress));
}

std::vector<xs_unsignedInt> DetailedDiscovery::getFeaturesByFeatureType(
    const std::vector<xs_unsignedInt> &entityAddress,
    const FeatureType &featureType) const {
  return d->getFeaturesByFeatureType(EntityAddress(entityAddress),
                                     featureType.toString());
}

std::vector<xs_unsignedInt> DetailedDiscovery::getFeaturesByFeatureType(
    const std::vector<xs_unsignedInt> &entityAddress,
    const xs_string &featureType) const {
  return d->getFeaturesByFeatureType(EntityAddress(entityAddress), featureType);
}

NodeManagementDetailedDiscoveryDataPtr
DetailedDiscovery::getDetailedDiscoveryDataPtr() const {
  return d->getDetailedDiscoveryDataPtr();
}

bool DetailedDiscovery::setDetailedDiscoveryData(
    const NodeManagementDetailedDiscoveryData &detailedDiscoveryData) {
  return d->setDetailedDiscoveryData(detailedDiscoveryData);
}

bool DetailedDiscovery::addDetailedDiscoveryEntityInformation(
    const NodeManagementDetailedDiscoveryEntityInformation &entityInformation) {
  return d->addDetailedDiscoveryEntityInformation(entityInformation);
}

NodeManagementDetailedDiscoveryEntityInformationPtr
DetailedDiscovery::getDetailedDiscoveryEntityInformation(
    const std::vector<xs_unsignedInt> &entityAddress) const {
  return d->getDetailedDiscoveryEntityInformation(EntityAddress(entityAddress));
}

bool DetailedDiscovery::addDetailedDiscoveryFeatureInformation(
    const NodeManagementDetailedDiscoveryFeatureInformation
        &featureInformation) {
  return d->addDetailedDiscoveryFeatureInformation(featureInformation);
}

NodeManagementDetailedDiscoveryFeatureInformationPtr
DetailedDiscovery::getDetailedDiscoveryFeatureInformation(
    const std::vector<xs_unsignedInt> &entityAddress,
    xs_unsignedInt featureId) const {
  return d->getDetailedDiscoveryFeatureInformation(EntityAddress(entityAddress),
                                                   featureId);
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscovery::getDetailedDiscoveryFeatureInformationByEntity(
    const std::vector<xs_unsignedInt> &entityAddress) const {
  return d->getFeatureInformationByEntity(EntityAddress(entityAddress));
}

std::vector<FunctionProperty> DetailedDiscovery::getFunctionPropertiesByFeature(
    const EntityAddress &entityAddress, xs_unsignedInt feature) const {
  return d->getFunctionPropertiesByFeature(entityAddress, feature);
}

} // end namespace keo_datagram