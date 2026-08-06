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

#include <keo_datagram/incentivetable/TariffTierRelationDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffTierRelationDataElements::TariffTierRelationDataElements()
    : DataElements(), m_tariffIdIsSet(false), m_tierIdIsSet(false)

{}

TariffTierRelationDataElements::TariffTierRelationDataElements(
    xs_boolean c_tariffIdIsSet, xs_boolean c_tierIdIsSet)
    : DataElements(), m_tariffIdIsSet(c_tariffIdIsSet),
      m_tierIdIsSet(c_tierIdIsSet)

{}

bool TariffTierRelationDataElements::
operator==(const TariffTierRelationDataElements &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet) {
    return false;
  }
  if (m_tierIdIsSet != c_classObject.m_tierIdIsSet) {
    return false;
  }

  return true;
}

bool TariffTierRelationDataElements::
operator!=(const TariffTierRelationDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffTierRelationDataElements::isEmpty() const {
  return !m_tariffIdIsSet && !m_tierIdIsSet;
}

DataElements::Type TariffTierRelationDataElements::getDataType() const {
  return DataElements::Type::TARIFF_TIER_RELATION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TariffTierRelationDataElements::clone() const {
  return std::make_shared<TariffTierRelationDataElements>(*this);
}

void TariffTierRelationDataElements::setTariffId() { m_tariffIdIsSet = true; }

void TariffTierRelationDataElements::cleanTariffId() {
  m_tariffIdIsSet = false;
}

bool TariffTierRelationDataElements::getTariffIdIsSet() const {
  return m_tariffIdIsSet;
}

void TariffTierRelationDataElements::setTierId() { m_tierIdIsSet = true; }

void TariffTierRelationDataElements::cleanTierId() { m_tierIdIsSet = false; }

bool TariffTierRelationDataElements::getTierIdIsSet() const {
  return m_tierIdIsSet;
}

bool TariffTierRelationDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tariffId", "tierId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tariffId")) {
      m_tariffIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "tierId")) {
      m_tierIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffTierRelationDataElements::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tariffId");
  }
  if (m_tierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tierId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram