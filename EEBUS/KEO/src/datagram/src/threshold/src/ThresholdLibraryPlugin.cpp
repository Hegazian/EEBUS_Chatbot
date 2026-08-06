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

#include <keo_datagram/threshold/ThresholdConstraintsDataElements.h>
#include <keo_datagram/threshold/ThresholdConstraintsListData.h>
#include <keo_datagram/threshold/ThresholdConstraintsListDataSelectors.h>
#include <keo_datagram/threshold/ThresholdDataElements.h>
#include <keo_datagram/threshold/ThresholdDescriptionDataElements.h>
#include <keo_datagram/threshold/ThresholdDescriptionListData.h>
#include <keo_datagram/threshold/ThresholdDescriptionListDataSelectors.h>
#include <keo_datagram/threshold/ThresholdListData.h>
#include <keo_datagram/threshold/ThresholdListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class ThresholdDatagramPlugin : public KeoDatagramPlugin {
public:
  ThresholdDatagramPlugin();
  virtual ~ThresholdDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(ThresholdDatagramPlugin, "Threshold Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

ThresholdDatagramPlugin::ThresholdDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

ThresholdDatagramPlugin::~ThresholdDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new ThresholdDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
ThresholdDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<ThresholdConstraintsListData>();
  case CmdData::Type::THRESHOLD_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<ThresholdDescriptionListData>();
  case CmdData::Type::THRESHOLD_LIST_DATA_TYPE:
    return std::make_shared<ThresholdListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr ThresholdDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::THRESHOLD_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<ThresholdConstraintsListDataSelectors>();
  case DataSelectors::Type::THRESHOLD_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<ThresholdDescriptionListDataSelectors>();
  case DataSelectors::Type::THRESHOLD_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<ThresholdListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr ThresholdDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::THRESHOLD_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<ThresholdConstraintsDataElements>();
  case DataElements::Type::THRESHOLD_DATA_ELEMENTS_TYPE:
    return std::make_shared<ThresholdDataElements>();
  case DataElements::Type::THRESHOLD_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<ThresholdDescriptionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
