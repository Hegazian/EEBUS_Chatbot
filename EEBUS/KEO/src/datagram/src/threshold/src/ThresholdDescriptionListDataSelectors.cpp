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

#include <keo_datagram/threshold/ThresholdDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdDescriptionListDataSelectors::ThresholdDescriptionListDataSelectors()
    : DataSelectors(), m_thresholdIdIsSet(false), m_thresholdId(0),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType())

{}

ThresholdDescriptionListDataSelectors::ThresholdDescriptionListDataSelectors(
    const xs_unsignedInt &c_thresholdId, const ScopeType &c_scopeType)
    : DataSelectors(), m_thresholdIdIsSet(true), m_thresholdId(c_thresholdId),
      m_scopeTypeIsSet(true), m_scopeType(c_scopeType)

{}

bool ThresholdDescriptionListDataSelectors::
operator==(const ThresholdDescriptionListDataSelectors &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool ThresholdDescriptionListDataSelectors::
operator!=(const ThresholdDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdDescriptionListDataSelectors::isEmpty() const {
  return !m_thresholdIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type ThresholdDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::THRESHOLD_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr ThresholdDescriptionListDataSelectors::clone() const {
  return std::make_shared<ThresholdDescriptionListDataSelectors>(*this);
}

void ThresholdDescriptionListDataSelectors::setThresholdId(
    const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &
ThresholdDescriptionListDataSelectors::getThresholdId() const {
  return m_thresholdId;
}

void ThresholdDescriptionListDataSelectors::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool ThresholdDescriptionListDataSelectors::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

void ThresholdDescriptionListDataSelectors::setScopeType(
    const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &ThresholdDescriptionListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void ThresholdDescriptionListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool ThresholdDescriptionListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool ThresholdDescriptionListDataSelectors::selects(
    const ThresholdDescriptionData &data) const {
  if (getThresholdIdIsSet() && (!data.getThresholdIdIsSet() ||
                                getThresholdId() != data.getThresholdId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool ThresholdDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"thresholdId", "scopeType"})) {
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
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram