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

#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionDataElements.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionDescriptionListDataSelectors.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionDataElements.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionListDataSelectors.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetDataElements.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetListDataSelectors.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionStateDataElements.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionStateListData.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionStateListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class ElectricalConnectionDatagramPlugin : public KeoDatagramPlugin {
public:
  ElectricalConnectionDatagramPlugin();
  virtual ~ElectricalConnectionDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(ElectricalConnectionDatagramPlugin,
                    "ElectricalConnection Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

ElectricalConnectionDatagramPlugin::ElectricalConnectionDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

ElectricalConnectionDatagramPlugin::~ElectricalConnectionDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new ElectricalConnectionDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr ElectricalConnectionDatagramPlugin::createCmdData(
    const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<ElectricalConnectionDescriptionListData>();
  case CmdData::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<ElectricalConnectionParameterDescriptionListData>();
  case CmdData::Type::ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE:
    return std::make_shared<ElectricalConnectionPermittedValueSetListData>();
  case CmdData::Type::ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE:
    return std::make_shared<ElectricalConnectionStateListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr ElectricalConnectionDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<ElectricalConnectionDescriptionListDataSelectors>();
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        ElectricalConnectionParameterDescriptionListDataSelectors>();
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        ElectricalConnectionPermittedValueSetListDataSelectors>();
  case DataSelectors::Type::
      ELECTRICAL_CONNECTION_STATE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<ElectricalConnectionStateListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr ElectricalConnectionDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::ELECTRICAL_CONNECTION_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<ElectricalConnectionDescriptionDataElements>();
  case DataElements::Type::
      ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        ElectricalConnectionParameterDescriptionDataElements>();
  case DataElements::Type::
      ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_DATA_ELEMENTS_TYPE:
    return std::make_shared<
        ElectricalConnectionPermittedValueSetDataElements>();
  case DataElements::Type::ELECTRICAL_CONNECTION_STATE_DATA_ELEMENTS_TYPE:
    return std::make_shared<ElectricalConnectionStateDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
