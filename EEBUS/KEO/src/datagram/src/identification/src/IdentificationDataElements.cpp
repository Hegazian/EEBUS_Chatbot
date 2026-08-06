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

#include <keo_datagram/identification/IdentificationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IdentificationDataElements::IdentificationDataElements()
    : DataElements(), m_identificationIdIsSet(false),
      m_identificationTypeIsSet(false), m_identificationValueIsSet(false),
      m_authorizedIsSet(false)

{}

bool IdentificationDataElements::
operator==(const IdentificationDataElements &c_classObject) const {
  if (m_identificationIdIsSet != c_classObject.m_identificationIdIsSet) {
    return false;
  }
  if (m_identificationTypeIsSet != c_classObject.m_identificationTypeIsSet) {
    return false;
  }
  if (m_identificationValueIsSet != c_classObject.m_identificationValueIsSet) {
    return false;
  }
  if (m_authorizedIsSet != c_classObject.m_authorizedIsSet) {
    return false;
  }

  return true;
}

bool IdentificationDataElements::
operator!=(const IdentificationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IdentificationDataElements::isEmpty() const {
  return !m_identificationIdIsSet && !m_identificationTypeIsSet &&
         !m_identificationValueIsSet && !m_authorizedIsSet;
}

DataElements::Type IdentificationDataElements::getDataType() const {
  return DataElements::Type::IDENTIFICATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr IdentificationDataElements::clone() const {
  return std::make_shared<IdentificationDataElements>(*this);
}

void IdentificationDataElements::setIdentificationId() {
  m_identificationIdIsSet = true;
}

void IdentificationDataElements::cleanIdentificationId() {
  m_identificationIdIsSet = false;
}

bool IdentificationDataElements::getIdentificationIdIsSet() const {
  return m_identificationIdIsSet;
}

void IdentificationDataElements::setIdentificationType() {
  m_identificationTypeIsSet = true;
}

void IdentificationDataElements::cleanIdentificationType() {
  m_identificationTypeIsSet = false;
}

bool IdentificationDataElements::getIdentificationTypeIsSet() const {
  return m_identificationTypeIsSet;
}

void IdentificationDataElements::setIdentificationValue() {
  m_identificationValueIsSet = true;
}

void IdentificationDataElements::cleanIdentificationValue() {
  m_identificationValueIsSet = false;
}

bool IdentificationDataElements::getIdentificationValueIsSet() const {
  return m_identificationValueIsSet;
}

void IdentificationDataElements::setAuthorized() { m_authorizedIsSet = true; }

void IdentificationDataElements::cleanAuthorized() {
  m_authorizedIsSet = false;
}

bool IdentificationDataElements::getAuthorizedIsSet() const {
  return m_authorizedIsSet;
}

bool IdentificationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"identificationId", "identificationType",
                   "identificationValue", "authorized"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "identificationId")) {
      m_identificationIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "identificationType")) {
      m_identificationTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "identificationValue")) {
      m_identificationValueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "authorized")) {
      m_authorizedIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IdentificationDataElements::toJson() const {
  std::string result = "[";
  if (m_identificationIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("identificationId");
  }
  if (m_identificationTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("identificationType");
  }
  if (m_identificationValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("identificationValue");
  }
  if (m_authorizedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("authorized");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram