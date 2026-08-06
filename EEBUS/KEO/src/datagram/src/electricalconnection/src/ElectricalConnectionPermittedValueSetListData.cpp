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
#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionPermittedValueSetListData::
    ElectricalConnectionPermittedValueSetListData()
    : CmdData(), m_electricalConnectionPermittedValueSetDataIsSet(false),
      m_electricalConnectionPermittedValueSetData(
          std::vector<ElectricalConnectionPermittedValueSetData>())

{}

ElectricalConnectionPermittedValueSetListData::
    ElectricalConnectionPermittedValueSetListData(
        const std::vector<ElectricalConnectionPermittedValueSetData>
            &c_electricalConnectionPermittedValueSetData) {
  setElectricalConnectionPermittedValueSetData(
      c_electricalConnectionPermittedValueSetData);
}

bool ElectricalConnectionPermittedValueSetListData::operator==(
    const ElectricalConnectionPermittedValueSetListData &c_classObject) const {
  if (m_electricalConnectionPermittedValueSetDataIsSet !=
          c_classObject.m_electricalConnectionPermittedValueSetDataIsSet ||
      (m_electricalConnectionPermittedValueSetDataIsSet &&
       (m_electricalConnectionPermittedValueSetData !=
        c_classObject.m_electricalConnectionPermittedValueSetData))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionPermittedValueSetListData::operator!=(
    const ElectricalConnectionPermittedValueSetListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionPermittedValueSetListData::isEmpty() const {
  return !m_electricalConnectionPermittedValueSetDataIsSet;
}

CmdData::Type
ElectricalConnectionPermittedValueSetListData::getDataType() const {
  return CmdData::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE;
}

CmdDataPtr ElectricalConnectionPermittedValueSetListData::clone() const {
  return std::make_shared<ElectricalConnectionPermittedValueSetListData>(*this);
}

void ElectricalConnectionPermittedValueSetListData::
    setElectricalConnectionPermittedValueSetData(
        const std::vector<ElectricalConnectionPermittedValueSetData>
            &electricalConnectionPermittedValueSetData) {
  m_electricalConnectionPermittedValueSetData =
      electricalConnectionPermittedValueSetData;
  m_electricalConnectionPermittedValueSetDataIsSet = true;
}

const std::vector<ElectricalConnectionPermittedValueSetData> &
ElectricalConnectionPermittedValueSetListData::
    getElectricalConnectionPermittedValueSetData() const {
  return m_electricalConnectionPermittedValueSetData;
}

void ElectricalConnectionPermittedValueSetListData::
    cleanElectricalConnectionPermittedValueSetData() {
  m_electricalConnectionPermittedValueSetData.clear();
  m_electricalConnectionPermittedValueSetDataIsSet = false;
}

bool ElectricalConnectionPermittedValueSetListData::
    getElectricalConnectionPermittedValueSetDataIsSet() const {
  return m_electricalConnectionPermittedValueSetDataIsSet;
}

CmdDataPtr ElectricalConnectionPermittedValueSetListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<ElectricalConnectionPermittedValueSetData> dataOut;
  for (const auto &data : getElectricalConnectionPermittedValueSetData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ElectricalConnectionPermittedValueSetListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  ElectricalConnectionPermittedValueSetListDataSelectors>(
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
          const ElectricalConnectionPermittedValueSetDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  ElectricalConnectionPermittedValueSetDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(ElectricalConnectionPermittedValueSetData(data));
          }
        }
      } else {
        return std::make_shared<ElectricalConnectionPermittedValueSetListData>(
            *this);
      }
    } else {
      return std::make_shared<ElectricalConnectionPermittedValueSetListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ElectricalConnectionPermittedValueSetListData>(
        dataOut);
  } else {
    return std::make_shared<ElectricalConnectionPermittedValueSetListData>();
  }
}

bool ElectricalConnectionPermittedValueSetListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionPermittedValueSetData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            ElectricalConnectionPermittedValueSetData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "electricalConnectionPermittedValueSetData",
            &m_electricalConnectionPermittedValueSetData)) {
      m_electricalConnectionPermittedValueSetDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionPermittedValueSetListData::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionPermittedValueSetDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        ElectricalConnectionPermittedValueSetData>(
        "electricalConnectionPermittedValueSetData",
        m_electricalConnectionPermittedValueSetData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram