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

#include "WebSocketParser.h"
#include "base64/base64.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <openssl/sha.h>

#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <string>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

#define WS_SHIP_SUBPROTOCOL "ship"

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

bool normalizeAscii(const std::string& in, std::string& out)
{
    // to lower case

    char c;
    out = in;
    for (unsigned int i = 0; i < out.length(); i++)
    {
        c = out[i];
        if (c < '!' || c > '~')
        {
            return false;
        }
        if (c >= 'A' && c <= 'Z')
        {
            out[i] = c - 'A' + 'a';
        }
    }
    return true;
}

std::string readWord(int& index, const std::string& line, char delimiter = '\0', char normalize = 1)
{
    // read word of http data

    std::string word;
    while (index < (int)line.size() && line[index] == ' ')
    {
        index++;
    }
    while (index < (int)line.size() && line[index] != ' ' && line[index] != delimiter)
    {
        word.push_back(line[index++]);
    }
    index++;
    if (normalize && !normalizeAscii(word, word))
    {
        return "";
    }
    return word;
}

std::string readLine(int& index, const std::vector<char>& data)
{
    // read line of http data

    std::string line;
    while (index < (int)data.size() && data[index] != '\r')
    {
        line.push_back(data[index++]);
    }
    if (index == (int)data.size())
    {
        return line;
    }
    if (data[++index] != '\n')
    {
        return "";
    }
    index++;
    return line;
}

std::string getSecWebSocketKey()
{
    unsigned char key[16];

    srand((unsigned int)clock());
    for (int i = 0; i < (int)sizeof(key); i++)
    {
        key[i] = (unsigned char)((double)rand() / (double)RAND_MAX * (double)0xFF);
    }
    return base64_encode(key, sizeof(key));
}

std::string getSecWebSocketAccept(const std::string& key)
{
    std::string accept;

    if (key.size() < 24)
    {
        LOG_ERROR() << "Invalid key size";
        return accept; // TODO
    }
    unsigned char hash[20];
    // WesSocket Magic Number
    const std::string GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    accept = key + GUID;
    SHA1(reinterpret_cast<const unsigned char*>(accept.c_str()), accept.size(), hash);
    accept = base64_encode(hash, sizeof(hash));
    return accept;
}

std::vector<char> createMaskingKey()
{
    std::vector<char> maskingKey(4);

    srand((unsigned int)clock());
    for (int i = 0; i < 4; i++)
    {
        maskingKey[i] = (char)((double)rand() / (double)RAND_MAX * (double)0xFF);
    }

    return maskingKey;
}

void xOrData(std::vector<char>& data, const std::vector<char>& maskingKey, size_t indexBegin, size_t size)
{
    int j = 0;
    for (size_t i = indexBegin; i < size; i++, j++)
    {
        data[i] ^= maskingKey[j % 4];
    }
}

std::string WebSocketParser::createClientOpeningHandshake(
    const std::string& host, const std::string& port, const std::string& resourceName)
{
    std::string request;

    std::string secWebSocketKey = getSecWebSocketKey();
    mExpectedAccept = getSecWebSocketAccept(secWebSocketKey);

    request = "GET ";
    request.append(resourceName.empty() ? "/" : resourceName);
    request.append(" HTTP/1.1");
    request.append("\r\n");

    request.append("Host: ");
    request.append(host);
    request.append(":");
    request.append(port);
    request.append("\r\n");

    request.append("Upgrade: websocket");
    request.append("\r\n");
    request.append("Connection: Upgrade");
    request.append("\r\n");
    request.append("Sec-WebSocket-Key: ");
    request.append(secWebSocketKey);
    request.append("\r\n");
    request.append("Sec-WebSocket-Version: 13");
    request.append("\r\n");

    // only ship
    request.append("Sec-WebSocket-Protocol: ");
    request.append(WS_SHIP_SUBPROTOCOL);

    request.append("\r\n");
    request.append("\r\n");

    mClient = true;

    return request;
}

WebSocketParser::WebSocketFrameType WebSocketParser::validateServerResponse(std::vector<char>& data)
{
    if (!isClient())
        return FrameError;

    const char* crlf2 = "\r\n\r\n";
    auto it = std::search(data.begin(), data.end(), crlf2, crlf2 + ::strlen(crlf2));

    if (it != data.end())
    {
        std::string serverProtocol;
        std::string word, line;
        std::string upgrade, connection, accept;
        int indexLine = 0, indexWord = 0;

        line = readLine(indexLine, data);
        if ((word = readWord(indexWord, line)) != "http/1.1")
        {
            LOG_ERROR() << "WebSocket validate server response: Wrong Header!";
            return FrameError;
        }
        if ((word = readWord(indexWord, line)) != "101")
        {
            LOG_ERROR() << "WebSocket validate server response:  Response not 101!";
            return FrameClosing;
        }
        /*
         if ((word = readWord(indexWord, line)) != "switching")
         {
         return 0;
         }
         if ((word = readWord(indexWord, line)) != "protocols")
         {
         return 0;
         }
         */
        while (!(line = readLine(indexLine, data)).empty())
        {
            indexWord = 0;
            word = readWord(indexWord, line, ':');

            if (word == "upgrade")
            {
                upgrade = readWord(indexWord, line);
            }
            else if (word == "connection")
            {
                connection = readWord(indexWord, line);
            }
            else if (word == "sec-websocket-accept")
            {
                accept = readWord(indexWord, line, '\0', 0);
            }
            else if (word == "sec-websocket-protocol")
            {
                serverProtocol = readWord(indexWord, line);
            }
        }
        if (upgrade != "websocket" || connection != "upgrade" || accept != mExpectedAccept
            || 0 != serverProtocol.compare(WS_SHIP_SUBPROTOCOL))
        {
            LOG_ERROR() << "WebSocket validate server response: Response does not conform the requirements!";
            return FrameError;
        }
        return FrameOpening;
    }
    return FrameIncomplete;
}

WebSocketParser::WebSocketFrameType WebSocketParser::validateClientOpeningHandshake(std::vector<char>& data)
{
    if (isClient())
        return FrameError;

    const char* crlf2 = "\r\n\r\n";
    auto it = std::search(data.begin(), data.end(), crlf2, crlf2 + ::strlen(crlf2));

    if (it != data.end())
    {
        int indexLine = 0, indexWord = 0;
        std::string message, word, line, resourceName;
        std::vector<std::string> subprotocols;

        line = readLine(indexLine, data);
        if (readWord(indexWord, line) != "get")
        {
            LOG_ERROR() << "WebSocket validate client request: Wrong Header!";
            return FrameError;
        }
        resourceName = readWord(indexWord, line);
        if (resourceName[0] != '/')
        {
            LOG_ERROR() << "WebSocket validate client request: Wrong Header!";
            return FrameError;
        }
        if (readWord(indexWord, line) != "http/1.1")
        {
            LOG_ERROR() << "WebSocket validate client request: Wrong Header!";
            return FrameError;
        }
        std::string upgrade, connection, host, origin, key, protocols, version;

        while (!(line = readLine(indexLine, data)).empty())
        {
            indexWord = 0;
            word = readWord(indexWord, line, ':');

            if (word == "upgrade")
            {
                upgrade = readWord(indexWord, line);
            }
            else if (word == "connection")
            {
                connection = readWord(indexWord, line);
            }
            else if (word == "host")
            {
                host = readWord(indexWord, line);
            }
            else if (word == "origin")
            {
                origin = readWord(indexWord, line);
            }
            else if (word == "sec-websocket-key")
            {
                key = readWord(indexWord, line, '\0', 0);
            }
            else if (word == "sec-websocket-version")
            {
                version = readWord(indexWord, line);
            }
            else if (word == "sec-websocket-protocol")
            {
                while ((word = readWord(indexWord, line, ',')) != "")
                {
                    subprotocols.push_back(word);
                }
            }
            else if (word == "sec-websocket-extensions")
            {
            }
        }

        if (upgrade != "websocket" || connection != "upgrade" || version != "13" || host.empty() || subprotocols.empty()
            || key.size() < 24)
        {
            LOG_ERROR() << "WebSocket validate client request: Request does not conform the requirements!";
            return FrameError;
        }

        // find ship subprotocol
        for (size_t i = 0; i < subprotocols.size(); ++i)
        {
            if (0 == subprotocols[i].compare(WS_SHIP_SUBPROTOCOL))
            {
                mProtocol = WS_SHIP_SUBPROTOCOL;
                break;
            }
        }

        if (!mProtocol.empty())
        {
            mExpectedAccept = getSecWebSocketAccept(key);
            return FrameOpening;
        }
        else
        {
            LOG_ERROR() << "WebSocket validate client request: Subprotocol not ship or not set!";
        }

        return FrameError;
    }

    return FrameIncomplete;
}

