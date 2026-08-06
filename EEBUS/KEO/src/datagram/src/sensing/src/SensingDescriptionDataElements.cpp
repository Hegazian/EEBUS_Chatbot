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

#include <keo_datagram/sensing/SensingDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SensingDescriptionDataElements::SensingDescriptionDataElements()
    : DataElements(), m_sensingTypeIsSet(false), m_unitIsSet(false),
      m_scopeTypeIsSet(false), m_labelIsSet(false), m_descriptionIsSet(false)

{}

bool SensingDescriptionDataElements::
operator==(const SensingDescriptionDataElements &c_classObject) const {
  if (m_sensingTypeIsSet != c_classObject.m_sensingTypeIsSet) {
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

bool SensingDescriptionDataElements::
operator!=(const SensingDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool SensingDescriptionDataElements::isEmpty() const {
  return !m_sensingTypeIsSet && !m_unitIsSet && !m_scopeTypeIsSet &&
         !m_labelIsSet && !m_descriptionIsSet;
}

DataElements::Type SensingDescriptionDataElements::getDataType() const {
  return DataElements::Type::SENSING_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr SensingDescriptionDataElements::clone() const {
  return std::make_shared<SensingDescriptionDataElements>(*this);
}

void SensingDescriptionDataElements::setSensingType() {
  m_sensingTypeIsSet = true;
}

void SensingDescriptionDataElements::cleanSensingType() {
  m_sensingTypeIsSet = false;
}

bool SensingDescriptionDataElements::getSensingTypeIsSet() const {
  return m_sensingTypeIsSet;
}

void SensingDescriptionDataElements::setUnit() { m_unitIsSet = true; }

void SensingDescriptionDataElements::cleanUnit() { m_unitIsSet = false; }

bool SensingDescriptionDataElements::getUnitIsSet() const {
  return m_unitIsSet;
}

void SensingDescriptionDataElements::setScopeType() { m_scopeTypeIsSet = true; }

void SensingDescriptionDataElements::cleanScopeType() {
  m_scopeTypeIsSet = false;
}

bool SensingDescriptionDataElements::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

void SensingDescriptionDataElements::setLabel() { m_labelIsSet = true; }

void SensingDescriptionDataElements::cleanLabel() { m_labelIsSet = false; }

bool SensingDescriptionDataElements::getLabelIsSet() const {
  return m_labelIsSet;
}

void SensingDescriptionDataElements::setDescription() {
  m_descriptionIsSet = true;
}

void SensingDescriptionDataElements::cleanDescription() {
  m_descriptionIsSet = false;
}

bool SensingDescriptionDataElements::getDescriptionIsSet() const {
  return m_descriptionIsSet;
}

bool SensingDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json,
            {"sensingType", "unit", "scopeType", "label", "description"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "sensingType")) {
      m_sensingTypeIsSet = true;
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

std::string SensingDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_sensingTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("sensingType");
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