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

#include <keo_datagram/timeseries/TimeSeriesDescriptionData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TimeSeriesDescriptionData::TimeSeriesDescriptionData()
    : m_timeSeriesIdIsSet(false), m_timeSeriesId(0),
      m_timeSeriesTypeIsSet(false), m_timeSeriesType(TimeSeriesType()),
      m_timeSeriesWriteableIsSet(false), m_timeSeriesWriteable(false),
      m_updateRequiredIsSet(false), m_updateRequired(false),
      m_measurementIdIsSet(false), m_measurementId(0), m_currencyIsSet(false),
      m_currency(Currency()), m_unitIsSet(false), m_unit(UnitOfMeasurement()),
      m_labelIsSet(false), m_label(""), m_descriptionIsSet(false),
      m_description(""), m_scopeTypeIsSet(false), m_scopeType(ScopeType())

{}

bool TimeSeriesDescriptionData::
operator==(const TimeSeriesDescriptionData &c_classObject) const {
  if (m_timeSeriesIdIsSet != c_classObject.m_timeSeriesIdIsSet ||
      (m_timeSeriesIdIsSet &&
       (m_timeSeriesId != c_classObject.m_timeSeriesId))) {
    return false;
  }
  if (m_timeSeriesTypeIsSet != c_classObject.m_timeSeriesTypeIsSet ||
      (m_timeSeriesTypeIsSet &&
       (m_timeSeriesType != c_classObject.m_timeSeriesType))) {
    return false;
  }
  if (m_timeSeriesWriteableIsSet != c_classObject.m_timeSeriesWriteableIsSet ||
      (m_timeSeriesWriteableIsSet &&
       (m_timeSeriesWriteable != c_classObject.m_timeSeriesWriteable))) {
    return false;
  }
  if (m_updateRequiredIsSet != c_classObject.m_updateRequiredIsSet ||
      (m_updateRequiredIsSet &&
       (m_updateRequired != c_classObject.m_updateRequired))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_currencyIsSet != c_classObject.m_currencyIsSet ||
      (m_currencyIsSet && (m_currency != c_classObject.m_currency))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet ||
      (m_labelIsSet && (m_label != c_classObject.m_label))) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet ||
      (m_descriptionIsSet && (m_description != c_classObject.m_description))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool TimeSeriesDescriptionData::
operator!=(const TimeSeriesDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool TimeSeriesDescriptionData::isEmpty() const {
  return !m_timeSeriesIdIsSet && !m_timeSeriesTypeIsSet &&
         !m_timeSeriesWriteableIsSet && !m_updateRequiredIsSet &&
         !m_measurementIdIsSet && !m_currencyIsSet && !m_unitIsSet &&
         !m_labelIsSet && !m_descriptionIsSet && !m_scopeTypeIsSet;
}

void TimeSeriesDescriptionData::setTimeSeriesId(
    const xs_unsignedInt &timeSeriesId) {
  m_timeSeriesId = timeSeriesId;
  m_timeSeriesIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesDescriptionData::getTimeSeriesId() const {
  return m_timeSeriesId;
}

void TimeSeriesDescriptionData::cleanTimeSeriesId() {
  m_timeSeriesId = 0;
  m_timeSeriesIdIsSet = false;
}

bool TimeSeriesDescriptionData::getTimeSeriesIdIsSet() const {
  return m_timeSeriesIdIsSet;
}

void TimeSeriesDescriptionData::setTimeSeriesType(
    const TimeSeriesType &timeSeriesType) {
  m_timeSeriesType = timeSeriesType;
  m_timeSeriesTypeIsSet = true;
}

const TimeSeriesType &TimeSeriesDescriptionData::getTimeSeriesType() const {
  return m_timeSeriesType;
}

void TimeSeriesDescriptionData::cleanTimeSeriesType() {
  m_timeSeriesType = TimeSeriesType();
  m_timeSeriesTypeIsSet = false;
}

bool TimeSeriesDescriptionData::getTimeSeriesTypeIsSet() const {
  return m_timeSeriesTypeIsSet;
}

void TimeSeriesDescriptionData::setTimeSeriesWriteable(
    const xs_boolean &timeSeriesWriteable) {
  m_timeSeriesWriteable = timeSeriesWriteable;
  m_timeSeriesWriteableIsSet = true;
}

const xs_boolean &TimeSeriesDescriptionData::getTimeSeriesWriteable() const {
  return m_timeSeriesWriteable;
}

void TimeSeriesDescriptionData::cleanTimeSeriesWriteable() {
  m_timeSeriesWriteable = false;
  m_timeSeriesWriteableIsSet = false;
}

bool TimeSeriesDescriptionData::getTimeSeriesWriteableIsSet() const {
  return m_timeSeriesWriteableIsSet;
}

void TimeSeriesDescriptionData::setUpdateRequired(
    const xs_boolean &updateRequired) {
  m_updateRequired = updateRequired;
  m_updateRequiredIsSet = true;
}

const xs_boolean &TimeSeriesDescriptionData::getUpdateRequired() const {
  return m_updateRequired;
}

void TimeSeriesDescriptionData::cleanUpdateRequired() {
  m_updateRequired = false;
  m_updateRequiredIsSet = false;
}

bool TimeSeriesDescriptionData::getUpdateRequiredIsSet() const {
  return m_updateRequiredIsSet;
}

void TimeSeriesDescriptionData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &TimeSeriesDescriptionData::getMeasurementId() const {
  return m_measurementId;
}

void TimeSeriesDescriptionData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool TimeSeriesDescriptionData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void TimeSeriesDescriptionData::setCurrency(const Currency &currency) {
  m_currency = currency;
  m_currencyIsSet = true;
}

const Currency &TimeSeriesDescriptionData::getCurrency() const {
  return m_currency;
}

void TimeSeriesDescriptionData::cleanCurrency() {
  m_currency = Currency();
  m_currencyIsSet = false;
}

bool TimeSeriesDescriptionData::getCurrencyIsSet() const {
  return m_currencyIsSet;
}

void TimeSeriesDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &TimeSeriesDescriptionData::getUnit() const {
  return m_unit;
}

void TimeSeriesDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool TimeSeriesDescriptionData::getUnitIsSet() const { return m_unitIsSet; }

void TimeSeriesDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &TimeSeriesDescriptionData::getLabel() const { return m_label; }

void TimeSeriesDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool TimeSeriesDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void TimeSeriesDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &TimeSeriesDescriptionData::getDescription() const {
  return m_description;
}

void TimeSeriesDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool TimeSeriesDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

void TimeSeriesDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &TimeSeriesDescriptionData::getScopeType() const {
  return m_scopeType;
}

void TimeSeriesDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool TimeSeriesDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool TimeSeriesDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"timeSeriesId", "timeSeriesType", "timeSeriesWriteable",
                   "updateRequired", "measurementId", "currency", "unit",
                   "label", "description", "scopeType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesId", &m_timeSeriesId)) {
      m_timeSeriesIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesType", &m_timeSeriesType)) {
      m_timeSeriesTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "timeSeriesWriteable",
                                   &m_timeSeriesWriteable)) {
      m_timeSeriesWriteableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "updateRequired", &m_updateRequired)) {
      m_updateRequiredIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementId", &m_measurementId)) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "currency", &m_currency)) {
      m_currencyIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "unit", &m_unit)) {
      m_unitIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "label", &m_label)) {
      m_labelIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "description", &m_description)) {
      m_descriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TimeSeriesDescriptionData::toJson() const {
  std::string result = "[";
  if (m_timeSeriesIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesId", m_timeSeriesId);
  }
  if (m_timeSeriesTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesType", m_timeSeriesType);
  }
  if (m_timeSeriesWriteableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("timeSeriesWriteable",
                                           m_timeSeriesWriteable);
  }
  if (m_updateRequiredIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("updateRequired", m_updateRequired);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_currencyIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("currency", m_currency);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram