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

#include <keo_datagram/directcontrol/DirectControlActivityDataElements.h>
#include <keo_datagram/directcontrol/DirectControlActivityListData.h>
#include <keo_datagram/directcontrol/DirectControlActivityListDataSelectors.h>
#include <keo_datagram/directcontrol/DirectControlDescriptionData.h>
#include <keo_datagram/directcontrol/DirectControlDescriptionDataElements.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class DirectControlDatagramPlugin : public KeoDatagramPlugin {
public:
  DirectControlDatagramPlugin();
  virtual ~DirectControlDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(DirectControlDatagramPlugin,
                    "DirectControl Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

DirectControlDatagramPlugin::DirectControlDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

DirectControlDatagramPlugin::~DirectControlDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new DirectControlDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
DirectControlDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE:
    return std::make_shared<DirectControlActivityListData>();
  case CmdData::Type::DIRECT_CONTROL_DESCRIPTION_DATA_TYPE:
    return std::make_shared<DirectControlDescriptionData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr DirectControlDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::DIRECT_CONTROL_ACTIVITY_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<DirectControlActivityListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr DirectControlDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::DIRECT_CONTROL_ACTIVITY_DATA_ELEMENTS_TYPE:
    return std::make_shared<DirectControlActivityDataElements>();
  case DataElements::Type::DIRECT_CONTROL_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<DirectControlDescriptionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
