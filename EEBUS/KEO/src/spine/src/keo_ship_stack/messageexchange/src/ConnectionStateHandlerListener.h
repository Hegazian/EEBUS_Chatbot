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
 *     @brief      ConnectionStateHandler listener
 *
 *     @par        Action module listener interface class
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_CONNECTION_STATE_HANDLER_LISTENER_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_CONNECTION_STATE_HANDLER_LISTENER_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <string>
#include <vector>
/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */
#include "NodeEvent.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{

/**
 * @ingroup framework_event
 */
class ConnectionStateHandlerListener
{
public:
    ConnectionStateHandlerListener()
    {
    }
    virtual ~ConnectionStateHandlerListener()
    {
    }

    /**
     * Send message to connection.
     *
     */
    virtual bool sendToShipTransport(const std::vector<char>& message) = 0;

    virtual void announceEvent(keo_ship::NodeEvent event, const std::string& data) = 0;

    virtual void closeConnection(int statusCode, const std::string& reason) = 0;
};

} /* namespace keo_spine */

#endif /* KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_CONNECTION_STATE_HANDLER_LISTENER_H_ */
