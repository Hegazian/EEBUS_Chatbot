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

#include <keo_datagram/loadcontrol/LoadControlStateDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlStateDataElements::LoadControlStateDataElements()
    : DataElements(), m_timestampIsSet(false), m_eventIdIsSet(false),
      m_eventStateConsumeIsSet(false), m_appliedEventActionConsumeIsSet(false),
      m_eventStateProduceIsSet(false), m_appliedEventActionProduceIsSet(false)

{}

bool LoadControlStateDataElements::
operator==(const LoadControlStateDataElements &c_classObject) const {
  if (m_timestampIsSet != c_classObject.m_timestampIsSet) {
    return false;
  }
  if (m_eventIdIsSet != c_classObject.m_eventIdIsSet) {
    return false;
  }
  if (m_eventStateConsumeIsSet != c_classObject.m_eventStateConsumeIsSet) {
    return false;
  }
  if (m_appliedEventActionConsumeIsSet !=
      c_classObject.m_appliedEventActionConsumeIsSet) {
    return false;
  }
  if (m_eventStateProduceIsSet != c_classObject.m_eventStateProduceIsSet) {
    return false;
  }
  if (m_appliedEventActionProduceIsSet !=
      c_classObject.m_appliedEventActionProduceIsSet) {
    return false;
  }

  return true;
}

bool LoadControlStateDataElements::
operator!=(const LoadControlStateDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlStateDataElements::isEmpty() const {
  return !m_timestampIsSet && !m_eventIdIsSet && !m_eventStateConsumeIsSet &&
         !m_appliedEventActionConsumeIsSet && !m_eventStateProduceIsSet &&
         !m_appliedEventActionProduceIsSet;
}

DataElements::Type LoadControlStateDataElements::getDataType() const {
  return DataElements::Type::LOAD_CONTROL_STATE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr LoadControlStateDataElements::clone() const {
  return std::make_shared<LoadControlStateDataElements>(*this);
}

void LoadControlStateDataElements::setTimestamp() { m_timestampIsSet = true; }

void LoadControlStateDataElements::cleanTimestamp() {
  m_timestampIsSet = false;
}

bool LoadControlStateDataElements::getTimestampIsSet() const {
  return m_timestampIsSet;
}

void LoadControlStateDataElements::setEventId() { m_eventIdIsSet = true; }

void LoadControlStateDataElements::cleanEventId() { m_eventIdIsSet = false; }

bool LoadControlStateDataElements::getEventIdIsSet() const {
  return m_eventIdIsSet;
}

void LoadControlStateDataElements::setEventStateConsume() {
  m_eventStateConsumeIsSet = true;
}

void LoadControlStateDataElements::cleanEventStateConsume() {
  m_eventStateConsumeIsSet = false;
}

bool LoadControlStateDataElements::getEventStateConsumeIsSet() const {
  return m_eventStateConsumeIsSet;
}

void LoadControlStateDataElements::setAppliedEventActionConsume() {
  m_appliedEventActionConsumeIsSet = true;
}

void LoadControlStateDataElements::cleanAppliedEventActionConsume() {
  m_appliedEventActionConsumeIsSet = false;
}

bool LoadControlStateDataElements::getAppliedEventActionConsumeIsSet() const {
  return m_appliedEventActionConsumeIsSet;
}

void LoadControlStateDataElements::setEventStateProduce() {
  m_eventStateProduceIsSet = true;
}

void LoadControlStateDataElements::cleanEventStateProduce() {
  m_eventStateProduceIsSet = false;
}

bool LoadControlStateDataElements::getEventStateProduceIsSet() const {
  return m_eventStateProduceIsSet;
}

void LoadControlStateDataElements::setAppliedEventActionProduce() {
  m_appliedEventActionProduceIsSet = true;
}

void LoadControlStateDataElements::cleanAppliedEventActionProduce() {
  m_appliedEventActionProduceIsSet = false;
}

bool LoadControlStateDataElements::getAppliedEventActionProduceIsSet() const {
  return m_appliedEventActionProduceIsSet;
}

bool LoadControlStateDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timestamp", "eventId", "eventStateConsume",
                   "appliedEventActionConsume", "eventStateProduce",
                   "appliedEventActionProduce"})) {
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
                                     "eventStateConsume")) {
      m_eventStateConsumeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "appliedEventActionConsume")) {
      m_appliedEventActionConsumeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "eventStateProduce")) {
      m_eventStateProduceIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "appliedEventActionProduce")) {
      m_appliedEventActionProduceIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlStateDataElements::toJson() const {
  std::string result = "[";
  if (m_timestampIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timestamp");
  }
  if (m_eventIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventId");
  }
  if (m_eventStateConsumeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventStateConsume");
  }
  if (m_appliedEventActionConsumeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("appliedEventActionConsume");
  }
  if (m_eventStateProduceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("eventStateProduce");
  }
  if (m_appliedEventActionProduceIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("appliedEventActionProduce");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram