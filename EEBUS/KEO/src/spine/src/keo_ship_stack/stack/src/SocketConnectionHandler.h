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

#ifndef KEO_SHIP_STACK_STACK_SRC_SOCKETCONNECTIONHANDLER_H_
#define KEO_SHIP_STACK_STACK_SRC_SOCKETCONNECTIONHANDLER_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipServerInfo.h"
#include <ShipMessageExchange.h>
#include <ShipMessageExchangeConnectionConfirmedListener.h>
#include <ShipSocket.h>
#include <keo_ship/ShipSecurity.h>
#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <condition_variable>
#include <list>
#include <map>
#include <mutex>
#include <string>

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

class ShipStateSocket;

class SocketConnectionHandler : public ShipSocketConnectionStatusListener,
                                public ShipMessageExchangeConnectionConfirmedListener
{
public:
    SocketConnectionHandler(
        ShipStackConfiguration& ship, SecurityHandlerPtr shipSecurityData, ShipNodeFactoryPtr shipNodeFactory);

    /**
     *
     */
    virtual ~SocketConnectionHandler();

    /**
     * Initializes the SocketConnectionHandler
     * @return StackResultOk on success
     */
    ShipStackResult initialize();

    /**
     * Finalizes the SocketConnectionHandler
     * @return StackResultOk on success
     */
    ShipStackResult finalize();

    /**
     * @return ship server info const reference
     */
    const ShipServerInfo& getServerInfo() const;

    /**
     *
     * @param ski
     * @return
     */
    bool isConnected(const std::string& ski) const;

    /**
     *
     * @param flag
     */
    void denyConnections(bool flag);

    /**
     * @param socket
     * @see ShipSocketConnectionStatusListener
     */
    virtual void onConnect(ShipSocket* rawSocket);

    /**
     * @param remoteSki
     * @param statusCode
     * @param reason
     * @see ShipSocketConnectionStatusListener
     */
    virtual void onClose(ShipSocket* rawSocket, int statusCode, const std::string& reason);

    /**
     * @param shipSocket related socket
     * @see ShipSocketConnectionStatusListener
     */
    virtual void onTimeout(ShipSocket* shipSocket);

    /**
     * @param socket
     * @param id
     * @see ShipMessageExchangeConnectionConfirmedListener
     */
    virtual void onConnectionConfirmed(ShipSocket* shipSocket, const std::string& id);

private:
    /**
     *
     * @param socket
     * @return
     */
    std::string getServerUri(ShipSocket* shipSocket);

private:
    class ShipStateSocket;

private:
    static const std::string WSS_STRING; // = "wss://";
    static const int CLOSE_STATUS_CODE_GENERAL_ERROR; // = 4200;
    static const int CLOSE_STATUS_CODE_DOUBLE_CONNECTION; // = 4201;
    static const int CLOSE_STATUS_CODE_DENY_CONNECTION; // = 4202;

    typedef std::map<std::string /* remoteSKI */, std::list<ShipStateSocket*> > ShipStateSocketMapType;

    mutable std::recursive_mutex mtx;
    keo_tool::KEJobRunner* jobRunner;
    ShipStateSocketMapType connectedPeers;
    SecurityHandlerPtr shipSecurityData;
    ShipServerInfo serverInfo;
    ShipNodeFactoryPtr shipNodeFactory;
    bool denyConnectionsFlag;
    bool finalizing;
    std::condition_variable_any cv_peersClosed;
};

} /* namespace keo_ship */

/** @}
 * end of file
 */

#endif /* KEO_SHIP_STACK_STACK_SRC_SOCKETCONNECTIONHANDLER_H_ */
