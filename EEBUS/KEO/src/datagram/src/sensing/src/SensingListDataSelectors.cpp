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

#include <keo_datagram/sensing/SensingListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SensingListDataSelectors::SensingListDataSelectors()
    : DataSelectors(), m_timestampIntervalIsSet(false),
      m_timestampInterval(TimestampInterval())

{}

SensingListDataSelectors::SensingListDataSelectors(
    const TimestampInterval &c_timestampInterval) {
  setTimestampInterval(c_timestampInterval);
}

bool SensingListDataSelectors::
operator==(const SensingListDataSelectors &c_classObject) const {
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
    return false;
  }

  return true;
}

bool SensingListDataSelectors::
operator!=(const SensingListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool SensingListDataSelectors::isEmpty() const {
  return !m_timestampIntervalIsSet;
}

DataSelectors::Type SensingListDataSelectors::getDataType() const {
  return DataSelectors::Type::SENSING_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr SensingListDataSelectors::clone() const {
  return std::make_shared<SensingListDataSelectors>(*this);
}

void SensingListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
SensingListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void SensingListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool SensingListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

bool SensingListDataSelectors::selects(const SensingData &data) const {
  if (getTimestampIntervalIsSet() &&
      (!data.getTimestampIsSet() ||
       (data.getTimestamp().getDateTime() <
            getTimestampInterval().getStartTime().getDateTime() ||
        data.getTimestamp().getDateTime() >
            getTimestampInterval().getEndTime().getDateTime()))) {
    return false;
  }
  return true;
}

bool SensingListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"timestampInterval"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestampInterval", &m_timestampInterval)) {
      m_timestampIntervalIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SensingListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_timestampIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timestampInterval", m_timestampInterval);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram