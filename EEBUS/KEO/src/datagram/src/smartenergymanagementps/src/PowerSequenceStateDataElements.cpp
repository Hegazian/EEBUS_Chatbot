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

#include <keo_datagram/smartenergymanagementps/PowerSequenceStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

PowerSequenceStateDataElements::PowerSequenceStateDataElements()
    : DataElements(), m_sequenceIdIsSet(false), m_stateIsSet(false),
      m_activeSlotNumberIsSet(false), m_elapsedSlotTimeIsSet(false),
      m_remainingSlotTimeIsSet(false), m_sequenceRemoteControllableIsSet(false),
      m_activeRepetitionNumberIsSet(false), m_remainingPauseTimeIsSet(false)

{}

bool PowerSequenceStateDataElements::
operator==(const PowerSequenceStateDataElements &c_classObject) const {
  if (m_sequenceIdIsSet != c_classObject.m_sequenceIdIsSet) {
    return false;
  }
  if (m_stateIsSet != c_classObject.m_stateIsSet) {
    return false;
  }
  if (m_activeSlotNumberIsSet != c_classObject.m_activeSlotNumberIsSet) {
    return false;
  }
  if (m_elapsedSlotTimeIsSet != c_classObject.m_elapsedSlotTimeIsSet) {
    return false;
  }
  if (m_remainingSlotTimeIsSet != c_classObject.m_remainingSlotTimeIsSet) {
    return false;
  }
  if (m_sequenceRemoteControllableIsSet !=
      c_classObject.m_sequenceRemoteControllableIsSet) {
    return false;
  }
  if (m_activeRepetitionNumberIsSet !=
      c_classObject.m_activeRepetitionNumberIsSet) {
    return false;
  }
  if (m_remainingPauseTimeIsSet != c_classObject.m_remainingPauseTimeIsSet) {
    return false;
  }

  return true;
}

bool PowerSequenceStateDataElements::
operator!=(const PowerSequenceStateDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool PowerSequenceStateDataElements::isEmpty() const {
  return !m_sequenceIdIsSet && !m_stateIsSet && !m_activeSlotNumberIsSet &&
         !m_elapsedSlotTimeIsSet && !m_remainingSlotTimeIsSet &&
         !m_sequenceRemoteControllableIsSet && !m_activeRepetitionNumberIsSet &&
         !m_remainingPauseTimeIsSet;
}

DataElements::Type PowerSequenceStateDataElements::getDataType() const {
  return DataElements::Type::POWER_SEQUENCE_STATE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr PowerSequenceStateDataElements::clone() const {
  return std::make_shared<PowerSequenceStateDataElements>(*this);
}

void PowerSequenceStateDataElements::setSequenceId() {
  m_sequenceIdIsSet = true;
}

void PowerSequenceStateDataElements::cleanSequenceId() {
  m_sequenceIdIsSet = false;
}

bool PowerSequenceStateDataElements::getSequenceIdIsSet() const {
  return m_sequenceIdIsSet;
}

void PowerSequenceStateDataElements::setState() { m_stateIsSet = true; }

void PowerSequenceStateDataElements::cleanState() { m_stateIsSet = false; }

bool PowerSequenceStateDataElements::getStateIsSet() const {
  return m_stateIsSet;
}

void PowerSequenceStateDataElements::setActiveSlotNumber() {
  m_activeSlotNumberIsSet = true;
}

void PowerSequenceStateDataElements::cleanActiveSlotNumber() {
  m_activeSlotNumberIsSet = false;
}

bool PowerSequenceStateDataElements::getActiveSlotNumberIsSet() const {
  return m_activeSlotNumberIsSet;
}

void PowerSequenceStateDataElements::setElapsedSlotTime() {
  m_elapsedSlotTimeIsSet = true;
}

void PowerSequenceStateDataElements::cleanElapsedSlotTime() {
  m_elapsedSlotTimeIsSet = false;
}

bool PowerSequenceStateDataElements::getElapsedSlotTimeIsSet() const {
  return m_elapsedSlotTimeIsSet;
}

void PowerSequenceStateDataElements::setRemainingSlotTime() {
  m_remainingSlotTimeIsSet = true;
}

void PowerSequenceStateDataElements::cleanRemainingSlotTime() {
  m_remainingSlotTimeIsSet = false;
}

bool PowerSequenceStateDataElements::getRemainingSlotTimeIsSet() const {
  return m_remainingSlotTimeIsSet;
}

void PowerSequenceStateDataElements::setSequenceRemoteControllable() {
  m_sequenceRemoteControllableIsSet = true;
}

void PowerSequenceStateDataElements::cleanSequenceRemoteControllable() {
  m_sequenceRemoteControllableIsSet = false;
}

bool PowerSequenceStateDataElements::getSequenceRemoteControllableIsSet()
    const {
  return m_sequenceRemoteControllableIsSet;
}

void PowerSequenceStateDataElements::setActiveRepetitionNumber() {
  m_activeRepetitionNumberIsSet = true;
}

void PowerSequenceStateDataElements::cleanActiveRepetitionNumber() {
  m_activeRepetitionNumberIsSet = false;
}

bool PowerSequenceStateDataElements::getActiveRepetitionNumberIsSet() const {
  return m_activeRepetitionNumberIsSet;
}

void PowerSequenceStateDataElements::setRemainingPauseTime() {
  m_remainingPauseTimeIsSet = true;
}

void PowerSequenceStateDataElements::cleanRemainingPauseTime() {
  m_remainingPauseTimeIsSet = false;
}

bool PowerSequenceStateDataElements::getRemainingPauseTimeIsSet() const {
  return m_remainingPauseTimeIsSet;
}

bool PowerSequenceStateDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"sequenceId", "state", "activeSlotNumber", "elapsedSlotTime",
                   "remainingSlotTime", "sequenceRemoteControllable",
                   "activeRepetitionNumber", "remainingPauseTime"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceId")) {
      m_sequenceIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "state")) {
      m_stateIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activeSlotNumber")) {
      m_activeSlotNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "elapsedSlotTime")) {
      m_elapsedSlotTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "remainingSlotTime")) {
      m_remainingSlotTimeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sequenceRemoteControllable")) {
      m_sequenceRemoteControllableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activeRepetitionNumber")) {
      m_activeRepetitionNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "remainingPauseTime")) {
      m_remainingPauseTimeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string PowerSequenceStateDataElements::toJson() const {
  std::string result = "[";
  if (m_sequenceIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceId");
  }
  if (m_stateIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("state");
  }
  if (m_activeSlotNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeSlotNumber");
  }
  if (m_elapsedSlotTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("elapsedSlotTime");
  }
  if (m_remainingSlotTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("remainingSlotTime");
  }
  if (m_sequenceRemoteControllableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sequenceRemoteControllable");
  }
  if (m_activeRepetitionNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeRepetitionNumber");
  }
  if (m_remainingPauseTimeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("remainingPauseTime");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram