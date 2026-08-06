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
#include <net/if.h>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ShipServiceInternal.h"

#include <keo_util/KELogging.h>
#include <map>
#include <sstream>

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

ShipServiceInternal::ShipServiceInternal()
    : port(0)
    , registerFlag(false)
    , interfaceId(-1)
{
}

ShipServiceInternal::~ShipServiceInternal()
{
}

std::string ShipServiceInternal::getHostname() const
{
    return hostname;
}

void ShipServiceInternal::setHostname(const std::string& hostname)
{
    this->hostname = hostname;
}

unsigned short ShipServiceInternal::getPort() const
{
    return port;
}

void ShipServiceInternal::setPort(unsigned short port)
{
    this->port = port;
}

std::string ShipServiceInternal::getIdentifier() const
{
    return identifier;
}

void ShipServiceInternal::setIdentifier(const std::string& identifier)
{
    this->identifier = identifier;
}

std::string ShipServiceInternal::getPath() const
{
    return path;
}

void ShipServiceInternal::setPath(const std::string& path)
{
    this->path = path;
}

std::string ShipServiceInternal::getSki() const
{
    return ski;
}

void ShipServiceInternal::setSki(const std::string& ski)
{
    this->ski = ski;
}

bool ShipServiceInternal::isRegister() const
{
    return registerFlag;
}

void ShipServiceInternal::setRegister(bool registerFlag)
{
    this->registerFlag = registerFlag;
}

std::string ShipServiceInternal::getBrand() const
{
    return brand;
}

void ShipServiceInternal::setBrand(const std::string& brand)
{
    this->brand = brand;
}

std::string ShipServiceInternal::getType() const
{
    return type;
}

void ShipServiceInternal::setType(const std::string& type)
{
    this->type = type;
}

std::string ShipServiceInternal::getModel() const
{
    return model;
}

void ShipServiceInternal::setModel(const std::string& model)
{
    this->model = model;
}

std::string ShipServiceInternal::getURI() const
{
    return uri;
}

void ShipServiceInternal::setURI(const std::string& uri)
{
    this->uri = uri;
}

std::string ShipServiceInternal::getIpAddress() const
{
    return ipAddress;
}

void ShipServiceInternal::setIpAddress(const std::string& ipAddress)
{
    this->ipAddress = ipAddress;
}

int ShipServiceInternal::getNetworkInterfaceId() const
{
    return interfaceId;
}

void ShipServiceInternal::setNetworkInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

std::string ShipServiceInternal::getInstanceName() const
{
    return instanceName;
}

void ShipServiceInternal::setInstanceName(const std::string& instanceName)
{
    this->instanceName = instanceName;
}

std::string ShipServiceInternal::getNetworkInterfaceString() const
{
    std::string interfaceStr;
    char ifname[IF_NAMESIZE + 1];

    // The interfaceId is only set for discovered services not for "local" services
    if (interfaceId != -1)
    {
        if (NULL != if_indextoname(interfaceId, ifname))
        {
            interfaceStr = ifname;
        }
        else
        {
            LOG_WARN() << "Could not get name for interfaceId: " << interfaceId;
        }
    }
    return interfaceStr;
}

bool ShipServiceInternal::isAddressIpv6LinkLocal() const
{
    return ShipServiceInternal::isAddressIpv6LinkLocal(ipAddress);
}

bool ShipServiceInternal::isAddressIpv6LinkLocal(const std::string& address)
{
    if (address.size() >= 4 && address.substr(0, 4) == "fe80")
    {
        return true;
    }
    return false;
}

std::string ShipServiceInternal::createURI(const ShipService& shipService, bool useIpAddress)
{
    std::string uri;
    std::string address;

    if (useIpAddress)
    {
        address = shipService.getIpAddress();
        if (!address.empty())
        {
            // check if address is IPv6
            if (address.find(":") != std::string::npos)
            {
                // add %interface if address is link-local
                if (ShipServiceInternal::isAddressIpv6LinkLocal(address))
                {
                    std::string networkInterface = shipService.getNetworkInterfaceString();
                    if (!networkInterface.empty())
                    {
                        address += "%25" + networkInterface;
                    }
                    else
                    {
                        address = ""; // error
                    }
                }

                // add brackets around ipv6 address (if not empty)
                if (!address.empty())
                {
                    address = "[" + address + "]";
                }
            }
        }
    }
    else
    {
        address = shipService.getHostname();
    }

    // get port
    std::ostringstream ss;
    ss << shipService.getPort();
    std::string port = ss.str();

    // get path
    std::string path = shipService.getPath();

    if (address.empty() || port.empty() || "0" == port || path.empty())
    {
        LOG_WARN() << "Could not create URI from service: Address, port or path is empty or invalid";
    }
    else
    {
        uri = "wss://" + address + ":" + port + path;
        DEBUG_INFO() << "URI created from service: '" << uri << "'";
    }

    return uri;
}

ShipService ShipServiceInternal::createFromKEOZeroconfService(const KEOZeroconfService& service)
{
    ShipService shipService;
    shipService.setHostname(service.mHost);
    shipService.setPort(service.mPort);
    shipService.setIpAddress(service.mAddress);
    shipService.setNetworkInterfaceId(service.mInterfaceId);
    shipService.setInstanceName(service.mName);

    std::map<std::string, std::string> txtMap;
    for (auto txtPair : service.mTxt)
    {
        txtMap.insert(txtPair);
    }
    shipService.setIdentifier(txtMap["id"]);
    shipService.setPath(txtMap["path"]);
    shipService.setRegister(txtMap["register"] == "true");
    shipService.setSki(txtMap["ski"]);
    shipService.setBrand(txtMap["brand"]);
    shipService.setType(txtMap["type"]);
    shipService.setModel(txtMap["model"]);

    return shipService;
}

} /* namespace keo_ship_discovery */
