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

#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionData.h>

#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionParameterDescriptionData::
    ElectricalConnectionParameterDescriptionData()
    : m_electricalConnectionIdIsSet(false), m_electricalConnectionId(0),
      m_parameterIdIsSet(false), m_parameterId(0), m_measurementIdIsSet(false),
      m_measurementId(0), m_voltageTypeIsSet(false),
      m_voltageType(ElectricalConnectionVoltageType()),
      m_acMeasuredPhasesIsSet(false),
      m_acMeasuredPhases(ElectricalConnectionPhaseName()),
      m_acMeasuredInReferenceToIsSet(false),
      m_acMeasuredInReferenceTo(ElectricalConnectionPhaseName()),
      m_acMeasurementTypeIsSet(false),
      m_acMeasurementType(ElectricalConnectionAcMeasurementType()),
      m_acMeasurementVariantIsSet(false),
      m_acMeasurementVariant(ElectricalConnectionMeasurandVariant()),
      m_acMeasuredHarmonicIsSet(false), m_acMeasuredHarmonic(0),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool ElectricalConnectionParameterDescriptionData::operator==(
    const ElectricalConnectionParameterDescriptionData &c_classObject) const {
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
  if (m_voltageTypeIsSet != c_classObject.m_voltageTypeIsSet ||
      (m_voltageTypeIsSet && (m_voltageType != c_classObject.m_voltageType))) {
    return false;
  }
  if (m_acMeasuredPhasesIsSet != c_classObject.m_acMeasuredPhasesIsSet ||
      (m_acMeasuredPhasesIsSet &&
       (m_acMeasuredPhases != c_classObject.m_acMeasuredPhases))) {
    return false;
  }
  if (m_acMeasuredInReferenceToIsSet !=
          c_classObject.m_acMeasuredInReferenceToIsSet ||
      (m_acMeasuredInReferenceToIsSet &&
       (m_acMeasuredInReferenceTo !=
        c_classObject.m_acMeasuredInReferenceTo))) {
    return false;
  }
  if (m_acMeasurementTypeIsSet != c_classObject.m_acMeasurementTypeIsSet ||
      (m_acMeasurementTypeIsSet &&
       (m_acMeasurementType != c_classObject.m_acMeasurementType))) {
    return false;
  }
  if (m_acMeasurementVariantIsSet !=
          c_classObject.m_acMeasurementVariantIsSet ||
      (m_acMeasurementVariantIsSet &&
       (m_acMeasurementVariant != c_classObject.m_acMeasurementVariant))) {
    return false;
  }
  if (m_acMeasuredHarmonicIsSet != c_classObject.m_acMeasuredHarmonicIsSet ||
      (m_acMeasuredHarmonicIsSet &&
       (m_acMeasuredHarmonic != c_classObject.m_acMeasuredHarmonic))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionParameterDescriptionData::operator!=(
    const ElectricalConnectionParameterDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionParameterDescriptionData::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_parameterIdIsSet &&
         !m_measurementIdIsSet && !m_voltageTypeIsSet &&
         !m_acMeasuredPhasesIsSet && !m_acMeasuredInReferenceToIsSet &&
         !m_acMeasurementTypeIsSet && !m_acMeasurementVariantIsSet &&
         !m_acMeasuredHarmonicIsSet && !m_scopeTypeIsSet && !m_labelIsSet &&
         !m_descriptionIsSet;
}

void ElectricalConnectionParameterDescriptionData::setElectricalConnectionId(
    const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionParameterDescriptionData::getElectricalConnectionId()
    const {
  return m_electricalConnectionId;
}

void ElectricalConnectionParameterDescriptionData::
    cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionParameterDescriptionData::setParameterId(
    const xs_unsignedInt &parameterId) {
  m_parameterId = parameterId;
  m_parameterIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionParameterDescriptionData::getParameterId() const {
  return m_parameterId;
}

void ElectricalConnectionParameterDescriptionData::cleanParameterId() {
  m_parameterId = 0;
  m_parameterIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getParameterIdIsSet() const {
  return m_parameterIdIsSet;
}

void ElectricalConnectionParameterDescriptionData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionParameterDescriptionData::getMeasurementId() const {
  return m_measurementId;
}

void ElectricalConnectionParameterDescriptionData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getMeasurementIdIsSet()
    const {
  return m_measurementIdIsSet;
}

void ElectricalConnectionParameterDescriptionData::setVoltageType(
    const ElectricalConnectionVoltageType &voltageType) {
  m_voltageType = voltageType;
  m_voltageTypeIsSet = true;
}

const ElectricalConnectionVoltageType &
ElectricalConnectionParameterDescriptionData::getVoltageType() const {
  return m_voltageType;
}

void ElectricalConnectionParameterDescriptionData::cleanVoltageType() {
  m_voltageType = ElectricalConnectionVoltageType();
  m_voltageTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getVoltageTypeIsSet() const {
  return m_voltageTypeIsSet;
}

void ElectricalConnectionParameterDescriptionData::setAcMeasuredPhases(
    const ElectricalConnectionPhaseName &acMeasuredPhases) {
  m_acMeasuredPhases = acMeasuredPhases;
  m_acMeasuredPhasesIsSet = true;
}

const ElectricalConnectionPhaseName &
ElectricalConnectionParameterDescriptionData::getAcMeasuredPhases() const {
  return m_acMeasuredPhases;
}

void ElectricalConnectionParameterDescriptionData::cleanAcMeasuredPhases() {
  m_acMeasuredPhases = ElectricalConnectionPhaseName();
  m_acMeasuredPhasesIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getAcMeasuredPhasesIsSet()
    const {
  return m_acMeasuredPhasesIsSet;
}

void ElectricalConnectionParameterDescriptionData::setAcMeasuredInReferenceTo(
    const ElectricalConnectionPhaseName &acMeasuredInReferenceTo) {
  m_acMeasuredInReferenceTo = acMeasuredInReferenceTo;
  m_acMeasuredInReferenceToIsSet = true;
}

const ElectricalConnectionPhaseName &
ElectricalConnectionParameterDescriptionData::getAcMeasuredInReferenceTo()
    const {
  return m_acMeasuredInReferenceTo;
}

void ElectricalConnectionParameterDescriptionData::
    cleanAcMeasuredInReferenceTo() {
  m_acMeasuredInReferenceTo = ElectricalConnectionPhaseName();
  m_acMeasuredInReferenceToIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::
    getAcMeasuredInReferenceToIsSet() const {
  return m_acMeasuredInReferenceToIsSet;
}

void ElectricalConnectionParameterDescriptionData::setAcMeasurementType(
    const ElectricalConnectionAcMeasurementType &acMeasurementType) {
  m_acMeasurementType = acMeasurementType;
  m_acMeasurementTypeIsSet = true;
}

const ElectricalConnectionAcMeasurementType &
ElectricalConnectionParameterDescriptionData::getAcMeasurementType() const {
  return m_acMeasurementType;
}

void ElectricalConnectionParameterDescriptionData::cleanAcMeasurementType() {
  m_acMeasurementType = ElectricalConnectionAcMeasurementType();
  m_acMeasurementTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getAcMeasurementTypeIsSet()
    const {
  return m_acMeasurementTypeIsSet;
}

void ElectricalConnectionParameterDescriptionData::setAcMeasurementVariant(
    const ElectricalConnectionMeasurandVariant &acMeasurementVariant) {
  m_acMeasurementVariant = acMeasurementVariant;
  m_acMeasurementVariantIsSet = true;
}

const ElectricalConnectionMeasurandVariant &
ElectricalConnectionParameterDescriptionData::getAcMeasurementVariant() const {
  return m_acMeasurementVariant;
}

void ElectricalConnectionParameterDescriptionData::cleanAcMeasurementVariant() {
  m_acMeasurementVariant = ElectricalConnectionMeasurandVariant();
  m_acMeasurementVariantIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::
    getAcMeasurementVariantIsSet() const {
  return m_acMeasurementVariantIsSet;
}

void ElectricalConnectionParameterDescriptionData::setAcMeasuredHarmonic(
    const xs_unsignedByte &acMeasuredHarmonic) {
  m_acMeasuredHarmonic = acMeasuredHarmonic;
  m_acMeasuredHarmonicIsSet = true;
}

const xs_unsignedByte &
ElectricalConnectionParameterDescriptionData::getAcMeasuredHarmonic() const {
  return m_acMeasuredHarmonic;
}

void ElectricalConnectionParameterDescriptionData::cleanAcMeasuredHarmonic() {
  m_acMeasuredHarmonic = 0;
  m_acMeasuredHarmonicIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getAcMeasuredHarmonicIsSet()
    const {
  return m_acMeasuredHarmonicIsSet;
}

void ElectricalConnectionParameterDescriptionData::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &
ElectricalConnectionParameterDescriptionData::getScopeType() const {
  return m_scopeType;
}

void ElectricalConnectionParameterDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void ElectricalConnectionParameterDescriptionData::setLabel(
    const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &
ElectricalConnectionParameterDescriptionData::getLabel() const {
  return m_label;
}

void ElectricalConnectionParameterDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void ElectricalConnectionParameterDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &
ElectricalConnectionParameterDescriptionData::getDescription() const {
  return m_description;
}

void ElectricalConnectionParameterDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool ElectricalConnectionParameterDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

ElectricalConnectionParameterDescriptionData
ElectricalConnectionParameterDescriptionData::reduce(
    const ElectricalConnectionParameterDescriptionDataElements &elements)
    const {
  ElectricalConnectionParameterDescriptionData dataOut;
  if (getElectricalConnectionIdIsSet() &&
      elements.getElectricalConnectionIdIsSet()) {
    dataOut.setElectricalConnectionId(getElectricalConnectionId());
  }
  if (getParameterIdIsSet() && elements.getParameterIdIsSet()) {
    dataOut.setParameterId(getParameterId());
  }
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getVoltageTypeIsSet() && elements.getVoltageTypeIsSet()) {
    dataOut.setVoltageType(getVoltageType());
  }
  if (getAcMeasuredPhasesIsSet() && elements.getAcMeasuredPhasesIsSet()) {
    dataOut.setAcMeasuredPhases(getAcMeasuredPhases());
  }
  if (getAcMeasuredInReferenceToIsSet() &&
      elements.getAcMeasuredInReferenceToIsSet()) {
    dataOut.setAcMeasuredInReferenceTo(getAcMeasuredInReferenceTo());
  }
  if (getAcMeasurementTypeIsSet() && elements.getAcMeasurementTypeIsSet()) {
    dataOut.setAcMeasurementType(getAcMeasurementType());
  }
  if (getAcMeasurementVariantIsSet() &&
      elements.getAcMeasurementVariantIsSet()) {
    dataOut.setAcMeasurementVariant(getAcMeasurementVariant());
  }
  if (getAcMeasuredHarmonicIsSet() && elements.getAcMeasuredHarmonicIsSet()) {
    dataOut.setAcMeasuredHarmonic(getAcMeasuredHarmonic());
  }
  if (getScopeTypeIsSet() && elements.getScopeTypeIsSet()) {
    dataOut.setScopeType(getScopeType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool ElectricalConnectionParameterDescriptionData::fromJson(
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
                                   "voltageType", &m_voltageType)) {
      m_voltageTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acMeasuredPhases", &m_acMeasuredPhases)) {
      m_acMeasuredPhasesIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acMeasuredInReferenceTo",
                                   &m_acMeasuredInReferenceTo)) {
      m_acMeasuredInReferenceToIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acMeasurementType", &m_acMeasurementType)) {
      m_acMeasurementTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acMeasurementVariant",
                                   &m_acMeasurementVariant)) {
      m_acMeasurementVariantIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acMeasuredHarmonic",
                                   &m_acMeasuredHarmonic)) {
      m_acMeasuredHarmonicIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
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

std::string ElectricalConnectionParameterDescriptionData::toJson() const {
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
  if (m_voltageTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("voltageType", m_voltageType);
  }
  if (m_acMeasuredPhasesIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("acMeasuredPhases", m_acMeasuredPhases);
  }
  if (m_acMeasuredInReferenceToIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("acMeasuredInReferenceTo",
                                           m_acMeasuredInReferenceTo);
  }
  if (m_acMeasurementTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("acMeasurementType", m_acMeasurementType);
  }
  if (m_acMeasurementVariantIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("acMeasurementVariant",
                                           m_acMeasurementVariant);
  }
  if (m_acMeasuredHarmonicIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("acMeasuredHarmonic",
                                           m_acMeasuredHarmonic);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram