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

#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionDescriptionListDataSelectors::
    ElectricalConnectionDescriptionListDataSelectors()
    : DataSelectors(), m_electricalConnectionIdIsSet(false),
      m_electricalConnectionId(0), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType())

{}

ElectricalConnectionDescriptionListDataSelectors::
    ElectricalConnectionDescriptionListDataSelectors(
        const xs_unsignedInt &c_electricalConnectionId,
        const ScopeType &c_scopeType)
    : DataSelectors(), m_electricalConnectionIdIsSet(true),
      m_electricalConnectionId(c_electricalConnectionId),
      m_scopeTypeIsSet(true), m_scopeType(c_scopeType)

{}

bool ElectricalConnectionDescriptionListDataSelectors::operator==(
    const ElectricalConnectionDescriptionListDataSelectors &c_classObject)
    const {
  if (m_electricalConnectionIdIsSet !=
          c_classObject.m_electricalConnectionIdIsSet ||
      (m_electricalConnectionIdIsSet &&
       (m_electricalConnectionId != c_classObject.m_electricalConnectionId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionDescriptionListDataSelectors::operator!=(
    const ElectricalConnectionDescriptionListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionDescriptionListDataSelectors::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type
ElectricalConnectionDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
ElectricalConnectionDescriptionListDataSelectors::clone() const {
  return std::make_shared<ElectricalConnectionDescriptionListDataSelectors>(
      *this);
}

void ElectricalConnectionDescriptionListDataSelectors::
    setElectricalConnectionId(const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionDescriptionListDataSelectors::getElectricalConnectionId()
    const {
  return m_electricalConnectionId;
}

void ElectricalConnectionDescriptionListDataSelectors::
    cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionDescriptionListDataSelectors::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &
ElectricalConnectionDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void ElectricalConnectionDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool ElectricalConnectionDescriptionListDataSelectors::getScopeTypeIsSet()
    const {
  return m_scopeTypeIsSet;
}

bool ElectricalConnectionDescriptionListDataSelectors::selects(
    const ElectricalConnectionDescriptionData &data) const {
  if (getElectricalConnectionIdIsSet() &&
      (!data.getElectricalConnectionIdIsSet() ||
       getElectricalConnectionId() != data.getElectricalConnectionId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool ElectricalConnectionDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionId", "scopeType"})) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("electricalConnectionId",
                                           m_electricalConnectionId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram