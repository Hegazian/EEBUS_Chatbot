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

#include <keo_datagram/messaging/MessagingData.h>

#include <keo_datagram/messaging/MessagingDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MessagingData::MessagingData()
    : m_timestampIsSet(false), m_timestamp(AbsoluteOrRelativeTime()),
      m_messagingNumberIsSet(false), m_messagingNumber(0), m_typeIsSet(false),
      m_type(MessagingType()), m_textIsSet(false), m_text("")

{}

bool MessagingData::operator==(const MessagingData &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet ||
      (m_timestampIsSet && (m_timestamp != c_classObject.m_timestamp))) {
    return false;
  }
  if (m_messagingNumberIsSet != c_classObject.m_messagingNumberIsSet ||
      (m_messagingNumberIsSet &&
       (m_messagingNumber != c_classObject.m_messagingNumber))) {
    return false;
  }
  if (m_typeIsSet != c_classObject.m_typeIsSet ||
      (m_typeIsSet && (m_type != c_classObject.m_type))) {
    return false;
  }
  if (m_textIsSet != c_classObject.m_textIsSet ||
      (m_textIsSet && (m_text != c_classObject.m_text))) {
    return false;
  }

  return true;
}

bool MessagingData::operator!=(const MessagingData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MessagingData::isEmpty() const {
  return !m_timestampIsSet && !m_messagingNumberIsSet && !m_typeIsSet &&
         !m_textIsSet;
}

void MessagingData::setTimestamp(const AbsoluteOrRelativeTime &timestamp) {
  m_timestamp = timestamp;
  m_timestampIsSet = true;
}

const AbsoluteOrRelativeTime &MessagingData::getTimestamp() const {
  return m_timestamp;
}

void MessagingData::cleanTimestamp() {
  m_timestamp = AbsoluteOrRelativeTime();
  m_timestampIsSet = false;
}

bool MessagingData::getTimestampIsSet() const { return m_timestampIsSet; }

void MessagingData::setMessagingNumber(const xs_unsignedInt &messagingNumber) {
  m_messagingNumber = messagingNumber;
  m_messagingNumberIsSet = true;
}

const xs_unsignedInt &MessagingData::getMessagingNumber() const {
  return m_messagingNumber;
}

void MessagingData::cleanMessagingNumber() {
  m_messagingNumber = 0;
  m_messagingNumberIsSet = false;
}

bool MessagingData::getMessagingNumberIsSet() const {
  return m_messagingNumberIsSet;
}

void MessagingData::setType(const MessagingType &type) {
  m_type = type;
  m_typeIsSet = true;
}

const MessagingType &MessagingData::getType() const { return m_type; }

void MessagingData::cleanType() {
  m_type = MessagingType();
  m_typeIsSet = false;
}

bool MessagingData::getTypeIsSet() const { return m_typeIsSet; }

void MessagingData::setText(const xs_string &text) {
  m_text = text;
  m_textIsSet = true;
}

const xs_string &MessagingData::getText() const { return m_text; }

void MessagingData::cleanText() {
  m_text = "";
  m_textIsSet = false;
}

bool MessagingData::getTextIsSet() const { return m_textIsSet; }

MessagingData
MessagingData::reduce(const MessagingDataElements &elements) const {
  MessagingData dataOut;
  if (getTimestampIsSet() && elements.getTimestampIsSet()) {
    dataOut.setTimestamp(getTimestamp());
  }
  if (getMessagingNumberIsSet() && elements.getMessagingNumberIsSet()) {
    dataOut.setMessagingNumber(getMessagingNumber());
  }
  if (getTypeIsSet() && elements.getTypeIsSet()) {
    dataOut.setType(getType());
  }
  if (getTextIsSet() && elements.getTextIsSet()) {
    dataOut.setText(getText());
  }
  return dataOut;
}

bool MessagingData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "messagingNumber", "type", "text"})) {
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
                                   "messagingNumber", &m_messagingNumber)) {
      m_messagingNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "type", &m_type)) {
      m_typeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "text", &m_text)) {
      m_textIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MessagingData::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timestamp", m_timestamp);
  }
  if (m_messagingNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("messagingNumber", m_messagingNumber);
  }
  if (m_typeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("type", m_type);
  }
  if (m_textIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("text", m_text);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram