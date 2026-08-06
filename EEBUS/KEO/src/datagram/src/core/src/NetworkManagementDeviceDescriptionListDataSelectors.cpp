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

#include <keo_datagram/core/NetworkManagementDeviceDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementDeviceDescriptionListDataSelectors::
    NetworkManagementDeviceDescriptionListDataSelectors()
    : DataSelectors(), m_deviceAddressIsSet(false),
      m_deviceAddress(DeviceAddress()), m_deviceTypeIsSet(false),
      m_deviceType(DeviceType())

{}

NetworkManagementDeviceDescriptionListDataSelectors::
    NetworkManagementDeviceDescriptionListDataSelectors(
        const DeviceAddress &c_deviceAddress, const DeviceType &c_deviceType)
    : DataSelectors(), m_deviceAddressIsSet(true),
      m_deviceAddress(c_deviceAddress), m_deviceTypeIsSet(true),
      m_deviceType(c_deviceType)

{}

bool NetworkManagementDeviceDescriptionListDataSelectors::operator==(
    const NetworkManagementDeviceDescriptionListDataSelectors &c_classObject)
    const {
  if (m_deviceAddressIsSet != c_classObject.m_deviceAddressIsSet ||
      (m_deviceAddressIsSet &&
       (m_deviceAddress != c_classObject.m_deviceAddress))) {
    return false;
  }
  if (m_deviceTypeIsSet != c_classObject.m_deviceTypeIsSet ||
      (m_deviceTypeIsSet && (m_deviceType != c_classObject.m_deviceType))) {
    return false;
  }

  return true;
}

bool NetworkManagementDeviceDescriptionListDataSelectors::operator!=(
    const NetworkManagementDeviceDescriptionListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool NetworkManagementDeviceDescriptionListDataSelectors::isEmpty() const {
  return !m_deviceAddressIsSet && !m_deviceTypeIsSet;
}

DataSelectors::Type
NetworkManagementDeviceDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
NetworkManagementDeviceDescriptionListDataSelectors::clone() const {
  return std::make_shared<NetworkManagementDeviceDescriptionListDataSelectors>(
      *this);
}

void NetworkManagementDeviceDescriptionListDataSelectors::setDeviceAddress(
    const DeviceAddress &deviceAddress) {
  m_deviceAddress = deviceAddress;
  m_deviceAddressIsSet = true;
}

const DeviceAddress &
NetworkManagementDeviceDescriptionListDataSelectors::getDeviceAddress() const {
  return m_deviceAddress;
}

void NetworkManagementDeviceDescriptionListDataSelectors::cleanDeviceAddress() {
  m_deviceAddress = DeviceAddress();
  m_deviceAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionListDataSelectors::
    getDeviceAddressIsSet() const {
  return m_deviceAddressIsSet;
}

void NetworkManagementDeviceDescriptionListDataSelectors::setDeviceType(
    const DeviceType &deviceType) {
  m_deviceType = deviceType;
  m_deviceTypeIsSet = true;
}

const DeviceType &
NetworkManagementDeviceDescriptionListDataSelectors::getDeviceType() const {
  return m_deviceType;
}

void NetworkManagementDeviceDescriptionListDataSelectors::cleanDeviceType() {
  m_deviceType = DeviceType();
  m_deviceTypeIsSet = false;
}

bool NetworkManagementDeviceDescriptionListDataSelectors::getDeviceTypeIsSet()
    const {
  return m_deviceTypeIsSet;
}

bool NetworkManagementDeviceDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"deviceAddress", "deviceType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceAddress", &m_deviceAddress)) {
      m_deviceAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceType", &m_deviceType)) {
      m_deviceTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
NetworkManagementDeviceDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_deviceAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceAddress", m_deviceAddress);
  }
  if (m_deviceTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceType", m_deviceType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram