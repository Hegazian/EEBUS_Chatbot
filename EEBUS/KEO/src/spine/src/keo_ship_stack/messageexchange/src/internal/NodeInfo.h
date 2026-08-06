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

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_NODEINFO_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_NODEINFO_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_ship/ShipSecurity.h>
#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>

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
class NodeInfo
{

public:
    NodeInfo()
        : id()
        , preliminaryId()
        , connected(false)
        , enabledDataExchange(false)
        , needUnrestrictedAccess(false)
        , shipVersionMajor(1)
        , shipVersionMinor(0)
        , shipFormat()
        , pinOwnRequirement(PinRequirement::PIN_REQUIRED)
        , pinRequirement(PinRequirement::PIN_REQUIRED)
        , trustLevel()
        , pin()
    {
    }

    std::string getId() const
    {
        return id;
    }

    void setId(const std::string& id)
    {
        this->id = id;
    }

    std::string getPreliminaryId() const
    {
        return preliminaryId;
    }

    void setPreliminaryId(const std::string& id)
    {
        this->preliminaryId = id;
    }

    bool isConnected() const
    {
        return connected;
    }

    void setConnected(bool connected)
    {
        this->connected = connected;
    }

    bool isEnabledDataExchange() const
    {
        return enabledDataExchange;
    }

    void setEnabledDataExchange(bool enabledDataExchange)
    {
        this->enabledDataExchange = enabledDataExchange;
    }

    bool isNeedUnrestrictedAccess() const
    {
        return needUnrestrictedAccess;
    }

    void setNeedUnrestrictedAccess(bool needUnrestrictedAccess)
    {
        this->needUnrestrictedAccess = needUnrestrictedAccess;
    }

    int getShipVersionMajor() const
    {
        return shipVersionMajor;
    }

    void setShipVersionMajor(int shipVersionMajor)
    {
        this->shipVersionMajor = shipVersionMajor;
    }

    int getShipVersionMinor() const
    {
        return shipVersionMinor;
    }

    void setShipVersionMinor(int shipVersionMinor)
    {
        this->shipVersionMinor = shipVersionMinor;
    }

    std::string getShipFormat() const
    {
        return shipFormat;
    }

    void setShipFormat(const std::string& shipFormat)
    {
        this->shipFormat = shipFormat;
    }

    PinRequirement getPinRequirement() const
    {
        return pinRequirement;
    }

    void setPinRequirement(const PinRequirement& pinRequirement)
    {
        this->pinRequirement = pinRequirement;
    }

    PinRequirement getPinOwnRequirement() const
    {
        return pinOwnRequirement;
    }

    void setPinOwnRequirement(const PinRequirement& pinRequirement)
    {
        this->pinOwnRequirement = pinRequirement;
    }

    TrustLevel getTrustLevel() const
    {
        return trustLevel;
    }

    void setTrustLevel(const TrustLevel& trustLevel)
    {
        this->trustLevel = trustLevel;
    }

    std::string getPin() const
    {
        return pin;
    }

    void setPin(const std::string& pin)
    {
        this->pin = pin;
    }

private:
    std::string id;

    std::string preliminaryId;

    /*
     * Enumeration of the ship formats //TODO need a restriction in xsd public
     * enum ShipFormats { JSON_UTF8 , JSON_UTF16 , ASN1_PER };
     */

    /// flag, if node is still connected (needed for session resumption)
    bool connected;

    /// flag, if commissioning phase is ended
    bool enabledDataExchange;

    /// flag, if data exchange can be done without pin
    bool needUnrestrictedAccess;

    /**
     * SHIP protocol version string, supported by the node. This will be set in
     * the commissioning phase
     */
    int shipVersionMajor;
    /**
     * SHIP protocol version string, supported by the node. This will be set in
     * the commissioning phase
     */
    int shipVersionMinor;

    /**
     * SHIP protocol format. This will be set in the commissioning phase
     */
    std::string shipFormat;

    /**
     * Pin requirement. Starts with "PIN required". If the correct pin is
     * received it changes to OK
     */
    PinRequirement pinOwnRequirement;

    /**
     * Pin requirement of the peer
     */
    PinRequirement pinRequirement;

    /// TrustLevel for this connection
    TrustLevel trustLevel;

    /**
     * Pin from the other device This can be set in between and is send when the
     * the other device is ready
     */
    std::string pin;
};

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_NODEINFO_H_ */
