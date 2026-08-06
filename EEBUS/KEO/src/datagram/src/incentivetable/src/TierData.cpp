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

#include <keo_datagram/incentivetable/TierData.h>

#include <keo_datagram/incentivetable/TierDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierData::TierData()
    : m_tierIdIsSet(false), m_tierId(0), m_timePeriodIsSet(false),
      m_timePeriod(TimePeriod()), m_timeTableIdIsSet(false), m_timeTableId(0),
      m_activeIncentiveIdIsSet(false),
      m_activeIncentiveId(std::vector<xs_unsignedInt>())

{}

bool TierData::operator==(const TierData &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet ||
      (m_tierIdIsSet && (m_tierId != c_classObject.m_tierId))) {
    return false;
  }
  if (m_timePeriodIsSet != c_classObject.m_timePeriodIsSet ||
      (m_timePeriodIsSet && (m_timePeriod != c_classObject.m_timePeriod))) {
    return false;
  }
  if (m_timeTableIdIsSet != c_classObject.m_timeTableIdIsSet ||
      (m_timeTableIdIsSet && (m_timeTableId != c_classObject.m_timeTableId))) {
    return false;
  }
  if (m_activeIncentiveIdIsSet != c_classObject.m_activeIncentiveIdIsSet ||
      (m_activeIncentiveIdIsSet &&
       (m_activeIncentiveId != c_classObject.m_activeIncentiveId))) {
    return false;
  }

  return true;
}

bool TierData::operator!=(const TierData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierData::isEmpty() const {
  return !m_tierIdIsSet && !m_timePeriodIsSet && !m_timeTableIdIsSet &&
         !m_activeIncentiveIdIsSet;
}

void TierData::setTierId(const xs_unsignedInt &tierId) {
  m_tierId = tierId;
  m_tierIdIsSet = true;
}

const xs_unsignedInt &TierData::getTierId() const { return m_tierId; }

void TierData::cleanTierId() {
  m_tierId = 0;
  m_tierIdIsSet = false;
}

bool TierData::getTierIdIsSet() const { return m_tierIdIsSet; }

void TierData::setTimePeriod(const TimePeriod &timePeriod) {
  m_timePeriod = timePeriod;
  m_timePeriodIsSet = true;
}

const TimePeriod &TierData::getTimePeriod() const { return m_timePeriod; }

void TierData::cleanTimePeriod() {
  m_timePeriod = TimePeriod();
  m_timePeriodIsSet = false;
}

bool TierData::getTimePeriodIsSet() const { return m_timePeriodIsSet; }

void TierData::setTimeTableId(const xs_unsignedInt &timeTableId) {
  m_timeTableId = timeTableId;
  m_timeTableIdIsSet = true;
}

const xs_unsignedInt &TierData::getTimeTableId() const { return m_timeTableId; }

void TierData::cleanTimeTableId() {
  m_timeTableId = 0;
  m_timeTableIdIsSet = false;
}

bool TierData::getTimeTableIdIsSet() const { return m_timeTableIdIsSet; }

void TierData::setActiveIncentiveId(
    const std::vector<xs_unsignedInt> &activeIncentiveId) {
  m_activeIncentiveId = activeIncentiveId;
  m_activeIncentiveIdIsSet = true;
}

const std::vector<xs_unsignedInt> &TierData::getActiveIncentiveId() const {
  return m_activeIncentiveId;
}

void TierData::cleanActiveIncentiveId() {
  m_activeIncentiveId.clear();
  m_activeIncentiveIdIsSet = false;
}

bool TierData::getActiveIncentiveIdIsSet() const {
  return m_activeIncentiveIdIsSet;
}

TierData TierData::reduce(const TierDataElements &elements) const {
  TierData dataOut;
  if (getTierIdIsSet() && elements.getTierIdIsSet()) {
    dataOut.setTierId(getTierId());
  }
  if (getTimePeriodIsSet() && elements.getTimePeriodIsSet()) {
    dataOut.setTimePeriod(getTimePeriod().reduce(elements.getTimePeriod()));
  }
  if (getTimeTableIdIsSet() && elements.getTimeTableIdIsSet()) {
    dataOut.setTimeTableId(getTimeTableId());
  }
  if (getActiveIncentiveIdIsSet() && elements.getActiveIncentiveIdIsSet()) {
    dataOut.setActiveIncentiveId(getActiveIncentiveId());
  }
  return dataOut;
}

bool TierData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"tierId", "timePeriod", "timeTableId", "activeIncentiveId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierId", &m_tierId)) {
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
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeTableId", &m_timeTableId)) {
      m_timeTableIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<xs_unsignedInt>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "activeIncentiveId", &m_activeIncentiveId)) {
      m_activeIncentiveIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierData::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tierId", m_tierId);
  }
  if (m_timePeriodIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timePeriod", m_timePeriod);
  }
  if (m_timeTableIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeTableId", m_timeTableId);
  }
  if (m_activeIncentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<xs_unsignedInt>(
        "activeIncentiveId", m_activeIncentiveId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram