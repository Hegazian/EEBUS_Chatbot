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

#include <keo_datagram/bill/BillListDataSelectors.h>

#include <algorithm>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillListDataSelectors::BillListDataSelectors()
    : DataSelectors(), m_billIdIsSet(false), m_billId(0),
      m_scopeTypeIsSet(false), m_scopeType(ScopeType())

{}

BillListDataSelectors::BillListDataSelectors(const xs_unsignedInt &c_billId,
                                             const ScopeType &c_scopeType)
    : DataSelectors(), m_billIdIsSet(true), m_billId(c_billId),
      m_scopeTypeIsSet(true), m_scopeType(c_scopeType)

{}

bool BillListDataSelectors::
operator==(const BillListDataSelectors &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet ||
      (m_billIdIsSet && (m_billId != c_classObject.m_billId))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
    return false;
  }

  return true;
}

bool BillListDataSelectors::
operator!=(const BillListDataSelectors &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillListDataSelectors::isEmpty() const {
  return !m_billIdIsSet && !m_scopeTypeIsSet;
}

DataSelectors::Type BillListDataSelectors::getDataType() const {
  return DataSelectors::Type::BILL_LIST_DATA_SELECTORS_TYPE;
}

DataSelectorsPtr BillListDataSelectors::clone() const {
  return std::make_shared<BillListDataSelectors>(*this);
}

void BillListDataSelectors::setBillId(const xs_unsignedInt &billId) {
  m_billId = billId;
  m_billIdIsSet = true;
}

const xs_unsignedInt &BillListDataSelectors::getBillId() const {
  return m_billId;
}

void BillListDataSelectors::cleanBillId() {
  m_billId = 0;
  m_billIdIsSet = false;
}

bool BillListDataSelectors::getBillIdIsSet() const { return m_billIdIsSet; }

void BillListDataSelectors::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &BillListDataSelectors::getScopeType() const {
  return m_scopeType;
}

void BillListDataSelectors::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool BillListDataSelectors::getScopeTypeIsSet() const {
  return m_scopeTypeIsSet;
}

bool BillListDataSelectors::selects(const BillData &data) const {
  if (getBillIdIsSet() &&
      (!data.getBillIdIsSet() || getBillId() != data.getBillId())) {
    return false;
  }
  if (getScopeTypeIsSet() &&
      (!data.getScopeTypeIsSet() || getScopeType() != data.getScopeType())) {
    return false;
  }
  return true;
}

bool BillListDataSelectors::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"billId", "scopeType"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "billId", &m_billId)) {
      m_billIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillListDataSelectors::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billId", m_billId);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram