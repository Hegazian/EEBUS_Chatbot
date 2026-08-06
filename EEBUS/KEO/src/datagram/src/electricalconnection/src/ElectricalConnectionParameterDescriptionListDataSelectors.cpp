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

#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionParameterDescriptionListDataSelectors::
    ElectricalConnectionParameterDescriptionListDataSelectors()
    : DataSelectors(), m_electricalConnectionIdIsSet(false),
      m_electricalConnectionId(0), m_parameterIdIsSet(false), m_parameterId(0),
      m_measurementIdIsSet(false), m_measurementId(0), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType())

{}

bool ElectricalConnectionParameterDescriptionListDataSelectors::
operator==(const ElectricalConnectionParameterDescriptionListDataSelectors
               &c_classObject) const {
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
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::
operator!=(const ElectricalConnectionParameterDescriptionListDataSelectors
               &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::isEmpty()
    const {
  return !m_electricalConnectionIdIsSet && !m_parameterIdIsSet &&
         !m_measurementIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type
ElectricalConnectionParameterDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr
ElectricalConnectionParameterDescriptionListDataSelectors::clone() const {
  return std::make_shared<
      ElectricalConnectionParameterDescriptionListDataSelectors>(*this);
}

void ElectricalConnectionParameterDescriptionListDataSelectors::
    setElectricalConnectionId(const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionParameterDescriptionListDataSelectors::
    getElectricalConnectionId() const {
  return m_electricalConnectionId;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::
    cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::setParameterId(
    const xs_unsignedInt &parameterId) {
  m_parameterId = parameterId;
  m_parameterIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionParameterDescriptionListDataSelectors::getParameterId()
    const {
  return m_parameterId;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::
    cleanParameterId() {
  m_parameterId = 0;
  m_parameterIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::
    getParameterIdIsSet() const {
  return m_parameterIdIsSet;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::
    setMeasurementId(const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionParameterDescriptionListDataSelectors::getMeasurementId()
    const {
  return m_measurementId;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::
    cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::
    getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &
ElectricalConnectionParameterDescriptionListDataSelectors::getScopeType()
    const {
  return m_scopeType;
}

void ElectricalConnectionParameterDescriptionListDataSelectors::
    cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::
    getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::selects(
    const ElectricalConnectionParameterDescriptionData &data) const {
  if (getElectricalConnectionIdIsSet() &&
      (!data.getElectricalConnectionIdIsSet() ||
       getElectricalConnectionId() != data.getElectricalConnectionId())) {
    return false;
  }
  if (getParameterIdIsSet() && (!data.getParameterIdIsSet() ||
                                getParameterId() != data.getParameterId())) {
    return false;
  }
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool ElectricalConnectionParameterDescriptionListDataSelectors::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionId", "parameterId", "measurementId",
                   "scopeType"})) {
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
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
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

std::string
ElectricalConnectionParameterDescriptionListDataSelectors::toJson() const {
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
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram