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

#include <keo_datagram/core/NodeManagementDestinationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDestinationListDataSelectors::
    NodeManagementDestinationListDataSelectors()
    : DataSelectors(), m_deviceDescriptionIsSet(false),
      m_deviceDescription(NetworkManagementDeviceDescriptionListDataSelectors())

{}

NodeManagementDestinationListDataSelectors::
    NodeManagementDestinationListDataSelectors(
        const NetworkManagementDeviceDescriptionListDataSelectors
            &c_deviceDescription) {
  setDeviceDescription(c_deviceDescription);
}

bool NodeManagementDestinationListDataSelectors::operator==(
    const NodeManagementDestinationListDataSelectors &c_classObject) const {
  if (m_deviceDescriptionIsSet != c_classObject.m_deviceDescriptionIsSet ||
      (m_deviceDescriptionIsSet &&
       (m_deviceDescription != c_classObject.m_deviceDescription))) {
    return false;
  }

  return true;
}

bool NodeManagementDestinationListDataSelectors::operator!=(
    const NodeManagementDestinationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementDestinationListDataSelectors::isEmpty() const {
  return !m_deviceDescriptionIsSet;
}

DataSelectors::Type
NodeManagementDestinationListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      NODE_MANAGEMENT_DESTINATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr NodeManagementDestinationListDataSelectors::clone() const {
  return std::make_shared<NodeManagementDestinationListDataSelectors>(*this);
}

void NodeManagementDestinationListDataSelectors::setDeviceDescription(
    const NetworkManagementDeviceDescriptionListDataSelectors
        &deviceDescription) {
  m_deviceDescription = deviceDescription;
  m_deviceDescriptionIsSet = true;
}

const NetworkManagementDeviceDescriptionListDataSelectors &
NodeManagementDestinationListDataSelectors::getDeviceDescription() const {
  return m_deviceDescription;
}

void NodeManagementDestinationListDataSelectors::cleanDeviceDescription() {
  m_deviceDescription = NetworkManagementDeviceDescriptionListDataSelectors();
  m_deviceDescriptionIsSet = false;
}

bool NodeManagementDestinationListDataSelectors::getDeviceDescriptionIsSet()
    const {
  return m_deviceDescriptionIsSet;
}

bool NodeManagementDestinationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"deviceDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "deviceDescription", &m_deviceDescription)) {
      m_deviceDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementDestinationListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_deviceDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("deviceDescription", m_deviceDescription);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram