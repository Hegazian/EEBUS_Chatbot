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

#include <keo_datagram/incentivetable/IncentiveTableDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableDataElements::IncentiveTableDataElements()
    : DataElements(), m_incentiveTableIsSet(false),
      m_incentiveTable(IncentiveTableElements())

{}

IncentiveTableDataElements::IncentiveTableDataElements(
    const IncentiveTableElements &c_incentiveTable) {
  setIncentiveTable(c_incentiveTable);
}

bool IncentiveTableDataElements::
operator==(const IncentiveTableDataElements &c_classObject) const {
  if (m_incentiveTableIsSet != c_classObject.m_incentiveTableIsSet ||
      (m_incentiveTableIsSet &&
       (m_incentiveTable != c_classObject.m_incentiveTable))) {
    return false;
  }

  return true;
}

bool IncentiveTableDataElements::
operator!=(const IncentiveTableDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableDataElements::isEmpty() const {
  return !m_incentiveTableIsSet;
}

DataElements::Type IncentiveTableDataElements::getDataType() const {
  return DataElements::Type::INCENTIVE_TABLE_DATA_ELEMENTS_TYPE;
}

DataElementsPtr IncentiveTableDataElements::clone() const {
  return std::make_shared<IncentiveTableDataElements>(*this);
}

void IncentiveTableDataElements::setIncentiveTable(
    const IncentiveTableElements &incentiveTable) {
  m_incentiveTable = incentiveTable;
  m_incentiveTableIsSet = true;
}

const IncentiveTableElements &
IncentiveTableDataElements::getIncentiveTable() const {
  return m_incentiveTable;
}

void IncentiveTableDataElements::cleanIncentiveTable() {
  m_incentiveTable = IncentiveTableElements();
  m_incentiveTableIsSet = false;
}

bool IncentiveTableDataElements::getIncentiveTableIsSet() const {
  return m_incentiveTableIsSet;
}

bool IncentiveTableDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"incentiveTable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveTable", &m_incentiveTable)) {
      m_incentiveTableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableDataElements::toJson() const {
  std::string result = "[";
  if (m_incentiveTableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("incentiveTable", m_incentiveTable);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram