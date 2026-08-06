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
 *  project header files                                                          *
 * ****************************************************************************** */

#include "TrustAllShipTransportConnector.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_json_security_handler/JsonSecurityHandler.h>
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

namespace keo_spine_example_server
{

TrustAllShipTransportConnector::TrustAllShipTransportConnector(
    keo_default_ship_transport::ShipTransportConfigurationPtr shipConfiguration, keo_spine::SpineLinkPtr spineLink)
    : keo_default_ship_transport::ShipTransportConnector(shipConfiguration)
    , configuration(shipConfiguration)
    , spineLink(spineLink)
{
}

TrustAllShipTransportConnector::~TrustAllShipTransportConnector()
{
}

bool TrustAllShipTransportConnector::initialize()
{
    bool success = false;
    // Initialize the security handler
    auto shipSecurityHandler = std::make_shared<keo_json_security_handler::JsonSecurityHandler>();
    if (shipSecurityHandler->init(configuration->getCertificateFullFilename(),
            configuration->getPrivateKeyFullFilename(), configuration->getTruststoreFullFilename()))
    {
        success = initializeShip(configuration->getInstanceName(), shipSecurityHandler, spineLink);
    }

    if (!success)
    {
        LOG_ERROR() << "Cannot initialize SHIP";
    }
    return success;
}

bool TrustAllShipTransportConnector::start(bool autoconnect)
{
    if (!startServer())
    {
        LOG_ERROR() << "Cannot start server";
        return false;
    }
    // connect to all devices
    setAutoConnect(autoconnect);
    // set register flag to true and start discovery
    if (!startDiscovery(true))
    {
        LOG_ERROR() << "Cannot start discovery";
        return false;
    }
    return true;
}

void TrustAllShipTransportConnector::stop()
{
    stopDiscovery();
    stopServer();
}

unsigned short TrustAllShipTransportConnector::onTrustCertificate(keo_default_ship_transport::ShipConnection* node,
    const std::string& ski, const keo_ship::X509Certificate& certificate)
{
    (void)node;
    (void)ski;
    (void)certificate;

    // Everyone is trusted
    return keo_ship::TrustLevel::TRUST_VALUE_USER_USER_VERIFIED;
}

unsigned short TrustAllShipTransportConnector::onValidatePin(
    keo_default_ship_transport::ShipConnection* node, const std::string& pin)
{
    (void)node;
    (void)pin;
    // Every pin is valid
    return keo_ship::TrustLevel::TRUST_VALUE_2NDFACTOR_PIN;
}
}
