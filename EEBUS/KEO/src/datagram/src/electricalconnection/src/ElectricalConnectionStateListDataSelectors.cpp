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

#include <keo_datagram/electricalconnection/ElectricalConnectionStateListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionStateListDataSelectors::
    ElectricalConnectionStateListDataSelectors()
    : DataSelectors(), m_electricalConnectionIdIsSet(false),
      m_electricalConnectionId(0)

{}

ElectricalConnectionStateListDataSelectors::
    ElectricalConnectionStateListDataSelectors(
        const xs_unsignedInt &c_electricalConnectionId) {
  setElectricalConnectionId(c_electricalConnectionId);
}

bool ElectricalConnectionStateListDataSelectors::operator==(
    const ElectricalConnectionStateListDataSelectors &c_classObject) const {
  if (m_electricalConnectionIdIsSet !=
          c_classObject.m_electricalConnectionIdIsSet ||
      (m_electricalConnectionIdIsSet &&
       (m_electricalConnectionId != c_classObject.m_electricalConnectionId))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionStateListDataSelectors::operator!=(
    const ElectricalConnectionStateListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionStateListDataSelectors::isEmpty() const {
  return !m_electricalConnectionIdIsSet;
}

DataSelectors::Type
ElectricalConnectionStateListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      ELECTRICAL_CONNECTION_STATE_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr ElectricalConnectionStateListDataSelectors::clone() const {
  return std::make_shared<ElectricalConnectionStateListDataSelectors>(*this);
}

void ElectricalConnectionStateListDataSelectors::setElectricalConnectionId(
    const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionStateListDataSelectors::getElectricalConnectionId() const {
  return m_electricalConnectionId;
}

void ElectricalConnectionStateListDataSelectors::cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionStateListDataSelectors::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

bool ElectricalConnectionStateListDataSelectors::selects(
    const ElectricalConnectionStateData &data) const {
  if (getElectricalConnectionIdIsSet() &&
      (!data.getElectricalConnectionIdIsSet() ||
       getElectricalConnectionId() != data.getElectricalConnectionId())) {
    return false;
  }
  return true;
}

bool ElectricalConnectionStateListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"electricalConnectionId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "electricalConnectionId",
                                   &m_electricalConnectionId)) {
      m_electricalConnectionIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionStateListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("electricalConnectionId",
                                           m_electricalConnectionId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram