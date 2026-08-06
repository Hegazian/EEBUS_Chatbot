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
 *     @brief      ShipControl interface.
 *
 *     @par        Callbacks from the SHIP stack.
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_FRAMEWORK_SHIPTRANSPORT_SRC_SHIPCONTROLINTERFACE_H_
#define KEO_FRAMEWORK_SHIPTRANSPORT_SRC_SHIPCONTROLINTERFACE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_ship/ShipSecurity.h>
#include <string>
#include <keo_default_ship_transport/ShipTransportConnector.h>

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

/** @ingroup keo_ship_transport
 * @{
 */

/**
 * Interface for the application to receive Information about the SHIP stack and devices
 */
class ShipControlInterface
{
public:
    virtual ~ShipControlInterface()
    {
    }

    /**
     * {@see ShipTransportConnector#onConnect()}
     */
    virtual void onConnect(ShipConnection* connection) = 0;

    /**
     * {@see ShipTransportConnector#onClose()}
     */
    virtual void onClose(ShipConnection* connection, int status, const std::string& reason, bool dataExchangeEnabled)
        = 0;

    /**
     * {@see ShipTransportConnector#onDataExchangeEnabled()}
     */
    virtual void onDataExchangeEnabled(ShipConnection* connection) = 0;

    /**
     * {@see ShipTransportConnector#onTrustCertificate()}
     */
    virtual unsigned short onTrustCertificate(
        ShipConnection* connection, const std::string& ski, const keo_ship::X509Certificate& certificate)
        = 0;

    /**
     * {@see ShipTransportConnector#onValidatePin()}
     */
    virtual unsigned short onValidatePin(ShipConnection* connection, const std::string& pin) = 0;

    /**
     * {@see ShipTransportConnector#onPinRequest()}
     */
    virtual void onPinRequest(ShipConnection* connection) = 0;

    /**
     * {@see ShipTransportConnector#onPinRecallTimeout()}
     */
    virtual void onPinRecallTimeout(ShipConnection* connection) = 0;

    /**
     * {@see ShipTransportConnector#onPinWrong()}
     */
    virtual void onPinWrong(ShipConnection* connection) = 0;
};

/** @}
 * end of group keo_default_ship_transport
 */

} /* namespace keo_default_ship_transport */

#endif /* KEO_FRAMEWORK_SHIPCONTROL_SRC_SHIPCONTROLINTERFACE_H_ */
