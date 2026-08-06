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

#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionParameterDescriptionDataElements::
    ElectricalConnectionParameterDescriptionDataElements()
    : DataElements(), m_electricalConnectionIdIsSet(false),
      m_parameterIdIsSet(false), m_measurementIdIsSet(false),
      m_voltageTypeIsSet(false), m_acMeasuredPhasesIsSet(false),
      m_acMeasuredInReferenceToIsSet(false), m_acMeasurementTypeIsSet(false),
      m_acMeasurementVariantIsSet(false), m_acMeasuredHarmonicIsSet(false),
      m_scopeTypeIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool ElectricalConnectionParameterDescriptionDataElements::operator==(
    const ElectricalConnectionParameterDescriptionDataElements &c_classObject)
    const {
  if (m_electricalConnectionIdIsSet !=
      c_classObject.m_electricalConnectionIdIsSet) {
    return false;
  }
  if (m_parameterIdIsSet != c_classObject.m_parameterIdIsSet) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_voltageTypeIsSet != c_classObject.m_voltageTypeIsSet) {
    return false;
  }
  if (m_acMeasuredPhasesIsSet != c_classObject.m_acMeasuredPhasesIsSet) {
    return false;
  }
  if (m_acMeasuredInReferenceToIsSet !=
      c_classObject.m_acMeasuredInReferenceToIsSet) {
    return false;
  }
  if (m_acMeasurementTypeIsSet != c_classObject.m_acMeasurementTypeIsSet) {
    return false;
  }
  if (m_acMeasurementVariantIsSet !=
      c_classObject.m_acMeasurementVariantIsSet) {
    return false;
  }
  if (m_acMeasuredHarmonicIsSet != c_classObject.m_acMeasuredHarmonicIsSet) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool ElectricalConnectionParameterDescriptionDataElements::operator!=(
    const ElectricalConnectionParameterDescriptionDataElements &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionParameterDescriptionDataElements::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_parameterIdIsSet &&
         !m_measurementIdIsSet && !m_voltageTypeIsSet &&
         !m_acMeasuredPhasesIsSet && !m_acMeasuredInReferenceToIsSet &&
         !m_acMeasurementTypeIsSet && !m_acMeasurementVariantIsSet &&
         !m_acMeasuredHarmonicIsSet && !m_scopeTypeIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

DataElements::Type
ElectricalConnectionParameterDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr
ElectricalConnectionParameterDescriptionDataElements::clone() const {
  return std::make_shared<ElectricalConnectionParameterDescriptionDataElements>(
      *this);
}

void ElectricalConnectionParameterDescriptionDataElements::
    setElectricalConnectionId() {
  m_electricalConnectionIdIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanElectricalConnectionId() {
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::setParameterId() {
  m_parameterIdIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::cleanParameterId() {
  m_parameterIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::getParameterIdIsSet()
    const {
  return m_parameterIdIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::setVoltageType() {
  m_voltageTypeIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::cleanVoltageType() {
  m_voltageTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::getVoltageTypeIsSet()
    const {
  return m_voltageTypeIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::
    setAcMeasuredPhases() {
  m_acMeasuredPhasesIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanAcMeasuredPhases() {
  m_acMeasuredPhasesIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getAcMeasuredPhasesIsSet() const {
  return m_acMeasuredPhasesIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::
    setAcMeasuredInReferenceTo() {
  m_acMeasuredInReferenceToIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanAcMeasuredInReferenceTo() {
  m_acMeasuredInReferenceToIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getAcMeasuredInReferenceToIsSet() const {
  return m_acMeasuredInReferenceToIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::
    setAcMeasurementType() {
  m_acMeasurementTypeIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanAcMeasurementType() {
  m_acMeasurementTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getAcMeasurementTypeIsSet() const {
  return m_acMeasurementTypeIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::
    setAcMeasurementVariant() {
  m_acMeasurementVariantIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanAcMeasurementVariant() {
  m_acMeasurementVariantIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getAcMeasurementVariantIsSet() const {
  return m_acMeasurementVariantIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::
    setAcMeasuredHarmonic() {
  m_acMeasuredHarmonicIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::
    cleanAcMeasuredHarmonic() {
  m_acMeasuredHarmonicIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::
    getAcMeasuredHarmonicIsSet() const {
  return m_acMeasuredHarmonicIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::getScopeTypeIsSet()
    const {
  return m_scopeTypeIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::getLabelIsSet()
    const {
  return m_labelIsSet;
}

void ElectricalConnectionParameterDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void ElectricalConnectionParameterDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool ElectricalConnectionParameterDescriptionDataElements::getDescriptionIsSet()
    const {
  return m_descriptionIsSet;
}

bool ElectricalConnectionParameterDescriptionDataElements::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"electricalConnectionId", "parameterId", "measurementId",
             "voltageType", "acMeasuredPhases", "acMeasuredInReferenceTo",
             "acMeasurementType", "acMeasurementVariant", "acMeasuredHarmonic",
             "scopeType", "label", "description"})) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "voltageType")) {
      m_voltageTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acMeasuredPhases")) {
      m_acMeasuredPhasesIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acMeasuredInReferenceTo")) {
      m_acMeasuredInReferenceToIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acMeasurementType")) {
      m_acMeasurementTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acMeasurementVariant")) {
      m_acMeasurementVariantIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acMeasuredHarmonic")) {
      m_acMeasuredHarmonicIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
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

std::string
ElectricalConnectionParameterDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("electricalConnectionId");
  }
  if (m_parameterIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("parameterId");
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_voltageTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("voltageType");
  }
  if (m_acMeasuredPhasesIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acMeasuredPhases");
  }
  if (m_acMeasuredInReferenceToIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acMeasuredInReferenceTo");
  }
  if (m_acMeasurementTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acMeasurementType");
  }
  if (m_acMeasurementVariantIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acMeasurementVariant");
  }
  if (m_acMeasuredHarmonicIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acMeasuredHarmonic");
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram