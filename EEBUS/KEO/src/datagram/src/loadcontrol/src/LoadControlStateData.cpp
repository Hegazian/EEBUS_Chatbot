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

#include <keo_datagram/loadcontrol/LoadControlStateData.h>

#include <keo_datagram/loadcontrol/LoadControlStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlStateData::LoadControlStateData()
    : m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_eventIdIsSet(false), m_eventId(0), m_eventStateConsumeIsSet(false),
      m_eventStateConsume(LoadControlEventState()),
      m_appliedEventActionConsumeIsSet(false),
      m_appliedEventActionConsume(LoadControlEventAction()),
      m_eventStateProduceIsSet(false),
      m_eventStateProduce(LoadControlEventState()),
      m_appliedEventActionProduceIsSet(false),
      m_appliedEventActionProduce(LoadControlEventAction())

{}

bool LoadControlStateData::
operator==(const LoadControlStateData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_eventIdIsSet != c_classObject.m_eventIdIsSet ||
      (m_eventIdIsSet && (m_eventId != c_classObject.m_eventId))) {
    return false;
  }
  if (m_eventStateConsumeIsSet != c_classObject.m_eventStateConsumeIsSet ||
      (m_eventStateConsumeIsSet &&
       (m_eventStateConsume != c_classObject.m_eventStateConsume))) {
    return false;
  }
  if (m_appliedEventActionConsumeIsSet !=
          c_classObject.m_appliedEventActionConsumeIsSet ||
      (m_appliedEventActionConsumeIsSet &&
       (m_appliedEventActionConsume !=
        c_classObject.m_appliedEventActionConsume))) {
    return false;
  }
  if (m_eventStateProduceIsSet != c_classObject.m_eventStateProduceIsSet ||
      (m_eventStateProduceIsSet &&
       (m_eventStateProduce != c_classObject.m_eventStateProduce))) {
    return false;
  }
  if (m_appliedEventActionProduceIsSet !=
          c_classObject.m_appliedEventActionProduceIsSet ||
      (m_appliedEventActionProduceIsSet &&
       (m_appliedEventActionProduce !=
        c_classObject.m_appliedEventActionProduce))) {
    return false;
  }

  return true;
}

bool LoadControlStateData::
operator!=(const LoadControlStateData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlStateData::isEmpty() const {
  return !m_timestampIsSet && !m_eventIdIsSet && !m_eventStateConsumeIsSet &&
         !m_appliedEventActionConsumeIsSet && !m_eventStateProduceIsSet &&
         !m_appliedEventActionProduceIsSet;
}

void LoadControlStateData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &LoadControlStateData::getTimestamp() const {
  return m_timestamp;
}

void LoadControlStateData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool LoadControlStateData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void LoadControlStateData::setEventId(const xs_unsignedInt &eventId) {
  m_eventId = eventId;
  m_eventIdIsSet = true;
}

const xs_unsignedInt &LoadControlStateData::getEventId() const {
  return m_eventId;
}

void LoadControlStateData::cleanEventId() {
  m_eventId = 0;
  m_eventIdIsSet = false;
}

bool LoadControlStateData::getEventIdIsSet() const { return m_eventIdIsSet; }

void LoadControlStateData::setEventStateConsume(
    const LoadControlEventState &eventStateConsume) {
  m_eventStateConsume = eventStateConsume;
  m_eventStateConsumeIsSet = true;
}

const LoadControlEventState &
LoadControlStateData::getEventStateConsume() const {
  return m_eventStateConsume;
}

void LoadControlStateData::cleanEventStateConsume() {
  m_eventStateConsume = LoadControlEventState();
  m_eventStateConsumeIsSet = false;
}

bool LoadControlStateData::getEventStateConsumeIsSet() const {
  return m_eventStateConsumeIsSet;
}

void LoadControlStateData::setAppliedEventActionConsume(
    const LoadControlEventAction &appliedEventActionConsume) {
  m_appliedEventActionConsume = appliedEventActionConsume;
  m_appliedEventActionConsumeIsSet = true;
}

const LoadControlEventAction &
LoadControlStateData::getAppliedEventActionConsume() const {
  return m_appliedEventActionConsume;
}

void LoadControlStateData::cleanAppliedEventActionConsume() {
  m_appliedEventActionConsume = LoadControlEventAction();
  m_appliedEventActionConsumeIsSet = false;
}

bool LoadControlStateData::getAppliedEventActionConsumeIsSet() const {
  return m_appliedEventActionConsumeIsSet;
}

void LoadControlStateData::setEventStateProduce(
    const LoadControlEventState &eventStateProduce) {
  m_eventStateProduce = eventStateProduce;
  m_eventStateProduceIsSet = true;
}

const LoadControlEventState &
LoadControlStateData::getEventStateProduce() const {
  return m_eventStateProduce;
}

void LoadControlStateData::cleanEventStateProduce() {
  m_eventStateProduce = LoadControlEventState();
  m_eventStateProduceIsSet = false;
}

bool LoadControlStateData::getEventStateProduceIsSet() const {
  return m_eventStateProduceIsSet;
}

void LoadControlStateData::setAppliedEventActionProduce(
    const LoadControlEventAction &appliedEventActionProduce) {
  m_appliedEventActionProduce = appliedEventActionProduce;
  m_appliedEventActionProduceIsSet = true;
}

const LoadControlEventAction &
LoadControlStateData::getAppliedEventActionProduce() const {
  return m_appliedEventActionProduce;
}

void LoadControlStateData::cleanAppliedEventActionProduce() {
  m_appliedEventActionProduce = LoadControlEventAction();
  m_appliedEventActionProduceIsSet = false;
}

bool LoadControlStateData::getAppliedEventActionProduceIsSet() const {
  return m_appliedEventActionProduceIsSet;
}

LoadControlStateData LoadControlStateData::reduce(
    const LoadControlStateDataElements &elements) const {
  LoadControlStateData dataOut;
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getEventIdIsSet() && elements.getEventIdIsSet()) {
    dataOut.setEventId(getEventId());
  }
  if (getEventStateConsumeIsSet() && elements.getEventStateConsumeIsSet()) {
    dataOut.setEventStateConsume(getEventStateConsume());
  }
  if (getAppliedEventActionConsumeIsSet() &&
      elements.getAppliedEventActionConsumeIsSet()) {
    dataOut.setAppliedEventActionConsume(getAppliedEventActionConsume());
  }
  if (getEventStateProduceIsSet() && elements.getEventStateProduceIsSet()) {
    dataOut.setEventStateProduce(getEventStateProduce());
  }
  if (getAppliedEventActionProduceIsSet() &&
      elements.getAppliedEventActionProduceIsSet()) {
    dataOut.setAppliedEventActionProduce(getAppliedEventActionProduce());
  }
  return dataOut;
}

bool LoadControlStateData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "eventId", "eventStateConsume",
                   "appliedEventActionConsume", "eventStateProduce",
                   "appliedEventActionProduce"})) {
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
                                   "eventId", &m_eventId)) {
      m_eventIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "eventStateConsume", &m_eventStateConsume)) {
      m_eventStateConsumeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "appliedEventActionConsume",
                                   &m_appliedEventActionConsume)) {
      m_appliedEventActionConsumeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "eventStateProduce", &m_eventStateProduce)) {
      m_eventStateProduceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "appliedEventActionProduce",
                                   &m_appliedEventActionProduce)) {
      m_appliedEventActionProduceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlStateData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_eventIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventId", m_eventId);
  }
  if (m_eventStateConsumeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("eventStateConsume", m_eventStateConsume);
  }
  if (m_appliedEventActionConsumeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("appliedEventActionConsume",
                                           m_appliedEventActionConsume);
  }
  if (m_eventStateProduceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("eventStateProduce", m_eventStateProduce);
  }
  if (m_appliedEventActionProduceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("appliedEventActionProduce",
                                           m_appliedEventActionProduce);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram