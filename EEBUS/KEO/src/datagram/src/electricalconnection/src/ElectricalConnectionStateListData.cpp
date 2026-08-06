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
#include <keo_datagram/electricalconnection/ElectricalConnectionStateListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionStateListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionStateListData::ElectricalConnectionStateListData()
    : CmdData(), m_electricalConnectionStateDataIsSet(false),
      m_electricalConnectionStateData(
          std::vector<ElectricalConnectionStateData>())

{}

ElectricalConnectionStateListData::ElectricalConnectionStateListData(
    const std::vector<ElectricalConnectionStateData>
        &c_electricalConnectionStateData) {
  setElectricalConnectionStateData(c_electricalConnectionStateData);
}

bool ElectricalConnectionStateListData::
operator==(const ElectricalConnectionStateListData &c_classObject) const {
  if (m_electricalConnectionStateDataIsSet !=
          c_classObject.m_electricalConnectionStateDataIsSet ||
      (m_electricalConnectionStateDataIsSet &&
       (m_electricalConnectionStateData !=
        c_classObject.m_electricalConnectionStateData))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionStateListData::
operator!=(const ElectricalConnectionStateListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionStateListData::isEmpty() const {
  return !m_electricalConnectionStateDataIsSet;
}

CmdData::Type ElectricalConnectionStateListData::getDataType() const {
  return CmdData::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE;
}

CmdDataPtr ElectricalConnectionStateListData::clone() const {
  return std::make_shared<ElectricalConnectionStateListData>(*this);
}

void ElectricalConnectionStateListData::setElectricalConnectionStateData(
    const std::vector<ElectricalConnectionStateData>
        &electricalConnectionStateData) {
  m_electricalConnectionStateData = electricalConnectionStateData;
  m_electricalConnectionStateDataIsSet = true;
}

const std::vector<ElectricalConnectionStateData> &
ElectricalConnectionStateListData::getElectricalConnectionStateData() const {
  return m_electricalConnectionStateData;
}

void ElectricalConnectionStateListData::cleanElectricalConnectionStateData() {
  m_electricalConnectionStateData.clear();
  m_electricalConnectionStateDataIsSet = false;
}

bool ElectricalConnectionStateListData::getElectricalConnectionStateDataIsSet()
    const {
  return m_electricalConnectionStateDataIsSet;
}

CmdDataPtr ElectricalConnectionStateListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<ElectricalConnectionStateData> dataOut;
  for (const auto &data : getElectricalConnectionStateData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ElectricalConnectionStateListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  ElectricalConnectionStateListDataSelectors>(
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
          const ElectricalConnectionStateDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<ElectricalConnectionStateDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(ElectricalConnectionStateData(data));
          }
        }
      } else {
        return std::make_shared<ElectricalConnectionStateListData>(*this);
      }
    } else {
      return std::make_shared<ElectricalConnectionStateListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ElectricalConnectionStateListData>(dataOut);
  } else {
    return std::make_shared<ElectricalConnectionStateListData>();
  }
}

bool ElectricalConnectionStateListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionStateData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<ElectricalConnectionStateData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "electricalConnectionStateData",
            &m_electricalConnectionStateData)) {
      m_electricalConnectionStateDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionStateListData::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionStateDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<ElectricalConnectionStateData>(
        "electricalConnectionStateData", m_electricalConnectionStateData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram