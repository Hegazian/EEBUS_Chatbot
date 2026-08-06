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
#include <keo_datagram/bill/BillDescriptionListData.h>
#include <keo_datagram/bill/BillDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BillDescriptionListData::BillDescriptionListData()
    : CmdData(), m_billDescriptionDataIsSet(false),
      m_billDescriptionData(std::vector<BillDescriptionData>())

{}

BillDescriptionListData::BillDescriptionListData(
    const std::vector<BillDescriptionData> &c_billDescriptionData) {
  setBillDescriptionData(c_billDescriptionData);
}

bool BillDescriptionListData::
operator==(const BillDescriptionListData &c_classObject) const {
  if (m_billDescriptionDataIsSet != c_classObject.m_billDescriptionDataIsSet ||
      (m_billDescriptionDataIsSet &&
       (m_billDescriptionData != c_classObject.m_billDescriptionData))) {
    return false;
  }

  return true;
}

bool BillDescriptionListData::
operator!=(const BillDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BillDescriptionListData::isEmpty() const {
  return !m_billDescriptionDataIsSet;
}

CmdData::Type BillDescriptionListData::getDataType() const {
  return CmdData::Type::BILL_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr BillDescriptionListData::clone() const {
  return std::make_shared<BillDescriptionListData>(*this);
}

void BillDescriptionListData::setBillDescriptionData(
    const std::vector<BillDescriptionData> &billDescriptionData) {
  m_billDescriptionData = billDescriptionData;
  m_billDescriptionDataIsSet = true;
}

const std::vector<BillDescriptionData> &
BillDescriptionListData::getBillDescriptionData() const {
  return m_billDescriptionData;
}

void BillDescriptionListData::cleanBillDescriptionData() {
  m_billDescriptionData.clear();
  m_billDescriptionDataIsSet = false;
}

bool BillDescriptionListData::getBillDescriptionDataIsSet() const {
  return m_billDescriptionDataIsSet;
}

CmdDataPtr
BillDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<BillDescriptionData> dataOut;
  for (const auto &data : getBillDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          BillDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<BillDescriptionListDataSelectors>(
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
          const BillDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<BillDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(BillDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<BillDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<BillDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<BillDescriptionListData>(dataOut);
  } else {
    return std::make_shared<BillDescriptionListData>();
  }
}

bool BillDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"billDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BillDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "billDescriptionData",
            &m_billDescriptionData)) {
      m_billDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BillDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_billDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BillDescriptionData>(
        "billDescriptionData", m_billDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram