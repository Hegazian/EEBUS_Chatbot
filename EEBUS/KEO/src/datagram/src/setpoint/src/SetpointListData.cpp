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
#include <keo_datagram/setpoint/SetpointListData.h>
#include <keo_datagram/setpoint/SetpointListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointListData::SetpointListData()
    : CmdData(), m_setpointDataIsSet(false),
      m_setpointData(std::vector<SetpointData>())

{}

SetpointListData::SetpointListData(
    const std::vector<SetpointData> &c_setpointData) {
  setSetpointData(c_setpointData);
}

bool SetpointListData::operator==(const SetpointListData &c_classObject) const {
  if (m_setpointDataIsSet != c_classObject.m_setpointDataIsSet ||
      (m_setpointDataIsSet &&
       (m_setpointData != c_classObject.m_setpointData))) {
    return false;
  }

  return true;
}

bool SetpointListData::operator!=(const SetpointListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointListData::isEmpty() const { return !m_setpointDataIsSet; }

CmdData::Type SetpointListData::getDataType() const {
  return CmdData::Type::SETPOINT_LIST_DATA_TYPE;
}

CmdDataPtr SetpointListData::clone() const {
  return std::make_shared<SetpointListData>(*this);
}

void SetpointListData::setSetpointData(
    const std::vector<SetpointData> &setpointData) {
  m_setpointData = setpointData;
  m_setpointDataIsSet = true;
}

const std::vector<SetpointData> &SetpointListData::getSetpointData() const {
  return m_setpointData;
}

void SetpointListData::cleanSetpointData() {
  m_setpointData.clear();
  m_setpointDataIsSet = false;
}

bool SetpointListData::getSetpointDataIsSet() const {
  return m_setpointDataIsSet;
}

CmdDataPtr SetpointListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<SetpointData> dataOut;
  for (const auto &data : getSetpointData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SetpointListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<SetpointListDataSelectors>(
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
          const SetpointDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<SetpointDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SetpointData(data));
          }
        }
      } else {
        return std::make_shared<SetpointListData>(*this);
      }
    } else {
      return std::make_shared<SetpointListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SetpointListData>(dataOut);
  } else {
    return std::make_shared<SetpointListData>();
  }
}

bool SetpointListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"setpointData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<SetpointData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "setpointData", &m_setpointData)) {
      m_setpointDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SetpointListData::toJson() const {
  std::string result = "[";
  if (m_setpointDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SetpointData>("setpointData",
                                                             m_setpointData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram