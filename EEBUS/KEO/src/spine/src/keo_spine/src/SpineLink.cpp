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
 *     @file  Distributor.cpp
 *     @brief Distributor class definition
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/SpineLink.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <algorithm>
#include <assert.h>
#include <atomic>
#include <mutex>

/* ****************************************************************************** *
 * documentation                                                                  *
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

class SpineLink::SpineLinkPriv : public SpineLinkSendServiceInterface, public TransportConnectionHandler
{
public:
    SpineLinkPriv()
        : mtx()
        , spineLinkReceiveService()
        , closed(false)
    {
    }

    ~SpineLinkPriv()
    {
    }

    TransportConnectionWeakPtr getConnection(const TransportId& transportId) const;

    std::set<TransportId> getConnectionIds() const;

    bool isClosed();

    void close();

    void setSpineLinkReceiveService(SpineLinkReceiveServiceInterfaceWeakPtr spineLinkReceiveService)
    {
        this->spineLinkReceiveService = spineLinkReceiveService;
    }

    SpineLinkReceiveServiceInterfaceWeakPtr getSpineLinkReceiveService()
    {
        return spineLinkReceiveService;
    }

private:
    // SpineLinkSendServiceInterface
    virtual bool sendDatagram(const DatagramRecord& datagramRecord) override;

    // TransportConnectionHandler
    virtual void addConnection(TransportConnectionWeakPtr transportConnection) override;

    // TransportConnectionHandler
    virtual void removeConnection(const TransportId& transportId) override;

    // TransportConnectionHandler
    virtual bool onDatagram(const keo_datagram::Datagram& datagram, const TransportId& transportId) override;

    /**
     * Insert a connection in the internal data structure after acquiring a lock.
     */
    void insertConnectionSafe(const TransportId& transportId, TransportConnectionWeakPtr transportConnection);

    /**
     * Delete a connection from the internal data structure after acquiring a lock.
     */
    bool eraseConnectionSafe(const TransportId& transportId);

private:
    mutable std::recursive_mutex mtx;
    std::map<TransportId, TransportConnectionWeakPtr> transportConnections;
    SpineLinkReceiveServiceInterfaceWeakPtr spineLinkReceiveService;
    std::atomic_bool closed;
};

SpineLink::SpineLink()
    : p(new SpineLinkPriv())
{
}

SpineLink::~SpineLink()
{
    delete p;
}

void SpineLink::setMainDevice(SpineLinkDevicePtr device)
{
    if (device)
    {
        p->setSpineLinkReceiveService(device->getSpineLinkReceiveService());
        if (!p->getSpineLinkReceiveService().expired())
        {
            device->setSpineLinkSendService(p);
        }
        else
        {
            LOG_ERROR() << "Spine link receive service not valid";
        }
    }
    else
    {
        LOG_ERROR() << "Main device is not valid";
    }
}

void SpineLink::close()
{
    p->close();
}

TransportConnectionHandler* SpineLink::getConnectionHandler()
{
    return p;
}

TransportConnectionWeakPtr SpineLink::SpineLinkPriv::getConnection(const TransportId& transportId) const
{
    TransportConnectionWeakPtr tpif;
    if (!transportId.empty())
    {
        std::lock_guard<std::recursive_mutex> locker(mtx);
        auto iter = transportConnections.find(transportId);
        if (iter != transportConnections.end())
        {
            tpif = iter->second;
        }
    }
    else
    {
        LOG_ERROR() << "Transport ID is not set!";
    }
    return tpif;
}

std::set<TransportId> SpineLink::SpineLinkPriv::getConnectionIds() const
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    std::set<TransportId> keys;
    for (auto iter = transportConnections.begin(); iter != transportConnections.end(); ++iter)
    {
        keys.insert(iter->first);
    }
    return keys;
}

bool SpineLink::SpineLinkPriv::isClosed()
{
    return closed;
}

void SpineLink::SpineLinkPriv::close()
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    for (auto iter = transportConnections.begin(); iter != transportConnections.end(); ++iter)
    {
        if (auto spt = iter->second.lock())
        {
            spt->closeConnection();
        }
        else
        {
            LOG_ERROR() << "Invalid transport connection for interface '" << iter->first << "' found.";
        }
    }

    closed = true;
}

// SpineLinkSendServiceInterface
bool SpineLink::SpineLinkPriv::sendDatagram(const DatagramRecord& datagramRecord)
{
    bool transmitted = false;
    const TransportId& transportId = datagramRecord.getTransportId();
    if (!transportId.empty())
    {
        if (auto spt = getConnection(transportId).lock())
        {
            spt->sendDatagram(datagramRecord.getDatagram());
            transmitted = true;
        }
        else
        {
            LOG_ERROR() << "Cannot send datagram to invalid transport connection.";
        }
    }
    else
    {
        LOG_ERROR() << "Cannot send datagram. Invalid transport identifier.";
    }
    return transmitted;
}

void SpineLink::SpineLinkPriv::insertConnectionSafe(
    const TransportId& transportId, TransportConnectionWeakPtr transportConnection)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    transportConnections.insert(std::make_pair(transportId, transportConnection));
}

// TransportConnectionHandler
void SpineLink::SpineLinkPriv::addConnection(TransportConnectionWeakPtr transportConnection)
{
    DEBUG_FUNC();

    if (isClosed())
    {
        return;
    }

    if (auto spt = transportConnection.lock())
    {
        TransportId transportId = spt->getId();
        if (!transportId.empty())
        {
            if (getConnection(transportId).expired())
            {
                insertConnectionSafe(transportId, transportConnection);

                if (auto spt = spineLinkReceiveService.lock())
                {
                    spt->addConnection(transportId);
                }
                else
                {
                    LOG_ERROR() << "SpineLink receive interface not set! Cannot add transport connection";
                }
            }
            else
            {
                LOG_ERROR() << "Could not add connection. Transport identifier already exists.";
            }
        }
        else
        {
            LOG_ERROR() << "Could not add connection. Transport identifier is empty.";
        }
    }
    else
    {
        LOG_ERROR() << "Could not add connection. Transport connection is invalid";
    }
}

bool SpineLink::SpineLinkPriv::eraseConnectionSafe(const TransportId& transportId)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return transportConnections.erase(transportId) == 1;
}

// TransportConnectionHandler
void SpineLink::SpineLinkPriv::removeConnection(const TransportId& transportId)
{
    DEBUG_FUNC();

    if (isClosed())
    {
        return;
    }

    if (!transportId.empty())
    {
        bool removed = eraseConnectionSafe(transportId);
        if (removed)
        {
            if (auto spt = spineLinkReceiveService.lock())
            {
                spt->removeConnection(transportId);
            }
            else
            {
                LOG_ERROR() << "Could not remove connection " << transportId
                            << " from transport connection handler (receive interface not set)";
            }
        }
        else
        {
            LOG_WARNING() << "Could not remove connection " << transportId
                          << " from transport connection handler (connection unknown)";
        }
    }
    else
    {
        LOG_ERROR() << "Could not remove connection from transport connection handler (transport id empty)";
    }
}

// TransportConnectionHandler
bool SpineLink::SpineLinkPriv::onDatagram(const keo_datagram::Datagram& datagram, const TransportId& transportId)
{
    DEBUG_FUNC();

    if (isClosed())
    {
        return false;
    }

    if (auto sptConnection = getConnection(transportId).lock())
    {
        if (auto sptReceiveService = spineLinkReceiveService.lock())
        {
            DatagramRecord datagramRecord(datagram, transportId);
            sptReceiveService->onDatagram(datagramRecord);
            return true;
        }
        else
        {
            LOG_ERROR() << "SpineLink receive interface not set. Cannot receive datagram.";
            return false;
        }
    }
    else
    {
        LOG_WARNING() << "Unknown connection transport identifier " << transportId;
        return false;
    }
}

} /* namespace keo_spine */
