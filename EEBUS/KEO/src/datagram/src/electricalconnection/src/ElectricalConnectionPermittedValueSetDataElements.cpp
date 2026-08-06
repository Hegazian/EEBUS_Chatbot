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

#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionPermittedValueSetDataElements::
    ElectricalConnectionPermittedValueSetDataElements()
    : DataElements(), m_electricalConnectionIdIsSet(false),
      m_parameterIdIsSet(false), m_permittedValueSetIsSet(false),
      m_permittedValueSet(ScaledNumberSetElements())

{}

ElectricalConnectionPermittedValueSetDataElements::
    ElectricalConnectionPermittedValueSetDataElements(
        xs_boolean c_electricalConnectionIdIsSet, xs_boolean c_parameterIdIsSet,
        const ScaledNumberSetElements &c_permittedValueSet)
    : DataElements(),
      m_electricalConnectionIdIsSet(c_electricalConnectionIdIsSet),
      m_parameterIdIsSet(c_parameterIdIsSet), m_permittedValueSetIsSet(true),
      m_permittedValueSet(c_permittedValueSet)

{}

bool ElectricalConnectionPermittedValueSetDataElements::operator==(
    const ElectricalConnectionPermittedValueSetDataElements &c_classObject)
    const {
  if (m_electricalConnectionIdIsSet !=
      c_classObject.m_electricalConnectionIdIsSet) {
    return false;
  }
  if (m_parameterIdIsSet != c_classObject.m_parameterIdIsSet) {
    return false;
  }
  if (m_permittedValueSetIsSet != c_classObject.m_permittedValueSetIsSet ||
      (m_permittedValueSetIsSet &&
       (m_permittedValueSet != c_classObject.m_permittedValueSet))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionPermittedValueSetDataElements::operator!=(
    const ElectricalConnectionPermittedValueSetDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionPermittedValueSetDataElements::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_parameterIdIsSet &&
         !m_permittedValueSetIsSet;
}

DataElements::Type
ElectricalConnectionPermittedValueSetDataElements::getDataType() const {
  return DataElements::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
ElectricalConnectionPermittedValueSetDataElements::clone() const {
  return std::make_shared<ElectricalConnectionPermittedValueSetDataElements>(
      *this);
}

void ElectricalConnectionPermittedValueSetDataElements::
    setElectricalConnectionId() {
  m_electricalConnectionIdIsSet = true;
}

void ElectricalConnectionPermittedValueSetDataElements::
    cleanElectricalConnectionId() {
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionPermittedValueSetDataElements::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionPermittedValueSetDataElements::setParameterId() {
  m_parameterIdIsSet = true;
}

void ElectricalConnectionPermittedValueSetDataElements::cleanParameterId() {
  m_parameterIdIsSet = false;
}

bool ElectricalConnectionPermittedValueSetDataElements::getParameterIdIsSet()
    const {
  return m_parameterIdIsSet;
}

void ElectricalConnectionPermittedValueSetDataElements::setPermittedValueSet(
    const ScaledNumberSetElements &permittedValueSet) {
  m_permittedValueSet = permittedValueSet;
  m_permittedValueSetIsSet = true;
}

const ScaledNumberSetElements &
ElectricalConnectionPermittedValueSetDataElements::getPermittedValueSet()
    const {
  return m_permittedValueSet;
}

void ElectricalConnectionPermittedValueSetDataElements::
    cleanPermittedValueSet() {
  m_permittedValueSet = ScaledNumberSetElements();
  m_permittedValueSetIsSet = false;
}

bool ElectricalConnectionPermittedValueSetDataElements::
    getPermittedValueSetIsSet() const {
  return m_permittedValueSetIsSet;
}

bool ElectricalConnectionPermittedValueSetDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"electricalConnectionId", "parameterId", "permittedValueSet"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "electricalConnectionId")) {
      m_electricalConnectionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "parameterId")) {
      m_parameterIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "permittedValueSet", &m_permittedValueSet)) {
      m_permittedValueSetIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionPermittedValueSetDataElements::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("electricalConnectionId");
  }
  if (m_parameterIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("parameterId");
  }
  if (m_permittedValueSetIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("permittedValueSet", m_permittedValueSet);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram