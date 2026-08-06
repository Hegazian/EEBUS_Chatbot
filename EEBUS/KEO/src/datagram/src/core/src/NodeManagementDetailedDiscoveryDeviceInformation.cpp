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

#include <keo_datagram/core/NodeManagementDetailedDiscoveryDeviceInformation.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDetailedDiscoveryDeviceInformation::
    NodeManagementDetailedDiscoveryDeviceInformation()
    : m_descriptionIsSet(false),
      m_description(NetworkManagementDeviceDescriptionData())

{}

NodeManagementDetailedDiscoveryDeviceInformation::
    NodeManagementDetailedDiscoveryDeviceInformation(
        const NetworkManagementDeviceDescriptionData &c_description) {
  setDescription(c_description);
}

bool NodeManagementDetailedDiscoveryDeviceInformation::operator==(
    const NodeManagementDetailedDiscoveryDeviceInformation &c_classObject)
    const {
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool NodeManagementDetailedDiscoveryDeviceInformation::operator!=(
    const NodeManagementDetailedDiscoveryDeviceInformation &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool NodeManagementDetailedDiscoveryDeviceInformation::isEmpty() const {
  return !m_descriptionIsSet;
}

void NodeManagementDetailedDiscoveryDeviceInformation::setDescription(
    const NetworkManagementDeviceDescriptionData &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const NetworkManagementDeviceDescriptionData &
NodeManagementDetailedDiscoveryDeviceInformation::getDescription() const {
  return m_description;
}

void NodeManagementDetailedDiscoveryDeviceInformation::cleanDescription() {
  m_description = NetworkManagementDeviceDescriptionData();
  m_descriptionIsSet = false;
}

bool NodeManagementDetailedDiscoveryDeviceInformation::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool NodeManagementDetailedDiscoveryDeviceInformation::fromJson(
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

std::string NodeManagementDetailedDiscoveryDeviceInformation::toJson() const {
  std::string result = "[";
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram