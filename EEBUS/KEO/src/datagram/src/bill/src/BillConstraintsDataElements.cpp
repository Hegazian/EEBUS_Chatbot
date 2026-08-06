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

#include <keo_datagram/bill/BillConstraintsDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillConstraintsDataElements::BillConstraintsDataElements()
    : DataElements(), m_billIdIsSet(false), m_positionCountMinIsSet(false),
      m_positionCountMaxIsSet(false)

{}

BillConstraintsDataElements::BillConstraintsDataElements(
    xs_boolean c_billIdIsSet, xs_boolean c_positionCountMinIsSet,
    xs_boolean c_positionCountMaxIsSet)
    : DataElements(), m_billIdIsSet(c_billIdIsSet),
      m_positionCountMinIsSet(c_positionCountMinIsSet),
      m_positionCountMaxIsSet(c_positionCountMaxIsSet)

{}

bool BillConstraintsDataElements::
operator==(const BillConstraintsDataElements &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet) {
    return false;
  }
  if (m_positionCountMinIsSet != c_classObject.m_positionCountMinIsSet) {
    return false;
  }
  if (m_positionCountMaxIsSet != c_classObject.m_positionCountMaxIsSet) {
    return false;
  }

  return true;
}

bool BillConstraintsDataElements::
operator!=(const BillConstraintsDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillConstraintsDataElements::isEmpty() const {
  return !m_billIdIsSet && !m_positionCountMinIsSet && !m_positionCountMaxIsSet;
}

DataElements::Type BillConstraintsDataElements::getDataType() const {
  return DataElements::Type::BILL_CONSTRAINTS_DATA_ELEMENTS_TYPE;
}

DataElementsPtr BillConstraintsDataElements::clone() const {
  return std::make_shared<BillConstraintsDataElements>(*this);
}

void BillConstraintsDataElements::setBillId() { m_billIdIsSet = true; }

void BillConstraintsDataElements::cleanBillId() { m_billIdIsSet = false; }

bool BillConstraintsDataElements::getBillIdIsSet() const {
  return m_billIdIsSet;
}

void BillConstraintsDataElements::setPositionCountMin() {
  m_positionCountMinIsSet = true;
}

void BillConstraintsDataElements::cleanPositionCountMin() {
  m_positionCountMinIsSet = false;
}

bool BillConstraintsDataElements::getPositionCountMinIsSet() const {
  return m_positionCountMinIsSet;
}

void BillConstraintsDataElements::setPositionCountMax() {
  m_positionCountMaxIsSet = true;
}

void BillConstraintsDataElements::cleanPositionCountMax() {
  m_positionCountMaxIsSet = false;
}

bool BillConstraintsDataElements::getPositionCountMaxIsSet() const {
  return m_positionCountMaxIsSet;
}

bool BillConstraintsDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"billId", "positionCountMin", "positionCountMax"})) {
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
                                     "positionCountMin")) {
      m_positionCountMinIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "positionCountMax")) {
      m_positionCountMaxIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillConstraintsDataElements::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("billId");
  }
  if (m_positionCountMinIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positionCountMin");
  }
  if (m_positionCountMaxIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("positionCountMax");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram