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

#include <algorithm>
#include <keo_datagram/bill/BillListData.h>
#include <keo_datagram/bill/BillListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillListData::BillListData()
    : CmdData(), m_billDataIsSet(false), m_billData(std::vector<BillData>())

{}

BillListData::BillListData(const std::vector<BillData> &c_billData) {
  setBillData(c_billData);
}

bool BillListData::operator==(const BillListData &c_classObject) const {
  if (m_billDataIsSet != c_classObject.m_billDataIsSet ||
      (m_billDataIsSet && (m_billData != c_classObject.m_billData))) {
    return false;
  }

  return true;
}

bool BillListData::operator!=(const BillListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillListData::isEmpty() const { return !m_billDataIsSet; }

CmdData::Type BillListData::getDataType() const {
  return CmdData::Type::BILL_LIST_DATA_TYPE;
}

CmdDataPtr BillListData::clone() const {
  return std::make_shared<BillListData>(*this);
}

void BillListData::setBillData(const std::vector<BillData> &billData) {
  m_billData = billData;
  m_billDataIsSet = true;
}

const std::vector<BillData> &BillListData::getBillData() const {
  return m_billData;
}

void BillListData::cleanBillData() {
  m_billData.clear();
  m_billDataIsSet = false;
}

bool BillListData::getBillDataIsSet() const { return m_billDataIsSet; }

CmdDataPtr BillListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<BillData> dataOut;
  for (const auto &data : getBillData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          BillListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<BillListDataSelectors>(
                  baseSelectorsClass);
          if (selectors) {
            if (selectors->selects(data)) {
              // The first selecting selector selects
              isSelected = true;
              break;
            }
          } else {
            // Selectors of wrong type are ignored and don't select anything.
          }
        }
        if (isSelected) {
          const BillDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<BillDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(BillData(data));
          }
        }
      } else {
        return std::make_shared<BillListData>(*this);
      }
    } else {
      return std::make_shared<BillListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<BillListData>(dataOut);
  } else {
    return std::make_shared<BillListData>();
  }
}

bool BillListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"billData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BillData>(
            static_cast<KeoJsonValue *>(&(*iter)), "billData", &m_billData)) {
      m_billDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillListData::toJson() const {
  std::string result = "[";
  if (m_billDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<BillData>("billData", m_billData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram