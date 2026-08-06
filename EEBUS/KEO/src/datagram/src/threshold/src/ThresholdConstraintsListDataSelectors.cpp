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

#include <keo_datagram/threshold/ThresholdConstraintsListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ThresholdConstraintsListDataSelectors::ThresholdConstraintsListDataSelectors()
    : DataSelectors(), m_thresholdIdIsSet(false), m_thresholdId(0)

{}

ThresholdConstraintsListDataSelectors::ThresholdConstraintsListDataSelectors(
    const xs_unsignedInt &c_thresholdId) {
  setThresholdId(c_thresholdId);
}

bool ThresholdConstraintsListDataSelectors::
operator==(const ThresholdConstraintsListDataSelectors &c_classObject) const {
  if (m_thresholdIdIsSet != c_classObject.m_thresholdIdIsSet ||
      (m_thresholdIdIsSet && (m_thresholdId != c_classObject.m_thresholdId))) {
    return false;
  }

  return true;
}

bool ThresholdConstraintsListDataSelectors::
operator!=(const ThresholdConstraintsListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool ThresholdConstraintsListDataSelectors::isEmpty() const {
  return !m_thresholdIdIsSet;
}

DataSelectors::Type ThresholdConstraintsListDataSelectors::getDataType() const {
  return DataSelectors::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr ThresholdConstraintsListDataSelectors::clone() const {
  return std::make_shared<ThresholdConstraintsListDataSelectors>(*this);
}

void ThresholdConstraintsListDataSelectors::setThresholdId(
    const xs_unsignedInt &thresholdId) {
  m_thresholdId = thresholdId;
  m_thresholdIdIsSet = true;
}

const xs_unsignedInt &
ThresholdConstraintsListDataSelectors::getThresholdId() const {
  return m_thresholdId;
}

void ThresholdConstraintsListDataSelectors::cleanThresholdId() {
  m_thresholdId = 0;
  m_thresholdIdIsSet = false;
}

bool ThresholdConstraintsListDataSelectors::getThresholdIdIsSet() const {
  return m_thresholdIdIsSet;
}

bool ThresholdConstraintsListDataSelectors::selects(
    const ThresholdConstraintsData &data) const {
  if (getThresholdIdIsSet() && (!data.getThresholdIdIsSet() ||
                                getThresholdId() != data.getThresholdId())) {
    return false;
  }
  return true;
}

bool ThresholdConstraintsListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"thresholdId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "thresholdId", &m_thresholdId)) {
      m_thresholdIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ThresholdConstraintsListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_thresholdIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("thresholdId", m_thresholdId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram