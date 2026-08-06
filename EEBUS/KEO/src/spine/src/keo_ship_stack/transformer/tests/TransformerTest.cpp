/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2014
*****************************************************************************/

#define DBG_MODUL_NAME "Transformer Test"
#include <gtest/gtest.h>
// ASSERT_TRUE
// ASSERT_EQ

#include "ShipControlTransformer.h"
#include "keo_ship/ShipHeader.h"

std::string testConnectionHello = "{\"connectionHello\":[{\"waiting\":100},{\"prolongationRequest\":true}]}";
std::string testProtocolHandshakeError = "{\"messageProtocolHandshakeError\":[{\"error\":69}]}";
std::string testProtocolHandshake = "{\"messageProtocolHandshake\":[{\"handshakeType\":\"select\"},{\"version\":[{"
                                    "\"major\":1},{\"minor\":2}]},{\"formats\":[{\"format\":[\"JSON-UTF8\"]}]}]}";

std::string testProtocolHandshakeFaulty = "{\"messageProtocolHandshake\":[{\"handshakeType\":\"select\"},{\"version\":[{"
                                    "\"major\":1},{\"minor\":2}]},{\"format\":[{\"format\":[\"JSON-UTF8\"]}]}]}";


TEST(ParserToJsonTest, ConnectionHello)
{
    std::vector<char> testJsonArray;
    testJsonArray.push_back(1);
    std::copy(testConnectionHello.begin(), testConnectionHello.end(), std::back_inserter(testJsonArray));

    keo_ship::CShipDataClass* pDataClass
        = keo_ship::ShipControlTransformer::createDataClassFromCommissioningMessage(testJsonArray);
    ASSERT_TRUE(pDataClass != NULL);
    ASSERT_EQ(pDataClass->getDataType(), keo_ship::CONNECTION_HELLO_TYPE);
    keo_ship::ConnectionHello* pConnectionHello = static_cast<keo_ship::ConnectionHello*>(pDataClass);
    ASSERT_TRUE(pConnectionHello->getWaitingIsSet());
    // ASSERT_EQ(pConnectionHello->getWaiting(),100);
    ASSERT_TRUE(pConnectionHello->getProlongationRequestIsSet());
    ASSERT_TRUE(pConnectionHello->getProlongationRequest());

    delete pDataClass;
}

TEST(ParserToJsonTest, ProtocolHandshakeError)
{
    std::vector<char> testJsonArray;
    testJsonArray.push_back(1);
    std::copy(testProtocolHandshakeError.begin(), testProtocolHandshakeError.end(), std::back_inserter(testJsonArray));

    keo_ship::CShipDataClass* pDataClass
        = keo_ship::ShipControlTransformer::createDataClassFromCommissioningMessage(testJsonArray);
    ASSERT_TRUE(pDataClass != NULL);
    ASSERT_EQ(pDataClass->getDataType(), keo_ship::MESSAGE_PROTOCOL_HANDSHAKE_ERROR_TYPE);
    keo_ship::MessageProtocolHandshakeError* pMessageProtocolHandshakeError
        = static_cast<keo_ship::MessageProtocolHandshakeError*>(pDataClass);
    ASSERT_TRUE(pMessageProtocolHandshakeError->getErrorIsSet());
    ASSERT_EQ(pMessageProtocolHandshakeError->getError(), 69);

    delete pDataClass;
}

TEST(ParserToJsonTest, ProtocolHandshake)
{
    std::vector<char> testJsonArray;
    testJsonArray.push_back(1);
    std::copy(testProtocolHandshake.begin(), testProtocolHandshake.end(), std::back_inserter(testJsonArray));

    keo_ship::CShipDataClass* pDataClass
        = keo_ship::ShipControlTransformer::createDataClassFromCommissioningMessage(testJsonArray);
    ASSERT_TRUE(pDataClass != NULL);
    ASSERT_EQ(pDataClass->getDataType(), keo_ship::MESSAGE_PROTOCOL_HANDSHAKE_TYPE);
    keo_ship::MessageProtocolHandshake* pMessageProtocolHandshake
        = static_cast<keo_ship::MessageProtocolHandshake*>(pDataClass);
    ASSERT_TRUE(pMessageProtocolHandshake->getVersionIsSet());
    ASSERT_TRUE(pMessageProtocolHandshake->getVersion().getMajorIsSet());
    ASSERT_EQ(pMessageProtocolHandshake->getVersion().getMajor(), 1);
    ASSERT_TRUE(pMessageProtocolHandshake->getVersion().getMinorIsSet());
    ASSERT_EQ(pMessageProtocolHandshake->getVersion().getMinor(), 2);
    ASSERT_TRUE(pMessageProtocolHandshake->getFormatsIsSet());
    ASSERT_TRUE(pMessageProtocolHandshake->getFormats().getFormat().size() > 0);
    ASSERT_EQ(pMessageProtocolHandshake->getFormats().getFormat().at(0), "JSON-UTF8");

    std::vector<char> jsonMessage;
    bool ready = keo_ship::ShipControlTransformer::getJsonFromDataClass(pDataClass, jsonMessage, 1);
    ASSERT_TRUE(ready);

    std::string jsonString(jsonMessage.begin() + 1, jsonMessage.end());
    ASSERT_EQ(testProtocolHandshake, jsonString);

    delete pDataClass;
}

TEST(ParserToJsonTest, ProtocolHandshakeFaulty)
{
    std::vector<char> testJsonArray;
    testJsonArray.push_back(1);
    std::copy(testProtocolHandshakeFaulty.begin(), testProtocolHandshakeFaulty.end(), std::back_inserter(testJsonArray));

    keo_ship::CShipDataClass* pDataClass
        = keo_ship::ShipControlTransformer::createDataClassFromCommissioningMessage(testJsonArray);
    ASSERT_TRUE(pDataClass == NULL);
}

TEST(ParserFromJsonTest, Construct)
{
    std::vector<char> testJsonArray;
    testJsonArray.push_back(1);
    std::copy(testConnectionHello.begin(), testConnectionHello.end(), std::back_inserter(testJsonArray));

    keo_ship::CShipDataClass* pDataClass
        = keo_ship::ShipControlTransformer::createDataClassFromCommissioningMessage(testJsonArray);
    ASSERT_TRUE(pDataClass != NULL);
    ASSERT_EQ(pDataClass->getDataType(), keo_ship::CONNECTION_HELLO_TYPE);

    std::vector<char> jsonMessage;
    bool ready = keo_ship::ShipControlTransformer::getJsonFromDataClass(pDataClass, jsonMessage, 1);
    ASSERT_TRUE(ready);

    std::string jsonString(jsonMessage.begin() + 1, jsonMessage.end());
    //    ASSERT_EQ(testConnectionHello.replace(' ',''),jsonString.replace('\n','').replace(' ','').replace('\t',''));
    ASSERT_EQ(testConnectionHello, jsonString);

    delete pDataClass;
}
