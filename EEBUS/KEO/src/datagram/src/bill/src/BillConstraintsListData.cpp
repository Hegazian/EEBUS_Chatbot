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
#include <keo_datagram/bill/BillConstraintsListData.h>
#include <keo_datagram/bill/BillConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillConstraintsListData::BillConstraintsListData()
    : CmdData(), m_billConstraintsDataIsSet(false),
      m_billConstraintsData(std::vector<BillConstraintsData>())

{}

BillConstraintsListData::BillConstraintsListData(
    const std::vector<BillConstraintsData> &c_billConstraintsData) {
  setBillConstraintsData(c_billConstraintsData);
}

bool BillConstraintsListData::
operator==(const BillConstraintsListData &c_classObject) const {
  if (m_billConstraintsDataIsSet != c_classObject.m_billConstraintsDataIsSet ||
      (m_billConstraintsDataIsSet &&
       (m_billConstraintsData != c_classObject.m_billConstraintsData))) {
    return false;
  }

  return true;
}

bool BillConstraintsListData::
operator!=(const BillConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillConstraintsListData::isEmpty() const {
  return !m_billConstraintsDataIsSet;
}

CmdData::Type BillConstraintsListData::getDataType() const {
  return CmdData::Type::BILL_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr BillConstraintsListData::clone() const {
  return std::make_shared<BillConstraintsListData>(*this);
}

void BillConstraintsListData::setBillConstraintsData(
    const std::vector<BillConstraintsData> &billConstraintsData) {
  m_billConstraintsData = billConstraintsData;
  m_billConstraintsDataIsSet = true;
}

const std::vector<BillConstraintsData> &
BillConstraintsListData::getBillConstraintsData() const {
  return m_billConstraintsData;
}

void BillConstraintsListData::cleanBillConstraintsData() {
  m_billConstraintsData.clear();
  m_billConstraintsDataIsSet = false;
}

bool BillConstraintsListData::getBillConstraintsDataIsSet() const {
  return m_billConstraintsDataIsSet;
}

CmdDataPtr
BillConstraintsListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<BillConstraintsData> dataOut;
  for (const auto &data : getBillConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          BillConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<BillConstraintsListDataSelectors>(
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
          const BillConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<BillConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(BillConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<BillConstraintsListData>(*this);
      }
    } else {
      return std::make_shared<BillConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<BillConstraintsListData>(dataOut);
  } else {
    return std::make_shared<BillConstraintsListData>();
  }
}

bool BillConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"billConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BillConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)), "billConstraintsData",
            &m_billConstraintsData)) {
      m_billConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_billConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BillConstraintsData>(
        "billConstraintsData", m_billConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram