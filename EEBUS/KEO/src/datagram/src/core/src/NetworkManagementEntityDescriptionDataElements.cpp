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

#include <keo_datagram/core/NetworkManagementEntityDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementEntityDescriptionDataElements::
    NetworkManagementEntityDescriptionDataElements()
    : DataElements(), m_entityAddressIsSet(false),
      m_entityAddress(EntityAddressElements()), m_entityTypeIsSet(false),
      m_lastStateChangeIsSet(false), m_minimumTrustLevelIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool NetworkManagementEntityDescriptionDataElements::operator==(
    const NetworkManagementEntityDescriptionDataElements &c_classObject) const {
  if (m_entityAddressIsSet != c_classObject.m_entityAddressIsSet ||
      (m_entityAddressIsSet &&
       (m_entityAddress != c_classObject.m_entityAddress))) {
    return false;
  }
  if (m_entityTypeIsSet != c_classObject.m_entityTypeIsSet) {
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

bool NetworkManagementEntityDescriptionDataElements::operator!=(
    const NetworkManagementEntityDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementEntityDescriptionDataElements::isEmpty() const {
  return !m_entityAddressIsSet && !m_entityTypeIsSet &&
         !m_lastStateChangeIsSet && !m_minimumTrustLevelIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
NetworkManagementEntityDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementEntityDescriptionDataElements::clone() const {
  return std::make_shared<NetworkManagementEntityDescriptionDataElements>(
      *this);
}

void NetworkManagementEntityDescriptionDataElements::setEntityAddress(
    const EntityAddressElements &entityAddress) {
  m_entityAddress = entityAddress;
  m_entityAddressIsSet = true;
}

const EntityAddressElements &
NetworkManagementEntityDescriptionDataElements::getEntityAddress() const {
  return m_entityAddress;
}

void NetworkManagementEntityDescriptionDataElements::cleanEntityAddress() {
  m_entityAddress = EntityAddressElements();
  m_entityAddressIsSet = false;
}

bool NetworkManagementEntityDescriptionDataElements::getEntityAddressIsSet()
    const {
  return m_entityAddressIsSet;
}

void NetworkManagementEntityDescriptionDataElements::setEntityType() {
  m_entityTypeIsSet = true;
}

void NetworkManagementEntityDescriptionDataElements::cleanEntityType() {
  m_entityTypeIsSet = false;
}

bool NetworkManagementEntityDescriptionDataElements::getEntityTypeIsSet()
    const {
  return m_entityTypeIsSet;
}

void NetworkManagementEntityDescriptionDataElements::setLastStateChange() {
  m_lastStateChangeIsSet = true;
}

void NetworkManagementEntityDescriptionDataElements::cleanLastStateChange() {
  m_lastStateChangeIsSet = false;
}

bool NetworkManagementEntityDescriptionDataElements::getLastStateChangeIsSet()
    const {
  return m_lastStateChangeIsSet;
}

void NetworkManagementEntityDescriptionDataElements::setMinimumTrustLevel() {
  m_minimumTrustLevelIsSet = true;
}

void NetworkManagementEntityDescriptionDataElements::cleanMinimumTrustLevel() {
  m_minimumTrustLevelIsSet = false;
}

bool NetworkManagementEntityDescriptionDataElements::getMinimumTrustLevelIsSet()
    const {
  return m_minimumTrustLevelIsSet;
}

void NetworkManagementEntityDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void NetworkManagementEntityDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool NetworkManagementEntityDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void NetworkManagementEntityDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void NetworkManagementEntityDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool NetworkManagementEntityDescriptionDataElements::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool NetworkManagementEntityDescriptionDataElements::fromJson(
    KeoJsonValue *json) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "entityType")) {
      m_entityTypeIsSet = true;
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

std::string NetworkManagementEntityDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_entityAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("entityAddress", m_entityAddress);
  }
  if (m_entityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("entityType");
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