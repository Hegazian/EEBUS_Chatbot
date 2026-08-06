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

#include <keo_datagram/core/NetworkManagementFeatureDescriptionListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementFeatureDescriptionListData::
    NetworkManagementFeatureDescriptionListData()
    : CmdData(), m_networkManagementFeatureDescriptionDataIsSet(false),
      m_networkManagementFeatureDescriptionData(
          std::vector<NetworkManagementFeatureDescriptionData>())

{}

NetworkManagementFeatureDescriptionListData::
    NetworkManagementFeatureDescriptionListData(
        const std::vector<NetworkManagementFeatureDescriptionData>
            &c_networkManagementFeatureDescriptionData) {
  setNetworkManagementFeatureDescriptionData(
      c_networkManagementFeatureDescriptionData);
}

bool NetworkManagementFeatureDescriptionListData::operator==(
    const NetworkManagementFeatureDescriptionListData &c_classObject) const {
  if (m_networkManagementFeatureDescriptionDataIsSet !=
          c_classObject.m_networkManagementFeatureDescriptionDataIsSet ||
      (m_networkManagementFeatureDescriptionDataIsSet &&
       (m_networkManagementFeatureDescriptionData !=
        c_classObject.m_networkManagementFeatureDescriptionData))) {
    return false;
  }

  return true;
}

bool NetworkManagementFeatureDescriptionListData::operator!=(
    const NetworkManagementFeatureDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementFeatureDescriptionListData::isEmpty() const {
  return !m_networkManagementFeatureDescriptionDataIsSet;
}

CmdData::Type NetworkManagementFeatureDescriptionListData::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr NetworkManagementFeatureDescriptionListData::clone() const {
  return std::make_shared<NetworkManagementFeatureDescriptionListData>(*this);
}

void NetworkManagementFeatureDescriptionListData::
    setNetworkManagementFeatureDescriptionData(
        const std::vector<NetworkManagementFeatureDescriptionData>
            &networkManagementFeatureDescriptionData) {
  m_networkManagementFeatureDescriptionData =
      networkManagementFeatureDescriptionData;
  m_networkManagementFeatureDescriptionDataIsSet = true;
}

const std::vector<NetworkManagementFeatureDescriptionData> &
NetworkManagementFeatureDescriptionListData::
    getNetworkManagementFeatureDescriptionData() const {
  return m_networkManagementFeatureDescriptionData;
}

void NetworkManagementFeatureDescriptionListData::
    cleanNetworkManagementFeatureDescriptionData() {
  m_networkManagementFeatureDescriptionData.clear();
  m_networkManagementFeatureDescriptionDataIsSet = false;
}

bool NetworkManagementFeatureDescriptionListData::
    getNetworkManagementFeatureDescriptionDataIsSet() const {
  return m_networkManagementFeatureDescriptionDataIsSet;
}

CmdDataPtr NetworkManagementFeatureDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementFeatureDescriptionListData>(*this);
}

bool NetworkManagementFeatureDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"networkManagementFeatureDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<NetworkManagementFeatureDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "networkManagementFeatureDescriptionData",
            &m_networkManagementFeatureDescriptionData)) {
      m_networkManagementFeatureDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementFeatureDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_networkManagementFeatureDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        NetworkManagementFeatureDescriptionData>(
        "networkManagementFeatureDescriptionData",
        m_networkManagementFeatureDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram