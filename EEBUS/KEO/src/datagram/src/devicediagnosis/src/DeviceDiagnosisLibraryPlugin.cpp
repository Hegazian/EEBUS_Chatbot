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

#include <keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatData.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisHeartbeatDataElements.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisServiceData.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisServiceDataElements.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisStateData.h>
#include <keo_datagram/devicediagnosis/DeviceDiagnosisStateDataElements.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class DeviceDiagnosisDatagramPlugin : public KeoDatagramPlugin {
public:
  DeviceDiagnosisDatagramPlugin();
  virtual ~DeviceDiagnosisDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(DeviceDiagnosisDatagramPlugin,
                    "DeviceDiagnosis Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

DeviceDiagnosisDatagramPlugin::DeviceDiagnosisDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

DeviceDiagnosisDatagramPlugin::~DeviceDiagnosisDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new DeviceDiagnosisDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
DeviceDiagnosisDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE:
    return std::make_shared<DeviceDiagnosisHeartbeatData>();
  case CmdData::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE:
    return std::make_shared<DeviceDiagnosisServiceData>();
  case CmdData::Type::DEVICE_DIAGNOSIS_STATE_DATA_TYPE:
    return std::make_shared<DeviceDiagnosisStateData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr DeviceDiagnosisDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr DeviceDiagnosisDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::DEVICE_DIAGNOSIS_HEARTBEAT_DATA_ELEMENTS_TYPE:
    return std::make_shared<DeviceDiagnosisHeartbeatDataElements>();
  case DataElements::Type::DEVICE_DIAGNOSIS_SERVICE_DATA_ELEMENTS_TYPE:
    return std::make_shared<DeviceDiagnosisServiceDataElements>();
  case DataElements::Type::DEVICE_DIAGNOSIS_STATE_DATA_ELEMENTS_TYPE:
    return std::make_shared<DeviceDiagnosisStateDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
