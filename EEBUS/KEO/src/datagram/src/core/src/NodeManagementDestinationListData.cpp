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

#include <keo_datagram/core/NodeManagementDestinationListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NodeManagementDestinationListData::NodeManagementDestinationListData()
    : CmdData(), m_nodeManagementDestinationDataIsSet(false),
      m_nodeManagementDestinationData(
          std::vector<NodeManagementDestinationData>())

{}

NodeManagementDestinationListData::NodeManagementDestinationListData(
    const std::vector<NodeManagementDestinationData>
        &c_nodeManagementDestinationData) {
  setNodeManagementDestinationData(c_nodeManagementDestinationData);
}

bool NodeManagementDestinationListData::
operator==(const NodeManagementDestinationListData &c_classObject) const {
  if (m_nodeManagementDestinationDataIsSet !=
          c_classObject.m_nodeManagementDestinationDataIsSet ||
      (m_nodeManagementDestinationDataIsSet &&
       (m_nodeManagementDestinationData !=
        c_classObject.m_nodeManagementDestinationData))) {
    return false;
  }

  return true;
}

bool NodeManagementDestinationListData::
operator!=(const NodeManagementDestinationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NodeManagementDestinationListData::isEmpty() const {
  return !m_nodeManagementDestinationDataIsSet;
}

CmdData::Type NodeManagementDestinationListData::getDataType() const {
  return CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE;
}

CmdDataPtr NodeManagementDestinationListData::clone() const {
  return std::make_shared<NodeManagementDestinationListData>(*this);
}

void NodeManagementDestinationListData::setNodeManagementDestinationData(
    const std::vector<NodeManagementDestinationData>
        &nodeManagementDestinationData) {
  m_nodeManagementDestinationData = nodeManagementDestinationData;
  m_nodeManagementDestinationDataIsSet = true;
}

const std::vector<NodeManagementDestinationData> &
NodeManagementDestinationListData::getNodeManagementDestinationData() const {
  return m_nodeManagementDestinationData;
}

void NodeManagementDestinationListData::cleanNodeManagementDestinationData() {
  m_nodeManagementDestinationData.clear();
  m_nodeManagementDestinationDataIsSet = false;
}

bool NodeManagementDestinationListData::getNodeManagementDestinationDataIsSet()
    const {
  return m_nodeManagementDestinationDataIsSet;
}

CmdDataPtr NodeManagementDestinationListData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NodeManagementDestinationListData>(*this);
}

bool NodeManagementDestinationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"nodeManagementDestinationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<NodeManagementDestinationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "nodeManagementDestinationData",
            &m_nodeManagementDestinationData)) {
      m_nodeManagementDestinationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NodeManagementDestinationListData::toJson() const {
  std::string result = "[";
  if (m_nodeManagementDestinationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<NodeManagementDestinationData>(
        "nodeManagementDestinationData", m_nodeManagementDestinationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram