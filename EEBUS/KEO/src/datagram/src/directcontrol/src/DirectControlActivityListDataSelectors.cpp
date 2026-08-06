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

#include <keo_datagram/directcontrol/DirectControlActivityListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DirectControlActivityListDataSelectors::DirectControlActivityListDataSelectors()
    : DataSelectors(), m_timestampIntervalIsSet(false),
      m_timestampInterval(TimestampInterval())

{}

DirectControlActivityListDataSelectors::DirectControlActivityListDataSelectors(
    const TimestampInterval &c_timestampInterval) {
  setTimestampInterval(c_timestampInterval);
}

bool DirectControlActivityListDataSelectors::
operator==(const DirectControlActivityListDataSelectors &c_classObject) const {
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
    return false;
  }

  return true;
}

bool DirectControlActivityListDataSelectors::
operator!=(const DirectControlActivityListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool DirectControlActivityListDataSelectors::isEmpty() const {
  return !m_timestampIntervalIsSet;
}

DataSelectors::Type
DirectControlActivityListDataSelectors::getDataType() const {
  return DataSelectors::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr DirectControlActivityListDataSelectors::clone() const {
  return std::make_shared<DirectControlActivityListDataSelectors>(*this);
}

void DirectControlActivityListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
DirectControlActivityListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void DirectControlActivityListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool DirectControlActivityListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

bool DirectControlActivityListDataSelectors::selects(
    const DirectControlActivityData &data) const {
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

bool DirectControlActivityListDataSelectors::fromJson(KeoJsonValue *json) {
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

std::string DirectControlActivityListDataSelectors::toJson() const {
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