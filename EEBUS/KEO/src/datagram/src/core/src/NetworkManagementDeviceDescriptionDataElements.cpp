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

#include <keo_datagram/core/NetworkManagementDeviceDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementDeviceDescriptionDataElements::
    NetworkManagementDeviceDescriptionDataElements()
    : DataElements(), m_deviceAddressIsSet(false),
      m_deviceAddress(DeviceAddressElements()), m_deviceTypeIsSet(false),
      m_networkManagementResponsibleAddressIsSet(false),
      m_nativeSetupIsSet(false), m_technologyAddressIsSet(false),
      m_communicationsTechnologyInformationIsSet(false),
      m_networkFeatureSetIsSet(false), m_lastStateChangeIsSet(false),
      m_minimumTrustLevelIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool NetworkManagementDeviceDescriptionDataElements::operator==(
    const NetworkManagementDeviceDescriptionDataElements &c_classObject) const {
  if (m_deviceAddressIsSet != c_classObject.m_deviceAddressIsSet ||
      (m_deviceAddressIsSet &&
       (m_deviceAddress != c_classObject.m_deviceAddress))) {
    return false;
  }
  if (m_deviceTypeIsSet != c_classObject.m_deviceTypeIsSet) {
    return false;
  }
  if (m_networkManagementResponsibleAddressIsSet !=
      c_classObject.m_networkManagementResponsibleAddressIsSet) {
    return false;
  }
  if (m_nativeSetupIsSet != c_classObject.m_nativeSetupIsSet) {
    return false;
  }
  if (m_technologyAddressIsSet != c_classObject.m_technologyAddressIsSet) {
    return false;
  }
  if (m_communicationsTechnologyInformationIsSet !=
      c_classObject.m_communicationsTechnologyInformationIsSet) {
    return false;
  }
  if (m_networkFeatureSetIsSet != c_classObject.m_networkFeatureSetIsSet) {
    return false;
  }
  if (m_lastStateChangeIsSet != c_classObject.m_lastStateChangeIsSet) {
    return false;
  }
  if (m_minimumTrustLevelIsSet != c_classObject.m_minimumTrustLevelIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool NetworkManagementDeviceDescriptionDataElements::operator!=(
    const NetworkManagementDeviceDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementDeviceDescriptionDataElements::isEmpty() const {
  return !m_deviceAddressIsSet && !m_deviceTypeIsSet &&
         !m_networkManagementResponsibleAddressIsSet && !m_nativeSetupIsSet &&
         !m_technologyAddressIsSet &&
         !m_communicationsTechnologyInformationIsSet &&
         !m_networkFeatureSetIsSet && !m_lastStateChangeIsSet &&
         !m_minimumTrustLevelIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
NetworkManagementDeviceDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementDeviceDescriptionDataElements::clone() const {
  return std::make_shared<NetworkManagementDeviceDescriptionDataElements>(
      *this);
}

void NetworkManagementDeviceDescriptionDataElements::setDeviceAddress(
    const DeviceAddressElements &deviceAddress) {
  m_deviceAddress = deviceAddress;
  m_deviceAddressIsSet = true;
}

const DeviceAddressElements &
NetworkManagementDeviceDescriptionDataElements::getDeviceAddress() const {
  return m_deviceAddress;
}

void NetworkManagementDeviceDescriptionDataElements::cleanDeviceAddress() {
  m_deviceAddress = DeviceAddressElements();
  m_deviceAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getDeviceAddressIsSet()
    const {
  return m_deviceAddressIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setDeviceType() {
  m_deviceTypeIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanDeviceType() {
  m_deviceTypeIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getDeviceTypeIsSet()
    const {
  return m_deviceTypeIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::
    setNetworkManagementResponsibleAddress() {
  m_networkManagementResponsibleAddressIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::
    cleanNetworkManagementResponsibleAddress() {
  m_networkManagementResponsibleAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::
    getNetworkManagementResponsibleAddressIsSet() const {
  return m_networkManagementResponsibleAddressIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setNativeSetup() {
  m_nativeSetupIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanNativeSetup() {
  m_nativeSetupIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getNativeSetupIsSet()
    const {
  return m_nativeSetupIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setTechnologyAddress() {
  m_technologyAddressIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanTechnologyAddress() {
  m_technologyAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getTechnologyAddressIsSet()
    const {
  return m_technologyAddressIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::
    setCommunicationsTechnologyInformation() {
  m_communicationsTechnologyInformationIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::
    cleanCommunicationsTechnologyInformation() {
  m_communicationsTechnologyInformationIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::
    getCommunicationsTechnologyInformationIsSet() const {
  return m_communicationsTechnologyInformationIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setNetworkFeatureSet() {
  m_networkFeatureSetIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanNetworkFeatureSet() {
  m_networkFeatureSetIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getNetworkFeatureSetIsSet()
    const {
  return m_networkFeatureSetIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setLastStateChange() {
  m_lastStateChangeIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanLastStateChange() {
  m_lastStateChangeIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getLastStateChangeIsSet()
    const {
  return m_lastStateChangeIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setMinimumTrustLevel() {
  m_minimumTrustLevelIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanMinimumTrustLevel() {
  m_minimumTrustLevelIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getMinimumTrustLevelIsSet()
    const {
  return m_minimumTrustLevelIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementDeviceDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void NetworkManagementDeviceDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool NetworkManagementDeviceDescriptionDataElements::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool NetworkManagementDeviceDescriptionDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"deviceAddress", "deviceType",
                   "networkManagementResponsibleAddress", "nativeSetup",
                   "technologyAddress", "communicationsTechnologyInformation",
                   "networkFeatureSet", "lastStateChange", "minimumTrustLevel",
                   "label", "description"})) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "deviceType")) {
      m_deviceTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "networkManagementResponsibleAddress")) {
      m_networkManagementResponsibleAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "nativeSetup")) {
      m_nativeSetupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "technologyAddress")) {
      m_technologyAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "communicationsTechnologyInformation")) {
      m_communicationsTechnologyInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "networkFeatureSet")) {
      m_networkFeatureSetIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "lastStateChange")) {
      m_lastStateChangeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "minimumTrustLevel")) {
      m_minimumTrustLevelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementDeviceDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_deviceAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceAddress", m_deviceAddress);
  }
  if (m_deviceTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("deviceType");
  }
  if (m_networkManagementResponsibleAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeTag("networkManagementResponsibleAddress");
  }
  if (m_nativeSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("nativeSetup");
  }
  if (m_technologyAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("technologyAddress");
  }
  if (m_communicationsTechnologyInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeTag("communicationsTechnologyInformation");
  }
  if (m_networkFeatureSetIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("networkFeatureSet");
  }
  if (m_lastStateChangeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("lastStateChange");
  }
  if (m_minimumTrustLevelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("minimumTrustLevel");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram