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

#include <KeoDatagramPlugin.h>
#include <keo_spine_datagramVersion.h>

#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsDataElements.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsListData.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueConstraintsListDataSelectors.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDataElements.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionDataElements.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListData.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueDescriptionListDataSelectors.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueListData.h>
#include <keo_datagram/deviceconfiguration/DeviceConfigurationKeyValueListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class DeviceConfigurationDatagramPlugin : public KeoDatagramPlugin {
public:
  DeviceConfigurationDatagramPlugin();
  virtual ~DeviceConfigurationDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(DeviceConfigurationDatagramPlugin,
                    "DeviceConfiguration Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

DeviceConfigurationDatagramPlugin::DeviceConfigurationDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

DeviceConfigurationDatagramPlugin::~DeviceConfigurationDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new DeviceConfigurationDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr DeviceConfigurationDatagramPlugin::createCmdData(
    const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<DeviceConfigurationKeyValueConstraintsListData>();
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<DeviceConfigurationKeyValueDescriptionListData>();
  case CmdData::Type::DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_TYPE:
    return std::make_shared<DeviceConfigurationKeyValueListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr DeviceConfigurationDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        DeviceConfigurationKeyValueConstraintsListDataSelectors>();
  case DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        DeviceConfigurationKeyValueDescriptionListDataSelectors>();
  case DataSelectors::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<DeviceConfigurationKeyValueListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr DeviceConfigurationDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        DeviceConfigurationKeyValueConstraintsDataElements>();
  case DataElements::Type::DEVICE_CONFIGURATION_KEY_VALUE_DATA_ELEMENTS_TYPE:
    return std::make_shared<DeviceConfigurationKeyValueDataElements>();
  case DataElements::Type::
      DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        DeviceConfigurationKeyValueDescriptionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
