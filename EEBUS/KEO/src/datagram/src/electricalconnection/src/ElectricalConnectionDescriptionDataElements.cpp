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

#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionDescriptionDataElements::
    ElectricalConnectionDescriptionDataElements()
    : DataElements(), m_electricalConnectionIdIsSet(false),
      m_powerSupplyTypeIsSet(false), m_acConnectedPhasesIsSet(false),
      m_acRmsPeriodDurationIsSet(false), m_positiveEnergyDirectionIsSet(false),
      m_scopeTypeIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool ElectricalConnectionDescriptionDataElements::operator==(
    const ElectricalConnectionDescriptionDataElements &c_classObject) const {
  if (m_electricalConnectionIdIsSet !=
      c_classObject.m_electricalConnectionIdIsSet) {
    return false;
  }
  if (m_powerSupplyTypeIsSet != c_classObject.m_powerSupplyTypeIsSet) {
    return false;
  }
  if (m_acConnectedPhasesIsSet != c_classObject.m_acConnectedPhasesIsSet) {
    return false;
  }
  if (m_acRmsPeriodDurationIsSet != c_classObject.m_acRmsPeriodDurationIsSet) {
    return false;
  }
  if (m_positiveEnergyDirectionIsSet !=
      c_classObject.m_positiveEnergyDirectionIsSet) {
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

bool ElectricalConnectionDescriptionDataElements::operator!=(
    const ElectricalConnectionDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionDescriptionDataElements::isEmpty() const {
  return !m_electricalConnectionIdIsSet && !m_powerSupplyTypeIsSet &&
         !m_acConnectedPhasesIsSet && !m_acRmsPeriodDurationIsSet &&
         !m_positiveEnergyDirectionIsSet && !m_scopeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
ElectricalConnectionDescriptionDataElements::getDataType() const {
  return DataElements::Type::
      ELECTRICAL_CONNECTION_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ElectricalConnectionDescriptionDataElements::clone() const {
  return std::make_shared<ElectricalConnectionDescriptionDataElements>(*this);
}

void ElectricalConnectionDescriptionDataElements::setElectricalConnectionId() {
  m_electricalConnectionIdIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::
    cleanElectricalConnectionId() {
  m_electricalConnectionIdIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::
    getElectricalConnectionIdIsSet() const {
  return m_electricalConnectionIdIsSet;
}

void ElectricalConnectionDescriptionDataElements::setPowerSupplyType() {
  m_powerSupplyTypeIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::cleanPowerSupplyType() {
  m_powerSupplyTypeIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::getPowerSupplyTypeIsSet()
    const {
  return m_powerSupplyTypeIsSet;
}

void ElectricalConnectionDescriptionDataElements::setAcConnectedPhases() {
  m_acConnectedPhasesIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::cleanAcConnectedPhases() {
  m_acConnectedPhasesIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::getAcConnectedPhasesIsSet()
    const {
  return m_acConnectedPhasesIsSet;
}

void ElectricalConnectionDescriptionDataElements::setAcRmsPeriodDuration() {
  m_acRmsPeriodDurationIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::cleanAcRmsPeriodDuration() {
  m_acRmsPeriodDurationIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::getAcRmsPeriodDurationIsSet()
    const {
  return m_acRmsPeriodDurationIsSet;
}

void ElectricalConnectionDescriptionDataElements::setPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::
    cleanPositiveEnergyDirection() {
  m_positiveEnergyDirectionIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::
    getPositiveEnergyDirectionIsSet() const {
  return m_positiveEnergyDirectionIsSet;
}

void ElectricalConnectionDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void ElectricalConnectionDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void ElectricalConnectionDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void ElectricalConnectionDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool ElectricalConnectionDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool ElectricalConnectionDescriptionDataElements::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "electricalConnectionId")) {
      m_electricalConnectionIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "powerSupplyType")) {
      m_powerSupplyTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acConnectedPhases")) {
      m_acConnectedPhasesIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "acRmsPeriodDuration")) {
      m_acRmsPeriodDurationIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positiveEnergyDirection")) {
      m_positiveEnergyDirectionIsSet = true;
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

std::string ElectricalConnectionDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("electricalConnectionId");
  }
  if (m_powerSupplyTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("powerSupplyType");
  }
  if (m_acConnectedPhasesIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acConnectedPhases");
  }
  if (m_acRmsPeriodDurationIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("acRmsPeriodDuration");
  }
  if (m_positiveEnergyDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positiveEnergyDirection");
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