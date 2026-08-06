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

#include <keo_datagram/bill/BillConstraintsListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillConstraintsListDataSelectors::BillConstraintsListDataSelectors()
    : DataSelectors(), m_billIdIsSet(false), m_billId(0)

{}

BillConstraintsListDataSelectors::BillConstraintsListDataSelectors(
    const xs_unsignedInt &c_billId) {
  setBillId(c_billId);
}

bool BillConstraintsListDataSelectors::
operator==(const BillConstraintsListDataSelectors &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet ||
      (m_billIdIsSet && (m_billId != c_classObject.m_billId))) {
    return false;
  }

  return true;
}

bool BillConstraintsListDataSelectors::
operator!=(const BillConstraintsListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillConstraintsListDataSelectors::isEmpty() const {
  return !m_billIdIsSet;
}

DataSelectors::Type BillConstraintsListDataSelectors::getDataType() const {
  return DataSelectors::Type::BILL_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr BillConstraintsListDataSelectors::clone() const {
  return std::make_shared<BillConstraintsListDataSelectors>(*this);
}

void BillConstraintsListDataSelectors::setBillId(const xs_unsignedInt &billId) {
  m_billId = billId;
  m_billIdIsSet = true;
}

const xs_unsignedInt &BillConstraintsListDataSelectors::getBillId() const {
  return m_billId;
}

void BillConstraintsListDataSelectors::cleanBillId() {
  m_billId = 0;
  m_billIdIsSet = false;
}

bool BillConstraintsListDataSelectors::getBillIdIsSet() const {
  return m_billIdIsSet;
}

bool BillConstraintsListDataSelectors::selects(
    const BillConstraintsData &data) const {
  if (getBillIdIsSet() &&
      (!data.getBillIdIsSet() || getBillId() != data.getBillId())) {
    return false;
  }
  return true;
}

bool BillConstraintsListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"billId"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "billId", &m_billId)) {
      m_billIdIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillConstraintsListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billId", m_billId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram