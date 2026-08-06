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

#include <keo_datagram/incentivetable/IncentiveTableDescriptionElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableDescriptionElements::IncentiveTableDescriptionElements()
    : m_tariffDescriptionIsSet(false),
      m_tariffDescription(TariffDescriptionDataElements()), m_tierIsSet(false),
      m_tier(IncentiveTableDescriptionTierElements())

{}

IncentiveTableDescriptionElements::IncentiveTableDescriptionElements(
    const TariffDescriptionDataElements &c_tariffDescription,
    const IncentiveTableDescriptionTierElements &c_tier)
    : m_tariffDescriptionIsSet(true), m_tariffDescription(c_tariffDescription),
      m_tierIsSet(true), m_tier(c_tier)

{}

bool IncentiveTableDescriptionElements::
operator==(const IncentiveTableDescriptionElements &c_classObject) const {
  if (m_tariffDescriptionIsSet != c_classObject.m_tariffDescriptionIsSet ||
      (m_tariffDescriptionIsSet &&
       (m_tariffDescription != c_classObject.m_tariffDescription))) {
    return false;
  }
  if (m_tierIsSet != c_classObject.m_tierIsSet ||
      (m_tierIsSet && (m_tier != c_classObject.m_tier))) {
    return false;
  }

  return true;
}

bool IncentiveTableDescriptionElements::
operator!=(const IncentiveTableDescriptionElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableDescriptionElements::isEmpty() const {
  return !m_tariffDescriptionIsSet && !m_tierIsSet;
}

void IncentiveTableDescriptionElements::setTariffDescription(
    const TariffDescriptionDataElements &tariffDescription) {
  m_tariffDescription = tariffDescription;
  m_tariffDescriptionIsSet = true;
}

const TariffDescriptionDataElements &
IncentiveTableDescriptionElements::getTariffDescription() const {
  return m_tariffDescription;
}

void IncentiveTableDescriptionElements::cleanTariffDescription() {
  m_tariffDescription = TariffDescriptionDataElements();
  m_tariffDescriptionIsSet = false;
}

bool IncentiveTableDescriptionElements::getTariffDescriptionIsSet() const {
  return m_tariffDescriptionIsSet;
}

void IncentiveTableDescriptionElements::setTier(
    const IncentiveTableDescriptionTierElements &tier) {
  m_tier = tier;
  m_tierIsSet = true;
}

const IncentiveTableDescriptionTierElements &
IncentiveTableDescriptionElements::getTier() const {
  return m_tier;
}

void IncentiveTableDescriptionElements::cleanTier() {
  m_tier = IncentiveTableDescriptionTierElements();
  m_tierIsSet = false;
}

bool IncentiveTableDescriptionElements::getTierIsSet() const {
  return m_tierIsSet;
}

bool IncentiveTableDescriptionElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"tariffDescription", "tier"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffDescription", &m_tariffDescription)) {
      m_tariffDescriptionIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tier", &m_tier)) {
      m_tierIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableDescriptionElements::toJson() const {
  std::string result = "[";
  if (m_tariffDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("tariffDescription", m_tariffDescription);
  }
  if (m_tierIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("tier", m_tier);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram