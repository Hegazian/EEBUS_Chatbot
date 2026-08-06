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
#include "internal/ShipServiceInternal.h"
#include "internal/ShipDiscoveryInternal.h"

#include <keo_ship_discovery/ShipDiscovery.h>

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

ShipDiscovery::ShipDiscovery(
    const std::string& serviceType, const std::string& serviceDomain, ShipDiscoveryInterface* discoveryInterface)
    : d(new ShipDiscoveryInternal(serviceType, serviceDomain, discoveryInterface))
{
}

ShipDiscovery::~ShipDiscovery()
{
    delete d;
}

std::string ShipDiscovery::getServiceInstanceLabel() const
{
    return d->getServiceName();
}

void ShipDiscovery::setServiceInstanceLabel(const std::string& serviceInstance)
{
    d->setServiceName(serviceInstance);
}

std::string ShipDiscovery::getTxtRecordBrand() const
{
    return d->getBrand();
}

void ShipDiscovery::setTxtRecordBrand(const std::string& brand)
{
    d->setBrand(brand);
}

std::string ShipDiscovery::getTxtRecordType() const
{
    return d->getType();
}

void ShipDiscovery::setTxtRecordType(const std::string& type)
{
    d->setType(type);
}

std::string ShipDiscovery::getTxtRecordModel() const
{
    return d->getModel();
}

void ShipDiscovery::setTxtRecordModel(const std::string& model)
{
    d->setModel(model);
}

std::string ShipDiscovery::getServiceType() const
{
    return d->getServiceType();
}

void ShipDiscovery::setServiceType(const std::string& type)
{
    d->setServiceType(type);
}

std::string ShipDiscovery::getServiceDomain() const
{
    return d->getServiceDomain();
}

void ShipDiscovery::setServiceDomain(const std::string& serviceDomain)
{
    d->setServiceDomain(serviceDomain);
}

bool ShipDiscovery::getTxtRecordRegister() const
{
    return d->isRegister();
}

void ShipDiscovery::setTxtRecordRegister(bool registerFlag)
{
    d->setRegister(registerFlag);
}

void ShipDiscovery::registerService(
    const std::string& identifier, const std::string& wssPath, const std::string& ski, unsigned short port) const
{
    d->registerService(identifier, wssPath, ski, "", port);
}

void ShipDiscovery::registerService(const std::string& identifier, const std::string& wssPath, const std::string& ski,
    const std::string& host, unsigned short port) const
{
    d->registerService(identifier, wssPath, ski, host, port);
}

void ShipDiscovery::unregisterService()
{
    d->unregisterService();
}

void ShipDiscovery::startServiceResolver()
{
    d->startServiceResolver();
}

void ShipDiscovery::stopServiceResolver()
{
    d->stopServiceResolver();
}

bool ShipDiscovery::isServiceRegistered() const
{
    return d->isRegisterActive();
}

bool ShipDiscovery::isServiceResolverStarted() const
{
    return d->isResolverActive();
}

std::list<ShipService> ShipDiscovery::getDiscoveredServiceList() const
{
    return d->getDiscoveredServiceList();
}

void ShipDiscovery::logDiscoveredService(const ShipService& shipService)
{
    LOG_INFO() << "SHIP Service on " << shipService.getHostname() << " (" << shipService.getIpAddress()
               << ")";
    LOG_INFO() << "port       : " << shipService.getPort();
    LOG_INFO() << "identifier : " << shipService.getIdentifier();
    LOG_INFO() << "path       : " << shipService.getPath();
    LOG_INFO() << "register   : " << (shipService.isRegister() ? "true" : "false");
    LOG_INFO() << "SKI        : " << shipService.getSki();

    if (!shipService.getBrand().empty())
    {
        LOG_INFO() << "brand      : " << shipService.getBrand();
    }

    if (!shipService.getType().empty())
    {
        LOG_INFO() << "type       : " << shipService.getType();
    }

    if (!shipService.getModel().empty())
    {
        LOG_INFO() << "model      : " << shipService.getModel();
    }

    if (!shipService.getURI().empty())
    {
        LOG_INFO() << "URI        : " << shipService.getURI();
    }

    if (shipService.getNetworkInterfaceId() >= 0)
    {
        LOG_INFO() << "interface  : " << shipService.getNetworkInterfaceString();
    }
}

std::string ShipDiscovery::createUriWithIpAddress(const ShipService& shipService)
{
    return ShipServiceInternal::createURI(shipService, true);
}
}
/* namespace keo_ship_discovery */
