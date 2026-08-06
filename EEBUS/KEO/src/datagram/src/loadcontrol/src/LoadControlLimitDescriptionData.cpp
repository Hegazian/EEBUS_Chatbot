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

#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionData.h>

#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitDescriptionData::LoadControlLimitDescriptionData()
    : m_limitIdIsSet(false), m_limitId(0), m_limitTypeIsSet(false),
      m_limitType(LoadControlLimitType()), m_limitCategoryIsSet(false),
      m_limitCategory(LoadControlCategory()), m_limitDirectionIsSet(false),
      m_limitDirection(EnergyDirection()), m_measurementIdIsSet(false),
      m_measurementId(0), m_unitIsSet(false), m_unit(UnitOfMeasurement()),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType()), m_labelIsSet(false),
      m_label(""), m_descriptionIsSet(false), m_description("")

{}

bool LoadControlLimitDescriptionData::
operator==(const LoadControlLimitDescriptionData &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet ||
      (m_limitIdIsSet && (m_limitId != c_classObject.m_limitId))) {
    return false;
  }
  if (m_limitTypeIsSet != c_classObject.m_limitTypeIsSet ||
      (m_limitTypeIsSet && (m_limitType != c_classObject.m_limitType))) {
    return false;
  }
  if (m_limitCategoryIsSet != c_classObject.m_limitCategoryIsSet ||
      (m_limitCategoryIsSet &&
       (m_limitCategory != c_classObject.m_limitCategory))) {
    return false;
  }
  if (m_limitDirectionIsSet != c_classObject.m_limitDirectionIsSet ||
      (m_limitDirectionIsSet &&
       (m_limitDirection != c_classObject.m_limitDirection))) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet ||
      (m_measurementIdIsSet &&
       (m_measurementId != c_classObject.m_measurementId))) {
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

bool LoadControlLimitDescriptionData::
operator!=(const LoadControlLimitDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitDescriptionData::isEmpty() const {
  return !m_limitIdIsSet && !m_limitTypeIsSet && !m_limitCategoryIsSet &&
         !m_limitDirectionIsSet && !m_measurementIdIsSet && !m_unitIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

void LoadControlLimitDescriptionData::setLimitId(
    const xs_unsignedInt &limitId) {
  m_limitId = limitId;
  m_limitIdIsSet = true;
}

const xs_unsignedInt &LoadControlLimitDescriptionData::getLimitId() const {
  return m_limitId;
}

void LoadControlLimitDescriptionData::cleanLimitId() {
  m_limitId = 0;
  m_limitIdIsSet = false;
}

bool LoadControlLimitDescriptionData::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

void LoadControlLimitDescriptionData::setLimitType(
    const LoadControlLimitType &limitType) {
  m_limitType = limitType;
  m_limitTypeIsSet = true;
}

const LoadControlLimitType &
LoadControlLimitDescriptionData::getLimitType() const {
  return m_limitType;
}

void LoadControlLimitDescriptionData::cleanLimitType() {
  m_limitType = LoadControlLimitType();
  m_limitTypeIsSet = false;
}

bool LoadControlLimitDescriptionData::getLimitTypeIsSet() const {
  return m_limitTypeIsSet;
}

void LoadControlLimitDescriptionData::setLimitCategory(
    const LoadControlCategory &limitCategory) {
  m_limitCategory = limitCategory;
  m_limitCategoryIsSet = true;
}

const LoadControlCategory &
LoadControlLimitDescriptionData::getLimitCategory() const {
  return m_limitCategory;
}

void LoadControlLimitDescriptionData::cleanLimitCategory() {
  m_limitCategory = LoadControlCategory();
  m_limitCategoryIsSet = false;
}

bool LoadControlLimitDescriptionData::getLimitCategoryIsSet() const {
  return m_limitCategoryIsSet;
}

void LoadControlLimitDescriptionData::setLimitDirection(
    const EnergyDirection &limitDirection) {
  m_limitDirection = limitDirection;
  m_limitDirectionIsSet = true;
}

const EnergyDirection &
LoadControlLimitDescriptionData::getLimitDirection() const {
  return m_limitDirection;
}

void LoadControlLimitDescriptionData::cleanLimitDirection() {
  m_limitDirection = EnergyDirection();
  m_limitDirectionIsSet = false;
}

bool LoadControlLimitDescriptionData::getLimitDirectionIsSet() const {
  return m_limitDirectionIsSet;
}

void LoadControlLimitDescriptionData::setMeasurementId(
    const xs_unsignedInt &measurementId) {
  m_measurementId = measurementId;
  m_measurementIdIsSet = true;
}

const xs_unsignedInt &
LoadControlLimitDescriptionData::getMeasurementId() const {
  return m_measurementId;
}

void LoadControlLimitDescriptionData::cleanMeasurementId() {
  m_measurementId = 0;
  m_measurementIdIsSet = false;
}

bool LoadControlLimitDescriptionData::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void LoadControlLimitDescriptionData::setUnit(const UnitOfMeasurement &unit) {
  m_unit = unit;
  m_unitIsSet = true;
}

const UnitOfMeasurement &LoadControlLimitDescriptionData::getUnit() const {
  return m_unit;
}

void LoadControlLimitDescriptionData::cleanUnit() {
  m_unit = UnitOfMeasurement();
  m_unitIsSet = false;
}

bool LoadControlLimitDescriptionData::getUnitIsSet() const {
  return m_unitIsSet;
}

void LoadControlLimitDescriptionData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &LoadControlLimitDescriptionData::getScopeType() const {
  return m_scopeType;
}

void LoadControlLimitDescriptionData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool LoadControlLimitDescriptionData::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void LoadControlLimitDescriptionData::setLabel(const xs_string &label) {
  m_label = label;
  m_labelIsSet = true;
}

const xs_string &LoadControlLimitDescriptionData::getLabel() const {
  return m_label;
}

void LoadControlLimitDescriptionData::cleanLabel() {
  m_label = "";
  m_labelIsSet = false;
}

bool LoadControlLimitDescriptionData::getLabelIsSet() const {
  return m_labelIsSet;
}

void LoadControlLimitDescriptionData::setDescription(
    const xs_string &description) {
  m_description = description;
  m_descriptionIsSet = true;
}

const xs_string &LoadControlLimitDescriptionData::getDescription() const {
  return m_description;
}

void LoadControlLimitDescriptionData::cleanDescription() {
  m_description = "";
  m_descriptionIsSet = false;
}

bool LoadControlLimitDescriptionData::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

LoadControlLimitDescriptionData LoadControlLimitDescriptionData::reduce(
    const LoadControlLimitDescriptionDataElements &elements) const {
  LoadControlLimitDescriptionData dataOut;
  if (getLimitIdIsSet() && elements.getLimitIdIsSet()) {
    dataOut.setLimitId(getLimitId());
  }
  if (getLimitTypeIsSet() && elements.getLimitTypeIsSet()) {
    dataOut.setLimitType(getLimitType());
  }
  if (getLimitCategoryIsSet() && elements.getLimitCategoryIsSet()) {
    dataOut.setLimitCategory(getLimitCategory());
  }
  if (getLimitDirectionIsSet() && elements.getLimitDirectionIsSet()) {
    dataOut.setLimitDirection(getLimitDirection());
  }
  if (getMeasurementIdIsSet() && elements.getMeasurementIdIsSet()) {
    dataOut.setMeasurementId(getMeasurementId());
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

bool LoadControlLimitDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"limitId", "limitType", "limitCategory", "limitDirection",
             "measurementId", "unit", "scopeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitId", &m_limitId)) {
      m_limitIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitType", &m_limitType)) {
      m_limitTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitCategory", &m_limitCategory)) {
      m_limitCategoryIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitDirection", &m_limitDirection)) {
      m_limitDirectionIsSet = true;
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

std::string LoadControlLimitDescriptionData::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitId", m_limitId);
  }
  if (m_limitTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitType", m_limitType);
  }
  if (m_limitCategoryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitCategory", m_limitCategory);
  }
  if (m_limitDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitDirection", m_limitDirection);
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("measurementId", m_measurementId);
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