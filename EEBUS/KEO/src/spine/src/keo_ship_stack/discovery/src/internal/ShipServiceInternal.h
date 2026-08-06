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

#ifndef KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVEREDSERVICE_H_
#define KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVEREDSERVICE_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_ship_discovery/ShipDiscovery.h>

#include "KEOZeroconfService.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship_discovery
{

class ShipServiceInternal
{
public:
    ShipServiceInternal();
    virtual ~ShipServiceInternal();

    std::string getHostname() const;
    void setHostname(const std::string& hostname);
    unsigned short getPort() const;
    void setPort(unsigned short port);
    std::string getIdentifier() const;
    void setIdentifier(const std::string& identifier);
    std::string getPath() const;
    void setPath(const std::string& path);
    std::string getSki() const;
    void setSki(const std::string& ski);
    bool isRegister() const;
    void setRegister(bool registerFlag);
    std::string getBrand() const;
    void setBrand(const std::string& brand);
    std::string getType() const;
    void setType(const std::string& type);
    std::string getModel() const;
    void setModel(const std::string& model);
    std::string getURI() const;
    void setURI(const std::string& uri);
    std::string getInstanceName() const;
    void setInstanceName(const std::string& instanceName);
    std::string getIpAddress() const;
    void setIpAddress(const std::string& ipAddress);
    int getNetworkInterfaceId() const;
    void setNetworkInterfaceId(int interfaceId);
    std::string getNetworkInterfaceString() const;
    bool isAddressIpv6LinkLocal() const;

    static bool isAddressIpv6LinkLocal(const std::string& address);
    static ShipService createFromKEOZeroconfService(const KEOZeroconfService& service);
    static std::string createURI(const ShipService& shipService, bool useIpAddress = false);

private:
    std::string hostname;
    unsigned short port;
    std::string identifier;
    std::string path;
    std::string ski;
    bool registerFlag;
    std::string brand;
    std::string type;
    std::string model;
    std::string uri;
    std::string ipAddress;
    int interfaceId;
    std::string instanceName;
};

} /* namespace keo_ship_discovery */

/** @}
 * end of file
 */

#endif /* KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVEREDSERVICE_H_ */
