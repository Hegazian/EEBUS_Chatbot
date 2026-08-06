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

#include <keo_datagram/measurement/MeasurementConstraintsDataElements.h>
#include <keo_datagram/measurement/MeasurementConstraintsListData.h>
#include <keo_datagram/measurement/MeasurementConstraintsListDataSelectors.h>
#include <keo_datagram/measurement/MeasurementDataElements.h>
#include <keo_datagram/measurement/MeasurementDescriptionDataElements.h>
#include <keo_datagram/measurement/MeasurementDescriptionListData.h>
#include <keo_datagram/measurement/MeasurementDescriptionListDataSelectors.h>
#include <keo_datagram/measurement/MeasurementListData.h>
#include <keo_datagram/measurement/MeasurementListDataSelectors.h>
#include <keo_datagram/measurement/MeasurementThresholdRelationDataElements.h>
#include <keo_datagram/measurement/MeasurementThresholdRelationListData.h>
#include <keo_datagram/measurement/MeasurementThresholdRelationListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class MeasurementDatagramPlugin : public KeoDatagramPlugin {
public:
  MeasurementDatagramPlugin();
  virtual ~MeasurementDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(MeasurementDatagramPlugin, "Measurement Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

MeasurementDatagramPlugin::MeasurementDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

MeasurementDatagramPlugin::~MeasurementDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new MeasurementDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
MeasurementDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<MeasurementConstraintsListData>();
  case CmdData::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<MeasurementDescriptionListData>();
  case CmdData::Type::MEASUREMENT_LIST_DATA_TYPE:
    return std::make_shared<MeasurementListData>();
  case CmdData::Type::MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE:
    return std::make_shared<MeasurementThresholdRelationListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr MeasurementDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::MEASUREMENT_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<MeasurementConstraintsListDataSelectors>();
  case DataSelectors::Type::MEASUREMENT_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<MeasurementDescriptionListDataSelectors>();
  case DataSelectors::Type::MEASUREMENT_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<MeasurementListDataSelectors>();
  case DataSelectors::Type::
      MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<MeasurementThresholdRelationListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr MeasurementDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::MEASUREMENT_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<MeasurementConstraintsDataElements>();
  case DataElements::Type::MEASUREMENT_DATA_ELEMENTS_TYPE:
    return std::make_shared<MeasurementDataElements>();
  case DataElements::Type::MEASUREMENT_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<MeasurementDescriptionDataElements>();
  case DataElements::Type::MEASUREMENT_THRESHOLD_RELATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<MeasurementThresholdRelationDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
