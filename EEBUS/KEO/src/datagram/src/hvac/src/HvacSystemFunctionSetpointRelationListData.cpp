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
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionSetpointRelationListData::
    HvacSystemFunctionSetpointRelationListData()
    : CmdData(), m_hvacSystemFunctionSetpointRelationDataIsSet(false),
      m_hvacSystemFunctionSetpointRelationData(
          std::vector<HvacSystemFunctionSetpointRelationData>())

{}

HvacSystemFunctionSetpointRelationListData::
    HvacSystemFunctionSetpointRelationListData(
        const std::vector<HvacSystemFunctionSetpointRelationData>
            &c_hvacSystemFunctionSetpointRelationData) {
  setHvacSystemFunctionSetpointRelationData(
      c_hvacSystemFunctionSetpointRelationData);
}

bool HvacSystemFunctionSetpointRelationListData::operator==(
    const HvacSystemFunctionSetpointRelationListData &c_classObject) const {
  if (m_hvacSystemFunctionSetpointRelationDataIsSet !=
          c_classObject.m_hvacSystemFunctionSetpointRelationDataIsSet ||
      (m_hvacSystemFunctionSetpointRelationDataIsSet &&
       (m_hvacSystemFunctionSetpointRelationData !=
        c_classObject.m_hvacSystemFunctionSetpointRelationData))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionSetpointRelationListData::operator!=(
    const HvacSystemFunctionSetpointRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionSetpointRelationListData::isEmpty() const {
  return !m_hvacSystemFunctionSetpointRelationDataIsSet;
}

CmdData::Type HvacSystemFunctionSetpointRelationListData::getDataType() const {
  return CmdData::Type::HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr HvacSystemFunctionSetpointRelationListData::clone() const {
  return std::make_shared<HvacSystemFunctionSetpointRelationListData>(*this);
}

void HvacSystemFunctionSetpointRelationListData::
    setHvacSystemFunctionSetpointRelationData(
        const std::vector<HvacSystemFunctionSetpointRelationData>
            &hvacSystemFunctionSetpointRelationData) {
  m_hvacSystemFunctionSetpointRelationData =
      hvacSystemFunctionSetpointRelationData;
  m_hvacSystemFunctionSetpointRelationDataIsSet = true;
}

const std::vector<HvacSystemFunctionSetpointRelationData> &
HvacSystemFunctionSetpointRelationListData::
    getHvacSystemFunctionSetpointRelationData() const {
  return m_hvacSystemFunctionSetpointRelationData;
}

void HvacSystemFunctionSetpointRelationListData::
    cleanHvacSystemFunctionSetpointRelationData() {
  m_hvacSystemFunctionSetpointRelationData.clear();
  m_hvacSystemFunctionSetpointRelationDataIsSet = false;
}

bool HvacSystemFunctionSetpointRelationListData::
    getHvacSystemFunctionSetpointRelationDataIsSet() const {
  return m_hvacSystemFunctionSetpointRelationDataIsSet;
}

CmdDataPtr HvacSystemFunctionSetpointRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<HvacSystemFunctionSetpointRelationData> dataOut;
  for (const auto &data : getHvacSystemFunctionSetpointRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacSystemFunctionSetpointRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  HvacSystemFunctionSetpointRelationListDataSelectors>(
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
          const HvacSystemFunctionSetpointRelationDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  HvacSystemFunctionSetpointRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(HvacSystemFunctionSetpointRelationData(data));
          }
        }
      } else {
        return std::make_shared<HvacSystemFunctionSetpointRelationListData>(
            *this);
      }
    } else {
      return std::make_shared<HvacSystemFunctionSetpointRelationListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacSystemFunctionSetpointRelationListData>(
        dataOut);
  } else {
    return std::make_shared<HvacSystemFunctionSetpointRelationListData>();
  }
}

bool HvacSystemFunctionSetpointRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"hvacSystemFunctionSetpointRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<HvacSystemFunctionSetpointRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "hvacSystemFunctionSetpointRelationData",
            &m_hvacSystemFunctionSetpointRelationData)) {
      m_hvacSystemFunctionSetpointRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionSetpointRelationListData::toJson() const {
  std::string result = "[";
  if (m_hvacSystemFunctionSetpointRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        HvacSystemFunctionSetpointRelationData>(
        "hvacSystemFunctionSetpointRelationData",
        m_hvacSystemFunctionSetpointRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram