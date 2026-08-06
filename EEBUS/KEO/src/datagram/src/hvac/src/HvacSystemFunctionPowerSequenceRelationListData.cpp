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
#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionPowerSequenceRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionPowerSequenceRelationListData::
    HvacSystemFunctionPowerSequenceRelationListData()
    : CmdData(), m_hvacSystemFunctionPowerSequenceRelationDataIsSet(false),
      m_hvacSystemFunctionPowerSequenceRelationData(
          std::vector<HvacSystemFunctionPowerSequenceRelationData>())

{}

HvacSystemFunctionPowerSequenceRelationListData::
    HvacSystemFunctionPowerSequenceRelationListData(
        const std::vector<HvacSystemFunctionPowerSequenceRelationData>
            &c_hvacSystemFunctionPowerSequenceRelationData) {
  setHvacSystemFunctionPowerSequenceRelationData(
      c_hvacSystemFunctionPowerSequenceRelationData);
}

bool HvacSystemFunctionPowerSequenceRelationListData::
operator==(const HvacSystemFunctionPowerSequenceRelationListData &c_classObject)
    const {
  if (m_hvacSystemFunctionPowerSequenceRelationDataIsSet !=
          c_classObject.m_hvacSystemFunctionPowerSequenceRelationDataIsSet ||
      (m_hvacSystemFunctionPowerSequenceRelationDataIsSet &&
       (m_hvacSystemFunctionPowerSequenceRelationData !=
        c_classObject.m_hvacSystemFunctionPowerSequenceRelationData))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionPowerSequenceRelationListData::
operator!=(const HvacSystemFunctionPowerSequenceRelationListData &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionPowerSequenceRelationListData::isEmpty() const {
  return !m_hvacSystemFunctionPowerSequenceRelationDataIsSet;
}

CmdData::Type
HvacSystemFunctionPowerSequenceRelationListData::getDataType() const {
  return CmdData::Type::
      HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr HvacSystemFunctionPowerSequenceRelationListData::clone() const {
  return std::make_shared<HvacSystemFunctionPowerSequenceRelationListData>(
      *this);
}

void HvacSystemFunctionPowerSequenceRelationListData::
    setHvacSystemFunctionPowerSequenceRelationData(
        const std::vector<HvacSystemFunctionPowerSequenceRelationData>
            &hvacSystemFunctionPowerSequenceRelationData) {
  m_hvacSystemFunctionPowerSequenceRelationData =
      hvacSystemFunctionPowerSequenceRelationData;
  m_hvacSystemFunctionPowerSequenceRelationDataIsSet = true;
}

const std::vector<HvacSystemFunctionPowerSequenceRelationData> &
HvacSystemFunctionPowerSequenceRelationListData::
    getHvacSystemFunctionPowerSequenceRelationData() const {
  return m_hvacSystemFunctionPowerSequenceRelationData;
}

void HvacSystemFunctionPowerSequenceRelationListData::
    cleanHvacSystemFunctionPowerSequenceRelationData() {
  m_hvacSystemFunctionPowerSequenceRelationData.clear();
  m_hvacSystemFunctionPowerSequenceRelationDataIsSet = false;
}

bool HvacSystemFunctionPowerSequenceRelationListData::
    getHvacSystemFunctionPowerSequenceRelationDataIsSet() const {
  return m_hvacSystemFunctionPowerSequenceRelationDataIsSet;
}

CmdDataPtr HvacSystemFunctionPowerSequenceRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<HvacSystemFunctionPowerSequenceRelationData> dataOut;
  for (const auto &data : getHvacSystemFunctionPowerSequenceRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacSystemFunctionPowerSequenceRelationListDataSelectorsPtr
              selectors = std::dynamic_pointer_cast<
                  HvacSystemFunctionPowerSequenceRelationListDataSelectors>(
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
          const HvacSystemFunctionPowerSequenceRelationDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  HvacSystemFunctionPowerSequenceRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(
                HvacSystemFunctionPowerSequenceRelationData(data));
          }
        }
      } else {
        return std::make_shared<
            HvacSystemFunctionPowerSequenceRelationListData>(*this);
      }
    } else {
      return std::make_shared<HvacSystemFunctionPowerSequenceRelationListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacSystemFunctionPowerSequenceRelationListData>(
        dataOut);
  } else {
    return std::make_shared<HvacSystemFunctionPowerSequenceRelationListData>();
  }
}

bool HvacSystemFunctionPowerSequenceRelationListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"hvacSystemFunctionPowerSequenceRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            HvacSystemFunctionPowerSequenceRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "hvacSystemFunctionPowerSequenceRelationData",
            &m_hvacSystemFunctionPowerSequenceRelationData)) {
      m_hvacSystemFunctionPowerSequenceRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionPowerSequenceRelationListData::toJson() const {
  std::string result = "[";
  if (m_hvacSystemFunctionPowerSequenceRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        HvacSystemFunctionPowerSequenceRelationData>(
        "hvacSystemFunctionPowerSequenceRelationData",
        m_hvacSystemFunctionPowerSequenceRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram