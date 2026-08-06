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

#include <keo_datagram/incentivetable/IncentiveTableDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableDescriptionDataElements::IncentiveTableDescriptionDataElements()
    : DataElements(), m_incentiveTableDescriptionIsSet(false),
      m_incentiveTableDescription(IncentiveTableDescriptionElements())

{}

IncentiveTableDescriptionDataElements::IncentiveTableDescriptionDataElements(
    const IncentiveTableDescriptionElements &c_incentiveTableDescription) {
  setIncentiveTableDescription(c_incentiveTableDescription);
}

bool IncentiveTableDescriptionDataElements::
operator==(const IncentiveTableDescriptionDataElements &c_classObject) const {
  if (m_incentiveTableDescriptionIsSet !=
          c_classObject.m_incentiveTableDescriptionIsSet ||
      (m_incentiveTableDescriptionIsSet &&
       (m_incentiveTableDescription !=
        c_classObject.m_incentiveTableDescription))) {
    return false;
  }

  return true;
}

bool IncentiveTableDescriptionDataElements::
operator!=(const IncentiveTableDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableDescriptionDataElements::isEmpty() const {
  return !m_incentiveTableDescriptionIsSet;
}

DataElements::Type IncentiveTableDescriptionDataElements::getDataType() const {
  return DataElements::Type::INCENTIVE_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr IncentiveTableDescriptionDataElements::clone() const {
  return std::make_shared<IncentiveTableDescriptionDataElements>(*this);
}

void IncentiveTableDescriptionDataElements::setIncentiveTableDescription(
    const IncentiveTableDescriptionElements &incentiveTableDescription) {
  m_incentiveTableDescription = incentiveTableDescription;
  m_incentiveTableDescriptionIsSet = true;
}

const IncentiveTableDescriptionElements &
IncentiveTableDescriptionDataElements::getIncentiveTableDescription() const {
  return m_incentiveTableDescription;
}

void IncentiveTableDescriptionDataElements::cleanIncentiveTableDescription() {
  m_incentiveTableDescription = IncentiveTableDescriptionElements();
  m_incentiveTableDescriptionIsSet = false;
}

bool IncentiveTableDescriptionDataElements::getIncentiveTableDescriptionIsSet()
    const {
  return m_incentiveTableDescriptionIsSet;
}

bool IncentiveTableDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveTableDescription"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveTableDescription",
                                   &m_incentiveTableDescription)) {
      m_incentiveTableDescriptionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_incentiveTableDescriptionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveTableDescription",
                                           m_incentiveTableDescription);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram