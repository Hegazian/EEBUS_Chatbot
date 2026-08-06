/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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
 *     @brief      Module for handling the state sequence action.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_TEST_CONNECTION_STATE_HANDLER_EXTEND_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_TEST_CONNECTION_STATE_HANDLER_EXTEND_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ConnectionStateHandler.h"

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
 * Handling of connection states in test
 */
class ConnectionStateHandlerExtend : public ConnectionStateHandler
{
public:
    ConnectionStateHandlerExtend(const std::string& id, const NodeInfo& nodeInfo, bool isClient,
        ConnectionStateHandlerListener* actionModuleListener, const std::string& serverUri);

    NodeInfo* getNodeInfo();

    void setNodeInfo(const NodeInfo& nodeInfo);

    StateInfo* getStateInfo();

    void setStateInfo(const StateInfo& stateInfo);

    void startTimer();

    void start()
    {
        ConnectionStateHandler::start();
    }

    void doAction(ActionState action)
    {
        ConnectionStateHandler::doAction(action);
    }
};
}

#endif
