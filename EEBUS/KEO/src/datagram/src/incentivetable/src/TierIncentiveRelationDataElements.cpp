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

#include <keo_datagram/incentivetable/TierIncentiveRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TierIncentiveRelationDataElements::TierIncentiveRelationDataElements()
    : DataElements(), m_tierIdIsSet(false), m_incentiveIdIsSet(false)

{}

TierIncentiveRelationDataElements::TierIncentiveRelationDataElements(
    xs_boolean c_tierIdIsSet, xs_boolean c_incentiveIdIsSet)
    : DataElements(), m_tierIdIsSet(c_tierIdIsSet),
      m_incentiveIdIsSet(c_incentiveIdIsSet)

{}

bool TierIncentiveRelationDataElements::
operator==(const TierIncentiveRelationDataElements &c_classObject) const {
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet) {
    return false;
  }
  if (m_incentiveIdIsSet != c_classObject.m_incentiveIdIsSet) {
    return false;
  }

  return true;
}

bool TierIncentiveRelationDataElements::
operator!=(const TierIncentiveRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TierIncentiveRelationDataElements::isEmpty() const {
  return !m_tierIdIsSet && !m_incentiveIdIsSet;
}

DataElements::Type TierIncentiveRelationDataElements::getDataType() const {
  return DataElements::Type::TIER_INCENTIVE_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TierIncentiveRelationDataElements::clone() const {
  return std::make_shared<TierIncentiveRelationDataElements>(*this);
}

void TierIncentiveRelationDataElements::setTierId() { m_tierIdIsSet = true; }

void TierIncentiveRelationDataElements::cleanTierId() { m_tierIdIsSet = false; }

bool TierIncentiveRelationDataElements::getTierIdIsSet() const {
  return m_tierIdIsSet;
}

void TierIncentiveRelationDataElements::setIncentiveId() {
  m_incentiveIdIsSet = true;
}

void TierIncentiveRelationDataElements::cleanIncentiveId() {
  m_incentiveIdIsSet = false;
}

bool TierIncentiveRelationDataElements::getIncentiveIdIsSet() const {
  return m_incentiveIdIsSet;
}

bool TierIncentiveRelationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tierId", "incentiveId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tierId")) {
      m_tierIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "incentiveId")) {
      m_incentiveIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TierIncentiveRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tierId");
  }
  if (m_incentiveIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("incentiveId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram