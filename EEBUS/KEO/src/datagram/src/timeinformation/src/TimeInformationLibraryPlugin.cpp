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

#include <keo_datagram/timeinformation/TimeDistributorData.h>
#include <keo_datagram/timeinformation/TimeDistributorDataElements.h>
#include <keo_datagram/timeinformation/TimeDistributorEnquiryCall.h>
#include <keo_datagram/timeinformation/TimeDistributorEnquiryCallElements.h>
#include <keo_datagram/timeinformation/TimeInformationData.h>
#include <keo_datagram/timeinformation/TimeInformationDataElements.h>
#include <keo_datagram/timeinformation/TimePrecisionData.h>
#include <keo_datagram/timeinformation/TimePrecisionDataElements.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class TimeInformationDatagramPlugin : public KeoDatagramPlugin {
public:
  TimeInformationDatagramPlugin();
  virtual ~TimeInformationDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(TimeInformationDatagramPlugin,
                    "TimeInformation Datagram Plugin", SPINE_VERSION_STRING,
                    SPINE_VERSION_POSTFIX)

TimeInformationDatagramPlugin::TimeInformationDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

TimeInformationDatagramPlugin::~TimeInformationDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new TimeInformationDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
TimeInformationDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::TIME_DISTRIBUTOR_DATA_TYPE:
    return std::make_shared<TimeDistributorData>();
  case CmdData::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE:
    return std::make_shared<TimeDistributorEnquiryCall>();
  case CmdData::Type::TIME_INFORMATION_DATA_TYPE:
    return std::make_shared<TimeInformationData>();
  case CmdData::Type::TIME_PRECISION_DATA_TYPE:
    return std::make_shared<TimePrecisionData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr TimeInformationDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr TimeInformationDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::TIME_DISTRIBUTOR_DATA_ELEMENTS_TYPE:
    return std::make_shared<TimeDistributorDataElements>();
  case DataElements::Type::TIME_DISTRIBUTOR_ENQUIRY_CALL_ELEMENTS_TYPE:
    return std::make_shared<TimeDistributorEnquiryCallElements>();
  case DataElements::Type::TIME_INFORMATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TimeInformationDataElements>();
  case DataElements::Type::TIME_PRECISION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TimePrecisionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
