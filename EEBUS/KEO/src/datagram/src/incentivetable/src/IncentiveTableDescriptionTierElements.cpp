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

#include <keo_datagram/incentivetable/IncentiveTableDescriptionTierElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableDescriptionTierElements::IncentiveTableDescriptionTierElements()
    : m_tierDescriptionIsSet(false),
      m_tierDescription(TierDescriptionDataElements()),
      m_boundaryDescriptionIsSet(false),
      m_boundaryDescription(TierBoundaryDescriptionDataElements()),
      m_incentiveDescriptionIsSet(false),
      m_incentiveDescription(IncentiveDescriptionDataElements())

{}

IncentiveTableDescriptionTierElements::IncentiveTableDescriptionTierElements(
    const TierDescriptionDataElements &c_tierDescription,
    const TierBoundaryDescriptionDataElements &c_boundaryDescription,
    const IncentiveDescriptionDataElements &c_incentiveDescription)
    : m_tierDescriptionIsSet(true), m_tierDescription(c_tierDescription),
      m_boundaryDescriptionIsSet(true),
      m_boundaryDescription(c_boundaryDescription),
      m_incentiveDescriptionIsSet(true),
      m_incentiveDescription(c_incentiveDescription)

{}

bool IncentiveTableDescriptionTierElements::
operator==(const IncentiveTableDescriptionTierElements &c_classObject) const {
  if (m_tierDescriptionIsSet != c_classObject.m_tierDescriptionIsSet ||
      (m_tierDescriptionIsSet &&
       (m_tierDescription != c_classObject.m_tierDescription))) {
    return false;
  }
  if (m_boundaryDescriptionIsSet != c_classObject.m_boundaryDescriptionIsSet ||
      (m_boundaryDescriptionIsSet &&
       (m_boundaryDescription != c_classObject.m_boundaryDescription))) {
    return false;
  }
  if (m_incentiveDescriptionIsSet !=
          c_classObject.m_incentiveDescriptionIsSet ||
      (m_incentiveDescriptionIsSet &&
       (m_incentiveDescription != c_classObject.m_incentiveDescription))) {
    return false;
  }

  return true;
}

bool IncentiveTableDescriptionTierElements::
operator!=(const IncentiveTableDescriptionTierElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableDescriptionTierElements::isEmpty() const {
  return !m_tierDescriptionIsSet && !m_boundaryDescriptionIsSet &&
         !m_incentiveDescriptionIsSet;
}

void IncentiveTableDescriptionTierElements::setTierDescription(
    const TierDescriptionDataElements &tierDescription) {
  m_tierDescription = tierDescription;
  m_tierDescriptionIsSet = true;
}

const TierDescriptionDataElements &
IncentiveTableDescriptionTierElements::getTierDescription() const {
  return m_tierDescription;
}

void IncentiveTableDescriptionTierElements::cleanTierDescription() {
  m_tierDescription = TierDescriptionDataElements();
  m_tierDescriptionIsSet = false;
}

bool IncentiveTableDescriptionTierElements::getTierDescriptionIsSet() const {
  return m_tierDescriptionIsSet;
}

void IncentiveTableDescriptionTierElements::setBoundaryDescription(
    const TierBoundaryDescriptionDataElements &boundaryDescription) {
  m_boundaryDescription = boundaryDescription;
  m_boundaryDescriptionIsSet = true;
}

const TierBoundaryDescriptionDataElements &
IncentiveTableDescriptionTierElements::getBoundaryDescription() const {
  return m_boundaryDescription;
}

void IncentiveTableDescriptionTierElements::cleanBoundaryDescription() {
  m_boundaryDescription = TierBoundaryDescriptionDataElements();
  m_boundaryDescriptionIsSet = false;
}

bool IncentiveTableDescriptionTierElements::getBoundaryDescriptionIsSet()
    const {
  return m_boundaryDescriptionIsSet;
}

void IncentiveTableDescriptionTierElements::setIncentiveDescription(
    const IncentiveDescriptionDataElements &incentiveDescription) {
  m_incentiveDescription = incentiveDescription;
  m_incentiveDescriptionIsSet = true;
}

const IncentiveDescriptionDataElements &
IncentiveTableDescriptionTierElements::getIncentiveDescription() const {
  return m_incentiveDescription;
}

void IncentiveTableDescriptionTierElements::cleanIncentiveDescription() {
  m_incentiveDescription = IncentiveDescriptionDataElements();
  m_incentiveDescriptionIsSet = false;
}

bool IncentiveTableDescriptionTierElements::getIncentiveDescriptionIsSet()
    const {
  return m_incentiveDescriptionIsSet;
}

bool IncentiveTableDescriptionTierElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tierDescription", "boundaryDescription",
                   "incentiveDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tierDescription", &m_tierDescription)) {
      m_tierDescriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "boundaryDescription",
                                   &m_boundaryDescription)) {
      m_boundaryDescriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveDescription",
                                   &m_incentiveDescription)) {
      m_incentiveDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableDescriptionTierElements::toJson() const {
  std::string result = "[";
  if (m_tierDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("tierDescription", m_tierDescription);
  }
  if (m_boundaryDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("boundaryDescription",
                                           m_boundaryDescription);
  }
  if (m_incentiveDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveDescription",
                                           m_incentiveDescription);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram