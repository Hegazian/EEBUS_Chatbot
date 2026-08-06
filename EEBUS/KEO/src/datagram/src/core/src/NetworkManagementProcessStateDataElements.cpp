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

#include <keo_datagram/core/NetworkManagementProcessStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

NetworkManagementProcessStateDataElements::
    NetworkManagementProcessStateDataElements()
    : DataElements(), m_stateIsSet(false), m_descriptionIsSet(false)

{}

NetworkManagementProcessStateDataElements::
    NetworkManagementProcessStateDataElements(xs_boolean c_stateIsSet,
                                              xs_boolean c_descriptionIsSet)
    : DataElements(), m_stateIsSet(c_stateIsSet),
      m_descriptionIsSet(c_descriptionIsSet)

{}

bool NetworkManagementProcessStateDataElements::operator==(
    const NetworkManagementProcessStateDataElements &c_classObject) const {
  if (m_stateIsSet != c_classObject.m_stateIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool NetworkManagementProcessStateDataElements::operator!=(
    const NetworkManagementProcessStateDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool NetworkManagementProcessStateDataElements::isEmpty() const {
  return !m_stateIsSet && !m_descriptionIsSet;
}

DataElements::Type
NetworkManagementProcessStateDataElements::getDataType() const {
  return DataElements::Type::
      NETWORK_MANAGEMENT_PROCESS_STATE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr NetworkManagementProcessStateDataElements::clone() const {
  return std::make_shared<NetworkManagementProcessStateDataElements>(*this);
}

void NetworkManagementProcessStateDataElements::setState() {
  m_stateIsSet = true;
}

void NetworkManagementProcessStateDataElements::cleanState() {
  m_stateIsSet = false;
}

bool NetworkManagementProcessStateDataElements::getStateIsSet() const {
  return m_stateIsSet;
}

void NetworkManagementProcessStateDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void NetworkManagementProcessStateDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool NetworkManagementProcessStateDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool NetworkManagementProcessStateDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"state", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "state")) {
      m_stateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string NetworkManagementProcessStateDataElements::toJson() const {
  std::string result = "[";
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("state");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram