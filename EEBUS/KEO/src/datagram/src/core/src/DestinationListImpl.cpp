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

#include "DestinationListImpl.h"
#include <keo_datagram/core/NodeManagementDestinationListDataSelectors.h>

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

DestinationList::DestinationListImpl::DestinationListImpl() {}

DestinationList::DestinationListImpl::DestinationListImpl(
    NodeManagementDestinationListDataConstPtr listData) {
  updateDestinationList(listData, std::vector<Filter>());
  commit();
}

void DestinationList::DestinationListImpl::clear() {
  m_informationData.clear();
  m_informationDataRemoved.clear();
  m_dataModified.clear();
  m_dataAdded.clear();
}

NodeManagementDestinationData
DestinationList::DestinationListImpl::getDestinationInformation(
    const xs_string &deviceName) const {
  informationData_MapType::const_iterator it =
      m_informationData.find(deviceName);
  if (it != m_informationData.end()) {
    return it->second;
  }
  return NodeManagementDestinationData();
}

std::vector<xs_string>
DestinationList::DestinationListImpl::getListOfDestinations() const {
  std::vector<xs_string> destinations;

  informationData_MapType::const_iterator iter = m_informationData.begin();
  informationData_MapType::const_iterator iterEnd = m_informationData.end();
  for (; iter != iterEnd; ++iter) {
    destinations.push_back(iter->first);
  }

  return destinations;
}

std::vector<xs_string>
DestinationList::DestinationListImpl::getListOfSmartDestinations() const {
  std::vector<xs_string> smartDestinations;

  informationData_MapType::const_iterator iter = m_informationData.begin();
  informationData_MapType::const_iterator iterEnd = m_informationData.end();

  for (; iter != iterEnd; ++iter) {
    if (iter->second.getDeviceDescriptionIsSet() &&
        iter->second.getDeviceDescription().getNetworkFeatureSetIsSet() &&
        iter->second.getDeviceDescription().getNetworkFeatureSet().getValue() !=
            NetworkManagementFeatureSet::Value::SIMPLE) {
      smartDestinations.push_back(iter->first);
    }
  }

  return smartDestinations;
}

bool DestinationList::DestinationListImpl::insertDestinationListInformation(
    NodeManagementDestinationListDataConstPtr destinationListInformation) {
  bool retval = false;
  if (destinationListInformation->getNodeManagementDestinationDataIsSet()) {
    std::vector<NodeManagementDestinationData> destinationData =
        destinationListInformation->getNodeManagementDestinationData();
    std::vector<NodeManagementDestinationData>::const_iterator iter =
        destinationData.begin();
    std::vector<NodeManagementDestinationData>::const_iterator iterEnd =
        destinationData.end();
    retval = true;
    for (; iter != iterEnd; ++iter) {
      retval |= insertDestinationInformation(*iter);
    }
  }
  return retval;
}

bool DestinationList::DestinationListImpl::insertDestinationInformation(
    const NodeManagementDestinationData &data) {
  bool retval = false;

  // is valid
  if (data.getDeviceDescriptionIsSet() &&
      data.getDeviceDescription().getDeviceAddressIsSet()) {
    xs_string deviceName =
        data.getDeviceDescription().getDeviceAddress().getDevice();
    if (!deviceName.empty()) {
      retval = true;
      if (!data.getDeviceDescription().getLastStateChangeIsSet() ||
          NetworkManagementStateChange::Value::REMOVED !=
              data.getDeviceDescription().getLastStateChange().getValue()) {
        NodeManagementDestinationData copyData(data);
        informationData_MapType::iterator it =
            m_informationData.find(deviceName);
        if (it != m_informationData.end()) {
          NetworkManagementDeviceDescriptionData descriptionData =
              copyData.getDeviceDescription();
          descriptionData.setLastStateChange(
              NetworkManagementStateChange::Value::MODIFIED);
          copyData.setDeviceDescription(descriptionData);
          m_dataModified.push_back(deviceName);
        } else {
          if (NetworkManagementStateChange::Value::MODIFIED ==
              data.getDeviceDescription().getLastStateChange().getValue()) {
            m_dataModified.push_back(deviceName);
          } else {
            NetworkManagementDeviceDescriptionData descriptionData =
                copyData.getDeviceDescription();
            descriptionData.setLastStateChange(
                NetworkManagementStateChange::Value::ADDED);
            copyData.setDeviceDescription(descriptionData);
            m_dataAdded.push_back(deviceName);
          }
        }
        if (!m_informationData.insert(std::make_pair(deviceName, copyData))
                 .second) {
          //  Element already present
          m_informationData[deviceName] = copyData;
        }
      } else {
        // removed
        informationData_MapType::iterator it =
            m_informationData.find(deviceName);
        if (it != m_informationData.end()) {
          // remove from destinations list
          m_informationData.erase(it);
        }

        if (!m_informationDataRemoved.insert(std::make_pair(deviceName, data))
                 .second) {
          //  Element already present
          m_informationDataRemoved[deviceName] = data;
        }
      }
    }
  }
  return retval;
}

bool DestinationList::DestinationListImpl::updateDestinationList(
    NodeManagementDestinationListDataConstPtr listData,
    const std::vector<Filter> &cmdFilterList) {
  bool retval = insertDestinationListInformation(listData);
  for (Filter filter : cmdFilterList) {
    if (filter.getCmdControlIsSet() &&
        filter.getCmdControl().getDeleteIsSet()) {
      if (filter.getDataSelectorsIsSet()) {
        std::vector<DataSelectorsPtr> selectorList = filter.getDataSelectors();
        auto iter = selectorList.begin();
        auto iterEnd = selectorList.end();
        for (; iter != iterEnd; ++iter) {
          if ((*iter)->getDataType() ==
              DataSelectors::Type::
                  NODE_MANAGEMENT_DESTINATION_LIST_DATA_SELECTORS_TYPE) {
            NodeManagementDestinationListDataSelectorsPtr selector =
                std::dynamic_pointer_cast<
                    NodeManagementDestinationListDataSelectorsPtr::
                        element_type>(*iter);
            if (selector->getDeviceDescriptionIsSet() &&
                selector->getDeviceDescription().getDeviceAddressIsSet() &&
                selector->getDeviceDescription()
                    .getDeviceAddress()
                    .getDeviceIsSet()) {
              std::string deviceName = selector->getDeviceDescription()
                                           .getDeviceAddress()
                                           .getDevice();
              NodeManagementDestinationData data;
              informationData_MapType::iterator it =
                  m_informationData.find(deviceName);
              if (it != m_informationData.end()) {
                data = it->second;
                m_informationData.erase(it);
              }
              if (!m_informationDataRemoved
                       .insert(std::make_pair(deviceName, data))
                       .second) {
                m_informationDataRemoved[deviceName] = data;
              }
              retval &= true;
            }
          }
        }
      }
    }
  }
  return retval;
}

void DestinationList::DestinationListImpl::removeDestinationInformation(
    const xs_string &deviceName) {
  informationData_MapType::iterator it = m_informationData.find(deviceName);

  if (it != m_informationData.end()) {
    m_informationDataRemoved.insert(std::make_pair(deviceName, it->second));
    m_informationData.erase(it);
  }
}

NodeManagementDestinationData
DestinationList::DestinationListImpl::getDestinationInformationFromRemoved(
    const xs_string &deviceName) {
  NodeManagementDestinationData destinationInformation;

  informationData_MapType::iterator it =
      m_informationDataRemoved.find(deviceName);

  if (it != m_informationDataRemoved.end()) {
    destinationInformation = m_informationDataRemoved[deviceName];
  }
  return destinationInformation;
}
std::vector<xs_string>
DestinationList::DestinationListImpl::getRemovedDevicesList() const {
  std::vector<xs_string> destinations;

  informationData_MapType::const_iterator iter =
      m_informationDataRemoved.begin();
  informationData_MapType::const_iterator iterEnd =
      m_informationDataRemoved.end();
  for (; iter != iterEnd; ++iter) {
    destinations.push_back(iter->first);
  }

  return destinations;
}
void DestinationList::DestinationListImpl::commit() {
  m_dataAdded.clear();
  m_dataModified.clear();
  m_informationDataRemoved.clear();
}
CmdPtr DestinationList::DestinationListImpl::createNotificationCmd() {
  NodeManagementDestinationListDataPtr cmdData =
      NodeManagementDestinationListDataPtr(
          new NodeManagementDestinationListData());
  std::vector<Filter> cmdFilterList;
  std::vector<xs_string> removedDevices = getRemovedDevicesList();
  if (removedDevices.size() > 0) {
    Filter filterType;
    CmdControl cmdControl;
    cmdControl.setDelete();
    filterType.setCmdControl(cmdControl);
    std::vector<DataSelectorsPtr> selectorList;
    auto iter = removedDevices.begin();
    auto iterEnd = removedDevices.end();
    for (; iter != iterEnd; ++iter) {
      DeviceAddress deviceAddress(*iter);
      NetworkManagementDeviceDescriptionListDataSelectors description;
      description.setDeviceAddress(deviceAddress);
      NodeManagementDestinationListDataSelectorsPtr selector =
          NodeManagementDestinationListDataSelectorsPtr(
              new NodeManagementDestinationListDataSelectors(description));
      selectorList.push_back(selector);
    }
    filterType.setDataSelectors(selectorList);
    cmdFilterList.push_back(filterType);
  }
  if (m_dataModified.size() > 0 || m_dataAdded.size() > 0) {
    Filter filterType;
    CmdControl cmdControl;
    cmdControl.setPartial();
    filterType.setCmdControl(cmdControl);
    std::vector<NodeManagementDestinationData> dataList;
    dataModified_ListType::const_iterator iter = m_dataModified.begin();
    dataModified_ListType::const_iterator iterEnd = m_dataModified.end();
    for (; iter != iterEnd; ++iter) {
      dataList.push_back(m_informationData[*iter]);
    }
    iter = m_dataAdded.begin();
    iterEnd = m_dataAdded.end();
    for (; iter != iterEnd; ++iter) {
      dataList.push_back(m_informationData[*iter]);
    }
    cmdData->setNodeManagementDestinationData(dataList);
    cmdFilterList.push_back(filterType);
  }
  if (cmdFilterList.size() > 0) {
    CmdPtr notificationCmd = CmdPtr(new Cmd(cmdData));
    notificationCmd->setFunction(
        Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA);
    notificationCmd->setFilter(cmdFilterList);
    return notificationCmd;
  }
  return CmdPtr();
}
bool DestinationList::DestinationListImpl::contains(
    const xs_string &address) const {
  return (m_informationData.find(address) != m_informationData.end());
}
}