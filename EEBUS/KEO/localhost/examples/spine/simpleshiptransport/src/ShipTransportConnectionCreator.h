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

#ifndef _SHIPTRANSPORTCONNECTIONCREATOR_H_
#define _SHIPTRANSPORTCONNECTIONCREATOR_H_

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include "SimpleShipConnection.h"
#include <keo_ship/ShipStack.h>

namespace keo_simple_ship_transport
{

/**
 * @ingroup keo_simple_ship_transport
 * @{
 */

/** Interface to announce new connection objects.
 *
 */
class ShipTransportConnectionCreatorHandler
{
public:
    virtual ~ShipTransportConnectionCreatorHandler()
    {
    }

    virtual void onNewShipTransportConnection(SimpleShipConnectionPtr connection) = 0;
};

/** Connection creator
 *
 */
class ShipTransportConnectionCreator: public keo_ship::ShipNodeFactory
{
public:
    ShipTransportConnectionCreator(ShipTransportConnectionCreatorHandler* shipTransportConnectionCreatorHandler,
        SimpleShipConnectionHandler* simpleShipConnectionHandler)
        : shipTransportConnectionCreatorHandler(shipTransportConnectionCreatorHandler),
          simpleShipConnectionHandler(simpleShipConnectionHandler)
    {

    }

private:

    virtual keo_ship::ShipNodePtr createShipNode()
    {
        SimpleShipConnectionPtr connection = SimpleShipConnectionPtr(
            new SimpleShipConnection(simpleShipConnectionHandler));

        shipTransportConnectionCreatorHandler->onNewShipTransportConnection(connection);

        return connection;
    }

private:
    ShipTransportConnectionCreatorHandler* shipTransportConnectionCreatorHandler;
    SimpleShipConnectionHandler* simpleShipConnectionHandler;
};

/** @} */ //  end of group keo_simple_ship_transport
} /* namespace keo_simple_ship_transport */



#endif /* _SHIPTRANSPORTCONNECTIONCREATOR_H_ */
