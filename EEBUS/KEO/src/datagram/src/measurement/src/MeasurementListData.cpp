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
#include <keo_datagram/measurement/MeasurementListData.h>
#include <keo_datagram/measurement/MeasurementListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementListData::MeasurementListData()
    : CmdData(), m_measurementDataIsSet(false),
      m_measurementData(std::vector<MeasurementData>())

{}

MeasurementListData::MeasurementListData(
    const std::vector<MeasurementData> &c_measurementData) {
  setMeasurementData(c_measurementData);
}

bool MeasurementListData::
operator==(const MeasurementListData &c_classObject) const {
  if (m_measurementDataIsSet != c_classObject.m_measurementDataIsSet ||
      (m_measurementDataIsSet &&
       (m_measurementData != c_classObject.m_measurementData))) {
    return false;
  }

  return true;
}

bool MeasurementListData::
operator!=(const MeasurementListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementListData::isEmpty() const { return !m_measurementDataIsSet; }

CmdData::Type MeasurementListData::getDataType() const {
  return CmdData::Type::MEASUREMENT_LIST_DATA_TYPE;
}

CmdDataPtr MeasurementListData::clone() const {
  return std::make_shared<MeasurementListData>(*this);
}

void MeasurementListData::setMeasurementData(
    const std::vector<MeasurementData> &measurementData) {
  m_measurementData = measurementData;
  m_measurementDataIsSet = true;
}

const std::vector<MeasurementData> &
MeasurementListData::getMeasurementData() const {
  return m_measurementData;
}

void MeasurementListData::cleanMeasurementData() {
  m_measurementData.clear();
  m_measurementDataIsSet = false;
}

bool MeasurementListData::getMeasurementDataIsSet() const {
  return m_measurementDataIsSet;
}

CmdDataPtr
MeasurementListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<MeasurementData> dataOut;
  for (const auto &data : getMeasurementData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          MeasurementListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<MeasurementListDataSelectors>(
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
          const MeasurementDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<MeasurementDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(MeasurementData(data));
          }
        }
      } else {
        return std::make_shared<MeasurementListData>(*this);
      }
    } else {
      return std::make_shared<MeasurementListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<MeasurementListData>(dataOut);
  } else {
    return std::make_shared<MeasurementListData>();
  }
}

bool MeasurementListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"measurementData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<MeasurementData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "measurementData", &m_measurementData)) {
      m_measurementDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementListData::toJson() const {
  std::string result = "[";
  if (m_measurementDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<MeasurementData>(
        "measurementData", m_measurementData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram