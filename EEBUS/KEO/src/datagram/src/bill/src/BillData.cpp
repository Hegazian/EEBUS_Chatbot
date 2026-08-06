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

#include <keo_datagram/bill/BillData.h>

#include <keo_datagram/bill/BillDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillData::BillData()
    : m_billIdIsSet(false), m_billId(0), m_billTypeIsSet(false),
      m_billType(BillType()), m_scopeTypeIsSet(false), m_scopeType(ScopeType()),
      m_totalIsSet(false), m_total(BillPosition()), m_positionIsSet(false),
      m_position(std::vector<BillPosition>())

{}

bool BillData::operator==(const BillData &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet ||
      (m_billIdIsSet && (m_billId != c_classObject.m_billId))) {
    return false;
  }
  if (m_billTypeIsSet != c_classObject.m_billTypeIsSet ||
      (m_billTypeIsSet && (m_billType != c_classObject.m_billType))) {
    return false;
  }
  if (m_scopeTypeIsSet != c_classObject.m_scopeTypeIsSet ||
      (m_scopeTypeIsSet && (m_scopeType != c_classObject.m_scopeType))) {
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

bool BillData::operator!=(const BillData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillData::isEmpty() const {
  return !m_billIdIsSet && !m_billTypeIsSet && !m_scopeTypeIsSet &&
         !m_totalIsSet && !m_positionIsSet;
}

void BillData::setBillId(const xs_unsignedInt &billId) {
  m_billId = billId;
  m_billIdIsSet = true;
}

const xs_unsignedInt &BillData::getBillId() const { return m_billId; }

void BillData::cleanBillId() {
  m_billId = 0;
  m_billIdIsSet = false;
}

bool BillData::getBillIdIsSet() const { return m_billIdIsSet; }

void BillData::setBillType(const BillType &billType) {
  m_billType = billType;
  m_billTypeIsSet = true;
}

const BillType &BillData::getBillType() const { return m_billType; }

void BillData::cleanBillType() {
  m_billType = BillType();
  m_billTypeIsSet = false;
}

bool BillData::getBillTypeIsSet() const { return m_billTypeIsSet; }

void BillData::setScopeType(const ScopeType &scopeType) {
  m_scopeType = scopeType;
  m_scopeTypeIsSet = true;
}

const ScopeType &BillData::getScopeType() const { return m_scopeType; }

void BillData::cleanScopeType() {
  m_scopeType = ScopeType();
  m_scopeTypeIsSet = false;
}

bool BillData::getScopeTypeIsSet() const { return m_scopeTypeIsSet; }

void BillData::setTotal(const BillPosition &total) {
  m_total = total;
  m_totalIsSet = true;
}

const BillPosition &BillData::getTotal() const { return m_total; }

void BillData::cleanTotal() {
  m_total = BillPosition();
  m_totalIsSet = false;
}

bool BillData::getTotalIsSet() const { return m_totalIsSet; }

void BillData::setPosition(const std::vector<BillPosition> &position) {
  m_position = position;
  m_positionIsSet = true;
}

const std::vector<BillPosition> &BillData::getPosition() const {
  return m_position;
}

void BillData::cleanPosition() {
  m_position.clear();
  m_positionIsSet = false;
}

bool BillData::getPositionIsSet() const { return m_positionIsSet; }

BillData BillData::reduce(const BillDataElements &elements) const {
  BillData dataOut;
  if (getBillIdIsSet() && elements.getBillIdIsSet()) {
    dataOut.setBillId(getBillId());
  }
  if (getBillTypeIsSet() && elements.getBillTypeIsSet()) {
    dataOut.setBillType(getBillType());
  }
  if (getScopeTypeIsSet() && elements.getScopeTypeIsSet()) {
    dataOut.setScopeType(getScopeType());
  }
  if (getTotalIsSet() && elements.getTotalIsSet()) {
    dataOut.setTotal(getTotal().reduce(elements.getTotal()));
  }
  if (getPositionIsSet() && elements.getPositionIsSet()) {
    std::vector<BillPosition> values;
    for (const auto &value : getPosition()) {
      values.push_back(value.reduce(elements.getPosition()));
    }
    dataOut.setPosition(values);
  }
  return dataOut;
}

bool BillData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"billId", "billType", "scopeType", "total", "position"})) {
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
                                   "billType", &m_billType)) {
      m_billTypeIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "scopeType", &m_scopeType)) {
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
        KeoJsonTransformation::getList<BillPosition>(
            static_cast<KeoJsonValue *>(&(*iter)), "position", &m_position)) {
      m_positionIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillData::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billId", m_billId);
  }
  if (m_billTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billType", m_billType);
  }
  if (m_scopeTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("scopeType", m_scopeType);
  }
  if (m_totalIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("total", m_total);
  }
  if (m_positionIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<BillPosition>("position", m_position);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram