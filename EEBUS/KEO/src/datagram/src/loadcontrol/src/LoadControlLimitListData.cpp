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
#include <keo_datagram/loadcontrol/LoadControlLimitListData.h>
#include <keo_datagram/loadcontrol/LoadControlLimitListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitListData::LoadControlLimitListData()
    : CmdData(), m_loadControlLimitDataIsSet(false),
      m_loadControlLimitData(std::vector<LoadControlLimitData>())

{}

LoadControlLimitListData::LoadControlLimitListData(
    const std::vector<LoadControlLimitData> &c_loadControlLimitData) {
  setLoadControlLimitData(c_loadControlLimitData);
}

bool LoadControlLimitListData::
operator==(const LoadControlLimitListData &c_classObject) const {
  if (m_loadControlLimitDataIsSet !=
          c_classObject.m_loadControlLimitDataIsSet ||
      (m_loadControlLimitDataIsSet &&
       (m_loadControlLimitData != c_classObject.m_loadControlLimitData))) {
    return false;
  }

  return true;
}

bool LoadControlLimitListData::
operator!=(const LoadControlLimitListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitListData::isEmpty() const {
  return !m_loadControlLimitDataIsSet;
}

CmdData::Type LoadControlLimitListData::getDataType() const {
  return CmdData::Type::LOAD_CONTROL_LIMIT_LIST_DATA_TYPE;
}

CmdDataPtr LoadControlLimitListData::clone() const {
  return std::make_shared<LoadControlLimitListData>(*this);
}

void LoadControlLimitListData::setLoadControlLimitData(
    const std::vector<LoadControlLimitData> &loadControlLimitData) {
  m_loadControlLimitData = loadControlLimitData;
  m_loadControlLimitDataIsSet = true;
}

const std::vector<LoadControlLimitData> &
LoadControlLimitListData::getLoadControlLimitData() const {
  return m_loadControlLimitData;
}

void LoadControlLimitListData::cleanLoadControlLimitData() {
  m_loadControlLimitData.clear();
  m_loadControlLimitDataIsSet = false;
}

bool LoadControlLimitListData::getLoadControlLimitDataIsSet() const {
  return m_loadControlLimitDataIsSet;
}

CmdDataPtr
LoadControlLimitListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<LoadControlLimitData> dataOut;
  for (const auto &data : getLoadControlLimitData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          LoadControlLimitListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<LoadControlLimitListDataSelectors>(
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
          const LoadControlLimitDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<LoadControlLimitDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(LoadControlLimitData(data));
          }
        }
      } else {
        return std::make_shared<LoadControlLimitListData>(*this);
      }
    } else {
      return std::make_shared<LoadControlLimitListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<LoadControlLimitListData>(dataOut);
  } else {
    return std::make_shared<LoadControlLimitListData>();
  }
}

bool LoadControlLimitListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"loadControlLimitData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<LoadControlLimitData>(
            static_cast<KeoJsonValue *>(&(*iter)), "loadControlLimitData",
            &m_loadControlLimitData)) {
      m_loadControlLimitDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlLimitListData::toJson() const {
  std::string result = "[";
  if (m_loadControlLimitDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<LoadControlLimitData>(
        "loadControlLimitData", m_loadControlLimitData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram