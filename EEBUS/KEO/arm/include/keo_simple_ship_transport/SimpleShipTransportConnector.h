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

#ifndef _KEO_SIMPLE_SHIP_TRANSPORT_CONNECTOR_H_
#define _KEO_SIMPLE_SHIP_TRANSPORT_CONNECTOR_H_

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_spine/SpineLink.h>
#include <keo_ship/ShipSecurity.h>
#include <keo_ship/ShipStack.h>
#include <keo_ship/Uri.h>

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_simple_ship_transport
{

/**
 * @ingroup keo_simple_ship_transport
 * @{
 */

/** Represents a SPINE connection via SHIP
 *
 */
class ShipTransportConnection
{
public:

    virtual ~ShipTransportConnection()
    {
    }

    /** Returns if a connection reaches the data exchange phase.
     * Data exchange is the indication thatSHIP data messages can be exchanged and
     * therewith the connection is trusted and the SHIP identifier is available.
     * @return True if the connection reaches the data exchange phase
     */
    virtual bool isDataExchangeEnabled() const = 0;

    /**
     * Retrieve the identifier identifying the current connection
     * (aka transportId).
     *
     * The transport id is valid, if the connection reached the data
     * exchange phase.
     *
     * @return
     *        Transport identifier
     */
    virtual std::string getTransportId() const = 0;

    /**
     * Retrieve the SHIP identifier.
     *
     * The SHIP identifier id is valid, if the connection reached the data
     * exchange phase.
     *
     * @return
     *        Ship identifier
     */
    virtual std::string getShipId() const = 0;

    /**
     * Retrieve the remote SHIP node's SKI of the current SHIP connection.
     * @return
     *        Remote SHIP node's SKI.
     */
    virtual std::string getSki() const = 0;

    /**
     * Retrieve the remote SHIP node's IP address of the current SHIP connection.
     * @return
     *        Remote SHIP node's IP address.
     */
    virtual std::string getIpAddress() const = 0;

    /**
     * Retrieve the trust level to the remote SHIP node of the current SHIP connection.
     * Note: SHIP is based on mutual trust. I.e. different trust level may be assigned to each other.
     * This method returns exclusively the trust level that "my SHIP node" has assigned
     * to "the other SHIP node".
     * @return
     *        Trust level value assigned to the remote SHIP node.
     */
    virtual keo_ship::TrustLevel getTrustLevel() const = 0;

    /**
     * Retrieve the own (WebSocket) role of the current SHIP connection.
     * A client role represents the initiator of a connection request.
     * A server role represents the receiver of a connection request.
     * @return
     *        true if client role, else false.
     */
    virtual bool isClient() const = 0;

    /**
     * Close the current SHIP connection.
     */
    virtual void closeConnection() = 0;

    /**
     * Get this connection's PIN requirement.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     *
     * @return pin requirement
     */
    virtual keo_ship::PinRequirement getPinRequirement() const = 0;

    /**
     * Set a PIN for this connection. The PIN is transmitted via this connection for the remote end to validate it.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     */
    virtual void setPin(const std::string& pin) = 0;

    /**
     * Set a penalty time for this connection. A remote end has to wait that time before it can enter another PIN.
     *
     * Refer to the SHIP specification to learn more about PIN handling.
     */
    virtual void setPinPenaltyTime(long penaltyTime) = 0;
};

//! typedef for smart pointer type TransportConnection
typedef std::weak_ptr<ShipTransportConnection> ShipTransportConnectionWeakPtr;

/** Interface to handle SHIP transport connections.
 *
 * Implement this interface in your application to
 * handle incoming and terminating connections.
 */
class SimpleShipTransportConnectorHandler
{
public:

    virtual ~SimpleShipTransportConnectorHandler()
    {

    }

    /**
     * Called when a new SHIP connection is established.
     *
     * Note, that the SHIP Id of the remote node is only known after
     * onDataExchangeEnabled(ShipConnection* connection) has been called.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onConnect(ShipTransportConnectionWeakPtr connection)
    {
        (void) connection;
    }

    /**
     * Called if a the SHIP connection reached the DataExchangeEnabled status.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onDataExchangeEnabled(ShipTransportConnectionWeakPtr connection)
    {
        (void) connection;
    }

    /**
     * Called when a SHIP connection is closed.
     *
     * @param connection
     *            the connection
     * @param status
     *            status code of the connection
     * @param reason
     *            reason why the connection is closed
     */
    virtual void onClose(ShipTransportConnectionWeakPtr connection, int status, const std::string& reason)
    {
        (void) connection;
        (void) status;
        (void) reason;
    }

    /**
     * Callback to check whether the certificate of a new SHIP connection should
     * be trusted. This callback is not invoked when the certificate has been trusted before.
     *
     * It might be necessary, according to the SHIP specification, to set a
     * penalty time using {@link ShipTransportConnection#setPinPenaltyTime(long)} on
     * the connection to avoid brute-force attacks. Refer to the SHIP
     * specification to learn which penalty times are valid.
     *
     * @param connection
     *            the SHIP connection
     * @param ski
     *            the SKI of the certificate
     * @param certificate
     *            the certificate of the remote end
     * @return the new user trust level
     */
    virtual unsigned short onTrustCertificate(ShipTransportConnectionWeakPtr, const std::string& ski,
        const keo_ship::X509Certificate& certificate)
        = 0;

    /**
     * Callback to check whether a received pin is valid.
     *
     * If the PIN is not valid, it might be necessary, according to the SHIP
     * specification, to set a penalty time using
     * {@link ShipTransportConnection#setPinPenaltyTime(long)} on the connection to
     * avoid brute-force attacks. Refer to the SHIP specification to learn which
     * penalty times are valid.
     *
     * @param connection
     *            the SHIP connection
     * @param pin
     *            the received PIN
     * @return the new second factor trust level
     */
    virtual unsigned short onValidatePin(ShipTransportConnectionWeakPtr connection, const std::string& pin)
    {
        (void) connection;
        (void) pin;
        return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
    }

    /**
     * Callback to announce that the remote end of a SHIP connection is requesting a PIN.
     * To enter a PIN, use {@link ShipTransportConnection#setPin()}.
     * Use {@link ShipTransportConnection#getPinRequirement()} to check whether the PIN is optional or required.
     *
     * It is safe to keep a reference to the ShipConnection object, in order to enter the PIN at a later point in time.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onPinRequest(ShipTransportConnectionWeakPtr connection)
    {
        (void) connection;
    }

    /**
     * Callback to announce that the remote end of a connection did not enter a PIN in time.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onPinRecallTimeout(ShipTransportConnectionWeakPtr connection)
    {
        (void) connection;
    }

    /**
     * Callback to announce that the last PIN entered on a connection has been rejected by the receiver.
     * This is called at both endpoints of the connection.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onPinWrong(ShipTransportConnectionWeakPtr connection)
    {
        (void) connection;
    }

};

/** Simple SHIP Spine transport connector.
 *
 */
class SimpleShipTransportConnector
{
public:

    SimpleShipTransportConnector();

    ~SimpleShipTransportConnector();

    /** Sets the transport connection handler.
     *
     * @note This handler is mandatory.
     * @see keo_spine::SpineLink
     *
     * @param transportConnectionHandler Pointer to transport connection handler.
     */
    void setSpineLinkTransportConnectionHandler(keo_spine::TransportConnectionHandler* transportConnectionHandler);

    /** Sets the SHIP transport connection handler.
     *
     * @note This handler is mandatory.
     *
     * @param handler Pointer to SHIP transport connection handler.
     */
    void setSimpleShipTransportConnectorHandler(SimpleShipTransportConnectorHandler* handler);

    bool initializeShipStack(const keo_ship::ShipStackConfiguration& shipStackConfiguration,
        keo_ship::SecurityHandlerPtr shipSecurityhandler);

    /**
     * Try to connect to a remote SHIP node via a given URI.
     * The URI is expected to be valid (see keo_ship::Uri).
     * An asynchronous connection callback will be issued, in case the remote SHIP
     * node is successfully connected.
     * @param uri
     *        URI of the remote SHIP node.
     * @return true if connection process starts, else false.
     */
    bool connectTo(const keo_ship::Uri& uri);

    /**
     * Start own SHIP server.
     * If started, other remote SHIP nodes can connect to this server.
     * @return true, if server could be started
     */
    bool startServer(const std::string& host, int serverPort, const std::string& websocketpath = std::string("/ship/"));

    /**
     * Stop the own SHIP server.
     * I.e. no other remote SHIP nodes can connect to this server.
     * All connections will be closed.
     */
    void stopShip();

    /**
     * Close connection identified by SKI.
     * @param ski
     *        SKI of the connection.
     */
    void closeConnectionBySKI(const std::string& ski);

    /**
     * Close connection identified by SHIP identifier.
     * @param shipId
     *        SHIP identifier of the connection.
     */
    void closeConnectionByShipId(const std::string& shipId);

    /**
     * Close connection identified by the transport identifier.
     * @param transportId
     *        Transport identifier of the connection.
     */
    void closeConnectionByTransportId(const std::string& transportId);

    /** Tests if a peer connection exists.
     *
     * @param ski SKI of the peer
     * @return True if a peer with the given SKI is connected.
     */
    bool isConnectedBySKI(const std::string& ski) const;

    /** Returns the transport connection.
     *
     * @param ski SKI of the peer.
     * @return Weak pointer of the connection. Weak pointer is expired if a peer, identified by the SKI, is not connected.
     */
    ShipTransportConnectionWeakPtr getShipTransportConnectionBySKI(const std::string& ski) const;

    /** Returns the transport connection.
     *
     * @param shipId SHIPO identifier of the peer.
     * @return Weak pointer of the connection. Weak pointer is expired if a peer, identified by the shipId, is not connected.
     */
    ShipTransportConnectionWeakPtr getShipTransportConnectionByShipId(const std::string& shipId) const;

    /** Returns the transport connection.
     *
     * @param transportId Transport identifier of the connection.
     * @return Weak pointer of the connection. Weak pointer is expired if a peer, identified by the transportId, is not connected.
     */
    ShipTransportConnectionWeakPtr getShipTransportConnectionByTransportId(const std::string& transportId) const;

    /** Returns the list of the connection SKI's.
     *
     * @return List of connections SKI's
     */
    std::list<std::string> getSKIs() const;

    /** Returns the list of the connection SHIP identifiers.
     *
     * @return List of SHIP identifiers.
     */
    std::list<std::string> getShipIds() const;

    /** Returns the list of the transport identifiers.
     *
     * @return List of transport identifiers.
     */
    std::list<std::string> getTransportIds() const;

private:
    class ShipTransportConnectorImpl;
    ShipTransportConnectorImpl *p;
};

/** @} */ //  end of group keo_simple_ship_transport
} /* namespace keo_simple_ship_transport */

#endif /* _KEO_SIMPLE_SHIP_TRANSPORT_CONNECTOR_H_ */
