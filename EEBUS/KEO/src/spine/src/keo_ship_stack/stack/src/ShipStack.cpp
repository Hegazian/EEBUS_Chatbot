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

#include "ShipWss.h"
#include "SocketConnectionHandler.h"
#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_tool/KEJobRunner.h>
#include <keo_util/KELogging.h>
/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

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

namespace keo_ship
{

class ShipStackPriv
{
public:
    ShipStackPriv(ShipStackConfiguration shipStackConfiguration, SecurityHandlerPtr shipSecurityData,
        ShipNodeFactoryPtr shipNodeCreator)
        : shipSecurityData(shipSecurityData)
        , socketConnectionHandler(shipStackConfiguration, shipSecurityData, shipNodeCreator)
        , shipWss(&socketConnectionHandler, shipSecurityData, shipStackConfiguration.getSessionCacheSize())
    {
    }

    ShipStackResult initialize()
    {
        // initialize in the same order the components has been created

        ShipStackResult result = socketConnectionHandler.initialize();
        if (ShipStackResult::StackResultOk == result)
        {
            result = shipWss.initialize();
        }

        return result;
    }

    ShipStackResult finalize()
    {
        // finalize in the reverse order the components has been created

        ShipStackResult result = shipWss.finalize();
        if (ShipStackResult::StackResultOk == result)
        {
            result = socketConnectionHandler.finalize();
        }
        //LOG_TRACE() << "finalized";
        return result;
    }

private:
    SecurityHandlerPtr shipSecurityData;

public:
    SocketConnectionHandler socketConnectionHandler;
    ShipWss shipWss;
};

ShipStack::ShipStack(ShipStackConfiguration shipStackConfiguration, SecurityHandlerPtr shipSecurityData,
    ShipNodeFactoryPtr shipNodeCreator)
    : d(new ShipStackPriv(shipStackConfiguration, shipSecurityData, shipNodeCreator))
{
    //DEBUG_FUNC();
}

ShipStack::~ShipStack()
{
    //DEBUG_FUNC();

    stopServer();
    shutdown();

    delete d;
}

std::string ShipStack::getSki() const
{
    return d->socketConnectionHandler.getServerInfo().getSki();
}

bool ShipStack::isConnected(const std::string& ski) const
{
    return d->socketConnectionHandler.isConnected(ski);
}

ShipStackResult ShipStack::initialize()
{
    //DEBUG_FUNC();
    return d->initialize();
}

ShipStackResult ShipStack::shutdown()
{
    //DEBUG_FUNC();
    return d->finalize();
}

void ShipStack::initializeServer(const std::list<std::string>& hosts, int serverPort, const std::string& socketPath)
{
    d->shipWss.setHosts(hosts);
    d->shipWss.setPort(serverPort);
    d->shipWss.setSocketPath(socketPath);
}

bool ShipStack::startServer()
{
    return d->shipWss.start();
}

void ShipStack::serverJoin()
{
    d->shipWss.join();
}

void ShipStack::stopServer()
{
    d->shipWss.stop();
}

bool ShipStack::isServerStarted() const
{
    return d->shipWss.isStarted();
}

bool ShipStack::connectTo(const Uri& uri)
{
    return d->shipWss.connectTo(uri);
}

void ShipStack::setRejectConnections(bool rejectConnections)
{
    d->socketConnectionHandler.denyConnections(rejectConnections);
}

} /* namespace keo_ship */
