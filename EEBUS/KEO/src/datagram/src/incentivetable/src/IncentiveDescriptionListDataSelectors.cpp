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

#include <keo_datagram/incentivetable/IncentiveDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveDescriptionListDataSelectors::IncentiveDescriptionListDataSelectors()
    : DataSelectors(), m_incentiveIdIsSet(false), m_incentiveId(0),
      m_incentiveTypeIsSet(false), m_incentiveType(IncentiveType())

{}

IncentiveDescriptionListDataSelectors::IncentiveDescriptionListDataSelectors(
    const xs_unsignedInt &c_incentiveId, const IncentiveType &c_incentiveType)
    : DataSelectors(), m_incentiveIdIsSet(true), m_incentiveId(c_incentiveId),
      m_incentiveTypeIsSet(true), m_incentiveType(c_incentiveType)

{}

bool IncentiveDescriptionListDataSelectors::
operator==(const IncentiveDescriptionListDataSelectors &c_classObject) const {
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet ||
      (m_incentiveIdIsSet && (m_incentiveId != c_classObject.m_incentiveId))) {
    return false;
  }
  if (m_incentiveTypeIsSet != c_classObject.m_incentiveTypeIsSet ||
      (m_incentiveTypeIsSet &&
       (m_incentiveType != c_classObject.m_incentiveType))) {
    return false;
  }

  return true;
}

bool IncentiveDescriptionListDataSelectors::
operator!=(const IncentiveDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveDescriptionListDataSelectors::isEmpty() const {
  return !m_incentiveIdIsSet && !m_incentiveTypeIsSet;
}

DataSelectors::Type IncentiveDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::INCENTIVE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr IncentiveDescriptionListDataSelectors::clone() const {
  return std::make_shared<IncentiveDescriptionListDataSelectors>(*this);
}

void IncentiveDescriptionListDataSelectors::setIncentiveId(
    const xs_unsignedInt &incentiveId) {
  m_incentiveId = incentiveId;
  m_incentiveIdIsSet = true;
}

const xs_unsignedInt &
IncentiveDescriptionListDataSelectors::getIncentiveId() const {
  return m_incentiveId;
}

void IncentiveDescriptionListDataSelectors::cleanIncentiveId() {
  m_incentiveId = 0;
  m_incentiveIdIsSet = false;
}

bool IncentiveDescriptionListDataSelectors::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

void IncentiveDescriptionListDataSelectors::setIncentiveType(
    const IncentiveType &incentiveType) {
  m_incentiveType = incentiveType;
  m_incentiveTypeIsSet = true;
}

const IncentiveType &
IncentiveDescriptionListDataSelectors::getIncentiveType() const {
  return m_incentiveType;
}

void IncentiveDescriptionListDataSelectors::cleanIncentiveType() {
  m_incentiveType = IncentiveType();
  m_incentiveTypeIsSet = false;
}

bool IncentiveDescriptionListDataSelectors::getIncentiveTypeIsSet() const {
  return m_incentiveTypeIsSet;
}

bool IncentiveDescriptionListDataSelectors::selects(
    const IncentiveDescriptionData &data) const {
  if (getIncentiveIdIsSet() && (!data.getIncentiveIdIsSet() ||
                                getIncentiveId() != data.getIncentiveId())) {
    return false;
  }
  if (getIncentiveTypeIsSet() &&
      (!data.getIncentiveTypeIsSet() ||
       getIncentiveType() != data.getIncentiveType())) {
    return false;
  }
  return true;
}

bool IncentiveDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveId", "incentiveType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveId", &m_incentiveId)) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveType", &m_incentiveType)) {
      m_incentiveTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveId", m_incentiveId);
  }
  if (m_incentiveTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveType", m_incentiveType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram