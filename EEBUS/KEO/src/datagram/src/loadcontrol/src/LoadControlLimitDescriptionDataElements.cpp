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

#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitDescriptionDataElements::
    LoadControlLimitDescriptionDataElements()
    : DataElements(), m_limitIdIsSet(false), m_limitTypeIsSet(false),
      m_limitCategoryIsSet(false), m_limitDirectionIsSet(false),
      m_measurementIdIsSet(false), m_unitIsSet(false), m_scopeTypeIsSet(false),
      m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool LoadControlLimitDescriptionDataElements::
operator==(const LoadControlLimitDescriptionDataElements &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet) {
    return false;
  }
  if (m_limitTypeIsSet != c_classObject.m_limitTypeIsSet) {
    return false;
  }
  if (m_limitCategoryIsSet != c_classObject.m_limitCategoryIsSet) {
    return false;
  }
  if (m_limitDirectionIsSet != c_classObject.m_limitDirectionIsSet) {
    return false;
  }
  if (m_measurementIdIsSet != c_classObject.m_measurementIdIsSet) {
    return false;
  }
  if (m_unitIsSet != c_classObject.m_unitIsSet) {
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

bool LoadControlLimitDescriptionDataElements::
operator!=(const LoadControlLimitDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitDescriptionDataElements::isEmpty() const {
  return !m_limitIdIsSet && !m_limitTypeIsSet && !m_limitCategoryIsSet &&
         !m_limitDirectionIsSet && !m_measurementIdIsSet && !m_unitIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type
LoadControlLimitDescriptionDataElements::getDataType() const {
  return DataElements::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr LoadControlLimitDescriptionDataElements::clone() const {
  return std::make_shared<LoadControlLimitDescriptionDataElements>(*this);
}

void LoadControlLimitDescriptionDataElements::setLimitId() {
  m_limitIdIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanLimitId() {
  m_limitIdIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

void LoadControlLimitDescriptionDataElements::setLimitType() {
  m_limitTypeIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanLimitType() {
  m_limitTypeIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getLimitTypeIsSet() const {
  return m_limitTypeIsSet;
}

void LoadControlLimitDescriptionDataElements::setLimitCategory() {
  m_limitCategoryIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanLimitCategory() {
  m_limitCategoryIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getLimitCategoryIsSet() const {
  return m_limitCategoryIsSet;
}

void LoadControlLimitDescriptionDataElements::setLimitDirection() {
  m_limitDirectionIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanLimitDirection() {
  m_limitDirectionIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getLimitDirectionIsSet() const {
  return m_limitDirectionIsSet;
}

void LoadControlLimitDescriptionDataElements::setMeasurementId() {
  m_measurementIdIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanMeasurementId() {
  m_measurementIdIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getMeasurementIdIsSet() const {
  return m_measurementIdIsSet;
}

void LoadControlLimitDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void LoadControlLimitDescriptionDataElements::cleanUnit() {
  m_unitIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void LoadControlLimitDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void LoadControlLimitDescriptionDataElements::setLabel() {
  m_labelIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanLabel() {
  m_labelIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void LoadControlLimitDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void LoadControlLimitDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool LoadControlLimitDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool LoadControlLimitDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"limitId", "limitType", "limitCategory", "limitDirection",
             "measurementId", "unit", "scopeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "limitId")) {
      m_limitIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "limitType")) {
      m_limitTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "limitCategory")) {
      m_limitCategoryIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "limitDirection")) {
      m_limitDirectionIsSet = true;
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
                                     "unit")) {
      m_unitIsSet = true;
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

std::string LoadControlLimitDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("limitId");
  }
  if (m_limitTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("limitType");
  }
  if (m_limitCategoryIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("limitCategory");
  }
  if (m_limitDirectionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("limitDirection");
  }
  if (m_measurementIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("measurementId");
  }
  if (m_unitIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("unit");
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