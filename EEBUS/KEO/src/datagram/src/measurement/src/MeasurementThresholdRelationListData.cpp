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
#include <keo_datagram/measurement/MeasurementThresholdRelationListData.h>
#include <keo_datagram/measurement/MeasurementThresholdRelationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementThresholdRelationListData::MeasurementThresholdRelationListData()
    : CmdData(), m_measurementThresholdRelationDataIsSet(false),
      m_measurementThresholdRelationData(
          std::vector<MeasurementThresholdRelationData>())

{}

MeasurementThresholdRelationListData::MeasurementThresholdRelationListData(
    const std::vector<MeasurementThresholdRelationData>
        &c_measurementThresholdRelationData) {
  setMeasurementThresholdRelationData(c_measurementThresholdRelationData);
}

bool MeasurementThresholdRelationListData::
operator==(const MeasurementThresholdRelationListData &c_classObject) const {
  if (m_measurementThresholdRelationDataIsSet !=
          c_classObject.m_measurementThresholdRelationDataIsSet ||
      (m_measurementThresholdRelationDataIsSet &&
       (m_measurementThresholdRelationData !=
        c_classObject.m_measurementThresholdRelationData))) {
    return false;
  }

  return true;
}

bool MeasurementThresholdRelationListData::
operator!=(const MeasurementThresholdRelationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementThresholdRelationListData::isEmpty() const {
  return !m_measurementThresholdRelationDataIsSet;
}

CmdData::Type MeasurementThresholdRelationListData::getDataType() const {
  return CmdData::Type::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE;
}

CmdDataPtr MeasurementThresholdRelationListData::clone() const {
  return std::make_shared<MeasurementThresholdRelationListData>(*this);
}

void MeasurementThresholdRelationListData::setMeasurementThresholdRelationData(
    const std::vector<MeasurementThresholdRelationData>
        &measurementThresholdRelationData) {
  m_measurementThresholdRelationData = measurementThresholdRelationData;
  m_measurementThresholdRelationDataIsSet = true;
}

const std::vector<MeasurementThresholdRelationData> &
MeasurementThresholdRelationListData::getMeasurementThresholdRelationData()
    const {
  return m_measurementThresholdRelationData;
}

void MeasurementThresholdRelationListData::
    cleanMeasurementThresholdRelationData() {
  m_measurementThresholdRelationData.clear();
  m_measurementThresholdRelationDataIsSet = false;
}

bool MeasurementThresholdRelationListData::
    getMeasurementThresholdRelationDataIsSet() const {
  return m_measurementThresholdRelationDataIsSet;
}

CmdDataPtr MeasurementThresholdRelationListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<MeasurementThresholdRelationData> dataOut;
  for (const auto &data : getMeasurementThresholdRelationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          MeasurementThresholdRelationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  MeasurementThresholdRelationListDataSelectors>(
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
          const MeasurementThresholdRelationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<
                  MeasurementThresholdRelationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(MeasurementThresholdRelationData(data));
          }
        }
      } else {
        return std::make_shared<MeasurementThresholdRelationListData>(*this);
      }
    } else {
      return std::make_shared<MeasurementThresholdRelationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<MeasurementThresholdRelationListData>(dataOut);
  } else {
    return std::make_shared<MeasurementThresholdRelationListData>();
  }
}

bool MeasurementThresholdRelationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementThresholdRelationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<MeasurementThresholdRelationData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "measurementThresholdRelationData",
            &m_measurementThresholdRelationData)) {
      m_measurementThresholdRelationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementThresholdRelationListData::toJson() const {
  std::string result = "[";
  if (m_measurementThresholdRelationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result +=
        KeoJsonTransformation::writeList<MeasurementThresholdRelationData>(
            "measurementThresholdRelationData",
            m_measurementThresholdRelationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram