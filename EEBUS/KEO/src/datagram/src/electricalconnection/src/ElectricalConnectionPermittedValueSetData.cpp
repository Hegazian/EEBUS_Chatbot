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

#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetData.h>

#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionPermittedValueSetData::
    ElectricalConnectionPermittedValueSetData()
    : m_electricalConnectionIdIsSet(false), m_electricalConnectionId(0),
      m_parameterIdIsSet(false), m_parameterId(0),
      m_permittedValueSetIsSet(false),
      m_permittedValueSet(std::vector<ScaledNumberSet>())

{}

ElectricalConnectionPermittedValueSetData::
    ElectricalConnectionPermittedValueSetData(
        const xs_unsignedInt &c_electricalConnectionId,
        const xs_unsignedInt &c_parameterId,
        const std::vector<ScaledNumberSet> &c_permittedValueSet)
    : m_electricalConnectionIdIsSet(true),
      m_electricalConnectionId(c_electricalConnectionId),
      m_parameterIdIsSet(true), m_parameterId(c_parameterId),
      m_permittedValueSetIsSet(true), m_permittedValueSet(c_permittedValueSet)

{}

bool ElectricalConnectionPermittedValueSetData::operator==(
    const ElectricalConnectionPermittedValueSetData &c_classObject) const {
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
  if (m_permittedValueSetIsSet != c_classObject.m_permittedValueSetIsSet ||
      (m_permittedValueSetIsSet &&
       (m_permittedValueSet != c_classObject.m_permittedValueSet))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionPermittedValueSetData::operator!=(
    const ElectricalConnectionPermittedValueSetData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionPermittedValueSetData::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_parameterIdIsSet &&
         !m_permittedValueSetIsSet;
}

void ElectricalConnectionPermittedValueSetData::setElectricalConnectionId(
    const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionPermittedValueSetData::getElectricalConnectionId() const {
  return m_electricalConnectionId;
}

void ElectricalConnectionPermittedValueSetData::cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionPermittedValueSetData::getElectricalConnectionIdIsSet()
    const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionPermittedValueSetData::setParameterId(
    const xs_unsignedInt &parameterId) {
  m_parameterId = parameterId;
  m_parameterIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionPermittedValueSetData::getParameterId() const {
  return m_parameterId;
}

void ElectricalConnectionPermittedValueSetData::cleanParameterId() {
  m_parameterId = 0;
  m_parameterIdIsSet = false;
}

bool ElectricalConnectionPermittedValueSetData::getParameterIdIsSet() const {
  return m_parameterIdIsSet;
}

void ElectricalConnectionPermittedValueSetData::setPermittedValueSet(
    const std::vector<ScaledNumberSet> &permittedValueSet) {
  m_permittedValueSet = permittedValueSet;
  m_permittedValueSetIsSet = true;
}

const std::vector<ScaledNumberSet> &
ElectricalConnectionPermittedValueSetData::getPermittedValueSet() const {
  return m_permittedValueSet;
}

void ElectricalConnectionPermittedValueSetData::cleanPermittedValueSet() {
  m_permittedValueSet.clear();
  m_permittedValueSetIsSet = false;
}

bool ElectricalConnectionPermittedValueSetData::getPermittedValueSetIsSet()
    const {
  return m_permittedValueSetIsSet;
}

ElectricalConnectionPermittedValueSetData
ElectricalConnectionPermittedValueSetData::reduce(
    const ElectricalConnectionPermittedValueSetDataElements &elements) const {
  ElectricalConnectionPermittedValueSetData dataOut;
  if (getElectricalConnectionIdIsSet() &&
      elements.getElectricalConnectionIdIsSet()) {
    dataOut.setElectricalConnectionId(getElectricalConnectionId());
  }
  if (getParameterIdIsSet() && elements.getParameterIdIsSet()) {
    dataOut.setParameterId(getParameterId());
  }
  if (getPermittedValueSetIsSet() && elements.getPermittedValueSetIsSet()) {
    std::vector<ScaledNumberSet> values;
    for (const auto &value : getPermittedValueSet()) {
      values.push_back(value.reduce(elements.getPermittedValueSet()));
    }
    dataOut.setPermittedValueSet(values);
  }
  return dataOut;
}

bool ElectricalConnectionPermittedValueSetData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"electricalConnectionId", "parameterId", "permittedValueSet"})) {
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
    if (iter != json->end() && KeoJsonTransformation::getList<ScaledNumberSet>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "permittedValueSet", &m_permittedValueSet)) {
      m_permittedValueSetIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionPermittedValueSetData::toJson() const {
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
  if (m_permittedValueSetIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ScaledNumberSet>(
        "permittedValueSet", m_permittedValueSet);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram