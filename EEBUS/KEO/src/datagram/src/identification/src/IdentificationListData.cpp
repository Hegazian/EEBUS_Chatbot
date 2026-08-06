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
#include <keo_datagram/identification/IdentificationListData.h>
#include <keo_datagram/identification/IdentificationListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

IdentificationListData::IdentificationListData()
    : CmdData(), m_identificationDataIsSet(false),
      m_identificationData(std::vector<IdentificationData>())

{}

IdentificationListData::IdentificationListData(
    const std::vector<IdentificationData> &c_identificationData) {
  setIdentificationData(c_identificationData);
}

bool IdentificationListData::
operator==(const IdentificationListData &c_classObject) const {
  if (m_identificationDataIsSet != c_classObject.m_identificationDataIsSet ||
      (m_identificationDataIsSet &&
       (m_identificationData != c_classObject.m_identificationData))) {
    return false;
  }

  return true;
}

bool IdentificationListData::
operator!=(const IdentificationListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool IdentificationListData::isEmpty() const {
  return !m_identificationDataIsSet;
}

CmdData::Type IdentificationListData::getDataType() const {
  return CmdData::Type::IDENTIFICATION_LIST_DATA_TYPE;
}

CmdDataPtr IdentificationListData::clone() const {
  return std::make_shared<IdentificationListData>(*this);
}

void IdentificationListData::setIdentificationData(
    const std::vector<IdentificationData> &identificationData) {
  m_identificationData = identificationData;
  m_identificationDataIsSet = true;
}

const std::vector<IdentificationData> &
IdentificationListData::getIdentificationData() const {
  return m_identificationData;
}

void IdentificationListData::cleanIdentificationData() {
  m_identificationData.clear();
  m_identificationDataIsSet = false;
}

bool IdentificationListData::getIdentificationDataIsSet() const {
  return m_identificationDataIsSet;
}

CmdDataPtr
IdentificationListData::reduce(const std::vector<Filter> &filters) const {
  std::vector<IdentificationData> dataOut;
  for (const auto &data : getIdentificationData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          IdentificationListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<IdentificationListDataSelectors>(
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
          const IdentificationDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<IdentificationDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(IdentificationData(data));
          }
        }
      } else {
        return std::make_shared<IdentificationListData>(*this);
      }
    } else {
      return std::make_shared<IdentificationListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<IdentificationListData>(dataOut);
  } else {
    return std::make_shared<IdentificationListData>();
  }
}

bool IdentificationListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(json, {"identificationData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<IdentificationData>(
            static_cast<KeoJsonValue *>(&(*iter)), "identificationData",
            &m_identificationData)) {
      m_identificationDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string IdentificationListData::toJson() const {
  std::string result = "[";
  if (m_identificationDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<IdentificationData>(
        "identificationData", m_identificationData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram