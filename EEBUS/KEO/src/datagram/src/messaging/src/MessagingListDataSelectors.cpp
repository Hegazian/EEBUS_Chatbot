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

#include <keo_datagram/messaging/MessagingListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MessagingListDataSelectors::MessagingListDataSelectors()
    : DataSelectors(), m_timestampIntervalIsSet(false),
      m_timestampInterval(TimestampInterval()), m_messagingNumberIsSet(false),
      m_messagingNumber(0)

{}

MessagingListDataSelectors::MessagingListDataSelectors(
    const TimestampInterval &c_timestampInterval,
    const xs_unsignedInt &c_messagingNumber)
    : DataSelectors(), m_timestampIntervalIsSet(true),
      m_timestampInterval(c_timestampInterval), m_messagingNumberIsSet(true),
      m_messagingNumber(c_messagingNumber)

{}

bool MessagingListDataSelectors::
operator==(const MessagingListDataSelectors &c_classObject) const {
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
    return false;
  }
  if (m_messagingNumberIsSet != c_classObject.m_messagingNumberIsSet ||
      (m_messagingNumberIsSet &&
       (m_messagingNumber != c_classObject.m_messagingNumber))) {
    return false;
  }

  return true;
}

bool MessagingListDataSelectors::
operator!=(const MessagingListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool MessagingListDataSelectors::isEmpty() const {
  return !m_timestampIntervalIsSet && !m_messagingNumberIsSet;
}

DataSelectors::Type MessagingListDataSelectors::getDataType() const {
  return DataSelectors::Type::MESSAGING_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr MessagingListDataSelectors::clone() const {
  return std::make_shared<MessagingListDataSelectors>(*this);
}

void MessagingListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
MessagingListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void MessagingListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool MessagingListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

void MessagingListDataSelectors::setMessagingNumber(
    const xs_unsignedInt &messagingNumber) {
  m_messagingNumber = messagingNumber;
  m_messagingNumberIsSet = true;
}

const xs_unsignedInt &MessagingListDataSelectors::getMessagingNumber() const {
  return m_messagingNumber;
}

void MessagingListDataSelectors::cleanMessagingNumber() {
  m_messagingNumber = 0;
  m_messagingNumberIsSet = false;
}

bool MessagingListDataSelectors::getMessagingNumberIsSet() const {
  return m_messagingNumberIsSet;
}

bool MessagingListDataSelectors::selects(const MessagingData &data) const {
  if (getTimestampIntervalIsSet() &&
      (!data.getTimestampIsSet() ||
       (data.getTimestamp().getDateTime() <
            getTimestampInterval().getStartTime().getDateTime() ||
        data.getTimestamp().getDateTime() >
            getTimestampInterval().getEndTime().getDateTime()))) {
    return false;
  }
  if (getMessagingNumberIsSet() &&
      (!data.getMessagingNumberIsSet() ||
       getMessagingNumber() != data.getMessagingNumber())) {
    return false;
  }
  return true;
}

bool MessagingListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestampInterval", "messagingNumber"})) {
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
                                   "messagingNumber", &m_messagingNumber)) {
      m_messagingNumberIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MessagingListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timestampIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timestampInterval", m_timestampInterval);
  }
  if (m_messagingNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("messagingNumber", m_messagingNumber);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram