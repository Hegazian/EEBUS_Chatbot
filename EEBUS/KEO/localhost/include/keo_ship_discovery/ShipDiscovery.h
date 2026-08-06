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
/**
 *     @brief      Ship Discovery
 *
 *     @par        The Ship Discovery API
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_DISCOVERY_INCLUDE_KEO_SHIP_DISCOVERY_SHIPDISCOVERY_H_
#define KEO_SHIP_STACK_DISCOVERY_INCLUDE_KEO_SHIP_DISCOVERY_SHIPDISCOVERY_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <list>
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
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

namespace keo_ship_discovery
{

/**
 * @addtogroup ship
 * @{
 */

/**
 * @defgroup ship_discovery Discovery
 * ShipDiscovery offers an API to announce own services and status on the network
 * and to discovering services and statuses announced by remote nodes.
 * @{
 */

class ShipDiscoveryInternal;
class ShipService;
class ShipDiscoveryInterface;

/**
 * @class ShipDiscovery
 * ShipDiscovery offers an API to announce own services and status on the network
 * and to discovering services and statuses announced by other remote nodes.
 * @n
 * Example discovery service data:
 * @n
 * Service instance name:
 * @code{.unparsed}
     "Dishwasher Bosch SMI69T45EU._ship._tcp.local."
      \_________________________/ \________/ \___/
                  |                   |        |
        serviceInstanceLabel          |        |
                                 serviceType   |
                                          serviceDomain
 * @endcode
 * @n
 * Service TXT records:
 * @n
 * @code{.unparsed}
    Key          Value                       Example Runtime     Behaviour   Required

    register     Boolean                     register=true       Static      Mandatory
    brand        String with brand           brand=Bosch         Static      Optional
    type         String with device type     type=Dishwasher     Static      Optional
    model        String with model           model=SMI69T45EU    Static      Optional
 * @endcode
 * @n
 *
 */
class ShipDiscovery
{
public:
    /**
     * Construct a ShipDiscovery instance.
     * @param serviceType Type of the local service to announce (eg. _ship._tcp).
     * @param serviceDomain Domain of the local service to announce (eg. local).
     * @param discoveryInterface Callback interface pointer, to inform user implementation about servis changes (local
     * and remote).
     */
    ShipDiscovery(
        const std::string& serviceType, const std::string& serviceDomain, ShipDiscoveryInterface* discoveryInterface);
    /**
     * Destructor
     */
    virtual ~ShipDiscovery();

    /**
     * Returns the service type (e.g. _ship._tcp).
     * @return The service type.
     */
    std::string getServiceType() const;

    /**
     * Sets the service type (e.g. _ship._tcp).
     * @param type The service type.
     */
    void setServiceType(const std::string& type);

    /**
     * Returns the service domain (e.g. local).
     * @return The service domain.
     */
    std::string getServiceDomain() const;

    /**
     * Sets the service domain (e.g. local).
     * @param serviceDomain The service domain.
     */
    void setServiceDomain(const std::string& serviceDomain);

    /**
     * Returns the service instance (e.g. "Dishwasher Bosch 498 SMI69T45EU").
     * @return The service instance.
     */
    std::string getServiceInstanceLabel() const;

    /**
     * Sets the service instance (e.g. "Dishwasher Bosch 498 SMI69T45EU").
     * @param serviceInstance The service instance.
     */
    void setServiceInstanceLabel(const std::string& serviceInstance);

    /**
     * Returns the optional brand of the device announced by the service (empty if not set).
     * @return The brand.
     */
    std::string getTxtRecordBrand() const;

    /**
     * Sets the optional brand of the device announced by the service.
     * @param brand The brand.
     */
    void setTxtRecordBrand(const std::string& brand);

    /**
     * Returns the optional type (e.g. washer, dryer, ...) of the device announced by the service (empty if not set).
     * @return The type.
     */
    std::string getTxtRecordType() const;

    /**
     * Sets the optional type (e.g. washer, dryer, ...) of the device announced by the service.
     * @param type The type.
     */
    void setTxtRecordType(const std::string& type);

    /**
     * Returns the optional model of the device announced by the service (empty if not set).
     * @return The type.
     */
    std::string getTxtRecordModel() const;

    /**
     * Sets the optional model of the device announced by the service.
     * @param model The model.
     */
    void setTxtRecordModel(const std::string& model);

    /**
     * Set the register flag indicating that this node accepts new connections.
     * If this service is currently registered on the network
     * @see registerService the state will be updated automatically in place.
     * @param registerFlag
     */
    void setTxtRecordRegister(bool registerFlag);

    /**
     * Returns the register flag indicating that the node accepts new connections if true.
     * @return The register flag.
     */
    bool getTxtRecordRegister() const;

    /** Register a new service on the network.
     * Publish the configured parameter periodically to become visible to other nodes.
     * @param identifier Unique identifier.
     * @param wssPath Path, e.g. /ship/.
     * @param ski SKI of the service.
     * @param port Port of the service.
     * Will call @see onOwnServiceAdded (@see ShipDiscoveryInterface).
     */
    void registerService(
        const std::string& identifier, const std::string& wssPath, const std::string& ski, unsigned short port) const;

    /** Register a new service on the network.
     * Publish the configured parameter periodically to become visible to other nodes.
     * @param identifier Unique identifier.
     * @param wssPath Path, e.g. /ship/.
     * @param ski SKI of the service.
     * @param address The address of the interface the service should be announced on (the service will be announced for
     * all addresses on that interface).
     * @param port Port of the service.
     * Will call @see onOwnServiceAdded (@see ShipDiscoveryInterface).
     */
    void registerService(const std::string& identifier, const std::string& wssPath, const std::string& ski,
        const std::string& address, unsigned short port) const;

    /**
     * Unregisters current registered service.
     * Will call @see  onOwnServiceRemoved (@see  ShipDiscoveryInterface).
     */
    void unregisterService();

    /**
     * Returns if service is currently registered.
     * @return true for active registering, otherwise false.
     */
    bool isServiceRegistered() const;

    /**
     * Starts the service resolver to discover other services announced on the local network.
     * Will call @see onServiceAdded and @see onServiceRemoved
     * (@see  ShipDiscoveryInterface.h).
     */
    void startServiceResolver();

    /**
     * Stops the service resolver.
     */
    void stopServiceResolver();

    /**
     * Returns if the resolver is currently active.
     * @return true for active resolver, otherwise false.
     */
    bool isServiceResolverStarted() const;

    /**
     * Returns all discovered remote services.
     * The own registered service is not part of the list.
     * @return List of discovered services.
     */
    std::list<ShipService> getDiscoveredServiceList() const;

    /**
     * Logs out the discovered service (loglevel INFO).
     * @param shipService The service to log.
     */
    static void logDiscoveredService(const ShipService& shipService);

    /**
     * Returns an URI with resolved IP address (IPv6 link-local addresses are extended by interface).
     * Examples:
     *      wss://192.168.0.1:4711/ship/                            (IPv4)
     *      wss://[fe80::a00:27ff:febc:9797%25eth0]:4711/ship/      (IPv6 link-local)
     *      wss://[2001:db8:85a3::8a2e:370:7334]:4711/ship/         (IPv6 global)
     *
     * Connecting to an IP address breaks ServerNameIndication (SNI).
     * Use with care!
     *
     * @param shipService ShipService
     * @return URI with IP address (empty on error)
     */
    static std::string createUriWithIpAddress(const ShipService& shipService);

private:
    ShipDiscovery(const ShipDiscovery& rhs);
    ShipDiscovery& operator=(const ShipDiscovery& rhs);
    ShipDiscoveryInternal* d;
};

class ShipServiceInternal;

/**
 * @class ShipService
 * The ShipService offers a central API for services discovered on the network.
 * It collects all informations of remote services on the network needed by the application.
 *
 * Services are announced by nodes to publish their features and ability to retrieve connections.
 */
class ShipService
{
public:
    /**
     * Constructs an instance of this class and allocate all needed ressources.
     **/
    ShipService();

    /**
     * Destroys the local instance and releases all ressources.
     * */
    virtual ~ShipService();

    /**
     * Copy Constructor
     **/
    ShipService(const ShipService& rhs);

    /**
     * Copy operator
     **/
    ShipService& operator=(const ShipService& rhs);

    /**
     * Returns the hostname of the service
     *
     * @return hostname
     */
    std::string getHostname() const;

    /**
     * Sets the hostname of the service
     *
     * @param hostname
     */
    void setHostname(const std::string& hostname) const;

    /**
     * Returns the port of the service
     *
     * @return port
     */
    unsigned short getPort() const;

    /**
     * Sets the port of the service
     *
     * @param port
     */
    void setPort(unsigned short port) const;

    /**
     * Returns the identifier of the service
     *
     * @return identifier
     */
    std::string getIdentifier() const;

    /**
     * Sets the identifier of the service
     *
     * @param identifier
     */
    void setIdentifier(const std::string& identifier) const;

    /**
     * Returns the path of the service
     *
     * @return path
     */
    std::string getPath() const;

    /**
     * Sets the path of the service
     *
     * @param path
     */
    void setPath(const std::string& path) const;

    /**
     * Returns the instance name of the service
     *
     * @return instanceName
     */
    std::string getInstanceName() const;

    /**
     * Sets the instance name of the service
     *
     * @param instanceName
     */
    void setInstanceName(const std::string& instanceName) const;

    /**
     * Returns the SKI of the service
     *
     * @return ski
     */
    std::string getSki() const;

    /**
     * Sets the SKI of the service
     *
     * @param ski
     */
    void setSki(const std::string& ski) const;

    /**
     * Returns the register flag of the service
     *
     * @return registerFlag
     */
    bool isRegister() const;

    /**
     * Sets the register flag of the service
     *
     * @param registerFlag
     */
    void setRegister(bool registerFlag) const;

    /**
     * Returns the brand description of the service
     *
     * @return brand
     */
    std::string getBrand() const;

    /**
     * Sets the brand description of the service
     *
     * @param brand
     */
    void setBrand(const std::string& brand) const;

    /**
     * Returns the type description of the service
     *
     * @return type
     */
    std::string getType() const;

    /**
     * Sets the type description of the service
     *
     * @param type
     */
    void setType(const std::string& type) const;

    /**
     * Returns the model description of the service
     *
     * @return model
     */
    std::string getModel() const;

    /**
     * Sets the model description of the service
     *
     * @param model
     */
    void setModel(const std::string& model) const;

    /**
     * Returns the URI of the service
     *
     * @return uri
     */
    std::string getURI() const;

    /**
     * Sets the URI of the service
     *
     * @param uri
     */
    void setURI(const std::string& uri) const;

    /**
     * Returns the IP address of the service
     *
     * @return ipAddress
     */
    std::string getIpAddress() const;

    /**
     * Sets the IP address of the service
     *
     * @param ipAddress
     */
    void setIpAddress(const std::string& ipAddress) const;

    /**
     * Returns the network interface id of the service
     *
     * @return interfaceId
     */
    int getNetworkInterfaceId() const;

    /**
     * Sets the network interface id of the service
     *
     * @param interfaceId
     */
    void setNetworkInterfaceId(int interfaceId) const;

    /**
     * Returns the network interface of the service as string
     *
     * @return interfaceString
     */
    std::string getNetworkInterfaceString() const;

    /**
     * Checks if resolved address is IPv6 link-local
     *
     * @return true if IPv6 link-local, otherwise false
     */
    bool isAddressIpv6LinkLocal() const;

private:
    ShipServiceInternal* d;
};

/**
 * @class ShipDiscoveryInterface
 * ShipDiscoveryInterface implements a callback mechanism to inform the user about discovery events.
 *
 * This class is abstract by intention. Implementations of this interface are vendor-
 * and/or application-specific.
 */
class ShipDiscoveryInterface
{
public:
    virtual ~ShipDiscoveryInterface()
    {
    }

    /**
     * Callback called when new service has been added to the network.
     * @param service The service added.
     */
    virtual void onServiceAdded(const ShipService& service) = 0;

    /**
     * Callback called when new service has been removed from the network.
     * @param service The service removed.
     */
    virtual void onServiceRemoved(const ShipService& service) = 0;

    /**
     * Callback called when own service has been registered on the network.
     * @param service The service registered.
     */
    virtual void onOwnServiceRegistered(const ShipService& service) = 0;

    /**
     * Callback called when own service has been removed from the network.
     * @param service The service removed.
     */
    virtual void onOwnServiceRemoved(const ShipService& service) = 0;
};

/** @}
 * ship_discovery
 */

/** @}
 * ship
 */

} /* namespace keo_ship_discovery */

#endif /* KEO_SHIP_STACK_DISCOVERY_INCLUDE_KEO_SHIP_DISCOVERY_SHIPDISCOVERY_H_ */
