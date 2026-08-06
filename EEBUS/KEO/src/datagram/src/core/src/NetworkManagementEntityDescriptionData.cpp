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

#include <keo_datagram/core/NetworkManagementEntityDescriptionData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementEntityDescriptionData::NetworkManagementEntityDescriptionData()
    : m_entityAddressIsSet(false), m_entityAddress(EntityAddress()),
      m_entityTypeIsSet(false), m_entityType(EntityType()),
      m_lastStateChangeIsSet(false),
      m_lastStateChange(NetworkManagementStateChange()),
      m_minimumTrustLevelIsSet(false), m_minimumTrustLevel(""),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description("")

{}

bool NetworkManagementEntityDescriptionData::
operator==(const NetworkManagementEntityDescriptionData &c_classObject) const {
  if (m_entityAddressIsSet != c_classObject.m_entityAddressIsSet ||
      (m_entityAddressIsSet &&
       (m_entityAddress != c_classObject.m_entityAddress))) {
    return false;
  }
  if (m_entityTypeIsSet != c_classObject.m_entityTypeIsSet ||
      (m_entityTypeIsSet && (m_entityType != c_classObject.m_entityType))) {
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

bool NetworkManagementEntityDescriptionData::
operator!=(const NetworkManagementEntityDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementEntityDescriptionData::isEmpty() const {
  return !m_entityAddressIsSet && !m_entityTypeIsSet &&
         !m_lastStateChangeIsSet && !m_minimumTrustLevelIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void NetworkManagementEntityDescriptionData::setEntityAddress(
    const EntityAddress &entityAddress) {
  m_entityAddress = entityAddress;
  m_entityAddressIsSet = true;
}

const EntityAddress &
NetworkManagementEntityDescriptionData::getEntityAddress() const {
  return m_entityAddress;
}

void NetworkManagementEntityDescriptionData::cleanEntityAddress() {
  m_entityAddress = EntityAddress();
  m_entityAddressIsSet = false;
}

bool NetworkManagementEntityDescriptionData::getEntityAddressIsSet() const {
  return m_entityAddressIsSet;
}

void NetworkManagementEntityDescriptionData::setEntityType(
    const EntityType &entityType) {
  m_entityType = entityType;
  m_entityTypeIsSet = true;
}

const EntityType &
NetworkManagementEntityDescriptionData::getEntityType() const {
  return m_entityType;
}

void NetworkManagementEntityDescriptionData::cleanEntityType() {
  m_entityType = EntityType();
  m_entityTypeIsSet = false;
}

bool NetworkManagementEntityDescriptionData::getEntityTypeIsSet() const {
  return m_entityTypeIsSet;
}

void NetworkManagementEntityDescriptionData::setLastStateChange(
    const NetworkManagementStateChange &lastStateChange) {
  m_lastStateChange = lastStateChange;
  m_lastStateChangeIsSet = true;
}

const NetworkManagementStateChange &
NetworkManagementEntityDescriptionData::getLastStateChange() const {
  return m_lastStateChange;
}

void NetworkManagementEntityDescriptionData::cleanLastStateChange() {
  m_lastStateChange = NetworkManagementStateChange();
  m_lastStateChangeIsSet = false;
}

bool NetworkManagementEntityDescriptionData::getLastStateChangeIsSet() const {
  return m_lastStateChangeIsSet;
}

void NetworkManagementEntityDescriptionData::setMinimumTrustLevel(
    const xs_string &minimumTrustLevel) {
  m_minimumTrustLevel = minimumTrustLevel;
  m_minimumTrustLevelIsSet = true;
}

const xs_string &
NetworkManagementEntityDescriptionData::getMinimumTrustLevel() const {
  return m_minimumTrustLevel;
}

void NetworkManagementEntityDescriptionData::cleanMinimumTrustLevel() {
  m_minimumTrustLevel = "";
  m_minimumTrustLevelIsSet = false;
}

bool NetworkManagementEntityDescriptionData::getMinimumTrustLevelIsSet() const {
  return m_minimumTrustLevelIsSet;
}

void NetworkManagementEntityDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &NetworkManagementEntityDescriptionData::getLabel() const {
  return m_label;
}

void NetworkManagementEntityDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool NetworkManagementEntityDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementEntityDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &
NetworkManagementEntityDescriptionData::getDescription() const {
  return m_description;
}

void NetworkManagementEntityDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementEntityDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool NetworkManagementEntityDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"entityAddress", "entityType", "lastStateChange",
                   "minimumTrustLevel", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "entityAddress", &m_entityAddress)) {
      m_entityAddressIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "entityType", &m_entityType)) {
      m_entityTypeIsSet = true;
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

std::string NetworkManagementEntityDescriptionData::toJson() const {
  std::string result = "[";
  if (m_entityAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("entityAddress", m_entityAddress);
  }
  if (m_entityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("entityType", m_entityType);
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