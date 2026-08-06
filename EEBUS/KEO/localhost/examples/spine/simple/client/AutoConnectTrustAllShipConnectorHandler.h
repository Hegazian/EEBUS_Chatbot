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

#ifndef EXAMPLES_FRAMEWORK_SIMPLEEXAMPLE_CLIENT_SRC_AUTOCONNECTTRUSTALLSHIPCONNECTORHANDLER_H_
#define EXAMPLES_FRAMEWORK_SIMPLEEXAMPLE_CLIENT_SRC_AUTOCONNECTTRUSTALLSHIPCONNECTORHANDLER_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "AppConfiguration.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_json_security_handler/JsonSecurityHandler.h>
#include <keo_ship_discovery/ShipDiscovery.h>
#include <keo_simple_ship_transport/SimpleShipTransportConnector.h>
#include <keo_spine/SpineLink.h>
#include <keo_util/KETimer.h>

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
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

/**
 * @addtogroup framework_example_client
 * @{
 */
class AutoConnectTrustAllShipConnectorHandler : public keo_simple_ship_transport::SimpleShipTransportConnectorHandler,
                                                public keo_ship_discovery::ShipDiscoveryInterface,
                                                public keo_util::TimerHandlerInterface
{
public:
    /**
     * Constructor
     * @param spineLink
     */
    AutoConnectTrustAllShipConnectorHandler(const AppConfiguration& config, keo_spine::SpineLinkPtr spineLink);

    /**
     * Destructor
     */
    ~AutoConnectTrustAllShipConnectorHandler();

    bool initialize();

    /** Start SHIP server, mDNS resolver and publish own service
     * with register TRUE.
     * The flag will be reset after two minutes.
     */
    bool start();

    void setRegisterFlag(bool registerFlag = true);

    /** Shutdown discovery, service and stack
     *
     */
    void stop();

    /**
     * Close connection to a SHIP node.
     * @param id
     *        ID of the connection.
     */
    void closeConnection(std::string id);

private:
    /**
     * Callback to check if the certificate is trusted. The trust level is
     * USER_VERIFIED if it is trusted.
     *
     * @param connection
     *            SHIP connection
     * @param ski
     *            SKI of the certificate
     * @param certificate
     *            Received certificate
     * @return user trust level
     */
    unsigned short onTrustCertificate(keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection,
        const std::string& ski, const keo_ship::X509Certificate& certificate) override;

    /**
      * Callback to request a pin input for the SHIP connection.
      *
      * @param node
      *            Interface to the connection
      */
    void onPinRequest(keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection) override;

private:
    // keo_ship_discovery::ShipDiscoveryInterface,
    void onServiceAdded(const keo_ship_discovery::ShipService& service) override;
    void onServiceRemoved(const keo_ship_discovery::ShipService& service) override;
    void onOwnServiceRegistered(const keo_ship_discovery::ShipService& service) override;
    void onOwnServiceRemoved(const keo_ship_discovery::ShipService& service) override;

private:
    void handleTimer(keo_util::Timer::id_t timerId) override;

private:
    const AppConfiguration& config;
    keo_json_security_handler::JsonSecurityHandlerPtr shipSecurityHandler;
    keo_ship_discovery::ShipDiscovery shipDiscovery;
    keo_simple_ship_transport::SimpleShipTransportConnector shipConnector;

    keo_util::Timer timer;
    keo_util::Timer::id_t registerTimerId;
};

/** @} */ //  end of group framework_example_client

} // namespace keo_spine_example_client

#endif /* EXAMPLES_FRAMEWORK_SIMPLEEXAMPLE_CLIENT_SRC_AUTOCONNECTTRUSTALLSHIPCONNECTORHANDLER_H_ */
