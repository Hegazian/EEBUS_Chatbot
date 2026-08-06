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
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListData.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListDataSelectors.h>

#include "KeoJsonTransformation.h"
#include "KeoJsonValue.h"

namespace keo_datagram {

DeviceConfigurationKeyValueDescriptionListData::
    DeviceConfigurationKeyValueDescriptionListData()
    : CmdData(), m_deviceConfigurationKeyValueDescriptionDataIsSet(false),
      m_deviceConfigurationKeyValueDescriptionData(
          std::vector<DeviceConfigurationKeyValueDescriptionData>())

{}

DeviceConfigurationKeyValueDescriptionListData::
    DeviceConfigurationKeyValueDescriptionListData(
        const std::vector<DeviceConfigurationKeyValueDescriptionData>
            &c_deviceConfigurationKeyValueDescriptionData) {
  setDeviceConfigurationKeyValueDescriptionData(
      c_deviceConfigurationKeyValueDescriptionData);
}

bool DeviceConfigurationKeyValueDescriptionListData::operator==(
    const DeviceConfigurationKeyValueDescriptionListData &c_classObject) const {
  if (m_deviceConfigurationKeyValueDescriptionDataIsSet !=
          c_classObject.m_deviceConfigurationKeyValueDescriptionDataIsSet ||
      (m_deviceConfigurationKeyValueDescriptionDataIsSet &&
       (m_deviceConfigurationKeyValueDescriptionData !=
        c_classObject.m_deviceConfigurationKeyValueDescriptionData))) {
    return false;
  }

  return true;
}

bool DeviceConfigurationKeyValueDescriptionListData::operator!=(
    const DeviceConfigurationKeyValueDescriptionListData &c_classObject) const {
  return !(*this == c_classObject);
}

bool DeviceConfigurationKeyValueDescriptionListData::isEmpty() const {
  return !m_deviceConfigurationKeyValueDescriptionDataIsSet;
}

CmdData::Type
DeviceConfigurationKeyValueDescriptionListData::getDataType() const {
  return CmdData::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE;
}

CmdDataPtr DeviceConfigurationKeyValueDescriptionListData::clone() const {
  return std::make_shared<DeviceConfigurationKeyValueDescriptionListData>(
      *this);
}

void DeviceConfigurationKeyValueDescriptionListData::
    setDeviceConfigurationKeyValueDescriptionData(
        const std::vector<DeviceConfigurationKeyValueDescriptionData>
            &deviceConfigurationKeyValueDescriptionData) {
  m_deviceConfigurationKeyValueDescriptionData =
      deviceConfigurationKeyValueDescriptionData;
  m_deviceConfigurationKeyValueDescriptionDataIsSet = true;
}

const std::vector<DeviceConfigurationKeyValueDescriptionData> &
DeviceConfigurationKeyValueDescriptionListData::
    getDeviceConfigurationKeyValueDescriptionData() const {
  return m_deviceConfigurationKeyValueDescriptionData;
}

void DeviceConfigurationKeyValueDescriptionListData::
    cleanDeviceConfigurationKeyValueDescriptionData() {
  m_deviceConfigurationKeyValueDescriptionData.clear();
  m_deviceConfigurationKeyValueDescriptionDataIsSet = false;
}

bool DeviceConfigurationKeyValueDescriptionListData::
    getDeviceConfigurationKeyValueDescriptionDataIsSet() const {
  return m_deviceConfigurationKeyValueDescriptionDataIsSet;
}

CmdDataPtr DeviceConfigurationKeyValueDescriptionListData::reduce(
    const std::vector<Filter> &filters) const {
  std::vector<DeviceConfigurationKeyValueDescriptionData> dataOut;
  for (const auto &data : getDeviceConfigurationKeyValueDescriptionData()) {
    if (!filters.empty()) {
      const auto &filter = filters[0];
      if (filter.getCmdControl() == CmdControl::PARTIAL) {
        // For READ semantics only "partial" filters make sense
        bool isSelected =
            filter.getDataSelectors()
                .empty(); // always select when there are no filters
        for (const auto &baseSelectorsClass : filter.getDataSelectors()) {
          DeviceConfigurationKeyValueDescriptionListDataSelectorsPtr selectors =
              std::dynamic_pointer_cast<
                  DeviceConfigurationKeyValueDescriptionListDataSelectors>(
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
          const DeviceConfigurationKeyValueDescriptionDataElementsPtr
              elementsClass = std::dynamic_pointer_cast<
                  DeviceConfigurationKeyValueDescriptionDataElements>(
                  filter.getDataElements());
          if (elementsClass) {
            dataOut.push_back(data.reduce(*elementsClass.get()));
          } else {
            dataOut.push_back(DeviceConfigurationKeyValueDescriptionData(data));
          }
        }
      } else {
        return std::make_shared<DeviceConfigurationKeyValueDescriptionListData>(
            *this);
      }
    } else {
      return std::make_shared<DeviceConfigurationKeyValueDescriptionListData>(
          *this);
    }
  }
  if (!dataOut.empty()) {
    return std::make_shared<DeviceConfigurationKeyValueDescriptionListData>(
        dataOut);
  } else {
    return std::make_shared<DeviceConfigurationKeyValueDescriptionListData>();
  }
}

bool DeviceConfigurationKeyValueDescriptionListData::fromJson(
    KeoJsonValue *json) {
  if (!json->empty()) {
    if (!KeoJsonTransformation::hasCorrectOrder(
            json, {"deviceConfigurationKeyValueDescriptionData"})) {
      throw DatagramParserException("Incorrect order");
    }

    auto iter = json->begin();
    if (iter != json->end() &&
        KeoJsonTransformation::getList<
            DeviceConfigurationKeyValueDescriptionData>(
            static_cast<KeoJsonValue *>(&(*iter)),
            "deviceConfigurationKeyValueDescriptionData",
            &m_deviceConfigurationKeyValueDescriptionData)) {
      m_deviceConfigurationKeyValueDescriptionDataIsSet = true;
      ++iter;
    }
  }
  return true;
}

std::string DeviceConfigurationKeyValueDescriptionListData::toJson() const {
  std::string result = "[";
  if (m_deviceConfigurationKeyValueDescriptionDataIsSet) {
    KeoJsonTransformation::appendCommaIfObjectPrecedent(result);
    result += KeoJsonTransformation::writeList<
        DeviceConfigurationKeyValueDescriptionData>(
        "deviceConfigurationKeyValueDescriptionData",
        m_deviceConfigurationKeyValueDescriptionData);
  }
  result += "]";
  return result;
}

} // namespace keo_datagram