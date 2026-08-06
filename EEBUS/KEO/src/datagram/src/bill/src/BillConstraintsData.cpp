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

#include <keo_datagram/bill/BillConstraintsData.h>

#include <keo_datagram/bill/BillConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillConstraintsData::BillConstraintsData()
    : m_billIdIsSet(false), m_billId(0), m_positionCountMinIsSet(false),
      m_positionCountMin(0), m_positionCountMaxIsSet(false),
      m_positionCountMax(0)

{}

BillConstraintsData::BillConstraintsData(
    const xs_unsignedInt &c_billId, const xs_unsignedInt &c_positionCountMin,
    const xs_unsignedInt &c_positionCountMax)
    : m_billIdIsSet(true), m_billId(c_billId), m_positionCountMinIsSet(true),
      m_positionCountMin(c_positionCountMin), m_positionCountMaxIsSet(true),
      m_positionCountMax(c_positionCountMax)

{}

bool BillConstraintsData::
operator==(const BillConstraintsData &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet ||
      (m_billIdIsSet && (m_billId != c_classObject.m_billId))) {
    return false;
  }
  if (m_positionCountMinIsSet != c_classObject.m_positionCountMinIsSet ||
      (m_positionCountMinIsSet &&
       (m_positionCountMin != c_classObject.m_positionCountMin))) {
    return false;
  }
  if (m_positionCountMaxIsSet != c_classObject.m_positionCountMaxIsSet ||
      (m_positionCountMaxIsSet &&
       (m_positionCountMax != c_classObject.m_positionCountMax))) {
    return false;
  }

  return true;
}

bool BillConstraintsData::
operator!=(const BillConstraintsData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillConstraintsData::isEmpty() const {
  return !m_billIdIsSet && !m_positionCountMinIsSet && !m_positionCountMaxIsSet;
}

void BillConstraintsData::setBillId(const xs_unsignedInt &billId) {
  m_billId = billId;
  m_billIdIsSet = true;
}

const xs_unsignedInt &BillConstraintsData::getBillId() const {
  return m_billId;
}

void BillConstraintsData::cleanBillId() {
  m_billId = 0;
  m_billIdIsSet = false;
}

bool BillConstraintsData::getBillIdIsSet() const { return m_billIdIsSet; }

void BillConstraintsData::setPositionCountMin(
    const xs_unsignedInt &positionCountMin) {
  m_positionCountMin = positionCountMin;
  m_positionCountMinIsSet = true;
}

const xs_unsignedInt &BillConstraintsData::getPositionCountMin() const {
  return m_positionCountMin;
}

void BillConstraintsData::cleanPositionCountMin() {
  m_positionCountMin = 0;
  m_positionCountMinIsSet = false;
}

bool BillConstraintsData::getPositionCountMinIsSet() const {
  return m_positionCountMinIsSet;
}

void BillConstraintsData::setPositionCountMax(
    const xs_unsignedInt &positionCountMax) {
  m_positionCountMax = positionCountMax;
  m_positionCountMaxIsSet = true;
}

const xs_unsignedInt &BillConstraintsData::getPositionCountMax() const {
  return m_positionCountMax;
}

void BillConstraintsData::cleanPositionCountMax() {
  m_positionCountMax = 0;
  m_positionCountMaxIsSet = false;
}

bool BillConstraintsData::getPositionCountMaxIsSet() const {
  return m_positionCountMaxIsSet;
}

BillConstraintsData
BillConstraintsData::reduce(const BillConstraintsDataElements &elements) const {
  BillConstraintsData dataOut;
  if (getBillIdIsSet() && elements.getBillIdIsSet()) {
    dataOut.setBillId(getBillId());
  }
  if (getPositionCountMinIsSet() && elements.getPositionCountMinIsSet()) {
    dataOut.setPositionCountMin(getPositionCountMin());
  }
  if (getPositionCountMaxIsSet() && elements.getPositionCountMaxIsSet()) {
    dataOut.setPositionCountMax(getPositionCountMax());
  }
  return dataOut;
}

bool BillConstraintsData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"billId", "positionCountMin", "positionCountMax"})) {
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
                                   "positionCountMin", &m_positionCountMin)) {
      m_positionCountMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "positionCountMax", &m_positionCountMax)) {
      m_positionCountMaxIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillConstraintsData::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billId", m_billId);
  }
  if (m_positionCountMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("positionCountMin", m_positionCountMin);
  }
  if (m_positionCountMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::write("positionCountMax", m_positionCountMax);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram