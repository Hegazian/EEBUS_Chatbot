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

#include <keo_datagram/directcontrol/DirectControlActivityDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DirectControlActivityDataElements::DirectControlActivityDataElements()
    : DataElements(), m_timestampIsSet(false), m_activityStateIsSet(false),
      m_isActivityStateChangeableIsSet(false), m_energyModeIsSet(false),
      m_isEnergyModeChangeableIsSet(false), m_powerIsSet(false),
      m_power(ScaledNumberElements()), m_isPowerChangeableIsSet(false),
      m_energyIsSet(false), m_energy(ScaledNumberElements()),
      m_isEnergyChangeableIsSet(false), m_sequenceIdIsSet(false)

{}

bool DirectControlActivityDataElements::
operator==(const DirectControlActivityDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_activityStateIsSet != c_classObject.m_activityStateIsSet) {
    return false;
  }
  if (m_isActivityStateChangeableIsSet !=
      c_classObject.m_isActivityStateChangeableIsSet) {
    return false;
  }
  if (m_energyModeIsSet != c_classObject.m_energyModeIsSet) {
    return false;
  }
  if (m_isEnergyModeChangeableIsSet !=
      c_classObject.m_isEnergyModeChangeableIsSet) {
    return false;
  }
  if (m_powerIsSet != c_classObject.m_powerIsSet ||
      (m_powerIsSet && (m_power != c_classObject.m_power))) {
    return false;
  }
  if (m_isPowerChangeableIsSet != c_classObject.m_isPowerChangeableIsSet) {
    return false;
  }
  if (m_energyIsSet != c_classObject.m_energyIsSet ||
      (m_energyIsSet && (m_energy != c_classObject.m_energy))) {
    return false;
  }
  if (m_isEnergyChangeableIsSet != c_classObject.m_isEnergyChangeableIsSet) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }

  return true;
}

bool DirectControlActivityDataElements::
operator!=(const DirectControlActivityDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool DirectControlActivityDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_activityStateIsSet &&
         !m_isActivityStateChangeableIsSet && !m_energyModeIsSet &&
         !m_isEnergyModeChangeableIsSet && !m_powerIsSet &&
         !m_isPowerChangeableIsSet && !m_energyIsSet &&
         !m_isEnergyChangeableIsSet && !m_sequenceIdIsSet;
}

DataElements::Type DirectControlActivityDataElements::getDataType() const {
  return DataElements::Type::DIRECT_CONTROL_ACTIVITY_DATA_ELEMENTS_TYPE;
}

DataElementsPtr DirectControlActivityDataElements::clone() const {
  return std::make_shared<DirectControlActivityDataElements>(*this);
}

void DirectControlActivityDataElements::setTimestamp() {
  m_timestampIsSet = true;
}

void DirectControlActivityDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool DirectControlActivityDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DirectControlActivityDataElements::setActivityState() {
  m_activityStateIsSet = true;
}

void DirectControlActivityDataElements::cleanActivityState() {
  m_activityStateIsSet = false;
}

bool DirectControlActivityDataElements::getActivityStateIsSet() const {
  return m_activityStateIsSet;
}

void DirectControlActivityDataElements::setIsActivityStateChangeable() {
  m_isActivityStateChangeableIsSet = true;
}

void DirectControlActivityDataElements::cleanIsActivityStateChangeable() {
  m_isActivityStateChangeableIsSet = false;
}

bool DirectControlActivityDataElements::getIsActivityStateChangeableIsSet()
    const {
  return m_isActivityStateChangeableIsSet;
}

void DirectControlActivityDataElements::setEnergyMode() {
  m_energyModeIsSet = true;
}

void DirectControlActivityDataElements::cleanEnergyMode() {
  m_energyModeIsSet = false;
}

bool DirectControlActivityDataElements::getEnergyModeIsSet() const {
  return m_energyModeIsSet;
}

void DirectControlActivityDataElements::setIsEnergyModeChangeable() {
  m_isEnergyModeChangeableIsSet = true;
}

void DirectControlActivityDataElements::cleanIsEnergyModeChangeable() {
  m_isEnergyModeChangeableIsSet = false;
}

bool DirectControlActivityDataElements::getIsEnergyModeChangeableIsSet() const {
  return m_isEnergyModeChangeableIsSet;
}

void DirectControlActivityDataElements::setPower(
    const ScaledNumberElements &power) {
  m_power = power;
  m_powerIsSet = true;
}

const ScaledNumberElements &
DirectControlActivityDataElements::getPower() const {
  return m_power;
}

void DirectControlActivityDataElements::cleanPower() {
  m_power = ScaledNumberElements();
  m_powerIsSet = false;
}

bool DirectControlActivityDataElements::getPowerIsSet() const {
  return m_powerIsSet;
}

void DirectControlActivityDataElements::setIsPowerChangeable() {
  m_isPowerChangeableIsSet = true;
}

void DirectControlActivityDataElements::cleanIsPowerChangeable() {
  m_isPowerChangeableIsSet = false;
}

bool DirectControlActivityDataElements::getIsPowerChangeableIsSet() const {
  return m_isPowerChangeableIsSet;
}

void DirectControlActivityDataElements::setEnergy(
    const ScaledNumberElements &energy) {
  m_energy = energy;
  m_energyIsSet = true;
}

const ScaledNumberElements &
DirectControlActivityDataElements::getEnergy() const {
  return m_energy;
}

void DirectControlActivityDataElements::cleanEnergy() {
  m_energy = ScaledNumberElements();
  m_energyIsSet = false;
}

bool DirectControlActivityDataElements::getEnergyIsSet() const {
  return m_energyIsSet;
}

void DirectControlActivityDataElements::setIsEnergyChangeable() {
  m_isEnergyChangeableIsSet = true;
}

void DirectControlActivityDataElements::cleanIsEnergyChangeable() {
  m_isEnergyChangeableIsSet = false;
}

bool DirectControlActivityDataElements::getIsEnergyChangeableIsSet() const {
  return m_isEnergyChangeableIsSet;
}

void DirectControlActivityDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void DirectControlActivityDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool DirectControlActivityDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

bool DirectControlActivityDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "activityState", "isActivityStateChangeable",
                   "energyMode", "isEnergyModeChangeable", "power",
                   "isPowerChangeable", "energy", "isEnergyChangeable",
                   "sequenceId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timestamp")) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activityState")) {
      m_activityStateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isActivityStateChangeable")) {
      m_isActivityStateChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "energyMode")) {
      m_energyModeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isEnergyModeChangeable")) {
      m_isEnergyModeChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "power", &m_power)) {
      m_powerIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isPowerChangeable")) {
      m_isPowerChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energy", &m_energy)) {
      m_energyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "isEnergyChangeable")) {
      m_isEnergyChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DirectControlActivityDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_activityStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activityState");
  }
  if (m_isActivityStateChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isActivityStateChangeable");
  }
  if (m_energyModeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("energyMode");
  }
  if (m_isEnergyModeChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isEnergyModeChangeable");
  }
  if (m_powerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("power", m_power);
  }
  if (m_isPowerChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isPowerChangeable");
  }
  if (m_energyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energy", m_energy);
  }
  if (m_isEnergyChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("isEnergyChangeable");
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram