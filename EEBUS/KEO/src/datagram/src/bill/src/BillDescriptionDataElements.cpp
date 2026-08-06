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

#include <keo_datagram/bill/BillDescriptionDataElements.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillDescriptionDataElements::BillDescriptionDataElements()
    : DataElements(), m_billIdIsSet(false), m_billWriteableIsSet(false),
      m_updateRequiredIsSet(false), m_supportedBillTypeIsSet(false)

{}

bool BillDescriptionDataElements::
operator==(const BillDescriptionDataElements &c_classObject) const {
  if (m_billIdIsSet != c_classObject.m_billIdIsSet) {
    return false;
  }
  if (m_billWriteableIsSet != c_classObject.m_billWriteableIsSet) {
    return false;
  }
  if (m_updateRequiredIsSet != c_classObject.m_updateRequiredIsSet) {
    return false;
  }
  if (m_supportedBillTypeIsSet != c_classObject.m_supportedBillTypeIsSet) {
    return false;
  }

  return true;
}

bool BillDescriptionDataElements::
operator!=(const BillDescriptionDataElements &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillDescriptionDataElements::isEmpty() const {
  return !m_billIdIsSet && !m_billWriteableIsSet && !m_updateRequiredIsSet &&
         !m_supportedBillTypeIsSet;
}

DataElements::Type BillDescriptionDataElements::getDataType() const {
  return DataElements::Type::BILL_DESCRIPTION_DATA_ELEMENTS_TYPE;
}

DataElementsPtr BillDescriptionDataElements::clone() const {
  return std::make_shared<BillDescriptionDataElements>(*this);
}

void BillDescriptionDataElements::setBillId() { m_billIdIsSet = true; }

void BillDescriptionDataElements::cleanBillId() { m_billIdIsSet = false; }

bool BillDescriptionDataElements::getBillIdIsSet() const {
  return m_billIdIsSet;
}

void BillDescriptionDataElements::setBillWriteable() {
  m_billWriteableIsSet = true;
}

void BillDescriptionDataElements::cleanBillWriteable() {
  m_billWriteableIsSet = false;
}

bool BillDescriptionDataElements::getBillWriteableIsSet() const {
  return m_billWriteableIsSet;
}

void BillDescriptionDataElements::setUpdateRequired() {
  m_updateRequiredIsSet = true;
}

void BillDescriptionDataElements::cleanUpdateRequired() {
  m_updateRequiredIsSet = false;
}

bool BillDescriptionDataElements::getUpdateRequiredIsSet() const {
  return m_updateRequiredIsSet;
}

void BillDescriptionDataElements::setSupportedBillType() {
  m_supportedBillTypeIsSet = true;
}

void BillDescriptionDataElements::cleanSupportedBillType() {
  m_supportedBillTypeIsSet = false;
}

bool BillDescriptionDataElements::getSupportedBillTypeIsSet() const {
  return m_supportedBillTypeIsSet;
}

bool BillDescriptionDataElements::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"billId", "billWriteable", "updateRequired",
                   "supportedBillType"})) {
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
                                     "billWriteable")) {
      m_billWriteableIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "updateRequired")) {
      m_updateRequiredIsSet = true;
      ++iter;
    }
    if (iter != json->end() &&
        KeoJsonTransformation::isTag(static_cast<KeoJsonValue *>(&(*iter)),
                                     "supportedBillType")) {
      m_supportedBillTypeIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillDescriptionDataElements::toJson() const {
  std::string result = "[";
  if (m_billIdIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("billId");
  }
  if (m_billWriteableIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("billWriteable");
  }
  if (m_updateRequiredIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("updateRequired");
  }
  if (m_supportedBillTypeIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeTag("supportedBillType");
  }
  result += "]";
  return result;
}

} // namespace keo_datagram