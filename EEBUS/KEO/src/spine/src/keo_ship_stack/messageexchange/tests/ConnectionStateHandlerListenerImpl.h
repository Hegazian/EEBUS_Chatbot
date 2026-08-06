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

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_TEST_CONNECTION_STATE_HANDLER_LISTENER_IMPL_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_TEST_CONNECTION_STATE_HANDLER_LISTENER_IMPL_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "CShipDataClass.h"
#include "ConnectionStateHandlerListener.h"

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
class ConnectionStateHandlerListenerImpl : public ConnectionStateHandlerListener
{
public:
    ConnectionStateHandlerListenerImpl();

    bool sendToShipTransport(const std::vector<char>& message);

    void announceEvent(keo_ship::NodeEvent event, const std::string& data);

    void closeConnection(int statusCode, const std::string& reason);

    std::vector<CShipDataClass*> getSentClasses();

    std::vector<std::vector<char> > getSentData();

    std::vector<NodeEvent> getSentEvent();

    void clear();

private:
    std::vector<CShipDataClass*> m_sentClasses;
    std::vector<std::vector<char> > m_sentData;
    std::vector<NodeEvent> m_sentEvent;
};
}

#endif
