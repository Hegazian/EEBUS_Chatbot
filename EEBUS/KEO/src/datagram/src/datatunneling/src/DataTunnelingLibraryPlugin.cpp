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

#include <keo_datagram/datatunneling/DataTunnelingCall.h>
#include <keo_datagram/datatunneling/DataTunnelingCallElements.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class DataTunnelingDatagramPlugin : public KeoDatagramPlugin {
public:
  DataTunnelingDatagramPlugin();
  virtual ~DataTunnelingDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(DataTunnelingDatagramPlugin,
                    "DataTunneling Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

DataTunnelingDatagramPlugin::DataTunnelingDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

DataTunnelingDatagramPlugin::~DataTunnelingDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new DataTunnelingDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
DataTunnelingDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::DATA_TUNNELING_CALL_TYPE:
    return std::make_shared<DataTunnelingCall>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr DataTunnelingDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr DataTunnelingDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::DATA_TUNNELING_CALL_ELEMENTS_TYPE:
    return std::make_shared<DataTunnelingCallElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
