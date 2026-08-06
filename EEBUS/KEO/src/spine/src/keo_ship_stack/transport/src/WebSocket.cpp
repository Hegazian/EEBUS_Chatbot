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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <WebSocket.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

#define OPENING_HANDSHAKE_TIMEOUT (10 * 1000)
#define CLOSING_HANDSHAKE_TIMEOUT (5 * 1000)
#define READ_SOCKET_TIMEOUT (5 * 1000)

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

WebSocket::WebSocket(WebSocketHandler* handler)
    : mWebSocketState(Closed)
    , mPort()
    , mHandler(handler)
    , mPeerIp()
    , mPeerPort(0)
    , code(0)
    , mProcessMutex()
    , mProcessReceiveThread()
    , mProcessReceiveCond()
    , processReceiverClosing(false)

{
    mSecureConnection = nullptr;
}

WebSocket::~WebSocket()
{
    DEBUG_FUNC();
    finalize();
}

bool WebSocket::initialize()
{
    return true;
}

void WebSocket::finalize()
{
    DEBUG_FUNC();

    std::unique_lock<std::recursive_mutex> locker(mProcessMutex);
    if (mWebSocketState != Closed)
    {
        DEBUG_INFO() << "WebSocket: Shutdown receiver thread";

        if (nullptr != mSecureConnection && -1 != mSecureConnection->get_fd())
        {
            mSecureConnection->socketModeBlock(false);
            mSecureConnection->close();
        }

        mSecureConnection = nullptr;

        mWebSocketState = Closed;
    }

    if (mProcessReceiveThread.joinable())
    {
        mProcessReceiveCond.notify_one();

        locker.unlock();
        mProcessReceiveThread.join();
        locker.lock();
    }
}

bool WebSocket::openClient(OpenSSLConnection* secureConnection, const Uri& destinationURI)
{
    DEBUG_FUNC();
    bool result = false;
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);

    if (mWebSocketState == Closed)
    {
        mWebSocketState = Connecting;

        mSecureConnection = secureConnection;

        std::string host = destinationURI.getHost();
        mPort = std::to_string(destinationURI.getPort());

        // send opening handshake to the server
        std::string mHttpRequest = webSocketParser.createClientOpeningHandshake(host, mPort, destinationURI.getPath());

        if (writeData(std::vector<char>(mHttpRequest.begin(), mHttpRequest.end())))
        {
            if (waitAndHandleServerResponse())
            {
                mWebSocketState = Open;

                setPeerAddress();
                result = true;

                mProcessReceiveThread = std::thread(&WebSocket::processReceive, this);
            }
            else
            {
                result = false;
                mWebSocketState = Failed;
            }
        }
        else
        {
            result = false;
            mWebSocketState = Failed;
        }
    }
    else
    {
        LOG_WARN() << "WebSocket::open(): Socket state not 'CLOSED'";
    }

    return result;
}

bool WebSocket::waitAndHandleServerResponse()
{
    DEBUG_FUNC();

    char receiveBuffer[KEO_WEBSOCKET_BUFFER_SIZE];
    std::vector<char> data;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = begin;

    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    while (elapsed < OPENING_HANDSHAKE_TIMEOUT)
    {
        int result = readData(receiveBuffer, sizeof receiveBuffer, OPENING_HANDSHAKE_TIMEOUT - elapsed);

        end = std::chrono::steady_clock::now();

        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        if (result > 0)
        {
            data.insert(data.end(), receiveBuffer, &receiveBuffer[result]);

            switch (webSocketParser.validateServerResponse(data))
            {
                case WebSocketParser::FrameError:
                case WebSocketParser::FrameClosing:
                {
                    LOG_ERROR() << "Cannot handle HTTP response '" << std::string(data.begin(), data.end()) << "'";
                    return false;
                }

                case WebSocketParser::FrameOpening:
                {
                    DEBUG_INFO() << "Opening handshake received";
                    return true;
                }

                case WebSocketParser::FrameIncomplete:
                {
                    DEBUG_INFO() << "Incomplete or no data!";
                    break;
                }

                default:
                    break;
            }
        }
        else if (result == 0)
        {
            continue; // poll timeout - try again
        }
        else
        {
            return false;
        }
    }

    LOG_WARN() << "WebSocket opening handshake timeout!";
    return false;
}

bool WebSocket::openServer(OpenSSLConnection* secureConnection)
{
    DEBUG_FUNC();
    bool result = false;
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);

    if (mWebSocketState == Closed)
    {
        mWebSocketState = Connecting;

        mSecureConnection = secureConnection;

        if (waitAndHandleClientOpening())
        {
            mWebSocketState = Open;

            setPeerAddress();
            result = true;

            mProcessReceiveThread = std::thread(&WebSocket::processReceive, this);
        }
        else
        {
            result = false;
            mWebSocketState = Failed;
        }
    }

    return result;
}

bool WebSocket::waitAndHandleClientOpening()
{
    DEBUG_FUNC();

    char receiveBuffer[KEO_WEBSOCKET_BUFFER_SIZE];
    std::vector<char> data;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = begin;

    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    while (elapsed < OPENING_HANDSHAKE_TIMEOUT)
    {
        int result = readData(receiveBuffer, sizeof receiveBuffer, OPENING_HANDSHAKE_TIMEOUT - elapsed);

        end = std::chrono::steady_clock::now();

        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        if (result > 0)
        {
            data.insert(data.end(), receiveBuffer, &receiveBuffer[result]);

            switch (webSocketParser.validateClientOpeningHandshake(data))
            {
                case WebSocketParser::FrameError:
                case WebSocketParser::FrameClosing:
                {
                    LOG_ERROR() << "Cannot handle HTTP request '" << std::string(data.begin(), data.end()) << "'";
                    return false;
                }

                case WebSocketParser::FrameOpening:
                {
                    DEBUG_INFO() << "Opening handshake received. Sending response.";

                    std::string response = webSocketParser.createServerResponse();
                    return writeData(std::vector<char>(response.begin(), response.end()));
                }

                case WebSocketParser::FrameIncomplete:
                {
                    DEBUG_INFO() << "Incomplete or no data!";
                    break;
                }

                default:
                    break;
            }
        }
        else if (result == 0)
        {
            continue; // poll timeout - try again
        }
        else
        {
            return false;
        }
    }

    LOG_WARN() << "WebSocket opening handshake timeout!";
    return false;
}

void WebSocket::close(unsigned short code, const std::string& reason)
{
    std::unique_lock<std::recursive_mutex> lock(mProcessMutex);

    if (mWebSocketState != Closed && mWebSocketState != Closing && mWebSocketState != Failed)
    {
        LOG_DEBUG() << "Close connection " << std::dec << code << " " << reason;

        this->code = code;
        this->reason = reason;

        mWebSocketState = Closing;
        if (!writeData(webSocketParser.createCloseFrame(code, reason)))
        {
            LOG_INFO() << "Send close frame failed!";
        }
        // close frame send; wait for response and close the connection
        // wait for the thread to post the semaphore
        while (!processReceiverClosing)
        {
            mProcessReceiveCond.wait(lock);
        }

        // with finalize set the state to close, release the ssl socket and take care
        // receiver thread is terminated.
        finalize();
    }
}

bool WebSocket::send(WebSocketHandler::Opcode opcode, const std::vector<char>& data, bool bFinal)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);

    if (mWebSocketState != Open)
    {
        LOG_WARN() << "WebSocket::send(): Connection not open!";
        return false;
    }

    return writeData(webSocketParser.createFrame(bFinal, (WebSocketParser::WebSocketOpcode)opcode, data));
}

bool WebSocket::writeData(const std::vector<char>& buf)
{
    int ret = -1;
    size_t dataWritten = 0;

    if (!buf.empty())
    {
        struct pollfd fd;
        fd.fd = mSecureConnection->get_fd();
        fd.events = POLLOUT | POLLRDHUP | POLLHUP | POLLNVAL;

        mProcessMutex.unlock();
        ret = ::poll(&fd, 1, waitForWriteBufferMs);
        mProcessMutex.lock();

        if (ret > 0)
        {
            if (fd.revents & POLLOUT)
            {
                dataWritten = 0;
                while (dataWritten < buf.size())
                {
                    size_t bytes_to_send
                        = std::min(static_cast<size_t>(KEO_WEBSOCKET_BUFFER_SIZE), buf.size() - dataWritten);
                    mProcessMutex.unlock();
                    ret = mSecureConnection->write(static_cast<void const*>(&(buf[dataWritten])), bytes_to_send);
                    mProcessMutex.lock();
                    if (ret > 0)
                    {
                        dataWritten += ret;
                    }
                    else if (!mSecureConnection->noError(ret))
                    {
			LOG_WARN() << "END" << dataWritten << buf.size();
                        break;
                    }
                }
            }
        }
    }
    if(!(dataWritten == buf.size()))
    {
	LOG_WARN() << "Could not write all bytes " << dataWritten << " of " << buf.size();
    }
    return (dataWritten == buf.size());
}

int WebSocket::readData(char* buf, size_t bufsize, int timeoutInMSec)
{
    DEBUG_FUNC();

    if (mSecureConnection->pending())
    {
        return mSecureConnection->read(buf, bufsize);
    }

    struct pollfd fd;
    fd.fd = mSecureConnection->get_fd();
    fd.events = POLLIN | POLLRDHUP | POLLHUP | POLLNVAL;

    int ret = ::poll(&fd, 1, timeoutInMSec);

    if (ret == -1)
    {
        LOG_WARN() << "Poll error: " << ::strerror(errno);
    }
    else if (ret == 0)
    {
        DEBUG_INFO() << "Poll timeout";
    }
    else if (ret > 0)
    {
        if (fd.revents & (POLLPRI | POLLOUT | POLLRDHUP | POLLERR | POLLHUP | POLLNVAL))
        {
            ret = -1;
            LOG_WARN() << "Poll error 0x" << std::hex << fd.revents << std::dec;
        }
        else if (fd.revents & POLLIN)
        {
            DEBUG_INFO() << "POLLIN";
            ret = mSecureConnection->read(buf, bufsize);
            DEBUG_INFO() << "Read data ret: " << ret;
        }
    }
    else
    {
        DEBUG_INFO() << "Unexpected result from poll: " << ret;
        ret = -1;
    }

    return ret;
}

void WebSocket::processReceive()
{

    char receiveBuffer[KEO_WEBSOCKET_BUFFER_SIZE];
    std::vector<char> data;

    std::unique_lock<std::recursive_mutex> locker(mProcessMutex);

    while (!processReceiverClosing && mSecureConnection && (mSecureConnection->get_fd() != -1))
    {
        int result;
        locker.unlock();
        result = readData(receiveBuffer, sizeof receiveBuffer, READ_SOCKET_TIMEOUT);
        locker.lock();

        DEBUG_INFO() << "WebSocket::processReceive(): read data " << result;

        if (result >= 0)
        {
            // handle data even in case of poll timeout
            // the method handleDataStateOpen takes care if the websocket shall be closed
            data.insert(data.end(), receiveBuffer, &receiveBuffer[result]);

            if (!handleDataStateOpen(data))
            {
                if (handleDataStateClosing(data))
                {
                    processSocketClose(code, reason);
                }
                else
                {
                    // wrong state
                    processSocketClose(1006, "General Error!");
                }
                processReceiverClosing = true;
            }
        }
        else
        {
            if (mWebSocketState == Open)
            {
                processSocketClose(1006, "Local Socket Error");
            }
            else if (mWebSocketState == Closing)
            {
                processSocketClose(code, reason);
            }
            processReceiverClosing = true;
        }
    }

    processReceiverClosing = true;
    mProcessReceiveCond.notify_one();
}

void WebSocket::processSocketClose(unsigned short code, const std::string& reason)
{
    LOG_TRACE() << "WebSocket::processSocketClose(): Closing socket with code: " << std::dec << code
                << " reason: " << reason;

    if (mWebSocketState == Closed)
    {
        return;
    }

    mSecureConnection->close();
    mWebSocketState = Closed;

    mProcessMutex.unlock();
    mHandler->onClose(this, code, reason);
    mProcessMutex.lock();
}

bool WebSocket::handleDataStateClosing(std::vector<char>& data)
{
    if (mWebSocketState == Closing)
    {
        DEBUG_INFO() << "WebSocket::handleData(): Handle frame data state closing";

        bool loop = true;

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end = begin;

        do
        {
            size_t payloadLength = 0;
            switch (webSocketParser.parseFrame(data, payloadLength))
            {
                case WebSocketParser::FrameClosing:
                {
                    DEBUG_INFO() << "Closing frame received";
                    webSocketParser.parseClosePayload(data, code, reason);
                    loop = false;
                    break;
                }

                case WebSocketParser::FrameError:
                {
                    LOG_WARN() << "Frame error in close handshake. Closing anyway!";
                    loop = false;
                    break;
                }

                case WebSocketParser::FrameIncomplete:
                {
                    DEBUG_INFO() << "Incomplete frame or no data  received!";
                    break;
                }

                default:
                {
                    // Ignore all other frames
                    data.erase(data.begin(), data.begin() + payloadLength);
                    break;
                }
            }

            int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

            if (loop && elapsed < CLOSING_HANDSHAKE_TIMEOUT)
            {
                char receiveBuffer[KEO_WEBSOCKET_BUFFER_SIZE];

                int result = readData(receiveBuffer, sizeof receiveBuffer, CLOSING_HANDSHAKE_TIMEOUT - elapsed);

                end = std::chrono::steady_clock::now();

                if (result > 0)
                {
                    data.insert(data.end(), receiveBuffer, &receiveBuffer[result]);
                }
                else if (result == 0)
                {
                    continue; // poll timeout - try again
                }
                else
                {
                    loop = false;
                }
            }
            else
            {
                loop = false;
            }

        } while (loop);

        return true;
    }

    return false;
}

bool WebSocket::handleDataStateOpen(std::vector<char>& data)
{
    if (mWebSocketState == Open)
    {
        // handle incoming frame data
        DEBUG_INFO() << "WebSocket::handleData(): Handle frame data";

        size_t payloadLength = 0;
        bool finalFrame = true;

        switch (webSocketParser.parseFrame(data, payloadLength))
        {
            case WebSocketParser::FrameIncomplete:
            {
                DEBUG_INFO() << "WebSocket incomplete frame or no data received!";
                break;
            }

            case WebSocketParser::FrameBinary:
            {
                finalFrame = false;
            }
                // fall through
                // no break

            case WebSocketParser::FrameBinaryFin:
            {
                DEBUG_INFO() << "Binary frame received";

                mProcessMutex.unlock();
                mHandler->onMessage(this, WebSocketHandler::OpcodeBinary, data, payloadLength, finalFrame);
                mProcessMutex.lock();

                data.erase(data.begin(), data.begin() + payloadLength);
                break;
            }

            case WebSocketParser::FrameClosing:
            {
                DEBUG_INFO() << "Closing frame received";

                mWebSocketState = Closing;
                // write close response
                writeData(
                    webSocketParser.createCloseReply(std::vector<char>(data.begin(), data.begin() + payloadLength)));

                webSocketParser.parseClosePayload(data, code, reason);
                processSocketClose(code, reason);
                break;
            }

            case WebSocketParser::FramePing:
            {
                DEBUG_INFO() << "Ping frame received";

                mProcessMutex.unlock();
                mHandler->onMessage(this, WebSocketHandler::OpcodePing, data, payloadLength, true);
                mProcessMutex.lock();

                data.erase(data.begin(), data.begin() + payloadLength);
                break;
            }

            case WebSocketParser::FramePong:
            {
                DEBUG_INFO() << "Pong frame received";

                mProcessMutex.unlock();
                mHandler->onMessage(this, WebSocketHandler::OpcodePong, data, payloadLength, true);
                mProcessMutex.lock();

                data.erase(data.begin(), data.begin() + payloadLength);
                break;
            }

            case WebSocketParser::FrameContinuation:
            {
                DEBUG_INFO() << "Continuation frame received";
                finalFrame = false;
            }
                // fall through
                // no break

            case WebSocketParser::FrameContinuationFin:
            {
                DEBUG_INFO() << "ContinuationFin frame received";

                mProcessMutex.unlock();
                mHandler->onMessage(this, WebSocketHandler::OpcodeContinuation, data, payloadLength, finalFrame);
                mProcessMutex.lock();

                data.erase(data.begin(), data.begin() + payloadLength);
                break;
            }

            case WebSocketParser::FrameError:
            default:
            {
                LOG_WARN() << "WebSocket frame error! Closing connection";
                code = 1002;
                reason = "Frame Error!";
                mWebSocketState = Closing;
                writeData(webSocketParser.createCloseFrame(code, reason));
                break;
            }
        }

        return true;
    }

    return false;
}

int WebSocket::getPeerPort() const
{
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);
    return (mPeerPort);
}

std::string WebSocket::getPeerIp() const
{
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);
    return (mPeerIp);
}

bool WebSocket::isOutgoingConnection() const
{
    return webSocketParser.isClient();
}

WebSocket::WebSocketState WebSocket::getState() const
{
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);
    return mWebSocketState;
}

std::string WebSocket::getProtocol() const
{
    std::lock_guard<std::recursive_mutex> locker(mProcessMutex);
    return webSocketParser.getProtocol();
}

void WebSocket::setPeerAddress()
{
    sockaddr_storage name;
    socklen_t nameLen = sizeof(name);
    ::memset(&name, 0, nameLen);
    char ipstr[INET6_ADDRSTRLEN];

    if (::getpeername(mSecureConnection->get_fd(), (sockaddr*)&name, &nameLen) == 0)
    {
        if (name.ss_family == AF_INET)
        { // IPv4
            struct sockaddr_in* s = (struct sockaddr_in*)&name;
            mPeerPort = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        }
        else
        { // IPv6
            struct sockaddr_in6* s = (struct sockaddr_in6*)&name;
            mPeerPort = ntohs(s->sin6_port);
            inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
        }
        mPeerIp = ipstr;
    }
    else
    {
        LOG_WARN() << "sock_getpeername failed";
    }
}

} // namespace keo_ship
