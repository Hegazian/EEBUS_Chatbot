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
#include <keo_datagram/sensing/SensingListData.h>
#include <keo_datagram/sensing/SensingListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

SensingListData::SensingListData()
    : CmdData(), m_sensingDataIsSet(false),
      m_sensingData(std::vector<SensingData>())

{}

SensingListData::SensingListData(
    const std::vector<SensingData> &c_sensingData) {
  setSensingData(c_sensingData);
}

bool SensingListData::operator==(const SensingListData &c_classObject) const {
  if (m_sensingDataIsSet != c_classObject.m_sensingDataIsSet ||
      (m_sensingDataIsSet && (m_sensingData != c_classObject.m_sensingData))) {
    return false;
  }

  return true;
}

bool SensingListData::operator!=(const SensingListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool SensingListData::isEmpty() const { return !m_sensingDataIsSet; }

CmdData::Type SensingListData::getDataType() const {
  return CmdData::Type::SENSING_LIST_DATA_TYPE;
}

CmdDataPtr SensingListData::clone() const {
  return std::make_shared<SensingListData>(*this);
}

void SensingListData::setSensingData(
    const std::vector<SensingData> &sensingData) {
  m_sensingData = sensingData;
  m_sensingDataIsSet = true;
}

const std::vector<SensingData> &SensingListData::getSensingData() const {
  return m_sensingData;
}

void SensingListData::cleanSensingData() {
  m_sensingData.clear();
  m_sensingDataIsSet = false;
}

bool SensingListData::getSensingDataIsSet() const { return m_sensingDataIsSet; }

CmdDataPtr SensingListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<SensingData> dataOut;
  for (const auto &data : getSensingData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          SensingListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<SensingListDataSelectors>(
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
          const SensingDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<SensingDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(SensingData(data));
          }
        }
      } else {
        return std::make_shared<SensingListData>(*this);
      }
    } else {
      return std::make_shared<SensingListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<SensingListData>(dataOut);
  } else {
    return std::make_shared<SensingListData>();
  }
}

bool SensingListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"sensingData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() && KeoJsonTransformation::getList<SensingData>(
                                   static_cast<KeoJsonValue *>(&(*iter)),
                                   "sensingData", &m_sensingData)) {
      m_sensingDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string SensingListData::toJson() const {
  std::string result = "[";
  if (m_sensingDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<SensingData>("sensingData",
                                                            m_sensingData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram