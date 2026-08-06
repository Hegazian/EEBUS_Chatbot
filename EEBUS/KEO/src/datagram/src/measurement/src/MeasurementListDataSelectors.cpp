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

#include <keo_datagram/measurement/MeasurementListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementListDataSelectors::MeasurementListDataSelectors()
    : DataSelectors(), m_measurementIdIsSet(false), m_measurementId(0),
      m_valueTypeIsSet(false), m_valueType(MeasurementValueType()),
      m_timestampIntervalIsSet(false), m_timestampInterval(TimestampInterval())

{}

MeasurementListDataSelectors::MeasurementListDataSelectors(
    const xs_unsignedInt &c_measurementId,
    const MeasurementValueType &c_valueType,
    const TimestampInterval &c_timestampInterval)
    : DataSelectors(), m_measurementIdIsSet(true),
      m_measurementId(c_measurementId), m_valueTypeIsSet(true),
      m_valueType(c_valueType), m_timestampIntervalIsSet(true),
      m_timestampInterval(c_timestampInterval)

{}

bool MeasurementListDataSelectors::
operator==(const MeasurementListDataSelectors &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_valueTypeIsSet != c_classObject.m_valueTypeIsSet ||
      (m_valueTypeIsSet && (m_valueType != c_classObject.m_valueType))) {
    return false;
  }
  if (m_timestampIntervalIsSet != c_classObject.m_timestampIntervalIsSet ||
      (m_timestampIntervalIsSet &&
       (m_timestampInterval != c_classObject.m_timestampInterval))) {
    return false;
  }

  return true;
}

bool MeasurementListDataSelectors::
operator!=(const MeasurementListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementListDataSelectors::isEmpty() const {
  return !m_measurementIdIsSet && !m_valueTypeIsSet &&
         !m_timestampIntervalIsSet;
}

DataSelectors::Type MeasurementListDataSelectors::getDataType() const {
  return DataSelectors::Type::MEASUREMENT_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr MeasurementListDataSelectors::clone() const {
  return std::make_shared<MeasurementListDataSelectors>(*this);
}

void MeasurementListDataSelectors::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &MeasurementListDataSelectors::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementListDataSelectors::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementListDataSelectors::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementListDataSelectors::setValueType(
    const MeasurementValueType &valueType) {
  m_valueType = valueType;
  m_valueTypeIsSet = true;
}

const MeasurementValueType &MeasurementListDataSelectors::getValueType() const {
  return m_valueType;
}

void MeasurementListDataSelectors::cleanValueType() {
  m_valueType = MeasurementValueType();
  m_valueTypeIsSet = false;
}

bool MeasurementListDataSelectors::getValueTypeIsSet() const {
  return m_valueTypeIsSet;
}

void MeasurementListDataSelectors::setTimestampInterval(
    const TimestampInterval &timestampInterval) {
  m_timestampInterval = timestampInterval;
  m_timestampIntervalIsSet = true;
}

const TimestampInterval &
MeasurementListDataSelectors::getTimestampInterval() const {
  return m_timestampInterval;
}

void MeasurementListDataSelectors::cleanTimestampInterval() {
  m_timestampInterval = TimestampInterval();
  m_timestampIntervalIsSet = false;
}

bool MeasurementListDataSelectors::getTimestampIntervalIsSet() const {
  return m_timestampIntervalIsSet;
}

bool MeasurementListDataSelectors::selects(const MeasurementData &data) const {
  if (getMeasurementIdIsSet() &&
      (!data.getMeasurementIdIsSet() ||
       getMeasurementId() != data.getMeasurementId())) {
    return false;
  }
  if (getValueTypeIsSet() &&
      (!data.getValueTypeIsSet() || getValueType() != data.getValueType())) {
    return false;
  }
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

bool MeasurementListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "valueType", "timestampInterval"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "valueType", &m_valueType)) {
      m_valueTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timestampInterval", &m_timestampInterval)) {
      m_timestampIntervalIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_valueTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("valueType", m_valueType);
  }
  if (m_timestampIntervalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("timestampInterval", m_timestampInterval);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram