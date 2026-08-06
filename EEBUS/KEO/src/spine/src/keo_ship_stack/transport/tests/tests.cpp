#include "gtest/gtest.h"

#include "WebSocket.h"
#include "WebSocketServer.h"
#include <time.h>

#include "WebSocketUtility.h"

using namespace keo_ship;

void* gUserData = NULL;
WebSocket* gClient = NULL;
std::vector<std::string> gProtocols;
int gProtocolIndex = 0;
std::string gProtocol;
unsigned short gCode = 0;
std::string gReason;
std::string gDescription;
WebSocket::Opcode gOpcode;
std::vector<char> gData;
char gFinal;

char gServerProtocol;
char gServerConnect;
char gServerError;
char gServerMessage;
char gServerClose;

char gClientConnect;
char gClientError;
char gClientMessage;
char gClientClose;

int serverHandlerProtocol(
    void* userData, WebSocket* client, const std::string& path, const std::vector<std::string>& protocols)
{
    (void)path;

    gUserData = userData;
    gClient = (WebSocket*)client;
    gProtocols = protocols;
    gServerProtocol = 1;
    return gProtocolIndex;
};

void serverHandlerConnect(void* userData, WebSocket* client, const std::string& protocol)
{
    gUserData = userData;
    gClient = client;
    gProtocol = protocol;
    gServerConnect = 1;
}

void serverHandlerClose(void* userData, WebSocket* client, unsigned short code, const std::string& reason)
{
    gUserData = userData;
    gClient = client;
    gCode = code;
    gReason = reason;
    gServerClose = 1;
};

void serverHandlerError(void* userData, WebSocket* client, const std::string& description)
{
    gUserData = userData;
    gClient = client;
    gDescription = description;
    gServerError = 1;
};

void serverHandlerMessage(
    void* userData, WebSocket* client, WebSocket::Opcode opcode, const std::vector<char>& data, char bFinal)
{
    gUserData = userData;
    gClient = client;
    gOpcode = opcode;
    gData = data;
    gFinal = bFinal;
    gServerMessage = 1;
};

void clientHandlerConnect(void* userData, WebSocket* client, const std::string& protocol)
{
    gUserData = userData;
    gClient = client;
    gProtocol = protocol;
    gClientConnect = 1;
};

void clientHandlerClose(void* userData, WebSocket* client, unsigned short code, const std::string& reason)
{
    gUserData = userData;
    gClient = client;
    gCode = code;
    gReason = reason;
    gClientClose = 1;
};

void clientHandlerError(void* userData, WebSocket* client, const std::string& description)
{
    gUserData = userData;
    gClient = client;
    gDescription = description;
    gClientError = 1;
};

void clientHandlerMessage(
    void* userData, WebSocket* client, WebSocket::Opcode opcode, const std::vector<char>& data, char bFinal)
{
    gUserData = userData;
    gClient = client;
    gOpcode = opcode;
    gData = data;
    gFinal = bFinal;
    gClientMessage = 1;
};

class WebSocketsTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        mServer = new WebSocketServer(serverHandlerProtocol, serverHandlerConnect, serverHandlerClose,
            serverHandlerError, serverHandlerMessage, this);
        mServer->init();
        mClients[0]
            = new WebSocket(clientHandlerConnect, clientHandlerClose, clientHandlerError, clientHandlerMessage, this);
        mClients[0]->init();
        mClients[1]
            = new WebSocket(clientHandlerConnect, clientHandlerClose, clientHandlerError, clientHandlerMessage, this);
        mClients[1]->init();
        mClients[2]
            = new WebSocket(clientHandlerConnect, clientHandlerClose, clientHandlerError, clientHandlerMessage, this);
        mClients[2]->init();
        mClients[3]
            = new WebSocket(clientHandlerConnect, clientHandlerClose, clientHandlerError, clientHandlerMessage, this);
        mClients[3]->init();

        gServerProtocol = 0;
        gServerConnect = 0;
        gServerError = 0;
        gServerMessage = 0;
        gServerClose = 0;

        gClientConnect = 0;
        gClientError = 0;
        gClientMessage = 0;
        gClientClose = 0;
    }

    virtual void TearDown()
    {
        delete mClients[3];
        delete mClients[2];
        delete mClients[1];
        delete mClients[0];
        delete mServer;
    }
    char waitOnHandler(char& handlerCalled)
    {
        time_t t = time(NULL);
        while (!handlerCalled && time(NULL) < t + 60)
        {
        }
        char result = handlerCalled;
        handlerCalled = 0;
        return result;
    }

    WebSocketServer* mServer;
    WebSocket* mClients[4];
};

unsigned char encodeSrc[][16] = { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
    { 255, 254, 253, 252, 251, 250, 249, 248, 247, 246 }, { 12, 18, 0, 11, 158, 111, 87, 200, 211, 76 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 } };

char encodeDst[][25] = { "AAECAwQFBgcICQAAAAAAAA==", "//79/Pv6+fj39gAAAAAAAA==", "DBIAC55vV8jTTAAAAAAAAA==",
    "AAAAAAAAAAAAAAAAAAAAAA==", "/////////////wAAAAAAAA==" };

char encodeSha1[][29] = { "ulXtrabWUR7Gw0gYiSpg6CQedtw=", "zDQu/am7TrjqmabyDTjbjwfak8Q=",
    "Fjk4IjYJqC07caFTCYkDs6CvyJc=", "l9/3W2wImePAoJsQRElC0pNA900=", "nolQg3Sj2fsgn3OrB5YrucFrnV4=" };

TEST_F(WebSocketsTest, ConnectWrongPort)
{
    mServer->open("localhost", "5002");
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    char result = mClients[0]->open("localhost", "", "10", "", protocols);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(waitOnHandler(gClientClose), 1);
    // mClients[0]->close();
    mServer->close();
}

TEST_F(WebSocketsTest, ConnectWsSyntaxError)
{
    mServer->open("localhost", "5003");
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    char result = mClients[0]->open("localhost", "", "5003", "abc", protocols);
    EXPECT_EQ(result, 1);
    mClients[0]->close();
    mServer->close();
}

TEST_F(WebSocketsTest, ConnectionSuccessful)
{
    mServer->open("localhost", "5005");
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    char result = mClients[0]->open("localhost", "", "5005", "", protocols);
    gProtocolIndex = 0;
    result &= waitOnHandler(gServerProtocol);
    result &= waitOnHandler(gServerConnect);
    WebSocket* serverClient = gClient;
    result &= waitOnHandler(gClientConnect);
    result &= gProtocol == "ship" ? 1 : 0;
    EXPECT_EQ(result, 1);

    std::vector<char> data;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodePing, data);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodePing ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodePong, data);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodePong ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeText, data, 0);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodeText ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodeText, data, 0);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodeText ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodeContinuation ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodeContinuation ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeBinary, data, 0);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodeBinary ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodeBinary, data, 0);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodeBinary ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodeContinuation ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodeContinuation ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gServerClose);
    result &= waitOnHandler(gClientClose);

    EXPECT_EQ(result, 1);
    mClients[0]->close();
    mServer->close();
}

TEST_F(WebSocketsTest, Encode)
{
    std::string result;
    for (unsigned int i = 0; i < sizeof(encodeSrc) / sizeof(encodeSrc[0]); i++)
    {
        result = base64_encode(encodeSrc[i], sizeof(encodeSrc[i]));
        EXPECT_TRUE(result == std::string(encodeDst[i]));
    }
}

TEST_F(WebSocketsTest, SHA)
{
    std::string result;
    unsigned char hash[20];

    for (unsigned int i = 0; i < sizeof(encodeSrc) / sizeof(encodeSrc[0]); i++)
    {
        sha1_calc(encodeDst[i], sizeof(encodeDst[i]) - 1, hash);
        result = base64_encode(hash, sizeof(hash));
        EXPECT_TRUE(result == std::string(encodeSha1[i]));
    }
}

TEST_F(WebSocketsTest, ConnectNoProtocol)
{
    mServer->open("localhost", "5000");
    std::vector<std::string> protocols;
    char result = mClients[0]->open("localhost", "", "5000", "", protocols);
    EXPECT_EQ(result, 0);

    mClients[0]->close();
    mServer->close();
}

TEST_F(WebSocketsTest, ConnectWrongHost)
{
    mServer->open("localhost", "5001");
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    char result = mClients[0]->open("ocalhost", "", "5001", "", protocols);

    EXPECT_EQ(result, 1);
    EXPECT_EQ(waitOnHandler(gClientClose), 1);
    // mClients[0]->close();
    mServer->close();
}

TEST_F(WebSocketsTest, ConnectionRefused)
{
    mServer->open("localhost", "5004");
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    mClients[0]->open("localhost", "", "5004", "", protocols);
    gProtocolIndex = -1;

    EXPECT_EQ(waitOnHandler(gServerProtocol), 1);
    EXPECT_EQ(waitOnHandler(gServerClose), 1);
    EXPECT_EQ(waitOnHandler(gClientClose), 1);
    mClients[0]->close();
    mServer->close();
}

TEST_F(WebSocketsTest, ContinuationFrames)
{
    mServer->open("localhost", "5005");
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    char result = mClients[0]->open("localhost", "", "5005", "", protocols);
    gProtocolIndex = 0;
    result &= waitOnHandler(gServerProtocol);
    result &= waitOnHandler(gServerConnect);
    WebSocket* serverClient = gClient;
    result &= waitOnHandler(gClientConnect);
    result &= gProtocol == "ship" ? 1 : 0;
    EXPECT_EQ(result, 1);

    std::vector<char> data;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeText, data, 0);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodeText ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodeText, data, 0);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodeText ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x12);
    mClients[0]->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gServerMessage);
    result &= gOpcode == WebSocket::OpcodeContinuation ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    data.clear();
    data.push_back(0x45);
    serverClient->send(WebSocket::OpcodeContinuation, data, 1);
    result &= waitOnHandler(gClientMessage);
    result &= gOpcode == WebSocket::OpcodeContinuation ? 1 : 0;
    result &= gData[0] == data[0] ? 1 : 0;

    mClients[0]->close();
    mServer->close();
}
