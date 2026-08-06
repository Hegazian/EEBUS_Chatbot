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
/**
 *     @brief      ClientFeature class definition
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/******************************************************************************* *
 * project header files                                                          *
 ******************************************************************************* */

#include "DeviceTransportIdHandler.h"

/******************************************************************************* *
 * KEO header files                                                              *
 ******************************************************************************* */

#include <keo_util/KELogging.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

#include <assert.h>

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

DeviceTransportIdHandler::DeviceTransportIdHandler()
    : mapDeviceToTransportIds()
    , mapTransportIdToMainDevice()
    , mutex()
{
}

DeviceTransportIdHandler::~DeviceTransportIdHandler()
{
}

bool DeviceTransportIdHandler::containsTransportIdForDevice(const std::string& deviceName) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);
    return mapDeviceToTransportIds.find(deviceName) != mapDeviceToTransportIds.end();
}

std::string DeviceTransportIdHandler::getTransportIdForDevice(const std::string& deviceName) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapDeviceToTransportIds.find(deviceName);
    if (iter != mapDeviceToTransportIds.end())
    {
        if (!iter->second.empty())
        {
            return iter->second.front();
        }
    }
    return std::string();
}

std::vector<std::string> DeviceTransportIdHandler::getDevicesForTransportId(const TransportId& transportId) const
{
    std::vector<std::string> retval;
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapDeviceToTransportIds.begin();
    auto iterEnd = mapDeviceToTransportIds.end();

    for (; iter != iterEnd; ++iter)
    {
        auto iterList = iter->second.begin();
        auto iterListEnd = iter->second.end();
        for (; iterList != iterListEnd; ++iterList)
        {
            if (iterList->compare(transportId) == 0)
            {
                // Add map key to return list
                retval.push_back(iter->first);
                break;
            }
        }
    }
    return retval;
}

void DeviceTransportIdHandler::removeDevice(const std::string& deviceName, const TransportId& transportId)
{
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapTransportIdToMainDevice.find(transportId);
    if (iter != mapTransportIdToMainDevice.end())
    {
        // if device is not 'main' device
        if (iter->second.compare(deviceName) != 0)
        {
            auto iterDevice = mapDeviceToTransportIds.find(deviceName);
            if (iterDevice != mapDeviceToTransportIds.end())
            {
                LOG_TRACE() << "Remove mapping: " << deviceName << " -> " << transportId;
                mapDeviceToTransportIds.erase(iterDevice);
            }
        }
    }
}

void DeviceTransportIdHandler::addDevice(const std::string& deviceName, const TransportId& transportId)
{
    if (deviceName.empty() || transportId.empty())
    {
        LOG_WARN() << "Invalid parameter to add a transport Id for device! DeviceName " << deviceName
                   << ", Transport Id " << transportId;
        return;
    }

    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapTransportIdToMainDevice.find(transportId);
    if (iter != mapTransportIdToMainDevice.end())
    {
        auto iterTransport = mapDeviceToTransportIds.find(deviceName);
        std::vector<TransportId> addList;
        if (iterTransport != mapDeviceToTransportIds.end())
        {
            addList = iterTransport->second;
            bool addDevice = true;
            auto iterList = addList.begin();
            auto iterListEnd = addList.end();
            for (; iterList != iterListEnd; ++iterList)
            {
                if (iterList->compare(transportId) == 0)
                {
                    addDevice = false;
                    break;
                }
            }
            if (addDevice)
            {
                LOG_TRACE() << "Add mapping: " << deviceName << " -> " << transportId;
                addList.push_back(transportId);
                mapDeviceToTransportIds[deviceName] = addList;
            }
        }
        else
        {
            LOG_TRACE() << "Add mapping: " << deviceName << " -> " << transportId;
            addList.push_back(transportId);
            mapDeviceToTransportIds.insert(std::make_pair(deviceName, addList));
        }
    }
    else
    {
        LOG_WARN() << "Transport Id " << transportId << " does not exist! Device " << deviceName << " cannot be added!";
    }
}

void DeviceTransportIdHandler::addDirectlyConnectedDevice(const std::string& deviceName, const TransportId& transportId)
{
    if (deviceName.empty() || transportId.empty())
    {
        LOG_WARN() << "Invalid parameter to add a transport Id for device! DeviceName " << deviceName
                   << ", Transport Id " << transportId;
        return;
    }

    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapTransportIdToMainDevice.find(transportId);
    if (iter == mapTransportIdToMainDevice.end())
    {
        mapTransportIdToMainDevice.insert(std::make_pair(transportId, deviceName));
        addDevice(deviceName, transportId);
    }
}

bool DeviceTransportIdHandler::isDirectlyConnectedDevice(const std::string& deviceName) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapTransportIdToMainDevice.begin();
    auto iterEnd = mapTransportIdToMainDevice.end();

    for (; iter != iterEnd; ++iter)
    {
        if (iter->second.compare(deviceName) == 0)
        {
            return true;
        }
    }
    return false;
}

std::string DeviceTransportIdHandler::getDirectlyConnectedDevice(const TransportId& transportId) const
{
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapTransportIdToMainDevice.find(transportId);
    if (iter != mapTransportIdToMainDevice.end())
    {
        return iter->second;
    }
    return std::string();
}

void DeviceTransportIdHandler::removeTransportId(const TransportId& transportId)
{
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iterTransport = mapTransportIdToMainDevice.find(transportId);
    if (iterTransport != mapTransportIdToMainDevice.end())
    {
        LOG_TRACE() << "Remove mapping: " << iterTransport->second << " -> " << transportId;
        mapTransportIdToMainDevice.erase(iterTransport);
    }

    auto mappingsIter = mapDeviceToTransportIds.begin();
    while (mappingsIter != mapDeviceToTransportIds.end())
    {
        auto transportIdsIter = mappingsIter->second.begin();
        bool removeIter = false;
        while (transportIdsIter != mappingsIter->second.end())
        {
            if (transportIdsIter->compare(transportId) == 0)
            {
                if (mappingsIter->second.size() == 1)
                {
                    removeIter = true;
                    ++transportIdsIter;
                }
                else
                {
                    LOG_TRACE() << "Remove mapping: " << mappingsIter->first << " -> " << transportId;
                    transportIdsIter = mappingsIter->second.erase(transportIdsIter);
                }
                break;
            }
            else
            {
                ++transportIdsIter;
            }
        }

        if (removeIter)
        {
            LOG_TRACE() << "Remove mapping: " << mappingsIter->first << " -> " << transportId;
            mappingsIter = mapDeviceToTransportIds.erase(mappingsIter);
        }
        else
        {
            ++mappingsIter;
        }
    }
}

std::map<std::string, std::vector<TransportId> > DeviceTransportIdHandler::getDeviceTransportIds() const
{
    return mapDeviceToTransportIds;
}

std::vector<TransportId> DeviceTransportIdHandler::getTransportIds() const
{
    std::vector<TransportId> resultList;
    std::lock_guard<std::recursive_mutex> locker(mutex);
    auto iter = mapTransportIdToMainDevice.begin();
    auto iterEnd = mapTransportIdToMainDevice.end();

    for (; iter != iterEnd; ++iter)
    {
        resultList.push_back(iter->first);
    }
    return resultList;
}

} /* namespace keo_spine */
