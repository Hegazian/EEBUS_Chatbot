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

#include <keo_datagram/core/NetworkManagementEntityDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementEntityDescriptionListDataSelectors::
    NetworkManagementEntityDescriptionListDataSelectors()
    : DataSelectors(), m_entityAddressIsSet(false),
      m_entityAddress(EntityAddress()), m_entityTypeIsSet(false),
      m_entityType(EntityType())

{}

NetworkManagementEntityDescriptionListDataSelectors::
    NetworkManagementEntityDescriptionListDataSelectors(
        const EntityAddress &c_entityAddress, const EntityType &c_entityType)
    : DataSelectors(), m_entityAddressIsSet(true),
      m_entityAddress(c_entityAddress), m_entityTypeIsSet(true),
      m_entityType(c_entityType)

{}

bool NetworkManagementEntityDescriptionListDataSelectors::operator==(
    const NetworkManagementEntityDescriptionListDataSelectors &c_classObject)
    const {
  if (m_entityAddressIsSet != c_classObject.m_entityAddressIsSet ||
      (m_entityAddressIsSet &&
       (m_entityAddress != c_classObject.m_entityAddress))) {
    return false;
  }
  if (m_entityTypeIsSet != c_classObject.m_entityTypeIsSet ||
      (m_entityTypeIsSet && (m_entityType != c_classObject.m_entityType))) {
    return false;
  }

  return true;
}

bool NetworkManagementEntityDescriptionListDataSelectors::operator!=(
    const NetworkManagementEntityDescriptionListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool NetworkManagementEntityDescriptionListDataSelectors::isEmpty() const {
  return !m_entityAddressIsSet && !m_entityTypeIsSet;
}

DataSelectors::Type
NetworkManagementEntityDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
NetworkManagementEntityDescriptionListDataSelectors::clone() const {
  return std::make_shared<NetworkManagementEntityDescriptionListDataSelectors>(
      *this);
}

void NetworkManagementEntityDescriptionListDataSelectors::setEntityAddress(
    const EntityAddress &entityAddress) {
  m_entityAddress = entityAddress;
  m_entityAddressIsSet = true;
}

const EntityAddress &
NetworkManagementEntityDescriptionListDataSelectors::getEntityAddress() const {
  return m_entityAddress;
}

void NetworkManagementEntityDescriptionListDataSelectors::cleanEntityAddress() {
  m_entityAddress = EntityAddress();
  m_entityAddressIsSet = false;
}

bool NetworkManagementEntityDescriptionListDataSelectors::
    getEntityAddressIsSet() const {
  return m_entityAddressIsSet;
}

void NetworkManagementEntityDescriptionListDataSelectors::setEntityType(
    const EntityType &entityType) {
  m_entityType = entityType;
  m_entityTypeIsSet = true;
}

const EntityType &
NetworkManagementEntityDescriptionListDataSelectors::getEntityType() const {
  return m_entityType;
}

void NetworkManagementEntityDescriptionListDataSelectors::cleanEntityType() {
  m_entityType = EntityType();
  m_entityTypeIsSet = false;
}

bool NetworkManagementEntityDescriptionListDataSelectors::getEntityTypeIsSet()
    const {
  return m_entityTypeIsSet;
}

bool NetworkManagementEntityDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"entityAddress", "entityType"})) {
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
  }
  return true;
}

std::string
NetworkManagementEntityDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_entityAddressIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("entityAddress", m_entityAddress);
  }
  if (m_entityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("entityType", m_entityType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram