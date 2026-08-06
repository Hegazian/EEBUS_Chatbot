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

#include <keo_datagram/threshold/ThresholdDescriptionData.h>

#include <keo_datagram/threshold/ThresholdDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdDescriptionData::ThresholdDescriptionData()
    : m_thresholdIdIsSet(false), m_thresholdId(0), m_thresholdTypeIsSet(false),
      m_thresholdType(ThresholdType()), m_unitIsSet(false),
      m_unit(UnitOfMeasurement()), m_scopeTypeIsSet(false),
      m_scopeType(ScopeType()), m_labelIsSet(false), m_label(""),
      m_descriptionIsSet(false), m_description("")

{}

bool ThresholdDescriptionData::
operator==(const ThresholdDescriptionData &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }
  if (m_thresholdTypeIsSet != c_classObject.m_thresholdTypeIsSet ||
      (m_thresholdTypeIsSet &&
       (m_thresholdType != c_classObject.m_thresholdType))) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet ||
      (m_unitIsSet && (m_unit != c_classObject.m_unit))) {
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

bool ThresholdDescriptionData::
operator!=(const ThresholdDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdDescriptionData::isEmpty() const {
  return !m_thresholdIdIsSet && !m_thresholdTypeIsSet && !m_unitIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void ThresholdDescriptionData::setThresholdId(
    const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &ThresholdDescriptionData::getThresholdId() const {
  return m_thresholdId;
}

void ThresholdDescriptionData::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool ThresholdDescriptionData::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void ThresholdDescriptionData::setThresholdType(
    const ThresholdType &thresholdType) {
  m_thresholdType = thresholdType;
  m_thresholdTypeIsSet = true;
}

const ThresholdType &ThresholdDescriptionData::getThresholdType() const {
  return m_thresholdType;
}

void ThresholdDescriptionData::cleanThresholdType() {
  m_thresholdType = ThresholdType();
  m_thresholdTypeIsSet = false;
}

bool ThresholdDescriptionData::getThresholdTypeIsSet() const {
  return m_thresholdTypeIsSet;
}

void ThresholdDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &ThresholdDescriptionData::getUnit() const {
  return m_unit;
}

void ThresholdDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool ThresholdDescriptionData::getUnitIsSet() const { return m_unitIsSet; }

void ThresholdDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &ThresholdDescriptionData::getScopeType() const {
  return m_scopeType;
}

void ThresholdDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool ThresholdDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void ThresholdDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &ThresholdDescriptionData::getLabel() const { return m_label; }

void ThresholdDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool ThresholdDescriptionData::getLabelIsSet() const { return m_labelIsSet; }

void ThresholdDescriptionData::setDescription(const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &ThresholdDescriptionData::getDescription() const {
  return m_description;
}

void ThresholdDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool ThresholdDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

ThresholdDescriptionData ThresholdDescriptionData::reduce(
    const ThresholdDescriptionDataElements &elements) const {
  ThresholdDescriptionData dataOut;
  if (getThresholdIdIsSet() && elements.getThresholdIdIsSet()) {
    dataOut.setThresholdId(getThresholdId());
  }
  if (getThresholdTypeIsSet() && elements.getThresholdTypeIsSet()) {
    dataOut.setThresholdType(getThresholdType());
  }
  if (getUnitIsSet() && elements.getUnitIsSet()) {
    dataOut.setUnit(getUnit());
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

bool ThresholdDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"thresholdId", "thresholdType", "unit", "scopeType", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdType", &m_thresholdType)) {
      m_thresholdTypeIsSet = true;
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

std::string ThresholdDescriptionData::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  if (m_thresholdTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdType", m_thresholdType);
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("unit", m_unit);
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