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

#include <keo_datagram/incentivetable/IncentiveTableDescriptionDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableDescriptionDataSelectors::IncentiveTableDescriptionDataSelectors()
    : DataSelectors(), m_tariffDescriptionIsSet(false),
      m_tariffDescription(TariffDescriptionListDataSelectors())

{}

IncentiveTableDescriptionDataSelectors::IncentiveTableDescriptionDataSelectors(
    const TariffDescriptionListDataSelectors &c_tariffDescription) {
  setTariffDescription(c_tariffDescription);
}

bool IncentiveTableDescriptionDataSelectors::
operator==(const IncentiveTableDescriptionDataSelectors &c_classObject) const {
  if (m_tariffDescriptionIsSet != c_classObject.m_tariffDescriptionIsSet ||
      (m_tariffDescriptionIsSet &&
       (m_tariffDescription != c_classObject.m_tariffDescription))) {
    return false;
  }

  return true;
}

bool IncentiveTableDescriptionDataSelectors::
operator!=(const IncentiveTableDescriptionDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableDescriptionDataSelectors::isEmpty() const {
  return !m_tariffDescriptionIsSet;
}

DataSelectors::Type
IncentiveTableDescriptionDataSelectors::getDataType() const {
  return DataSelectors::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr IncentiveTableDescriptionDataSelectors::clone() const {
  return std::make_shared<IncentiveTableDescriptionDataSelectors>(*this);
}

void IncentiveTableDescriptionDataSelectors::setTariffDescription(
    const TariffDescriptionListDataSelectors &tariffDescription) {
  m_tariffDescription = tariffDescription;
  m_tariffDescriptionIsSet = true;
}

const TariffDescriptionListDataSelectors &
IncentiveTableDescriptionDataSelectors::getTariffDescription() const {
  return m_tariffDescription;
}

void IncentiveTableDescriptionDataSelectors::cleanTariffDescription() {
  m_tariffDescription = TariffDescriptionListDataSelectors();
  m_tariffDescriptionIsSet = false;
}

bool IncentiveTableDescriptionDataSelectors::getTariffDescriptionIsSet() const {
  return m_tariffDescriptionIsSet;
}

bool IncentiveTableDescriptionDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"tariffDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "tariffDescription", &m_tariffDescription)) {
      m_tariffDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableDescriptionDataSelectors::toJson() const {
  std::string result = "[";
  if (m_tariffDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("tariffDescription", m_tariffDescription);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram