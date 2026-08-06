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

#ifndef KEO_SHIP_STACK_TRANSPORT_SRC_SHIPSOCKET_H_
#define KEO_SHIP_STACK_TRANSPORT_SRC_SHIPSOCKET_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipTimer.h"
#include "WebSocket.h"
#include "tls/ShipOpenSSL.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_ship/ShipSecurity.h>
#include <keo_tool/KESemaphore.h>
#include <mutex>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */
namespace keo_tool
{
class KEJobRunner;
}
namespace keo_ship
{

class ShipSocket;

class ShipSocketMessageListener
{
public:
    virtual ~ShipSocketMessageListener()
    {
    }
    virtual void onShipMessage(const std::vector<char>& message) = 0;
};

class ShipSocketConnectionStatusListener
{
public:
    virtual ~ShipSocketConnectionStatusListener()
    {
    }

    virtual void onConnect(ShipSocket* shipSocket) = 0;
    virtual void onClose(ShipSocket* shipSocket, int statusCode, const std::string& reason) = 0;
};

class ShipSocket
{
public:
    typedef enum
    {
        ROLE_CLIENT,
        ROLE_SERVER
    } SocketRole;

    /**
     * Constructor
     *
     * @param statusListener
     * @param securityHandler
     * @param role
     */
    ShipSocket(ShipSocketConnectionStatusListener* statusListener, SocketRole role);

    /**
     * Destructor
     */
    virtual ~ShipSocket();

    /**
     *
     * @param listener
     */
    void setShipSocketMessageListener(ShipSocketMessageListener* listener);

    /**
     * Initialize and starts the socket sender and receiver threads
     * @return true on success
     */
    bool initialize();

    void finalize();
    /**
     *
     * @param message
     * @return
     */
    bool sendMessage(const std::vector<char>& message);

    /**
     * Get the role
     * @return the role
     */
    SocketRole getRole() const;

    /**
     * Get the remote SKI
     * @return the remote SKI
     */
    std::string getRemoteSki() const;

    /**
     * Get the peer's IP address
     * @return IP address of the peer
     */
    std::string getIP() const;

    /**
     * Get the peer's port
     * @return port of the peer
     */
    int getPort() const;

    /**
     * Get the connection's display name
     * @return display name of the connection
     */
    std::string getDisplayName() const;

    /**
     * Get the peer's certificate
     * @return certificate of the peer
     */
    X509Certificate getRemoteCertificate() const;

    /**
     * Open a WebSocket connection from server side; intended to be used only by the WebSocketServer
     * @param socket the socket to use
     * @return true if open succeeded
     */
    bool openServer(OpenSSLConnection* secureConnection);

    /**
     * Open a WebSocket connection from client side
     * @param sockfd the socket
     * @param destinationURI the URI to connect to
     * @param wssProtocols wss protocol (default: "ship")
     * @return true if open succeeded
     */
    bool openClient(OpenSSLConnection* secureConnection, const Uri& destinationURI);

    /**
     * Close a WebSocket connection
     * @param statusCode the status code to use
     * @param reason the reason for closing the connection
     */
    void close(int statusCode, const std::string& reason);

    /**
     * Set the display name
     * @param displayName the display name to set
     */
    void setDisplayName(const std::string& displayName);

    /**
     * Get the closing flag
     * @return true if the socket is closing, false otherwise
     */
    bool isClosing();

private:
    ShipSocketConnectionStatusListener* getShipSocketConnectionStatusListener() const;
    ShipSocketMessageListener* getShipSocketMessageListener() const;
    keo_tool::KEJobRunner* getJobRunner() const;

    /**
     * Set the closing flag
     */
    void setClosing();

    /**
     * Set the remote SKI
     * @param remoteSKI the remote SKI to set
     */
    bool setSKI(const std::string& remoteSKI);

    bool sendPing();
    void pongExpired();

    class WebSocketListener : public WebSocketHandler
    {
        ShipSocket& parent;
        std::vector<char> binaryData;
        std::list<std::vector<char>> receivedMessages;

        ShipTimer pingTimer;
        ShipTimer pongExpiredTimer;

    public:
        explicit WebSocketListener(ShipSocket& parent);
        virtual ~WebSocketListener();
        void startPingTimer();

    private:
        virtual void onClose(WebSocket* client, unsigned short code, const std::string& reason);
        virtual void onMessage(WebSocket* client, WebSocketHandler::Opcode opcode, const std::vector<char>& data,
            size_t dataSize, bool bFinal);

        void onPongExpiredTimeout();
        void onPingTimeout();
    };

private:
    static const long PING_TIMEOUT;
    static const long PONG_EXPIRED_TIMEOUT;

    static const int CLOSE_STATUS_CODE_GENERAL_ERROR;
    static const int CLOSE_STATUS_CODE_CLOSED_BY_PEER;
    static const int CLOSE_STATUS_CODE_PING_EXPIRED;

    mutable std::recursive_mutex mtx;
    keo_tool::KEJobRunner* jobRunner;
    WebSocketListener wsListener;
    OpenSSLConnection* secureConnection;
    mutable std::recursive_mutex timerMtx;

    ShipSocketConnectionStatusListener* statusListener;
    ShipSocketMessageListener* messageListener;
    std::vector<char> message;
    std::string remoteSki;
    X509Certificate remoteCertificate;
    SocketRole role;
    bool closing;
    std::string displayName;
    keo_tool::KESemaphore acceptMessages;
    WebSocket websocket;
};

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_TRANSPORT_SRC_SHIPSOCKET_H_ */
