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
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ShipDiscoveryInternal.h"
#include "KEOZeroconf.h"
#include "ShipServiceInternal.h"
#include "ShipDiscoveryInterfaceInternal.h"

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship_discovery
{

ShipDiscoveryInternal::ShipDiscoveryInternal(
    const std::string& serviceType, const std::string& serviceDomain, ShipDiscoveryInterface* interface)
    : serviceType(serviceType)
    , registerFlag(true)
    , registerActive(false)
    , resolverActive(false)
    , discoveryInterfaceInternal(new ShipDiscoveryInterfaceInternal(interface))
    , zeroconf(new KEOZeroconf(serviceType, discoveryInterfaceInternal))
{
    service.mDomain = serviceDomain;

    bool ret = zeroconf->init();
    if (!ret)
    {
        LOG_ERROR() << "Error while initializing Zeroconf!";
    }
}

ShipDiscoveryInternal::~ShipDiscoveryInternal()
{
    delete zeroconf;
    delete discoveryInterfaceInternal;
}

std::string ShipDiscoveryInternal::getServiceName() const
{
    return service.mName;
}

void ShipDiscoveryInternal::setServiceName(const std::string& serviceName)
{
    service.mName = serviceName;
}

std::string ShipDiscoveryInternal::getBrand() const
{
    return brand;
}

void ShipDiscoveryInternal::setBrand(const std::string& brand)
{
    this->brand = brand;
}

std::string ShipDiscoveryInternal::getType() const
{
    return type;
}

void ShipDiscoveryInternal::setType(const std::string& type)
{
    this->type = type;
}

std::string ShipDiscoveryInternal::getModel() const
{
    return model;
}

void ShipDiscoveryInternal::setModel(const std::string& model)
{
    this->model = model;
}

std::string ShipDiscoveryInternal::getServiceType() const
{
    return serviceType;
}

void ShipDiscoveryInternal::setServiceType(const std::string& type)
{
    this->serviceType = type;
}

std::string ShipDiscoveryInternal::getServiceDomain() const
{
    return service.mDomain;
}

void ShipDiscoveryInternal::setServiceDomain(const std::string& serviceDomain)
{
    service.mDomain = serviceDomain;
}

bool ShipDiscoveryInternal::isRegister() const
{
    return registerFlag;
}

void ShipDiscoveryInternal::setRegister(bool registerFlag)
{
    if (this->registerFlag != registerFlag)
    {
        this->registerFlag = registerFlag;
        service.mTxt = getProperties();
        if (registerActive)
        {
            zeroconf->updateServiceTxtRecord(service);
        }
    }
}

void ShipDiscoveryInternal::registerService(const std::string& identifier, const std::string& wssPath,
    const std::string& ski, const std::string& host, unsigned short port)
{
    if (!registerActive)
    {
        this->identifier = identifier;
        this->wssPath = wssPath;
        this->ski = ski;
        service.mPort = port;

        if (0 == service.mName.size())
        {
            service.mName = identifier;
        }

        if (0 == service.mHost.size())
        {
            service.mHost = host;
        }

        service.mTxt = getProperties();
        registerActive = zeroconf->registerService(service, false);
    }
}

void ShipDiscoveryInternal::unregisterService()
{
    if (registerActive)
    {
        registerActive = !zeroconf->registerService(service, true);
    }
}

void ShipDiscoveryInternal::startServiceResolver()
{
    if (!resolverActive)
    {
        resolverActive = zeroconf->browseServices();
    }
}

void ShipDiscoveryInternal::stopServiceResolver()
{
    if (resolverActive)
    {
        zeroconf->stopBrowseServices();
        resolverActive = false;
    }
}

bool ShipDiscoveryInternal::isRegisterActive() const
{
    return registerActive;
}

bool ShipDiscoveryInternal::isResolverActive() const
{
    return resolverActive;
}

std::list<ShipService> ShipDiscoveryInternal::getDiscoveredServiceList() const
{
    std::list<ShipService> shipServicesList;
    for (auto zcService : zeroconf->getBrowsedServices())
    {
        if (!zcService.mOwnService)
        {
            ShipService shipService = ShipServiceInternal::createFromKEOZeroconfService(zcService);
            shipService.setURI(ShipServiceInternal::createURI(shipService));
            shipServicesList.push_back(shipService);
        }
    }
    return shipServicesList;
}

std::list<std::pair<std::string, std::string> > ShipDiscoveryInternal::getProperties()
{
    std::list<std::pair<std::string, std::string> > props;
    props.push_back(std::pair<std::string, std::string>("txtvers", "1"));
    props.push_back(std::pair<std::string, std::string>("id", identifier));
    props.push_back(std::pair<std::string, std::string>("path", wssPath));
    props.push_back(std::pair<std::string, std::string>("register", registerFlag ? "true" : "false"));
    props.push_back(std::pair<std::string, std::string>("ski", ski));
    if (!brand.empty())
    {
        props.push_back(std::pair<std::string, std::string>("brand", brand));
    }
    if (!type.empty())
    {
        props.push_back(std::pair<std::string, std::string>("type", type));
    }
    if (!model.empty())
    {
        props.push_back(std::pair<std::string, std::string>("model", model));
    }
    return props;
}
}
/* namespace keo_ship_discovery */
