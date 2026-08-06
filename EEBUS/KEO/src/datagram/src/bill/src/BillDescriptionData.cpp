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

#include <keo_datagram/bill/BillDescriptionData.h>

#include <keo_datagram/bill/BillDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillDescriptionData::BillDescriptionData()
    : m_billIdIsSet(false), m_billId(0), m_billWriteableIsSet(false),
      m_billWriteable(false), m_updateRequiredIsSet(false),
      m_updateRequired(false), m_supportedBillTypeIsSet(false),
      m_supportedBillType(std::vector<BillType>())

{}

bool BillDescriptionData::
operator==(const BillDescriptionData &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet ||
      (m_billIdIsSet && (m_billId != c_classObject.m_billId))) {
    return false;
  }
  if (m_billWriteableIsSet != c_classObject.m_billWriteableIsSet ||
      (m_billWriteableIsSet &&
       (m_billWriteable != c_classObject.m_billWriteable))) {
    return false;
  }
  if (m_updateRequiredIsSet != c_classObject.m_updateRequiredIsSet ||
      (m_updateRequiredIsSet &&
       (m_updateRequired != c_classObject.m_updateRequired))) {
    return false;
  }
  if (m_supportedBillTypeIsSet != c_classObject.m_supportedBillTypeIsSet ||
      (m_supportedBillTypeIsSet &&
       (m_supportedBillType != c_classObject.m_supportedBillType))) {
    return false;
  }

  return true;
}

bool BillDescriptionData::
operator!=(const BillDescriptionData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillDescriptionData::isEmpty() const {
  return !m_billIdIsSet && !m_billWriteableIsSet && !m_updateRequiredIsSet &&
         !m_supportedBillTypeIsSet;
}

void BillDescriptionData::setBillId(const xs_unsignedInt &billId) {
  m_billId = billId;
  m_billIdIsSet = true;
}

const xs_unsignedInt &BillDescriptionData::getBillId() const {
  return m_billId;
}

void BillDescriptionData::cleanBillId() {
  m_billId = 0;
  m_billIdIsSet = false;
}

bool BillDescriptionData::getBillIdIsSet() const { return m_billIdIsSet; }

void BillDescriptionData::setBillWriteable(const xs_boolean &billWriteable) {
  m_billWriteable = billWriteable;
  m_billWriteableIsSet = true;
}

const xs_boolean &BillDescriptionData::getBillWriteable() const {
  return m_billWriteable;
}

void BillDescriptionData::cleanBillWriteable() {
  m_billWriteable = false;
  m_billWriteableIsSet = false;
}

bool BillDescriptionData::getBillWriteableIsSet() const {
  return m_billWriteableIsSet;
}

void BillDescriptionData::setUpdateRequired(const xs_boolean &updateRequired) {
  m_updateRequired = updateRequired;
  m_updateRequiredIsSet = true;
}

const xs_boolean &BillDescriptionData::getUpdateRequired() const {
  return m_updateRequired;
}

void BillDescriptionData::cleanUpdateRequired() {
  m_updateRequired = false;
  m_updateRequiredIsSet = false;
}

bool BillDescriptionData::getUpdateRequiredIsSet() const {
  return m_updateRequiredIsSet;
}

void BillDescriptionData::setSupportedBillType(
    const std::vector<BillType> &supportedBillType) {
  m_supportedBillType = supportedBillType;
  m_supportedBillTypeIsSet = true;
}

const std::vector<BillType> &BillDescriptionData::getSupportedBillType() const {
  return m_supportedBillType;
}

void BillDescriptionData::cleanSupportedBillType() {
  m_supportedBillType.clear();
  m_supportedBillTypeIsSet = false;
}

bool BillDescriptionData::getSupportedBillTypeIsSet() const {
  return m_supportedBillTypeIsSet;
}

BillDescriptionData
BillDescriptionData::reduce(const BillDescriptionDataElements &elements) const {
  BillDescriptionData dataOut;
  if (getBillIdIsSet() && elements.getBillIdIsSet()) {
    dataOut.setBillId(getBillId());
  }
  if (getBillWriteableIsSet() && elements.getBillWriteableIsSet()) {
    dataOut.setBillWriteable(getBillWriteable());
  }
  if (getUpdateRequiredIsSet() && elements.getUpdateRequiredIsSet()) {
    dataOut.setUpdateRequired(getUpdateRequired());
  }
  if (getSupportedBillTypeIsSet() && elements.getSupportedBillTypeIsSet()) {
    dataOut.setSupportedBillType(getSupportedBillType());
  }
  return dataOut;
}

bool BillDescriptionData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"billId", "billWriteable", "updateRequired",
                   "supportedBillType"})) {
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
                                   "billWriteable", &m_billWriteable)) {
      m_billWriteableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::get(static_cast<KeoJsonValue *>(&(*iter)),
                                   "updateRequired", &m_updateRequired)) {
      m_updateRequiredIsSet = true;
      ++iter;
    }
    if (iter != json->end() && KeoJsonTransformation::getList<BillType>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "supportedBillType", &m_supportedBillType)) {
      m_supportedBillTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillDescriptionData::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billId", m_billId);
  }
  if (m_billWriteableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("billWriteable", m_billWriteable);
  }
  if (m_updateRequiredIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::write("updateRequired", m_updateRequired);
  }
  if (m_supportedBillTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BillType>("supportedBillType",
                                                         m_supportedBillType);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram