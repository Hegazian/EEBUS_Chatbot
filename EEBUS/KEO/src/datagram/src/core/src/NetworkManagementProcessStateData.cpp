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

#include <keo_datagram/core/NetworkManagementProcessStateData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementProcessStateData::NetworkManagementProcessStateData()
    : CmdData(), m_stateIsSet(false),
      m_state(NetworkManagementProcessStateState()), m_descriptionIsSet(false),
      m_description("")

{}

NetworkManagementProcessStateData::NetworkManagementProcessStateData(
    const NetworkManagementProcessStateState &c_state,
    const xs_string &c_description)
    : CmdData(), m_stateIsSet(true), m_state(c_state), m_descriptionIsSet(true),
      m_description(c_description)

{}

bool NetworkManagementProcessStateData::
operator==(const NetworkManagementProcessStateData &c_classObject) const {
  if (m_stateIsSet != c_classObject.m_stateIsSet ||
      (m_stateIsSet && (m_state != c_classObject.m_state))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool NetworkManagementProcessStateData::
operator!=(const NetworkManagementProcessStateData &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementProcessStateData::isEmpty() const {
  return !m_stateIsSet && !m_descriptionIsSet;
}

CmdData::Type NetworkManagementProcessStateData::getDataType() const {
  return CmdData::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE;
}

CmdDataPtr NetworkManagementProcessStateData::clone() const {
  return std::make_shared<NetworkManagementProcessStateData>(*this);
}

void NetworkManagementProcessStateData::setState(
    const NetworkManagementProcessStateState &state) {
  m_state = state;
  m_stateIsSet = true;
}

const NetworkManagementProcessStateState &
NetworkManagementProcessStateData::getState() const {
  return m_state;
}

void NetworkManagementProcessStateData::cleanState() {
  m_state = NetworkManagementProcessStateState();
  m_stateIsSet = false;
}

bool NetworkManagementProcessStateData::getStateIsSet() const {
  return m_stateIsSet;
}

void NetworkManagementProcessStateData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &NetworkManagementProcessStateData::getDescription() const {
  return m_description;
}

void NetworkManagementProcessStateData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool NetworkManagementProcessStateData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

CmdDataPtr NetworkManagementProcessStateData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<NetworkManagementProcessStateData>(*this);
}

bool NetworkManagementProcessStateData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"state", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "state", &m_state)) {
      m_stateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementProcessStateData::toJson() const {
  std::string result = "[";
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("state", m_state);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram