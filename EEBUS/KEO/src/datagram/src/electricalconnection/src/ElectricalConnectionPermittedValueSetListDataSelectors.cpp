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

#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionPermittedValueSetListDataSelectors::
    ElectricalConnectionPermittedValueSetListDataSelectors()
    : DataSelectors(), m_electricalConnectionIdIsSet(false),
      m_electricalConnectionId(0), m_parameterIdIsSet(false), m_parameterId(0)

{}

ElectricalConnectionPermittedValueSetListDataSelectors::
    ElectricalConnectionPermittedValueSetListDataSelectors(
        const xs_unsignedInt &c_electricalConnectionId,
        const xs_unsignedInt &c_parameterId)
    : DataSelectors(), m_electricalConnectionIdIsSet(true),
      m_electricalConnectionId(c_electricalConnectionId),
      m_parameterIdIsSet(true), m_parameterId(c_parameterId)

{}

bool ElectricalConnectionPermittedValueSetListDataSelectors::operator==(
    const ElectricalConnectionPermittedValueSetListDataSelectors &c_classObject)
    const {
  if (m_electricalConnectionIdIsSet !=
          c_classObject.m_electricalConnectionIdIsSet ||
      (m_electricalConnectionIdIsSet &&
       (m_electricalConnectionId != c_classObject.m_electricalConnectionId))) {
    return false;
  }
  if (m_parameterIdIsSet != c_classObject.m_parameterIdIsSet ||
      (m_parameterIdIsSet && (m_parameterId != c_classObject.m_parameterId))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionPermittedValueSetListDataSelectors::operator!=(
    const ElectricalConnectionPermittedValueSetListDataSelectors &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionPermittedValueSetListDataSelectors::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_parameterIdIsSet;
}

DataSelectors::Type
ElectricalConnectionPermittedValueSetListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
ElectricalConnectionPermittedValueSetListDataSelectors::clone() const {
  return std::make_shared<
      ElectricalConnectionPermittedValueSetListDataSelectors>(*this);
}

void ElectricalConnectionPermittedValueSetListDataSelectors::
    setElectricalConnectionId(const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &ElectricalConnectionPermittedValueSetListDataSelectors::
    getElectricalConnectionId() const {
  return m_electricalConnectionId;
}

void ElectricalConnectionPermittedValueSetListDataSelectors::
    cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionPermittedValueSetListDataSelectors::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionPermittedValueSetListDataSelectors::setParameterId(
    const xs_unsignedInt &parameterId) {
  m_parameterId = parameterId;
  m_parameterIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionPermittedValueSetListDataSelectors::getParameterId() const {
  return m_parameterId;
}

void ElectricalConnectionPermittedValueSetListDataSelectors::
    cleanParameterId() {
  m_parameterId = 0;
  m_parameterIdIsSet = false;
}

bool ElectricalConnectionPermittedValueSetListDataSelectors::
    getParameterIdIsSet() const {
  return m_parameterIdIsSet;
}

bool ElectricalConnectionPermittedValueSetListDataSelectors::selects(
    const ElectricalConnectionPermittedValueSetData &data) const {
  if (getElectricalConnectionIdIsSet() &&
      (!data.getElectricalConnectionIdIsSet() ||
       getElectricalConnectionId() != data.getElectricalConnectionId())) {
    return false;
  }
  if (getParameterIdIsSet() && (!data.getParameterIdIsSet() ||
                                getParameterId() != data.getParameterId())) {
    return false;
  }
  return true;
}

bool ElectricalConnectionPermittedValueSetListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionId", "parameterId"})) {
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
                                   "parameterId", &m_parameterId)) {
      m_parameterIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string
ElectricalConnectionPermittedValueSetListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("electricalConnectionId",
                                           m_electricalConnectionId);
  }
  if (m_parameterIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("parameterId", m_parameterId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram