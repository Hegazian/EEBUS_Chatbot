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

#include <keo_datagram/bill/BillDescriptionListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillDescriptionListDataSelectors::BillDescriptionListDataSelectors()
    : DataSelectors(), m_billIdIsSet(false), m_billId(0)

{}

BillDescriptionListDataSelectors::BillDescriptionListDataSelectors(
    const xs_unsignedInt &c_billId) {
  setBillId(c_billId);
}

bool BillDescriptionListDataSelectors::
operator==(const BillDescriptionListDataSelectors &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet ||
      (m_billIdIsSet && (m_billId != c_classObject.m_billId))) {
    return false;
  }

  return true;
}

bool BillDescriptionListDataSelectors::
operator!=(const BillDescriptionListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillDescriptionListDataSelectors::isEmpty() const {
  return !m_billIdIsSet;
}

DataSelectors::Type BillDescriptionListDataSelectors::getDataType() const {
  return DataSelectors::Type::BILL_DESCRIPTION_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr BillDescriptionListDataSelectors::clone() const {
  return std::make_shared<BillDescriptionListDataSelectors>(*this);
}

void BillDescriptionListDataSelectors::setBillId(const xs_unsignedInt &billId) {
  m_billId = billId;
  m_billIdIsSet = true;
}

const xs_unsignedInt &BillDescriptionListDataSelectors::getBillId() const {
  return m_billId;
}

void BillDescriptionListDataSelectors::cleanBillId() {
  m_billId = 0;
  m_billIdIsSet = false;
}

bool BillDescriptionListDataSelectors::getBillIdIsSet() const {
  return m_billIdIsSet;
}

bool BillDescriptionListDataSelectors::selects(
    const BillDescriptionData &data) const {
  if (getBillIdIsSet() &&
      (!data.getBillIdIsSet() || getBillId() != data.getBillId())) {
    return false;
  }
  return true;
}

bool BillDescriptionListDataSelectors::fromJson(KeoJsonValue *json) {
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

std::string BillDescriptionListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billId", m_billId);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram