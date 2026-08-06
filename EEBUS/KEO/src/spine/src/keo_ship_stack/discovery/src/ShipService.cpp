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

#include <keo_ship_discovery/ShipDiscovery.h>

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

ShipService::ShipService()
    : d(new ShipServiceInternal())
{
}

ShipService::~ShipService()
{
    delete d;
}

ShipService::ShipService(const ShipService& rhs)
    : d(new ShipServiceInternal(*rhs.d))
{
}

ShipService& ShipService::operator=(const ShipService& rhs)
{
    if (this != &rhs)
    {
        *d = *rhs.d;
    }
    return *this;
}

std::string ShipService::getHostname() const
{
    return d->getHostname();
}

void ShipService::setHostname(const std::string& hostname) const
{
    d->setHostname(hostname);
}

unsigned short ShipService::getPort() const
{
    return d->getPort();
}

void ShipService::setPort(unsigned short port) const
{
    d->setPort(port);
}

std::string ShipService::getIdentifier() const
{
    return d->getIdentifier();
}

void ShipService::setIdentifier(const std::string& identifier) const
{
    d->setIdentifier(identifier);
}

std::string ShipService::getPath() const
{
    return d->getPath();
}

void ShipService::setPath(const std::string& path) const
{
    d->setPath(path);
}

std::string ShipService::getSki() const
{
    return d->getSki();
}

void ShipService::setSki(const std::string& ski) const
{
    d->setSki(ski);
}

bool ShipService::isRegister() const
{
    return d->isRegister();
}

void ShipService::setRegister(bool registerFlag) const
{
    d->setRegister(registerFlag);
}

std::string ShipService::getInstanceName() const
{
    return d->getInstanceName();
}

void ShipService::setInstanceName(const std::string& instanceName) const
{
    d->setInstanceName(instanceName);
}

std::string ShipService::getBrand() const
{
    return d->getBrand();
}

void ShipService::setBrand(const std::string& brand) const
{
    d->setBrand(brand);
}

std::string ShipService::getType() const
{
    return d->getType();
}

void ShipService::setType(const std::string& type) const
{
    d->setType(type);
}

std::string ShipService::getModel() const
{
    return d->getModel();
}

void ShipService::setModel(const std::string& model) const
{
    return d->setModel(model);
}

std::string ShipService::getURI() const
{
    return d->getURI();
}

void ShipService::setURI(const std::string& uri) const
{
    d->setURI(uri);
}

std::string ShipService::getIpAddress() const
{
    return d->getIpAddress();
}

void ShipService::setIpAddress(const std::string& ipAddress) const
{
    d->setIpAddress(ipAddress);
}

int ShipService::getNetworkInterfaceId() const
{
    return d->getNetworkInterfaceId();
}

void ShipService::setNetworkInterfaceId(int interfaceId) const
{
    d->setNetworkInterfaceId(interfaceId);
}

std::string ShipService::getNetworkInterfaceString() const
{
    return d->getNetworkInterfaceString();
}

bool ShipService::isAddressIpv6LinkLocal() const
{
    return d->isAddressIpv6LinkLocal();
}

} /* namespace keo_ship_discovery */
