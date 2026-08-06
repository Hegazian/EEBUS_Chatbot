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

#include "CreateSpineDataClass.h"
#include <KeoDatagramPlugin.h>
#include <keo_spine_datagramVersion.h>
#include <stdio.h>

#include <keo_datagram/core/BindingManagementDeleteCall.h>
#include <keo_datagram/core/BindingManagementDeleteCallElements.h>
#include <keo_datagram/core/BindingManagementEntryDataElements.h>
#include <keo_datagram/core/BindingManagementEntryListData.h>
#include <keo_datagram/core/BindingManagementEntryListDataSelectors.h>
#include <keo_datagram/core/BindingManagementRequestCall.h>
#include <keo_datagram/core/BindingManagementRequestCallElements.h>
#include <keo_datagram/core/CommodityDataElements.h>
#include <keo_datagram/core/CommodityListData.h>
#include <keo_datagram/core/CommodityListDataSelectors.h>
#include <keo_datagram/core/DeviceClassificationManufacturerData.h>
#include <keo_datagram/core/DeviceClassificationManufacturerDataElements.h>
#include <keo_datagram/core/DeviceClassificationUserData.h>
#include <keo_datagram/core/DeviceClassificationUserDataElements.h>
#include <keo_datagram/core/NetworkManagementAbortCall.h>
#include <keo_datagram/core/NetworkManagementAbortCallElements.h>
#include <keo_datagram/core/NetworkManagementAddNodeCall.h>
#include <keo_datagram/core/NetworkManagementAddNodeCallElements.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionDataElements.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionListData.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionListDataSelectors.h>
#include <keo_datagram/core/NetworkManagementDiscoverCall.h>
#include <keo_datagram/core/NetworkManagementDiscoverCallElements.h>
#include <keo_datagram/core/NetworkManagementEntityDescriptionDataElements.h>
#include <keo_datagram/core/NetworkManagementEntityDescriptionListData.h>
#include <keo_datagram/core/NetworkManagementEntityDescriptionListDataSelectors.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionDataElements.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionListData.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionListDataSelectors.h>
#include <keo_datagram/core/NetworkManagementJoiningModeData.h>
#include <keo_datagram/core/NetworkManagementJoiningModeDataElements.h>
#include <keo_datagram/core/NetworkManagementModifyNodeCall.h>
#include <keo_datagram/core/NetworkManagementModifyNodeCallElements.h>
#include <keo_datagram/core/NetworkManagementProcessStateData.h>
#include <keo_datagram/core/NetworkManagementProcessStateDataElements.h>
#include <keo_datagram/core/NetworkManagementRemoveNodeCall.h>
#include <keo_datagram/core/NetworkManagementRemoveNodeCallElements.h>
#include <keo_datagram/core/NetworkManagementReportCandidateData.h>
#include <keo_datagram/core/NetworkManagementReportCandidateDataElements.h>
#include <keo_datagram/core/NetworkManagementScanNetworkCall.h>
#include <keo_datagram/core/NetworkManagementScanNetworkCallElements.h>
#include <keo_datagram/core/NodeManagementBindingData.h>
#include <keo_datagram/core/NodeManagementBindingDataElements.h>
#include <keo_datagram/core/NodeManagementBindingDataSelectors.h>
#include <keo_datagram/core/NodeManagementBindingDeleteCall.h>
#include <keo_datagram/core/NodeManagementBindingDeleteCallElements.h>
#include <keo_datagram/core/NodeManagementBindingRequestCall.h>
#include <keo_datagram/core/NodeManagementBindingRequestCallElements.h>
#include <keo_datagram/core/NodeManagementDestinationDataElements.h>
#include <keo_datagram/core/NodeManagementDestinationListData.h>
#include <keo_datagram/core/NodeManagementDestinationListDataSelectors.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryData.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryDataElements.h>
#include <keo_datagram/core/NodeManagementDetailedDiscoveryDataSelectors.h>
#include <keo_datagram/core/NodeManagementSubscriptionData.h>
#include <keo_datagram/core/NodeManagementSubscriptionDataElements.h>
#include <keo_datagram/core/NodeManagementSubscriptionDataSelectors.h>
#include <keo_datagram/core/NodeManagementSubscriptionDeleteCall.h>
#include <keo_datagram/core/NodeManagementSubscriptionDeleteCallElements.h>
#include <keo_datagram/core/NodeManagementSubscriptionRequestCall.h>
#include <keo_datagram/core/NodeManagementSubscriptionRequestCallElements.h>
#include <keo_datagram/core/NodeManagementUseCaseData.h>
#include <keo_datagram/core/NodeManagementUseCaseDataElements.h>
#include <keo_datagram/core/NodeManagementUseCaseDataSelectors.h>
#include <keo_datagram/core/ResultData.h>
#include <keo_datagram/core/SpecificationVersionDataElements.h>
#include <keo_datagram/core/SpecificationVersionListData.h>
#include <keo_datagram/core/SpecificationVersionListDataSelectors.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCallElements.h>
#include <keo_datagram/core/SubscriptionManagementEntryDataElements.h>
#include <keo_datagram/core/SubscriptionManagementEntryListData.h>
#include <keo_datagram/core/SubscriptionManagementEntryListDataSelectors.h>
#include <keo_datagram/core/SubscriptionManagementRequestCall.h>
#include <keo_datagram/core/SubscriptionManagementRequestCallElements.h>
#include <keo_datagram/core/UseCaseInformationDataElements.h>
#include <keo_datagram/core/UseCaseInformationListData.h>
#include <keo_datagram/core/UseCaseInformationListDataSelectors.h>

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <vector>

namespace keo_datagram {

#define KEO_DATAGRAM_DEBUG 0

#if KEO_DATAGRAM_DEBUG == 1
#define DBG_OUT(format, args...) fprintf(stdout, format, ##__VA_ARGS__)
#else
#define DBG_OUT(...)
#endif

class KeoDatagramPluginLibrary {
public:
  KeoDatagramPluginLibrary()
      : lib(nullptr), info(nullptr), plugin(nullptr), destroyPlugin(nullptr) {}

  ~KeoDatagramPluginLibrary() { close(); }

  /// Opens a shared library.
  /// The filename is in utf-8. Returns true on success and false on error.
  /// Call `SharedLibrary::error()` to get the error message.
  bool open(const std::string &path) {
    if (!isOpen()) {
      if (0 == (lib = ::dlopen(path.c_str(), RTLD_LAZY))) {
        DBG_OUT("Cannot load library %s", path.c_str());
        return false;
      }

      if (!sym("datagramPluginExports", reinterpret_cast<void **>(&info))) {
        DBG_OUT("Cannot find plugin symbol in library %s", path.c_str());
        ::dlclose(lib);
        lib = nullptr;
        return false;
      }

      if (!create()) {
        ::dlclose(lib);
        lib = nullptr;
        return false;
      }
      return true;
    }

    return false;
  }

  /// Closes the shared library.
  void close() {
    if (isOpen()) {
      this->destroyPlugin(plugin);
      plugin = nullptr;
      ::dlclose(lib);
    }
  }

  KeoDatagramPlugin *getPlugin() const { return plugin; }

  const KeoDatagramPluginDetails *getPluginInfo() const { return info; }

  bool isOpen() const { return (plugin != nullptr); }

private:
  /// Retrieves a data pointer from a dynamic library.
  /// It is legal for a symbol to map to nullptr.
  /// Returns true on success and false if the symbol was not found.
  bool sym(const char *name, void **ptr) {
    if (nullptr != lib) {
      ::dlerror(); /* clear error code */
      char *error;
      *ptr = ::dlsym(lib, name);
      if ((error = ::dlerror()) != 0) {
        DBG_OUT("Error: Symbol not found! %s", error);
        return false;
      }
      return true;
    }
    return false;
  }

  bool create() {
    createPlugin_t *createPlugin;

    if (!sym("createPlugin", reinterpret_cast<void **>(&createPlugin))) {
      return false;
    }

    if (!sym("destroyPlugin", reinterpret_cast<void **>(&destroyPlugin))) {
      return false;
    }

    plugin = createPlugin();
    return true;
  }

protected:
  void *lib;
  KeoDatagramPluginDetails *info;
  KeoDatagramPlugin *plugin;
  destroyPlugin_t *destroyPlugin;
};

std::map<std::string, KeoDatagramPluginLibrary *> *gPluginMap;

__attribute__((constructor)) void on_load() {
  DBG_OUT("core::on_load()\n");

  gPluginMap = new std::map<std::string, KeoDatagramPluginLibrary *>();

  std::vector<std::string> libraries = {
      "actuator",
      "alarm",
      "bill",
      "datatunneling",
      "deviceconfiguration",
      "devicediagnosis",
      "directcontrol",
      "electricalconnection",
      "hvac",
      "identification",
      "incentivetable",
      "loadcontrol",
      "measurement",
      "messaging",
      "operatingconstraints",
      "sensing",
      "setpoint",
      "smartenergymanagementps",
      "supplycondition",
      "taskmanagement",
      "threshold",
      "timeinformation",
      "timeseries",
      "timetable",

  };

  for (std::string const &library : libraries) {
    // Set the plugin shared library location
    std::string path;
    path += "libkeo_datagram_" + library;
    path += ".so.";
    path += std::to_string(keo_spine_datagram_VERSION_MAJOR);

    // Load the shared library
    DBG_OUT("Loading library %s", path.c_str());
    KeoDatagramPluginLibrary *pLib = new KeoDatagramPluginLibrary();

    // try to open the plugin library
    if (pLib->open(path)) {
      const KeoDatagramPluginDetails *info = pLib->getPluginInfo();
      DBG_OUT("\nPluginInfo:\n"
              "   API Version    : %d\n"
              "   Class Name     : %s\n"
              "   Plugin Name    : %s\n"
              "   SPINE Version  : %s\n",
              info->apiVersion, info->className, info->pluginName,
              info->spineVersion);

      // API Version checking
      if (info->apiVersion != KEO_DATAGRAM_PLUGIN_API_VERSION) {
        DBG_OUT("Plugin ABI version mismatch. Expected %d got %d!",
                KEO_DATAGRAM_PLUGIN_API_VERSION, info->apiVersion);
        delete pLib;
      } else if (std::string(info->spineVersion) !=
                     std::string(SPINE_VERSION_STRING) ||
                 std::string(info->spineVersionString) !=
                     std::string(SPINE_VERSION_POSTFIX)) {
        DBG_OUT("Plugin SPINE version mismatch!");
        delete pLib;
      } else {
        // store plugin
        gPluginMap->insert(std::pair<std::string, KeoDatagramPluginLibrary *>(
            std::string(info->className), pLib));
      }
    } else {
      DBG_OUT("Load plugin library %s failed!", path.c_str());
      delete pLib;
    }
  }
}

__attribute__((destructor)) void on_unload() {
  DBG_OUT("core::on_unload\n");

  // Close the plugin and free memory
  std::map<std::string, KeoDatagramPluginLibrary *>::const_iterator it =
      gPluginMap->begin();
  while (it != gPluginMap->end()) {
    delete it->second;
    gPluginMap->erase(it++);
  }

  delete gPluginMap;
  gPluginMap = nullptr;
}

CmdDataPtr CreateSpineDataClass::createCmdData(const CmdData::Type type) {
  switch (type) {
  case CmdData::Type::BINDING_MANAGEMENT_DELETE_CALL_TYPE:
    return std::make_shared<BindingManagementDeleteCall>();
  case CmdData::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE:
    return std::make_shared<BindingManagementEntryListData>();
  case CmdData::Type::BINDING_MANAGEMENT_REQUEST_CALL_TYPE:
    return std::make_shared<BindingManagementRequestCall>();
  case CmdData::Type::COMMODITY_LIST_DATA_TYPE:
    return std::make_shared<CommodityListData>();
  case CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE:
    return std::make_shared<DeviceClassificationManufacturerData>();
  case CmdData::Type::DEVICE_CLASSIFICATION_USER_DATA_TYPE:
    return std::make_shared<DeviceClassificationUserData>();
  case CmdData::Type::NETWORK_MANAGEMENT_ABORT_CALL_TYPE:
    return std::make_shared<NetworkManagementAbortCall>();
  case CmdData::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE:
    return std::make_shared<NetworkManagementAddNodeCall>();
  case CmdData::Type::NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<NetworkManagementDeviceDescriptionListData>();
  case CmdData::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE:
    return std::make_shared<NetworkManagementDiscoverCall>();
  case CmdData::Type::NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<NetworkManagementEntityDescriptionListData>();
  case CmdData::Type::NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE:
    return std::make_shared<NetworkManagementFeatureDescriptionListData>();
  case CmdData::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE:
    return std::make_shared<NetworkManagementJoiningModeData>();
  case CmdData::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE:
    return std::make_shared<NetworkManagementModifyNodeCall>();
  case CmdData::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE:
    return std::make_shared<NetworkManagementProcessStateData>();
  case CmdData::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE:
    return std::make_shared<NetworkManagementRemoveNodeCall>();
  case CmdData::Type::NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE:
    return std::make_shared<NetworkManagementReportCandidateData>();
  case CmdData::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE:
    return std::make_shared<NetworkManagementScanNetworkCall>();
  case CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE:
    return std::make_shared<NodeManagementBindingData>();
  case CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE:
    return std::make_shared<NodeManagementBindingDeleteCall>();
  case CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE:
    return std::make_shared<NodeManagementBindingRequestCall>();
  case CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE:
    return std::make_shared<NodeManagementDestinationListData>();
  case CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE:
    return std::make_shared<NodeManagementDetailedDiscoveryData>();
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE:
    return std::make_shared<NodeManagementSubscriptionData>();
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE:
    return std::make_shared<SubscriptionManagementDeleteCall>();
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE:
    return std::make_shared<NodeManagementSubscriptionDeleteCall>();
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_TYPE:
    return std::make_shared<SubscriptionManagementRequestCall>();
  case CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE:
    return std::make_shared<NodeManagementSubscriptionRequestCall>();
  case CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE:
    return std::make_shared<NodeManagementUseCaseData>();
  case CmdData::Type::RESULT_DATA_TYPE:
    return std::make_shared<ResultData>();
  case CmdData::Type::SPECIFICATION_VERSION_LIST_DATA_TYPE:
    return std::make_shared<SpecificationVersionListData>();
  case CmdData::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE:
    return std::make_shared<SubscriptionManagementEntryListData>();
  case CmdData::Type::USE_CASE_INFORMATION_LIST_DATA_TYPE:
    return std::make_shared<UseCaseInformationListData>();

  default: {
    DBG_OUT("Data type not part of the core library.\n");
    for (auto it = gPluginMap->begin(); it != gPluginMap->end(); ++it) {
      DBG_OUT("Test Library %s\n", it->first.c_str());
      CmdDataPtr ptr = it->second->getPlugin()->createCmdData(type);
      if (ptr) {
        DBG_OUT("Library %s, Type %s found\n", it->first.c_str(),
                CmdData::getStringFromType(type));
        return ptr;
      }
    }
    break;
  }
  }
  return CmdDataPtr();
}

DataSelectorsPtr
CreateSpineDataClass::createDataSelectors(const DataSelectors::Type type) {
  switch (type) {
  case DataSelectors::Type::BINDING_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<BindingManagementEntryListDataSelectors>();
  case DataSelectors::Type::COMMODITY_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<CommodityListDataSelectors>();
  case DataSelectors::Type::
      NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        NetworkManagementDeviceDescriptionListDataSelectors>();
  case DataSelectors::Type::
      NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        NetworkManagementEntityDescriptionListDataSelectors>();
  case DataSelectors::Type::
      NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<
        NetworkManagementFeatureDescriptionListDataSelectors>();
  case DataSelectors::Type::NODE_MANAGEMENT_BINDING_DATA_SELECTORS_TYPE:
    return std::make_shared<NodeManagementBindingDataSelectors>();
  case DataSelectors::Type::
      NODE_MANAGEMENT_DESTINATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<NodeManagementDestinationListDataSelectors>();
  case DataSelectors::Type::
      NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_SELECTORS_TYPE:
    return std::make_shared<NodeManagementDetailedDiscoveryDataSelectors>();
  case DataSelectors::Type::
      SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SubscriptionManagementEntryListDataSelectors>();
  case DataSelectors::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_SELECTORS_TYPE:
    return std::make_shared<NodeManagementSubscriptionDataSelectors>();
  case DataSelectors::Type::USE_CASE_INFORMATION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<UseCaseInformationListDataSelectors>();
  case DataSelectors::Type::NODE_MANAGEMENT_USE_CASE_DATA_SELECTORS_TYPE:
    return std::make_shared<NodeManagementUseCaseDataSelectors>();
  case DataSelectors::Type::SPECIFICATION_VERSION_LIST_DATA_SELECTORS_TYPE:
    return std::make_shared<SpecificationVersionListDataSelectors>();

  default: {
    for (auto it = gPluginMap->begin(); it != gPluginMap->end(); ++it) {
      DBG_OUT("Test Library %s\n", it->first.c_str());
      DataSelectorsPtr ptr = it->second->getPlugin()->createDataSelectors(type);
      if (ptr) {
        DBG_OUT("Library %s, Type %s found\n", it->first.c_str(),
                DataSelectors::getStringFromType(type));
        return ptr;
      }
    }

    break;
  }
  }
  return DataSelectorsPtr();
}

DataElementsPtr
CreateSpineDataClass::createDataElements(const DataElements::Type type) {
  switch (type) {
  case DataElements::Type::BINDING_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE:
    return std::make_shared<BindingManagementDeleteCallElements>();
  case DataElements::Type::BINDING_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE:
    return std::make_shared<BindingManagementEntryDataElements>();
  case DataElements::Type::BINDING_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<BindingManagementRequestCallElements>();
  case DataElements::Type::COMMODITY_DATA_ELEMENTS_TYPE:
    return std::make_shared<CommodityDataElements>();
  case DataElements::Type::
      DEVICE_CLASSIFICATION_MANUFACTURER_DATA_ELEMENTS_TYPE:
    return std::make_shared<DeviceClassificationManufacturerDataElements>();
  case DataElements::Type::DEVICE_CLASSIFICATION_USER_DATA_ELEMENTS_TYPE:
    return std::make_shared<DeviceClassificationUserDataElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_ABORT_CALL_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementAbortCallElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_ADD_NODE_CALL_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementAddNodeCallElements>();
  case DataElements::Type::
      NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementDeviceDescriptionDataElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_DISCOVER_CALL_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementDiscoverCallElements>();
  case DataElements::Type::
      NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementEntityDescriptionDataElements>();
  case DataElements::Type::
      NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementFeatureDescriptionDataElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_JOINING_MODE_DATA_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementJoiningModeDataElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_MODIFY_NODE_CALL_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementModifyNodeCallElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_PROCESS_STATE_DATA_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementProcessStateDataElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_REMOVE_NODE_CALL_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementRemoveNodeCallElements>();
  case DataElements::Type::
      NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementReportCandidateDataElements>();
  case DataElements::Type::NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_ELEMENTS_TYPE:
    return std::make_shared<NetworkManagementScanNetworkCallElements>();
  case DataElements::Type::NODE_MANAGEMENT_BINDING_DATA_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementBindingDataElements>();
  case DataElements::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementBindingDeleteCallElements>();
  case DataElements::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementBindingRequestCallElements>();
  case DataElements::Type::NODE_MANAGEMENT_DESTINATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementDestinationDataElements>();
  case DataElements::Type::SPECIFICATION_VERSION_DATA_ELEMENTS_TYPE:
    return std::make_shared<SpecificationVersionDataElements>();
  case DataElements::Type::
      NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementDetailedDiscoveryDataElements>();
  case DataElements::Type::SUBSCRIPTION_MANAGEMENT_ENTRY_DATA_ELEMENTS_TYPE:
    return std::make_shared<SubscriptionManagementEntryDataElements>();
  case DataElements::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementSubscriptionDataElements>();
  case DataElements::Type::SUBSCRIPTION_MANAGEMENT_DELETE_CALL_ELEMENTS_TYPE:
    return std::make_shared<SubscriptionManagementDeleteCallElements>();
  case DataElements::Type::
      NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementSubscriptionDeleteCallElements>();
  case DataElements::Type::SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<SubscriptionManagementRequestCallElements>();
  case DataElements::Type::
      NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementSubscriptionRequestCallElements>();
  case DataElements::Type::USE_CASE_INFORMATION_DATA_ELEMENTS_TYPE:
    return std::make_shared<UseCaseInformationDataElements>();
  case DataElements::Type::NODE_MANAGEMENT_USE_CASE_DATA_ELEMENTS_TYPE:
    return std::make_shared<NodeManagementUseCaseDataElements>();

  default: {
    for (auto it = gPluginMap->begin(); it != gPluginMap->end(); ++it) {
      DBG_OUT("Test Library %s\n", it->first.c_str());
      DataElementsPtr ptr = it->second->getPlugin()->createDataElements(type);
      if (ptr) {
        DBG_OUT("Library %s, Type %s found\n", it->first.c_str(),
                DataElements::getStringFromType(type));
        return ptr;
      }
    }

    break;
  }
  }
  return DataElementsPtr();
}

} // end namespace
