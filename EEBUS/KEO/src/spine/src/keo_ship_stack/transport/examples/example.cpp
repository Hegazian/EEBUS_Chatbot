#include <stdio.h>

#include "WebSocket.h"
#include "SocketServer.h"

#ifdef USE_SSL
#include "ShipTLSSecurity.h"
#endif

using namespace keo_ship;

int wsProtocol(void* userData, const WebSocket* client, const std::vector<std::string>& protocols)
{
    (void)userData;
    (void)client;
    (void)protocols;
    printf("wsProtocol\n");
    return 0;
};

void wsConnect(void* userData, WebSocket* client, const std::string& protocol)
{
    (void)userData;
    (void)client;
    (void)protocol;
    printf("wsConnect %s\n", protocol.c_str());
}

void wsClose(void* userData, WebSocket* client, unsigned short code, const std::string& reason)
{
    (void)userData;
    (void)client;
    (void)code;
    (void)reason;
    printf("wsClose 0x%x %s\n", code, reason.c_str());
};

void wsError(void* userData, WebSocket* client, const std::string& description)
{
    (void)userData;
    (void)client;
    (void)description;
};

void wsMessage(void* userData, WebSocket* client, WebSocket::Opcode opcode, const std::vector<char>& data, char bFinal)
{
    (void)userData;
    (void)data;
    printf("wsMessage 0x%x %i\n", (int)opcode, bFinal);

    std::vector<char> msg;
    client->send(WebSocket::OpcodePong, msg);
    client->close(1234, "REASON");
};

void clientHandlerConnect(void* userData, WebSocket* client, const std::string& protocol)
{
    (void)userData;
    printf("clientHandlerConnect %s\n", protocol.c_str());

    std::vector<char> msg;
    msg.push_back(0x10);
    client->send(WebSocket::OpcodePing, msg);
};

void clientHandlerClose(void* userData, WebSocket* client, unsigned short code, const std::string& reason)
{
    (void)userData;
    (void)client;
    (void)code;
    (void)reason;
    printf("clientHandlerClose 0x%x %s\n", code, reason.c_str());
};

void clientHandlerError(void* userData, WebSocket* client, const std::string& description)
{
    (void)userData;
    (void)client;
    (void)description;
};

void clientHandlerMessage(
    void* userData, WebSocket* client, WebSocket::Opcode opcode, const std::vector<char>& data, char bFinal)
{
    (void)userData;
    (void)client;
    (void)data;
    printf("clientHandlerMessage 0x%x %i\n", (int)opcode, bFinal);
};
#define CERTFILE_SERVER std::string(PEM_DIRECTORY) + "/secp256r1Cert.pem"
#define KEYFILE_SERVER std::string(PEM_DIRECTORY) + "/secp256r1Key.pem"
#define CERTFILE_CLIENT std::string(PEM_DIRECTORY) + "/secp256r1Cert.pem"
#define KEYFILE_CLIENT std::string(PEM_DIRECTORY) + "/secp256r1Key.pem"

class SecurityCallbackClass : public ShipSecurity::CallbackHandler
{
public:
    SecurityCallbackClass()
    {
    }

    int PublicKeyAndCert(void* pUserCtx, const unsigned char* pPublicKey, size_t publicKeyLength,
        const unsigned char* pCert, size_t certLength)
    {
        return 1;
    }
    int onSslSessionNegotiated(void* pUserCtx, void* pSslSession, size_t sessionLength,
        const unsigned char* pSslSessionId, size_t sslSessionIdLength)
    {
        return 1;
    }

    void* onGetSslSession(void* pUserCtx, const unsigned char* pSslSessionId, size_t sslSessionIdLength)
    {
        return NULL;
    }
};

int main(int argc, char* argv[])
{
    argc = 0;
    argv = NULL;

    // unused args
    (void)argc;
    (void)argv;

    SecurityCallbackClass tmpClass;

#ifdef USE_SSL
    keo_ship::SecurityDataOwnInterface shipSecurityDataClient;
    shipSecurityDataClient.certPemFilePath = std::string(CERTFILE_CLIENT);
    shipSecurityDataClient.privateKeyPemFilePath = std::string(KEYFILE_CLIENT);

    keo_ship::SecurityDataOwnInterface shipSecurityDataServer;
    shipSecurityDataServer.certPemFilePath = std::string(CERTFILE_SERVER);
    shipSecurityDataServer.privateKeyPemFilePath = std::string(KEYFILE_SERVER);

    ShipSecurity shipSecurityClient(&tmpClass, shipSecurityDataClient);
    ShipSecurity shipSecurityServer(&tmpClass, shipSecurityDataServer);

#else
    void* shipSecurityServer = NULL;
#endif

    WebSocketServer* server = new WebSocketServer(wsProtocol, wsConnect, wsClose, wsError, wsMessage, &tmpClass);
    if (!server->open("localhost", "5000", &shipSecurityServer))
    {
        return 0;
    }

    WebSocket* client = new WebSocket(wsConnect, wsClose, wsError, wsMessage, &tmpClass);
    client->init();
    std::vector<std::string> protocols;
    protocols.push_back("ship");
    client->open("localhost", "5000", "", protocols, &shipSecurityClient);

    while (1)
    {
        client->process();
        server->process();
    }

    client->close();
    server->close();

    delete client;
    delete server;

    return 0;
}
