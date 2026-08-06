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

#include <keo_datagram/core/NetworkManagementJoiningModeData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementJoiningModeData::NetworkManagementJoiningModeData()
    : CmdData(), m_setupIsSet(false), m_setup("")

{}

NetworkManagementJoiningModeData::NetworkManagementJoiningModeData(
    const xs_string &c_setup) {
  setSetup(c_setup);
}

bool NetworkManagementJoiningModeData::
operator==(const NetworkManagementJoiningModeData &c_classObject) const {
  if (m_setupIsSet != c_classObject.m_setupIsSet ||
      (m_setupIsSet && (m_setup != c_classObject.m_setup))) {
    return false;
  }

  return true;
}

bool NetworkManagementJoiningModeData::
operator!=(const NetworkManagementJoiningModeData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementJoiningModeData::isEmpty() const { return !m_setupIsSet; }

CmdData::Type NetworkManagementJoiningModeData::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE;
}

CmdDataPtr NetworkManagementJoiningModeData::clone() const {
  return std::make_shared<NetworkManagementJoiningModeData>(*this);
}

void NetworkManagementJoiningModeData::setSetup(const xs_string &setup) {
  m_setup = setup;
  m_setupIsSet = true;
}

const xs_string &NetworkManagementJoiningModeData::getSetup() const {
  return m_setup;
}

void NetworkManagementJoiningModeData::cleanSetup() {
  m_setup = "";
  m_setupIsSet = false;
}

bool NetworkManagementJoiningModeData::getSetupIsSet() const {
  return m_setupIsSet;
}

CmdDataPtr NetworkManagementJoiningModeData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementJoiningModeData>(*this);
}

bool NetworkManagementJoiningModeData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"setup"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "setup", &m_setup)) {
      m_setupIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementJoiningModeData::toJson() const {
  std::string result = "[";
  if (m_setupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("setup", m_setup);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram