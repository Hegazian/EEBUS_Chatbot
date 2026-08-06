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
#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionOperationModeRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionOperationModeRelationListData::
    HvacSystemFunctionOperationModeRelationListData()
    : CmdData(), m_hvacSystemFunctionOperationModeRelationDataIsSet(false),
      m_hvacSystemFunctionOperationModeRelationData(
          std::vector<HvacSystemFunctionOperationModeRelationData>())

{}

HvacSystemFunctionOperationModeRelationListData::
    HvacSystemFunctionOperationModeRelationListData(
        const std::vector<HvacSystemFunctionOperationModeRelationData>
            &c_hvacSystemFunctionOperationModeRelationData) {
  setHvacSystemFunctionOperationModeRelationData(
      c_hvacSystemFunctionOperationModeRelationData);
}

bool HvacSystemFunctionOperationModeRelationListData::
operator==(const HvacSystemFunctionOperationModeRelationListData &c_classObject)
    const {
  if (m_hvacSystemFunctionOperationModeRelationDataIsSet !=
          c_classObject.m_hvacSystemFunctionOperationModeRelationDataIsSet ||
      (m_hvacSystemFunctionOperationModeRelationDataIsSet &&
       (m_hvacSystemFunctionOperationModeRelationData !=
        c_classObject.m_hvacSystemFunctionOperationModeRelationData))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionOperationModeRelationListData::
operator!=(const HvacSystemFunctionOperationModeRelationListData &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionOperationModeRelationListData::isEmpty() const {
  return !m_hvacSystemFunctionOperationModeRelationDataIsSet;
}

CmdData::Type
HvacSystemFunctionOperationModeRelationListData::getDataType() const {
  return CmdData::Type::
      HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr HvacSystemFunctionOperationModeRelationListData::clone() const {
  return std::make_shared<HvacSystemFunctionOperationModeRelationListData>(
      *this);
}

void HvacSystemFunctionOperationModeRelationListData::
    setHvacSystemFunctionOperationModeRelationData(
        const std::vector<HvacSystemFunctionOperationModeRelationData>
            &hvacSystemFunctionOperationModeRelationData) {
  m_hvacSystemFunctionOperationModeRelationData =
      hvacSystemFunctionOperationModeRelationData;
  m_hvacSystemFunctionOperationModeRelationDataIsSet = true;
}

const std::vector<HvacSystemFunctionOperationModeRelationData> &
HvacSystemFunctionOperationModeRelationListData::
    getHvacSystemFunctionOperationModeRelationData() const {
  return m_hvacSystemFunctionOperationModeRelationData;
}

void HvacSystemFunctionOperationModeRelationListData::
    cleanHvacSystemFunctionOperationModeRelationData() {
  m_hvacSystemFunctionOperationModeRelationData.clear();
  m_hvacSystemFunctionOperationModeRelationDataIsSet = false;
}

bool HvacSystemFunctionOperationModeRelationListData::
    getHvacSystemFunctionOperationModeRelationDataIsSet() const {
  return m_hvacSystemFunctionOperationModeRelationDataIsSet;
}

CmdDataPtr HvacSystemFunctionOperationModeRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<HvacSystemFunctionOperationModeRelationData> dataOut;
  for (const auto &data : getHvacSystemFunctionOperationModeRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacSystemFunctionOperationModeRelationListDataSelectorsPtr
              selectors = std::dynamic_pointer_cast<
                  HvacSystemFunctionOperationModeRelationListDataSelectors>(
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
          const HvacSystemFunctionOperationModeRelationDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  HvacSystemFunctionOperationModeRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(
                HvacSystemFunctionOperationModeRelationData(data));
          }
        }
      } else {
        return std::make_shared<
            HvacSystemFunctionOperationModeRelationListData>(*this);
      }
    } else {
      return std::make_shared<HvacSystemFunctionOperationModeRelationListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacSystemFunctionOperationModeRelationListData>(
        dataOut);
  } else {
    return std::make_shared<HvacSystemFunctionOperationModeRelationListData>();
  }
}

bool HvacSystemFunctionOperationModeRelationListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"hvacSystemFunctionOperationModeRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            HvacSystemFunctionOperationModeRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "hvacSystemFunctionOperationModeRelationData",
            &m_hvacSystemFunctionOperationModeRelationData)) {
      m_hvacSystemFunctionOperationModeRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionOperationModeRelationListData::toJson() const {
  std::string result = "[";
  if (m_hvacSystemFunctionOperationModeRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        HvacSystemFunctionOperationModeRelationData>(
        "hvacSystemFunctionOperationModeRelationData",
        m_hvacSystemFunctionOperationModeRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram