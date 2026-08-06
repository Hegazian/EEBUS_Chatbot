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

#include <keo_datagram/setpoint/SetpointConstraintsDataElements.h>
#include <keo_datagram/setpoint/SetpointConstraintsListData.h>
#include <keo_datagram/setpoint/SetpointConstraintsListDataSelectors.h>
#include <keo_datagram/setpoint/SetpointDataElements.h>
#include <keo_datagram/setpoint/SetpointDescriptionDataElements.h>
#include <keo_datagram/setpoint/SetpointDescriptionListData.h>
#include <keo_datagram/setpoint/SetpointDescriptionListDataSelectors.h>
#include <keo_datagram/setpoint/SetpointListData.h>
#include <keo_datagram/setpoint/SetpointListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class SetpointDatagramPlugin : public KeoDatagramPlugin {
public:
  SetpointDatagramPlugin();
  virtual ~SetpointDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(SetpointDatagramPlugin, "Setpoint Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

SetpointDatagramPlugin::SetpointDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

SetpointDatagramPlugin::~SetpointDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new SetpointDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
SetpointDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::SETPOINT_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<SetpointConstraintsListData>();
  case CmdData::Type::SETPOINT_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<SetpointDescriptionListData>();
  case CmdData::Type::SETPOINT_LIST_DATA_TYPE:
    return std::make_shared<SetpointListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr SetpointDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::SETPOINT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SetpointConstraintsListDataSelectors>();
  case DataSelectors::Type::SETPOINT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SetpointDescriptionListDataSelectors>();
  case DataSelectors::Type::SETPOINT_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SetpointListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr SetpointDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::SETPOINT_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<SetpointConstraintsDataElements>();
  case DataElements::Type::SETPOINT_DATA_ELEMENTS_TYPE:
    return std::make_shared<SetpointDataElements>();
  case DataElements::Type::SETPOINT_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<SetpointDescriptionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
