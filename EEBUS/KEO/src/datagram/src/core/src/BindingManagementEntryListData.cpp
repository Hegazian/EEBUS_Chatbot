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
#include <keo_datagram/core/BindingManagementEntryListData.h>
#include <keo_datagram/core/BindingManagementEntryListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

BindingManagementEntryListData::BindingManagementEntryListData()
    : CmdData(), m_bindingManagementEntryDataIsSet(false),
      m_bindingManagementEntryData(std::vector<BindingManagementEntryData>())

{}

BindingManagementEntryListData::BindingManagementEntryListData(
    const std::vector<BindingManagementEntryData>
        &c_bindingManagementEntryData) {
  setBindingManagementEntryData(c_bindingManagementEntryData);
}

bool BindingManagementEntryListData::
operator==(const BindingManagementEntryListData &c_classObject) const {
  if (m_bindingManagementEntryDataIsSet !=
          c_classObject.m_bindingManagementEntryDataIsSet ||
      (m_bindingManagementEntryDataIsSet &&
       (m_bindingManagementEntryData !=
        c_classObject.m_bindingManagementEntryData))) {
    return false;
  }

  return true;
}

bool BindingManagementEntryListData::
operator!=(const BindingManagementEntryListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool BindingManagementEntryListData::isEmpty() const {
  return !m_bindingManagementEntryDataIsSet;
}

CmdData::Type BindingManagementEntryListData::getDataType() const {
  return CmdData::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE;
}

CmdDataPtr BindingManagementEntryListData::clone() const {
  return std::make_shared<BindingManagementEntryListData>(*this);
}

void BindingManagementEntryListData::setBindingManagementEntryData(
    const std::vector<BindingManagementEntryData> &bindingManagementEntryData) {
  m_bindingManagementEntryData = bindingManagementEntryData;
  m_bindingManagementEntryDataIsSet = true;
}

const std::vector<BindingManagementEntryData> &
BindingManagementEntryListData::getBindingManagementEntryData() const {
  return m_bindingManagementEntryData;
}

void BindingManagementEntryListData::cleanBindingManagementEntryData() {
  m_bindingManagementEntryData.clear();
  m_bindingManagementEntryDataIsSet = false;
}

bool BindingManagementEntryListData::getBindingManagementEntryDataIsSet()
    const {
  return m_bindingManagementEntryDataIsSet;
}

CmdDataPtr BindingManagementEntryListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<BindingManagementEntryData> dataOut;
  for (const auto &data : getBindingManagementEntryData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          BindingManagementEntryListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  BindingManagementEntryListDataSelectors>(baseSelectorsClass);
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
          const BindingManagementEntryDataElementsPtr elementsClass =
              std::dynamic_pointer_cast<BindingManagementEntryDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(BindingManagementEntryData(data));
          }
        }
      } else {
        return std::make_shared<BindingManagementEntryListData>(*this);
      }
    } else {
      return std::make_shared<BindingManagementEntryListData>(*this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<BindingManagementEntryListData>(dataOut);
  } else {
    return std::make_shared<BindingManagementEntryListData>();
  }
}

bool BindingManagementEntryListData::fromJson(KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"bindingManagementEntryData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<BindingManagementEntryData>(
            static_cast<KeoJsonValue *>(&(*iter)), "bindingManagementEntryData",
            &m_bindingManagementEntryData)) {
      m_bindingManagementEntryDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string BindingManagementEntryListData::toJson() const {
  std::string result = "[";
  if (m_bindingManagementEntryDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<BindingManagementEntryData>(
        "bindingManagementEntryData", m_bindingManagementEntryData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram