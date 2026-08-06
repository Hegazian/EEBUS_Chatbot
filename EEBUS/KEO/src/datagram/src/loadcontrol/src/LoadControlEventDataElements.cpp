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

#include <keo_datagram/loadcontrol/LoadControlEventDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlEventDataElements::LoadControlEventDataElements()
    : DataElements(), m_timestampIsSet(false), m_eventIdIsSet(false),
      m_eventActionConsumeIsSet(false), m_eventActionProduceIsSet(false),
      m_timePeriodIsSet(false), m_timePeriod(TimePeriodElements())

{}

bool LoadControlEventDataElements::
operator==(const LoadControlEventDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_eventIdIsSet != c_classObject.m_eventIdIsSet) {
    return false;
  }
  if (m_eventActionConsumeIsSet != c_classObject.m_eventActionConsumeIsSet) {
    return false;
  }
  if (m_eventActionProduceIsSet != c_classObject.m_eventActionProduceIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }

  return true;
}

bool LoadControlEventDataElements::
operator!=(const LoadControlEventDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlEventDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_eventIdIsSet && !m_eventActionConsumeIsSet &&
         !m_eventActionProduceIsSet && !m_timePeriodIsSet;
}

DataElements::Type LoadControlEventDataElements::getDataType() const {
  return DataElements::Type::LOAD_CONTROL_EVENT_DATA_ELEMENTS_TYPE;
}

DataElementsPtr LoadControlEventDataElements::clone() const {
  return std::make_shared<LoadControlEventDataElements>(*this);
}

void LoadControlEventDataElements::setTimestamp() { m_timestampIsSet = true; }

void LoadControlEventDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool LoadControlEventDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void LoadControlEventDataElements::setEventId() { m_eventIdIsSet = true; }

void LoadControlEventDataElements::cleanEventId() { m_eventIdIsSet = false; }

bool LoadControlEventDataElements::getEventIdIsSet() const {
  return m_eventIdIsSet;
}

void LoadControlEventDataElements::setEventActionConsume() {
  m_eventActionConsumeIsSet = true;
}

void LoadControlEventDataElements::cleanEventActionConsume() {
  m_eventActionConsumeIsSet = false;
}

bool LoadControlEventDataElements::getEventActionConsumeIsSet() const {
  return m_eventActionConsumeIsSet;
}

void LoadControlEventDataElements::setEventActionProduce() {
  m_eventActionProduceIsSet = true;
}

void LoadControlEventDataElements::cleanEventActionProduce() {
  m_eventActionProduceIsSet = false;
}

bool LoadControlEventDataElements::getEventActionProduceIsSet() const {
  return m_eventActionProduceIsSet;
}

void LoadControlEventDataElements::setTimePeriod(
    const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &LoadControlEventDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void LoadControlEventDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool LoadControlEventDataElements::getTimePeriodIsSet() const {
  return m_timePeriodIsSet;
}

bool LoadControlEventDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "eventId", "eventActionConsume",
                   "eventActionProduce", "timePeriod"})) {
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
                                     "eventId")) {
      m_eventIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "eventActionConsume")) {
      m_eventActionConsumeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "eventActionProduce")) {
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

std::string LoadControlEventDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_eventIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventId");
  }
  if (m_eventActionConsumeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventActionConsume");
  }
  if (m_eventActionProduceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventActionProduce");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram