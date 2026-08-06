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

#ifndef KEO_FRAMEWORK_SRC_DEVICECALLBACKINTERFACE_H_
#define KEO_FRAMEWORK_SRC_DEVICECALLBACKINTERFACE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/DetailedDiscoveryPartial.h>
#include <keo_datagram/core/UseCaseDiscovery.h>
#include <keo_spine/DatagramRecord.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <list>
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

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

/**
 * Interface for an application to get SPINE-related callbacks from a device.
 */
class DeviceCallbackInterface
{
public:
    virtual ~DeviceCallbackInterface()
    {
    }

    /**
     * Announce a new transport connection. This callback is used if the device
     * is a main device @see {@link SpineLink#setMainDevice(SmartDevice)}
     *
     * @param transportId
     *            Identifier of the transport connection
     */
    virtual void onConnected(const std::string& transportId) = 0;

    /**
     * Callback to announce the closing of a transport connection. This callback
     * is used if the device is a main device @see
     * {@link SpineLink#setMainDevice(SmartDevice)}
     *
     * @param transportId
     *            Identifier of the transport connection
     */
    virtual void onDisconnect(const std::string& transportId) = 0;

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
    virtual void onDetailedDiscoveryFailed(const std::string& transportId) = 0;

    /**
     * Callback to announce new devices.
     *
     * @param devices
     *            New devices
     */
    virtual void onNewDevices(const std::vector<std::string>& devices) = 0;

    /**
     * Callback to announce the removal of devices either via a destination list
     * update or closing of a transport connection.
     *
     * @param devices
     *            Removed devices
     */
    virtual void onRemovedDevices(const std::vector<std::string>& devices) = 0;

    /**
     * Callback to announce an update for a device
     *
     * @param deviceName
     *            Name of the device of the DetailedDiscovery
     * @param detailedDiscovery
     *            Detailed discovery of this device
     */
    virtual void onDetailedDiscovery(const std::string& deviceName,
                                     const keo_datagram::DetailedDiscovery& detailedDiscovery) = 0;

    /**
     * Callback to announce a partial update for a device
     *
     * @param deviceName
     *            Name of the device of the DetailedDiscoveryPartial
     * @param detailedDiscoveryPartial
     *            Partial detailed discovery of this device
     */
    virtual void onDetailedDiscoveryPartial(const std::string& deviceName,
                                            const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) = 0;

    /**
     * Callback to announce use case data of another device.
     *
     * @param deviceName
     *            Name of the device of the UseCaseData
     * @param useCaseDiscovery
     *            a UseCaseDiscovery object containing local and remote NodeManagementUseCaseData
     */
    virtual void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
    {
        (void)deviceName;
        (void)useCaseDiscovery;
    }
};

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_SRC_DEVICECALLBACKINTERFACE_H_ */
