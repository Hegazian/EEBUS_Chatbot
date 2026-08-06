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

#ifndef KEO_SHIP_STACK_TRANSPORT_SRC_WEBSOCKETPARSER_H_
#define KEO_SHIP_STACK_TRANSPORT_SRC_WEBSOCKETPARSER_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>
#include <vector>

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

/** Creates and handles WebSocket frames and opening handshake
 *
 */
class WebSocketParser
{
public:
    enum WebSocketFrameType
    {
        FrameError,
        FrameIncomplete,
        FrameOpening,
        FrameClosing,
        FrameText,
        FrameTextFin,
        FrameBinary,
        FrameBinaryFin,
        FramePing,
        FramePong,
        FrameContinuation,
        FrameContinuationFin
    };

    enum WebSocketOpcode
    {
        OpcodeContinuation = 0x00,
        OpcodeText = 0x01,
        OpcodeBinary = 0x02,
        OpcodeClose = 0x08,
        OpcodePing = 0x09,
        OpcodePong = 0x0A
    };

    WebSocketParser()
        : mClient(false)
    {
    }

    /** Returns whether the WebSocketParser is set to client or server mode.
     *
     * @return True if WebSocketParser is set to client mode
     */
    bool isClient() const
    {
        return mClient;
    }

    std::string getProtocol() const
    {
        return mProtocol;
    }

    /** Creates the client opening handshake http request and sets the
     * WebSocketParser to client mode.
     *
     * @param host  Host name of the WebSocket URI
     * @param port  Port of the WebSocket URI
     * @param resourceName The path of the WebSocket URI
     * @return The client opening handshake http request
     */
    std::string createClientOpeningHandshake(
        const std::string& host, const std::string& port, const std::string& resourceName);

    /** Validate the server opening handshake response
     *
     * @param data The http response
     *
     * @return The frame type of the http response
     * @retval FrameError Invalid response
     * @retval FrameIncomplete Not all chunks received
     * @retval FrameClosing In case of an response other than 101
     * @retval FrameOpening A valid response received
     */
    WebSocketFrameType validateServerResponse(std::vector<char>& data);

    /** Validate the client opening handshake request.
     *
     * This sets the WebSocketParser into server mode.
     *
     * @param data The http opening request
     *
     * @return The frame type of the request
     * @retval FrameError Invalid request
     * @retval FrameIncomplete Not all chunks received
     * @retval FrameOpening A valid client opening request
     */
    WebSocketFrameType validateClientOpeningHandshake(std::vector<char>& data);

    /** Creates the server opening handshake http response.
     *
     * @return The server opening handshake response
     */
    std::string createServerResponse() const;

    /** Creates a WebSocket frame with opcode close.
     *
     * @param code The status code (mandatory)
     * @param reason The reason as string
     * @return The WebSocket close frame
     */
    std::vector<char> createCloseFrame(unsigned short code, const std::string& reason);

    /** Creates a WebSocket close frame response.
     *
     * The response echos the status code it received.
     *
     * @param data The previously retrieved close frame
     * @return The WebSocket close frame response
     */
    std::vector<char> createCloseReply(const std::vector<char>& data);

    /** Parse the close frame payload and returns the status code and reason.
     *
     * @param data The close frame payload [in]
     * @param code The status code [out]
     * @param reason The reason [out]
     */
    void parseClosePayload(const std::vector<char>& data, unsigned short& code, std::string& reason);

    /** Parse a WebSocket frame.
     *
     * If the frame is valid, the data will be unmasked, if necessary, and the
     * WebSocket header will be removed. The payloadLength contains the size of the application
     * data. The method expects the start of the frame at the beginning of the data buffer.
     *
     * @param data The WebSocketFrame [in]
     * @param payloadLength Application data length [out]
     *
     * @return The frame type of the WebSocket frame
     * @retval FrameIncomplete Not all chunks received
     * @retval FrameError Invalid frame
     * @retval FrameContinuation Continuation frame
     * @retval FrameContinuationFin Final continuation frame
     * @retval FrameText Text frame, not final
     * @retval FrameTextFin Text frame with final flag set
     * @retval FrameBinary Binary frame, not final
     * @retval FrameBinaryFin Binary frame with final flag set
     * @retval FrameClosing Close frame
     * @retval FramePing Ping frame
     * @retval FramePong Pong frame
     */
    WebSocketFrameType parseFrame(std::vector<char>& data, size_t& payloadLength);

    /** Creates a WebSocket frame.
     *
     * The frame will be masked if the WebSocketParser is in client mode.
     *
     * @param bFinal Set to true if this a final frame
     * @param opcode WebSocket frame opcode
     * @param payload The application data
     * @return WebSocket frame
     */
    std::vector<char> createFrame(bool bFinal, WebSocketOpcode opcode, const std::vector<char>& payload) const;

private:
    std::string mExpectedAccept;
    std::string mProtocol;
    bool mClient;
};
}

#endif /* KEO_SHIP_STACK_TRANSPORT_SRC_WEBSOCKETPARSER_H_ */
