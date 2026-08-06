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

#include <keo_datagram/threshold/ThresholdDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdDescriptionDataElements::ThresholdDescriptionDataElements()
    : DataElements(), m_thresholdIdIsSet(false), m_thresholdTypeIsSet(false),
      m_unitIsSet(false), m_scopeTypeIsSet(false), m_labelIsSet(false),
      m_descriptionIsSet(false)

{}

bool ThresholdDescriptionDataElements::
operator==(const ThresholdDescriptionDataElements &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet) {
    return false;
  }
  if (m_thresholdTypeIsSet != c_classObject.m_thresholdTypeIsSet) {
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

bool ThresholdDescriptionDataElements::
operator!=(const ThresholdDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdDescriptionDataElements::isEmpty() const {
  return !m_thresholdIdIsSet && !m_thresholdTypeIsSet && !m_unitIsSet &&
         !m_scopeTypeIsSet && !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type ThresholdDescriptionDataElements::getDataType() const {
  return DataElements::Type::THRESHOLD_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr ThresholdDescriptionDataElements::clone() const {
  return std::make_shared<ThresholdDescriptionDataElements>(*this);
}

void ThresholdDescriptionDataElements::setThresholdId() {
  m_thresholdIdIsSet = true;
}

void ThresholdDescriptionDataElements::cleanThresholdId() {
  m_thresholdIdIsSet = false;
}

bool ThresholdDescriptionDataElements::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void ThresholdDescriptionDataElements::setThresholdType() {
  m_thresholdTypeIsSet = true;
}

void ThresholdDescriptionDataElements::cleanThresholdType() {
  m_thresholdTypeIsSet = false;
}

bool ThresholdDescriptionDataElements::getThresholdTypeIsSet() const {
  return m_thresholdTypeIsSet;
}

void ThresholdDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void ThresholdDescriptionDataElements::cleanUnit() { m_unitIsSet = false; }

bool ThresholdDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void ThresholdDescriptionDataElements::setScopeType() {
  m_scopeTypeIsSet = true;
}

void ThresholdDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool ThresholdDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void ThresholdDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void ThresholdDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool ThresholdDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void ThresholdDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void ThresholdDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool ThresholdDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool ThresholdDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"thresholdId", "thresholdType", "unit", "scopeType", "label",
                   "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thresholdId")) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "thresholdType")) {
      m_thresholdTypeIsSet = true;
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

std::string ThresholdDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdId");
  }
  if (m_thresholdTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("thresholdType");
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