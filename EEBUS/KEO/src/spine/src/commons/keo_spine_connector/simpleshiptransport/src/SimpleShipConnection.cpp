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
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include "SimpleShipConnection.h"

#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/DatagramParserException.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <vector>

namespace keo_simple_ship_transport
{

// Extra prefix for all SHIP connections added to the SHIP id
const std::string ID_PREFIX("ship_");

SimpleShipConnection::SimpleShipConnection(SimpleShipConnectionHandler* simpleShipConnectionHandler)
    : simpleShipConnectionHandler(simpleShipConnectionHandler)
    , dataExchangeEnabled(false)
{
}

SimpleShipConnection::~SimpleShipConnection()
{
}

std::string SimpleShipConnection::getTransportId() const
{
    if (isDataExchangeEnabled())
    {
        return ID_PREFIX + getShipId();
    }
    return std::string();
}

std::string SimpleShipConnection::getShipId() const
{
    return keo_ship::ShipNode::getId();
}

std::string SimpleShipConnection::getSki() const
{
    return keo_ship::ShipNode::getSki();
}

std::string SimpleShipConnection::getIpAddress() const
{
    return keo_ship::ShipNode::getIpAddress();
}

keo_ship::TrustLevel SimpleShipConnection::getTrustLevel() const
{
    return keo_ship::ShipNode::getTrustLevel();
}

bool SimpleShipConnection::isClient() const
{
    return keo_ship::ShipNode::isClient();
}

void SimpleShipConnection::closeConnection()
{
    keo_ship::ShipNode::close();
}

keo_ship::PinRequirement SimpleShipConnection::getPinRequirement() const
{
    return keo_ship::ShipNode::getPinRequirement();
}

void SimpleShipConnection::setPin(const std::string& pin)
{
    keo_ship::ShipNode::setPin(pin);
}

void SimpleShipConnection::setPinPenaltyTime(long penaltyTime)
{
    keo_ship::ShipNode::setPinPenaltyTime(penaltyTime);
}

void SimpleShipConnection::onConnect()
{
    DEBUG_FUNC();
    LOG_INFO() << "Establishing SHIP connection";
    if (nullptr != simpleShipConnectionHandler)
    {
        simpleShipConnectionHandler->onConnect(this);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
}

void SimpleShipConnection::onClose(int status, const std::string& reason)
{
    DEBUG_FUNC();

    if (nullptr != simpleShipConnectionHandler)
    {
        simpleShipConnectionHandler->onClose(this, status, reason, dataExchangeEnabled);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
    dataExchangeEnabled = false;
}

void SimpleShipConnection::onDataExchangeEnabled()
{
    LOG_INFO() << "Ship connection '" << getTransportId() << "' data exchange enabled";

    dataExchangeEnabled = true;

    if (nullptr != simpleShipConnectionHandler)
    {
        simpleShipConnectionHandler->onDataExchangeEnabled(this);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
}

void SimpleShipConnection::onMessage(const std::vector<char>& message)
{
    std::string messageString(message.begin(), message.end());
    LOG_INFO() << "Received message from '" << getTransportId() << "': " << messageString;
    try
    {
        keo_datagram::Datagram datagram = keo_datagram::Datagram::fromJsonThrows(messageString);
        if (nullptr != simpleShipConnectionHandler)
        {
            simpleShipConnectionHandler->onDatagram(this, datagram);
        }
        else
        {
            LOG_ERROR() << "Ship transport connection handler not set!";
        }
    }
    catch (const keo_datagram::DatagramParserException& e)
    {
        LOG_ERROR() << "Could not parse header of datagram: " << e.what();
    }
}

unsigned short SimpleShipConnection::onTrustCertificate(
    const std::string& ski, const keo_ship::X509Certificate& certificate)
{
    DEBUG_FUNC();
    if (nullptr != simpleShipConnectionHandler)
    {
        return simpleShipConnectionHandler->onTrustCertificate(this, ski, certificate);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
    return keo_ship::TrustLevel::TRUST_VALUE_USER_UNTRUSTED;
}

unsigned short SimpleShipConnection::onValidatePin(const std::string& pin)
{
    DEBUG_FUNC();
    if (nullptr != simpleShipConnectionHandler)
    {
        return simpleShipConnectionHandler->onValidatePin(this, pin);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
    return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
}

void SimpleShipConnection::onPinRequest()
{
    DEBUG_FUNC();
    if (nullptr != simpleShipConnectionHandler)
    {
        simpleShipConnectionHandler->onPinRequest(this);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
}

void SimpleShipConnection::onPinRecallTimeout()
{
    DEBUG_FUNC();
    if (nullptr != simpleShipConnectionHandler)
    {
        simpleShipConnectionHandler->onPinRecallTimeout(this);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
}

void SimpleShipConnection::onPinWrong()
{
    DEBUG_FUNC();
    if (nullptr != simpleShipConnectionHandler)
    {
        simpleShipConnectionHandler->onPinWrong(this);
    }
    else
    {
        LOG_ERROR() << "Ship transport connection handler not set!";
    }
}

std::string SimpleShipConnection::getId() const
{
    return getTransportId();
}

void SimpleShipConnection::sendDatagram(const keo_datagram::Datagram& datagram)
{
    DEBUG_FUNC();
    if (!datagram.isEmpty())
    {
        std::string message = datagram.toJson();

        if (!message.empty())
        {
            LOG_INFO() << "Send message to '" << getId() << "': " << message;
            keo_ship::ShipNode::sendMessage(std::vector<char>(message.begin(), message.end()));
        }
        else
        {
            LOG_WARNING() << "Cannot send datagram. Encode datagram to message failed!";
        }
    }
    else
    {
        LOG_WARNING() << "Cannot send datagram! Datagram is invalid!";
    }
}

} /* namespace keo_simple_ship_transport */
