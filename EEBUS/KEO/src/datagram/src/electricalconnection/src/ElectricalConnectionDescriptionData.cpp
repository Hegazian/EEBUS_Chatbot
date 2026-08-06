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

#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionData.h>

#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionDescriptionData::ElectricalConnectionDescriptionData()
    : m_electricalConnectionIdIsSet(false), m_electricalConnectionId(0),
      m_powerSupplyTypeIsSet(false),
      m_powerSupplyType(ElectricalConnectionVoltageType()),
      m_acConnectedPhasesIsSet(false), m_acConnectedPhases(0),
      m_acRmsPeriodDurationIsSet(false), m_acRmsPeriodDuration(xs_duration()),
      m_positiveEnergyDirectionIsSet(false),
      m_positiveEnergyDirection(EnergyDirection()), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool ElectricalConnectionDescriptionData::
operator==(const ElectricalConnectionDescriptionData &c_classObject) const {
  if (m_electricalConnectionIdIsSet !=
          c_classObject.m_electricalConnectionIdIsSet ||
      (m_electricalConnectionIdIsSet &&
       (m_electricalConnectionId != c_classObject.m_electricalConnectionId))) {
    return false;
  }
  if (m_powerSupplyTypeIsSet != c_classObject.m_powerSupplyTypeIsSet ||
      (m_powerSupplyTypeIsSet &&
       (m_powerSupplyType != c_classObject.m_powerSupplyType))) {
    return false;
  }
  if (m_acConnectedPhasesIsSet != c_classObject.m_acConnectedPhasesIsSet ||
      (m_acConnectedPhasesIsSet &&
       (m_acConnectedPhases != c_classObject.m_acConnectedPhases))) {
    return false;
  }
  if (m_acRmsPeriodDurationIsSet != c_classObject.m_acRmsPeriodDurationIsSet ||
      (m_acRmsPeriodDurationIsSet &&
       (m_acRmsPeriodDuration != c_classObject.m_acRmsPeriodDuration))) {
    return false;
  }
  if (m_positiveEnergyDirectionIsSet !=
          c_classObject.m_positiveEnergyDirectionIsSet ||
      (m_positiveEnergyDirectionIsSet &&
       (m_positiveEnergyDirection !=
        c_classObject.m_positiveEnergyDirection))) {
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

bool ElectricalConnectionDescriptionData::
operator!=(const ElectricalConnectionDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionDescriptionData::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_powerSupplyTypeIsSet &&
         !m_acConnectedPhasesIsSet && !m_acRmsPeriodDurationIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_scopeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

void ElectricalConnectionDescriptionData::setElectricalConnectionId(
    const xs_unsignedInt &electricalConnectionId) {
  m_electricalConnectionId = electricalConnectionId;
  m_electricalConnectionIdIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionDescriptionData::getElectricalConnectionId() const {
  return m_electricalConnectionId;
}

void ElectricalConnectionDescriptionData::cleanElectricalConnectionId() {
  m_electricalConnectionId = 0;
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionDescriptionData::getElectricalConnectionIdIsSet()
    const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionDescriptionData::setPowerSupplyType(
    const ElectricalConnectionVoltageType &powerSupplyType) {
  m_powerSupplyType = powerSupplyType;
  m_powerSupplyTypeIsSet = true;
}

const ElectricalConnectionVoltageType &
ElectricalConnectionDescriptionData::getPowerSupplyType() const {
  return m_powerSupplyType;
}

void ElectricalConnectionDescriptionData::cleanPowerSupplyType() {
  m_powerSupplyType = ElectricalConnectionVoltageType();
  m_powerSupplyTypeIsSet = false;
}

bool ElectricalConnectionDescriptionData::getPowerSupplyTypeIsSet() const {
  return m_powerSupplyTypeIsSet;
}

void ElectricalConnectionDescriptionData::setAcConnectedPhases(
    const xs_unsignedInt &acConnectedPhases) {
  m_acConnectedPhases = acConnectedPhases;
  m_acConnectedPhasesIsSet = true;
}

const xs_unsignedInt &
ElectricalConnectionDescriptionData::getAcConnectedPhases() const {
  return m_acConnectedPhases;
}

void ElectricalConnectionDescriptionData::cleanAcConnectedPhases() {
  m_acConnectedPhases = 0;
  m_acConnectedPhasesIsSet = false;
}

bool ElectricalConnectionDescriptionData::getAcConnectedPhasesIsSet() const {
  return m_acConnectedPhasesIsSet;
}

void ElectricalConnectionDescriptionData::setAcRmsPeriodDuration(
    const xs_duration &acRmsPeriodDuration) {
  m_acRmsPeriodDuration = acRmsPeriodDuration;
  m_acRmsPeriodDurationIsSet = true;
}

const xs_duration &
ElectricalConnectionDescriptionData::getAcRmsPeriodDuration() const {
  return m_acRmsPeriodDuration;
}

void ElectricalConnectionDescriptionData::cleanAcRmsPeriodDuration() {
  m_acRmsPeriodDuration = xs_duration();
  m_acRmsPeriodDurationIsSet = false;
}

bool ElectricalConnectionDescriptionData::getAcRmsPeriodDurationIsSet() const {
  return m_acRmsPeriodDurationIsSet;
}

void ElectricalConnectionDescriptionData::setPositiveEnergyDirection(
    const EnergyDirection &positiveEnergyDirection) {
  m_positiveEnergyDirection = positiveEnergyDirection;
  m_positiveEnergyDirectionIsSet = true;
}

const EnergyDirection &
ElectricalConnectionDescriptionData::getPositiveEnergyDirection() const {
  return m_positiveEnergyDirection;
}

void ElectricalConnectionDescriptionData::cleanPositiveEnergyDirection() {
  m_positiveEnergyDirection = EnergyDirection();
  m_positiveEnergyDirectionIsSet = false;
}

bool ElectricalConnectionDescriptionData::getPositiveEnergyDirectionIsSet()
    const {
  return m_positiveEnergyDirectionIsSet;
}

void ElectricalConnectionDescriptionData::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &ElectricalConnectionDescriptionData::getScopeType() const {
  return m_scopeType;
}

void ElectricalConnectionDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool ElectricalConnectionDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void ElectricalConnectionDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &ElectricalConnectionDescriptionData::getLabel() const {
  return m_label;
}

void ElectricalConnectionDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool ElectricalConnectionDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void ElectricalConnectionDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &ElectricalConnectionDescriptionData::getDescription() const {
  return m_description;
}

void ElectricalConnectionDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool ElectricalConnectionDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

ElectricalConnectionDescriptionData ElectricalConnectionDescriptionData::reduce(
    const ElectricalConnectionDescriptionDataElements &elements) const {
  ElectricalConnectionDescriptionData dataOut;
  if (getElectricalConnectionIdIsSet() &&
      elements.getElectricalConnectionIdIsSet()) {
    dataOut.setElectricalConnectionId(getElectricalConnectionId());
  }
  if (getPowerSupplyTypeIsSet() && elements.getPowerSupplyTypeIsSet()) {
    dataOut.setPowerSupplyType(getPowerSupplyType());
  }
  if (getAcConnectedPhasesIsSet() && elements.getAcConnectedPhasesIsSet()) {
    dataOut.setAcConnectedPhases(getAcConnectedPhases());
  }
  if (getAcRmsPeriodDurationIsSet() && elements.getAcRmsPeriodDurationIsSet()) {
    dataOut.setAcRmsPeriodDuration(getAcRmsPeriodDuration());
  }
  if (getPositiveEnergyDirectionIsSet() &&
      elements.getPositiveEnergyDirectionIsSet()) {
    dataOut.setPositiveEnergyDirection(getPositiveEnergyDirection());
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

bool ElectricalConnectionDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"electricalConnectionId", "powerSupplyType", "acConnectedPhases",
             "acRmsPeriodDuration", "positiveEnergyDirection", "scopeType",
             "label", "description"})) {
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
                                   "powerSupplyType", &m_powerSupplyType)) {
      m_powerSupplyTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acConnectedPhases", &m_acConnectedPhases)) {
      m_acConnectedPhasesIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "acRmsPeriodDuration",
                                   &m_acRmsPeriodDuration)) {
      m_acRmsPeriodDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positiveEnergyDirection",
                                   &m_positiveEnergyDirection)) {
      m_positiveEnergyDirectionIsSet = true;
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

std::string ElectricalConnectionDescriptionData::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("electricalConnectionId",
                                           m_electricalConnectionId);
  }
  if (m_powerSupplyTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("powerSupplyType", m_powerSupplyType);
  }
  if (m_acConnectedPhasesIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("acConnectedPhases", m_acConnectedPhases);
  }
  if (m_acRmsPeriodDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("acRmsPeriodDuration",
                                           m_acRmsPeriodDuration);
  }
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("positiveEnergyDirection",
                                           m_positiveEnergyDirection);
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