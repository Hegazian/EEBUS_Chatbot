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
 *     @brief      ShipConnection class definition
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ShipConnectionImplementation.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_spine/DatagramRecord.h>
#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/DatagramParserException.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>
#include <sstream>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_default_ship_transport
{

// Status code for close
const int ShipConnectionImplementation::CLOSE_STATUS_CODE = 4500;
// Status string for close
const std::string ShipConnectionImplementation::CLOSE_REASON("User close");
// Extra prefix for all SHIP connections added to the SHIP id
const std::string ShipConnectionImplementation::ID_PREFIX("ship_");

ShipConnectionImplementation::ShipConnectionImplementation(
    keo_spine::TransportConnectionHandler* connectionHandler, ShipControlInterface* shipListener)
    : connectionHandler(connectionHandler)
    , shipListener(shipListener)
    , dataExchangeEnabled(false)
{
    DEBUG_FUNC();
    assert(NULL != connectionHandler);
    assert(NULL != shipListener);
}

ShipConnectionImplementation::~ShipConnectionImplementation()
{
    DEBUG_FUNC();
}

std::string ShipConnectionImplementation::getId() const
{
    DEBUG_FUNC();
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << ID_PREFIX << keo_ship::ShipNode::getId() << "_" << address;
    return ss.str();
}

std::string ShipConnectionImplementation::getShipId() const
{
    DEBUG_FUNC();
    return keo_ship::ShipNode::getId();
}

void ShipConnectionImplementation::sendDatagram(const keo_datagram::Datagram& datagram)
{
    DEBUG_FUNC();
    if (!datagram.isEmpty())
    {
        std::string message = datagram.toJson();
        LOG_INFO() << "Send message to '" << getId() << "': " << message;

        if (!message.empty())
        {
            keo_ship::ShipNode::sendMessage(std::vector<char>(message.begin(), message.end()));
        }
        else
        {
            LOG_WARNING() << "Sending datagram discarded. Cannot encode datagram to message";
        }
    }
    else
    {
        LOG_WARNING() << "Sending invalid datagram discarded";
    }
}

void ShipConnectionImplementation::closeConnection()
{
    DEBUG_FUNC();
    keo_ship::ShipNode::close();
}

std::string ShipConnectionImplementation::getSki() const
{
    DEBUG_FUNC();
    return keo_ship::ShipNode::getSki();
}

std::string ShipConnectionImplementation::getIpAddress() const
{
    DEBUG_FUNC();
    return keo_ship::ShipNode::getIpAddress();
}

int ShipConnectionImplementation::getIpPort() const
{
    DEBUG_FUNC();
    return keo_ship::ShipNode::getIpPort();
}


bool ShipConnectionImplementation::isClient() const
{
    DEBUG_FUNC();
    return keo_ship::ShipNode::isClient();
}

keo_ship::TrustLevel ShipConnectionImplementation::getTrustLevel() const
{
    DEBUG_FUNC();
    return keo_ship::ShipNode::getTrustLevel();
}

keo_ship::PinRequirement ShipConnectionImplementation::getPinRequirement() const
{
    return keo_ship::ShipNode::getPinRequirement();
}

void ShipConnectionImplementation::setPin(const std::string& pin)
{
    DEBUG_FUNC();
    keo_ship::ShipNode::setPin(pin);
}

void ShipConnectionImplementation::setPinPenaltyTime(long penaltyTime)
{
    DEBUG_FUNC();
    keo_ship::ShipNode::setPinPenaltyTime(penaltyTime);
}

void ShipConnectionImplementation::onConnect()
{
    DEBUG_FUNC();
    LOG_INFO() << "Establishing SHIP connection";
    if (NULL != shipListener)
    {
        shipListener->onConnect(this);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
}

void ShipConnectionImplementation::onClose(int status, const std::string& reason)
{
    DEBUG_FUNC();

    if (NULL != shipListener)
    {
        shipListener->onClose(this, status, reason, dataExchangeEnabled);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
    dataExchangeEnabled = false;
}

void ShipConnectionImplementation::onDataExchangeEnabled()
{
    LOG_INFO() << "Ship connection '" << getId() << "' data exchange enabled";

    dataExchangeEnabled = true;

    if (NULL != shipListener)
    {
        shipListener->onDataExchangeEnabled(this);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
}

void ShipConnectionImplementation::onMessage(const std::vector<char>& message)
{
    // DEBUG_FUNC();
    std::string messageString = std::string(message.begin(), message.end());
    LOG_INFO() << "Received message from '" << getId() << "': " << messageString;

    try
    {
        keo_datagram::Datagram datagram = keo_datagram::Datagram::fromJsonThrows(messageString);
        if (NULL != connectionHandler)
        {
            connectionHandler->onDatagram(datagram, getId());
        }
        else
        {
            LOG_ERROR() << "connectionHandler not set";
        }
    }
    catch (const keo_datagram::DatagramParserException& e)
    {
        LOG_ERROR() << "Could not parse header of datagram: " << e.what();
    }
}

unsigned short ShipConnectionImplementation::onTrustCertificate(
    const std::string& ski, const keo_ship::X509Certificate& certificate)
{
    DEBUG_FUNC();
    if (NULL != shipListener)
    {
        return shipListener->onTrustCertificate(this, ski, certificate);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
    return keo_ship::TrustLevel::TRUST_VALUE_USER_UNTRUSTED;
}

unsigned short ShipConnectionImplementation::onValidatePin(const std::string& pin)
{
    DEBUG_FUNC();
    if (NULL != shipListener)
    {
        return shipListener->onValidatePin(this, pin);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
    return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_NONE;
}

void ShipConnectionImplementation::onPinRequest()
{
    DEBUG_FUNC();
    if (NULL != shipListener)
    {
        shipListener->onPinRequest(this);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
}

void ShipConnectionImplementation::onPinRecallTimeout()
{
    DEBUG_FUNC();
    if (NULL != shipListener)
    {
        shipListener->onPinRecallTimeout(this);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
}

void ShipConnectionImplementation::onPinWrong()
{
    DEBUG_FUNC();
    if (NULL != shipListener)
    {
        shipListener->onPinWrong(this);
    }
    else
    {
        LOG_ERROR() << "shipListener not set";
    }
}
}
/* namespace keo_default_ship_transport */
