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

#include <keo_datagram/identification/IdentificationData.h>

#include <keo_datagram/identification/IdentificationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IdentificationData::IdentificationData()
    : m_identificationIdIsSet(false), m_identificationId(0),
      m_identificationTypeIsSet(false),
      m_identificationType(IdentificationType()),
      m_identificationValueIsSet(false), m_identificationValue(""),
      m_authorizedIsSet(false), m_authorized(false)

{}

bool IdentificationData::
operator==(const IdentificationData &c_classObject) const {
  if (m_identificationIdIsSet != c_classObject.m_identificationIdIsSet ||
      (m_identificationIdIsSet &&
       (m_identificationId != c_classObject.m_identificationId))) {
    return false;
  }
  if (m_identificationTypeIsSet != c_classObject.m_identificationTypeIsSet ||
      (m_identificationTypeIsSet &&
       (m_identificationType != c_classObject.m_identificationType))) {
    return false;
  }
  if (m_identificationValueIsSet != c_classObject.m_identificationValueIsSet ||
      (m_identificationValueIsSet &&
       (m_identificationValue != c_classObject.m_identificationValue))) {
    return false;
  }
  if (m_authorizedIsSet != c_classObject.m_authorizedIsSet ||
      (m_authorizedIsSet && (m_authorized != c_classObject.m_authorized))) {
    return false;
  }

  return true;
}

bool IdentificationData::
operator!=(const IdentificationData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IdentificationData::isEmpty() const {
  return !m_identificationIdIsSet && !m_identificationTypeIsSet &&
         !m_identificationValueIsSet && !m_authorizedIsSet;
}

void IdentificationData::setIdentificationId(
    const xs_unsignedInt &identificationId) {
  m_identificationId = identificationId;
  m_identificationIdIsSet = true;
}

const xs_unsignedInt &IdentificationData::getIdentificationId() const {
  return m_identificationId;
}

void IdentificationData::cleanIdentificationId() {
  m_identificationId = 0;
  m_identificationIdIsSet = false;
}

bool IdentificationData::getIdentificationIdIsSet() const {
  return m_identificationIdIsSet;
}

void IdentificationData::setIdentificationType(
    const IdentificationType &identificationType) {
  m_identificationType = identificationType;
  m_identificationTypeIsSet = true;
}

const IdentificationType &IdentificationData::getIdentificationType() const {
  return m_identificationType;
}

void IdentificationData::cleanIdentificationType() {
  m_identificationType = IdentificationType();
  m_identificationTypeIsSet = false;
}

bool IdentificationData::getIdentificationTypeIsSet() const {
  return m_identificationTypeIsSet;
}

void IdentificationData::setIdentificationValue(
    const xs_string &identificationValue) {
  m_identificationValue = identificationValue;
  m_identificationValueIsSet = true;
}

const xs_string &IdentificationData::getIdentificationValue() const {
  return m_identificationValue;
}

void IdentificationData::cleanIdentificationValue() {
  m_identificationValue = "";
  m_identificationValueIsSet = false;
}

bool IdentificationData::getIdentificationValueIsSet() const {
  return m_identificationValueIsSet;
}

void IdentificationData::setAuthorized(const xs_boolean &authorized) {
  m_authorized = authorized;
  m_authorizedIsSet = true;
}

const xs_boolean &IdentificationData::getAuthorized() const {
  return m_authorized;
}

void IdentificationData::cleanAuthorized() {
  m_authorized = false;
  m_authorizedIsSet = false;
}

bool IdentificationData::getAuthorizedIsSet() const {
  return m_authorizedIsSet;
}

IdentificationData
IdentificationData::reduce(const IdentificationDataElements &elements) const {
  IdentificationData dataOut;
  if (getIdentificationIdIsSet() && elements.getIdentificationIdIsSet()) {
    dataOut.setIdentificationId(getIdentificationId());
  }
  if (getIdentificationTypeIsSet() && elements.getIdentificationTypeIsSet()) {
    dataOut.setIdentificationType(getIdentificationType());
  }
  if (getIdentificationValueIsSet() && elements.getIdentificationValueIsSet()) {
    dataOut.setIdentificationValue(getIdentificationValue());
  }
  if (getAuthorizedIsSet() && elements.getAuthorizedIsSet()) {
    dataOut.setAuthorized(getAuthorized());
  }
  return dataOut;
}

bool IdentificationData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"identificationId", "identificationType",
                   "identificationValue", "authorized"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "identificationId", &m_identificationId)) {
      m_identificationIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "identificationType",
                                   &m_identificationType)) {
      m_identificationTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "identificationValue",
                                   &m_identificationValue)) {
      m_identificationValueIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "authorized", &m_authorized)) {
      m_authorizedIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IdentificationData::toJson() const {
  std::string result = "[";
  if (m_identificationIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("identificationId", m_identificationId);
  }
  if (m_identificationTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("identificationType",
                                           m_identificationType);
  }
  if (m_identificationValueIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("identificationValue",
                                           m_identificationValue);
  }
  if (m_authorizedIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("authorized", m_authorized);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram