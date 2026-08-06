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

#ifndef KEO_FRAMEWORK_SRC_DEVICE_TRANSPORT_ID_HANDLER_H_
#define KEO_FRAMEWORK_SRC_DEVICE_TRANSPORT_ID_HANDLER_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */
#include "keo_spine/DatagramRecord.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <vector>
#include <map>
#include <memory>
#include <mutex>
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

/**
 * @ingroup framework
 * @{
 */

/**
 * TODO brief description
 *
 */
class DeviceTransportIdHandler
{
public:
    /**
     * Constructor
     */
    DeviceTransportIdHandler();

    /**
     * Destructor
     */
    virtual ~DeviceTransportIdHandler();

    /**
     * Test if a transport Id for device exists
     *
     * @param deviceName
     *            Device name
     *
     * @return true if a connection Id for the device exists
     */
    bool containsTransportIdForDevice(const std::string& deviceName) const;

    /**
     * Returns the first transport id for a given device name.
     *
     * @return Transport ID or null
     */
    TransportId getTransportIdForDevice(const std::string& deviceName) const;

    /**
     * Gets the list of all devices for a transport Id
     *
     * @param transportId
     *            Transport Id
     * @return List of devices reachable via this transport Id or empty list
     */
    std::vector<std::string> getDevicesForTransportId(const TransportId& transportId) const;

    /**
     * Removes a device if it is not a main device
     *
     * @param deviceName
     *            Device name
     *
     * @param transportId
     *            Transport identifier
     */
    void removeDevice(const std::string& deviceName, const TransportId& transportId);

    /**
     * Add a transportId for a device
     *
     * @param deviceName
     *            Device Name
     * @param transportId
     *            TransportId Id
     */
    void addDevice(const std::string& deviceName, const TransportId& transportId);

    /**
     * Adds a new main device
     *
     * @param deviceName
     *            Device name
     * @param transportId
     *            Transport identifier
     */
    void addDirectlyConnectedDevice(const std::string& deviceName, const TransportId& transportId);

    /**
     * Tests if device is a main device
     *
     * @param deviceName
     *            Device name
     * @return True if device is main device
     */
    bool isDirectlyConnectedDevice(const std::string& deviceName) const;

    /**
     * Returns the main device for the given transport Id
     *
     * @param transportId
     *            Transport Id
     * @return Main device name or null
     */
    std::string getDirectlyConnectedDevice(const TransportId& transportId) const;

    /**
     * Removes the transport Id and all devices associated to this connection
     * id. Connections to devices via different transport Id's are not touched.
     *
     * @param transportId
     *            Transport Id to be removed
     */
    void removeTransportId(const TransportId& transportId);

    /**
     * Gets the map of devices and their transport Id's
     *
     * @return Device to transport Id's map
     */
    std::map<std::string, std::vector<TransportId> > getDeviceTransportIds() const;

    /**
     * Returns the list of known transport Id's
     *
     * @return List of transport Id's
     */
    std::vector<TransportId> getTransportIds() const;

private:
    // Mapping from device name to transport Id's
    std::map<std::string, std::vector<TransportId> > mapDeviceToTransportIds;

    // Main device mapping Transport Id to main device
    std::map<std::string, std::string> mapTransportIdToMainDevice;

    mutable std::recursive_mutex mutex; // guard
};

//! typedef for non-const smart pointer type DeviceTransportIdHandler
typedef std::shared_ptr<DeviceTransportIdHandler> DeviceTransportIdHandlerPtr;

//! typedef for const type DeviceTransportIdHandler
typedef const DeviceTransportIdHandler DeviceTransportIdHandlerConst;

//! typedef for const smart pointer type DeviceTransportIdHandler
typedef std::shared_ptr<DeviceTransportIdHandlerConst> DeviceTransportIdHandlerConstPtr;

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_SRC_DEVICE_TRANSPORT_ID_HANDLER_H_ */
