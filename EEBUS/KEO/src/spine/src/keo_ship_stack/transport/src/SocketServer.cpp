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

#include "SocketServer.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <arpa/inet.h>
#include <assert.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

#define SLEEP(ms) usleep(ms * 1000)

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{

SocketServer::SocketServer(SocketServerListener* socketServerListener)
    : m_socketServerListener(socketServerListener)
    , mPaused(false)
    , mPort()
    , mHost()
    , mProcessMutex()
    , mServerStarted(false)
    , mProcessCond()
    , mResumeCond()
{
    // mPipeFd[2] cannot be initialized here
    mPipeFd[0] = -1;
    mPipeFd[1] = -1;
    mSocket[0] = -1;
    mSocket[1] = -1;
}

SocketServer::~SocketServer()
{

    stop();
}

void SocketServer::stop()
{
    std::unique_lock<std::mutex> locker(mProcessMutex);
    if (mServerStarted)
    {
        mServerStarted = false;
        if (mSocket[0] != -1)
        {
            socketModeBlock(mSocket[0], false);
            if (-1 == ::shutdown(mSocket[0], SHUT_RDWR))
            {
                error("shutdown");
            }
            if (-1 == ::close(mSocket[0]))
            {
                error("close");
            }
            mSocket[0] = -1;
        }
        if (mSocket[1] != -1)
        {
            socketModeBlock(mSocket[1], false);
            if (-1 == ::shutdown(mSocket[1], SHUT_RDWR))
            {
                error("shutdown");
            }
            if (-1 == ::close(mSocket[1]))
            {
                error("close");
            }
            mSocket[1] = -1;
        }
        char dummyByte = 0;
        if (-1 == ::write(mPipeFd[1], &dummyByte, 1))
        {
            error("write");
        }
        mResumeCond.notify_one();
        mProcessCond.notify_one();
    }
}

void SocketServer::join()
{
    thread.join();
}

bool SocketServer::start()
{
    std::lock_guard<std::mutex> locker(mProcessMutex);
    if (!mServerStarted)
    {
        if (0 == pipe(mPipeFd))
        {
            thread = std::thread(&SocketServer::worker, this);
            mServerStarted = true;
        }
        else
        {
            error("pipe");
        }
    }
    else
    {
        LOG_FATAL() << "WSS server has already been started.";
        //::exit(EXIT_FAILURE);
    }
    return mServerStarted;
}

bool SocketServer::isStarted() const
{
    std::lock_guard<std::mutex> locker(mProcessMutex);
    return mServerStarted;
}

bool SocketServer::open(const std::string& host, const std::string& sPort)
{
    bool opened = false;
    std::lock_guard<std::mutex> locker(mProcessMutex);

    mHost = host;

    int index = 0;

    LOG_VERBOSE(6) << "SocketServer::open(): host: " << host << " port: " << sPort;

    int serverSocket;

    sockaddr_in addr4;
    sockaddr_in6 addr6;
    socklen_t addrlen;

    ::memset(&addr4, 0, sizeof(addr4));
    ::memset(&addr6, 0, sizeof(addr6));

    bool isV4 = false;
    (void)addrlen;

    if (host.find(":") == std::string::npos) // TODO Is this check correct?
    {
        // IPv4
        addr4.sin_family = AF_INET;
        inet_pton(AF_INET, host.c_str(), &addr4.sin_addr);
        int port = atoi(sPort.c_str());
        addr4.sin_port = htons(port);
        mPort = sPort;
        addrlen = sizeof(addr4);

        isV4 = true;

        serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    else
    {
        // IPv6
        addr6.sin6_family = AF_INET6;
        inet_pton(AF_INET6, host.c_str(), &addr6.sin6_addr);
        int port = atoi(sPort.c_str());
        addr6.sin6_port = htons(port);
        mPort = sPort;
        addrlen = sizeof(addr6);

        serverSocket = ::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    }

    if (serverSocket != -1)
    {
        int optval = 1;
        ::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (!isV4)
        {
            optval = 0;
            ::setsockopt(serverSocket, IPPROTO_IPV6, IPV6_V6ONLY, &optval, sizeof(optval));
        }

        int flags = ::fcntl(serverSocket, F_GETFL, 0);
        ::fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

        if ((::bind(serverSocket, (isV4 ? (sockaddr*)&addr4 : (sockaddr*)&addr6), addrlen) == 0)
            && (::listen(serverSocket, SOMAXCONN) == 0))
        {
            if (isV4)
            {
                ::memset(&addr4, 0, addrlen);
            }
            else
            {
                ::memset(&addr6, 0, addrlen);
            }

            if (-1 != ::getsockname(serverSocket, (isV4 ? (sockaddr*)&addr4 : (sockaddr*)&addr6), &addrlen))
            {
                mSocket[index++] = serverSocket;
                socketModeBlock(serverSocket, true);
                mProcessCond.notify_one();
                opened = true;

                LOG_VERBOSE(6) << "SocketServer::open(): Listening to " << (isV4 ? "IPv4" : "IPv6")
                               << " on port: " << mPort;
            }
            else
            {
                error("getsockname");
                ::shutdown(serverSocket, SHUT_RDWR);
                ::close(serverSocket);
            }
        }
        else
        {
            error("bind");
            ::shutdown(serverSocket, SHUT_RDWR);
            ::close(serverSocket);
        }
    }
    else
    {
        error("socket");
    }

    return opened;
}

void SocketServer::close(unsigned short code, const std::string& reason)
{
    std::lock_guard<std::mutex> locker(mProcessMutex);

    LOG_VERBOSE(6) << "SocketServer::close(): code: " << code << " reason: " << reason;

    if (mSocket[0] != -1)
    {
        socketModeBlock(mSocket[0], false);
        if (mSocket[1] != -1)
        {
            socketModeBlock(mSocket[1], false);
        }
    }
}

void SocketServer::worker()
{
    char doLoop = 1;

    int result;
    fd_set readfds, exceptfds;

    while (doLoop)
    {
        std::unique_lock<std::mutex> lock(mProcessMutex);
        if (mServerStarted)
        {
            if (mSocket[0] == -1 && mSocket[1] == -1)
            {
                mProcessCond.wait(lock);
            }
            if (mPaused)
            {
                mResumeCond.wait(lock);
            }
            if (mServerStarted)
            {
                // set file descriptors to listen for
                int fdnum = 0;
                FD_ZERO(&readfds);
                FD_ZERO(&exceptfds);
                if (mPipeFd[0] != -1)
                {
                    // pipe used to interrupt select() function, i.e. to leave thread
                    fdnum = mPipeFd[0];
                    FD_SET(mPipeFd[0], &readfds);
                    FD_SET(mPipeFd[0], &exceptfds);
                    if (mSocket[0] != -1)
                    {
                        fdnum = (int)mSocket[0] > fdnum ? (int)mSocket[0] : fdnum;
                        FD_SET(mSocket[0], &readfds);
                        FD_SET(mSocket[0], &exceptfds);
                        if (mSocket[1] != -1)
                        {
                            fdnum = (int)mSocket[1] > fdnum ? (int)mSocket[1] : fdnum;
                            FD_SET(mSocket[1], &readfds);
                            FD_SET(mSocket[1], &exceptfds);
                        }
                    }
                    fdnum++;
                }
                else
                {
                    // this part is only relevant for Windows implementation
                    FD_SET(mSocket[0], &readfds);
                    FD_SET(mSocket[0], &exceptfds);
                    if (mSocket[1] != -1)
                    {
                        FD_SET(mSocket[1], &readfds);
                        FD_SET(mSocket[1], &exceptfds);
                    }
                }
                mProcessMutex.unlock();
                result = ::select(fdnum, &readfds, NULL, &exceptfds, NULL); // block until something happens
                mProcessMutex.lock();

                if (mServerStarted)
                {
                    if (result > 0 && mPaused == 0 && 0 != m_socketServerListener)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            int sock = mSocket[i];
                            if (sock != -1 && FD_ISSET(sock, &readfds))
                            {
                                // incoming connection detected
                                LOG_VERBOSE(6)
                                    << "SocketServer new client connection to be accepted. Socket: " << std::dec
                                    << sock;

                                int sockfd = ::accept(sock, NULL, NULL);

                                if (-1 == sockfd)
                                {
                                    LOG_ERROR() << "Accept socket failed: " << ::strerror(errno);
                                }
                                else
                                {
                                    m_socketServerListener->onNewSocket(sockfd);
                                }
                            }
                        }
                    }
                }
            }
        }
        doLoop = mServerStarted;
        mProcessMutex.unlock();
    }
    mProcessMutex.lock();
    ::close(mPipeFd[0]);
    ::close(mPipeFd[1]);
    mPipeFd[0] = -1;
    mPipeFd[1] = -1;
    mProcessMutex.unlock();
}

const std::string& SocketServer::port() const
{
    return mPort;
}

const std::string& SocketServer::host() const
{
    return mHost;
}

void SocketServer::pause()
{
    std::lock_guard<std::mutex> locker(mProcessMutex);
    LOG_VERBOSE(6) << "SocketServer::pause(): Incoming connections will not be accepted now!";
    mPaused = 1;
}

void SocketServer::resume()
{
    std::lock_guard<std::mutex> locker(mProcessMutex);
    LOG_VERBOSE(6) << "SocketServer::resume(): Incoming connections will now be accepted!";
    mPaused = 0;
    mResumeCond.notify_one();
}

char SocketServer::isPaused()
{
    std::lock_guard<std::mutex> locker(mProcessMutex);

    return mPaused;
}

void SocketServer::socketModeBlock(int sockfd, bool block) const
{
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    flags = (block ? flags & ~O_NONBLOCK : flags | O_NONBLOCK);
    if (-1 == ::fcntl(sockfd, F_SETFL, flags))
    {
        error("fcntl");
    }
}

void SocketServer::error(const char* module, int errorNumber, const char* message) const
{
    LOG_ERROR() << "SocketServer ERROR(" << std::dec << errorNumber << ") in module: " << module << " : " << message;
}

void SocketServer::error(const char* module) const
{
    error(module, errno, ::strerror(errno));
}

} // namespace keo_ship
