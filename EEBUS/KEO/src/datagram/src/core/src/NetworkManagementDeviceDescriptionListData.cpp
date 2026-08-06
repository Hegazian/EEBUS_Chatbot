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

#include <keo_datagram/core/NetworkManagementDeviceDescriptionListData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementDeviceDescriptionListData::
    NetworkManagementDeviceDescriptionListData()
    : CmdData(), m_networkManagementDeviceDescriptionDataIsSet(false),
      m_networkManagementDeviceDescriptionData(
          std::vector<NetworkManagementDeviceDescriptionData>())

{}

NetworkManagementDeviceDescriptionListData::
    NetworkManagementDeviceDescriptionListData(
        const std::vector<NetworkManagementDeviceDescriptionData>
            &c_networkManagementDeviceDescriptionData) {
  setNetworkManagementDeviceDescriptionData(
      c_networkManagementDeviceDescriptionData);
}

bool NetworkManagementDeviceDescriptionListData::operator==(
    const NetworkManagementDeviceDescriptionListData &c_classObject) const {
  if (m_networkManagementDeviceDescriptionDataIsSet !=
          c_classObject.m_networkManagementDeviceDescriptionDataIsSet ||
      (m_networkManagementDeviceDescriptionDataIsSet &&
       (m_networkManagementDeviceDescriptionData !=
        c_classObject.m_networkManagementDeviceDescriptionData))) {
    return false;
  }

  return true;
}

bool NetworkManagementDeviceDescriptionListData::operator!=(
    const NetworkManagementDeviceDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementDeviceDescriptionListData::isEmpty() const {
  return !m_networkManagementDeviceDescriptionDataIsSet;
}

CmdData::Type NetworkManagementDeviceDescriptionListData::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr NetworkManagementDeviceDescriptionListData::clone() const {
  return std::make_shared<NetworkManagementDeviceDescriptionListData>(*this);
}

void NetworkManagementDeviceDescriptionListData::
    setNetworkManagementDeviceDescriptionData(
        const std::vector<NetworkManagementDeviceDescriptionData>
            &networkManagementDeviceDescriptionData) {
  m_networkManagementDeviceDescriptionData =
      networkManagementDeviceDescriptionData;
  m_networkManagementDeviceDescriptionDataIsSet = true;
}

const std::vector<NetworkManagementDeviceDescriptionData> &
NetworkManagementDeviceDescriptionListData::
    getNetworkManagementDeviceDescriptionData() const {
  return m_networkManagementDeviceDescriptionData;
}

void NetworkManagementDeviceDescriptionListData::
    cleanNetworkManagementDeviceDescriptionData() {
  m_networkManagementDeviceDescriptionData.clear();
  m_networkManagementDeviceDescriptionDataIsSet = false;
}

bool NetworkManagementDeviceDescriptionListData::
    getNetworkManagementDeviceDescriptionDataIsSet() const {
  return m_networkManagementDeviceDescriptionDataIsSet;
}

CmdDataPtr NetworkManagementDeviceDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementDeviceDescriptionListData>(*this);
}

bool NetworkManagementDeviceDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"networkManagementDeviceDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<NetworkManagementDeviceDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "networkManagementDeviceDescriptionData",
            &m_networkManagementDeviceDescriptionData)) {
      m_networkManagementDeviceDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementDeviceDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_networkManagementDeviceDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        NetworkManagementDeviceDescriptionData>(
        "networkManagementDeviceDescriptionData",
        m_networkManagementDeviceDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram