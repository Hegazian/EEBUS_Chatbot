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
 *     @brief      Creator for TransportConnections for SHIP
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipConnectionHandler.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>
#include <mutex>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_default_ship_transport
{

ShipConnectionHandler::ShipConnectionHandler(
    keo_spine::TransportConnectionHandler* handler, ShipControlInterface* listener)
    : connectionHandler(handler)
    , shipListener(listener)
    , transportConnections()
    , shipNodeFactory(ShipConnectionNodeFactoryPtr(new ShipConnectionNodeFactory(*this)))
    , mtx()
{
    DEBUG_FUNC();
    assert(NULL != handler);
    assert(NULL != listener);
}

ShipConnectionHandler::~ShipConnectionHandler()
{
    DEBUG_FUNC();
}

keo_ship::ShipNodeFactoryPtr ShipConnectionHandler::getShipNodeFactory()
{
    return shipNodeFactory;
}

void ShipConnectionHandler::closeConnections()
{
    DEBUG_FUNC();
    std::lock_guard<std::mutex> locker(mtx);
    std::vector<ShipConnectionImplementationPtr>::iterator iter = transportConnections.begin();
    std::vector<ShipConnectionImplementationPtr>::iterator iterEnd = transportConnections.end();
    for (; iter != iterEnd; ++iter)
    {
        iter->get()->close();
    }
}

void ShipConnectionHandler::removeConnection(ShipConnection* node, bool dataExchangeEnabled)
{
    DEBUG_FUNC();
    keo_spine::TransportId id;

    {
        std::lock_guard<std::mutex> locker(mtx);
        std::vector<ShipConnectionImplementationPtr>::iterator iter = transportConnections.begin();
        std::vector<ShipConnectionImplementationPtr>::iterator iterEnd = transportConnections.end();
        for (; iter != iterEnd;)
        {
            std::vector<ShipConnectionImplementationPtr>::iterator actIter = iter++;
            if (actIter->get() == node)
            {
                if (dataExchangeEnabled)
                {
                    id = actIter->get()->getId();
                }
                transportConnections.erase(actIter);
            }
        }
    }
    if (dataExchangeEnabled)
    {
        connectionHandler->removeConnection(id);
    }
}

void ShipConnectionHandler::onDataExchangeEnabled(ShipConnection* node)
{
    ShipConnectionImplementationPtr ptr;
    {
        std::lock_guard<std::mutex> locker(mtx);
        std::vector<ShipConnectionImplementationPtr>::iterator iter = transportConnections.begin();
        std::vector<ShipConnectionImplementationPtr>::iterator iterEnd = transportConnections.end();
        for (; iter != iterEnd;)
        {
            std::vector<ShipConnectionImplementationPtr>::iterator actIter = iter++;
            if (actIter->get() == node)
            {
                ptr = *actIter;
                break;
            }
        }
    }
    if (0 != connectionHandler)
    {
        connectionHandler->addConnection(std::static_pointer_cast<keo_spine::TransportConnection>(ptr));
    }
}

void ShipConnectionHandler::closeConnection(const std::string& id)
{
    DEBUG_FUNC();
    std::lock_guard<std::mutex> locker(mtx);
    std::vector<ShipConnectionImplementationPtr>::iterator iter = transportConnections.begin();
    std::vector<ShipConnectionImplementationPtr>::iterator iterEnd = transportConnections.end();
    for (; iter != iterEnd;)
    {
        std::vector<ShipConnectionImplementationPtr>::iterator actIter = iter++;
        if (actIter->get()->getId() == id)
        {
            actIter->get()->close();
            break;
        }
    }
}

ShipConnectionHandler::ShipConnectionNodeFactory::ShipConnectionNodeFactory(ShipConnectionHandler& creator)
    : parent(creator)
{
}

keo_ship::ShipNodePtr ShipConnectionHandler::ShipConnectionNodeFactory::createShipNode()
{
    DEBUG_FUNC();
    std::lock_guard<std::mutex> locker(parent.mtx);
    ShipConnectionImplementationPtr transportConnection = ShipConnectionImplementationPtr(
        new ShipConnectionImplementation(parent.connectionHandler, parent.shipListener));
    // TODO this needs to be refactored. A factory method should not add the object it created to some list...
    parent.transportConnections.push_back(transportConnection);
    return transportConnection;
}

} /* namespace keo_default_ship_transport */
