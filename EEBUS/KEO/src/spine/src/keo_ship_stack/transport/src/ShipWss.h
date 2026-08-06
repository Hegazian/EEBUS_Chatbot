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

#ifndef KEO_SHIP_STACK_TRANSPORT_SHIPWSS_H_
#define KEO_SHIP_STACK_TRANSPORT_SHIPWSS_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "SocketServer.h"
#include "tls/ShipOpenSSL.h"
#include <keo_ship/ShipStack.h>
#include <keo_ship/Uri.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <list>
#include <map>
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

class ShipSocketConnectionStatusListener;

class ShipWss : public SocketServerListener
{
public:
    /**
     * Constructor
     */
    ShipWss(ShipSocketConnectionStatusListener* socketConnectionHandler, SecurityHandlerPtr shipSecurityHandler,
        std::uint32_t sessionCacheSize);

    /**
     * Destructor
     */
    ~ShipWss();

    /**
     * Initializes ShipWss
     * @return StackResultOk on success
     */
    ShipStackResult initialize();

    /**
     * Finalize ShipWss
     * @return StackResultOk
     */
    ShipStackResult finalize();

    /**
     * Get the hosts
     * @return the list of hosts
     */
    std::list<std::string> getHosts() const;

    /**
     * Get the server listening port
     * @return port the server listens to
     */
    int getPort() const;

    /**
     * Get the path of the socket
     * @return the path of the socket
     */
    std::string getSocketPath() const;

    /**
     * Set the list of hosts
     * @param the list of hosts to set
     */
    void setHosts(const std::list<std::string>& hosts);

    /**
     * Set the server listening port
     * @param serverPort the port to set
     */
    void setPort(int serverPort);

    /**
     * Set the socket path
     * @param socketPath the socket path to set
     */
    void setSocketPath(const std::string& socketPath);

    /**
     * Connect to a peer
     * @param destinationURI the URI to connect to
     * @return true upon success, false upon failure
     */
    bool connectTo(const Uri& destinationURI);

    /**
     * Start the WSS servers
     * @return true, when all servers have been started
     */
    bool start();

    /**
     * Check if the server is started
     * @return true if the server has been started
     */
    bool isStarted() const;

    /**
     * Pause the wss server
     */
    void pause();

    /**
     * Resume the wss server
     */
    void resume();

    /**
     * Terminate the wss server
     */
    void stop();

    /**
     * Join the terminated wss server
     */
    void join();

private:
    /** Remove all active servers
     */
    void clearServers();

    /** Opens a socket to host::port
     *
     * @param host Host address
     * @param port Port
     * @return The socket or -1 (INVALID_SOCKET) in case of an error
     */
    int openSocket(const std::string& host, const std::string& port);

    OpenSSLConnection* createAndEstablishConnection(int sockfd, const Uri& destinationURI, bool server);

    void addToSessionCache(std::string key, SSL_SESSION* session);

    SSL_SESSION* getCachedSession(std::string key) const;

    void removeFromSessionCache(std::string key);

    bool isSessionCached(std::string key) const;

    void logGetaddrinfoError(std::string const& host, std::string const& port, int result, int error);

private:
    void onNewSocket(int sockfd) override;

private:
    int port;
    std::string socketPath;
    std::list<std::string> hosts;
    std::list<SocketServer*> servers;
    ShipOpenSSL shipOpenSSL;
    ShipSocketConnectionStatusListener* statusListener;
    std::uint32_t maxSessionCacheSize;
    std::list<std::string> clientSessionCacheOrder;
    typedef std::map<std::string, SSL_SESSION*> clientSessionCacheType;
    clientSessionCacheType clientSessionCache;
};

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_TRANSPORT_SHIPWSS_H_ */
