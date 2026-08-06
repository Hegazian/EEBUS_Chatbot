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

#include <keo_datagram/timetable/TimeTableConstraintsDataElements.h>
#include <keo_datagram/timetable/TimeTableConstraintsListData.h>
#include <keo_datagram/timetable/TimeTableConstraintsListDataSelectors.h>
#include <keo_datagram/timetable/TimeTableDataElements.h>
#include <keo_datagram/timetable/TimeTableDescriptionDataElements.h>
#include <keo_datagram/timetable/TimeTableDescriptionListData.h>
#include <keo_datagram/timetable/TimeTableDescriptionListDataSelectors.h>
#include <keo_datagram/timetable/TimeTableListData.h>
#include <keo_datagram/timetable/TimeTableListDataSelectors.h>

namespace keo_datagram {

/* ******************************************************************************
 *
    class ##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: definition
 *
 ******************************************************************************
 */
class TimeTableDatagramPlugin : public KeoDatagramPlugin {
public:
  TimeTableDatagramPlugin();
  virtual ~TimeTableDatagramPlugin();

  CmdDataPtr createCmdData(const CmdData::Type type) const override;
  DataSelectorsPtr
  createDataSelectors(const DataSelectors::Type type) const override;
  DataElementsPtr
  createDataElements(const DataElements::Type type) const override;
};

KEO_DATAGRAM_PLUGIN(TimeTableDatagramPlugin, "TimeTable Datagram Plugin",
                    SPINE_VERSION_STRING, SPINE_VERSION_POSTFIX)

TimeTableDatagramPlugin::TimeTableDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Create" <<
  // std::endl;
}

TimeTableDatagramPlugin::~TimeTableDatagramPlugin() {
  // std::cout << "##LIBRARY_PLUGIN_CLASS_NAME##DatagramPlugin: Destroy" <<
  // std::endl;
}

extern "C" KeoDatagramPlugin *createPlugin() {
  return new TimeTableDatagramPlugin;
}

extern "C" void destroyPlugin(KeoDatagramPlugin *p) { delete p; }

CmdDataPtr
TimeTableDatagramPlugin::createCmdData(const CmdData::Type type) const {
  switch (type) {
  case CmdData::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE:
    return std::make_shared<TimeTableConstraintsListData>();
  case CmdData::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<TimeTableDescriptionListData>();
  case CmdData::Type::TIME_TABLE_LIST_DATA_TYPE:
    return std::make_shared<TimeTableListData>();

  default: { break; }
  }
  return CmdDataPtr();
}

DataSelectorsPtr TimeTableDatagramPlugin::createDataSelectors(
    const DataSelectors::Type type) const {
  switch (type) {
  case DataSelectors::Type::TIME_TABLE_CONSTRAINTS_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TimeTableConstraintsListDataSelectors>();
  case DataSelectors::Type::TIME_TABLE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TimeTableDescriptionListDataSelectors>();
  case DataSelectors::Type::TIME_TABLE_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<TimeTableListDataSelectors>();

  default: { break; }
  }
  return DataSelectorsPtr();
}

DataElementsPtr TimeTableDatagramPlugin::createDataElements(
    const DataElements::Type type) const {
  switch (type) {
  case DataElements::Type::TIME_TABLE_CONSTRAINTS_DATA_ELEMENTS_TYPE:
    return std::make_shared<TimeTableConstraintsDataElements>();
  case DataElements::Type::TIME_TABLE_DATA_ELEMENTS_TYPE:
    return std::make_shared<TimeTableDataElements>();
  case DataElements::Type::TIME_TABLE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<TimeTableDescriptionDataElements>();

  default: { break; }
  }
  return DataElementsPtr();
}

} // namespace keo_datagram
