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
#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionParameterDescriptionListData::
    ElectricalConnectionParameterDescriptionListData()
    : CmdData(), m_electricalConnectionParameterDescriptionDataIsSet(false),
      m_electricalConnectionParameterDescriptionData(
          std::vector<ElectricalConnectionParameterDescriptionData>())

{}

ElectricalConnectionParameterDescriptionListData::
    ElectricalConnectionParameterDescriptionListData(
        const std::vector<ElectricalConnectionParameterDescriptionData>
            &c_electricalConnectionParameterDescriptionData) {
  setElectricalConnectionParameterDescriptionData(
      c_electricalConnectionParameterDescriptionData);
}

bool ElectricalConnectionParameterDescriptionListData::operator==(
    const ElectricalConnectionParameterDescriptionListData &c_classObject)
    const {
  if (m_electricalConnectionParameterDescriptionDataIsSet !=
          c_classObject.m_electricalConnectionParameterDescriptionDataIsSet ||
      (m_electricalConnectionParameterDescriptionDataIsSet &&
       (m_electricalConnectionParameterDescriptionData !=
        c_classObject.m_electricalConnectionParameterDescriptionData))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionParameterDescriptionListData::operator!=(
    const ElectricalConnectionParameterDescriptionListData &c_classObject)
    const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionParameterDescriptionListData::isEmpty() const {
  return !m_electricalConnectionParameterDescriptionDataIsSet;
}

CmdData::Type
ElectricalConnectionParameterDescriptionListData::getDataType() const {
  return CmdData::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr ElectricalConnectionParameterDescriptionListData::clone() const {
  return std::make_shared<ElectricalConnectionParameterDescriptionListData>(
      *this);
}

void ElectricalConnectionParameterDescriptionListData::
    setElectricalConnectionParameterDescriptionData(
        const std::vector<ElectricalConnectionParameterDescriptionData>
            &electricalConnectionParameterDescriptionData) {
  m_electricalConnectionParameterDescriptionData =
      electricalConnectionParameterDescriptionData;
  m_electricalConnectionParameterDescriptionDataIsSet = true;
}

const std::vector<ElectricalConnectionParameterDescriptionData> &
ElectricalConnectionParameterDescriptionListData::
    getElectricalConnectionParameterDescriptionData() const {
  return m_electricalConnectionParameterDescriptionData;
}

void ElectricalConnectionParameterDescriptionListData::
    cleanElectricalConnectionParameterDescriptionData() {
  m_electricalConnectionParameterDescriptionData.clear();
  m_electricalConnectionParameterDescriptionDataIsSet = false;
}

bool ElectricalConnectionParameterDescriptionListData::
    getElectricalConnectionParameterDescriptionDataIsSet() const {
  return m_electricalConnectionParameterDescriptionDataIsSet;
}

CmdDataPtr ElectricalConnectionParameterDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<ElectricalConnectionParameterDescriptionData> dataOut;
  for (const auto &data : getElectricalConnectionParameterDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ElectricalConnectionParameterDescriptionListDataSelectorsPtr
              selectors = std::dynamic_pointer_cast<
                  ElectricalConnectionParameterDescriptionListDataSelectors>(
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
          const ElectricalConnectionParameterDescriptionDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  ElectricalConnectionParameterDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(
                ElectricalConnectionParameterDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<
            ElectricalConnectionParameterDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<ElectricalConnectionParameterDescriptionListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ElectricalConnectionParameterDescriptionListData>(
        dataOut);
  } else {
    return std::make_shared<ElectricalConnectionParameterDescriptionListData>();
  }
}

bool ElectricalConnectionParameterDescriptionListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionParameterDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            ElectricalConnectionParameterDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "electricalConnectionParameterDescriptionData",
            &m_electricalConnectionParameterDescriptionData)) {
      m_electricalConnectionParameterDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionParameterDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionParameterDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        ElectricalConnectionParameterDescriptionData>(
        "electricalConnectionParameterDescriptionData",
        m_electricalConnectionParameterDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram