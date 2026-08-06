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

#include <keo_datagram/identification/IdentificationListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IdentificationListDataSelectors::IdentificationListDataSelectors()
    : DataSelectors(), m_identificationIdIsSet(false), m_identificationId(0),
      m_identificationTypeIsSet(false),
      m_identificationType(IdentificationType())

{}

IdentificationListDataSelectors::IdentificationListDataSelectors(
    const xs_unsignedInt &c_identificationId,
    const IdentificationType &c_identificationType)
    : DataSelectors(), m_identificationIdIsSet(true),
      m_identificationId(c_identificationId), m_identificationTypeIsSet(true),
      m_identificationType(c_identificationType)

{}

bool IdentificationListDataSelectors::
operator==(const IdentificationListDataSelectors &c_classObject) const {
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

  return true;
}

bool IdentificationListDataSelectors::
operator!=(const IdentificationListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool IdentificationListDataSelectors::isEmpty() const {
  return !m_identificationIdIsSet && !m_identificationTypeIsSet;
}

DataSelectors::Type IdentificationListDataSelectors::getDataType() const {
  return DataSelectors::Type::IDENTIFICATION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr IdentificationListDataSelectors::clone() const {
  return std::make_shared<IdentificationListDataSelectors>(*this);
}

void IdentificationListDataSelectors::setIdentificationId(
    const xs_unsignedInt &identificationId) {
  m_identificationId = identificationId;
  m_identificationIdIsSet = true;
}

const xs_unsignedInt &
IdentificationListDataSelectors::getIdentificationId() const {
  return m_identificationId;
}

void IdentificationListDataSelectors::cleanIdentificationId() {
  m_identificationId = 0;
  m_identificationIdIsSet = false;
}

bool IdentificationListDataSelectors::getIdentificationIdIsSet() const {
  return m_identificationIdIsSet;
}

void IdentificationListDataSelectors::setIdentificationType(
    const IdentificationType &identificationType) {
  m_identificationType = identificationType;
  m_identificationTypeIsSet = true;
}

const IdentificationType &
IdentificationListDataSelectors::getIdentificationType() const {
  return m_identificationType;
}

void IdentificationListDataSelectors::cleanIdentificationType() {
  m_identificationType = IdentificationType();
  m_identificationTypeIsSet = false;
}

bool IdentificationListDataSelectors::getIdentificationTypeIsSet() const {
  return m_identificationTypeIsSet;
}

bool IdentificationListDataSelectors::selects(
    const IdentificationData &data) const {
  if (getIdentificationIdIsSet() &&
      (!data.getIdentificationIdIsSet() ||
       getIdentificationId() != data.getIdentificationId())) {
    return false;
  }
  if (getIdentificationTypeIsSet() &&
      (!data.getIdentificationTypeIsSet() ||
       getIdentificationType() != data.getIdentificationType())) {
    return false;
  }
  return true;
}

bool IdentificationListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"identificationId", "identificationType"})) {
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
  }
  return true;
}

std::string IdentificationListDataSelectors::toJson() const {
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
  result += "]";
  return result;
}

} // namespace keo_datagram