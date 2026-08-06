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
#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionListData.h>
#include <keo_datagram/loadcontrol/LoadControlLimitDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

LoadControlLimitDescriptionListData::LoadControlLimitDescriptionListData()
    : CmdData(), m_loadControlLimitDescriptionDataIsSet(false),
      m_loadControlLimitDescriptionData(
          std::vector<LoadControlLimitDescriptionData>())

{}

LoadControlLimitDescriptionListData::LoadControlLimitDescriptionListData(
    const std::vector<LoadControlLimitDescriptionData>
        &c_loadControlLimitDescriptionData) {
  setLoadControlLimitDescriptionData(c_loadControlLimitDescriptionData);
}

bool LoadControlLimitDescriptionListData::
operator==(const LoadControlLimitDescriptionListData &c_classObject) const {
  if (m_loadControlLimitDescriptionDataIsSet !=
          c_classObject.m_loadControlLimitDescriptionDataIsSet ||
      (m_loadControlLimitDescriptionDataIsSet &&
       (m_loadControlLimitDescriptionData !=
        c_classObject.m_loadControlLimitDescriptionData))) {
    return false;
  }

  return true;
}

bool LoadControlLimitDescriptionListData::
operator!=(const LoadControlLimitDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool LoadControlLimitDescriptionListData::isEmpty() const {
  return !m_loadControlLimitDescriptionDataIsSet;
}

CmdData::Type LoadControlLimitDescriptionListData::getDataType() const {
  return CmdData::Type::LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr LoadControlLimitDescriptionListData::clone() const {
  return std::make_shared<LoadControlLimitDescriptionListData>(*this);
}

void LoadControlLimitDescriptionListData::setLoadControlLimitDescriptionData(
    const std::vector<LoadControlLimitDescriptionData>
        &loadControlLimitDescriptionData) {
  m_loadControlLimitDescriptionData = loadControlLimitDescriptionData;
  m_loadControlLimitDescriptionDataIsSet = true;
}

const std::vector<LoadControlLimitDescriptionData> &
LoadControlLimitDescriptionListData::getLoadControlLimitDescriptionData()
    const {
  return m_loadControlLimitDescriptionData;
}

void LoadControlLimitDescriptionListData::
    cleanLoadControlLimitDescriptionData() {
  m_loadControlLimitDescriptionData.clear();
  m_loadControlLimitDescriptionDataIsSet = false;
}

bool LoadControlLimitDescriptionListData::
    getLoadControlLimitDescriptionDataIsSet() const {
  return m_loadControlLimitDescriptionDataIsSet;
}

CmdDataPtr LoadControlLimitDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<LoadControlLimitDescriptionData> dataOut;
  for (const auto &data : getLoadControlLimitDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          LoadControlLimitDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  LoadControlLimitDescriptionListDataSelectors>(
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
          const LoadControlLimitDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  LoadControlLimitDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(LoadControlLimitDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<LoadControlLimitDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<LoadControlLimitDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<LoadControlLimitDescriptionListData>(dataOut);
  } else {
    return std::make_shared<LoadControlLimitDescriptionListData>();
  }
}

bool LoadControlLimitDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"loadControlLimitDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<LoadControlLimitDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "loadControlLimitDescriptionData",
            &m_loadControlLimitDescriptionData)) {
      m_loadControlLimitDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string LoadControlLimitDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_loadControlLimitDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<LoadControlLimitDescriptionData>(
        "loadControlLimitDescriptionData", m_loadControlLimitDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram