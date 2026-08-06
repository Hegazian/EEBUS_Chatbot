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

#include <keo_datagram/core/NodeManagementDetailedDiscoveryEntityInformation.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDetailedDiscoveryEntityInformation::
    NodeManagementDetailedDiscoveryEntityInformation()
    : m_descriptionIsSet(false),
      m_description(NetworkManagementEntityDescriptionData())

{}

NodeManagementDetailedDiscoveryEntityInformation::
    NodeManagementDetailedDiscoveryEntityInformation(
        const NetworkManagementEntityDescriptionData &c_description) {
  setDescription(c_description);
}

bool NodeManagementDetailedDiscoveryEntityInformation::operator==(
    const NodeManagementDetailedDiscoveryEntityInformation &c_classObject)
    const {
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool NodeManagementDetailedDiscoveryEntityInformation::operator!=(
    const NodeManagementDetailedDiscoveryEntityInformation &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool NodeManagementDetailedDiscoveryEntityInformation::isEmpty() const {
  return !m_descriptionIsSet;
}

void NodeManagementDetailedDiscoveryEntityInformation::setDescription(
    const NetworkManagementEntityDescriptionData &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const NetworkManagementEntityDescriptionData &
NodeManagementDetailedDiscoveryEntityInformation::getDescription() const {
  return m_description;
}

void NodeManagementDetailedDiscoveryEntityInformation::cleanDescription() {
  m_description = NetworkManagementEntityDescriptionData();
  m_descriptionIsSet = false;
}

bool NodeManagementDetailedDiscoveryEntityInformation::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool NodeManagementDetailedDiscoveryEntityInformation::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementDetailedDiscoveryEntityInformation::toJson() const {
  std::string result = "[";
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram