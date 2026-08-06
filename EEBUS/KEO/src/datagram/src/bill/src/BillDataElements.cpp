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

#include <keo_datagram/bill/BillDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillDataElements::BillDataElements()
    : DataElements(), m_billIdIsSet(false), m_billTypeIsSet(false),
      m_scopeTypeIsSet(false), m_totalIsSet(false),
      m_total(BillPositionElements()), m_positionIsSet(false),
      m_position(BillPositionElements())

{}

bool BillDataElements::operator==(const BillDataElements &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet) {
    return false;
  }
  if (m_billTypeIsSet != c_classObject.m_billTypeIsSet) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet) {
    return false;
  }
  if (m_totalIsSet != c_classObject.m_totalIsSet ||
      (m_totalIsSet && (m_total != c_classObject.m_total))) {
    return false;
  }
  if (m_positionIsSet != c_classObject.m_positionIsSet ||
      (m_positionIsSet && (m_position != c_classObject.m_position))) {
    return false;
  }

  return true;
}

bool BillDataElements::operator!=(const BillDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillDataElements::isEmpty() const {
  return !m_billIdIsSet && !m_billTypeIsSet && !m_scopeTypeIsSet &&
         !m_totalIsSet && !m_positionIsSet;
}

DataElements::Type BillDataElements::getDataType() const {
  return DataElements::Type::BILL_DATA_ELEMENTS_TYPE;
}

DataElementsPtr BillDataElements::clone() const {
  return std::make_shared<BillDataElements>(*this);
}

void BillDataElements::setBillId() { m_billIdIsSet = true; }

void BillDataElements::cleanBillId() { m_billIdIsSet = false; }

bool BillDataElements::getBillIdIsSet() const { return m_billIdIsSet; }

void BillDataElements::setBillType() { m_billTypeIsSet = true; }

void BillDataElements::cleanBillType() { m_billTypeIsSet = false; }

bool BillDataElements::getBillTypeIsSet() const { return m_billTypeIsSet; }

void BillDataElements::setScopeType() { m_scopeTypeIsSet = true; }

void BillDataElements::cleanScopeType() { m_scopeTypeIsSet = false; }

bool BillDataElements::getScopeTypeIsSet() const { return m_scopeTypeIsSet; }

void BillDataElements::setTotal(const BillPositionElements &total) {
  m_total = total;
  m_totalIsSet = true;
}

const BillPositionElements &BillDataElements::getTotal() const {
  return m_total;
}

void BillDataElements::cleanTotal() {
  m_total = BillPositionElements();
  m_totalIsSet = false;
}

bool BillDataElements::getTotalIsSet() const { return m_totalIsSet; }

void BillDataElements::setPosition(const BillPositionElements &position) {
  m_position = position;
  m_positionIsSet = true;
}

const BillPositionElements &BillDataElements::getPosition() const {
  return m_position;
}

void BillDataElements::cleanPosition() {
  m_position = BillPositionElements();
  m_positionIsSet = false;
}

bool BillDataElements::getPositionIsSet() const { return m_positionIsSet; }

bool BillDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"billId", "billType", "scopeType", "total", "position"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "billId")) {
      m_billIdIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "billType")) {
      m_billTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "scopeType")) {
      m_scopeTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "total", &m_total)) {
      m_totalIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "position", &m_position)) {
      m_positionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillDataElements::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("billId");
  }
  if (m_billTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("billType");
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("scopeType");
  }
  if (m_totalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("total", m_total);
  }
  if (m_positionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("position", m_position);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram