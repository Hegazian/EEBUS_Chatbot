/*
 * DeviceCallbackListener.cpp
 *
 *  Created on: Jan 30, 2017
 *      Author: mesmer
 */

#include "DeviceCallbackListener.h"

DeviceCallbackListener::DeviceCallbackListener()
{
}

DeviceCallbackListener::~DeviceCallbackListener()
{
}

void DeviceCallbackListener::onConnect(const TransportId& transportId)
{
    connectedDevices.push_back(transportId);
}

void DeviceCallbackListener::onDisconnect(const TransportId& transportId)
{
    disconnectedDevices.push_back(transportId);
}

void DeviceCallbackListener::onDetailedDiscoveryFailed(const TransportId& transportId)
{
    (void)transportId;
}

void DeviceCallbackListener::onNewDevices(const std::list<std::string>& devices)
{
    (void)devices;
}

void DeviceCallbackListener::onRemovedDevices(const std::list<std::string>& devices)
{
    (void)devices;
}

void DeviceCallbackListener::onDetailedDiscovery(const std::string& deviceName,
                                                 const DetailedDiscovery& detailedDiscovery)
{
    (void)deviceName;
    (void)detailedDiscovery;
}
