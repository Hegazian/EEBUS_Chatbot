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

#include <keo_datagram/incentivetable/IncentiveTableData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableData::IncentiveTableData()
    : CmdData(), m_incentiveTableIsSet(false),
      m_incentiveTable(std::vector<IncentiveTable>())

{}

IncentiveTableData::IncentiveTableData(
    const std::vector<IncentiveTable> &c_incentiveTable) {
  setIncentiveTable(c_incentiveTable);
}

bool IncentiveTableData::
operator==(const IncentiveTableData &c_classObject) const {
  if (m_incentiveTableIsSet != c_classObject.m_incentiveTableIsSet ||
      (m_incentiveTableIsSet &&
       (m_incentiveTable != c_classObject.m_incentiveTable))) {
    return false;
  }

  return true;
}

bool IncentiveTableData::
operator!=(const IncentiveTableData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableData::isEmpty() const { return !m_incentiveTableIsSet; }

CmdData::Type IncentiveTableData::getDataType() const {
  return CmdData::Type::INCENTIVE_TABLE_DATA_TYPE;
}

CmdDataPtr IncentiveTableData::clone() const {
  return std::make_shared<IncentiveTableData>(*this);
}

void IncentiveTableData::setIncentiveTable(
    const std::vector<IncentiveTable> &incentiveTable) {
  m_incentiveTable = incentiveTable;
  m_incentiveTableIsSet = true;
}

const std::vector<IncentiveTable> &
IncentiveTableData::getIncentiveTable() const {
  return m_incentiveTable;
}

void IncentiveTableData::cleanIncentiveTable() {
  m_incentiveTable.clear();
  m_incentiveTableIsSet = false;
}

bool IncentiveTableData::getIncentiveTableIsSet() const {
  return m_incentiveTableIsSet;
}

CmdDataPtr
IncentiveTableData::reduce(const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<IncentiveTableData>(*this);
}

bool IncentiveTableData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"incentiveTable"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<IncentiveTable>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "incentiveTable", &m_incentiveTable)) {
      m_incentiveTableIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableData::toJson() const {
  std::string result = "[";
  if (m_incentiveTableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IncentiveTable>(
        "incentiveTable", m_incentiveTable);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram