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

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

#include "DestinationListImpl.h"
#include <keo_datagram/core/DestinationList.h>

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

DestinationList::DestinationList() : d(new DestinationListImpl()) {}

DestinationList::DestinationList(
    NodeManagementDestinationListDataConstPtr listData)
    : d(new DestinationListImpl(listData)) {}

DestinationList::~DestinationList() { delete d; }

void DestinationList::clear() { d->clear(); }

NodeManagementDestinationListDataPtr
DestinationList::getDestinationListInformation() const {
  std::vector<NodeManagementDestinationData> listData;

  // get list of destinations
  std::vector<xs_string> destinations = d->getListOfDestinations();

  auto iter = destinations.begin();
  auto iterEnd = destinations.end();

  for (; iter != iterEnd; ++iter) {
    listData.push_back(d->getDestinationInformation(*iter));
  }

  return NodeManagementDestinationListDataPtr(
      new NodeManagementDestinationListData(listData));
}

NodeManagementDestinationData
DestinationList::getDestinationInformation(const xs_string &deviceName) const {
  return d->getDestinationInformation(deviceName);
}

std::vector<xs_string> DestinationList::getListOfDestinations() const {
  return d->getListOfDestinations();
}

std::vector<xs_string> DestinationList::getListOfSmartDestinations() const {
  return d->getListOfSmartDestinations();
}

bool DestinationList::insertDestinationListInformation(
    NodeManagementDestinationListDataConstPtr destinationListInformation) {
  return d->insertDestinationListInformation(destinationListInformation);
}

bool DestinationList::insertDestinationInformation(
    const NodeManagementDestinationData &data) {
  return d->insertDestinationInformation(data);
}

bool DestinationList::updateDestinationList(
    NodeManagementDestinationListDataConstPtr listData,
    const std::vector<Filter> &cmdFilterList) {
  return d->updateDestinationList(listData, cmdFilterList);
}

void DestinationList::removeDestinationInformation(
    const xs_string &deviceName) {
  d->removeDestinationInformation(deviceName);
}

NodeManagementDestinationData
DestinationList::getDestinationInformationFromRemoved(
    const xs_string &deviceName) {
  return d->getDestinationInformationFromRemoved(deviceName);
}

int DestinationList::getNumberOfModifiedDevices() const {
  return d->getNumberOfModifiedDevices();
}

std::vector<xs_string> DestinationList::getModifiedDevicesList() const {
  return d->getModifiedDevicesList();
}

int DestinationList::getNumberOfAddedDevices() const {
  return d->getNumberOfAddedDevices();
}

std::vector<xs_string> DestinationList::getAddedDevicesList() const {
  return d->getAddedDevicesList();
}

int DestinationList::getNumberOfRemovedDevices() const {
  return d->getNumberOfRemovedDevices();
}

std::vector<xs_string> DestinationList::getRemovedDevicesList() const {
  return d->getRemovedDevicesList();
}

void DestinationList::commit() { d->commit(); }

void DestinationList::unite(const DestinationList &other) {
  addIfNotExists(other);

  commit();
}

void DestinationList::subtract(const DestinationList &other) {
  std::vector<xs_string> except;

  removeIfExists(other, except);

  commit();
}

void DestinationList::addIfNotExists(const DestinationList &other) {
  std::vector<xs_string> otherDestinations = other.getListOfDestinations();

  std::vector<xs_string>::const_iterator iter = otherDestinations.begin();

  for (; iter != otherDestinations.end(); ++iter) {
    if (!d->contains(*iter)) {
      insertDestinationInformation(other.getDestinationInformation(*iter));
    }
  }
}

void DestinationList::removeIfExists(const DestinationList &other,
                                     const std::vector<xs_string> &except) {
  std::vector<xs_string> otherDestinations = other.getListOfDestinations();

  std::vector<xs_string>::const_iterator iter = otherDestinations.begin();

  for (; iter != otherDestinations.end(); ++iter) {
    if (0 == except.size() ||
        std::find(except.begin(), except.end(), *iter) != except.end()) {
      removeDestinationInformation(*iter);
    }
  }
}

std::vector<NodeManagementDestinationData>
DestinationList::getDestinationInformationUpdate(
    const xs_string &except) const {
  std::vector<NodeManagementDestinationData> retval;

  std::vector<xs_string> list = getAddedDevicesList();

  auto iter = list.begin();
  auto iterEnd = list.end();

  for (; iter != iterEnd; ++iter) {
    if (except != *iter) {
      retval.push_back(d->getDestinationInformation(*iter));
    }
  }

  list = getModifiedDevicesList();

  iter = list.begin();
  iterEnd = list.end();

  for (; iter != iterEnd; ++iter) {
    if (except != *iter) {
      retval.push_back(d->getDestinationInformation(*iter));
    }
  }

  list = getRemovedDevicesList();

  iter = list.begin();
  iterEnd = list.end();

  for (; iter != iterEnd; ++iter) {
    if (except != *iter) {
      retval.push_back(d->getDestinationInformationFromRemoved(*iter));
    }
  }

  return retval;
}

NodeManagementDestinationListDataPtr
DestinationList::getDestinationListInformationUpdate(
    const xs_string &except) const {
  NodeManagementDestinationListDataPtr ptr =
      NodeManagementDestinationListDataPtr(
          new NodeManagementDestinationListData());
  ptr->setNodeManagementDestinationData(
      getDestinationInformationUpdate(except));

  return ptr;
}

CmdPtr DestinationList::createNotificationCmd() {
  return d->createNotificationCmd();
}
}