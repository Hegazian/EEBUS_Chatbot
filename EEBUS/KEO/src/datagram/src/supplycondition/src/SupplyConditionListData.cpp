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
#include <keo_datagram/supplycondition/SupplyConditionListData.h>
#include <keo_datagram/supplycondition/SupplyConditionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionListData::SupplyConditionListData()
    : CmdData(), m_supplyConditionDataIsSet(false),
      m_supplyConditionData(std::vector<SupplyConditionData>())

{}

SupplyConditionListData::SupplyConditionListData(
    const std::vector<SupplyConditionData> &c_supplyConditionData) {
  setSupplyConditionData(c_supplyConditionData);
}

bool SupplyConditionListData::
operator==(const SupplyConditionListData &c_classObject) const {
  if (m_supplyConditionDataIsSet != c_classObject.m_supplyConditionDataIsSet ||
      (m_supplyConditionDataIsSet &&
       (m_supplyConditionData != c_classObject.m_supplyConditionData))) {
    return false;
  }

  return true;
}

bool SupplyConditionListData::
operator!=(const SupplyConditionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionListData::isEmpty() const {
  return !m_supplyConditionDataIsSet;
}

CmdData::Type SupplyConditionListData::getDataType() const {
  return CmdData::Type::SUPPLY_CONDITION_LIST_DATA_TYPE;
}

CmdDataPtr SupplyConditionListData::clone() const {
  return std::make_shared<SupplyConditionListData>(*this);
}

void SupplyConditionListData::setSupplyConditionData(
    const std::vector<SupplyConditionData> &supplyConditionData) {
  m_supplyConditionData = supplyConditionData;
  m_supplyConditionDataIsSet = true;
}

const std::vector<SupplyConditionData> &
SupplyConditionListData::getSupplyConditionData() const {
  return m_supplyConditionData;
}

void SupplyConditionListData::cleanSupplyConditionData() {
  m_supplyConditionData.clear();
  m_supplyConditionDataIsSet = false;
}

bool SupplyConditionListData::getSupplyConditionDataIsSet() const {
  return m_supplyConditionDataIsSet;
}

CmdDataPtr
SupplyConditionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<SupplyConditionData> dataOut;
  for (const auto &data : getSupplyConditionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SupplyConditionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<SupplyConditionListDataSelectors>(
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
          const SupplyConditionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<SupplyConditionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SupplyConditionData(data));
          }
        }
      } else {
        return std::make_shared<SupplyConditionListData>(*this);
      }
    } else {
      return std::make_shared<SupplyConditionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SupplyConditionListData>(dataOut);
  } else {
    return std::make_shared<SupplyConditionListData>();
  }
}

bool SupplyConditionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"supplyConditionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SupplyConditionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "supplyConditionData",
            &m_supplyConditionData)) {
      m_supplyConditionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionListData::toJson() const {
  std::string result = "[";
  if (m_supplyConditionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SupplyConditionData>(
        "supplyConditionData", m_supplyConditionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram