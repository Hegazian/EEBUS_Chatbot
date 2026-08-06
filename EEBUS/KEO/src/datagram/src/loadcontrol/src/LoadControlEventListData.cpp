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
#include <keo_datagram/loadcontrol/LoadControlEventListData.h>
#include <keo_datagram/loadcontrol/LoadControlEventListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlEventListData::LoadControlEventListData()
    : CmdData(), m_loadControlEventDataIsSet(false),
      m_loadControlEventData(std::vector<LoadControlEventData>())

{}

LoadControlEventListData::LoadControlEventListData(
    const std::vector<LoadControlEventData> &c_loadControlEventData) {
  setLoadControlEventData(c_loadControlEventData);
}

bool LoadControlEventListData::
operator==(const LoadControlEventListData &c_classObject) const {
  if (m_loadControlEventDataIsSet !=
          c_classObject.m_loadControlEventDataIsSet ||
      (m_loadControlEventDataIsSet &&
       (m_loadControlEventData != c_classObject.m_loadControlEventData))) {
    return false;
  }

  return true;
}

bool LoadControlEventListData::
operator!=(const LoadControlEventListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlEventListData::isEmpty() const {
  return !m_loadControlEventDataIsSet;
}

CmdData::Type LoadControlEventListData::getDataType() const {
  return CmdData::Type::LOAD_CONTROL_EVENT_LIST_DATA_TYPE;
}

CmdDataPtr LoadControlEventListData::clone() const {
  return std::make_shared<LoadControlEventListData>(*this);
}

void LoadControlEventListData::setLoadControlEventData(
    const std::vector<LoadControlEventData> &loadControlEventData) {
  m_loadControlEventData = loadControlEventData;
  m_loadControlEventDataIsSet = true;
}

const std::vector<LoadControlEventData> &
LoadControlEventListData::getLoadControlEventData() const {
  return m_loadControlEventData;
}

void LoadControlEventListData::cleanLoadControlEventData() {
  m_loadControlEventData.clear();
  m_loadControlEventDataIsSet = false;
}

bool LoadControlEventListData::getLoadControlEventDataIsSet() const {
  return m_loadControlEventDataIsSet;
}

CmdDataPtr
LoadControlEventListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<LoadControlEventData> dataOut;
  for (const auto &data : getLoadControlEventData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          LoadControlEventListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<LoadControlEventListDataSelectors>(
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
          const LoadControlEventDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<LoadControlEventDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(LoadControlEventData(data));
          }
        }
      } else {
        return std::make_shared<LoadControlEventListData>(*this);
      }
    } else {
      return std::make_shared<LoadControlEventListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<LoadControlEventListData>(dataOut);
  } else {
    return std::make_shared<LoadControlEventListData>();
  }
}

bool LoadControlEventListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"loadControlEventData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<LoadControlEventData>(
            static_cast<KeoJsonValue *>(&(*iter)), "loadControlEventData",
            &m_loadControlEventData)) {
      m_loadControlEventDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlEventListData::toJson() const {
  std::string result = "[";
  if (m_loadControlEventDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<LoadControlEventData>(
        "loadControlEventData", m_loadControlEventData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram