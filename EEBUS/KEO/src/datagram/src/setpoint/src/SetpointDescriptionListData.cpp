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
#include <keo_datagram/setpoint/SetpointDescriptionListData.h>
#include <keo_datagram/setpoint/SetpointDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SetpointDescriptionListData::SetpointDescriptionListData()
    : CmdData(), m_setpointDescriptionDataIsSet(false),
      m_setpointDescriptionData(std::vector<SetpointDescriptionData>())

{}

SetpointDescriptionListData::SetpointDescriptionListData(
    const std::vector<SetpointDescriptionData> &c_setpointDescriptionData) {
  setSetpointDescriptionData(c_setpointDescriptionData);
}

bool SetpointDescriptionListData::
operator==(const SetpointDescriptionListData &c_classObject) const {
  if (m_setpointDescriptionDataIsSet !=
          c_classObject.m_setpointDescriptionDataIsSet ||
      (m_setpointDescriptionDataIsSet &&
       (m_setpointDescriptionData !=
        c_classObject.m_setpointDescriptionData))) {
    return false;
  }

  return true;
}

bool SetpointDescriptionListData::
operator!=(const SetpointDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SetpointDescriptionListData::isEmpty() const {
  return !m_setpointDescriptionDataIsSet;
}

CmdData::Type SetpointDescriptionListData::getDataType() const {
  return CmdData::Type::SETPOINT_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr SetpointDescriptionListData::clone() const {
  return std::make_shared<SetpointDescriptionListData>(*this);
}

void SetpointDescriptionListData::setSetpointDescriptionData(
    const std::vector<SetpointDescriptionData> &setpointDescriptionData) {
  m_setpointDescriptionData = setpointDescriptionData;
  m_setpointDescriptionDataIsSet = true;
}

const std::vector<SetpointDescriptionData> &
SetpointDescriptionListData::getSetpointDescriptionData() const {
  return m_setpointDescriptionData;
}

void SetpointDescriptionListData::cleanSetpointDescriptionData() {
  m_setpointDescriptionData.clear();
  m_setpointDescriptionDataIsSet = false;
}

bool SetpointDescriptionListData::getSetpointDescriptionDataIsSet() const {
  return m_setpointDescriptionDataIsSet;
}

CmdDataPtr
SetpointDescriptionListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<SetpointDescriptionData> dataOut;
  for (const auto &data : getSetpointDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SetpointDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<SetpointDescriptionListDataSelectors>(
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
          const SetpointDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<SetpointDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SetpointDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<SetpointDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<SetpointDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SetpointDescriptionListData>(dataOut);
  } else {
    return std::make_shared<SetpointDescriptionListData>();
  }
}

bool SetpointDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json,
                                                {"setpointDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<SetpointDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "setpointDescriptionData",
            &m_setpointDescriptionData)) {
      m_setpointDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SetpointDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_setpointDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SetpointDescriptionData>(
        "setpointDescriptionData", m_setpointDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram