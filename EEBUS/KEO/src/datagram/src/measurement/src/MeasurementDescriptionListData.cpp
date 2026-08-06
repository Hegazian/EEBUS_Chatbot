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
#include <keo_datagram/measurement/MeasurementDescriptionListData.h>
#include <keo_datagram/measurement/MeasurementDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

MeasurementDescriptionListData::MeasurementDescriptionListData()
    : CmdData(), m_measurementDescriptionDataIsSet(false),
      m_measurementDescriptionData(std::vector<MeasurementDescriptionData>())

{}

MeasurementDescriptionListData::MeasurementDescriptionListData(
    const std::vector<MeasurementDescriptionData>
        &c_measurementDescriptionData) {
  setMeasurementDescriptionData(c_measurementDescriptionData);
}

bool MeasurementDescriptionListData::
operator==(const MeasurementDescriptionListData &c_classObject) const {
  if (m_measurementDescriptionDataIsSet !=
          c_classObject.m_measurementDescriptionDataIsSet ||
      (m_measurementDescriptionDataIsSet &&
       (m_measurementDescriptionData !=
        c_classObject.m_measurementDescriptionData))) {
    return false;
  }

  return true;
}

bool MeasurementDescriptionListData::
operator!=(const MeasurementDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool MeasurementDescriptionListData::isEmpty() const {
  return !m_measurementDescriptionDataIsSet;
}

CmdData::Type MeasurementDescriptionListData::getDataType() const {
  return CmdData::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr MeasurementDescriptionListData::clone() const {
  return std::make_shared<MeasurementDescriptionListData>(*this);
}

void MeasurementDescriptionListData::setMeasurementDescriptionData(
    const std::vector<MeasurementDescriptionData> &measurementDescriptionData) {
  m_measurementDescriptionData = measurementDescriptionData;
  m_measurementDescriptionDataIsSet = true;
}

const std::vector<MeasurementDescriptionData> &
MeasurementDescriptionListData::getMeasurementDescriptionData() const {
  return m_measurementDescriptionData;
}

void MeasurementDescriptionListData::cleanMeasurementDescriptionData() {
  m_measurementDescriptionData.clear();
  m_measurementDescriptionDataIsSet = false;
}

bool MeasurementDescriptionListData::getMeasurementDescriptionDataIsSet()
    const {
  return m_measurementDescriptionDataIsSet;
}

CmdDataPtr MeasurementDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<MeasurementDescriptionData> dataOut;
  for (const auto &data : getMeasurementDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          MeasurementDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  MeasurementDescriptionListDataSelectors>(baseSelectorsClass);
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
          const MeasurementDescriptionDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<MeasurementDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(MeasurementDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<MeasurementDescriptionListData>(*this);
      }
    } else {
      return std::make_shared<MeasurementDescriptionListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<MeasurementDescriptionListData>(dataOut);
  } else {
    return std::make_shared<MeasurementDescriptionListData>();
  }
}

bool MeasurementDescriptionListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"measurementDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<MeasurementDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)), "measurementDescriptionData",
            &m_measurementDescriptionData)) {
      m_measurementDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string MeasurementDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_measurementDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<MeasurementDescriptionData>(
        "measurementDescriptionData", m_measurementDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram