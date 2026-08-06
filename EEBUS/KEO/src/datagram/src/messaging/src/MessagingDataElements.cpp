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

#include <keo_datagram/messaging/MessagingDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MessagingDataElements::MessagingDataElements()
    : DataElements(), m_timestampIsSet(false), m_messagingNumberIsSet(false),
      m_typeIsSet(false), m_textIsSet(false)

{}

bool MessagingDataElements::
operator==(const MessagingDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_messagingNumberIsSet != c_classObject.m_messagingNumberIsSet) {
    return false;
  }
  if (m_typeIsSet != c_classObject.m_typeIsSet) {
    return false;
  }
  if (m_textIsSet != c_classObject.m_textIsSet) {
    return false;
  }

  return true;
}

bool MessagingDataElements::
operator!=(const MessagingDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool MessagingDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_messagingNumberIsSet && !m_typeIsSet &&
         !m_textIsSet;
}

DataElements::Type MessagingDataElements::getDataType() const {
  return DataElements::Type::MESSAGING_DATA_ELEMENTS_TYPE;
}

DataElementsPtr MessagingDataElements::clone() const {
  return std::make_shared<MessagingDataElements>(*this);
}

void MessagingDataElements::setTimestamp() { m_timestampIsSet = true; }

void MessagingDataElements::cleanTimestamp() { m_timestampIsSet = false; }

bool MessagingDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void MessagingDataElements::setMessagingNumber() {
  m_messagingNumberIsSet = true;
}

void MessagingDataElements::cleanMessagingNumber() {
  m_messagingNumberIsSet = false;
}

bool MessagingDataElements::getMessagingNumberIsSet() const {
  return m_messagingNumberIsSet;
}

void MessagingDataElements::setType() { m_typeIsSet = true; }

void MessagingDataElements::cleanType() { m_typeIsSet = false; }

bool MessagingDataElements::getTypeIsSet() const { return m_typeIsSet; }

void MessagingDataElements::setText() { m_textIsSet = true; }

void MessagingDataElements::cleanText() { m_textIsSet = false; }

bool MessagingDataElements::getTextIsSet() const { return m_textIsSet; }

bool MessagingDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "messagingNumber", "type", "text"})) {
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
                                     "messagingNumber")) {
      m_messagingNumberIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "type")) {
      m_typeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "text")) {
      m_textIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MessagingDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_messagingNumberIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("messagingNumber");
  }
  if (m_typeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("type");
  }
  if (m_textIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("text");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram