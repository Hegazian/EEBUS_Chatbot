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
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationListData.h>
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SupplyConditionThresholdRelationListData::
    SupplyConditionThresholdRelationListData()
    : CmdData(), m_supplyConditionThresholdRelationDataIsSet(false),
      m_supplyConditionThresholdRelationData(
          std::vector<SupplyConditionThresholdRelationData>())

{}

SupplyConditionThresholdRelationListData::
    SupplyConditionThresholdRelationListData(
        const std::vector<SupplyConditionThresholdRelationData>
            &c_supplyConditionThresholdRelationData) {
  setSupplyConditionThresholdRelationData(
      c_supplyConditionThresholdRelationData);
}

bool SupplyConditionThresholdRelationListData::operator==(
    const SupplyConditionThresholdRelationListData &c_classObject) const {
  if (m_supplyConditionThresholdRelationDataIsSet !=
          c_classObject.m_supplyConditionThresholdRelationDataIsSet ||
      (m_supplyConditionThresholdRelationDataIsSet &&
       (m_supplyConditionThresholdRelationData !=
        c_classObject.m_supplyConditionThresholdRelationData))) {
    return false;
  }

  return true;
}

bool SupplyConditionThresholdRelationListData::operator!=(
    const SupplyConditionThresholdRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SupplyConditionThresholdRelationListData::isEmpty() const {
  return !m_supplyConditionThresholdRelationDataIsSet;
}

CmdData::Type SupplyConditionThresholdRelationListData::getDataType() const {
  return CmdData::Type::SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr SupplyConditionThresholdRelationListData::clone() const {
  return std::make_shared<SupplyConditionThresholdRelationListData>(*this);
}

void SupplyConditionThresholdRelationListData::
    setSupplyConditionThresholdRelationData(
        const std::vector<SupplyConditionThresholdRelationData>
            &supplyConditionThresholdRelationData) {
  m_supplyConditionThresholdRelationData = supplyConditionThresholdRelationData;
  m_supplyConditionThresholdRelationDataIsSet = true;
}

const std::vector<SupplyConditionThresholdRelationData> &
SupplyConditionThresholdRelationListData::
    getSupplyConditionThresholdRelationData() const {
  return m_supplyConditionThresholdRelationData;
}

void SupplyConditionThresholdRelationListData::
    cleanSupplyConditionThresholdRelationData() {
  m_supplyConditionThresholdRelationData.clear();
  m_supplyConditionThresholdRelationDataIsSet = false;
}

bool SupplyConditionThresholdRelationListData::
    getSupplyConditionThresholdRelationDataIsSet() const {
  return m_supplyConditionThresholdRelationDataIsSet;
}

CmdDataPtr SupplyConditionThresholdRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<SupplyConditionThresholdRelationData> dataOut;
  for (const auto &data : getSupplyConditionThresholdRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SupplyConditionThresholdRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  SupplyConditionThresholdRelationListDataSelectors>(
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
          const SupplyConditionThresholdRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  SupplyConditionThresholdRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SupplyConditionThresholdRelationData(data));
          }
        }
      } else {
        return std::make_shared<SupplyConditionThresholdRelationListData>(
            *this);
      }
    } else {
      return std::make_shared<SupplyConditionThresholdRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SupplyConditionThresholdRelationListData>(dataOut);
  } else {
    return std::make_shared<SupplyConditionThresholdRelationListData>();
  }
}

bool SupplyConditionThresholdRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"supplyConditionThresholdRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SupplyConditionThresholdRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "supplyConditionThresholdRelationData",
            &m_supplyConditionThresholdRelationData)) {
      m_supplyConditionThresholdRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SupplyConditionThresholdRelationListData::toJson() const {
  std::string result = "[";
  if (m_supplyConditionThresholdRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<SupplyConditionThresholdRelationData>(
            "supplyConditionThresholdRelationData",
            m_supplyConditionThresholdRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram