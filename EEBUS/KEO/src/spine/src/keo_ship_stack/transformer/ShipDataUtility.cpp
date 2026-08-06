/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "JsonBuilder.h"

// from ShipStack
#include "JsonParser.h"
#include "ShipDataUtility.h"

#define DBG_MODULE_NAME "ShipDataUtility"

using namespace keo_ship;

const char* JSON_DATA_MESSAGE_START = "\2{\"data\":[{\"header\":[{";

ShipDataUtility::ShipDataUtility()
    : m_keyString()
    , m_jsonParser()
{
}

std::size_t ShipDataUtility::findDatagramEnd(const std::vector<char>& c_jsonArray, std::size_t startPayload)
{
    if (startPayload < c_jsonArray.size())
    {
        std::vector<char>::const_iterator iter = c_jsonArray.begin() + startPayload;
        std::vector<char>::const_iterator iterEnd = c_jsonArray.end();
        int count = 1;
        bool isInsideString = false;
        for (; iter != iterEnd; ++iter)
        {
            if (*iter == '\"')
            {
                isInsideString = !isInsideString;
            }
            else if (isInsideString == false && *iter == '{')
            {
                count++;
            }
            else if (isInsideString == false && *iter == '}')
            {
                count--;
                if (count == 0)
                {
                    return iter - c_jsonArray.begin() + 1;
                }
            }
        }
    }
    return 0;
}

bool ShipDataUtility::createShipDataMessageFromJson(const std::vector<char>& c_jsonArray, keo_ship::Data*& pDataMessage)
{
    if (!c_jsonArray.size() || c_jsonArray[0] != 2)
    {
        return false;
    }
    size_t index = 1;
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_OBJECT)
    {
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::KEY_NAME)
    { // data
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_ARRAY)
    {
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_OBJECT)
    {
        return false;
    }
    JsonParser::JsonToken token = m_jsonParser.nextToken(c_jsonArray, index);
    if (token != JsonParser::KEY_NAME)
    { //
        return false;
    }
    m_keyString = m_jsonParser.getCurrentString();
    if (m_keyString.compare("header") != 0)
    {
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_ARRAY)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_OBJECT)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::KEY_NAME)
    {
        return false;
    }
    if (m_jsonParser.getCurrentString().compare("protocolId"))
    {
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::VALUE_STRING)
    { //
        return false;
    }
    if (m_jsonParser.getCurrentString().compare("ee1.0"))
    {
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::END_OBJECT)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::END_ARRAY)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::END_OBJECT)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_OBJECT)
    { //
        return false;
    }
    keo_ship::Header header;
    header.setProtocolId("ee1.0");
    pDataMessage->setHeader(header);
    token = m_jsonParser.nextToken(c_jsonArray, index);
    if (token != JsonParser::KEY_NAME)
    { //
        return false;
    }
    m_keyString = m_jsonParser.getCurrentString();
    if (m_keyString.compare("payload") != 0)
    {
        return false;
    }
    std::size_t end = findDatagramEnd(c_jsonArray, index);

    m_jsonParser.reset();

    if (index >= end || end > c_jsonArray.size())
    {
        return false;
    }
    std::vector<char> payloadJson;
    keo_ship::Payload payload;

    std::copy(c_jsonArray.begin() + index + 1, c_jsonArray.begin() + end - 1, std::back_inserter(payloadJson));

    payload.setPayload(payloadJson);
    pDataMessage->setPayload(payload);

    index = end;
    token = m_jsonParser.nextToken(c_jsonArray, index);

    if (token != JsonParser::START_OBJECT && token != JsonParser::END_ARRAY)
    { //
        return false;
    }
    token = m_jsonParser.nextToken(c_jsonArray, index);
    if (token == JsonParser::END_OBJECT)
    { //
        if (m_jsonParser.nextToken(c_jsonArray, index) == JsonParser::END_PARSING)
        {
            return true;
        }
        return false;
    }
    if (token != JsonParser::KEY_NAME)
    { //
        return false;
    }
    m_keyString = m_jsonParser.getCurrentString();

    if (m_keyString.compare("extension") != 0)
    {
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_ARRAY)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::START_OBJECT)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::KEY_NAME)
    {
        return false;
    }
    do
    {
        if (m_jsonParser.getCurrentString().compare("extensionId") == 0)
        {
            if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::VALUE_STRING)
            { //
                return false;
            }
            keo_ship::Extension extension = pDataMessage->getExtension();
            extension.setExtensionId(m_jsonParser.getCurrentString());
            pDataMessage->setExtension(extension);
        }
        else if (m_jsonParser.getCurrentString().compare("binary") == 0)
        {
            if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::VALUE_STRING)
            { //
                return false;
            }
            keo_ship::Extension extension = pDataMessage->getExtension();
            extension.setBinary(m_jsonParser.getCurrentString());
            pDataMessage->setExtension(extension);
        }
        else if (m_jsonParser.getCurrentString().compare("string") == 0)
        {
            if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::VALUE_STRING)
            { //
                return false;
            }
            keo_ship::Extension extension = pDataMessage->getExtension();
            extension.setString(m_jsonParser.getCurrentString());
            pDataMessage->setExtension(extension);
        }
        token = m_jsonParser.nextToken(c_jsonArray, index);
        if (token != JsonParser::END_OBJECT)
        { //
            return false;
        }
        token = m_jsonParser.nextToken(c_jsonArray, index);
        if (token != JsonParser::START_OBJECT)
        { //
            if (token != JsonParser::END_ARRAY)
            { //
                return false;
            }
            break;
        }
        token = m_jsonParser.nextToken(c_jsonArray, index);
    } while (token == JsonParser::KEY_NAME);
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::END_OBJECT)
    { //
        return false;
    }
    if (m_jsonParser.nextToken(c_jsonArray, index) != JsonParser::END_ARRAY)
    { //
        return false;
    }

    return true;
}

bool ShipDataUtility::getJsonFromMessageData(const keo_ship::Data& c_messageData, std::vector<char>& r_jsonArray)
{
    r_jsonArray.clear();
    r_jsonArray.insert(r_jsonArray.end(), (char*)JSON_DATA_MESSAGE_START,
        (char*)JSON_DATA_MESSAGE_START + strlen(JSON_DATA_MESSAGE_START));
    JsonBuilder::writeValueString("protocolId", c_messageData.getHeader().getProtocolId(), r_jsonArray);
    JsonBuilder::writeObjectEnd(r_jsonArray);
    JsonBuilder::writeArrayEnd(r_jsonArray);
    JsonBuilder::writeObjectEnd(r_jsonArray);
    JsonBuilder::writeObjectBegin(r_jsonArray);
    JsonBuilder::writeKey("payload", r_jsonArray);
    const std::vector<char> eebusJson = c_messageData.getPayload().getPayload();
    if (eebusJson.size() == 0)
    {
        r_jsonArray.clear();
        return false;
    }
    std::copy(eebusJson.begin(), eebusJson.end(), std::back_inserter(r_jsonArray));
    JsonBuilder::writeObjectEnd(r_jsonArray);
    if (c_messageData.getExtensionIsSet())
    {
        JsonBuilder::writeObjectBegin(r_jsonArray);
        JsonBuilder::writeKey("extension", r_jsonArray);
        JsonBuilder::writeArrayBegin(r_jsonArray);
        if (c_messageData.getExtension().getExtensionIdIsSet())
        {
            JsonBuilder::writeObjectBegin(r_jsonArray);
            JsonBuilder::writeValueString("extensionId", c_messageData.getExtension().getExtensionId(), r_jsonArray);
            JsonBuilder::writeObjectEnd(r_jsonArray);
        }
        if (c_messageData.getExtension().getBinaryIsSet())
        {
            JsonBuilder::writeObjectBegin(r_jsonArray);
            JsonBuilder::writeValueString("binary", c_messageData.getExtension().getBinary().toString(), r_jsonArray);
            JsonBuilder::writeObjectEnd(r_jsonArray);
        }
        if (c_messageData.getExtension().getStringIsSet())
        {
            JsonBuilder::writeObjectBegin(r_jsonArray);
            JsonBuilder::writeValueString("string", c_messageData.getExtension().getString(), r_jsonArray);
            JsonBuilder::writeObjectEnd(r_jsonArray);
        }
        JsonBuilder::writeArrayEnd(r_jsonArray);
        JsonBuilder::writeObjectEnd(r_jsonArray);
    }
    r_jsonArray.pop_back();
    r_jsonArray.push_back(']');
    r_jsonArray.push_back('}');
    return true;
}
