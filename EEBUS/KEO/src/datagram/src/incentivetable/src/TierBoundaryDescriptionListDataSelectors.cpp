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

#include <keo_datagram/incentivetable/TierBoundaryDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierBoundaryDescriptionListDataSelectors::
    TierBoundaryDescriptionListDataSelectors()
    : DataSelectors(), m_boundaryIdIsSet(false), m_boundaryId(0),
      m_boundaryTypeIsSet(false), m_boundaryType(TierBoundaryType())

{}

TierBoundaryDescriptionListDataSelectors::
    TierBoundaryDescriptionListDataSelectors(
        const xs_unsignedInt &c_boundaryId,
        const TierBoundaryType &c_boundaryType)
    : DataSelectors(), m_boundaryIdIsSet(true), m_boundaryId(c_boundaryId),
      m_boundaryTypeIsSet(true), m_boundaryType(c_boundaryType)

{}

bool TierBoundaryDescriptionListDataSelectors::operator==(
    const TierBoundaryDescriptionListDataSelectors &c_classObject) const {
  if (m_boundaryIdIsSet != c_classObject.m_boundaryIdIsSet ||
      (m_boundaryIdIsSet && (m_boundaryId != c_classObject.m_boundaryId))) {
    return false;
  }
  if (m_boundaryTypeIsSet != c_classObject.m_boundaryTypeIsSet ||
      (m_boundaryTypeIsSet &&
       (m_boundaryType != c_classObject.m_boundaryType))) {
    return false;
  }

  return true;
}

bool TierBoundaryDescriptionListDataSelectors::operator!=(
    const TierBoundaryDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierBoundaryDescriptionListDataSelectors::isEmpty() const {
  return !m_boundaryIdIsSet && !m_boundaryTypeIsSet;
}

DataSelectors::Type
TierBoundaryDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::
      TIER_BOUNDARY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr TierBoundaryDescriptionListDataSelectors::clone() const {
  return std::make_shared<TierBoundaryDescriptionListDataSelectors>(*this);
}

void TierBoundaryDescriptionListDataSelectors::setBoundaryId(
    const xs_unsignedInt &boundaryId) {
  m_boundaryId = boundaryId;
  m_boundaryIdIsSet = true;
}

const xs_unsignedInt &
TierBoundaryDescriptionListDataSelectors::getBoundaryId() const {
  return m_boundaryId;
}

void TierBoundaryDescriptionListDataSelectors::cleanBoundaryId() {
  m_boundaryId = 0;
  m_boundaryIdIsSet = false;
}

bool TierBoundaryDescriptionListDataSelectors::getBoundaryIdIsSet() const {
  return m_boundaryIdIsSet;
}

void TierBoundaryDescriptionListDataSelectors::setBoundaryType(
    const TierBoundaryType &boundaryType) {
  m_boundaryType = boundaryType;
  m_boundaryTypeIsSet = true;
}

const TierBoundaryType &
TierBoundaryDescriptionListDataSelectors::getBoundaryType() const {
  return m_boundaryType;
}

void TierBoundaryDescriptionListDataSelectors::cleanBoundaryType() {
  m_boundaryType = TierBoundaryType();
  m_boundaryTypeIsSet = false;
}

bool TierBoundaryDescriptionListDataSelectors::getBoundaryTypeIsSet() const {
  return m_boundaryTypeIsSet;
}

bool TierBoundaryDescriptionListDataSelectors::selects(
    const TierBoundaryDescriptionData &data) const {
  if (getBoundaryIdIsSet() &&
      (!data.getBoundaryIdIsSet() || getBoundaryId() != data.getBoundaryId())) {
    return false;
  }
  if (getBoundaryTypeIsSet() && (!data.getBoundaryTypeIsSet() ||
                                 getBoundaryType() != data.getBoundaryType())) {
    return false;
  }
  return true;
}

bool TierBoundaryDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"boundaryId", "boundaryType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryId", &m_boundaryId)) {
      m_boundaryIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryType", &m_boundaryType)) {
      m_boundaryTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierBoundaryDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_boundaryIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryId", m_boundaryId);
  }
  if (m_boundaryTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryType", m_boundaryType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram