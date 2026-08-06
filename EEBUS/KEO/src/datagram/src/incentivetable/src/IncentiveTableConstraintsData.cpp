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

#include <keo_datagram/incentivetable/IncentiveTableConstraintsData.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IncentiveTableConstraintsData::IncentiveTableConstraintsData()
    : CmdData(), m_incentiveTableConstraintsIsSet(false),
      m_incentiveTableConstraints(std::vector<IncentiveTableConstraints>())

{}

IncentiveTableConstraintsData::IncentiveTableConstraintsData(
    const std::vector<IncentiveTableConstraints> &c_incentiveTableConstraints) {
  setIncentiveTableConstraints(c_incentiveTableConstraints);
}

bool IncentiveTableConstraintsData::
operator==(const IncentiveTableConstraintsData &c_classObject) const {
  if (m_incentiveTableConstraintsIsSet !=
          c_classObject.m_incentiveTableConstraintsIsSet ||
      (m_incentiveTableConstraintsIsSet &&
       (m_incentiveTableConstraints !=
        c_classObject.m_incentiveTableConstraints))) {
    return false;
  }

  return true;
}

bool IncentiveTableConstraintsData::
operator!=(const IncentiveTableConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IncentiveTableConstraintsData::isEmpty() const {
  return !m_incentiveTableConstraintsIsSet;
}

CmdData::Type IncentiveTableConstraintsData::getDataType() const {
  return CmdData::Type::INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE;
}

CmdDataPtr IncentiveTableConstraintsData::clone() const {
  return std::make_shared<IncentiveTableConstraintsData>(*this);
}

void IncentiveTableConstraintsData::setIncentiveTableConstraints(
    const std::vector<IncentiveTableConstraints> &incentiveTableConstraints) {
  m_incentiveTableConstraints = incentiveTableConstraints;
  m_incentiveTableConstraintsIsSet = true;
}

const std::vector<IncentiveTableConstraints> &
IncentiveTableConstraintsData::getIncentiveTableConstraints() const {
  return m_incentiveTableConstraints;
}

void IncentiveTableConstraintsData::cleanIncentiveTableConstraints() {
  m_incentiveTableConstraints.clear();
  m_incentiveTableConstraintsIsSet = false;
}

bool IncentiveTableConstraintsData::getIncentiveTableConstraintsIsSet() const {
  return m_incentiveTableConstraintsIsSet;
}

CmdDataPtr IncentiveTableConstraintsData::reduce(
    const std::vector<Filter> &filters) const {
  // Class neither has selectors nor elements or the reduce method cannot be
  // generated
  // automatically
  (void)filters;
  return std::make_shared<IncentiveTableConstraintsData>(*this);
}

bool IncentiveTableConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"incentiveTableConstraints"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<IncentiveTableConstraints>(
            static_cast<KeoJsonValue *>(&(*iter)), "incentiveTableConstraints",
            &m_incentiveTableConstraints)) {
      m_incentiveTableConstraintsIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IncentiveTableConstraintsData::toJson() const {
  std::string result = "[";
  if (m_incentiveTableConstraintsIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IncentiveTableConstraints>(
        "incentiveTableConstraints", m_incentiveTableConstraints);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram