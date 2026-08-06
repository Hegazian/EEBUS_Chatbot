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

#include <keo_datagram/timeseries/TimeSeriesDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesDescriptionDataElements::TimeSeriesDescriptionDataElements()
    : DataElements(), m_timeSeriesIdIsSet(false), m_timeSeriesTypeIsSet(false),
      m_timeSeriesWriteableIsSet(false), m_updateRequiredIsSet(false),
      m_measurementIdIsSet(false), m_currencyIsSet(false), m_unitIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false), m_scopeTypeIsSet(false)

{}

bool TimeSeriesDescriptionDataElements::
operator==(const TimeSeriesDescriptionDataElements &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet) {
    return false;
  }
  if (m_timeSeriesTypeIsSet != c_classObject.m_timeSeriesTypeIsSet) {
    return false;
  }
  if (m_timeSeriesWriteableIsSet != c_classObject.m_timeSeriesWriteableIsSet) {
    return false;
  }
  if (m_updateRequiredIsSet != c_classObject.m_updateRequiredIsSet) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
    return false;
  }

  return true;
}

bool TimeSeriesDescriptionDataElements::
operator!=(const TimeSeriesDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesDescriptionDataElements::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_timeSeriesTypeIsSet &&
         !m_timeSeriesWriteableIsSet && !m_updateRequiredIsSet &&
         !m_measurementIdIsSet && !m_currencyIsSet && !m_unitIsSet &&
         !m_labelIsSet && !m_descriptionIsSet && !m_scopeTypeIsSet;
}

DataElements::Type TimeSeriesDescriptionDataElements::getDataType() const {
  return DataElements::Type::TIME_SERIES_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TimeSeriesDescriptionDataElements::clone() const {
  return std::make_shared<TimeSeriesDescriptionDataElements>(*this);
}

void TimeSeriesDescriptionDataElements::setTimeSeriesId() {
  m_timeSeriesIdIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanTimeSeriesId() {
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesDescriptionDataElements::setTimeSeriesType() {
  m_timeSeriesTypeIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanTimeSeriesType() {
  m_timeSeriesTypeIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getTimeSeriesTypeIsSet() const {
  return m_timeSeriesTypeIsSet;
}

void TimeSeriesDescriptionDataElements::setTimeSeriesWriteable() {
  m_timeSeriesWriteableIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanTimeSeriesWriteable() {
  m_timeSeriesWriteableIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getTimeSeriesWriteableIsSet() const {
  return m_timeSeriesWriteableIsSet;
}

void TimeSeriesDescriptionDataElements::setUpdateRequired() {
  m_updateRequiredIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanUpdateRequired() {
  m_updateRequiredIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getUpdateRequiredIsSet() const {
  return m_updateRequiredIsSet;
}

void TimeSeriesDescriptionDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void TimeSeriesDescriptionDataElements::setCurrency() {
  m_currencyIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanCurrency() {
  m_currencyIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

void TimeSeriesDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void TimeSeriesDescriptionDataElements::cleanUnit() { m_unitIsSet = false; }

bool TimeSeriesDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void TimeSeriesDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void TimeSeriesDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool TimeSeriesDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void TimeSeriesDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void TimeSeriesDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void TimeSeriesDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool TimeSeriesDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool TimeSeriesDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesId", "timeSeriesType", "timeSeriesWriteable",
                   "updateRequired", "measurementId", "currency", "unit",
                   "label", "description", "scopeType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSeriesId")) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSeriesType")) {
      m_timeSeriesTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "timeSeriesWriteable")) {
      m_timeSeriesWriteableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "updateRequired")) {
      m_updateRequiredIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "currency")) {
      m_currencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "unit")) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "label")) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "description")) {
      m_descriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSeriesId");
  }
  if (m_timeSeriesTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSeriesType");
  }
  if (m_timeSeriesWriteableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("timeSeriesWriteable");
  }
  if (m_updateRequiredIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("updateRequired");
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("currency");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram