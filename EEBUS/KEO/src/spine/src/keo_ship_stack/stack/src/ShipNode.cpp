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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <ShipMessageExchange.h>
#include <ShipSocket.h>
#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

const int ShipNode::CLOSE_STATUS_CODE_USER_CLOSE = 4500;
const std::string ShipNode::CLOSE_REASON_USER_CLOSE("User close");

ShipNode::ShipNode()
    : shipMessageExchange(new ShipMessageExchange(this))
{
    DEBUG_FUNC();
}

ShipNode::~ShipNode()
{
    DEBUG_FUNC();
    delete shipMessageExchange;
}

bool ShipNode::sendMessage(const std::vector<char>& message)
{
    return shipMessageExchange->sendMessage(message);
}

void ShipNode::close()
{
    shipMessageExchange->close(CLOSE_STATUS_CODE_USER_CLOSE, CLOSE_REASON_USER_CLOSE);
}

void ShipNode::closeAnnounce(int maxTimeMilliSeconds, bool isRemovedConnection)
{
    shipMessageExchange->closeIn(maxTimeMilliSeconds, isRemovedConnection);
}

void ShipNode::closeAnnounceConfirm()
{
    shipMessageExchange->closeInConfirm();
}

std::string ShipNode::getSki() const
{
    return shipMessageExchange->getSki();
}

std::string ShipNode::getIpAddress() const
{
    return shipMessageExchange->getIpAddress();
}

int ShipNode::getIpPort() const
{
    return shipMessageExchange->getIpPort();
}

std::string ShipNode::getId() const
{
    return shipMessageExchange->getId();
}

PinRequirement ShipNode::getPinRequirement() const
{
    return shipMessageExchange->getPinRequirement();
}

TrustLevel ShipNode::getTrustLevel() const
{
    return shipMessageExchange->getTrustLevel();
}

void ShipNode::setPin(const std::string& pin)
{
    shipMessageExchange->setPin(pin);
}

void ShipNode::setPinPenaltyTime(long penaltyTime)
{
    shipMessageExchange->setPinPenaltyTime(penaltyTime);
}

bool ShipNode::isClient() const
{
    return shipMessageExchange->getIsClient();
}

} /* namespace keo_ship */
