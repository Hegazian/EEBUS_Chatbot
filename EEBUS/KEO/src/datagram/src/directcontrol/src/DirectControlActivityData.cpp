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

#include <keo_datagram/directcontrol/DirectControlActivityData.h>

#include <keo_datagram/directcontrol/DirectControlActivityDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DirectControlActivityData::DirectControlActivityData()
    : m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_activityStateIsSet(false),
      m_activityState(DirectControlActivityState()),
      m_isActivityStateChangeableIsSet(false),
      m_isActivityStateChangeable(false), m_energyModeIsSet(false),
      m_energyMode(EnergyMode()), m_isEnergyModeChangeableIsSet(false),
      m_isEnergyModeChangeable(false), m_powerIsSet(false),
      m_power(ScaledNumber()), m_isPowerChangeableIsSet(false),
      m_isPowerChangeable(false), m_energyIsSet(false),
      m_energy(ScaledNumber()), m_isEnergyChangeableIsSet(false),
      m_isEnergyChangeable(false), m_sequenceIdIsSet(false), m_sequenceId(0)

{}

bool DirectControlActivityData::
operator==(const DirectControlActivityData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_activityStateIsSet != c_classObject.m_activityStateIsSet ||
      (m_activityStateIsSet &&
       (m_activityState != c_classObject.m_activityState))) {
    return false;
  }
  if (m_isActivityStateChangeableIsSet !=
          c_classObject.m_isActivityStateChangeableIsSet ||
      (m_isActivityStateChangeableIsSet &&
       (m_isActivityStateChangeable !=
        c_classObject.m_isActivityStateChangeable))) {
    return false;
  }
  if (m_energyModeIsSet != c_classObject.m_energyModeIsSet ||
      (m_energyModeIsSet && (m_energyMode != c_classObject.m_energyMode))) {
    return false;
  }
  if (m_isEnergyModeChangeableIsSet !=
          c_classObject.m_isEnergyModeChangeableIsSet ||
      (m_isEnergyModeChangeableIsSet &&
       (m_isEnergyModeChangeable != c_classObject.m_isEnergyModeChangeable))) {
    return false;
  }
  if (m_powerIsSet != c_classObject.m_powerIsSet ||
      (m_powerIsSet && (m_power != c_classObject.m_power))) {
    return false;
  }
  if (m_isPowerChangeableIsSet != c_classObject.m_isPowerChangeableIsSet ||
      (m_isPowerChangeableIsSet &&
       (m_isPowerChangeable != c_classObject.m_isPowerChangeable))) {
    return false;
  }
  if (m_energyIsSet != c_classObject.m_energyIsSet ||
      (m_energyIsSet && (m_energy != c_classObject.m_energy))) {
    return false;
  }
  if (m_isEnergyChangeableIsSet != c_classObject.m_isEnergyChangeableIsSet ||
      (m_isEnergyChangeableIsSet &&
       (m_isEnergyChangeable != c_classObject.m_isEnergyChangeable))) {
    return false;
  }
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }

  return true;
}

bool DirectControlActivityData::
operator!=(const DirectControlActivityData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DirectControlActivityData::isEmpty() const {
  return !m_timestampIsSet && !m_activityStateIsSet &&
         !m_isActivityStateChangeableIsSet && !m_energyModeIsSet &&
         !m_isEnergyModeChangeableIsSet && !m_powerIsSet &&
         !m_isPowerChangeableIsSet && !m_energyIsSet &&
         !m_isEnergyChangeableIsSet && !m_sequenceIdIsSet;
}

void DirectControlActivityData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &DirectControlActivityData::getTimestamp() const {
  return m_timestamp;
}

void DirectControlActivityData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool DirectControlActivityData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void DirectControlActivityData::setActivityState(
    const DirectControlActivityState &activityState) {
  m_activityState = activityState;
  m_activityStateIsSet = true;
}

const DirectControlActivityState &
DirectControlActivityData::getActivityState() const {
  return m_activityState;
}

void DirectControlActivityData::cleanActivityState() {
  m_activityState = DirectControlActivityState();
  m_activityStateIsSet = false;
}

bool DirectControlActivityData::getActivityStateIsSet() const {
  return m_activityStateIsSet;
}

void DirectControlActivityData::setIsActivityStateChangeable(
    const xs_boolean &isActivityStateChangeable) {
  m_isActivityStateChangeable = isActivityStateChangeable;
  m_isActivityStateChangeableIsSet = true;
}

const xs_boolean &
DirectControlActivityData::getIsActivityStateChangeable() const {
  return m_isActivityStateChangeable;
}

void DirectControlActivityData::cleanIsActivityStateChangeable() {
  m_isActivityStateChangeable = false;
  m_isActivityStateChangeableIsSet = false;
}

bool DirectControlActivityData::getIsActivityStateChangeableIsSet() const {
  return m_isActivityStateChangeableIsSet;
}

void DirectControlActivityData::setEnergyMode(const EnergyMode &energyMode) {
  m_energyMode = energyMode;
  m_energyModeIsSet = true;
}

const EnergyMode &DirectControlActivityData::getEnergyMode() const {
  return m_energyMode;
}

void DirectControlActivityData::cleanEnergyMode() {
  m_energyMode = EnergyMode();
  m_energyModeIsSet = false;
}

bool DirectControlActivityData::getEnergyModeIsSet() const {
  return m_energyModeIsSet;
}

void DirectControlActivityData::setIsEnergyModeChangeable(
    const xs_boolean &isEnergyModeChangeable) {
  m_isEnergyModeChangeable = isEnergyModeChangeable;
  m_isEnergyModeChangeableIsSet = true;
}

const xs_boolean &DirectControlActivityData::getIsEnergyModeChangeable() const {
  return m_isEnergyModeChangeable;
}

void DirectControlActivityData::cleanIsEnergyModeChangeable() {
  m_isEnergyModeChangeable = false;
  m_isEnergyModeChangeableIsSet = false;
}

bool DirectControlActivityData::getIsEnergyModeChangeableIsSet() const {
  return m_isEnergyModeChangeableIsSet;
}

void DirectControlActivityData::setPower(const ScaledNumber &power) {
  m_power = power;
  m_powerIsSet = true;
}

const ScaledNumber &DirectControlActivityData::getPower() const {
  return m_power;
}

void DirectControlActivityData::cleanPower() {
  m_power = ScaledNumber();
  m_powerIsSet = false;
}

bool DirectControlActivityData::getPowerIsSet() const { return m_powerIsSet; }

void DirectControlActivityData::setIsPowerChangeable(
    const xs_boolean &isPowerChangeable) {
  m_isPowerChangeable = isPowerChangeable;
  m_isPowerChangeableIsSet = true;
}

const xs_boolean &DirectControlActivityData::getIsPowerChangeable() const {
  return m_isPowerChangeable;
}

void DirectControlActivityData::cleanIsPowerChangeable() {
  m_isPowerChangeable = false;
  m_isPowerChangeableIsSet = false;
}

bool DirectControlActivityData::getIsPowerChangeableIsSet() const {
  return m_isPowerChangeableIsSet;
}

void DirectControlActivityData::setEnergy(const ScaledNumber &energy) {
  m_energy = energy;
  m_energyIsSet = true;
}

const ScaledNumber &DirectControlActivityData::getEnergy() const {
  return m_energy;
}

void DirectControlActivityData::cleanEnergy() {
  m_energy = ScaledNumber();
  m_energyIsSet = false;
}

bool DirectControlActivityData::getEnergyIsSet() const { return m_energyIsSet; }

void DirectControlActivityData::setIsEnergyChangeable(
    const xs_boolean &isEnergyChangeable) {
  m_isEnergyChangeable = isEnergyChangeable;
  m_isEnergyChangeableIsSet = true;
}

const xs_boolean &DirectControlActivityData::getIsEnergyChangeable() const {
  return m_isEnergyChangeable;
}

void DirectControlActivityData::cleanIsEnergyChangeable() {
  m_isEnergyChangeable = false;
  m_isEnergyChangeableIsSet = false;
}

bool DirectControlActivityData::getIsEnergyChangeableIsSet() const {
  return m_isEnergyChangeableIsSet;
}

void DirectControlActivityData::setSequenceId(
    const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &DirectControlActivityData::getSequenceId() const {
  return m_sequenceId;
}

void DirectControlActivityData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool DirectControlActivityData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

DirectControlActivityData DirectControlActivityData::reduce(
    const DirectControlActivityDataElements &elements) const {
  DirectControlActivityData dataOut;
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getActivityStateIsSet() && elements.getActivityStateIsSet()) {
    dataOut.setActivityState(getActivityState());
  }
  if (getIsActivityStateChangeableIsSet() &&
      elements.getIsActivityStateChangeableIsSet()) {
    dataOut.setIsActivityStateChangeable(getIsActivityStateChangeable());
  }
  if (getEnergyModeIsSet() && elements.getEnergyModeIsSet()) {
    dataOut.setEnergyMode(getEnergyMode());
  }
  if (getIsEnergyModeChangeableIsSet() &&
      elements.getIsEnergyModeChangeableIsSet()) {
    dataOut.setIsEnergyModeChangeable(getIsEnergyModeChangeable());
  }
  if (getPowerIsSet() && elements.getPowerIsSet()) {
    dataOut.setPower(getPower().reduce(elements.getPower()));
  }
  if (getIsPowerChangeableIsSet() && elements.getIsPowerChangeableIsSet()) {
    dataOut.setIsPowerChangeable(getIsPowerChangeable());
  }
  if (getEnergyIsSet() && elements.getEnergyIsSet()) {
    dataOut.setEnergy(getEnergy().reduce(elements.getEnergy()));
  }
  if (getIsEnergyChangeableIsSet() && elements.getIsEnergyChangeableIsSet()) {
    dataOut.setIsEnergyChangeable(getIsEnergyChangeable());
  }
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  return dataOut;
}

bool DirectControlActivityData::fromJson(KeoJsonValue *json) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestamp", &m_timestamp)) {
      m_timestampIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "activityState", &m_activityState)) {
      m_activityStateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isActivityStateChangeable",
                                   &m_isActivityStateChangeable)) {
      m_isActivityStateChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "energyMode", &m_energyMode)) {
      m_energyModeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isEnergyModeChangeable",
                                   &m_isEnergyModeChangeable)) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isPowerChangeable", &m_isPowerChangeable)) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "isEnergyChangeable",
                                   &m_isEnergyChangeable)) {
      m_isEnergyChangeableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DirectControlActivityData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_activityStateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("activityState", m_activityState);
  }
  if (m_isActivityStateChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isActivityStateChangeable",
                                           m_isActivityStateChangeable);
  }
  if (m_energyModeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energyMode", m_energyMode);
  }
  if (m_isEnergyModeChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isEnergyModeChangeable",
                                           m_isEnergyModeChangeable);
  }
  if (m_powerIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("power", m_power);
  }
  if (m_isPowerChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("isPowerChangeable", m_isPowerChangeable);
  }
  if (m_energyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("energy", m_energy);
  }
  if (m_isEnergyChangeableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("isEnergyChangeable",
                                           m_isEnergyChangeable);
  }
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram