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
#include <keo_datagram/directcontrol/DirectControlActivityListData.h>
#include <keo_datagram/directcontrol/DirectControlActivityListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DirectControlActivityListData::DirectControlActivityListData()
    : CmdData(), m_directControlActivityDataIsSet(false),
      m_directControlActivityData(std::vector<DirectControlActivityData>())

{}

DirectControlActivityListData::DirectControlActivityListData(
    const std::vector<DirectControlActivityData> &c_directControlActivityData) {
  setDirectControlActivityData(c_directControlActivityData);
}

bool DirectControlActivityListData::
operator==(const DirectControlActivityListData &c_classObject) const {
  if (m_directControlActivityDataIsSet !=
          c_classObject.m_directControlActivityDataIsSet ||
      (m_directControlActivityDataIsSet &&
       (m_directControlActivityData !=
        c_classObject.m_directControlActivityData))) {
    return false;
  }

  return true;
}

bool DirectControlActivityListData::
operator!=(const DirectControlActivityListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DirectControlActivityListData::isEmpty() const {
  return !m_directControlActivityDataIsSet;
}

CmdData::Type DirectControlActivityListData::getDataType() const {
  return CmdData::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE;
}

CmdDataPtr DirectControlActivityListData::clone() const {
  return std::make_shared<DirectControlActivityListData>(*this);
}

void DirectControlActivityListData::setDirectControlActivityData(
    const std::vector<DirectControlActivityData> &directControlActivityData) {
  m_directControlActivityData = directControlActivityData;
  m_directControlActivityDataIsSet = true;
}

const std::vector<DirectControlActivityData> &
DirectControlActivityListData::getDirectControlActivityData() const {
  return m_directControlActivityData;
}

void DirectControlActivityListData::cleanDirectControlActivityData() {
  m_directControlActivityData.clear();
  m_directControlActivityDataIsSet = false;
}

bool DirectControlActivityListData::getDirectControlActivityDataIsSet() const {
  return m_directControlActivityDataIsSet;
}

CmdDataPtr DirectControlActivityListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<DirectControlActivityData> dataOut;
  for (const auto &data : getDirectControlActivityData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          DirectControlActivityListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<DirectControlActivityListDataSelectors>(
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
          const DirectControlActivityDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<DirectControlActivityDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(DirectControlActivityData(data));
          }
        }
      } else {
        return std::make_shared<DirectControlActivityListData>(*this);
      }
    } else {
      return std::make_shared<DirectControlActivityListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<DirectControlActivityListData>(dataOut);
  } else {
    return std::make_shared<DirectControlActivityListData>();
  }
}

bool DirectControlActivityListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"directControlActivityData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<DirectControlActivityData>(
            static_cast<KeoJsonValue *>(&(*iter)), "directControlActivityData",
            &m_directControlActivityData)) {
      m_directControlActivityDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DirectControlActivityListData::toJson() const {
  std::string result = "[";
  if (m_directControlActivityDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<DirectControlActivityData>(
        "directControlActivityData", m_directControlActivityData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram