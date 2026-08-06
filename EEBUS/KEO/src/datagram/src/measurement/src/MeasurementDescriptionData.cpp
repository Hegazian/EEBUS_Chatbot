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

#include <keo_datagram/measurement/MeasurementDescriptionData.h>

#include <keo_datagram/measurement/MeasurementDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementDescriptionData::MeasurementDescriptionData()
    : m_measurementIdIsSet(false), m_measurementId(0),
      m_measurementTypeIsSet(false), m_measurementType(MeasurementType()),
      m_commodityTypeIsSet(false), m_commodityType(CommodityType()),
      m_unitIsSet(false), m_unit(UnitOfMeasurement()),
      m_calibrationValueIsSet(false), m_calibrationValue(ScaledNumber()),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool MeasurementDescriptionData::
operator==(const MeasurementDescriptionData &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
    return false;
  }
  if (m_measurementTypeIsSet != c_classObject.m_measurementTypeIsSet ||
      (m_measurementTypeIsSet &&
       (m_measurementType != c_classObject.m_measurementType))) {
    return false;
  }
  if (m_commodityTypeIsSet != c_classObject.m_commodityTypeIsSet ||
      (m_commodityTypeIsSet &&
       (m_commodityType != c_classObject.m_commodityType))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
    return false;
  }
  if (m_calibrationValueIsSet != c_classObject.m_calibrationValueIsSet ||
      (m_calibrationValueIsSet &&
       (m_calibrationValue != c_classObject.m_calibrationValue))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
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

  return true;
}

bool MeasurementDescriptionData::
operator!=(const MeasurementDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementDescriptionData::isEmpty() const {
  return !m_measurementIdIsSet && !m_measurementTypeIsSet &&
         !m_commodityTypeIsSet && !m_unitIsSet && !m_calibrationValueIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void MeasurementDescriptionData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &MeasurementDescriptionData::getMeasurementId() const {
  return m_measurementId;
}

void MeasurementDescriptionData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool MeasurementDescriptionData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementDescriptionData::setMeasurementType(
    const MeasurementType &measurementType) {
  m_measurementType = measurementType;
  m_measurementTypeIsSet = true;
}

const MeasurementType &MeasurementDescriptionData::getMeasurementType() const {
  return m_measurementType;
}

void MeasurementDescriptionData::cleanMeasurementType() {
  m_measurementType = MeasurementType();
  m_measurementTypeIsSet = false;
}

bool MeasurementDescriptionData::getMeasurementTypeIsSet() const {
  return m_measurementTypeIsSet;
}

void MeasurementDescriptionData::setCommodityType(
    const CommodityType &commodityType) {
  m_commodityType = commodityType;
  m_commodityTypeIsSet = true;
}

const CommodityType &MeasurementDescriptionData::getCommodityType() const {
  return m_commodityType;
}

void MeasurementDescriptionData::cleanCommodityType() {
  m_commodityType = CommodityType();
  m_commodityTypeIsSet = false;
}

bool MeasurementDescriptionData::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

void MeasurementDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &MeasurementDescriptionData::getUnit() const {
  return m_unit;
}

void MeasurementDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool MeasurementDescriptionData::getUnitIsSet() const { return m_unitIsSet; }

void MeasurementDescriptionData::setCalibrationValue(
    const ScaledNumber &calibrationValue) {
  m_calibrationValue = calibrationValue;
  m_calibrationValueIsSet = true;
}

const ScaledNumber &MeasurementDescriptionData::getCalibrationValue() const {
  return m_calibrationValue;
}

void MeasurementDescriptionData::cleanCalibrationValue() {
  m_calibrationValue = ScaledNumber();
  m_calibrationValueIsSet = false;
}

bool MeasurementDescriptionData::getCalibrationValueIsSet() const {
  return m_calibrationValueIsSet;
}

void MeasurementDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &MeasurementDescriptionData::getScopeType() const {
  return m_scopeType;
}

void MeasurementDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool MeasurementDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void MeasurementDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &MeasurementDescriptionData::getLabel() const {
  return m_label;
}

void MeasurementDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool MeasurementDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void MeasurementDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &MeasurementDescriptionData::getDescription() const {
  return m_description;
}

void MeasurementDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool MeasurementDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

MeasurementDescriptionData MeasurementDescriptionData::reduce(
    const MeasurementDescriptionDataElements &elements) const {
  MeasurementDescriptionData dataOut;
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
  }
  if (getMeasurementTypeIsSet() && elements.getMeasurementTypeIsSet()) {
    dataOut.setMeasurementType(getMeasurementType());
  }
  if (getCommodityTypeIsSet() && elements.getCommodityTypeIsSet()) {
    dataOut.setCommodityType(getCommodityType());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
  }
  if (getCalibrationValueIsSet() && elements.getCalibrationValueIsSet()) {
    dataOut.setCalibrationValue(
        getCalibrationValue().reduce(elements.getCalibrationValue()));
  }
  if (getScopeTypeIsSet() && elements.getScopeTypeIsSet()) {
    dataOut.setScopeType(getScopeType());
  }
  if (getLabelIsSet() && elements.getLabelIsSet()) {
    dataOut.setLabel(getLabel());
  }
  if (getDescriptionIsSet() && elements.getDescriptionIsSet()) {
    dataOut.setDescription(getDescription());
  }
  return dataOut;
}

bool MeasurementDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "measurementType", "commodityType", "unit",
                   "calibrationValue", "scopeType", "label", "description"})) {
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
                                   "measurementType", &m_measurementType)) {
      m_measurementTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "commodityType", &m_commodityType)) {
      m_commodityTypeIsSet = true;
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
                                   "calibrationValue", &m_calibrationValue)) {
      m_calibrationValueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
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
  }
  return true;
}

std::string MeasurementDescriptionData::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
  }
  if (m_measurementTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("measurementType", m_measurementType);
  }
  if (m_commodityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("commodityType", m_commodityType);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
  }
  if (m_calibrationValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("calibrationValue", m_calibrationValue);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("label", m_label);
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("description", m_description);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram