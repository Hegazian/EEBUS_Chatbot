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

#ifndef KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVERYINTERNAL_H_
#define KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVERYINTERNAL_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <list>
#include <map>
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

class KEOZeroconf;

namespace keo_ship_discovery
{

class ShipDiscoveryInterface;
class ShipDiscoveryInterfaceInternal;

class ShipDiscoveryInternal
{
public:
    ShipDiscoveryInternal(
        const std::string& serviceType, const std::string& serviceDomain, ShipDiscoveryInterface* interface);
    virtual ~ShipDiscoveryInternal();

    std::string getServiceName() const;
    void setServiceName(const std::string& serviceName);
    std::string getBrand() const;
    void setBrand(const std::string& brand);
    std::string getType() const;
    void setType(const std::string& type);
    std::string getModel() const;
    void setModel(const std::string& model);
    std::string getServiceType() const;
    void setServiceType(const std::string& type);
    std::string getServiceDomain() const;
    void setServiceDomain(const std::string& serviceDomain);
    bool isRegister() const;
    void setRegister(bool registerFlag);
    void registerService(const std::string& identifier, const std::string& wssPath, const std::string& ski,
        const std::string& host, unsigned short port);
    void unregisterService();
    void startServiceResolver();
    void stopServiceResolver();
    bool isRegisterActive() const;
    bool isResolverActive() const;
    std::list<ShipService> getDiscoveredServiceList() const;

private:
    std::list<std::pair<std::string, std::string> > getProperties();

    std::string brand;
    std::string type;
    std::string model;
    std::string serviceType;
    bool registerFlag;
    std::string identifier;
    std::string wssPath;
    std::string ski;

    bool registerActive;
    bool resolverActive;

    ShipDiscoveryInterfaceInternal* discoveryInterfaceInternal;
    KEOZeroconfService service;
    KEOZeroconf* zeroconf;
};

} /* namespace keo_ship */

/** @}
 * end of file
 */

#endif /* KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVERYINTERNAL_H_ */