std::string WebSocketParser::createServerResponse() const
{
    std::string response;
    response = "HTTP/1.1 101 Switching Protocols\r\n";
    response.append("Upgrade: websocket\r\n");
    response.append("Connection: Upgrade\r\n");
    response.append("Sec-WebSocket-Accept: ");
    response.append(mExpectedAccept);
    response.append("\r\n");
    if (!mProtocol.empty())
    {
        response.append("Sec-WebSocket-Protocol: ");
        response.append(mProtocol);
        response.append("\r\n");
    }
    response.append("\r\n");

    return response;
}

std::vector<char> WebSocketParser::createFrame(
    bool bFinal, WebSocketOpcode opcode, const std::vector<char>& payload) const
{
    std::vector<char> frame;

    char byte = bFinal ? 0x80 : 0x00;

    byte |= (char)opcode;
    frame.push_back(byte);

    // set masking flag
    byte = isClient() ? 0x80 : 0x00;
    if (payload.size() <= 125)
    {
        byte |= payload.size();
        frame.push_back(byte);
    }
    else if (payload.size() <= 0xFFFF)
    {
        byte |= 126;
        frame.push_back(byte);
        frame.push_back((char)(payload.size() >> 8));
        frame.push_back((char)(payload.size() >> 0));
    }
    else
    {
        byte |= 127;
        frame.push_back(byte);
        frame.push_back(0);
        frame.push_back(0);
        frame.push_back(0);
        frame.push_back(0);
        frame.push_back((char)(payload.size() >> 24));
        frame.push_back((char)(payload.size() >> 16));
        frame.push_back((char)(payload.size() >> 8));
        frame.push_back((char)(payload.size() >> 0));
    }

    std::vector<char> maskingKey;

    if (isClient())
    {
        maskingKey = createMaskingKey();
        frame.insert(frame.end(), maskingKey.begin(), maskingKey.end());
    }

    int index = frame.size();

    frame.insert(frame.end(), payload.begin(), payload.end());

    if (isClient())
    {
        xOrData(frame, maskingKey, index, frame.size());
    }

    return frame;
}

std::vector<char> WebSocketParser::createCloseFrame(unsigned short code, const std::string& reason)
{
    std::vector<char> data;

    data.push_back((char)(code >> 8));
    data.push_back((char)(code >> 0));
    data.insert(data.end(), reason.begin(), reason.end());

    return createFrame(true, WebSocketParser::OpcodeClose, data);
}

std::vector<char> WebSocketParser::createCloseReply(const std::vector<char>& data)
{
    return createFrame(true, WebSocketParser::OpcodeClose, data);
}

unsigned int getPayloadLength2(const std::vector<char>& data, int pos)
{
    unsigned int length = 0;

    length = (unsigned char)data[0 + pos];
    length <<= 8;
    length |= (unsigned char)data[1 + pos];

    return length;
}

unsigned int getPayloadLength8(const std::vector<char>& data, int pos)
{
    unsigned int length = 0;

    length = (unsigned char)data[0 + pos];
    length <<= 8;
    length |= (unsigned char)data[1 + pos];
    length <<= 8;
    length |= (unsigned char)data[2 + pos];
    length <<= 8;
    length |= (unsigned char)data[3 + pos];
    length <<= 8;
    length |= (unsigned char)data[4 + pos];
    length <<= 8;
    length |= (unsigned char)data[5 + pos];
    length <<= 8;
    length |= (unsigned char)data[6 + pos];
    length <<= 8;
    length |= (unsigned char)data[7 + pos];

    return length;
}

std::vector<char> getMaskingKey(const std::vector<char>& data, int pos)
{
    std::vector<char> maskingKey(4);

    maskingKey[0] = data[0 + pos];
    maskingKey[1] = data[1 + pos];
    maskingKey[2] = data[2 + pos];
    maskingKey[3] = data[3 + pos];

    return maskingKey;
}

WebSocketParser::WebSocketFrameType WebSocketParser::parseFrame(std::vector<char>& data, size_t& payloadLengthOut)
{
    if (data.size() < 2)
    {
        return FrameIncomplete;
    }

    unsigned char frameOpcode = data[0] & 0x0f;
    bool frameFin = ((data[0] & 0x80) == 0x80);
    bool frameMasked = ((data[1] & 0x80) == 0x80);

    size_t payloadLength = 0;

    // payload length
    int frameLength = data[1] & 0x7F;
    size_t index = 2;
    std::vector<char> maskingKey;

    if (frameLength <= 125)
    {
        payloadLength = frameLength;
    }
    else if (frameLength == 126)
    {
        if (data.size() < 5)
        {
            return FrameIncomplete;
        }
        payloadLength = getPayloadLength2(data, index);
        index += 2;
    }
    else if (frameLength == 127)
    {
        if (data.size() < 11)
        {
            return FrameIncomplete;
        }
        payloadLength = getPayloadLength8(data, index);
        index += 8;
    }

    if (frameMasked)
    {
        if (isClient())
        {
            return FrameError;
        }
        else
        {
            if (data.size() < index + 4)
            {
                return FrameIncomplete;
            }
            maskingKey = getMaskingKey(data, index);
            index += 4;
        }
    }
    else
    {
        if (!isClient())
        {
            return FrameError;
        }
    }

    DEBUG_INFO() << "WebSocketParser::parseFrame payload length! " << payloadLength << " data size " << data.size();

    if (data.size() < payloadLength + index)
    {
        return FrameIncomplete;
    }

    WebSocketFrameType retval = FrameError;

    switch (frameOpcode)
    {
        case OpcodeContinuation:
        {
            retval = (frameFin) ? FrameContinuationFin : FrameContinuation;
            break;
        }

        case OpcodeText:
        {
            retval = (frameFin) ? FrameTextFin : FrameText;
            break;
        }

        case OpcodeBinary:
        {
            retval = (frameFin) ? FrameBinaryFin : FrameBinary;
            break;
        }

        case OpcodeClose:
        {
            retval = (frameFin && (payloadLength >= 2)) ? FrameClosing : FrameError;
            break;
        }

        case OpcodePing:
        {
            retval = (frameFin) ? FramePing : FrameError;
            break;
        }

        case OpcodePong:
        {
            retval = (frameFin) ? FramePong : FrameError;
            break;
        }

        default:
        {
            break;
        }
    }

    if (retval != FrameError)
    {
        // cut off header
        data.erase(data.begin(), data.begin() + index);

        if (frameMasked)
        {
            xOrData(data, maskingKey, 0, payloadLength);
        }

        payloadLengthOut = payloadLength;
    }

    return retval;
}

void WebSocketParser::parseClosePayload(const std::vector<char>& data, unsigned short& code, std::string& reason)
{
    if (data.size() < 2)
    {
        return;
    }
    code = (unsigned char)data[0];
    code <<= 8;
    code |= (unsigned char)data[1];

    reason.insert(reason.begin(), data.begin() + 2, data.end());
}
}
