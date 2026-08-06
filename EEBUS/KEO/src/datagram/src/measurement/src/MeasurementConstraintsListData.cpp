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
#include <keo_datagram/measurement/MeasurementConstraintsListData.h>
#include <keo_datagram/measurement/MeasurementConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementConstraintsListData::MeasurementConstraintsListData()
    : CmdData(), m_measurementConstraintsDataIsSet(false),
      m_measurementConstraintsData(std::vector<MeasurementConstraintsData>())

{}

MeasurementConstraintsListData::MeasurementConstraintsListData(
    const std::vector<MeasurementConstraintsData>
        &c_measurementConstraintsData) {
  setMeasurementConstraintsData(c_measurementConstraintsData);
}

bool MeasurementConstraintsListData::
operator==(const MeasurementConstraintsListData &c_classObject) const {
  if (m_measurementConstraintsDataIsSet !=
          c_classObject.m_measurementConstraintsDataIsSet ||
      (m_measurementConstraintsDataIsSet &&
       (m_measurementConstraintsData !=
        c_classObject.m_measurementConstraintsData))) {
    return false;
  }

  return true;
}

bool MeasurementConstraintsListData::
operator!=(const MeasurementConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementConstraintsListData::isEmpty() const {
  return !m_measurementConstraintsDataIsSet;
}

CmdData::Type MeasurementConstraintsListData::getDataType() const {
  return CmdData::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr MeasurementConstraintsListData::clone() const {
  return std::make_shared<MeasurementConstraintsListData>(*this);
}

void MeasurementConstraintsListData::setMeasurementConstraintsData(
    const std::vector<MeasurementConstraintsData> &measurementConstraintsData) {
  m_measurementConstraintsData = measurementConstraintsData;
  m_measurementConstraintsDataIsSet = true;
}

const std::vector<MeasurementConstraintsData> &
MeasurementConstraintsListData::getMeasurementConstraintsData() const {
  return m_measurementConstraintsData;
}

void MeasurementConstraintsListData::cleanMeasurementConstraintsData() {
  m_measurementConstraintsData.clear();
  m_measurementConstraintsDataIsSet = false;
}

bool MeasurementConstraintsListData::getMeasurementConstraintsDataIsSet()
    const {
  return m_measurementConstraintsDataIsSet;
}

CmdDataPtr MeasurementConstraintsListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<MeasurementConstraintsData> dataOut;
  for (const auto &data : getMeasurementConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          MeasurementConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  MeasurementConstraintsListDataSelectors>(baseSelectorsClass);
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
          const MeasurementConstraintsDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<MeasurementConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(MeasurementConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<MeasurementConstraintsListData>(*this);
      }
    } else {
      return std::make_shared<MeasurementConstraintsListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<MeasurementConstraintsListData>(dataOut);
  } else {
    return std::make_shared<MeasurementConstraintsListData>();
  }
}

bool MeasurementConstraintsListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<MeasurementConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)), "measurementConstraintsData",
            &m_measurementConstraintsData)) {
      m_measurementConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_measurementConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<MeasurementConstraintsData>(
        "measurementConstraintsData", m_measurementConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram