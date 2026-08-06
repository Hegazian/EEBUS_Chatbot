/*
 *     Copyright KEO GmbH 2018 - All rights reserved!
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

#ifndef KEO_FRAMEWORK_SRC_SMARTDEVICE_H_
#define KEO_FRAMEWORK_SRC_SMARTDEVICE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                        *
 * ****************************************************************************** */
#include <keo_spine/DeviceCallbackInterface.h>
#include <keo_spine/PrimaryDeviceInformationEntity.h>
#include <keo_spine/SpineLinkDevice.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionData.h>
#include <keo_datagram/core/xs_types.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <string>
#include <vector>

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
 * This interface defines the last resort datagram record interface. This
 * interface can be used to retrieve all datagrams that are not handled inside
 * the device, either the destination is unknown, the datagram is faulty or
 * cannot be handled inside a featuer
 *
 * @author KEO GmbH 2017 All rights reserved !
 */

class UnhandledDatagramInterface
{

public:
    virtual ~UnhandledDatagramInterface()
    {
    }
    /**
     * Handle datagram record.
     *
     * The datagram record could not be processed inside the smart device.
     * Either the destination is unknown, the datagram itself is not supported
     * or the datagram is invalid.
     *
     * @param datagramRecord
     *            The datagram record
     * @param lastErrorValue
     *            SpineResultErrors as reason to call this function.
     * @return SpineResultErrors.OK if this handler handles the datagram,
     *         otherwise a error result is sent if appropriated.
     */
    virtual keo_datagram::xs_unsignedInt handleDatagram(
        const DatagramRecord& datagramRecord, keo_datagram::xs_unsignedInt lastErrorValue)
        = 0;
};

class SmartDevice;

//! typedef for non-const smart pointer type SmartDevice
typedef std::shared_ptr<SmartDevice> SmartDevicePtr;

//! typedef for const type SmartDevice
typedef const SmartDevice SmartDeviceConst;

//! typedef for const smart pointer type SmartDevice
typedef std::shared_ptr<SmartDeviceConst> SmartDeviceConstPtr;

/**
 * This represents a SPINE device and should be used by applications to model the desired functionality as devices,
 * entities and features.
 * The SPINE device model is a hierarchical structure of devices, entities and features.
 * - Features are children of entities
 * - Entities are children of devices
 *
 * You can have multiple devices in your application. One of these devices is linked to remote
 * devices using a transport connection via "SpineLink". This device is called "mainDevice".
 * Other devices are added to this device
 * and can communicate with remote devices using its transport connections. This devices are
 * called "subDevices" in this implementation.
 */
class SmartDevice : public SpineLinkDevice
{
public:
    /**
     * Constructor
     *
     * @param deviceDescription
     *            Description for this device
     * @param deviceCallbackHandler
     *            Interface to announce changes in connected devices
     */
    SmartDevice(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription,
        DeviceCallbackInterface* deviceCallbackHandler);

    /**
     * Constructor
     *
     * @param deviceDescription
     *            Description for this device
     */
    explicit SmartDevice(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription);

    /**
     * Constructor
     */
    SmartDevice();

    /**
     * Virtual destructor
     */
    virtual ~SmartDevice();

    /**
     *  Sets the network management device description data.
     *
     *  A valid device description data contains a device name (this is checked when
     *  this device is initialized).
     *
     * Attention: Calling this method will not update the device's detailed discovery. After adding device description
     * data to a device, {@link SmartDevice::initialize()} has to be called to create a new detailed discovery.
     *
     * @param deviceDescription Device description to set
     */
    void setDeviceDescription(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription);

    /**
     * Get this device's network management device description data.
     * @return the device description data
     */
    const keo_datagram::NetworkManagementDeviceDescriptionData& getDeviceDescription() const;

    /**
     * Sets a device callback listener
     *
     * @param deviceCallbackInterface
     *            Device callback interface
     */
    void setDeviceCallbackListener(DeviceCallbackInterface* deviceCallbackInterface);

    /**
     * Sets the mandatory primary device information entity.
     *
     * @param entity
     *            Primary device information entity
     */
    void setPrimaryDeviceInformationEntity(PrimaryDeviceInformationEntityPtr entity);

    /**
     * Sets the listener to handle erroneous or not handled datagrams.
     *
     * Set this listener to retrieve a callback before the device creates the
     * error result for the peer. The application can decide to handle the
     * datagram by itself or uses the default implementation by returning a
     * return value unequal 0.
     *
     * @param unhandledDatagramHandler
     *            Datagram listener
     */
    void setUnhandledDatagramInterface(UnhandledDatagramInterface* unhandledDatagramHandler);

    /**
     * Initialize the device. This will correctly set the addresses of all
     * entities and features added to this device and update the detailed
     * discovery of this device.
     *
     * After altering the device, e.g. adding/removing features, this function
     * shall be called to update the detailed discovery.
     *
     * If initialization of a device fails (signaled by this method returning false) and
     * the device is still used for communication, a std::logic_error is thrown. This
     * exception is not meant to be caught and handled, but to detect and fix this common
     * error more easily.
     *
     * Note that sub devices also have to be initialized.
     *
     * @return true, if successful
     *
     */
    bool initialize();

    /**
     * Closes the device and all sub-devices.
     *
     * All features receive the onClose() call.
     *
     */
    void close();

    /**
     * Add a (local) sub device to this device.
     *
     * Note that sub devices also have to be initialized.
     *
     * @param subDevice
     *            the sub device
     * @return true, if the device has been added
     */
    bool addSubDevice(SmartDevicePtr subDevice);

    /**
     * Remove a (local) sub device from this device.
     *
     * @param deviceName
     *            the name of the device to remove
     * @return the removed device, if no device was removed this returns null
     */
    SmartDevicePtr removeSubDevice(const std::string& deviceName);

    /**
     * Returns the list of 'sub'-devices of this Smart device.
     *
     * @return List of sub devices
     */
    std::vector<SmartDevicePtr> getSubDevices() const;

    /**
     * Returns the detailed discovery information of this device. The detailed
     * discovery information is only valid after calling {@see SmartDevice::initialize()}.
     *
     * @return Detailed discovery information
     */
    keo_datagram::DetailedDiscovery getDetailedDiscovery() const;

    /**
     * Returns the device name of this device. The device name is only set after
     * calling {@see SmartDevice::initialize()}.
     *
     * @return device name or empty string if the device is not initialized
     */
    std::string getDeviceName() const;

    /**
     * Add an entity with all its features to this device. Note, that for adding
     * a {@link keo_spine::PrimaryDeviceInformationEntity} to this device, the method
     * {@link SmartDevice#setPrimaryDeviceInformationEntity(PrimaryDeviceInformationEntity)}
     * has to be used.
     *
     * Attention: Calling this method will not update the device's detailed discovery. After adding entities to a
     * device, {@link SmartDevice::initialize()} has to be called to create a new detailed discovery.
     *
     * @param entity
     *            the entity to add
     * @return true, if the entity has been added
     */
    bool addEntity(EntityPtr entity);

    /**
     * Remove an entity with all its features.
     *
     * Attention: Calling this method will not update the device's detailed discovery. After removing entities to a
     * device, {@link SmartDevice::initialize()} has to be called to create a new detailed discovery.
     *
     * @param entity
     *            Entity to remove
     */
    void removeEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity);

    /**
     * Get entity class.
     *
     * Attention: The entity might be uninitialized and not present in the device's detailed discovery.
     *
     * @param entity
     *            Entity number of the entity class
     * @return Entity class if present
     */
    EntityPtr getEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity) const;

    /**
     * Get a list of all Entities added to this device.
     *
     * Attention: Some entities might be uninitialized and not present in the device's detailed discovery.
     *
     * Attention: This will also return Entities that are not reflected in this device's detailed discovery yet, when
     * {@see SmartDevice::initialize()} has not been called after the Entity has been added.
     */
    std::vector<EntityPtr> getEntities() const;

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
     * Gets the map of devices and their transport Id's
     *
     * @return Device to transport Id's map
     */
    std::map<std::string, std::vector<TransportId>> getDeviceTransportIds() const;

    /**
     * Returns the list of known transport identifiers.
     *
     * @return List of transport identifiers
     */
    std::vector<TransportId> getTransportIds() const;

    /**
     * Adds a device to the transport connection handling.
     *
     * Using this function will not notify the features. Use the primary node
     * management functions instead.
     *
     * It is not possible to add a device for a non existing transport id.
     *
     * @param deviceName
     *            Device name
     * @param transportId
     *            Transport identifier
     */
    void addDeviceTransportId(const std::string& deviceName, const TransportId& transportId);

    /**
     * Returns true if the device is direct connected to this device. A direct
     * connected device is the peer communication partner of a transport
     * connection.
     *
     * @param deviceName
     *            Device name
     * @return True if this is a direct peer of a transport connection.
     */
    bool isDirectlyConnectedDevice(const std::string& deviceName) const;

    /**
     * Remove a device from the transport connection mapping.
     *
     * It is not possible to remove the peer's main device.
     *
     * @param deviceName
     *            Device name
     * @param transportId
     *            Transport connection identifier
     */
    void removeDeviceTransportId(const std::string& deviceName, const TransportId& transportId);

    /**
     * Checks whether this device is initialized.
     * @return true, if the device is initialized
     */
    bool isInitialized() const;

    /**
     * Validate this SmartDevice. This ensures that the addresses are set
     * correctly in all entities that have been added to this device. Also, this
     * validates all entities, which in turn ensures that all features addresses
     * are set correctly.
     *
     * @return true, if this device has been validated successfully
     */
    bool validate();

    /**
     * Sends a datagram via this device's send service to a transport Id
     * specified in the datagram record.
     *
     * When using this method the caller is responsible for setting up a correct
     * device and transport identifiers.
     *
     * @param datagramRecord
     *            Datagarm and transport identifier.
     * @return True if successful
     */
    bool sendDatagram(const DatagramRecord& datagramRecord);

    /**
     * Returns spine link receive service.
     *
     * @return Spine link link receive service
     */
    SpineLinkReceiveServiceInterfaceWeakPtr getSpineLinkReceiveService();

    /**
     * Sets the spine links send service.
     *
     * @param spineLinkSendService
     *            Spine Links send service
     */
    void setSpineLinkSendService(SpineLinkSendServiceInterface* spineLinkSendService);

    /**
     * Creates a string representation of this device.
     * @return a string representation of this device
     */
    std::string toString() const;

private:
    class SmartDevicePriv;
    SmartDevicePriv* p;
};
// SmartDevice

/** @} */ //  end of group framework
} // namespace keo_spine

#endif /* KEO_FRAMEWORK_SRC_SMARTDEVICE_H_ */
