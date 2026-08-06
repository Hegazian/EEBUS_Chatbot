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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "SmartDevicePriv.h"
#include <TimeoutService.h>
#include <keo_datagram/core/DatagramParserException.h>
#include <keo_datagram/core/NetworkManagementDeviceDescriptionData.h>
#include <keo_datagram/core/SpineResultErrors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <sstream>

/* ****************************************************************************** *
 *  documentation                                                                 *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

// The maximum number of incoming datagrams of a transport connection that are kept in memory until a detailed discovery
// is received on that connection
const int BUFFER_DATAGRAMS_BEFORE_DETAILED_DISCOVERY = 100;

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine
{

SmartDevice::SmartDevicePriv::SmartDevicePriv()
    : deviceCallbackInterface(nullptr)
    , unhandledDatagramHandler(nullptr)
    , entityHandler(this)
    , subDeviceHandler(*this, mtx)
    , smartDeviceSendService(*this, mtx)
    , initialized(false)
{
    DEBUG_FUNC();
    spineLinkService = std::make_shared<SpineLinkService>(*this, mtx);
}

SmartDevice::SmartDevicePriv::~SmartDevicePriv()
{
    DEBUG_FUNC();
}

bool SmartDevice::SmartDevicePriv::initialize()
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    if (validate() && entityHandler.initialize(deviceDescription))
    {
        // Save the device name of this device
        keo_datagram::DetailedDiscoveryConstPtr dd = getDetailedDiscovery();
        if (dd)
        {
            deviceName = dd->getDeviceName();
        }
        LOG_INFO() << "Device initialized successfully";
        initialized = true;
    }
    else
    {
        initialized = false;
        LOG_ERROR() << "Device could not be initialized (device model invalid)";
    }
    return initialized;
}

std::string SmartDevice::SmartDevicePriv::getDeviceName() const
{
    return deviceName;
}

bool SmartDevice::SmartDevicePriv::addEntity(EntityPtr entity, bool isEntityZero)
{
    DEBUG_FUNC();
    if (!entity)
    {
        return false;
    }
    if (!isEntityZero && entity->getEntity() == (DeviceDefinition::EntityAddressZero.getEntity()))
    {
        // Make sure not to add a PrimaryDeviceInformation Entity using this method
        LOG_WARN() << "Cannot add " << entity->toString();
        return false;
    }

    entityHandler.addEntity(entity);

    LOG_INFO() << "Successfully added " << entity->toString() << " to " << this->toString();
    entity->setSendService(&smartDeviceSendService);
    return true;
}

bool SmartDevice::SmartDevicePriv::isInitialized() const
{
    return initialized;
}

bool SmartDevice::SmartDevicePriv::validate()
{
    DEBUG_FUNC();
    if (!deviceDescription.getDeviceAddressIsSet() || !deviceDescription.getDeviceAddress().getDeviceIsSet()
        || deviceDescription.getDeviceAddress().getDevice().empty())
    {
        LOG_ERROR() << "Incomplete device address in " << this->toString();
        return false;
    }

    return entityHandler.validate();
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId)
{
    DEBUG_FUNC();
    if (!transportId.empty() && !devices.empty())
    {
        spineLinkService->onNewDevices(devices, transportId);
        subDeviceHandler.onNewDevices(devices);

        if (deviceCallbackInterface != nullptr)
        {
            deviceCallbackInterface->onNewDevices(devices);
        }
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::onRemovedDevices(
    const std::vector<std::string>& devices, const TransportId& transportId)
{
    DEBUG_FUNC();
    if (!transportId.empty() && !devices.empty())
    {
        subDeviceHandler.onRemovedDevices(devices);
        spineLinkService->onRemovedDevices(devices, transportId);

        if (deviceCallbackInterface != nullptr)
        {
            deviceCallbackInterface->onRemovedDevices(devices);
        }
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    DEBUG_FUNC();
    subDeviceHandler.onDetailedDiscovery(deviceName, detailedDiscovery);

    if (deviceCallbackInterface != nullptr && !deviceName.empty())
    {
        deviceCallbackInterface->onDetailedDiscovery(deviceName, detailedDiscovery);
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    DEBUG_FUNC();
    subDeviceHandler.onDetailedDiscoveryPartial(deviceName, detailedDiscoveryPartial);

    if (deviceCallbackInterface != nullptr && !deviceName.empty())
    {
        deviceCallbackInterface->onDetailedDiscoveryPartial(deviceName, detailedDiscoveryPartial);
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::onUseCaseDiscovery(
    const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
{
    DEBUG_FUNC();

    subDeviceHandler.onUseCaseDiscovery(deviceName, useCaseDiscovery);

    if (deviceCallbackInterface != nullptr && !deviceName.empty())
    {
        deviceCallbackInterface->onUseCaseDiscovery(deviceName, useCaseDiscovery);
    }
}

// SendServiceInterface
std::string SmartDevice::SmartDevicePriv::SmartDeviceSendService::getDeviceName() const
{
    DEBUG_FUNC();
    return smartDevice.getDeviceName();
}

// SendServiceInterface
bool SmartDevice::SmartDevicePriv::SmartDeviceSendService::sendDatagram(DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    return sendPendingDatagram(datagramRecord, 0) != 0;
}

// SendServiceInterface
keo_datagram::xs_unsignedLong SmartDevice::SmartDevicePriv::SmartDeviceSendService::sendPendingDatagram(
    DatagramRecord& datagramRecord)
{
    long timeout
        = smartDevice.entityHandler.getRemoteFeatureTimeout(datagramRecord.getDatagram().getDestinationAddress());
    return sendPendingDatagram(datagramRecord, timeout == 0 ? DeviceDefinition::DatagramTimeoutDelay : timeout);
}

// SendServiceInterface
keo_datagram::xs_unsignedLong SmartDevice::SmartDevicePriv::SmartDeviceSendService::sendPendingDatagram(
    DatagramRecord& datagramRecord, long timeout)
{
    DEBUG_FUNC();
    if (!smartDevice.spineLinkService->isSpineLinkSendServiceSet())
    {
        LOG_ERROR() << "Send service interface not set in " << smartDevice.toString() << ". Cannot send datagram.";
        return 0;
    }

    if (!canSendDatagram(datagramRecord) || !setTransportId(datagramRecord))
    {
        return 0;
    }

    keo_datagram::xs_unsignedLong msgCounter = datagramRecord.getDatagram().getMsgCounter();

    if (timeout > 0)
    {
        addAckRequest(datagramRecord);

        std::lock_guard<std::recursive_mutex> locker(mtx);
        const TransportId& transportId = datagramRecord.getTransportId();
        pendingTimeoutsByMessageCounter[msgCounter]
            = std::make_pair(datagramRecord.getDatagram().getSourceAddress(), std::string(transportId));

        timeoutService.addTimeout(msgCounter, timeout);
    }

    DEBUG_INFO() << "Send datagram from " << datagramRecord.getDatagram().getSourceAddress().toString() << " to "
                 << datagramRecord.getDatagram().getDestinationAddress().toString() << " via transport Id "
                 << datagramRecord.getTransportId();

    if (!smartDevice.spineLinkService->sendDatagramRecordToTransportConnection(datagramRecord))
    {
        removeTimeoutByMsgCounter(msgCounter);
    }

    return msgCounter;
}

bool SmartDevice::SmartDevicePriv::SmartDeviceSendService::setTransportId(DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    keo_datagram::FeatureAddress destination = datagramRecord.getDatagram().getDestinationAddress();

    if (datagramRecord.getTransportId().empty())
    {
        if (!smartDevice.spineLinkService->containsTransportIdForDevice(destination.getDevice()))
        {
            LOG_ERROR() << "Cannot resolve transport ID for destination " << destination.getDevice();
            return false;
        }
        TransportId transportId = smartDevice.spineLinkService->getTransportIdForDevice(destination.getDevice());
        datagramRecord.setTransportId(transportId);
    }
    return true;
}

bool SmartDevice::SmartDevicePriv::SmartDeviceSendService::canSendDatagram(const DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    if (datagramRecord.getDatagram().isEmpty())
    {
        LOG_WARN() << "Cannot send empty datagram";
        return false;
    }

    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    if (!datagram.isHeaderValid())
    {
        LOG_WARN() << "Cannot send datagram with invalid header: " << datagramRecord.toJson();
        return false;
    }

    return true;
}

void SmartDevice::SmartDevicePriv::SmartDeviceSendService::addAckRequest(DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    bool ack = datagramRecord.getDatagram().getHeader().getAckRequest();
    if (!ack)
    {
        datagramRecord.getDatagram().getHeader().setAckRequest(true);
    }
}

// SendServiceInterface
bool SmartDevice::SmartDevicePriv::SmartDeviceSendService::removeTimeoutByMsgCounter(
    keo_datagram::xs_unsignedLong msgCounter)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = pendingTimeoutsByMessageCounter.find(msgCounter);
    if (iter != pendingTimeoutsByMessageCounter.end())
    {
        timeoutService.removeTimeout(msgCounter);
        pendingTimeoutsByMessageCounter.erase(iter);
        return true;
    }
    return false;
}

// TimeoutServiceInterface
void SmartDevice::SmartDevicePriv::SmartDeviceSendService::timeout(keo_datagram::xs_unsignedLong msgCounter)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = pendingTimeoutsByMessageCounter.find(msgCounter);
    if (iter != pendingTimeoutsByMessageCounter.end())
    {
        keo_datagram::FeatureAddress source = iter->second.first;
        pendingTimeoutsByMessageCounter.erase(iter);
        smartDevice.entityHandler.handleTimeout(source, msgCounter);
    }
}

// SendServiceInterface
bool SmartDevice::SmartDevicePriv::SmartDeviceSendService::isConnected(const std::string& deviceName) const
{
    DEBUG_FUNC();
    return smartDevice.spineLinkService->containsTransportIdForDevice(deviceName);
}

SmartDevice::SmartDevicePriv::SubDeviceHandler::~SubDeviceHandler()
{
    DEBUG_FUNC();
    subDevices.clear();
}

void SmartDevice::SmartDevicePriv::SubDeviceHandler::close()
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = subDevices.begin();
    while (iter != subDevices.end())
    {
        iter->second->close();
        ++iter;
    }
}

bool SmartDevice::SmartDevicePriv::SubDeviceHandler::addSubDevice(SmartDevicePtr subDevice)
{
    DEBUG_FUNC();

    bool retval = false;
    std::lock_guard<std::recursive_mutex> locker(mtx);

    std::string subDeviceName = subDevice->getDeviceName();
    auto iter = subDevices.find(subDeviceName);
    if (iter == subDevices.end())
    {
        keo_datagram::NetworkManagementDeviceDescriptionData subDeviceDescription
            = subDevice->getDetailedDiscovery().getDeviceDescription();
        keo_datagram::NetworkManagementDeviceDescriptionData descriptionData;
        descriptionData.setDeviceAddress(subDeviceDescription.getDeviceAddress());
        if (subDeviceDescription.getNetworkFeatureSetIsSet())
        {
            descriptionData.setNetworkFeatureSet(subDeviceDescription.getNetworkFeatureSet());
        }
        if (subDeviceDescription.getLabelIsSet())
        {
            descriptionData.setLabel(subDeviceDescription.getLabel());
        }

        std::vector<keo_datagram::NetworkManagementDeviceDescriptionData> deviceDataList;
        deviceDataList.push_back(descriptionData);
        if (smartDevice.entityHandler.addSubDevice(deviceDataList))
        {
            subDevice->setSpineLinkSendService(this);
            subDevices.insert(std::make_pair(subDeviceName, subDevice));
            subDevice->p->spineLinkService->addDirectlyConnectedDevice(
                smartDevice.getDeviceName(), smartDevice.getDeviceName());
            retval = true;
            LOG_INFO() << "Successfully added " << subDevice->toString() << " to " << smartDevice.toString();
        }
    }
    else
    {
        DEBUG_INFO() << "Cannot add " << subDevice->toString() << " to " << smartDevice.toString()
                     << " (already exists)";
    }

    return retval;
}

SmartDevicePtr SmartDevice::SmartDevicePriv::SubDeviceHandler::removeSubDevice(const std::string& deviceName)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);

    SmartDevicePtr device;

    auto iter = subDevices.find(deviceName);
    if (iter != subDevices.end())
    {
        std::vector<std::string> deviceNameList;
        deviceNameList.push_back(deviceName);
        if (smartDevice.entityHandler.removeSubDevice(deviceNameList))
        {
            device = iter->second;
            // TODO remove connection from sub device
            subDevices.erase(iter);
        }
    }

    return device;
}

std::vector<SmartDevicePtr> SmartDevice::SmartDevicePriv::SubDeviceHandler::getSubDevices() const
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    std::vector<SmartDevicePtr> deviceList;

    auto iter = subDevices.begin();
    while (iter != subDevices.end())
    {
        deviceList.push_back(iter->second);
        ++iter;
    }

    return deviceList;
}

void SmartDevice::SmartDevicePriv::SubDeviceHandler::onNewDevices(const std::vector<std::string>& devices)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = subDevices.begin();
    while (iter != subDevices.end())
    {
        iter->second->p->entityHandler.onNewDevices(devices, smartDevice.getDeviceName());
        ++iter;
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::SubDeviceHandler::onRemovedDevices(const std::vector<std::string>& devices)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = subDevices.begin();
    while (iter != subDevices.end())
    {
        iter->second->p->entityHandler.onRemovedDevices(devices, smartDevice.getDeviceName());
        ++iter;
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::SubDeviceHandler::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = subDevices.begin();
    while (iter != subDevices.end())
    {
        iter->second->p->entityHandler.onDetailedDiscovery(deviceName, detailedDiscovery);
        ++iter;
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::SubDeviceHandler::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = subDevices.begin();
    while (iter != subDevices.end())
    {
        iter->second->p->entityHandler.onDetailedDiscoveryPartial(deviceName, detailedDiscoveryPartial);
        ++iter;
    }
}

// EntityHandlerInterface
void SmartDevice::SmartDevicePriv::SubDeviceHandler::onUseCaseDiscovery(
    const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    for (auto const& subDevice : subDevices)
    {
        subDevice.second->p->entityHandler.onUseCaseDiscovery(deviceName, useCaseDiscovery);
    }
}

keo_datagram::xs_unsignedInt SmartDevice::SmartDevicePriv::SubDeviceHandler::onDatagram(DatagramRecord& datagramRecord)
{
    DEBUG_INFO() << smartDevice.getDeviceName() << " SmartDevice::SmartDevicePriv::SubDeviceHandler::onDatagram()";

    std::lock_guard<std::recursive_mutex> locker(mtx);
    auto iter = subDevices.find(datagramRecord.getDestinationDevice());
    if (iter != subDevices.end())
    {
        datagramRecord.setTransportId(smartDevice.getDeviceName());
        if (auto spt = iter->second->getSpineLinkReceiveService().lock())
        {
            spt->onDatagram(datagramRecord);
        }
        return keo_datagram::SpineResultErrors::OK;
    }
    return keo_datagram::SpineResultErrors::DESTINATION_UNKNOWN;
}

// SpineLinkSendServiceInterface
bool SmartDevice::SmartDevicePriv::SubDeviceHandler::sendDatagram(const DatagramRecord& datagramRecord_)
{
    // TODO const_cast ok?
    DatagramRecord datagramRecord = const_cast<DatagramRecord&>(datagramRecord_);
    DEBUG_INFO() << smartDevice.getDeviceName() << " SmartDevice::SmartDevicePriv::SubDeviceHandler::sendDatagram()";

    keo_datagram::FeatureAddress destination = datagramRecord.getDatagram().getDestinationAddress();

    if (!destination.getDeviceIsSet() || destination.getDevice().empty())
    {
        LOG_ERROR() << "Try to send datagram from via " << this->smartDevice.toString()
                    << ", but destination is not set!";
        return false;
    }

    if (!smartDevice.spineLinkService->containsTransportIdForDevice(destination.getDevice()))
    {
        LOG_ERROR() << "Try to send datagram from via " << this->smartDevice.toString() << ", but destination "
                    << destination.getDevice() << " is unknown!";
        return false;
    }

    TransportId transportId = smartDevice.spineLinkService->getTransportIdForDevice(destination.getDevice());
    datagramRecord.setTransportId(transportId);

    return smartDevice.spineLinkService->sendDatagramRecordToTransportConnection(datagramRecord);
}

bool SmartDevice::SmartDevicePriv::SpineLinkService::sendDatagramRecordToTransportConnection(
    const DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();

    smartDevice.ensureInitializedDevice();

    if (isSpineLinkSendServiceSet() && datagramRecord.getDatagram().isPayloadValid()
        && datagramRecord.getDatagram().isHeaderValid())
    {
        LOG_INFO() << smartDevice.getDeviceName() << " Sending datagram from " << datagramRecord.getSourceDevice()
                   << " to " << datagramRecord.getDestinationDevice() << " via " << datagramRecord.getTransportId();
        return spineLinkSendService->sendDatagram(datagramRecord);
    }
    return false;
}

void SmartDevice::SmartDevicePriv::SpineLinkService::addDirectlyConnectedDevice(
    const std::string& deviceName, const std::string& transportId)
{
    DEBUG_FUNC();
    deviceTransportIdHandler.addDirectlyConnectedDevice(deviceName, transportId);
}

bool SmartDevice::SmartDevicePriv::SpineLinkService::containsTransportIdForDevice(const std::string& deviceName) const
{
    DEBUG_FUNC();
    return !getTransportIdForDevice(deviceName).empty();
}

TransportId SmartDevice::SmartDevicePriv::SpineLinkService::getTransportIdForDevice(const std::string& deviceName) const
{
    DEBUG_FUNC();
    return deviceTransportIdHandler.getTransportIdForDevice(deviceName);
}

std::vector<std::string> SmartDevice::SmartDevicePriv::SpineLinkService::getDevicesForTransportId(
    const TransportId& transportId) const
{
    DEBUG_FUNC();
    return deviceTransportIdHandler.getDevicesForTransportId(transportId);
}

std::map<std::string, std::vector<TransportId>>
SmartDevice::SmartDevicePriv::SpineLinkService::getDeviceTransportIds() const
{
    DEBUG_FUNC();
    return deviceTransportIdHandler.getDeviceTransportIds();
}

std::vector<TransportId> SmartDevice::SmartDevicePriv::SpineLinkService::getTransportIds() const
{
    DEBUG_FUNC();
    return deviceTransportIdHandler.getTransportIds();
}

void SmartDevice::SmartDevicePriv::SpineLinkService::addDeviceTransportId(
    const std::string& deviceName, const TransportId& transportId)
{
    DEBUG_FUNC();
    deviceTransportIdHandler.addDevice(deviceName, transportId);
}

bool SmartDevice::SmartDevicePriv::SpineLinkService::isDirectlyConnectedDevice(const std::string& deviceName) const
{
    DEBUG_FUNC();
    return deviceTransportIdHandler.isDirectlyConnectedDevice(deviceName);
}

void SmartDevice::SmartDevicePriv::SpineLinkService::removeDeviceTransportId(
    const std::string& deviceName, const TransportId& transportId)
{
    DEBUG_FUNC();
    deviceTransportIdHandler.removeDevice(deviceName, transportId);
}

void SmartDevice::SmartDevicePriv::SpineLinkService::onNewDevices(
    const std::vector<std::string>& devices, const TransportId& transportId)
{
    DEBUG_FUNC();
    auto iter = devices.begin();
    while (iter != devices.end())
    {
        deviceTransportIdHandler.addDevice(*iter, transportId);
        ++iter;
    }
}

void SmartDevice::SmartDevicePriv::SpineLinkService::onRemovedDevices(
    const std::vector<std::string>& devices, const TransportId& transportId)
{
    DEBUG_FUNC();
    // remove devices from transport link mapping; main devices will not be removed
    auto iter = devices.begin();
    while (iter != devices.end())
    {
        deviceTransportIdHandler.removeDevice(*iter, transportId);
        ++iter;
    }
}

// SpineLinkReceiveServiceInterface
void SmartDevice::SmartDevicePriv::SpineLinkService::addConnection(TransportId transportId)
{
    DEBUG_FUNC();

    smartDevice.ensureInitializedDevice();

    DEBUG_INFO() << "Requesting detailed discovery on new connection " << transportId;
    if (nullptr == spineLinkSendService)
    {
        LOG_ERROR() << "Cannot send datagram (no send service set)";
        if (nullptr != smartDevice.deviceCallbackInterface)
        {
            smartDevice.deviceCallbackInterface->onDetailedDiscoveryFailed(transportId);
        }
        return;
    }

    if (nullptr != smartDevice.deviceCallbackInterface)
    {
        smartDevice.deviceCallbackInterface->onConnected(transportId);
    }

    // Request detailed discovery from remote main device
    keo_datagram::Datagram datagram
        = PrimaryNodeManagementFeature::createNodeManagementDetailedDiscoveryRequest(smartDevice.getDeviceName(), "");

    mtx.lock();
    pendingDetailedDiscovery.insert(std::make_pair(datagram.getMsgCounter(), transportId));
    mtx.unlock();

    if (sendDatagramRecordToTransportConnection(DatagramRecord(datagram, transportId)))
    {
        timeoutService.addTimeout(datagram.getMsgCounter(), DeviceDefinition::DatagramTimeoutDelay);
    }
    else
    {
        mtx.lock();
        pendingDetailedDiscovery.erase(datagram.getMsgCounter());
        mtx.unlock();

        if (nullptr != smartDevice.deviceCallbackInterface)
        {
            smartDevice.deviceCallbackInterface->onDetailedDiscoveryFailed(transportId);
        }
    }
}

// SpineLinkReceiveServiceInterface
void SmartDevice::SmartDevicePriv::SpineLinkService::removeConnection(TransportId transportId)
{
    DEBUG_FUNC();
    DEBUG_INFO() << "Connection removed: Transport Id " << transportId;
    int canceledTimeouts = 0;
    {
        // Cancel all pending detailed discovery read timeouts for that connection
        std::lock_guard<std::recursive_mutex> locker(mtx);
        auto ddIter = pendingDetailedDiscovery.begin();
        while (ddIter != pendingDetailedDiscovery.end())
        {
            if (ddIter->second == transportId)
            {
                timeoutService.removeTimeout(ddIter->first);
                pendingDetailedDiscovery.erase(ddIter);
                canceledTimeouts++;
                break;
            }
            ++ddIter;
        }
    }

    {
        // Cancel all pending datagram timeouts for that connection
        std::lock_guard<std::recursive_mutex> locker(smartDevice.smartDeviceSendService.mtx);
        auto timeoutIter = smartDevice.smartDeviceSendService.pendingTimeoutsByMessageCounter.begin();
        while (timeoutIter != smartDevice.smartDeviceSendService.pendingTimeoutsByMessageCounter.end())
        {
            const TransportId& timeoutTransportId = timeoutIter->second.second;
            if (transportId == timeoutTransportId)
            {
                const keo_datagram::xs_unsignedLong msgCounter = timeoutIter->first;
                smartDevice.smartDeviceSendService.timeoutService.removeTimeout(msgCounter);
                timeoutIter = smartDevice.smartDeviceSendService.pendingTimeoutsByMessageCounter.erase(timeoutIter);
                canceledTimeouts++;
            }
            else
            {
                ++timeoutIter;
            }
        }
        LOG_TRACE() << "Canceled " << canceledTimeouts << " timeouts on connection " << transportId;
    }

    // Get all connected devices and announce removal
    std::vector<std::string> devices = getDevicesForTransportId(transportId);

    if (!devices.empty())
    {
        smartDevice.entityHandler.onRemovedDevices(devices, transportId);
    }
    deviceTransportIdHandler.removeTransportId(transportId);

    if (0 != smartDevice.deviceCallbackInterface)
    {
        smartDevice.deviceCallbackInterface->onDisconnect(transportId);
    }
}

void SmartDevice::SmartDevicePriv::ensureInitializedDevice() const
{
    if (!isInitialized())
    {
        throw std::logic_error("Device is not initialized. Make sure SmartDevice::initialize() returns true.");
    }
}

// SpineLinkReceiveServiceInterface
void SmartDevice::SmartDevicePriv::SpineLinkService::onDatagram(DatagramRecord& record)
{
    smartDevice.ensureInitializedDevice();

    const TransportId& transportId = record.getTransportId();

    DEBUG_INFO() << "Received datagram from " << record.getSourceDevice() << " for " << record.getDestinationDevice()
                 << " via transport Id " << transportId << ": " << record.toJson();

    if (!record.getDatagram().isEmpty() && record.getDatagram().isHeaderValid())
    {
        keo_datagram::Datagram& datagram = record.getDatagram();

        try
        {
            datagram.parsePayloadThrows();
        }
        catch (const keo_datagram::DatagramParserException& e)
        {
            LOG_ERROR() << "Could not parse payload of datagram: " << e.what();
            handleParseError(record);
            return;
        }

        {
            std::lock_guard<std::recursive_mutex> locker(mtx);

            if (!pendingDetailedDiscovery.empty() && datagram.isReply()
                && datagram.getCmdDataType()
                    == keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE
                && pendingDetailedDiscovery.find(datagram.getMsgCounterReference()) != pendingDetailedDiscovery.end()
                && handleNodeManagementDetailedDiscoveryReply(record))
            {
                // Datagram is a reply to initial detailed discovery read
                return;
            }
            else if (!pendingDetailedDiscovery.empty() && !datagram.isRead()
                && datagram.getCmdDataType()
                    != keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE)
            {
                // Datagram is not an initial detailed discovery read
                for (auto pendingDDReminder : pendingDetailedDiscovery)
                {
                    if (pendingDDReminder.second == transportId)
                    {
                        // The detailed discovery on that transport connection is still pending
                        if (bufferedDatagrams[transportId].size() < BUFFER_DATAGRAMS_BEFORE_DETAILED_DISCOVERY)
                        {
                            DEBUG_INFO() << "Buffering datagram on transport connection" << transportId
                                         << " because no detailed discovery has been received on that connection yet";
                            bufferedDatagrams[transportId].push_back(record);
                            return;
                        }
                        else
                        {
                            DEBUG_INFO() << "Not buffering datagram because the maximum amount of datagrams before "
                                            "detailed discovery has already been received on this connection";
                        }
                    }
                }
            }

            // check if datagram is from a simple device (device name is not set)
            if (!datagram.getSourceAddress().getDeviceIsSet() || !datagram.getDestinationAddress().getDeviceIsSet())
            {
                rewriteDatagramHeaderAddress(datagram, transportId);
            }

            std::string const& sourceDevice = datagram.getSourceAddress().getDevice();
            // check if device is known for address translation
            if (!deviceTransportIdHandler.containsTransportIdForDevice(sourceDevice))
            {
                if (!deviceTransportIdHandler.getDevicesForTransportId(transportId).empty())
                {
                    LOG_INFO() << smartDevice.getDeviceName() << " Add destination " << sourceDevice
                               << " via transport Id " << transportId << " to address table.";
                    // Add transport Id mapping
                    deviceTransportIdHandler.addDevice(sourceDevice, transportId);
                }
                else
                {
                    LOG_INFO() << smartDevice.getDeviceName() << " Received datagram " << sourceDevice
                               << " via transport Id " << transportId
                               << ". Detailed Discovery reply not processed yet.";
                }
            }
        }

        // distribute datagram
        distributeDatagram(record);
    }
}

void SmartDevice::SmartDevicePriv::SpineLinkService::distributeDatagram(const DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    class DatagramProcessor : public keo_tool::KEJobRunnerJob
    {
    private:
        DatagramRecord datagramRecord;
        UnhandledDatagramInterface* unhandledDatagramHandler;
        SpineLinkService& spineLinkService;
        EntityHandler& entityHandler;
        SubDeviceHandler& subDeviceHandler;
        std::string deviceName;

    public:
        DatagramProcessor(const DatagramRecord& datagramRecord, UnhandledDatagramInterface* unhandledDatagramHandler,
            SpineLinkService& spineLinkService, EntityHandler& entityHandler, SubDeviceHandler& subDeviceHandler,
            const std::string& deviceName)
            : datagramRecord(datagramRecord)
            , unhandledDatagramHandler(unhandledDatagramHandler)
            , spineLinkService(spineLinkService)
            , entityHandler(entityHandler)
            , subDeviceHandler(subDeviceHandler)
            , deviceName(deviceName)
        {
        }

    private:
        virtual void run()
        {
            std::lock_guard<std::recursive_mutex> locker(spineLinkService.mtx);
            std::string destination = datagramRecord.getDestinationDevice();
            keo_datagram::xs_unsignedInt errorValue = keo_datagram::SpineResultErrors::DESTINATION_UNKNOWN;

            if (destination.empty() || destination == deviceName)
            {
                const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
                if (datagram.getHeader().getMsgCounterReferenceIsSet())
                {
                    // Deliver the datagram to the entity/feature
                    errorValue = entityHandler.handleDatagramResponse(datagramRecord, datagram.getDestinationAddress());
                }
                else
                {
                    errorValue = entityHandler.handleDatagram(datagramRecord, datagram.getDestinationAddress());
                }
            }
            else
            {
                errorValue = subDeviceHandler.onDatagram(datagramRecord);
            }

            if (keo_datagram::SpineResultErrors::OK != errorValue && unhandledDatagramHandler != nullptr)
            {
                errorValue = unhandledDatagramHandler->handleDatagram(datagramRecord, errorValue);
            }

            sendResultIfAppropriate(datagramRecord, errorValue);
        }

        void sendResultIfAppropriate(const DatagramRecord& datagramRecord, keo_datagram::xs_unsignedInt errorValue)
        {
            if (keo_datagram::SpineResultErrors::OK != errorValue && !datagramRecord.getDatagram().isResult()
                && !datagramRecord.getDatagram().isReply())
            {
                keo_datagram::Datagram result = datagramRecord.getDatagram().createResult(errorValue);
                if (result.getSourceAddress().getDevice() != deviceName)
                {
                    // Datagram::createResult() simply swaps source and destination address. That is okay in most cases.
                    // It is not okay when the initial datagram was addressed to an unknown device. In those cases we
                    // need to overwrite the source address set by Datagram::createResult().
                    keo_datagram::FeatureAddress fixedSourceAddress(result.getHeader().getAddressSource());
                    fixedSourceAddress.setDevice(deviceName);
                    keo_datagram::Header fixedHeader(result.getHeader());
                    fixedHeader.setAddressSource(fixedSourceAddress);
                    result.setHeader(fixedHeader);
                }
                spineLinkService.sendDatagramRecordToTransportConnection(
                    DatagramRecord(result, datagramRecord.getTransportId()));
            }
        }
    };

    jobRunner->addJob(new DatagramProcessor(datagramRecord, smartDevice.unhandledDatagramHandler, *this,
        smartDevice.entityHandler, smartDevice.subDeviceHandler, smartDevice.getDeviceName()));
}

void SmartDevice::SmartDevicePriv::SpineLinkService::handleParseError(const DatagramRecord& record)
{
    DEBUG_FUNC();
    keo_datagram::xs_unsignedInt errorValue = keo_datagram::SpineResultErrors::COMMAND_REJECTED;

    if (smartDevice.unhandledDatagramHandler != 0)
    {
        errorValue = smartDevice.unhandledDatagramHandler->handleDatagram(record, errorValue);
    }

    if (keo_datagram::SpineResultErrors::OK != errorValue)
    {
        sendDatagramRecordToTransportConnection(
            DatagramRecord(record.getDatagram().createResult(errorValue), record.getTransportId()));
    }
}

void SmartDevice::SmartDevicePriv::SpineLinkService::rewriteDatagramHeaderAddress(
    keo_datagram::Datagram& datagram, const TransportId& transportId)
{
    DEBUG_FUNC();
    if (!datagram.getSourceAddress().getDeviceIsSet())
    {
        DEBUG_INFO() << "Received datagram without device set in source address. Trying to complete header... ";

        // Source address is not set. Try to get the device name from device link handler and
        // manipulate header to set source. This only happens if the sender is a SimpleDevice.
        std::vector<std::string> devices = deviceTransportIdHandler.getDevicesForTransportId(transportId);

        // expect exactly one device for this transport Id
        if (devices.size() == 1)
        {
            keo_datagram::FeatureAddress source = datagram.getSourceAddress();
            source.setDevice(devices.front());
            datagram.setSourceAddress(source);
        }
        else
        {
            std::string deviceName = deviceTransportIdHandler.getDirectlyConnectedDevice(transportId);
            LOG_WARN() << "Device not set in source address and more than one device reachable via transport id "
                       << transportId << ". Setting source device name to " << deviceName;
            keo_datagram::FeatureAddress source = datagram.getSourceAddress();
            source.setDevice(deviceName);
            datagram.setSourceAddress(source);
        }
    }
    if (!datagram.getDestinationAddress().getDeviceIsSet())
    {
        // Destination address (this device) is not set. This only happens if this device is a SimpleDevice or
        // during initial detailed discovery request
        keo_datagram::FeatureAddress destination = datagram.getDestinationAddress();
        destination.setDevice(smartDevice.getDeviceName());
        datagram.setDestinationAddress(destination);
    }
}

bool SmartDevice::SmartDevicePriv::SpineLinkService::handleNodeManagementDetailedDiscoveryReply(
    const DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    timeoutService.removeTimeout(datagram.getMsgCounterReference());
    keo_datagram::DetailedDiscovery detailedDiscovery;

    detailedDiscovery.setDetailedDiscoveryData(
        *((keo_datagram::NodeManagementDetailedDiscoveryData*)datagram.getCmdData().get()));

    DEBUG_FUNC();

    const TransportId& transportId = datagramRecord.getTransportId();

    auto iter = pendingDetailedDiscovery.find(datagram.getMsgCounterReference());
    if (iter != pendingDetailedDiscovery.end())
    {
        pendingDetailedDiscovery.erase(iter);
    }

    if (!detailedDiscovery.getDeviceName().empty())
    {
        deviceTransportIdHandler.addDirectlyConnectedDevice(detailedDiscovery.getDeviceName(), transportId);
        std::vector<std::string> devices;
        devices.push_back(detailedDiscovery.getDeviceName());
        smartDevice.entityHandler.onNewDevices(devices, transportId);
        smartDevice.entityHandler.onDetailedDiscovery(detailedDiscovery.getDeviceName(), detailedDiscovery);

        if (smartDevice.spineLinkService->bufferedDatagrams.find(transportId)
            != smartDevice.spineLinkService->bufferedDatagrams.end())
        {
            // Deliver buffered datagrams now
            for (auto& bufferedDatagramRecord : smartDevice.spineLinkService->bufferedDatagrams[transportId])
            {
                DEBUG_INFO() << "Delivering buffered datagram on transport connection" << transportId;
                smartDevice.spineLinkService->onDatagram(bufferedDatagramRecord);
            }
            smartDevice.spineLinkService->bufferedDatagrams.erase(transportId);
        }
    }
    else
    {
        LOG_WARN() << "Received invalid detailed discovery from " << datagramRecord.getSourceDevice();
        if (smartDevice.deviceCallbackInterface != 0)
        {
            smartDevice.deviceCallbackInterface->onDetailedDiscoveryFailed(transportId);
        }
    }

    DEBUG_FUNC();

    return true;
}

void SmartDevice::SmartDevicePriv::SpineLinkService::timeout(keo_datagram::xs_unsignedLong msgCounter)
{
    DEBUG_FUNC();
    TransportId transportId;

    {
        std::lock_guard<std::recursive_mutex> locker(mtx);

        auto iter = pendingDetailedDiscovery.find(msgCounter);
        if (iter != pendingDetailedDiscovery.end())
        {
            transportId = iter->second;
            pendingDetailedDiscovery.erase(iter);
        }
    }

    if (!transportId.empty() && smartDevice.deviceCallbackInterface != 0)
    {
        smartDevice.deviceCallbackInterface->onDetailedDiscoveryFailed(transportId);
    }
}

std::string SmartDevice::SmartDevicePriv::toString() const
{
    // Example String: "Device d:_n:TestDevice (Generic)"
    std::stringstream ss;
    ss << "Device";
    if (deviceDescription.getDeviceAddressIsSet())
    {
        ss << " " << deviceDescription.getDeviceAddress().getDevice();
    }
    if (deviceDescription.getDeviceTypeIsSet())
    {
        ss << " (" << deviceDescription.getDeviceType().toString() << ")";
    }
    return ss.str();
}

} /* namespace keo_spine */
