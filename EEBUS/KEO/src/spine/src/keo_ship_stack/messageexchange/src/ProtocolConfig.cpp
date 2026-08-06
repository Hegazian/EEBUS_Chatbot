/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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
 * @brief SHIP node configuration structure.
 *        The information is the initial configuration of the SHIP message exchange
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#include <keo_ship/ShipStack.h>

using namespace keo_ship;

// config of the SHIP versions
/** major SHIP version number part */
uint16_t ProtocolConfig::SHIP_VERSION_MAJOR = 1;
/** minor SHIP version number part */
uint16_t ProtocolConfig::SHIP_VERSION_MINOR = 0;
/** major minimum SHIP version number part */
uint16_t ProtocolConfig::SHIP_MIN_VERSION_MAJOR = 1;
/** minor minimum SHIP version number part */
uint16_t ProtocolConfig::SHIP_MIN_VERSION_MINOR = 0;

#ifndef KEO_SHIP_PROTOCOL_CONFIG_PROTOCOL_FORMATS
std::string KEO_SHIP_PROTOCOL_CONFIG_PROTOCOL_FORMATS_TMP[] = { "JSON-UTF8" };

/** Supported protocol formats (sorted) */
std::vector<std::string> ProtocolConfig::PROTOCOL_FORMATS(
    std::begin(KEO_SHIP_PROTOCOL_CONFIG_PROTOCOL_FORMATS_TMP), std::end(KEO_SHIP_PROTOCOL_CONFIG_PROTOCOL_FORMATS_TMP));

ProtocolConfig::ProtocolConfig()
    : timeoutCmi(30 * 1000) // 10 to 30 sec
    , timeoutHelloWaitForReady(60 * 1000) // 60 sec
    , minimumHelloWaitForReadyForProlongation(30 * 1000) // 30 sec
    , maximumHelloAllowProlongationRequests(2) // 2 times
    , timeoutHelloProlongationWaiting(30 * 1000) // 0.5 times of timeout_HELLO_Wait_for_ready (=> max = 1.5 times)
    , timeoutHandshakeWaitForReady(10 * 1000) // 10 sec
    , timeoutPinRecall(120 * 1000) // 120 sec
    , timeoutPinAskInit(10 * 1000) // 10 sec
    , timeoutPinState(120 * 1000) // 30 sec to 120 sec
{
}


uint8_t keo_ship::ProtocolConfig::getMaximumHelloAllowProlongationRequests() const
{
    return maximumHelloAllowProlongationRequests;
}

void keo_ship::ProtocolConfig::setMaximumHelloAllowProlongationRequests(uint8_t maximumHelloAllowProlongationRequests)
{
    this->maximumHelloAllowProlongationRequests = maximumHelloAllowProlongationRequests;
}

uint32_t keo_ship::ProtocolConfig::getMinimumHelloWaitForReadyForProlongation() const
{
    return minimumHelloWaitForReadyForProlongation;
}

void keo_ship::ProtocolConfig::setMinimumHelloWaitForReadyForProlongation(
    uint32_t minimumHelloWaitForReadyForProlongation)
{
    this->minimumHelloWaitForReadyForProlongation = minimumHelloWaitForReadyForProlongation;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutCmi() const
{
    return timeoutCmi;
}

void keo_ship::ProtocolConfig::setTimeoutCmi(uint32_t timeoutCmi)
{
    this->timeoutCmi = timeoutCmi;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutHandshakeWaitForReady() const
{
    return timeoutHandshakeWaitForReady;
}

void keo_ship::ProtocolConfig::setTimeoutHandshakeWaitForReady(uint32_t timeoutHandshakeWaitForReady)
{
    this->timeoutHandshakeWaitForReady = timeoutHandshakeWaitForReady;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutHelloProlongationWaiting() const
{
    return timeoutHelloProlongationWaiting;
}

void keo_ship::ProtocolConfig::setTimeoutHelloProlongationWaiting(uint32_t timeoutHelloProlongationWaiting)
{
    this->timeoutHelloProlongationWaiting = timeoutHelloProlongationWaiting;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutHelloWaitForReady() const
{
    return timeoutHelloWaitForReady;
}

void keo_ship::ProtocolConfig::setTimeoutHelloWaitForReady(uint32_t timeoutHelloWaitForReady)
{
    this->timeoutHelloWaitForReady = timeoutHelloWaitForReady;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutPinAskInit() const
{
    return timeoutPinAskInit;
}

void keo_ship::ProtocolConfig::setTimeoutPinAskInit(uint32_t timeoutPinAskInit)
{
    this->timeoutPinAskInit = timeoutPinAskInit;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutPinRecall() const
{
    return timeoutPinRecall;
}

void keo_ship::ProtocolConfig::setTimeoutPinRecall(uint32_t timeoutPinRecall)
{
    this->timeoutPinRecall = timeoutPinRecall;
}

uint32_t keo_ship::ProtocolConfig::getTimeoutPinState() const
{
    return timeoutPinState;
}

void keo_ship::ProtocolConfig::setTimeoutPinState(uint32_t timeoutPinState)
{
    this->timeoutPinState = timeoutPinState;
}

/* static */ bool keo_ship::ProtocolConfig::isBetween(int value, int min, int max)
{
    return value >= min && value <= max;
}

/**
 * Check if the received SHIP version is in the space of the own device version
 * @return
 *        true, if the SHIP version fits
 */
/*static */ bool keo_ship::ProtocolConfig::isVersionValid(uint16_t versionMajor, uint16_t versionMinor)
{
    return isBetween(versionMajor, SHIP_MIN_VERSION_MAJOR, SHIP_VERSION_MAJOR)
        && isBetween(versionMinor, SHIP_MIN_VERSION_MINOR, SHIP_VERSION_MINOR);
}

/**
 * Try to match the config SHIP version with the received one
 * @return
 *        true, if the SHIP version are matched
 */
/*static */ bool keo_ship::ProtocolConfig::agreedVersion(uint16_t& versionMajor, uint16_t& versionMinor)
{
    if (versionMajor > SHIP_VERSION_MAJOR)
    {
        versionMajor = SHIP_VERSION_MAJOR;
        versionMinor = SHIP_VERSION_MINOR;
        return true;
    }
    if (versionMajor < SHIP_VERSION_MAJOR)
    {
        if (versionMajor > SHIP_MIN_VERSION_MAJOR)
        {
            return true;
        }
        if (versionMajor < SHIP_MIN_VERSION_MAJOR)
        {
            return false;
        }
    }
    if (versionMinor > SHIP_VERSION_MINOR)
    {
        versionMinor = SHIP_VERSION_MINOR;
        return true;
    }
    if (versionMinor > SHIP_MIN_VERSION_MINOR)
    {
        return true;
    }
    if (versionMajor < SHIP_MIN_VERSION_MINOR)
    {
        return false;
    }
    return true;
}

#define KEO_SHIP_PROTOCOL_CONFIG_PROTOCOL_FORMATS 1
#endif
