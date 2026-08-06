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

#include <keo_datagram/loadcontrol/LoadControlLimitListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitListDataSelectors::LoadControlLimitListDataSelectors()
    : DataSelectors(), m_limitIdIsSet(false), m_limitId(0)

{}

LoadControlLimitListDataSelectors::LoadControlLimitListDataSelectors(
    const xs_unsignedInt &c_limitId) {
  setLimitId(c_limitId);
}

bool LoadControlLimitListDataSelectors::
operator==(const LoadControlLimitListDataSelectors &c_classObject) const {
  if (m_limitIdIsSet != c_classObject.m_limitIdIsSet ||
      (m_limitIdIsSet && (m_limitId != c_classObject.m_limitId))) {
    return false;
  }

  return true;
}

bool LoadControlLimitListDataSelectors::
operator!=(const LoadControlLimitListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitListDataSelectors::isEmpty() const {
  return !m_limitIdIsSet;
}

DataSelectors::Type LoadControlLimitListDataSelectors::getDataType() const {
  return DataSelectors::Type::LOAD_CONTROL_LIMIT_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr LoadControlLimitListDataSelectors::clone() const {
  return std::make_shared<LoadControlLimitListDataSelectors>(*this);
}

void LoadControlLimitListDataSelectors::setLimitId(
    const xs_unsignedInt &limitId) {
  m_limitId = limitId;
  m_limitIdIsSet = true;
}

const xs_unsignedInt &LoadControlLimitListDataSelectors::getLimitId() const {
  return m_limitId;
}

void LoadControlLimitListDataSelectors::cleanLimitId() {
  m_limitId = 0;
  m_limitIdIsSet = false;
}

bool LoadControlLimitListDataSelectors::getLimitIdIsSet() const {
  return m_limitIdIsSet;
}

bool LoadControlLimitListDataSelectors::selects(
    const LoadControlLimitData &data) const {
  if (getLimitIdIsSet() &&
      (!data.getLimitIdIsSet() || getLimitId() != data.getLimitId())) {
    return false;
  }
  return true;
}

bool LoadControlLimitListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"limitId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "limitId", &m_limitId)) {
      m_limitIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlLimitListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_limitIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("limitId", m_limitId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram