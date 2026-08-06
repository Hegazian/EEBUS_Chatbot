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

#include <keo_datagram/core/NetworkManagementJoiningModeDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementJoiningModeDataElements::
    NetworkManagementJoiningModeDataElements()
    : DataElements(), m_setupIsSet(false)

{}

NetworkManagementJoiningModeDataElements::
    NetworkManagementJoiningModeDataElements(const xs_boolean &c_setupIsSet) {
  if (c_setupIsSet) {
    setSetup();
  }
}

bool NetworkManagementJoiningModeDataElements::operator==(
    const NetworkManagementJoiningModeDataElements &c_classObject) const {
  if (m_setupIsSet != c_classObject.m_setupIsSet) {
    return false;
  }

  return true;
}

bool NetworkManagementJoiningModeDataElements::operator!=(
    const NetworkManagementJoiningModeDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementJoiningModeDataElements::isEmpty() const {
  return !m_setupIsSet;
}

DataElements::Type
NetworkManagementJoiningModeDataElements::getDataType() const {
  return DataElements::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementJoiningModeDataElements::clone() const {
  return std::make_shared<NetworkManagementJoiningModeDataElements>(*this);
}

void NetworkManagementJoiningModeDataElements::setSetup() {
  m_setupIsSet = true;
}

void NetworkManagementJoiningModeDataElements::cleanSetup() {
  m_setupIsSet = false;
}

bool NetworkManagementJoiningModeDataElements::getSetupIsSet() const {
  return m_setupIsSet;
}

bool NetworkManagementJoiningModeDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"setup"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "setup")) {
      m_setupIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementJoiningModeDataElements::toJson() const {
  std::string result = "[";
  if (m_setupIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("setup");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram