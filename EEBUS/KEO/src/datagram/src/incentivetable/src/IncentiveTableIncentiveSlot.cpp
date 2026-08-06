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

#include <keo_datagram/incentivetable/IncentiveTableIncentiveSlot.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableIncentiveSlot::IncentiveTableIncentiveSlot()
    : m_timeIntervalIsSet(false), m_timeInterval(TimeTableData()),
      m_tierIsSet(false), m_tier(std::vector<IncentiveTableTier>())

{}

IncentiveTableIncentiveSlot::IncentiveTableIncentiveSlot(
    const TimeTableData &c_timeInterval,
    const std::vector<IncentiveTableTier> &c_tier)
    : m_timeIntervalIsSet(true), m_timeInterval(c_timeInterval),
      m_tierIsSet(true), m_tier(c_tier)

{}

bool IncentiveTableIncentiveSlot::
operator==(const IncentiveTableIncentiveSlot &c_classObject) const {
  if (m_timeIntervalIsSet != c_classObject.m_timeIntervalIsSet ||
      (m_timeIntervalIsSet &&
       (m_timeInterval != c_classObject.m_timeInterval))) {
    return false;
  }
  if (m_tierIsSet != c_classObject.m_tierIsSet ||
      (m_tierIsSet && (m_tier != c_classObject.m_tier))) {
    return false;
  }

  return true;
}

bool IncentiveTableIncentiveSlot::
operator!=(const IncentiveTableIncentiveSlot &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableIncentiveSlot::isEmpty() const {
  return !m_timeIntervalIsSet && !m_tierIsSet;
}

void IncentiveTableIncentiveSlot::setTimeInterval(
    const TimeTableData &timeInterval) {
  m_timeInterval = timeInterval;
  m_timeIntervalIsSet = true;
}

const TimeTableData &IncentiveTableIncentiveSlot::getTimeInterval() const {
  return m_timeInterval;
}

void IncentiveTableIncentiveSlot::cleanTimeInterval() {
  m_timeInterval = TimeTableData();
  m_timeIntervalIsSet = false;
}

bool IncentiveTableIncentiveSlot::getTimeIntervalIsSet() const {
  return m_timeIntervalIsSet;
}

void IncentiveTableIncentiveSlot::setTier(
    const std::vector<IncentiveTableTier> &tier) {
  m_tier = tier;
  m_tierIsSet = true;
}

const std::vector<IncentiveTableTier> &
IncentiveTableIncentiveSlot::getTier() const {
  return m_tier;
}

void IncentiveTableIncentiveSlot::cleanTier() {
  m_tier.clear();
  m_tierIsSet = false;
}

bool IncentiveTableIncentiveSlot::getTierIsSet() const { return m_tierIsSet; }

bool IncentiveTableIncentiveSlot::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"timeInterval", "tier"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeInterval", &m_timeInterval)) {
      m_timeIntervalIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::getList<IncentiveTableTier>(
            static_cast<KeoJsonValue *>(&(*iter)), "tier", &m_tier)) {
      m_tierIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableIncentiveSlot::toJson() const {
  std::string result = "[";
  if (m_timeIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeInterval", m_timeInterval);
  }
  if (m_tierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<IncentiveTableTier>("tier", m_tier);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram