/*
 *     Copyright KEO GmbH 2016 - All rights reserved!
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

#ifndef KEO_FRAMEWORK_EXAMPLE_SERVER_SRC_EXAMPLESERVER_APPLICATION_H_
#define KEO_FRAMEWORK_EXAMPLE_SERVER_SRC_EXAMPLESERVER_APPLICATION_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "MeasurementServerFeature.h"
#include "TrustAllShipTransportConnector.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/Core_All.h>
#include <keo_default_ship_transport/ShipTransportConfiguration.h>
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

namespace keo_spine_example_server
{

/**
 * @addtogroup framework_example_server
 * @{
 */

/**
 * ExampleServerApplication is the outermost instance that manages the application components.
 *
 * It is responsible for controlling the SHIP stack as well as managing SPINE features
 * that contain the example's business logic.
 */

class ExampleServerApplication : public keo_spine::DeviceCallbackInterface
{
public:
    /**
     * Constructor
     */
    ExampleServerApplication();

    /**
     * Destructor
     */
    virtual ~ExampleServerApplication();

    /**
     * Start the SPINE application
     *
     * @param configurationFileName
     *            configuration file
     *
     * @return true if the application has been initialized and started, false otherwise
     */
    bool start(const std::string& configurationFileName);

    /**
     * Close all
     */
    void close();

    /**
     * Announce a new transport connection. This callback is used if the device
     * is a main device @see {@link SpineLink#setMainDevice(SmartDevice)}
     *
     * @param transportId
     *            Identifier of the transport connection
     */
    void onConnected(const std::string& transportId) override;

    /**
     * Callback to announce the closing of a transport connection. This callback
     * is used if the device is a main device @see
     * {@link SpineLink#setMainDevice(SmartDevice)}
     *
     * @param transportId
     *            Identifier of the transport connection
     */
    void onDisconnect(const std::string& transportId) override;

    /**
     * Callback to signal a failed detailed discovery read on this transport
     * connection. The SmartDevice sends a initial read of the detailed
     * discovery on a new transport connection to gather the information of the
     * peer device. If this detailed discovery fails, the connection is not
     * usable.
     *
     * This callback is used if the device is a main device @see
     * {@link SpineLink#setMainDevice(SmartDevice)}
     *
     *
     * @param transportId
     *            Identifier of the transport connection.
     */
    void onDetailedDiscoveryFailed(const std::string& transportId) override;

    /**
     * Callback to announce new devices.
     *
     * @param devices
     *            New devices
     */
    void onNewDevices(const std::vector<std::string>& devices) override;

    /**
     * Callback to announce the removal of devices either via a destination list
     * update or closing of a transport connection.
     *
     * @param devices
     *            Removed devices
     */
    void onRemovedDevices(const std::vector<std::string>& devices) override;

    /**
     * Callback to announce an update for a device
     *
     * @param deviceName
     *            Name of the device of the DetailedDiscovery
     * @param detailedDiscovery
     *            Detailed discovery of this device
     */
    void onDetailedDiscovery(const std::string& deviceName,
                                     const keo_datagram::DetailedDiscovery& detailedDiscovery) override;

    /**
     * Callback to announce a partial update for a device
     *
     * @param deviceName
     *            Name of the device of the DetailedDiscoveryPartial
     * @param detailedDiscoveryPartial
     *            Partial detailed discovery of this device
     */
    void onDetailedDiscoveryPartial(const std::string& deviceName,
                                            const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override;

private:
    /**
     * Get NetworkManagementDeviceDescriptionData from configurations
     *
     * @param spineDeviceName
     *            the SPINE device name of the device
     * @return NetworkManagementDeviceDescriptionData
     */
    keo_datagram::NetworkManagementDeviceDescriptionData getNetworkManagementDeviceDescriptionData(
        const std::string& spineDeviceName);

    /**
     * Set the NetworkManagement entity
     *
     * @param device
     *            Device to set NetworkManagement entity to
     */
    void setNetworkManagementEntity(keo_spine::SmartDevicePtr device);

    /**
     * Add an entity with a measurement feature
     *
     * @param device
     *            Device to add the entity to
     */
    void addGenericEntityWithMeasurementFeature(keo_spine::SmartDevicePtr device);

    /**
     * Main device - measurement server
     */
    keo_spine::SmartDevicePtr device;

    /**
     * The SpineLink distributes the datagrams to their destinations
     */
    keo_spine::SpineLinkPtr spineLink;

    /**
     * Example server application
     */
    TrustAllShipTransportConnector* shipConnector;
};

/** @} */

} // namespace keo_spine_example_server

#endif /* KEO_FRAMEWORK_EXAMPLE_SERVER_SRC_EXAMPLESERVER_APPLICATION_H_ */
