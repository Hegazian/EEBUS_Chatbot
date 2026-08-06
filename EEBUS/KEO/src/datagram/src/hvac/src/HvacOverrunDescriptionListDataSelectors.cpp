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

#include <keo_datagram/hvac/HvacOverrunDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacOverrunDescriptionListDataSelectors::
    HvacOverrunDescriptionListDataSelectors()
    : DataSelectors(), m_overrunIdIsSet(false), m_overrunId(0)

{}

HvacOverrunDescriptionListDataSelectors::
    HvacOverrunDescriptionListDataSelectors(const xs_unsignedInt &c_overrunId) {
  setOverrunId(c_overrunId);
}

bool HvacOverrunDescriptionListDataSelectors::
operator==(const HvacOverrunDescriptionListDataSelectors &c_classObject) const {
  if (m_overrunIdIsSet != c_classObject.m_overrunIdIsSet ||
      (m_overrunIdIsSet && (m_overrunId != c_classObject.m_overrunId))) {
    return false;
  }

  return true;
}

bool HvacOverrunDescriptionListDataSelectors::
operator!=(const HvacOverrunDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacOverrunDescriptionListDataSelectors::isEmpty() const {
  return !m_overrunIdIsSet;
}

DataSelectors::Type
HvacOverrunDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::HVAC_OVERRUN_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr HvacOverrunDescriptionListDataSelectors::clone() const {
  return std::make_shared<HvacOverrunDescriptionListDataSelectors>(*this);
}

void HvacOverrunDescriptionListDataSelectors::setOverrunId(
    const xs_unsignedInt &overrunId) {
  m_overrunId = overrunId;
  m_overrunIdIsSet = true;
}

const xs_unsignedInt &
HvacOverrunDescriptionListDataSelectors::getOverrunId() const {
  return m_overrunId;
}

void HvacOverrunDescriptionListDataSelectors::cleanOverrunId() {
  m_overrunId = 0;
  m_overrunIdIsSet = false;
}

bool HvacOverrunDescriptionListDataSelectors::getOverrunIdIsSet() const {
  return m_overrunIdIsSet;
}

bool HvacOverrunDescriptionListDataSelectors::selects(
    const HvacOverrunDescriptionData &data) const {
  if (getOverrunIdIsSet() &&
      (!data.getOverrunIdIsSet() || getOverrunId() != data.getOverrunId())) {
    return false;
  }
  return true;
}

bool HvacOverrunDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"overrunId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "overrunId", &m_overrunId)) {
      m_overrunIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacOverrunDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_overrunIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("overrunId", m_overrunId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram