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

#ifndef KEO_SHIP_STACK_SOCKETSERVER_H_
#define KEO_SHIP_STACK_SOCKETSERVER_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

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

class SocketServerListener
{
public:
    virtual ~SocketServerListener()
    {
    }

    virtual void onNewSocket(int sockfd) = 0;
};

class SocketServer
{
public:
    explicit SocketServer(SocketServerListener* socketServerListener);
    virtual ~SocketServer();

    bool start();
    void stop();

    void join();

    bool open(const std::string& host, const std::string& port);
    void close(unsigned short code, const std::string& reason);

    const std::string& port() const;
    const std::string& host() const;

    void pause();
    void resume();

    bool isStarted() const;

    char isPaused();

private:
    SocketServer();

    void error(const char* module, int errorNumber, const char* message) const;
    void error(const char* module) const;

    void worker();

    void socketModeBlock(int sockFd, bool block) const;

    SocketServerListener* m_socketServerListener;
    char mPaused;

    std::string mPort;
    std::string mHost;
    int mSocket[2]; // Array was intentionally created
    // to support separate sockets for IPv4 and IPv6.
    // Currently not used anymore, one socket for IPv4 and IPv6
    // or one socket used for IPv4 only.
    mutable std::mutex mProcessMutex;
    char mServerStarted;
    std::condition_variable mProcessCond;
    std::condition_variable mResumeCond;
    int mPipeFd[2];

    std::thread thread;
};

} // namespace keo_ship

#endif
