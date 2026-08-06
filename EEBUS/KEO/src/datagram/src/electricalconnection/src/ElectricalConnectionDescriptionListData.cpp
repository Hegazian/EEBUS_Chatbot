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
#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

ElectricalConnectionDescriptionListData::
    ElectricalConnectionDescriptionListData()
    : CmdData(), m_electricalConnectionDescriptionDataIsSet(false),
      m_electricalConnectionDescriptionData(
          std::vector<ElectricalConnectionDescriptionData>())

{}

ElectricalConnectionDescriptionListData::
    ElectricalConnectionDescriptionListData(
        const std::vector<ElectricalConnectionDescriptionData>
            &c_electricalConnectionDescriptionData) {
  setElectricalConnectionDescriptionData(c_electricalConnectionDescriptionData);
}

bool ElectricalConnectionDescriptionListData::
operator==(const ElectricalConnectionDescriptionListData &c_classObject) const {
  if (m_electricalConnectionDescriptionDataIsSet !=
          c_classObject.m_electricalConnectionDescriptionDataIsSet ||
      (m_electricalConnectionDescriptionDataIsSet &&
       (m_electricalConnectionDescriptionData !=
        c_classObject.m_electricalConnectionDescriptionData))) {
    return false;
  }

  return true;
}

bool ElectricalConnectionDescriptionListData::
operator!=(const ElectricalConnectionDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool ElectricalConnectionDescriptionListData::isEmpty() const {
  return !m_electricalConnectionDescriptionDataIsSet;
}

CmdData::Type ElectricalConnectionDescriptionListData::getDataType() const {
  return CmdData::Type::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr ElectricalConnectionDescriptionListData::clone() const {
  return std::make_shared<ElectricalConnectionDescriptionListData>(*this);
}

void ElectricalConnectionDescriptionListData::
    setElectricalConnectionDescriptionData(
        const std::vector<ElectricalConnectionDescriptionData>
            &electricalConnectionDescriptionData) {
  m_electricalConnectionDescriptionData = electricalConnectionDescriptionData;
  m_electricalConnectionDescriptionDataIsSet = true;
}

const std::vector<ElectricalConnectionDescriptionData> &
ElectricalConnectionDescriptionListData::
    getElectricalConnectionDescriptionData() const {
  return m_electricalConnectionDescriptionData;
}

void ElectricalConnectionDescriptionListData::
    cleanElectricalConnectionDescriptionData() {
  m_electricalConnectionDescriptionData.clear();
  m_electricalConnectionDescriptionDataIsSet = false;
}

bool ElectricalConnectionDescriptionListData::
    getElectricalConnectionDescriptionDataIsSet() const {
  return m_electricalConnectionDescriptionDataIsSet;
}

CmdDataPtr ElectricalConnectionDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<ElectricalConnectionDescriptionData> dataOut;
  for (const auto &data : getElectricalConnectionDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          ElectricalConnectionDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  ElectricalConnectionDescriptionListDataSelectors>(
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
          const ElectricalConnectionDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  ElectricalConnectionDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(ElectricalConnectionDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<ElectricalConnectionDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<ElectricalConnectionDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<ElectricalConnectionDescriptionListData>(dataOut);
  } else {
    return std::make_shared<ElectricalConnectionDescriptionListData>();
  }
}

bool ElectricalConnectionDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"electricalConnectionDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<ElectricalConnectionDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "electricalConnectionDescriptionData",
            &m_electricalConnectionDescriptionData)) {
      m_electricalConnectionDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string ElectricalConnectionDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_electricalConnectionDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<ElectricalConnectionDescriptionData>(
            "electricalConnectionDescriptionData",
            m_electricalConnectionDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram