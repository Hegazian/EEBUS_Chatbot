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
#include <keo_datagram/loadcontrol/LoadControlStateListData.h>
#include <keo_datagram/loadcontrol/LoadControlStateListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlStateListData::LoadControlStateListData()
    : CmdData(), m_loadControlStateDataIsSet(false),
      m_loadControlStateData(std::vector<LoadControlStateData>())

{}

LoadControlStateListData::LoadControlStateListData(
    const std::vector<LoadControlStateData> &c_loadControlStateData) {
  setLoadControlStateData(c_loadControlStateData);
}

bool LoadControlStateListData::
operator==(const LoadControlStateListData &c_classObject) const {
  if (m_loadControlStateDataIsSet !=
          c_classObject.m_loadControlStateDataIsSet ||
      (m_loadControlStateDataIsSet &&
       (m_loadControlStateData != c_classObject.m_loadControlStateData))) {
    return false;
  }

  return true;
}

bool LoadControlStateListData::
operator!=(const LoadControlStateListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlStateListData::isEmpty() const {
  return !m_loadControlStateDataIsSet;
}

CmdData::Type LoadControlStateListData::getDataType() const {
  return CmdData::Type::LOAD_CONTROL_STATE_LIST_DATA_TYPE;
}

CmdDataPtr LoadControlStateListData::clone() const {
  return std::make_shared<LoadControlStateListData>(*this);
}

void LoadControlStateListData::setLoadControlStateData(
    const std::vector<LoadControlStateData> &loadControlStateData) {
  m_loadControlStateData = loadControlStateData;
  m_loadControlStateDataIsSet = true;
}

const std::vector<LoadControlStateData> &
LoadControlStateListData::getLoadControlStateData() const {
  return m_loadControlStateData;
}

void LoadControlStateListData::cleanLoadControlStateData() {
  m_loadControlStateData.clear();
  m_loadControlStateDataIsSet = false;
}

bool LoadControlStateListData::getLoadControlStateDataIsSet() const {
  return m_loadControlStateDataIsSet;
}

CmdDataPtr
LoadControlStateListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<LoadControlStateData> dataOut;
  for (const auto &data : getLoadControlStateData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          LoadControlStateListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<LoadControlStateListDataSelectors>(
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
          const LoadControlStateDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<LoadControlStateDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(LoadControlStateData(data));
          }
        }
      } else {
        return std::make_shared<LoadControlStateListData>(*this);
      }
    } else {
      return std::make_shared<LoadControlStateListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<LoadControlStateListData>(dataOut);
  } else {
    return std::make_shared<LoadControlStateListData>();
  }
}

bool LoadControlStateListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"loadControlStateData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<LoadControlStateData>(
            static_cast<KeoJsonValue *>(&(*iter)), "loadControlStateData",
            &m_loadControlStateData)) {
      m_loadControlStateDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlStateListData::toJson() const {
  std::string result = "[";
  if (m_loadControlStateDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<LoadControlStateData>(
        "loadControlStateData", m_loadControlStateData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram