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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "SmartDevicePriv.h"
#include <keo_spine/SmartDevice.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  documentation                                                                 *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine
{

SmartDevice::~SmartDevice()
{
    DEBUG_FUNC();
    delete p;
}

SmartDevice::SmartDevice(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription,
    DeviceCallbackInterface* deviceCallbackInterface)
    : SmartDevice(deviceDescription)
{
    DEBUG_FUNC();
    p->setDeviceCallbackListener(deviceCallbackInterface);
}

SmartDevice::SmartDevice(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription)
    : p(new SmartDevicePriv())
{
    DEBUG_FUNC();
    p->setDeviceDescription(deviceDescription);
}

SmartDevice::SmartDevice()
    : p(new SmartDevicePriv())
{
    DEBUG_FUNC();
}

void SmartDevice::setDeviceDescription(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription)
{
    DEBUG_FUNC();
    p->setDeviceDescription(deviceDescription);
}

const keo_datagram::NetworkManagementDeviceDescriptionData& SmartDevice::getDeviceDescription() const
{
    DEBUG_FUNC();
    return p->getDeviceDescription();
}

void SmartDevice::setDeviceCallbackListener(DeviceCallbackInterface* deviceCallbackInterface)
{
    p->setDeviceCallbackListener(deviceCallbackInterface);
}

void SmartDevice::setPrimaryDeviceInformationEntity(PrimaryDeviceInformationEntityPtr entity)
{
    p->setPrimaryDeviceInformationEntity(entity);
}

void SmartDevice::setUnhandledDatagramInterface(UnhandledDatagramInterface* unhandledDatagramHandler)
{
    p->setUnhandledDatagramInterface(unhandledDatagramHandler);
}

bool SmartDevice::initialize()
{
    return p->initialize();
}

void SmartDevice::close()
{
    p->close();
}

bool SmartDevice::addSubDevice(SmartDevicePtr subDevice)
{
    return p->addSubDevice(subDevice);
}

SmartDevicePtr SmartDevice::removeSubDevice(const std::string& deviceName)
{
    return p->removeSubDevice(deviceName);
}

std::vector<SmartDevicePtr> SmartDevice::getSubDevices() const
{
    return p->getSubDevices();
}

keo_datagram::DetailedDiscovery SmartDevice::getDetailedDiscovery() const
{
    keo_datagram::DetailedDiscoveryConstPtr ddPtr = p->getDetailedDiscovery();
    return keo_datagram::DetailedDiscovery(*ddPtr.get());
}

std::string SmartDevice::getDeviceName() const
{
    return p->getDeviceName();
}

bool SmartDevice::addEntity(EntityPtr entity)
{
    return p->addEntity(entity);
}

void SmartDevice::removeEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity)
{
    p->removeEntity(entity);
}

EntityPtr SmartDevice::getEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity) const
{
    return p->getEntity(entity);
}

std::vector<EntityPtr> SmartDevice::getEntities() const
{
    return p->getEntities();
}

TransportId SmartDevice::getTransportIdForDevice(const std::string& deviceName) const
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        return spt->getTransportIdForDevice(deviceName);
    }
    return "";
}

std::vector<std::string> SmartDevice::getDevicesForTransportId(const TransportId& transportId) const
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        return spt->getDevicesForTransportId(transportId);
    }
    return std::vector<std::string>();
}

std::map<std::string, std::vector<TransportId> > SmartDevice::getDeviceTransportIds() const
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        return spt->getDeviceTransportIds();
    }
    return std::map<std::string, std::vector<TransportId> >();
}

std::vector<TransportId> SmartDevice::getTransportIds() const
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        return spt->getTransportIds();
    }
    return std::vector<TransportId>();
}

void SmartDevice::addDeviceTransportId(const std::string& deviceName, const TransportId& transportId)
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        spt->addDeviceTransportId(deviceName, transportId);
    }
}

bool SmartDevice::isDirectlyConnectedDevice(const std::string& deviceName) const
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        return spt->isDirectlyConnectedDevice(deviceName);
    }
    return false;
}

void SmartDevice::removeDeviceTransportId(const std::string& deviceName, const TransportId& transportId)
{
    if (auto spt = p->getSpineLinkService().lock())
    {
        spt->removeDeviceTransportId(deviceName, transportId);
    }
}

bool SmartDevice::isInitialized() const
{
    return p->isInitialized();
}

bool SmartDevice::validate()
{
    return p->validate();
}

bool SmartDevice::sendDatagram(const DatagramRecord& datagramRecord)
{
    return p->sendSmartDeviceDatagram(datagramRecord);
}

SpineLinkReceiveServiceInterfaceWeakPtr SmartDevice::getSpineLinkReceiveService()
{
    return p->getSpineLinkService();
}

void SmartDevice::setSpineLinkSendService(SpineLinkSendServiceInterface* spineLinkSendService)
{
    p->setSpineLinkSendService(spineLinkSendService);
}

std::string SmartDevice::toString() const
{
    return p->toString();
}

} /* namespace keo_spine */
