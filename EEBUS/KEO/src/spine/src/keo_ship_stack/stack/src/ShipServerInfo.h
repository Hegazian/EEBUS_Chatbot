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

#ifndef KEO_SHIP_STACK_TRANSPORT_SRC_SHIPSERVERINFO_H_
#define KEO_SHIP_STACK_TRANSPORT_SRC_SHIPSERVERINFO_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <list>
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

/** @ingroup ship
 * @{
 */

class ShipServerInfo
{
public:
    /**
     * Constructor
     *
     * @param shipStackConfiguration the SHIP stack's configuration
     * @param ski the SKI to be used
     */
    ShipServerInfo(ShipStackConfiguration& shipStackConfiguration, const std::string& ski)
        : shipStackConfiguration(shipStackConfiguration)
        , ski(Ski::normalize(ski))
        , hosts()
        , serverPort(0)
        , socketPath()
    {
    }

    virtual ~ShipServerInfo()
    {
    }

    /**
     * Get the stack configuration
     *
     * @return the stack configuration
     */
    ShipStackConfiguration getShipStackConfiguration() const
    {
        return shipStackConfiguration;
    }

    /**
     * Get the SKI
     *
     * @return the SKI
     */
    std::string getSki() const
    {
        return ski;
    }

    /**
     * Set the server's interfaces
     *
     * @param hosts the hosts to use
     * @param serverPort the port to use
     * @param string the socket path to use
     */
    void setServerInterfaces(const std::list<std::string>& hosts, int serverPort, const std::string& socketPath)
    {
        this->hosts = hosts;
        this->serverPort = serverPort;
        this->socketPath = socketPath;
    }

    /**
     * Get the hosts
     *
     * @return the hosts
     */
    std::list<std::string> getHosts() const
    {
        return hosts;
    }

    /**
     * Get the server port
     *
     * @return the server port
     */
    int getServerPort() const
    {
        return serverPort;
    }

    /**
     * Get the socket path
     *
     * @return the socket path
     */
    std::string getSocketPath() const
    {
        return socketPath;
    }

private:
    ShipStackConfiguration shipStackConfiguration;
    std::string ski;
    std::list<std::string> hosts; // java type: InetAddress[]
    int serverPort;
    std::string socketPath;
};

/** @} */ //  end of group shipstack_transport

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_TRANSPORT_SRC_SHIPSERVERINFO_H_ */
