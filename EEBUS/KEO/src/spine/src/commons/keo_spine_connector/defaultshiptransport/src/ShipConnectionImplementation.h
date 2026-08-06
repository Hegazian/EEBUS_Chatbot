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
 *     @brief      An interface to a SHIP connection
 *
 *     @par        The TransportConnection is a container for ShipNode, to overwrite the
 * ShipNode functionality
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_SPINE_SHIPCONNECTION_SRC_SHIPCONNECTION_H_
#define KEO_SPINE_SHIPCONNECTION_SRC_SHIPCONNECTION_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/SpineLink.h>
#include <keo_spine/TransportConnection.h>

#include <keo_default_ship_transport/ShipTransportConnector.h>
#include "ShipControlInterface.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_ship/ShipSecurity.h>
#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <memory>

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
 * @startuml
 * [ShipConnection] -up- TransportConnectionInterface
 * [ShipConnection] -up-  ShipConnectionInterface
 * [ShipConnection] --> TransportConnectionHandlerInterface: uses
 * [ShipConnection] --> ShipControlInterface: uses
 * @enduml
 * @ingroup keo_ship_transport
 */
class ShipConnectionImplementation : public keo_ship::ShipNode,
                                     public keo_spine::TransportConnection,
                                     public ShipConnection
{
public:
    /**
     * Constructor
     * @param connectionHandler
     *            Interface to the SHIP connection handler
     * @param shipListener
     *            Interface to SHIP control
     */
    ShipConnectionImplementation(
        keo_spine::TransportConnectionHandler* connectionHandler, ShipControlInterface* shipListener);

    /**
     * Virtual destructor
     */
    virtual ~ShipConnectionImplementation();

    /**
     * @see TransportConnection or @see ShipConnection
     */
    std::string getId() const override;

    /**
     * @see TransportConnection or @see ShipConnection
     */
    std::string getShipId() const override;

    /**
     * @see TransportConnection
     */
    void sendDatagram(const keo_datagram::Datagram& datagram) override;

    /**
     * @see TransportConnection or @see ShipConnection
     */
    void closeConnection() override;

    /**
     * @see ShipConnection
     */
    std::string getSki() const override;

    /**
     * @see ShipConnection
     */
    std::string getIpAddress() const override;

    /**
     * @see ShipConnection
     */
    int getIpPort() const override;

    /**
     * @see ShipConnection
     */
    bool isClient() const override;

    /**
     * @see ShipConnection
     */
    keo_ship::TrustLevel getTrustLevel() const override;

    /**
     * @see ShipConnection
     */
    keo_ship::PinRequirement getPinRequirement() const override;

    /**
     * @see ShipConnection
     */
    void setPin(const std::string& pin) override;

    /**
     * @see ShipConnection
     */
    void setPinPenaltyTime(long penaltyTime) override;

    /**
     * The SHIP Stack announces that the Node is connected.
     *
     * SPINE data messages can not yet be exchanged.
     */
    void onConnect() override;

    /**
     * @see ShipNode
     */
    void onClose(int status, const std::string& reason) override;

    /**
     * The SHIP Stack announces that the Node is connected and ready for communication
     * SPINE data messages can be exchanged.
     */
    void onDataExchangeEnabled() override;

    /**
     * An incoming message was received from the SHIP Stack
     *
     * onMessage transforms the message into a SPINE datagram
     * and sends the datagram to the transport connection handler.
     * @param message JSON representation of the datagram.
     */
    void onMessage(const std::vector<char>& message) override;

    /**
     * @see ShipNode
     */
    unsigned short onTrustCertificate(
        const std::string& ski, const keo_ship::X509Certificate& certificate) override;

    /**
     * @see ShipNode
     */
    unsigned short onValidatePin(const std::string& pin) override;

    /**
     * @see ShipNode
     */
    void onPinRequest() override;

    /**
     * @see ShipNode
     */
    void onPinRecallTimeout() override;

    /**
     * @see ShipNode
     */
    void onPinWrong() override;

private:
    // Parent handler for the connection
    keo_spine::TransportConnectionHandler* connectionHandler;
    // Listener for SHIP callbacks
    ShipControlInterface* shipListener;
    // Status code for close
    static const int CLOSE_STATUS_CODE;
    // Status string for close
    static const std::string CLOSE_REASON;
    // Extra prefix for all SHIP connections added to the SHIP id
    static const std::string ID_PREFIX;
    // data exchange enabled
    bool dataExchangeEnabled;
};

//! typedef for non-const smart pointer type ShipConnection
typedef std::shared_ptr<ShipConnectionImplementation> ShipConnectionImplementationPtr;

//! typedef for const type ShipConnection
typedef const ShipConnectionImplementation ShipConnectionImplementationConst;

//! typedef for const smart pointer type ShipConnection
typedef std::shared_ptr<ShipConnectionImplementationConst> ShipConnectionImplementationConstPtr;

} /* namespace keo_default_ship_transport */

#endif /* KEO_SPINE_SHIPCONNECTION_SRC_SHIPCONNECTION_H_ */
