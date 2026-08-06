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
#include "ShipSocket.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <keo_util/KELogging.h>

#include <algorithm>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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

ShipWss::ShipWss(ShipSocketConnectionStatusListener* socketConnectionHandler, SecurityHandlerPtr shipSecurityHandler,
    std::uint32_t sessionCacheSize)
    : port(0)
    , socketPath()
    , hosts()
    , servers()
    , shipOpenSSL(shipSecurityHandler, sessionCacheSize)
    , statusListener(socketConnectionHandler)
    , maxSessionCacheSize(sessionCacheSize)
{
    assert(NULL != shipSecurityHandler.get());
}

ShipWss::~ShipWss()
{
    clearServers();

    for (auto it : clientSessionCache)
    {
        SSL_SESSION_free(it.second);
        it.second = nullptr;
    }
    clientSessionCache.clear();
}

void ShipWss::clearServers()
{
    while (!servers.empty())
    {
        delete servers.front(), servers.pop_front();
    }
}

ShipStackResult ShipWss::initialize()
{
    /* does nothing */
    return ShipStackResult::StackResultOk;
}

ShipStackResult ShipWss::finalize()
{
    DEBUG_FUNC();
    if (isStarted())
    {
        stop();
    }
    return ShipStackResult::StackResultOk; // FIXME no negative case(s)?
}

void ShipWss::setHosts(const std::list<std::string>& hosts)
{
    this->hosts = hosts;
}

std::list<std::string> ShipWss::getHosts() const
{
    return hosts;
}

void ShipWss::setPort(int serverPort)
{
    this->port = serverPort;
}

int ShipWss::getPort() const
{
    return port;
}

void ShipWss::setSocketPath(const std::string& socketPath)
{
    this->socketPath = socketPath;
}

std::string ShipWss::getSocketPath() const
{
    return socketPath;
}

bool ShipWss::start()
{
    DEBUG_FUNC();
    bool started = false;

    if (servers.empty())
    {
        if (!hosts.empty())
        {
            for (auto host : hosts)
            {
                SocketServer* server = new keo_ship::SocketServer(this);
                servers.push_back(server);

                LOG_INFO() << "Starting wss server '" << host << ":" << std::dec << port << "'";
                if (server->open(host, std::to_string(port)) && server->start())
                {
                    started = true;
                }
                else
                {
                    started = false;
                    break;
                }
            }
        }
        else
        {
            LOG_ERROR() << "Cannot start wss server! Hosts not set";
        }

        if (!started)
        {
            LOG_WARN() << "Not all wss sockets could be opened. Closing all.";
            clearServers();
        }
    }
    else
    {
        LOG_WARN() << "Server already started.";
    }
    return started;
}

void ShipWss::pause()
{
    DEBUG_FUNC();
    if (!servers.empty())
    {
        for (auto server : servers)
        {
            if (!server->isPaused())
            {
                server->pause();
            }
            else
            {
                DEBUG_INFO() << "ShipWss::pause(): Server is already paused.";
            }
        }
    }
    else
    {
        LOG_ERROR() << "Cannot pause server! Server has not been started.";
    }
}

void ShipWss::resume()
{
    DEBUG_FUNC();
    if (!servers.empty())
    {
        for (auto server : servers)
        {
            if (server->isPaused())
            {
                server->resume();
            }
            else
            {
                DEBUG_INFO() << "ShipWss::resume(): Server has not been paused.";
            }
        }
    }
    else
    {
        LOG_ERROR() << "Cannot resume server! Server has not been started.";
    }
}

void ShipWss::join()
{
    DEBUG_FUNC();
    if (!servers.empty())
    {
        while (!servers.empty())
        {
            servers.front()->join(), delete servers.front(), servers.pop_front();
        }
    }
    else
    {
        DEBUG_INFO() << "ShipWSS:join(): Server has not been started.";
    }
}

void ShipWss::stop()
{
    DEBUG_FUNC();
    if (!servers.empty())
    {
        for (auto server : servers)
        {
            server->stop();
        }
    }
    else
    {
        DEBUG_INFO() << "ShipWSS:stop(): Server has not been started.";
    }
}

bool ShipWss::isStarted() const
{
    for (auto server : servers)
    {
        if (server->isStarted())
        {
            return true;
        }
    }
    return false;
}

int ShipWss::openSocket(const std::string& host, const std::string& port)
{
    struct addrinfo aiHints;
    struct addrinfo* aiList = NULL;
    memset(&aiHints, 0, sizeof(aiHints));
    aiHints.ai_family = AF_UNSPEC;
    aiHints.ai_socktype = SOCK_STREAM;
    aiHints.ai_protocol = IPPROTO_TCP;

    LOG_VERBOSE(6) << "ShipWss::openSocket()";
    LOG_VERBOSE(6) << "ShipWss::openSocket(): Hostname: " << host;
    LOG_VERBOSE(6) << "ShipWss::openSocket(): Port    : " << port;

    {
        // //////////////////////
        // workaround for glibc < 2.27
        // see https://sourceware.org/bugzilla/show_bug.cgi?format=multiple&id=20532
        errno = 0;
        // //////////////////////
        int result = ::getaddrinfo(host.c_str(), port.c_str(), &aiHints, &aiList);
        if (result != 0)
        {
            logGetaddrinfoError(host, port, result, errno);
            return -1;
        }
    }

    int sockfd = -1;
    struct addrinfo* ai;
    for (ai = aiList; ai != NULL; ai = ai->ai_next)
    {
        sockfd = ::socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sockfd != -1)
        {
            if (ai->ai_family == AF_INET || ai->ai_family == AF_INET6)
            {
                fd_set fdset;
                struct timeval tv;

                FD_ZERO(&fdset);
                FD_SET(sockfd, &fdset);

                tv.tv_sec = 10; /* 10 second timeout */
                tv.tv_usec = 0;

                ::fcntl(sockfd, F_SETFL, O_NONBLOCK);

                int retval = ::connect(sockfd, ai->ai_addr, ai->ai_addrlen);

                if ((retval == -1) && (errno != EINPROGRESS))
                {
                    LOG_WARN() << "Cannot connect to " << host << ": " << ::strerror(errno);
                    ::close(sockfd);
                    sockfd = -1;
                }
                if (retval == 0)
                {
                    LOG_VERBOSE(6) << "ShipWss::openSocket(): "
                                   << "opened using " << ((ai->ai_family == AF_INET6) ? "IPv6" : "IPv4")
                                   << ", host address=" << host;
                    break;
                }

                if (1 == ::select(sockfd + 1, NULL, &fdset, NULL, &tv))
                {
                    int so_error;
                    socklen_t len = sizeof so_error;

                    ::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);

                    if (so_error == 0)
                    {
                        LOG_VERBOSE(6) << "ShipWss::openSocket(): "
                                       << "opened using " << ((ai->ai_family == AF_INET6) ? "IPv6" : "IPv4")
                                       << ", host address=" << host;
                        break;
                    }
                    else
                    {
                        LOG_WARN() << "Connect to " << host << " failed: " << ::strerror(so_error);
                        ::close(sockfd);
                        sockfd = -1;
                    }
                }
                else
                {
                    LOG_WARN() << "Connect to " << host << " failed: " << ::strerror(errno);
                    ::close(sockfd);
                    sockfd = -1;
                }
            }
            else
            {
                LOG_WARN() << "ShipWss::openSocket(): An enumerated Socket uses neither IPv4 nor IPv6";
                ::close(sockfd);
                sockfd = -1;
            }
        }
    }

    if (-1 == sockfd)
    {
        LOG_ERROR() << "Cannot connect to " << host;
    }

    ::freeaddrinfo(aiList);

    return sockfd;
}

OpenSSLConnection* ShipWss::createAndEstablishConnection(int sockfd, const Uri& destinationURI, bool server)
{
    OpenSSLConnection* secureConnection
        = shipOpenSSL.createSSLConnection(destinationURI.isValid() ? destinationURI.getHost().c_str() : nullptr);

    if (secureConnection == NULL)
    {
        LOG_ERROR() << "Unable to create a new SSL connection. (role: " << (server ? "server)" : "client)");
        return nullptr;
    }

    secureConnection->set_fd(sockfd);

    // TODO timeout???
    secureConnection->socketModeBlock(true);
    int result = 0;

    if (server)
    {
        result = secureConnection->accept();
        DEBUG_INFO() << "Accept result: " << result;
    }
    else
    {
        std::string key = destinationURI.getHost() + ":" + std::to_string(destinationURI.getPort());
        SSL_SESSION* session = getCachedSession(key);

        if (nullptr != session)
        {
            secureConnection->setSSLSession(session);
        }

        result = secureConnection->connect();
        DEBUG_INFO() << "Connect result: " << result;

        if (nullptr != session)
        {
            SSL_SESSION_free(session);
            removeFromSessionCache(key);
        }

        if (0 < maxSessionCacheSize)
        {
            addToSessionCache(key, secureConnection->getSSLSession1());
        }
    }

    secureConnection->socketModeBlock(false);

    if (secureConnection->sessionReused())
    {
        DEBUG_INFO() << "REUSED SESSION!";

        SSL_SESSION* sess = secureConnection->getSSLSession0();

        X509* x509 = SSL_SESSION_get0_peer(sess);

        unsigned char* certDER = NULL;
        int lengthDER = i2d_X509(x509, &certDER);
        if (lengthDER < 0)
        {
            LOG_ERROR() << "Error converting peer certificate to DER format. Rejecting the certificate.";
            return 0;
        }
        keo_ship::X509Certificate certificate(std::vector<unsigned char>(certDER, certDER + lengthDER));
        OPENSSL_free(certDER);

        secureConnection->setPeerCertificate(certificate);
    }

    if ((result == 1 || secureConnection->noError(result)))
    {
        return secureConnection;
    }

    LOG_WARN() << "SSL handshake failed";
    secureConnection->close();
    delete secureConnection;
    return nullptr;
}

bool ShipWss::connectTo(const Uri& destinationURI)
{
    int sockfd = openSocket(destinationURI.getHost(), std::to_string(destinationURI.getPort()));
    if (-1 != sockfd)
    {
        ShipSocket* shipSocket = new ShipSocket(statusListener, ShipSocket::ROLE_CLIENT);
        if (shipSocket->initialize())
        {
            OpenSSLConnection* secureConnection = createAndEstablishConnection(sockfd, destinationURI, false);

            if (nullptr != secureConnection)
            {
                if (!shipSocket->openClient(secureConnection, destinationURI))
                {
                    shipSocket->finalize();
                    delete shipSocket;
                    shipSocket = nullptr;
                    LOG_ERROR() << "Cannot open client websocket " << destinationURI.getUri() << "!";
                }
            }
            else
            {
                shipSocket->finalize();
                delete shipSocket;
                shipSocket = nullptr;
            }
        }
        else
        {
            LOG_ERROR() << "Cannot initialize client websocket!";
            delete shipSocket;
            shipSocket = nullptr;
        }

        if (NULL != shipSocket)
        {
            return true;
        }

        ::shutdown(sockfd, SHUT_RDWR);
        ::close(sockfd);
    }
    return false;
}

void ShipWss::onNewSocket(int sockfd)
{
    ShipSocket* shipSocket = new ShipSocket(statusListener, ShipSocket::ROLE_SERVER);
    if (shipSocket->initialize())
    {
        OpenSSLConnection* secureConnection = createAndEstablishConnection(sockfd, Uri(std::string()), true);

        if (nullptr != secureConnection)
        {
            if (!shipSocket->openServer(secureConnection))
            {
                shipSocket->finalize();
                delete shipSocket;
                shipSocket = nullptr;
                LOG_ERROR() << "Cannot open server websocket!";
            }
        }
        else
        {
            shipSocket->finalize();
            delete shipSocket;
            shipSocket = nullptr;
        }
    }
    else
    {
        LOG_ERROR() << "Cannot initialize server websocket!";
        delete shipSocket;
        shipSocket = nullptr;
    }

    if (shipSocket == nullptr)
    {
        ::shutdown(sockfd, SHUT_RDWR);
        ::close(sockfd);
    }
}

void ShipWss::addToSessionCache(std::string key, SSL_SESSION* session)
{
    while (clientSessionCacheOrder.size() >= maxSessionCacheSize)
    {
        std::string first = clientSessionCacheOrder.front();
        SSL_SESSION_free(clientSessionCache[first]);
        clientSessionCache.erase(first);
        clientSessionCacheOrder.pop_front();
    }

    clientSessionCacheOrder.push_back(key);
    clientSessionCache[key] = session;
}

void ShipWss::removeFromSessionCache(std::string key)
{
    clientSessionCacheType::iterator it = clientSessionCache.find(key);
    if (it != clientSessionCache.end())
    {
        clientSessionCache.erase(it);
        clientSessionCacheOrder.erase(std::find(clientSessionCacheOrder.begin(), clientSessionCacheOrder.end(), key));
    }
}

SSL_SESSION* ShipWss::getCachedSession(std::string key) const
{
    clientSessionCacheType::const_iterator it = clientSessionCache.find(key);
    if (it != clientSessionCache.end())
    {
        return it->second;
    }
    return nullptr;
}

bool ShipWss::isSessionCached(std::string key) const
{
    clientSessionCacheType::const_iterator it = clientSessionCache.find(key);
    return it != clientSessionCache.end();
}

void ShipWss::logGetaddrinfoError(std::string const& host, std::string const& port, int result, int error)
{
    std::stringstream err;
    err << "getaddrinfo failed for host \"" << host << "\" and port " << port
        << ". Is the DNS resolver configured correctly? Details: ";

    if (error == EAI_SYSTEM)
    {
        err << ::strerror(error);
    }
    else
    {
        err << ::gai_strerror(result);
    }

    LOG_ERROR() << err.str();
}

} /* namespace keo_ship */
