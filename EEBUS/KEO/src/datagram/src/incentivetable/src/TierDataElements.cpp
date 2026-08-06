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

#include <keo_datagram/incentivetable/TierDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierDataElements::TierDataElements()
    : DataElements(), m_tierIdIsSet(false), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriodElements()), m_timeTableIdIsSet(false),
      m_activeIncentiveIdIsSet(false)

{}

bool TierDataElements::operator==(const TierDataElements &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet) {
    return false;
  }
  if (m_activeIncentiveIdIsSet != c_classObject.m_activeIncentiveIdIsSet) {
    return false;
  }

  return true;
}

bool TierDataElements::operator!=(const TierDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierDataElements::isEmpty() const {
  return !m_tierIdIsSet && !m_timePeriodIsSet && !m_timeTableIdIsSet &&
         !m_activeIncentiveIdIsSet;
}

DataElements::Type TierDataElements::getDataType() const {
  return DataElements::Type::TIER_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TierDataElements::clone() const {
  return std::make_shared<TierDataElements>(*this);
}

void TierDataElements::setTierId() { m_tierIdIsSet = true; }

void TierDataElements::cleanTierId() { m_tierIdIsSet = false; }

bool TierDataElements::getTierIdIsSet() const { return m_tierIdIsSet; }

void TierDataElements::setTimePeriod(const TimePeriodElements &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriodElements &TierDataElements::getTimePeriod() const {
  return m_timePeriod;
}

void TierDataElements::cleanTimePeriod() {
  m_timePeriod = TimePeriodElements();
  m_timePeriodIsSet = false;
}

bool TierDataElements::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void TierDataElements::setTimeTableId() { m_timeTableIdIsSet = true; }

void TierDataElements::cleanTimeTableId() { m_timeTableIdIsSet = false; }

bool TierDataElements::getTimeTableIdIsSet() const {
  return m_timeTableIdIsSet;
}

void TierDataElements::setActiveIncentiveId() {
  m_activeIncentiveIdIsSet = true;
}

void TierDataElements::cleanActiveIncentiveId() {
  m_activeIncentiveIdIsSet = false;
}

bool TierDataElements::getActiveIncentiveIdIsSet() const {
  return m_activeIncentiveIdIsSet;
}

bool TierDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"tierId", "timePeriod", "timeTableId", "activeIncentiveId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tierId")) {
      m_tierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timePeriod", &m_timePeriod)) {
      m_timePeriodIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeTableId")) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "activeIncentiveId")) {
      m_activeIncentiveIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierDataElements::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tierId");
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeTableId");
  }
  if (m_activeIncentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeIncentiveId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram