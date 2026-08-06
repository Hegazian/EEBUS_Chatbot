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
#include <keo_datagram/hvac/HvacSystemFunctionListData.h>
#include <keo_datagram/hvac/HvacSystemFunctionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

HvacSystemFunctionListData::HvacSystemFunctionListData()
    : CmdData(), m_hvacSystemFunctionDataIsSet(false),
      m_hvacSystemFunctionData(std::vector<HvacSystemFunctionData>())

{}

HvacSystemFunctionListData::HvacSystemFunctionListData(
    const std::vector<HvacSystemFunctionData> &c_hvacSystemFunctionData) {
  setHvacSystemFunctionData(c_hvacSystemFunctionData);
}

bool HvacSystemFunctionListData::
operator==(const HvacSystemFunctionListData &c_classObject) const {
  if (m_hvacSystemFunctionDataIsSet !=
          c_classObject.m_hvacSystemFunctionDataIsSet ||
      (m_hvacSystemFunctionDataIsSet &&
       (m_hvacSystemFunctionData != c_classObject.m_hvacSystemFunctionData))) {
    return false;
  }

  return true;
}

bool HvacSystemFunctionListData::
operator!=(const HvacSystemFunctionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool HvacSystemFunctionListData::isEmpty() const {
  return !m_hvacSystemFunctionDataIsSet;
}

CmdData::Type HvacSystemFunctionListData::getDataType() const {
  return CmdData::Type::HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE;
}

CmdDataPtr HvacSystemFunctionListData::clone() const {
  return std::make_shared<HvacSystemFunctionListData>(*this);
}

void HvacSystemFunctionListData::setHvacSystemFunctionData(
    const std::vector<HvacSystemFunctionData> &hvacSystemFunctionData) {
  m_hvacSystemFunctionData = hvacSystemFunctionData;
  m_hvacSystemFunctionDataIsSet = true;
}

const std::vector<HvacSystemFunctionData> &
HvacSystemFunctionListData::getHvacSystemFunctionData() const {
  return m_hvacSystemFunctionData;
}

void HvacSystemFunctionListData::cleanHvacSystemFunctionData() {
  m_hvacSystemFunctionData.clear();
  m_hvacSystemFunctionDataIsSet = false;
}

bool HvacSystemFunctionListData::getHvacSystemFunctionDataIsSet() const {
  return m_hvacSystemFunctionDataIsSet;
}

CmdDataPtr
HvacSystemFunctionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<HvacSystemFunctionData> dataOut;
  for (const auto &data : getHvacSystemFunctionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          HvacSystemFunctionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<HvacSystemFunctionListDataSelectors>(
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
          const HvacSystemFunctionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<HvacSystemFunctionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(HvacSystemFunctionData(data));
          }
        }
      } else {
        return std::make_shared<HvacSystemFunctionListData>(*this);
      }
    } else {
      return std::make_shared<HvacSystemFunctionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<HvacSystemFunctionListData>(dataOut);
  } else {
    return std::make_shared<HvacSystemFunctionListData>();
  }
}

bool HvacSystemFunctionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"hvacSystemFunctionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<HvacSystemFunctionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "hvacSystemFunctionData",
            &m_hvacSystemFunctionData)) {
      m_hvacSystemFunctionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string HvacSystemFunctionListData::toJson() const {
  std::string result = "[";
  if (m_hvacSystemFunctionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<HvacSystemFunctionData>(
        "hvacSystemFunctionData", m_hvacSystemFunctionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram