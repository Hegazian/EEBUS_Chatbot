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

#ifndef _SHIPTRANSPORTCONNECTIONIMPL_H_
#define _SHIPTRANSPORTCONNECTIONIMPL_H_

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_ship/ShipStack.h>
#include <keo_simple_ship_transport/SimpleShipTransportConnector.h>
#include <keo_spine/TransportConnection.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <memory>

namespace keo_simple_ship_transport
{

/**
 * @ingroup keo_simple_ship_transport
 * @{
 */

/** Interface (internal) to handle the connections.
 *
 */
class SimpleShipConnectionHandler
{
public:
    virtual ~SimpleShipConnectionHandler()
    {
    }

    virtual void onConnect(ShipTransportConnection* connection) = 0;

    virtual void onClose(
        ShipTransportConnection* connection, int status, const std::string& reason, bool dataExchangeEnabled)
        = 0;

    virtual void onDataExchangeEnabled(ShipTransportConnection* connection) = 0;

    virtual unsigned short onTrustCertificate(
        ShipTransportConnection* connection, const std::string& ski, const keo_ship::X509Certificate& certificate)
        = 0;

    virtual unsigned short onValidatePin(ShipTransportConnection* connection, const std::string& pin) = 0;

    virtual void onPinRequest(ShipTransportConnection* connection) = 0;

    virtual void onPinRecallTimeout(ShipTransportConnection* connection) = 0;

    virtual void onPinWrong(ShipTransportConnection* connection) = 0;

    virtual void onDatagram(ShipTransportConnection* connection, const keo_datagram::Datagram& datagram) = 0;
};

/** Implementation of the SHIP transport connection.
 *
 */
class SimpleShipConnection : public ShipTransportConnection,
                             public keo_ship::ShipNode,
                             public keo_spine::TransportConnection
{
public:
    SimpleShipConnection(SimpleShipConnectionHandler* simpleShipConnectionHandler);

    virtual ~SimpleShipConnection();

    std::string getTransportId() const override;

    std::string getShipId() const override;

    std::string getSki() const override;

    std::string getIpAddress() const override;

    keo_ship::TrustLevel getTrustLevel() const override;

    bool isClient() const override;

    void closeConnection() override;

    keo_ship::PinRequirement getPinRequirement() const override;

    void setPin(const std::string& pin) override;

    void setPinPenaltyTime(long penaltyTime) override;

    bool isDataExchangeEnabled() const override
    {
        return dataExchangeEnabled;
    }

private:
    std::string getId() const override;

    void sendDatagram(const keo_datagram::Datagram& datagram) override;

private:
    void onConnect() override;

    void onClose(int status, const std::string& reason) override;

    void onDataExchangeEnabled() override;

    void onMessage(const std::vector<char>& message) override;

    unsigned short onTrustCertificate(const std::string& ski, const keo_ship::X509Certificate& certificate) override;

    unsigned short onValidatePin(const std::string& pin) override;

    void onPinRequest() override;

    void onPinRecallTimeout() override;

    void onPinWrong() override;

private:
    SimpleShipConnectionHandler* simpleShipConnectionHandler;
    bool dataExchangeEnabled;
};

typedef std::shared_ptr<SimpleShipConnection> SimpleShipConnectionPtr;

/** @} */ //  end of group keo_simple_ship_transport

} /* namespace keo_simple_ship_transport */

#endif /* _SHIPTRANSPORTCONNECTIONIMPL_H_ */
