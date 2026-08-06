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
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsListData.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueConstraintsListData::
    DeviceConfigurationKeyValueConstraintsListData()
    : CmdData(), m_deviceConfigurationKeyValueConstraintsDataIsSet(false),
      m_deviceConfigurationKeyValueConstraintsData(
          std::vector<DeviceConfigurationKeyValueConstraintsData>())

{}

DeviceConfigurationKeyValueConstraintsListData::
    DeviceConfigurationKeyValueConstraintsListData(
        const std::vector<DeviceConfigurationKeyValueConstraintsData>
            &c_deviceConfigurationKeyValueConstraintsData) {
  setDeviceConfigurationKeyValueConstraintsData(
      c_deviceConfigurationKeyValueConstraintsData);
}

bool DeviceConfigurationKeyValueConstraintsListData::operator==(
    const DeviceConfigurationKeyValueConstraintsListData &c_classObject) const {
  if (m_deviceConfigurationKeyValueConstraintsDataIsSet !=
          c_classObject.m_deviceConfigurationKeyValueConstraintsDataIsSet ||
      (m_deviceConfigurationKeyValueConstraintsDataIsSet &&
       (m_deviceConfigurationKeyValueConstraintsData !=
        c_classObject.m_deviceConfigurationKeyValueConstraintsData))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueConstraintsListData::operator!=(
    const DeviceConfigurationKeyValueConstraintsListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueConstraintsListData::isEmpty() const {
  return !m_deviceConfigurationKeyValueConstraintsDataIsSet;
}

CmdData::Type
DeviceConfigurationKeyValueConstraintsListData::getDataType() const {
  return CmdData::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE;
}

CmdDataPtr DeviceConfigurationKeyValueConstraintsListData::clone() const {
  return std::make_shared<DeviceConfigurationKeyValueConstraintsListData>(
      *this);
}

void DeviceConfigurationKeyValueConstraintsListData::
    setDeviceConfigurationKeyValueConstraintsData(
        const std::vector<DeviceConfigurationKeyValueConstraintsData>
            &deviceConfigurationKeyValueConstraintsData) {
  m_deviceConfigurationKeyValueConstraintsData =
      deviceConfigurationKeyValueConstraintsData;
  m_deviceConfigurationKeyValueConstraintsDataIsSet = true;
}

const std::vector<DeviceConfigurationKeyValueConstraintsData> &
DeviceConfigurationKeyValueConstraintsListData::
    getDeviceConfigurationKeyValueConstraintsData() const {
  return m_deviceConfigurationKeyValueConstraintsData;
}

void DeviceConfigurationKeyValueConstraintsListData::
    cleanDeviceConfigurationKeyValueConstraintsData() {
  m_deviceConfigurationKeyValueConstraintsData.clear();
  m_deviceConfigurationKeyValueConstraintsDataIsSet = false;
}

bool DeviceConfigurationKeyValueConstraintsListData::
    getDeviceConfigurationKeyValueConstraintsDataIsSet() const {
  return m_deviceConfigurationKeyValueConstraintsDataIsSet;
}

CmdDataPtr DeviceConfigurationKeyValueConstraintsListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<DeviceConfigurationKeyValueConstraintsData> dataOut;
  for (const auto &data : getDeviceConfigurationKeyValueConstraintsData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          DeviceConfigurationKeyValueConstraintsListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  DeviceConfigurationKeyValueConstraintsListDataSelectors>(
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
          const DeviceConfigurationKeyValueConstraintsDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  DeviceConfigurationKeyValueConstraintsDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(DeviceConfigurationKeyValueConstraintsData(data));
          }
        }
      } else {
        return std::make_shared<DeviceConfigurationKeyValueConstraintsListData>(
            *this);
      }
    } else {
      return std::make_shared<DeviceConfigurationKeyValueConstraintsListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<DeviceConfigurationKeyValueConstraintsListData>(
        dataOut);
  } else {
    return std::make_shared<DeviceConfigurationKeyValueConstraintsListData>();
  }
}

bool DeviceConfigurationKeyValueConstraintsListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"deviceConfigurationKeyValueConstraintsData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            DeviceConfigurationKeyValueConstraintsData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "deviceConfigurationKeyValueConstraintsData",
            &m_deviceConfigurationKeyValueConstraintsData)) {
      m_deviceConfigurationKeyValueConstraintsDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueConstraintsListData::toJson() const {
  std::string result = "[";
  if (m_deviceConfigurationKeyValueConstraintsDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        DeviceConfigurationKeyValueConstraintsData>(
        "deviceConfigurationKeyValueConstraintsData",
        m_deviceConfigurationKeyValueConstraintsData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram