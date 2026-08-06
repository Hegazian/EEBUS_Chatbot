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

#include <keo_datagram/incentivetable/TariffDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

TariffDataElements::TariffDataElements()
    : DataElements(), m_tariffIdIsSet(false), m_activeTierIdIsSet(false)

{}

TariffDataElements::TariffDataElements(xs_boolean c_tariffIdIsSet,
                                       xs_boolean c_activeTierIdIsSet)
    : DataElements(), m_tariffIdIsSet(c_tariffIdIsSet),
      m_activeTierIdIsSet(c_activeTierIdIsSet)

{}

bool TariffDataElements::
operator==(const TariffDataElements &c_classObject) const {
  if (m_tariffIdIsSet != c_classObject.m_tariffIdIsSet) {
    return false;
  }
  if (m_activeTierIdIsSet != c_classObject.m_activeTierIdIsSet) {
    return false;
  }

  return true;
}

bool TariffDataElements::
operator!=(const TariffDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool TariffDataElements::isEmpty() const {
  return !m_tariffIdIsSet && !m_activeTierIdIsSet;
}

DataElements::Type TariffDataElements::getDataType() const {
  return DataElements::Type::TARIFF_DATA_ELEMENTS_TYPE;
}

DataElementsPtr TariffDataElements::clone() const {
  return std::make_shared<TariffDataElements>(*this);
}

void TariffDataElements::setTariffId() { m_tariffIdIsSet = true; }

void TariffDataElements::cleanTariffId() { m_tariffIdIsSet = false; }

bool TariffDataElements::getTariffIdIsSet() const { return m_tariffIdIsSet; }

void TariffDataElements::setActiveTierId() { m_activeTierIdIsSet = true; }

void TariffDataElements::cleanActiveTierId() { m_activeTierIdIsSet = false; }

bool TariffDataElements::getActiveTierIdIsSet() const {
  return m_activeTierIdIsSet;
}

bool TariffDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"tariffId", "activeTierId"})) {
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
                                     "activeTierId")) {
      m_activeTierIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string TariffDataElements::toJson() const {
  std::string result = "[";
  if (m_tariffIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("tariffId");
  }
  if (m_activeTierIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("activeTierId");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram