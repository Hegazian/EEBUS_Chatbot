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
/**
 *     @brief Ship Stack
 *              Smart Home IP (SHIP) describes an IP based approach for interoperable connectivity of smart
 *              home appliances, which covers local SHIP nodes in the smart home as well as SHIP web
 *              services and remote SHIP nodes.
 *
 *     @par        The Ship Stack
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_STACK_SHIPSTACK_H_
#define KEO_SHIP_STACK_STACK_SHIPSTACK_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_ship/Uri.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <list>
#include <memory>
#include <mutex>
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

/**
 * @addtogroup ship
 * @{
 */

/**
 * @defgroup ship_stack Stack
 *
 * Smart Home IP (SHIP) stack API.
 * Implements functions and callbacks for data message transfer and connection handling to other nodes.
 *
 * Callback order (simplified, see SHIP Specification for details)
 * ---------------------------------------------------------------
 * onConnect()
 * onTrustCertificate()
 * onDataExchangeEnabled()
 * onMessage()
 * onClose()
 *
 * Please note that, depending on the situation, not all callbacks are necessarily called.
 * This might depend on e.g. if it is an incoming or an outgoing connection.
 *
 * @{
 */

/**
 * Result codes used by the SHIP stack
 */
enum ShipStackResult
{
    StackResultOk = 0, /**< Everything is ok */
    StackResultGeneralError, /**< General error */
    StackResultSkiError /**< SKI Error */
};

/**
 * PIN requirement needed for authentication of nodes
 */
typedef enum
{
    PIN_NONE = 0, /**< No PIN required */
    PIN_OK = 1, /**< A valid PIN has been entered before */
    PIN_OPTIONAL = 2, /**< A PIN is not required but can be entered for an increased trust level */
    PIN_REQUIRED = 3, /**< A PIN has to be entered for the connection to be established */
    ALL_PIN_REQUIREMENTS_NUMBER,
} PinRequirement;

/**
 * @cond HIDDEN_SYMBOLS
 */
struct ShipMessageExchangeListener
{
    virtual ~ShipMessageExchangeListener() = default;
    virtual void onConnect() = 0;
    virtual void onClose(int status, const std::string& reason) = 0;
    virtual void onCloseAnnounce(int maxTimeMilliSeconds, bool isRemovedConnection) = 0;
    virtual void onCloseAnnounceConfirm() = 0;
    virtual void onDataExchangeEnabled() = 0;
    virtual void onMessage(const std::vector<char>& message) = 0;
    virtual unsigned short onTrustCertificate(const std::string& ski, const X509Certificate& certificate) = 0;
    virtual unsigned short onValidatePin(const std::string& pin) = 0;
    virtual void onPinRequest() = 0;
    virtual void onPinRecallTimeout() = 0;
    virtual void onPinWrong() = 0;
};
class ShipMessageExchange;
// for internal use
class SocketConnectionHandler;
// for internal use
/**
 * @endcond
 */

/**
 * @class ShipNode
 * A SHIP node is a logical device which communicates via the described SHIP protocol.
 * The ShipNode class represents the remotely connected device and the connection in between.
 */
class ShipNode : public ShipMessageExchangeListener
{

public:
    /**
     * Constructs an empty ship Node.
     */
    ShipNode();

    /**
     * Destructor releasing all ressources.
     */
    virtual ~ShipNode();

    /**
     * Callback method issued on connect. At this stage a secure WebSocket
     * connection has been established. SHIP Message Exchange (SME) has not yet
     * been started, i.e. SHIP data messages can not yet be exchanged.
     *
     * @see onDataExchangeEnabled
     */
    virtual void onConnect() = 0;

    /**
     * Callback method that indicates that the connection to the remote ship node is closed.
     *
     * @param status
     *            WebSocket status code
     * @param reason
     *            description
     */
    virtual void onClose(int status, const std::string& reason) = 0;

    /**
     * Callback method that announces the connection to be closed.
     * On confirmation the connection will be closed immediately.
     *
     * @see closeAnnounce
     *
     * @param maxTimeMilliSeconds
     *            the maximum time in milliseconds
     * @param isRemovedConnection
     *            indicates whether a connection has been removed by the peer
     *
     * @see closeAnnounceConfirm
     */
    virtual void onCloseAnnounce(int maxTimeMilliSeconds, bool isRemovedConnection)
    {
        (void)maxTimeMilliSeconds;
        (void)isRemovedConnection;
    }

    /**
     * Callback method that indicates that the peer has confirmed the
     * announcement of closing a connection.
     *
     * @see closeAnnounceConfirm
     * @see onCloseAnnounce
     */
    virtual void onCloseAnnounceConfirm()
    {
    }

    /**
     * Immediately closes the connection to this node.
     *
     * @see onClose
     */
    void close();

    /**
     * Announces a connection to be closed.
     *
     * @see onCloseAnnounce
     *
     * @param maxTimeMilliSeconds
     *            maximum time in milliseconds
     * @param isRemovedConnection
     *            true iff connection will be removed
     *
     */
    void closeAnnounce(int maxTimeMilliSeconds, bool isRemovedConnection);

    /**
     * Confirms an announcement of a connection to be closed. Upon confirmation
     * the peer will immediately close the connection.
     *
     * @see onCloseAnnounce
     */
    void closeAnnounceConfirm();

    /**
     * Callback method that indicates that SHIP data messages can now be exchanged.
     * @see sendMessage
     * @see onMessage
     */
    virtual void onDataExchangeEnabled()
    {
    }

    /**
     * Sends a SHIP message to the peer.
     * @see onDataExchangeEnabled
     * @param message
     *            message payload
     *
     * @return true if message has been sent successfully
     */
    bool sendMessage(const std::vector<char>& message);

    /**
     * Callback for an incoming SHIP data message.
     *
     * @param message
     *            the payload of a SHIP message.
     */
    virtual void onMessage(const std::vector<char>& message)
    {
        (void)message;
    }

    /**
     * Callback to set the user trust level of a certificate/SHIP connection. This callback is not invoked when the
     * certificate has been trusted before.
     *
     * When this method returns a trust level larger than 0, this value is stored using the {@link
     * ShipSecurityHandler} passed to the SHIP stack.
     *
     * It might be necessary, according to the SHIP specification, to set a
     * penalty time using {@link #setPinPenaltyTime(long)} on
     * the connection to avoid brute-force attacks. Refer to the SHIP
     * specification to learn which penalty times are valid.
     *
     * @param ski
     *            the SKI of the certificate
     * @param certificate
     *            the certificate of the remote end
     * @return the new user trust level
     */
    virtual unsigned short onTrustCertificate(const std::string& ski, const X509Certificate& certificate)
    {
        (void)ski;
        (void)certificate;
        return TrustLevel::TRUST_VALUE_USER_UNTRUSTED;
    }

    /**
     * Callback to check whether a received PIN is valid is to set the Second Factor trust of a
     * certificate/SHIP connection.
     *
     * When this method returns a trust level larger than 0, this value is stored using the {@link
     * ShipSecurityHandler} passed to the SHIP stack.
     *
     * If the PIN is not valid, it might be necessary, according to the SHIP
     * specification, to set a penalty time using
     * {@link #setPinPenaltyTime(long)} on the connection to
     * avoid brute-force attacks. Refer to the SHIP specification to learn which
     * penalty times are valid.
     *
     * @param pin
     *            the received PIN
     * @return the new second factor trust level
     */
    virtual unsigned short onValidatePin(const std::string& pin)
    {
        (void)pin;
        return TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
    }

    /**
     * Gets trust level of the node
     *
     * The trust level expresses the trust in a certain communication partner over generic values.
     * The higher the values the stronger is the trust in the corresponding communication partner.
     * The trust level consists of different categories, which include different mechanisms and permit
     * a differentiated view of the trustworthiness of a communication partner.
     *
     * @return trust level of the node
     */
    TrustLevel getTrustLevel() const;

    /**
     * Get the PIN requirement of this connection.
     *
     * @return PIN requirement of this connection
     */
    PinRequirement getPinRequirement() const;

    /**
     * Set a PIN on this connection. To be used when the remote end of this connection request a PIN.
     * This will transmit the PIN to the remote end for validation.
     *
     * A PIN can be used for authentication (independent of TLS) to
     * improve the trust level. E.g. if only auto accept was used by a SHIP node in the first
     * authentication step, which only offers a relatively low trust level, a PIN can be used to reach
     * mutual authentication and e.g. enable commissioning.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     *
     * @param pin
     *            the PIN to set
     */
    void setPin(const std::string& pin);

    /**
     * Set a penalty time for this connection. The remote end has to wait that time before it can enter another PIN.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     */
    void setPinPenaltyTime(long penaltyTime);

    /**
     * Callback to announce that the remote end of a SHIP connection is requesting a PIN.
     * To enter a PIN, use {@link #setPin()}.
     * Use {@link #getPinRequirement()} to check whether the PIN is optional or required.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     */
    virtual void onPinRequest()
    {
    }

    /**
     * Callback to announce that the remote end of a connection did not enter a PIN in time.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     */
    virtual void onPinRecallTimeout()
    {
    }

    /**
     * Callback to announce that the last PIN entered on a connection has been rejected by the receiver.
     * This is called at both endpoints of the connection.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     */
    virtual void onPinWrong()
    {
    }

    /**
     * Get the SKI of the remote node represented by this instance.
     *
     * Each SHIP node has a specific public key. The Subject Key Identifier (SKI) is derived from
     * this public key and is used as cryptographically backed identification and authentication
     * criterion
     *
     * @return SKI of the node.
     */
    std::string getSki() const;

    /**
     * Get the IP address of the connection to the remote node represented by this instance.
     *
     * @return IP address of the node.
     */
    std::string getIpAddress() const;

    /**
     * Get the IP port of the connection to the remote node represented by this instance.
     *
     * @return IP port of the node.
     */
    int getIpPort() const;

    /**
     * Get the id of the remote node represented by this instance.
     *
     * Each SHIP node has a global unique SHIP ID.
     * The SHIP ID is used to uniquely identify a SHIP node.
     * <b>Important:</b>
     * The transport ID is not known before the onDataExchangeEnabled() callback
     * has been called for this connection. Accordingly getId() should not be called
     * before this callback has been seen.
     *
     * @return ID of the node.
     */
    std::string getId() const;

    /**
     * Indicates the role (client or server) of this node instance.
     *
     * Ship notes can act as client or server.
     * The SHIP client role shall be assigned to the SHIP node that also embodies the TCP client
     * role for a specific peer to peer connection.
     * The SHIP server role shall be assigned to the SHIP node that also embodies the TCP server
     * role for a specific peer to peer connection
     *
     * @return true if node is client, false in case of server
     */
    bool isClient() const;

private:
    friend class SocketConnectionHandler;

    /**
     * for internal use: used by connection handler
     */
    ShipMessageExchange* getMessageExchange()
    {
        return shipMessageExchange;
    }

    static const int CLOSE_STATUS_CODE_USER_CLOSE;
    static const std::string CLOSE_REASON_USER_CLOSE;

    ShipMessageExchange* shipMessageExchange;
};

//! typedef for non-const smart pointer type ShipNode
typedef std::shared_ptr<ShipNode> ShipNodePtr;

//! typedef for const type ShipNode
typedef const ShipNode ShipNodeConst;

//! typedef for const smart pointer type ShipNode
typedef std::shared_ptr<ShipNodeConst> ShipNodeConstPtr;

/**
 * @class ShipNodeFactory
 * The SHIP node factory implements a factory pattern to creates ship nodes.
 * This enable the user to create derived ShipNode instances.
 */
class ShipNodeFactory
{
public:
    /**
     * Destructor releasing all ressources.
     */
    virtual ~ShipNodeFactory() = default;

    class MinimalShipNode : public ShipNode
    {
    public:
        virtual void onConnect()
        {
        }

        virtual void onClose(int status, const std::string& reason)
        {
            (void)status;
            (void)reason;
        }
    };

    /**
     * Create a new instance of a minimal ship node.
     * @return shared pointer to the ship node.
     */
    virtual ShipNodePtr createShipNode()
    {
        return ShipNodePtr(new MinimalShipNode());
    }
};

//! typedef for non-const smart pointer type ShipNodeFactory
typedef std::shared_ptr<ShipNodeFactory> ShipNodeFactoryPtr;

//! typedef for const type ShipNodeFactory
typedef const ShipNodeFactory ShipNodeFactoryConst;

//! typedef for const smart pointer type ShipNodeFactory
typedef std::shared_ptr<ShipNodeFactoryConst> ShipNodeFactoryConstPtr;

/**
 * SHIP protocol configurations
 */
class ProtocolConfig
{
public:
    /**
     * Construct a ProtocolConfig with default values.
     */
    ProtocolConfig();
    virtual ~ProtocolConfig() = default;

    /**
     * Check if the received SHIP version is in the space of the own device version
     * @return
     *        true, if the SHIP version fits
     */
    static bool isVersionValid(uint16_t versionMajor, uint16_t versionMinor);

    /**
     * Try to match the config SHIP version with the received one
     * @return
     *        true, if the SHIP version are matched
     */
    static bool agreedVersion(uint16_t& versionMajor, uint16_t& versionMinor);

    // config of the SHIP versions
    /** major SHIP version number part */
    static uint16_t SHIP_VERSION_MAJOR;
    /** minor SHIP version number part */
    static uint16_t SHIP_VERSION_MINOR;
    /** major minimum SHIP version number part */
    static uint16_t SHIP_MIN_VERSION_MAJOR;
    /** minor minimum SHIP version number part */
    static uint16_t SHIP_MIN_VERSION_MINOR;

    /** Supported protocol formats (sorted) */
    static std::vector<std::string> PROTOCOL_FORMATS;

    uint8_t getMaximumHelloAllowProlongationRequests() const;
    void setMaximumHelloAllowProlongationRequests(uint8_t maximumHelloAllowProlongationRequests);
    uint32_t getMinimumHelloWaitForReadyForProlongation() const;
    void setMinimumHelloWaitForReadyForProlongation(uint32_t minimumHelloWaitForReadyForProlongation);
    uint32_t getTimeoutCmi() const;
    void setTimeoutCmi(uint32_t timeoutCmi);
    uint32_t getTimeoutHandshakeWaitForReady() const;
    void setTimeoutHandshakeWaitForReady(uint32_t timeoutHandshakeWaitForReady);
    uint32_t getTimeoutHelloProlongationWaiting() const;
    void setTimeoutHelloProlongationWaiting(uint32_t timeoutHelloProlongationWaiting);
    uint32_t getTimeoutHelloWaitForReady() const;
    void setTimeoutHelloWaitForReady(uint32_t timeoutHelloWaitForReady);
    uint32_t getTimeoutPinAskInit() const;
    void setTimeoutPinAskInit(uint32_t timeoutPinAskInit);
    uint32_t getTimeoutPinRecall() const;
    void setTimeoutPinRecall(uint32_t timeoutPinRecall);
    uint32_t getTimeoutPinState() const;
    void setTimeoutPinState(uint32_t timeoutPinState);

private:
    static bool isBetween(int value, int min, int max);

    // Timeouts of the SHIP message exchange
    uint32_t timeoutCmi; // 10 to 30 sec
    uint32_t timeoutHelloWaitForReady; // 60 sec
    uint32_t minimumHelloWaitForReadyForProlongation; // 30 sec
    uint8_t maximumHelloAllowProlongationRequests; // 2 times
    uint32_t timeoutHelloProlongationWaiting; // 0.5 times of timeout_HELLO_Wait_for_ready (=> max = 1.5 times)
    uint32_t timeoutHandshakeWaitForReady; // 10 sec
    uint32_t timeoutPinRecall; // 120 sec
    uint32_t timeoutPinAskInit; // 10 sec
    uint32_t timeoutPinState; // 30 sec to 120 sec
};

/**
 * @class ShipStackConfiguration
 * Stores all needed configuration data used by the ShipStack class
 * @see ShipStack
 */
class ShipStackConfiguration
{
    //!< default session cache size
    static const long DEFAULT_SESSION_CACHE_SIZE = 250;

public:
    /**
     * Constructs an instance
     */
    ShipStackConfiguration()
        : shipId()
        , pin()
        , pinRequirement(PinRequirement::PIN_NONE)
        , sessionCacheSize(DEFAULT_SESSION_CACHE_SIZE)
    {
    }

    /**
     * Get configured unique ship identifier.
     *
     * @see ShipNode::getId
     *
     *@return the unique ship identifier.
     */
    const std::string& getShipId() const
    {
        return shipId;
    }

    /**
     * Set the unique ship identifier.
     *
     * @see ShipNode::getId
     *
     *@param shipId The unique ship identifier.
     */
    void setShipId(const std::string& shipId)
    {
        this->shipId = shipId;
    }

    /**
     * Get configured PIN.
     *
     * @see ShipNode::getId
     *
     * @return the PIN.
     */
    const std::string& getPin() const
    {
        return pin;
    }

    /**
     * Set configured PIN.
     *
     * @see ShipNode::getId
     *
     * @param pin the PIN.
     */
    void setPin(const std::string& pin)
    {
        this->pin = pin;
    }

    /**
     * Get configured PIN requirement.
     * @return the PIN requirement.
     */
    PinRequirement getPinRequirement() const
    {
        return pinRequirement;
    }

    /**
     * Set the PIN requirement.
     * @param pinRequirement the PIN requirement.
     */
    void setPinRequirement(PinRequirement pinRequirement)
    {
        this->pinRequirement = pinRequirement;
    }

    /**
     * Get the SHIP protocol configuration.
     * @return the protocol configuration
     */
    const ProtocolConfig& getProtocolConfig() const
    {
        return protocolConfig;
    }

    /**
     * Set the SHIP protocol configuration.
     * @param protocolConfig the protocol configuration
     */
    void setProtocolConfig(const ProtocolConfig& protocolConfig)
    {
        this->protocolConfig = protocolConfig;
    }

    /** Sets the size of the internal session cache of the OpenSSL context and the
     * size of the client cache to t.
     *
     * This value is a hint and not an absolute value. Old sessions will be removed when the next
     * time a session shall be added. This removal is not synchronized with the expiration of
     * sessions.
     *
     * Set to 0 to disable session caching.
     *
     * @param t Session cache size.
     */
    void setSessionCacheSize(std::uint32_t t)
    {
        sessionCacheSize = t;
    }

    /** Returns the session cache size.
     * @return Session cache size.
     */
    long getSessionCacheSize() const
    {
        return sessionCacheSize;
    }

private:
    std::string shipId;
    std::string pin;
    PinRequirement pinRequirement;
    ProtocolConfig protocolConfig;
    std::uint32_t sessionCacheSize;
};

class ShipStackPriv;

/**
 * @class ShipStack
 * Smart Home IP (SHIP) describes an IP based approach for interoperable connectivity of smart
 * home appliances, which covers local SHIP nodes in the smart home as well as SHIP web
 * services and remote SHIP nodes.
 * The ShipStack class implements the main entry point for SHIP connections, security and other functionalities.
 */
class ShipStack final
{
public:
    /**
     * Creates an instance of the ShipStack.
     *
     * @param shipStackConfiguration
     *            Configuration parameters.
     * @param shipSecurityData
     *            Security handler to use by the stack.
     * @param shipNodeCreator
     *            Factory to create (derived) ship nodes.
     * @see ShipNode
     */
    ShipStack(ShipStackConfiguration shipStackConfiguration, SecurityHandlerPtr shipSecurityData,
        ShipNodeFactoryPtr shipNodeCreator);

    /**
     * Destructor
     */
    ~ShipStack();

    /**
     * Initializes stack and all needed ressources.
     * @return StackResultOk on success
     */
    ShipStackResult initialize();

    /**
     * Shutdown the stack.
     * @return StackResultOk on success
     */
    ShipStackResult shutdown();

    /**
     * Get the SKI of the local node.
     *
     * Each SHIP node has a specific public key. The Subject Key Identifier (SKI) is derived from
     * this public key and is used as cryptographically backed identification and authentication
     * criterion
     *
     * @return SKI
     */
    std::string getSki() const;

    /**
     * Checks whether a node is connected.
     *
     * @param ski
     *            SKI of node to check
     *
     * @return true iff node is connected
     */
    bool isConnected(const std::string& ski) const;

    /**
     * Initializes server part, to configure port and host list for the websocket server.
     *
     * Each entry in the host list represents one network interface. It is enough to specify
     * one address of an interface. The SHIP server will be reachable via all addresses
     * of that interface.
     *
     * @param hosts
     *            string list of all hosts to use
     * @param serverPort
     *            TCP/IP port to use
     * @param socketPath
     *            WebSocket path, e.g. /ship/
     */
    void initializeServer(const std::list<std::string>& hosts, int serverPort, const std::string& socketPath);

    /**
     * Starts the websocket server and listens for connections.
     * @return True if start was successful.
     */
    bool startServer();

    /**
     * Joins terminated server.
     * Wait for all server to be closed.
     */
    void serverJoin();

    /**
     * Stops server, and listening on ports for connections.
     */
    void stopServer();

    /**
     * Indicates if the websocket server is running.
     * @return True if server is started.
     */
    bool isServerStarted() const;

    /**
     * Connects to a remote node, i.e. initiates a client connection to the given uri.
     *
     * @param uri
     *            Secure WebSocket uri
     */
    bool connectTo(const Uri& uri);

    /**
     * Sets the connection handling behavior.
     *
     * By default the server accepts all new connection. To reject any further
     * connection, set 'rejectConnections' to true.
     *
     * @param rejectConnections
     *            Set to true to reject any further incoming connection.
     */
    void setRejectConnections(bool rejectConnections);

private:
    ShipStack(const ShipStack& rhs);

    ShipStackPriv* d;
};

/** @}
 * ship_stack
 */

/** @}
 * ship
 */

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_STACK_SHIPSTACK_H_ */
