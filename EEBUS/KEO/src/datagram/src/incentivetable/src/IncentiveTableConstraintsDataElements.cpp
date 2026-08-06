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

#include <keo_datagram/incentivetable/IncentiveTableConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableConstraintsDataElements::IncentiveTableConstraintsDataElements()
    : DataElements(), m_incentiveTableConstraintsIsSet(false),
      m_incentiveTableConstraints(IncentiveTableConstraintsElements())

{}

IncentiveTableConstraintsDataElements::IncentiveTableConstraintsDataElements(
    const IncentiveTableConstraintsElements &c_incentiveTableConstraints) {
  setIncentiveTableConstraints(c_incentiveTableConstraints);
}

bool IncentiveTableConstraintsDataElements::
operator==(const IncentiveTableConstraintsDataElements &c_classObject) const {
  if (m_incentiveTableConstraintsIsSet !=
          c_classObject.m_incentiveTableConstraintsIsSet ||
      (m_incentiveTableConstraintsIsSet &&
       (m_incentiveTableConstraints !=
        c_classObject.m_incentiveTableConstraints))) {
    return false;
  }

  return true;
}

bool IncentiveTableConstraintsDataElements::
operator!=(const IncentiveTableConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableConstraintsDataElements::isEmpty() const {
  return !m_incentiveTableConstraintsIsSet;
}

DataElements::Type IncentiveTableConstraintsDataElements::getDataType() const {
  return DataElements::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr IncentiveTableConstraintsDataElements::clone() const {
  return std::make_shared<IncentiveTableConstraintsDataElements>(*this);
}

void IncentiveTableConstraintsDataElements::setIncentiveTableConstraints(
    const IncentiveTableConstraintsElements &incentiveTableConstraints) {
  m_incentiveTableConstraints = incentiveTableConstraints;
  m_incentiveTableConstraintsIsSet = true;
}

const IncentiveTableConstraintsElements &
IncentiveTableConstraintsDataElements::getIncentiveTableConstraints() const {
  return m_incentiveTableConstraints;
}

void IncentiveTableConstraintsDataElements::cleanIncentiveTableConstraints() {
  m_incentiveTableConstraints = IncentiveTableConstraintsElements();
  m_incentiveTableConstraintsIsSet = false;
}

bool IncentiveTableConstraintsDataElements::getIncentiveTableConstraintsIsSet()
    const {
  return m_incentiveTableConstraintsIsSet;
}

bool IncentiveTableConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveTableConstraints"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveTableConstraints",
                                   &m_incentiveTableConstraints)) {
      m_incentiveTableConstraintsIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_incentiveTableConstraintsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveTableConstraints",
                                           m_incentiveTableConstraints);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram