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

#include <keo_datagram/core/NetworkManagementDeviceDescriptionData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementDeviceDescriptionData::NetworkManagementDeviceDescriptionData()
    : m_deviceAddressIsSet(false), m_deviceAddress(DeviceAddress()),
      m_deviceTypeIsSet(false), m_deviceType(DeviceType()),
      m_networkManagementResponsibleAddressIsSet(false),
      m_networkManagementResponsibleAddress(FeatureAddress()),
      m_nativeSetupIsSet(false), m_nativeSetup(""),
      m_technologyAddressIsSet(false), m_technologyAddress(""),
      m_communicationsTechnologyInformationIsSet(false),
      m_communicationsTechnologyInformation(""),
      m_networkFeatureSetIsSet(false),
      m_networkFeatureSet(NetworkManagementFeatureSet()),
      m_lastStateChangeIsSet(false),
      m_lastStateChange(NetworkManagementStateChange()),
      m_minimumTrustLevelIsSet(false), m_minimumTrustLevel(""),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description("")

{}

bool NetworkManagementDeviceDescriptionData::
operator==(const NetworkManagementDeviceDescriptionData &c_classObject) const {
  if (m_deviceAddressIsSet != c_classObject.m_deviceAddressIsSet ||
      (m_deviceAddressIsSet &&
       (m_deviceAddress != c_classObject.m_deviceAddress))) {
    return false;
  }
  if (m_deviceTypeIsSet != c_classObject.m_deviceTypeIsSet ||
      (m_deviceTypeIsSet && (m_deviceType != c_classObject.m_deviceType))) {
    return false;
  }
  if (m_networkManagementResponsibleAddressIsSet !=
          c_classObject.m_networkManagementResponsibleAddressIsSet ||
      (m_networkManagementResponsibleAddressIsSet &&
       (m_networkManagementResponsibleAddress !=
        c_classObject.m_networkManagementResponsibleAddress))) {
    return false;
  }
  if (m_nativeSetupIsSet != c_classObject.m_nativeSetupIsSet ||
      (m_nativeSetupIsSet && (m_nativeSetup != c_classObject.m_nativeSetup))) {
    return false;
  }
  if (m_technologyAddressIsSet != c_classObject.m_technologyAddressIsSet ||
      (m_technologyAddressIsSet &&
       (m_technologyAddress != c_classObject.m_technologyAddress))) {
    return false;
  }
  if (m_communicationsTechnologyInformationIsSet !=
          c_classObject.m_communicationsTechnologyInformationIsSet ||
      (m_communicationsTechnologyInformationIsSet &&
       (m_communicationsTechnologyInformation !=
        c_classObject.m_communicationsTechnologyInformation))) {
    return false;
  }
  if (m_networkFeatureSetIsSet != c_classObject.m_networkFeatureSetIsSet ||
      (m_networkFeatureSetIsSet &&
       (m_networkFeatureSet != c_classObject.m_networkFeatureSet))) {
    return false;
  }
  if (m_lastStateChangeIsSet != c_classObject.m_lastStateChangeIsSet ||
      (m_lastStateChangeIsSet &&
       (m_lastStateChange != c_classObject.m_lastStateChange))) {
    return false;
  }
  if (m_minimumTrustLevelIsSet != c_classObject.m_minimumTrustLevelIsSet ||
      (m_minimumTrustLevelIsSet &&
       (m_minimumTrustLevel != c_classObject.m_minimumTrustLevel))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool NetworkManagementDeviceDescriptionData::
operator!=(const NetworkManagementDeviceDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementDeviceDescriptionData::isEmpty() const {
  return !m_deviceAddressIsSet && !m_deviceTypeIsSet &&
         !m_networkManagementResponsibleAddressIsSet && !m_nativeSetupIsSet &&
         !m_technologyAddressIsSet &&
         !m_communicationsTechnologyInformationIsSet &&
         !m_networkFeatureSetIsSet && !m_lastStateChangeIsSet &&
         !m_minimumTrustLevelIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void NetworkManagementDeviceDescriptionData::setDeviceAddress(
    const DeviceAddress &deviceAddress) {
  m_deviceAddress = deviceAddress;
  m_deviceAddressIsSet = true;
}

const DeviceAddress &
NetworkManagementDeviceDescriptionData::getDeviceAddress() const {
  return m_deviceAddress;
}

void NetworkManagementDeviceDescriptionData::cleanDeviceAddress() {
  m_deviceAddress = DeviceAddress();
  m_deviceAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getDeviceAddressIsSet() const {
  return m_deviceAddressIsSet;
}

void NetworkManagementDeviceDescriptionData::setDeviceType(
    const DeviceType &deviceType) {
  m_deviceType = deviceType;
  m_deviceTypeIsSet = true;
}

const DeviceType &
NetworkManagementDeviceDescriptionData::getDeviceType() const {
  return m_deviceType;
}

void NetworkManagementDeviceDescriptionData::cleanDeviceType() {
  m_deviceType = DeviceType();
  m_deviceTypeIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getDeviceTypeIsSet() const {
  return m_deviceTypeIsSet;
}

void NetworkManagementDeviceDescriptionData::
    setNetworkManagementResponsibleAddress(
        const FeatureAddress &networkManagementResponsibleAddress) {
  m_networkManagementResponsibleAddress = networkManagementResponsibleAddress;
  m_networkManagementResponsibleAddressIsSet = true;
}

const FeatureAddress &
NetworkManagementDeviceDescriptionData::getNetworkManagementResponsibleAddress()
    const {
  return m_networkManagementResponsibleAddress;
}

void NetworkManagementDeviceDescriptionData::
    cleanNetworkManagementResponsibleAddress() {
  m_networkManagementResponsibleAddress = FeatureAddress();
  m_networkManagementResponsibleAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::
    getNetworkManagementResponsibleAddressIsSet() const {
  return m_networkManagementResponsibleAddressIsSet;
}

void NetworkManagementDeviceDescriptionData::setNativeSetup(
    const xs_string &nativeSetup) {
  m_nativeSetup = nativeSetup;
  m_nativeSetupIsSet = true;
}

const xs_string &
NetworkManagementDeviceDescriptionData::getNativeSetup() const {
  return m_nativeSetup;
}

void NetworkManagementDeviceDescriptionData::cleanNativeSetup() {
  m_nativeSetup = "";
  m_nativeSetupIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getNativeSetupIsSet() const {
  return m_nativeSetupIsSet;
}

void NetworkManagementDeviceDescriptionData::setTechnologyAddress(
    const xs_string &technologyAddress) {
  m_technologyAddress = technologyAddress;
  m_technologyAddressIsSet = true;
}

const xs_string &
NetworkManagementDeviceDescriptionData::getTechnologyAddress() const {
  return m_technologyAddress;
}

void NetworkManagementDeviceDescriptionData::cleanTechnologyAddress() {
  m_technologyAddress = "";
  m_technologyAddressIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getTechnologyAddressIsSet() const {
  return m_technologyAddressIsSet;
}

void NetworkManagementDeviceDescriptionData::
    setCommunicationsTechnologyInformation(
        const xs_string &communicationsTechnologyInformation) {
  m_communicationsTechnologyInformation = communicationsTechnologyInformation;
  m_communicationsTechnologyInformationIsSet = true;
}

const xs_string &
NetworkManagementDeviceDescriptionData::getCommunicationsTechnologyInformation()
    const {
  return m_communicationsTechnologyInformation;
}

void NetworkManagementDeviceDescriptionData::
    cleanCommunicationsTechnologyInformation() {
  m_communicationsTechnologyInformation = "";
  m_communicationsTechnologyInformationIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::
    getCommunicationsTechnologyInformationIsSet() const {
  return m_communicationsTechnologyInformationIsSet;
}

void NetworkManagementDeviceDescriptionData::setNetworkFeatureSet(
    const NetworkManagementFeatureSet &networkFeatureSet) {
  m_networkFeatureSet = networkFeatureSet;
  m_networkFeatureSetIsSet = true;
}

const NetworkManagementFeatureSet &
NetworkManagementDeviceDescriptionData::getNetworkFeatureSet() const {
  return m_networkFeatureSet;
}

void NetworkManagementDeviceDescriptionData::cleanNetworkFeatureSet() {
  m_networkFeatureSet = NetworkManagementFeatureSet();
  m_networkFeatureSetIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getNetworkFeatureSetIsSet() const {
  return m_networkFeatureSetIsSet;
}

void NetworkManagementDeviceDescriptionData::setLastStateChange(
    const NetworkManagementStateChange &lastStateChange) {
  m_lastStateChange = lastStateChange;
  m_lastStateChangeIsSet = true;
}

const NetworkManagementStateChange &
NetworkManagementDeviceDescriptionData::getLastStateChange() const {
  return m_lastStateChange;
}

void NetworkManagementDeviceDescriptionData::cleanLastStateChange() {
  m_lastStateChange = NetworkManagementStateChange();
  m_lastStateChangeIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getLastStateChangeIsSet() const {
  return m_lastStateChangeIsSet;
}

void NetworkManagementDeviceDescriptionData::setMinimumTrustLevel(
    const xs_string &minimumTrustLevel) {
  m_minimumTrustLevel = minimumTrustLevel;
  m_minimumTrustLevelIsSet = true;
}

const xs_string &
NetworkManagementDeviceDescriptionData::getMinimumTrustLevel() const {
  return m_minimumTrustLevel;
}

void NetworkManagementDeviceDescriptionData::cleanMinimumTrustLevel() {
  m_minimumTrustLevel = "";
  m_minimumTrustLevelIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getMinimumTrustLevelIsSet() const {
  return m_minimumTrustLevelIsSet;
}

void NetworkManagementDeviceDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &NetworkManagementDeviceDescriptionData::getLabel() const {
  return m_label;
}

void NetworkManagementDeviceDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementDeviceDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &
NetworkManagementDeviceDescriptionData::getDescription() const {
  return m_description;
}

void NetworkManagementDeviceDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementDeviceDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool NetworkManagementDeviceDescriptionData::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceType", &m_deviceType)) {
      m_deviceTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "networkManagementResponsibleAddress",
                                   &m_networkManagementResponsibleAddress)) {
      m_networkManagementResponsibleAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "nativeSetup", &m_nativeSetup)) {
      m_nativeSetupIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "technologyAddress", &m_technologyAddress)) {
      m_technologyAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "communicationsTechnologyInformation",
                                   &m_communicationsTechnologyInformation)) {
      m_communicationsTechnologyInformationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "networkFeatureSet", &m_networkFeatureSet)) {
      m_networkFeatureSetIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "lastStateChange", &m_lastStateChange)) {
      m_lastStateChangeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "minimumTrustLevel", &m_minimumTrustLevel)) {
      m_minimumTrustLevelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementDeviceDescriptionData::toJson() const {
  std::string result = "[";
  if (m_deviceAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceAddress", m_deviceAddress);
  }
  if (m_deviceTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("deviceType", m_deviceType);
  }
  if (m_networkManagementResponsibleAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("networkManagementResponsibleAddress",
                                     m_networkManagementResponsibleAddress);
  }
  if (m_nativeSetupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("nativeSetup", m_nativeSetup);
  }
  if (m_technologyAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("technologyAddress", m_technologyAddress);
  }
  if (m_communicationsTechnologyInformationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("communicationsTechnologyInformation",
                                     m_communicationsTechnologyInformation);
  }
  if (m_networkFeatureSetIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("networkFeatureSet", m_networkFeatureSet);
  }
  if (m_lastStateChangeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("lastStateChange", m_lastStateChange);
  }
  if (m_minimumTrustLevelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("minimumTrustLevel", m_minimumTrustLevel);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram