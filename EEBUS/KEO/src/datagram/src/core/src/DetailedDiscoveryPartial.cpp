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

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */
#include <keo_datagram/core/DetailedDiscoveryPartial.h>

#include "DetailedDiscoveryPartialImpl.h"

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

DetailedDiscoveryPartial::DetailedDiscoveryPartial()
    : d(new DetailedDiscoveryPartialImpl()) {}

DetailedDiscoveryPartial::~DetailedDiscoveryPartial() { delete d; }

DetailedDiscoveryPartial::DetailedDiscoveryPartial(
    const DetailedDiscoveryPartial &that)
    : d(new DetailedDiscoveryPartialImpl(*that.d)) {}

DetailedDiscoveryPartial &DetailedDiscoveryPartial::
operator=(const DetailedDiscoveryPartial &that) {
  if (this != &that) {
    *d = *that.d;
  }
  return *this;
}

bool DetailedDiscoveryPartial::setByDiffingDetailedDiscoveries(
    const DetailedDiscovery &sourceDetailedDiscovery,
    const DetailedDiscovery &targetDetailedDiscovery) {
  return d->setByDiffingDetailedDiscoveries(sourceDetailedDiscovery,
                                            targetDetailedDiscovery);
}

DetailedDiscovery DetailedDiscoveryPartial::getMergedDetailedDiscovery(
    const DetailedDiscovery &sourceDetailedDiscovery, bool *success) const {
  return d->getMergedDetailedDiscovery(sourceDetailedDiscovery, success);
}

bool DetailedDiscoveryPartial::setDetailedDiscoveryData(
    const NodeManagementDetailedDiscoveryData &detailedDiscoveryData) {
  return d->setDetailedDiscoveryData(detailedDiscoveryData);
}

NodeManagementDetailedDiscoveryDataPtr
DetailedDiscoveryPartial::getDetailedDiscoveryDataPtr() const {
  return d->getDetailedDiscoveryDataPtr();
}

bool DetailedDiscoveryPartial::addDetailedDiscoveryEntityInformation(
    const NodeManagementDetailedDiscoveryEntityInformation &entityInformation) {
  return d->addDetailedDiscoveryEntityInformation(entityInformation);
}

bool DetailedDiscoveryPartial::addDetailedDiscoveryFeatureInformation(
    const NodeManagementDetailedDiscoveryFeatureInformation
        &featureInformation) {
  return d->addDetailedDiscoveryFeatureInformation(featureInformation);
}

NodeManagementDetailedDiscoveryEntityInformationPtr
DetailedDiscoveryPartial::getDetailedDiscoveryEntityInformation(
    const std::vector<xs_unsignedInt> &entityAddress) const {
  return d->getDetailedDiscoveryEntityInformation(EntityAddress(entityAddress));
}

NodeManagementDetailedDiscoveryFeatureInformationPtr
DetailedDiscoveryPartial::getDetailedDiscoveryFeatureInformation(
    const std::vector<xs_unsignedInt> &entityAddress,
    xs_unsignedInt featureId) const {
  return d->getDetailedDiscoveryFeatureInformation(EntityAddress(entityAddress),
                                                   featureId);
}

Datagram DetailedDiscoveryPartial::createPartialDetailedDiscoveryDatagram(
    const Header &header) const {
  return d->createPartialDetailedDiscoveryDatagram(header);
}

bool DetailedDiscoveryPartial::getDeviceNameIsSet() const {
  return d->getDeviceNameIsSet();
}

std::string DetailedDiscoveryPartial::getDeviceName() const {
  return d->getDeviceName();
}

void DetailedDiscoveryPartial::setDeviceName(const std::string &deviceName) {
  return d->setDeviceName(deviceName);
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::getAddedEntities() const {
  return d->getAddedEntities();
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::getModifiedEntities() const {
  return d->getModifiedEntities();
}

std::vector<NodeManagementDetailedDiscoveryEntityInformation>
DetailedDiscoveryPartial::getRemovedEntities() const {
  return d->getRemovedEntities();
}

bool DetailedDiscoveryPartial::isEntityModified(
    const EntityAddress &entityAddress) const {
  return d->isEntityModified(entityAddress);
}

bool DetailedDiscoveryPartial::isEntityRemoved(
    const EntityAddress &entityAddress) const {
  return d->isEntityRemoved(entityAddress);
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::getAddedFeatures() const {
  return d->getAddedFeatures();
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::getModifiedFeatures() const {
  return d->getModifiedFeatures();
}

std::vector<NodeManagementDetailedDiscoveryFeatureInformation>
DetailedDiscoveryPartial::getRemovedFeatures() const {
  return d->getRemovedFeatures();
}

bool DetailedDiscoveryPartial::isFeatureModified(
    const FeatureAddress &featureAddress) const {
  return d->isFeatureModified(featureAddress);
}

bool DetailedDiscoveryPartial::isFeatureRemoved(
    const FeatureAddress &featureAddress) const {
  return d->isFeatureRemoved(featureAddress);
}

bool DetailedDiscoveryPartial::isEmpty() const {
  return d->getAddedEntities().empty() && d->getModifiedEntities().empty() &&
         d->getRemovedEntities().empty() && d->getAddedFeatures().empty() &&
         d->getModifiedFeatures().empty() && d->getRemovedFeatures().empty();
}

} // namespace keo_datagram