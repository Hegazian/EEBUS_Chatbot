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
#ifndef EXAMPLES_FRAMEWORK_SIMPLEEXAMPLE_SERVER_SRC_TRUSTALLSHIPTRANSPORTCONNECTOR_H_
#define EXAMPLES_FRAMEWORK_SIMPLEEXAMPLE_SERVER_SRC_TRUSTALLSHIPTRANSPORTCONNECTOR_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_default_ship_transport/ShipTransportConnector.h>
#include <keo_spine/SpineLink.h>

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

namespace keo_spine_example_server
{

/**
 * @addtogroup framework_example_server
 * @{
 */

class TrustAllShipTransportConnector : public keo_default_ship_transport::ShipTransportConnector
{
public:
    /**
     * Constructor
     * @param configuration
     */
    TrustAllShipTransportConnector(
        keo_default_ship_transport::ShipTransportConfigurationPtr configuration, keo_spine::SpineLinkPtr spineLink);

    /**
     * Destructor
     */
    virtual ~TrustAllShipTransportConnector();

    bool initialize();

    bool start(bool autoconnect);

    void stop();

    /**
     * Callback to check if the certificate is trusted. The trust level is
     * USER_VERIFIED if it is trusted.
     *
     * @param node
     *            SHIP connection
     * @param ski
     *            SKI of the certificate
     * @param certificate
     *            Received certificate
     * @return user trust level
     */
    unsigned short onTrustCertificate(keo_default_ship_transport::ShipConnection* node, const std::string& ski,
        const keo_ship::X509Certificate& certificate) override;

    /**
     * Callback to check if the pin is valid.
     *
     * @param node
     *            Interface to the connection
     * @param pin
     *            Received pin
     * @return pin trust level
     */
    unsigned short onValidatePin(keo_default_ship_transport::ShipConnection* node, const std::string& pin) override;

private:
    keo_default_ship_transport::ShipTransportConfigurationPtr configuration;
    keo_spine::SpineLinkPtr spineLink;
};

/** @} */ //  end of group framework_example_server

} // namespace keo_spine_example_server

#endif /* EXAMPLES_FRAMEWORK_SIMPLEEXAMPLE_SERVER_SRC_TRUSTALLSHIPTRANSPORTCONNECTOR_H_ */
