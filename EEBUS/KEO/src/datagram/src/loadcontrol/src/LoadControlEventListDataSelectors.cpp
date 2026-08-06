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

#include <keo_datagram/loadcontrol/LoadControlEventListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlEventListDataSelectors::LoadControlEventListDataSelectors()
    : DataSelectors(), m_timestampIntervalIsSet(false),
      m_timestampInterval(TimestampInterval()), m_eventIdIsSet(false),
      m_eventId(0)

{}

LoadControlEventListDataSelectors::LoadControlEventListDataSelectors(
    const TimestampInterval &c_timestampInterval,
    const xs_unsignedInt &c_eventId)
    : DataSelectors(), m_timestampIntervalIsSet(true),
      m_timestampInterval(c_timestampInterval), m_eventIdIsSet(true),
      m_eventId(c_eventId)

{}

bool LoadControlEventListDataSelectors::
operator==(const LoadControlEventListDataSelectors &c_classObject) const {
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
    return false;
  }
  if (m_eventIdIsSet != c_classObject.m_eventIdIsSet ||
      (m_eventIdIsSet && (m_eventId != c_classObject.m_eventId))) {
    return false;
  }

  return true;
}

bool LoadControlEventListDataSelectors::
operator!=(const LoadControlEventListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlEventListDataSelectors::isEmpty() const {
  return !m_timestampIntervalIsSet && !m_eventIdIsSet;
}

DataSelectors::Type LoadControlEventListDataSelectors::getDataType() const {
  return DataSelectors::Type::LOAD_CONTROL_EVENT_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr LoadControlEventListDataSelectors::clone() const {
  return std::make_shared<LoadControlEventListDataSelectors>(*this);
}

void LoadControlEventListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
LoadControlEventListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void LoadControlEventListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool LoadControlEventListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

void LoadControlEventListDataSelectors::setEventId(
    const xs_unsignedInt &eventId) {
  m_eventId = eventId;
  m_eventIdIsSet = true;
}

const xs_unsignedInt &LoadControlEventListDataSelectors::getEventId() const {
  return m_eventId;
}

void LoadControlEventListDataSelectors::cleanEventId() {
  m_eventId = 0;
  m_eventIdIsSet = false;
}

bool LoadControlEventListDataSelectors::getEventIdIsSet() const {
  return m_eventIdIsSet;
}

bool LoadControlEventListDataSelectors::selects(
    const LoadControlEventData &data) const {
  if (getTimestampIntervalIsSet() &&
      (!data.getTimestampIsSet() ||
       (data.getTimestamp().getDateTime() <
            getTimestampInterval().getStartTime().getDateTime() ||
        data.getTimestamp().getDateTime() >
            getTimestampInterval().getEndTime().getDateTime()))) {
    return false;
  }
  if (getEventIdIsSet() &&
      (!data.getEventIdIsSet() || getEventId() != data.getEventId())) {
    return false;
  }
  return true;
}

bool LoadControlEventListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestampInterval", "eventId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestampInterval", &m_timestampInterval)) {
      m_timestampIntervalIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "eventId", &m_eventId)) {
      m_eventIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlEventListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timestampIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timestampInterval", m_timestampInterval);
  }
  if (m_eventIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("eventId", m_eventId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram