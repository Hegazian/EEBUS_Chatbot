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

#include <keo_datagram/measurement/MeasurementDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementDescriptionDataElements::MeasurementDescriptionDataElements()
    : DataElements(), m_measurementIdIsSet(false),
      m_measurementTypeIsSet(false), m_commodityTypeIsSet(false),
      m_unitIsSet(false), m_calibrationValueIsSet(false),
      m_calibrationValue(ScaledNumberElements()), m_scopeTypeIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool MeasurementDescriptionDataElements::
operator==(const MeasurementDescriptionDataElements &c_classObject) const {
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_measurementTypeIsSet != c_classObject.m_measurementTypeIsSet) {
    return false;
  }
  if (m_commodityTypeIsSet != c_classObject.m_commodityTypeIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
    return false;
  }
  if (m_calibrationValueIsSet != c_classObject.m_calibrationValueIsSet ||
      (m_calibrationValueIsSet &&
       (m_calibrationValue != c_classObject.m_calibrationValue))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
    return false;
  }
  if (m_labelIsSet != c_classObject.m_labelIsSet) {
    return false;
  }
  if (m_descriptionIsSet != c_classObject.m_descriptionIsSet) {
    return false;
  }

  return true;
}

bool MeasurementDescriptionDataElements::
operator!=(const MeasurementDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementDescriptionDataElements::isEmpty() const {
  return !m_measurementIdIsSet && !m_measurementTypeIsSet &&
         !m_commodityTypeIsSet && !m_unitIsSet && !m_calibrationValueIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type MeasurementDescriptionDataElements::getDataType() const {
  return DataElements::Type::MEASUREMENT_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr MeasurementDescriptionDataElements::clone() const {
  return std::make_shared<MeasurementDescriptionDataElements>(*this);
}

void MeasurementDescriptionDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void MeasurementDescriptionDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool MeasurementDescriptionDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void MeasurementDescriptionDataElements::setMeasurementType() {
  m_measurementTypeIsSet = true;
}

void MeasurementDescriptionDataElements::cleanMeasurementType() {
  m_measurementTypeIsSet = false;
}

bool MeasurementDescriptionDataElements::getMeasurementTypeIsSet() const {
  return m_measurementTypeIsSet;
}

void MeasurementDescriptionDataElements::setCommodityType() {
  m_commodityTypeIsSet = true;
}

void MeasurementDescriptionDataElements::cleanCommodityType() {
  m_commodityTypeIsSet = false;
}

bool MeasurementDescriptionDataElements::getCommodityTypeIsSet() const {
  return m_commodityTypeIsSet;
}

void MeasurementDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void MeasurementDescriptionDataElements::cleanUnit() { m_unitIsSet = false; }

bool MeasurementDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void MeasurementDescriptionDataElements::setCalibrationValue(
    const ScaledNumberElements &calibrationValue) {
  m_calibrationValue = calibrationValue;
  m_calibrationValueIsSet = true;
}

const ScaledNumberElements &
MeasurementDescriptionDataElements::getCalibrationValue() const {
  return m_calibrationValue;
}

void MeasurementDescriptionDataElements::cleanCalibrationValue() {
  m_calibrationValue = ScaledNumberElements();
  m_calibrationValueIsSet = false;
}

bool MeasurementDescriptionDataElements::getCalibrationValueIsSet() const {
  return m_calibrationValueIsSet;
}

void MeasurementDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void MeasurementDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool MeasurementDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void MeasurementDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void MeasurementDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool MeasurementDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void MeasurementDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void MeasurementDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool MeasurementDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool MeasurementDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementId", "measurementType", "commodityType", "unit",
                   "calibrationValue", "scopeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementId")) {
      m_measurementIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "measurementType")) {
      m_measurementTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "commodityType")) {
      m_commodityTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "unit")) {
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
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
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
  }
  return true;
}

std::string MeasurementDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_measurementTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementType");
  }
  if (m_commodityTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("commodityType");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
  }
  if (m_calibrationValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("calibrationValue", m_calibrationValue);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
  }
  if (m_labelIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("label");
  }
  if (m_descriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("description");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram