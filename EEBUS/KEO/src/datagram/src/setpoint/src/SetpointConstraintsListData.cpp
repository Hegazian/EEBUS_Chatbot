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
#include <keo_datagram/setpoint/SetpointConstraintsListData.h>
#include <keo_datagram/setpoint/SetpointConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointConstraintsListData::SetpointConstraintsListData()
    : CmdData(), m_setpointConstraintsDataIsSet(false),
      m_setpointConstraintsData(std::vector<SetpointConstraintsData>())

{}

SetpointConstraintsListData::SetpointConstraintsListData(
    const std::vector<SetpointConstraintsData> &c_setpointConstraintsData) {
  setSetpointConstraintsData(c_setpointConstraintsData);
}

bool SetpointConstraintsListData::
operator==(const SetpointConstraintsListData &c_classObject) const {
  if (m_setpointConstraintsDataIsSet !=
          c_classObject.m_setpointConstraintsDataIsSet ||
      (m_setpointConstraintsDataIsSet &&
       (m_setpointConstraintsData !=
        c_classObject.m_setpointConstraintsData))) {
    return false;
  }

  return true;
}

bool SetpointConstraintsListData::
operator!=(const SetpointConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointConstraintsListData::isEmpty() const {
  return !m_setpointConstraintsDataIsSet;
}

CmdData::Type SetpointConstraintsListData::getDataType() const {
  return CmdData::Type::SETPOINT_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr SetpointConstraintsListData::clone() const {
  return std::make_shared<SetpointConstraintsListData>(*this);
}

void SetpointConstraintsListData::setSetpointConstraintsData(
    const std::vector<SetpointConstraintsData> &setpointConstraintsData) {
  m_setpointConstraintsData = setpointConstraintsData;
  m_setpointConstraintsDataIsSet = true;
}

const std::vector<SetpointConstraintsData> &
SetpointConstraintsListData::getSetpointConstraintsData() const {
  return m_setpointConstraintsData;
}

void SetpointConstraintsListData::cleanSetpointConstraintsData() {
  m_setpointConstraintsData.clear();
  m_setpointConstraintsDataIsSet = false;
}

bool SetpointConstraintsListData::getSetpointConstraintsDataIsSet() const {
  return m_setpointConstraintsDataIsSet;
}

CmdDataPtr
SetpointConstraintsListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<SetpointConstraintsData> dataOut;
  for (const auto &data : getSetpointConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SetpointConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<SetpointConstraintsListDataSelectors>(
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
          const SetpointConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<SetpointConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SetpointConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<SetpointConstraintsListData>(*this);
      }
    } else {
      return std::make_shared<SetpointConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SetpointConstraintsListData>(dataOut);
  } else {
    return std::make_shared<SetpointConstraintsListData>();
  }
}

bool SetpointConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"setpointConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SetpointConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)), "setpointConstraintsData",
            &m_setpointConstraintsData)) {
      m_setpointConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SetpointConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_setpointConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SetpointConstraintsData>(
        "setpointConstraintsData", m_setpointConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram