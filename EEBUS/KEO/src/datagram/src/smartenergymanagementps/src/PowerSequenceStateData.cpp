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

#include <keo_datagram/smartenergymanagementps/PowerSequenceStateData.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceStateData::PowerSequenceStateData()
    : m_sequenceIdIsSet(false), m_sequenceId(0), m_stateIsSet(false),
      m_state(PowerSequenceState()), m_activeSlotNumberIsSet(false),
      m_activeSlotNumber(0), m_elapsedSlotTimeIsSet(false),
      m_elapsedSlotTime(xs_duration()), m_remainingSlotTimeIsSet(false),
      m_remainingSlotTime(xs_duration()),
      m_sequenceRemoteControllableIsSet(false),
      m_sequenceRemoteControllable(false), m_activeRepetitionNumberIsSet(false),
      m_activeRepetitionNumber(0), m_remainingPauseTimeIsSet(false),
      m_remainingPauseTime(xs_duration())

{}

bool PowerSequenceStateData::
operator==(const PowerSequenceStateData &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet ||
      (m_sequenceIdIsSet && (m_sequenceId != c_classObject.m_sequenceId))) {
    return false;
  }
  if (m_stateIsSet != c_classObject.m_stateIsSet ||
      (m_stateIsSet && (m_state != c_classObject.m_state))) {
    return false;
  }
  if (m_activeSlotNumberIsSet != c_classObject.m_activeSlotNumberIsSet ||
      (m_activeSlotNumberIsSet &&
       (m_activeSlotNumber != c_classObject.m_activeSlotNumber))) {
    return false;
  }
  if (m_elapsedSlotTimeIsSet != c_classObject.m_elapsedSlotTimeIsSet ||
      (m_elapsedSlotTimeIsSet &&
       (m_elapsedSlotTime != c_classObject.m_elapsedSlotTime))) {
    return false;
  }
  if (m_remainingSlotTimeIsSet != c_classObject.m_remainingSlotTimeIsSet ||
      (m_remainingSlotTimeIsSet &&
       (m_remainingSlotTime != c_classObject.m_remainingSlotTime))) {
    return false;
  }
  if (m_sequenceRemoteControllableIsSet !=
          c_classObject.m_sequenceRemoteControllableIsSet ||
      (m_sequenceRemoteControllableIsSet &&
       (m_sequenceRemoteControllable !=
        c_classObject.m_sequenceRemoteControllable))) {
    return false;
  }
  if (m_activeRepetitionNumberIsSet !=
          c_classObject.m_activeRepetitionNumberIsSet ||
      (m_activeRepetitionNumberIsSet &&
       (m_activeRepetitionNumber != c_classObject.m_activeRepetitionNumber))) {
    return false;
  }
  if (m_remainingPauseTimeIsSet != c_classObject.m_remainingPauseTimeIsSet ||
      (m_remainingPauseTimeIsSet &&
       (m_remainingPauseTime != c_classObject.m_remainingPauseTime))) {
    return false;
  }

  return true;
}

bool PowerSequenceStateData::
operator!=(const PowerSequenceStateData &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceStateData::isEmpty() const {
  return !m_sequenceIdIsSet && !m_stateIsSet && !m_activeSlotNumberIsSet &&
         !m_elapsedSlotTimeIsSet && !m_remainingSlotTimeIsSet &&
         !m_sequenceRemoteControllableIsSet && !m_activeRepetitionNumberIsSet &&
         !m_remainingPauseTimeIsSet;
}

void PowerSequenceStateData::setSequenceId(const xs_unsignedInt &sequenceId) {
  m_sequenceId = sequenceId;
  m_sequenceIdIsSet = true;
}

const xs_unsignedInt &PowerSequenceStateData::getSequenceId() const {
  return m_sequenceId;
}

void PowerSequenceStateData::cleanSequenceId() {
  m_sequenceId = 0;
  m_sequenceIdIsSet = false;
}

bool PowerSequenceStateData::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceStateData::setState(const PowerSequenceState &state) {
  m_state = state;
  m_stateIsSet = true;
}

const PowerSequenceState &PowerSequenceStateData::getState() const {
  return m_state;
}

void PowerSequenceStateData::cleanState() {
  m_state = PowerSequenceState();
  m_stateIsSet = false;
}

bool PowerSequenceStateData::getStateIsSet() const { return m_stateIsSet; }

void PowerSequenceStateData::setActiveSlotNumber(
    const xs_unsignedInt &activeSlotNumber) {
  m_activeSlotNumber = activeSlotNumber;
  m_activeSlotNumberIsSet = true;
}

const xs_unsignedInt &PowerSequenceStateData::getActiveSlotNumber() const {
  return m_activeSlotNumber;
}

void PowerSequenceStateData::cleanActiveSlotNumber() {
  m_activeSlotNumber = 0;
  m_activeSlotNumberIsSet = false;
}

bool PowerSequenceStateData::getActiveSlotNumberIsSet() const {
  return m_activeSlotNumberIsSet;
}

void PowerSequenceStateData::setElapsedSlotTime(
    const xs_duration &elapsedSlotTime) {
  m_elapsedSlotTime = elapsedSlotTime;
  m_elapsedSlotTimeIsSet = true;
}

const xs_duration &PowerSequenceStateData::getElapsedSlotTime() const {
  return m_elapsedSlotTime;
}

void PowerSequenceStateData::cleanElapsedSlotTime() {
  m_elapsedSlotTime = xs_duration();
  m_elapsedSlotTimeIsSet = false;
}

bool PowerSequenceStateData::getElapsedSlotTimeIsSet() const {
  return m_elapsedSlotTimeIsSet;
}

void PowerSequenceStateData::setRemainingSlotTime(
    const xs_duration &remainingSlotTime) {
  m_remainingSlotTime = remainingSlotTime;
  m_remainingSlotTimeIsSet = true;
}

const xs_duration &PowerSequenceStateData::getRemainingSlotTime() const {
  return m_remainingSlotTime;
}

void PowerSequenceStateData::cleanRemainingSlotTime() {
  m_remainingSlotTime = xs_duration();
  m_remainingSlotTimeIsSet = false;
}

bool PowerSequenceStateData::getRemainingSlotTimeIsSet() const {
  return m_remainingSlotTimeIsSet;
}

void PowerSequenceStateData::setSequenceRemoteControllable(
    const xs_boolean &sequenceRemoteControllable) {
  m_sequenceRemoteControllable = sequenceRemoteControllable;
  m_sequenceRemoteControllableIsSet = true;
}

const xs_boolean &
PowerSequenceStateData::getSequenceRemoteControllable() const {
  return m_sequenceRemoteControllable;
}

void PowerSequenceStateData::cleanSequenceRemoteControllable() {
  m_sequenceRemoteControllable = false;
  m_sequenceRemoteControllableIsSet = false;
}

bool PowerSequenceStateData::getSequenceRemoteControllableIsSet() const {
  return m_sequenceRemoteControllableIsSet;
}

void PowerSequenceStateData::setActiveRepetitionNumber(
    const xs_unsignedInt &activeRepetitionNumber) {
  m_activeRepetitionNumber = activeRepetitionNumber;
  m_activeRepetitionNumberIsSet = true;
}

const xs_unsignedInt &
PowerSequenceStateData::getActiveRepetitionNumber() const {
  return m_activeRepetitionNumber;
}

void PowerSequenceStateData::cleanActiveRepetitionNumber() {
  m_activeRepetitionNumber = 0;
  m_activeRepetitionNumberIsSet = false;
}

bool PowerSequenceStateData::getActiveRepetitionNumberIsSet() const {
  return m_activeRepetitionNumberIsSet;
}

void PowerSequenceStateData::setRemainingPauseTime(
    const xs_duration &remainingPauseTime) {
  m_remainingPauseTime = remainingPauseTime;
  m_remainingPauseTimeIsSet = true;
}

const xs_duration &PowerSequenceStateData::getRemainingPauseTime() const {
  return m_remainingPauseTime;
}

void PowerSequenceStateData::cleanRemainingPauseTime() {
  m_remainingPauseTime = xs_duration();
  m_remainingPauseTimeIsSet = false;
}

bool PowerSequenceStateData::getRemainingPauseTimeIsSet() const {
  return m_remainingPauseTimeIsSet;
}

PowerSequenceStateData PowerSequenceStateData::reduce(
    const PowerSequenceStateDataElements &elements) const {
  PowerSequenceStateData dataOut;
  if (getSequenceIdIsSet() && elements.getSequenceIdIsSet()) {
    dataOut.setSequenceId(getSequenceId());
  }
  if (getStateIsSet() && elements.getStateIsSet()) {
    dataOut.setState(getState());
  }
  if (getActiveSlotNumberIsSet() && elements.getActiveSlotNumberIsSet()) {
    dataOut.setActiveSlotNumber(getActiveSlotNumber());
  }
  if (getElapsedSlotTimeIsSet() && elements.getElapsedSlotTimeIsSet()) {
    dataOut.setElapsedSlotTime(getElapsedSlotTime());
  }
  if (getRemainingSlotTimeIsSet() && elements.getRemainingSlotTimeIsSet()) {
    dataOut.setRemainingSlotTime(getRemainingSlotTime());
  }
  if (getSequenceRemoteControllableIsSet() &&
      elements.getSequenceRemoteControllableIsSet()) {
    dataOut.setSequenceRemoteControllable(getSequenceRemoteControllable());
  }
  if (getActiveRepetitionNumberIsSet() &&
      elements.getActiveRepetitionNumberIsSet()) {
    dataOut.setActiveRepetitionNumber(getActiveRepetitionNumber());
  }
  if (getRemainingPauseTimeIsSet() && elements.getRemainingPauseTimeIsSet()) {
    dataOut.setRemainingPauseTime(getRemainingPauseTime());
  }
  return dataOut;
}

bool PowerSequenceStateData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "state", "activeSlotNumber", "elapsedSlotTime",
                   "remainingSlotTime", "sequenceRemoteControllable",
                   "activeRepetitionNumber", "remainingPauseTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceId", &m_sequenceId)) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "state", &m_state)) {
      m_stateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "activeSlotNumber", &m_activeSlotNumber)) {
      m_activeSlotNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "elapsedSlotTime", &m_elapsedSlotTime)) {
      m_elapsedSlotTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "remainingSlotTime", &m_remainingSlotTime)) {
      m_remainingSlotTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "sequenceRemoteControllable",
                                   &m_sequenceRemoteControllable)) {
      m_sequenceRemoteControllableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "activeRepetitionNumber",
                                   &m_activeRepetitionNumber)) {
      m_activeRepetitionNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "remainingPauseTime",
                                   &m_remainingPauseTime)) {
      m_remainingPauseTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceStateData::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceId", m_sequenceId);
  }
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("state", m_state);
  }
  if (m_activeSlotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("activeSlotNumber", m_activeSlotNumber);
  }
  if (m_elapsedSlotTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("elapsedSlotTime", m_elapsedSlotTime);
  }
  if (m_remainingSlotTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("remainingSlotTime", m_remainingSlotTime);
  }
  if (m_sequenceRemoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("sequenceRemoteControllable",
                                           m_sequenceRemoteControllable);
  }
  if (m_activeRepetitionNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("activeRepetitionNumber",
                                           m_activeRepetitionNumber);
  }
  if (m_remainingPauseTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("remainingPauseTime",
                                           m_remainingPauseTime);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram