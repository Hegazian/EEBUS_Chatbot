/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright notice.
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

#ifndef KEO_FRAMEWORK_EXAMPLE_CLIENT_SRC_EXAMPLECLIENTAPPLICATION_H_
#define KEO_FRAMEWORK_EXAMPLE_CLIENT_SRC_EXAMPLECLIENTAPPLICATION_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "AppConfiguration.h"
#include "MeasurementClientFeature.h"
#include "AutoConnectTrustAllShipConnectorHandler.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/Core_All.h>
#include <keo_spine/DeviceCallbackInterface.h>
#include <keo_spine/SmartDevice.h>
#include <keo_spine/SpineLink.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

/**
 * @addtogroup framework_example_client
 * @{
 */

/**
 * ExampleClientApplication is the outermost instance that manages the application components.
 *
 * It is responsible for controlling the SHIP stack as well as managing SPINE features
 * that contain the example's business logic.
 */
class ExampleClientApplication : public keo_spine::DeviceCallbackInterface
{
public:
    /**
     * Constructor
     */
    ExampleClientApplication();

    /**
     * Destructor
     */
    virtual ~ExampleClientApplication();

    /**
     * Initialize and start the application
     *
     * Reads the configuration file given by the configurationFileName,
     * constructs the required objects, connects them and starts the SHIP stack.
     *
     * @param configurationFileName Filename to the JSON configuration file
     *
     * @return true if the application has been initialized and started, false otherwise
     */
    bool start(const std::string& configurationFileName);

    /**
     * Stop the application
     */
    void stop();

    void onConnected(const std::string& transportId) override;
    void onDisconnect(const std::string& transportId) override;
    void onDetailedDiscoveryFailed(const std::string& transportId) override;
    void onNewDevices(const std::vector<std::string>& devices) override;
    void onRemovedDevices(const std::vector<std::string>& devices) override;
    void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery) override;
    void onDetailedDiscoveryPartial(
        const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override;

private:
    keo_datagram::NetworkManagementDeviceDescriptionData getNetworkManagementDeviceDescriptionData(
        const AppConfiguration& config);
    void addNetworkManagementEntity(keo_spine::SmartDevicePtr device);
    void addGenericEntityWithMeasurementFeature(keo_spine::SmartDevicePtr device);

    /**
     * Main device - measurement client
     */
    keo_spine::SmartDevicePtr device;

    /**
     * The SpineLink distributes the datagrams to their destinations
     */
    keo_spine::SpineLinkPtr spineLink;

    // TODO: doxygen
    AutoConnectTrustAllShipConnectorHandler* shipConnector;
};

/** @}
 */

} // namespace keo_spine_example_client

#endif /* KEO_FRAMEWORK_EXAMPLE_CLIENT_SRC_EXAMPLECLIENTAPPLICATION_H_ */
