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

#ifndef KEO_FRAMEWORK_SHIPCONTROL_SRC_SHIPCONTROL_H_
#define KEO_FRAMEWORK_SHIPCONTROL_SRC_SHIPCONTROL_H_

/* ****************************************************************************** *
 *  Project header files
 * ****************************************************************************** */
#include <keo_default_ship_transport/ShipTransportConfiguration.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/core/xs_types.h>
#include <keo_ship/ShipSecurity.h>
#include <keo_ship/ShipStack.h>
#include <keo_ship/Uri.h>
#include <keo_ship_discovery/ShipDiscovery.h>
#include <keo_spine/SpineLink.h>
#include <keo_util/KETimer.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <map>
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

namespace keo_default_ship_transport
{

/**
 * @ingroup keo_default_ship_transport
 * @{
 */

/**
 * Interface for the application to receive information about SHIP service discovery events
 */
class ShipDiscoveryListener
{
public:
    /**
     * virtual destructor
     * Does nothing
     */
    virtual ~ShipDiscoveryListener()
    {
    }

    /**
     * An added or updated SHIP service of a remote SHIP node is discovered.
     *
     * @param service
     *        mDNS service information
     */
    virtual void serviceAdded(const keo_ship_discovery::ShipService& service) = 0;

    /**
     * A removed SHIP service of a remote SHIP node is discovered.
     *
     * @param service
     *        mDNS service information
     */
    virtual void serviceRemoved(const keo_ship_discovery::ShipService& service) = 0;

    /**
     * Own SHIP service is registered.
     *
     * @param service
     *        mDNS service information
     */
    virtual void ownServiceRegistered(const keo_ship_discovery::ShipService& service) = 0;

    /**
     * Own SHIP service is removed.
     *
     * @param service
     *        mDNS service information
     */
    virtual void ownServiceRemoved(const keo_ship_discovery::ShipService& service) = 0;
};

class ShipConnection
{
public:
    /// Destructor
    virtual ~ShipConnection()
    {
    }

    /**
     * Retrieve an identifier representing the current SHIP connection
     * (aka transportId).
     * @return
     *        Id representing the current SHIP connection.
     */
    virtual std::string getId() const = 0;

    /**
     * Retrieve the SHIP id of remote SHIP node.
     *
     * Note that the SHIP id is only available after the connection has reached the data
     * exchange phase.
     * @return
     *        SHIP Id of the remote SHIP node.
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
     * Retrieve the remote SHIP node's port.
     * @return
     *        Remote SHIP node's IP port.
     */
    virtual int getIpPort() const = 0;

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

/**
 * Access and control the SHIP stack
 *
 * ShipTransportConnector provides following interfaces
 * @startuml
 * [ShipTransportConnector] -- ShipControlInterface
 * @enduml
 *
 * The communication flow is shown below
 * @startuml
 * [ShipTransportConnector] -- ShipControlInterface
 * note bottom of ShipControlInterface
 * Called from a ShipConnection to control the SHIP stack
 * end note
 * @enduml
 *
 * @ingroup framework_shiptransportconnection
 */
class ShipTransportConnector
{
public:
    /**
     * Constructor
     * @param configuration
     */
    explicit ShipTransportConnector(ShipTransportConfigurationPtr configuration);

    /**
     * Destructor
     */
    virtual ~ShipTransportConnector();

    /**
     * Called when a new SHIP connection is established.
     *
     * Note, that the SHIP Id of the remote node is only known after
     * onDataExchangeEnabled(ShipConnection* connection) has been called.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onConnect(ShipConnection* connection)
    {
        (void)connection;
    }

    /**
     * Called if a the SHIP connection reached the DataExchangeEnabled status.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onDataExchangeEnabled(ShipConnection* connection)
    {
        (void)connection;
    }

    /**
     * Called when a  SHIP connection is closed.
     *
     * @param connection
     *            the SHIP connection
     * @param status
     *            status code of the connection
     * @param reason
     *            reason why the connection is closed
     */
    virtual void onClose(ShipConnection* connection, int status, const std::string& reason)
    {
        (void)connection;
        (void)status;
        (void)reason;
    }

    /**
     * Callback to set the user trust level of a certificate/SHIP connection. This callback is not invoked when the
     * certificate has been trusted before.
     *
     * When this method returns a trust level larger than 0, this value is stored using the {@link
     * ShipSecurityHandler} passed to the SHIP stack.
     *
     * It might be necessary, according to the SHIP specification, to set a
     * penalty time using {@link ShipConnection#setPinPenaltyTime(long)} on
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
    virtual unsigned short onTrustCertificate(
        ShipConnection* connection, const std::string& ski, const keo_ship::X509Certificate& certificate)
        = 0;

    /**
     * Callback to check whether a received PIN is valid is to set the Second Factor trust of a
     * certificate/SHIP connection.
     *
     * When this method returns a trust level larger than 0, this value is stored using the {@link
     * ShipSecurityHandler} passed to the SHIP stack.
     *
     * If the PIN is not valid, it might be necessary, according to the SHIP
     * specification, to set a penalty time using
     * {@link ShipConnection#setPinPenaltyTime(long)} on the connection to
     * avoid brute-force attacks. Refer to the SHIP specification to learn which
     * penalty times are valid.
     *
     * @param connection
     *            the SHIP connection
     * @param pin
     *            the received PIN
     * @return the new second factor trust level
     */
    virtual unsigned short onValidatePin(ShipConnection* connection, const std::string& pin);

    /**
     * Callback to announce that the remote end of a SHIP connection is requesting a PIN.
     * To enter a PIN, use {@link ShipConnection#setPin()}.
     * Use {@link ShipConnection#getPinRequirement()} to check whether the PIN is optional or required.
     *
     * It is safe to keep a reference to the ShipConnection object, in order to enter the PIN at a later point in time.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onPinRequest(ShipConnection* connection);

    /**
     * Callback to announce that the remote end of a connection did not enter a PIN in time.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onPinRecallTimeout(ShipConnection* connection);

    /**
     * Callback to announce that the last PIN entered on a connection has been rejected by the receiver.
     * This is called at both endpoints of the connection.
     *
     * @param connection
     *            the SHIP connection
     */
    virtual void onPinWrong(ShipConnection* connection);

    /** Set the discovery listener.
     * Any discovered SHIP services are reported to the listener.
     * @param listener
     *        The listener to be set.
     *        A nullptr unsets the listener.
     */
    void setDiscoveryListener(ShipDiscoveryListener* listener);

    /**
     * Initialize the SHIP stack.
     * @param instanceName
     *        The instance name (used for SHIP service announcement).
     * @param shipSecurityHandler
     *        The security handler (used for verification procedures in case of incoming SHIP connections).
     * @param pShipLink
     *        Used for SHIP connection creation.
     * @return
     *        true if successful, else false
     */
    bool initializeShip(const std::string& instanceName, keo_ship::SecurityHandlerPtr shipSecurityHandler,
        keo_spine::SpineLinkPtr pShipLink);

    /**
     * Start own SHIP server.
     * If started, other remote SHIP nodes can connect to this server.
     * @return true, if server could be started
     */
    bool startServer();

    /**
     * Start SHIP discovery.
     * If started, other SHIP services will be discovered and the own SHIP service is announced.
     * @param registerFlag
     *        This flag indicates the own status of "auto accept mode".
     * @return true, if discovery could be started
     */
    bool startDiscovery(bool registerFlag);

    /**
     * Stop the own SHIP server.
     * I.e. no other remote SHIP nodes can connect to this server.
     */
    void stopServer();

    /**
     * Stop SHIP discovery.
     * I.e. no other SHIP services will be discovered and the own SHIP service is not announced.
     * In case of calling this method right before application shutdown it's recommended to
     * deactivate the listener, i.e. setDiscoveryListener(nullptr).
     */
    void stopDiscovery();

    /**
     * Try to connect to a remote SHIP node via a given URI.
     * The URI is expected to be valid (see keo_ship::Uri).
     * An asynchronous connection callback will be issued, in case the remote SHIP
     * node is successfully connected.
     * @param uri
     *        URI of the remote SHIP node.
     * @return true if connection process starts, else false.
     */
    bool connectToShip(const keo_ship::Uri& uri);

    /**
     * Close all connections.
     */
    void closeConnections();

    /**
     * Close connection to a SHIP node.
     * @param id
     *        ID of the connection.
     */
    void closeConnection(std::string id);

    /**
     * Enable/Disable the SHIP stack's auto accept mode. If enabled, the
     * register flag will be set to true in the own SHIP service. If disabled,
     * the register flag will be set to false in the own SHIP service.
     * @param duration
     *        duration != 0: duration in seconds to enable the auto accept mode
     *     @n duration == 0: disable auto accept mode
     */
    void setAutoAccept(time_t duration);

    /**
     * Checks if auto accept mode is active.
     * @return
     *        true if own SHIP node is in auto accept mode, else false.
     */
    bool isAutoAccept() const;

    /**
     * Enable the ability to automatically connect to already trusted SHIP nodes.
     * Note: Only the certificate is verified, no trust level value!
     * Enabling this automatism is deprecated.
     * @param on
     *        Flag to enable or disable auto connect automatism.
     *
     * @deprecated This will be removed in a future release.
     */
    void setAutoConnect(bool on);

    /**
     * Checks if auto connect automatism is active.
     * @return
     *        true, if auto connect automatism is enabled.
     */
    bool isAutoConnect() const;

    /**
     * Checks if the SHIP register flag is set.
     * @return
     *        true if register flag is set, else false.
     */
    bool isRegister() const;

    /**
     * Checks if a connection to a SHIP node exists.
     * @param service
     *        Discovered SHIP service, containing SKI, SHIP-Node-ID (among others).
     * @return true, if already connected.
     */
    bool isConnected(const keo_ship_discovery::ShipService& service) const;

    /**
     * Checks if the SHIP node of a discovered service exists in the trust store
     * and has a valid certificate.
     *
     * @param service
     *            ShipService
     * @return true, if the node has a valid certificate
     */
    bool hasValidCertificate(const keo_ship_discovery::ShipService& service) const;

    /**
     * Get all currently discovered SHIP services.
     * @return all discovered SHIP services
     */
    std::vector<keo_ship_discovery::ShipService> getDiscoveredServices() const;

    /**
     * Get the maximum number of simultaneous SHIP connections.
     * @return maximum connections
     */
    int getMaximumConnections() const;

    /**
     * Set the maximum number of simultaneous SHIP connections. When this is set to 0 (default), no
     * limit is enforced.
     * @param maximumConnections
     *        Maximum connections
     */
    void setMaximumConnections(int maximumConnections);

    /**
     * Callback to check, if new server connection should be blocked.
     * Can be overwritten by application.
     * @return true, if new connections should be blocked, else false.
     *         default: false
     */
    virtual bool shouldBlockServerConnections() const;

    /**
     * Callback to check, if server connections should be activated.
     * Can be overwritten by application.
     * @return true, if reactivate server connections
     *         This is only relevant for servers which could handle only one
     *         connection
     *         default: true
     */
    virtual bool shouldActivateServerConnections() const;

private:
    class ShipTransportConnectorPriv;
    ShipTransportConnectorPriv* p;
};

/** @} */ //  end of group keo_default_ship_transport
} /* namespace keo_default_ship_transport */

#endif /* KEO_FRAMEWORK_SHIPCONTROL_SRC_SHIPCONTROL_H_ */
