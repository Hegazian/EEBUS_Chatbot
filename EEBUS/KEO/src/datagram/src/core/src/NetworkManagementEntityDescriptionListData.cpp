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

#include <keo_datagram/core/NetworkManagementEntityDescriptionListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementEntityDescriptionListData::
    NetworkManagementEntityDescriptionListData()
    : CmdData(), m_networkManagementEntityDescriptionDataIsSet(false),
      m_networkManagementEntityDescriptionData(
          std::vector<NetworkManagementEntityDescriptionData>())

{}

NetworkManagementEntityDescriptionListData::
    NetworkManagementEntityDescriptionListData(
        const std::vector<NetworkManagementEntityDescriptionData>
            &c_networkManagementEntityDescriptionData) {
  setNetworkManagementEntityDescriptionData(
      c_networkManagementEntityDescriptionData);
}

bool NetworkManagementEntityDescriptionListData::operator==(
    const NetworkManagementEntityDescriptionListData &c_classObject) const {
  if (m_networkManagementEntityDescriptionDataIsSet !=
          c_classObject.m_networkManagementEntityDescriptionDataIsSet ||
      (m_networkManagementEntityDescriptionDataIsSet &&
       (m_networkManagementEntityDescriptionData !=
        c_classObject.m_networkManagementEntityDescriptionData))) {
    return false;
  }

  return true;
}

bool NetworkManagementEntityDescriptionListData::operator!=(
    const NetworkManagementEntityDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementEntityDescriptionListData::isEmpty() const {
  return !m_networkManagementEntityDescriptionDataIsSet;
}

CmdData::Type NetworkManagementEntityDescriptionListData::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr NetworkManagementEntityDescriptionListData::clone() const {
  return std::make_shared<NetworkManagementEntityDescriptionListData>(*this);
}

void NetworkManagementEntityDescriptionListData::
    setNetworkManagementEntityDescriptionData(
        const std::vector<NetworkManagementEntityDescriptionData>
            &networkManagementEntityDescriptionData) {
  m_networkManagementEntityDescriptionData =
      networkManagementEntityDescriptionData;
  m_networkManagementEntityDescriptionDataIsSet = true;
}

const std::vector<NetworkManagementEntityDescriptionData> &
NetworkManagementEntityDescriptionListData::
    getNetworkManagementEntityDescriptionData() const {
  return m_networkManagementEntityDescriptionData;
}

void NetworkManagementEntityDescriptionListData::
    cleanNetworkManagementEntityDescriptionData() {
  m_networkManagementEntityDescriptionData.clear();
  m_networkManagementEntityDescriptionDataIsSet = false;
}

bool NetworkManagementEntityDescriptionListData::
    getNetworkManagementEntityDescriptionDataIsSet() const {
  return m_networkManagementEntityDescriptionDataIsSet;
}

CmdDataPtr NetworkManagementEntityDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementEntityDescriptionListData>(*this);
}

bool NetworkManagementEntityDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"networkManagementEntityDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<NetworkManagementEntityDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "networkManagementEntityDescriptionData",
            &m_networkManagementEntityDescriptionData)) {
      m_networkManagementEntityDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementEntityDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_networkManagementEntityDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        NetworkManagementEntityDescriptionData>(
        "networkManagementEntityDescriptionData",
        m_networkManagementEntityDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram