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

#include <keo_datagram/loadcontrol/LoadControlEventData.h>

#include <keo_datagram/loadcontrol/LoadControlEventDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlEventData::LoadControlEventData()
    : m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_eventIdIsSet(false), m_eventId(0), m_eventActionConsumeIsSet(false),
      m_eventActionConsume(LoadControlEventAction()),
      m_eventActionProduceIsSet(false),
      m_eventActionProduce(LoadControlEventAction()), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod())

{}

bool LoadControlEventData::
operator==(const LoadControlEventData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_eventIdIsSet != c_classObject.m_eventIdIsSet ||
      (m_eventIdIsSet && (m_eventId != c_classObject.m_eventId))) {
    return false;
  }
  if (m_eventActionConsumeIsSet != c_classObject.m_eventActionConsumeIsSet ||
      (m_eventActionConsumeIsSet &&
       (m_eventActionConsume != c_classObject.m_eventActionConsume))) {
    return false;
  }
  if (m_eventActionProduceIsSet != c_classObject.m_eventActionProduceIsSet ||
      (m_eventActionProduceIsSet &&
       (m_eventActionProduce != c_classObject.m_eventActionProduce))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }

  return true;
}

bool LoadControlEventData::
operator!=(const LoadControlEventData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlEventData::isEmpty() const {
  return !m_timestampIsSet && !m_eventIdIsSet && !m_eventActionConsumeIsSet &&
         !m_eventActionProduceIsSet && !m_timePeriodIsSet;
}

void LoadControlEventData::setTimestamp(
    const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &LoadControlEventData::getTimestamp() const {
  return m_timestamp;
}

void LoadControlEventData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool LoadControlEventData::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void LoadControlEventData::setEventId(const xs_unsignedInt &eventId) {
  m_eventId = eventId;
  m_eventIdIsSet = true;
}

const xs_unsignedInt &LoadControlEventData::getEventId() const {
  return m_eventId;
}

void LoadControlEventData::cleanEventId() {
  m_eventId = 0;
  m_eventIdIsSet = false;
}

bool LoadControlEventData::getEventIdIsSet() const { return m_eventIdIsSet; }

void LoadControlEventData::setEventActionConsume(
    const LoadControlEventAction &eventActionConsume) {
  m_eventActionConsume = eventActionConsume;
  m_eventActionConsumeIsSet = true;
}

const LoadControlEventAction &
LoadControlEventData::getEventActionConsume() const {
  return m_eventActionConsume;
}

void LoadControlEventData::cleanEventActionConsume() {
  m_eventActionConsume = LoadControlEventAction();
  m_eventActionConsumeIsSet = false;
}

bool LoadControlEventData::getEventActionConsumeIsSet() const {
  return m_eventActionConsumeIsSet;
}

void LoadControlEventData::setEventActionProduce(
    const LoadControlEventAction &eventActionProduce) {
  m_eventActionProduce = eventActionProduce;
  m_eventActionProduceIsSet = true;
}

const LoadControlEventAction &
LoadControlEventData::getEventActionProduce() const {
  return m_eventActionProduce;
}

void LoadControlEventData::cleanEventActionProduce() {
  m_eventActionProduce = LoadControlEventAction();
  m_eventActionProduceIsSet = false;
}

bool LoadControlEventData::getEventActionProduceIsSet() const {
  return m_eventActionProduceIsSet;
}

void LoadControlEventData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &LoadControlEventData::getTimePeriod() const {
  return m_timePeriod;
}

void LoadControlEventData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool LoadControlEventData::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

LoadControlEventData LoadControlEventData::reduce(
    const LoadControlEventDataElements &elements) const {
  LoadControlEventData dataOut;
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getEventIdIsSet() && elements.getEventIdIsSet()) {
    dataOut.setEventId(getEventId());
  }
  if (getEventActionConsumeIsSet() && elements.getEventActionConsumeIsSet()) {
    dataOut.setEventActionConsume(getEventActionConsume());
  }
  if (getEventActionProduceIsSet() && elements.getEventActionProduceIsSet()) {
    dataOut.setEventActionProduce(getEventActionProduce());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  return dataOut;
}

bool LoadControlEventData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "eventId", "eventActionConsume",
                   "eventActionProduce", "timePeriod"})) {
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
                                   "eventActionConsume",
                                   &m_eventActionConsume)) {
      m_eventActionConsumeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "eventActionProduce",
                                   &m_eventActionProduce)) {
      m_eventActionProduceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlEventData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_eventIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventId", m_eventId);
  }
  if (m_eventActionConsumeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventActionConsume",
                                           m_eventActionConsume);
  }
  if (m_eventActionProduceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventActionProduce",
                                           m_eventActionProduce);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram