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
#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsListData.h>
#include <keo_datagram/loadcontrol/LoadControlLimitConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitConstraintsListData::LoadControlLimitConstraintsListData()
    : CmdData(), m_loadControlLimitConstraintsDataIsSet(false),
      m_loadControlLimitConstraintsData(
          std::vector<LoadControlLimitConstraintsData>())

{}

LoadControlLimitConstraintsListData::LoadControlLimitConstraintsListData(
    const std::vector<LoadControlLimitConstraintsData>
        &c_loadControlLimitConstraintsData) {
  setLoadControlLimitConstraintsData(c_loadControlLimitConstraintsData);
}

bool LoadControlLimitConstraintsListData::
operator==(const LoadControlLimitConstraintsListData &c_classObject) const {
  if (m_loadControlLimitConstraintsDataIsSet !=
          c_classObject.m_loadControlLimitConstraintsDataIsSet ||
      (m_loadControlLimitConstraintsDataIsSet &&
       (m_loadControlLimitConstraintsData !=
        c_classObject.m_loadControlLimitConstraintsData))) {
    return false;
  }

  return true;
}

bool LoadControlLimitConstraintsListData::
operator!=(const LoadControlLimitConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitConstraintsListData::isEmpty() const {
  return !m_loadControlLimitConstraintsDataIsSet;
}

CmdData::Type LoadControlLimitConstraintsListData::getDataType() const {
  return CmdData::Type::LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr LoadControlLimitConstraintsListData::clone() const {
  return std::make_shared<LoadControlLimitConstraintsListData>(*this);
}

void LoadControlLimitConstraintsListData::setLoadControlLimitConstraintsData(
    const std::vector<LoadControlLimitConstraintsData>
        &loadControlLimitConstraintsData) {
  m_loadControlLimitConstraintsData = loadControlLimitConstraintsData;
  m_loadControlLimitConstraintsDataIsSet = true;
}

const std::vector<LoadControlLimitConstraintsData> &
LoadControlLimitConstraintsListData::getLoadControlLimitConstraintsData()
    const {
  return m_loadControlLimitConstraintsData;
}

void LoadControlLimitConstraintsListData::
    cleanLoadControlLimitConstraintsData() {
  m_loadControlLimitConstraintsData.clear();
  m_loadControlLimitConstraintsDataIsSet = false;
}

bool LoadControlLimitConstraintsListData::
    getLoadControlLimitConstraintsDataIsSet() const {
  return m_loadControlLimitConstraintsDataIsSet;
}

CmdDataPtr LoadControlLimitConstraintsListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<LoadControlLimitConstraintsData> dataOut;
  for (const auto &data : getLoadControlLimitConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          LoadControlLimitConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  LoadControlLimitConstraintsListDataSelectors>(
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
          const LoadControlLimitConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  LoadControlLimitConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(LoadControlLimitConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<LoadControlLimitConstraintsListData>(*this);
      }
    } else {
      return std::make_shared<LoadControlLimitConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<LoadControlLimitConstraintsListData>(dataOut);
  } else {
    return std::make_shared<LoadControlLimitConstraintsListData>();
  }
}

bool LoadControlLimitConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"loadControlLimitConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<LoadControlLimitConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "loadControlLimitConstraintsData",
            &m_loadControlLimitConstraintsData)) {
      m_loadControlLimitConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlLimitConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_loadControlLimitConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<LoadControlLimitConstraintsData>(
        "loadControlLimitConstraintsData", m_loadControlLimitConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram