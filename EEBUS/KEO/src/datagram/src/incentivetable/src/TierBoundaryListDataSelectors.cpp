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

#include <keo_datagram/incentivetable/TierBoundaryListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryListDataSelectors::TierBoundaryListDataSelectors()
    : DataSelectors(), m_boundaryIdIsSet(false), m_boundaryId(0)

{}

TierBoundaryListDataSelectors::TierBoundaryListDataSelectors(
    const xs_unsignedInt &c_boundaryId) {
  setBoundaryId(c_boundaryId);
}

bool TierBoundaryListDataSelectors::
operator==(const TierBoundaryListDataSelectors &c_classObject) const {
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet ||
      (m_boundaryIdIsSet && (m_boundaryId != c_classObject.m_boundaryId))) {
    return false;
  }

  return true;
}

bool TierBoundaryListDataSelectors::
operator!=(const TierBoundaryListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryListDataSelectors::isEmpty() const {
  return !m_boundaryIdIsSet;
}

DataSelectors::Type TierBoundaryListDataSelectors::getDataType() const {
  return DataSelectors::Type::TIER_BOUNDARY_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TierBoundaryListDataSelectors::clone() const {
  return std::make_shared<TierBoundaryListDataSelectors>(*this);
}

void TierBoundaryListDataSelectors::setBoundaryId(
    const xs_unsignedInt &boundaryId) {
  m_boundaryId = boundaryId;
  m_boundaryIdIsSet = true;
}

const xs_unsignedInt &TierBoundaryListDataSelectors::getBoundaryId() const {
  return m_boundaryId;
}

void TierBoundaryListDataSelectors::cleanBoundaryId() {
  m_boundaryId = 0;
  m_boundaryIdIsSet = false;
}

bool TierBoundaryListDataSelectors::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

bool TierBoundaryListDataSelectors::selects(
    const TierBoundaryData &data) const {
  if (getBoundaryIdIsSet() &&
      (!data.getBoundaryIdIsSet() || getBoundaryId() != data.getBoundaryId())) {
    return false;
  }
  return true;
}

bool TierBoundaryListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"boundaryId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryId", &m_boundaryId)) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierBoundaryListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryId", m_boundaryId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram