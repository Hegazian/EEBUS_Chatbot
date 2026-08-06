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

#ifndef KEO_SHIP_STACK_TRANSPORT_SRC_WEBSOCKET_H_
#define KEO_SHIP_STACK_TRANSPORT_SRC_WEBSOCKET_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "WebSocketParser.h"
#include "tls/OpenSSLConnection.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_ship/Uri.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <condition_variable>
#include <mutex>
#include <signal.h>
#include <string>
#include <thread>
#include <vector>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

#define KEO_WEBSOCKET_BUFFER_SIZE (8 * 1024)

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship
{

class SecureConnection;
class WebSocket;

class WebSocketHandler
{
public:
    /** WebSocket opcodes for message frames */
    enum Opcode
    {
        OpcodeText = 0x01,
        OpcodeBinary = 0x02,
        OpcodeClose = 0x08,
        OpcodeContinuation = 0x00,
        OpcodePing = 0x09,
        OpcodePong = 0x0A
    };

    virtual ~WebSocketHandler()
    {
    }

    /** WebSocket connection is closed
     *
     * @param client The pointer on the WebSocket object
     * @param code Status code
     * @param reason Reason as string
     */
    virtual void onClose(WebSocket* client, unsigned short code, const std::string& reason) = 0;

    /** WebSocket frame received.
     *
     * @param client The pointer on the WebSocket object
     * @param opcode WebSocket frame opcode
     * @param data Application data
     * @param dataSize Application data size
     * @param bFinal True if WebSocket final frame flag is set
     */
    virtual void onMessage(
        WebSocket* client, Opcode opcode, const std::vector<char>& data, size_t dataSize, bool bFinal)
        = 0;
};

class WebSocket
{
public:
    /** WebSocket states */
    enum WebSocketState
    {
        Closed, //!< Initial state
        Connecting, //!< Establish a WebSocket connection
        Closing, //!< WebSocket closing procedure ongoing
        Open, //!< WebSocket Connection is established
        Failed //!< WebSocket upgrade failed
    };

    explicit WebSocket(WebSocketHandler* handler);
    ~WebSocket();

    /** Initializes the WebSocket.
     */
    bool initialize();

    /** Finalizes the WebSocket.
     */
    void finalize();

    /** Opens a WebSocket connection from client side
     *
     * @param secureConnection The connection to be used
     * @param destinationURI URI of connection
     *
     * @return True if successful
     */
    bool openClient(OpenSSLConnection* secureConnection, const Uri& destinationURI);

    /** Opens a WebSocket connection from server side; intended to be used only by the WebSocketServer
     *
     * @param secureConnection The connection to be used
     *
     * @return True if successful
     */
    bool openServer(OpenSSLConnection* secureConnection);

    /** Closes a WebSocket connection
     *
     * @param code Status code
     * @param reason An arbitrary string describing the reason
     */
    void close(unsigned short code, const std::string& reason = "");

    /** Creates and sends a WebSocket frame.
     *
     * @param opcode WebSocket opcode
     * @param data Application data
     * @param bFinal Set to true if this is the final frame
     *
     * @return True if successful
     */
    bool send(WebSocketHandler::Opcode opcode, const std::vector<char>& data, bool bFinal = true);

    /** Returns the WebSocket state..
     *
     * @return WebSocket state
     */
    WebSocketState getState() const;

    /** Returns the used WebSocket subprotocol.
     *
     * @return webSocket subprotocol
     */
    std::string getProtocol() const;

    /** Returns the (pure) IP address of the peer
     *
     * @return IPv6/IPv4 address of the peer as string
     */
    std::string getPeerIp() const;

    /** Returns the port number of the peer.
     *
     * @return Port number of the peer.
     */
    int getPeerPort() const;

    /** Retrieve information, if the current connection is
     * an outgoing or incoming one.
     * @return
     */
    bool isOutgoingConnection() const;

private:
    WebSocket();

    bool writeData(const std::vector<char>& buf);
    int readData(char* buf, size_t bufsize, int timeoutInMSec);

    void processReceive(void);

    bool handleDataStateClosing(std::vector<char>& data);
    bool handleDataStateOpen(std::vector<char>& data);
    void processSocketClose(unsigned short code, const std::string& reason);

    bool waitAndHandleServerResponse();
    bool waitAndHandleClientOpening();

    void setPeerAddress();

private:
    WebSocketState mWebSocketState;

    std::string mPort;

    WebSocketHandler* mHandler;

    std::string mPeerIp;
    int mPeerPort;

    unsigned short code;
    std::string reason;

    OpenSSLConnection* mSecureConnection;

    mutable std::recursive_mutex mProcessMutex;

    std::thread mProcessReceiveThread;
    std::condition_variable_any mProcessReceiveCond;

    bool processReceiverClosing;

    WebSocketParser webSocketParser;

    // Timeout to wait for a free write buffer.
    // If the timeout occurs the writeData method returns an error.
    static const int waitForWriteBufferMs = 1000;
};

} // namespace keo_ship

#endif /* KEO_SHIP_STACK_TRANSPORT_SRC_WEBSOCKET_H_ */
