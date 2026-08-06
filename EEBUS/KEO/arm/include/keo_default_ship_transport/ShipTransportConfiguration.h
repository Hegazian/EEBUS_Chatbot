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

#ifndef KEO_SPINE_CONTROL_TRANSPORTCONFIGURATION_H_
#define KEO_SPINE_CONTROL_TRANSPORTCONFIGURATION_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>
#include <memory>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_default_ship_transport
{

/**
 * @ingroup keo_default_ship_transport
 * @{
 */

class ShipTransportConfiguration
{
public:
    ShipTransportConfiguration()
        : connectionPort(0)
        , maxConnections(1)
    {
    }

    /**
     * Gets the SHIP host address.
     *
     * @return the SHIP host address
     */
    std::string getSHIPHostAddress() const
    {
        return connectionHost;
    }

    /**
     * Sets the SHIP host address.
     *
     * @param inetAddresses
     *            the new SHIP host address
     */
    void setSHIPHostAddress(const std::string& connectionHost)
    {
        this->connectionHost = connectionHost;
    }

    /**
     * Gets the SHIP host port.
     *
     * @return the SHIP host port
     */
    int getSHIPHostPort() const
    {
        return connectionPort;
    }

    /**
     * Sets the SHIP host port.
     *
     * @param connectionPort
     *            the new SHIP host port
     */
    void setSHIPHostPort(int connectionPort)
    {
        this->connectionPort = connectionPort;
    }

    /**
     * Gets the own certificate path.
     *
     * @return the own certificate path
     */
    std::string getCertificateFullFilename() const
    {
        return certificateFullFilename;
    }

    /**
     * Sets the own certificate path.
     *
     * @param fileNameKeyStore
     *            the new own certificate path
     */
    void setCertificateFullFilename(const std::string& certificateFullFilename)
    {
        this->certificateFullFilename = certificateFullFilename;
    }

    /**
     * Gets the own private key path.
     *
     * @return the own private key path
     */
    std::string getPrivateKeyFullFilename() const
    {
        return privateKeyFullFilename;
    }

    /**
     * Sets the own private key path.
     *
     * @param privateKeyFullFilename
     *            the own private key path
     */
    void setPrivateKeyFullFilename(const std::string& privateKeyFullFilename)
    {
        this->privateKeyFullFilename = privateKeyFullFilename;
    }

    /**
     * Gets the trust store path.
     *
     * @return the trust store path
     */
    std::string getTruststoreFullFilename() const
    {
        return truststoreFullFilename;
    }

    /**
     * Sets the trust store path.
     *
     * @param truststoreFullFilename
     *            the trust store path
     */
    void setTruststoreFullFilename(const std::string& truststoreFullFilename)
    {
        this->truststoreFullFilename = truststoreFullFilename;
    }

    /**
     * Gets the ship id.
     *
     * @return the ship id
     */
    std::string getShipId() const
    {
        return shipId;
    }

    /**
     * Sets the ship id.
     *
     * @param shipId
     *            the new ship id
     */
    void setShipId(const std::string& shipId)
    {
        this->shipId = shipId;
    }

    /**
     * Gets the pin.
     *
     * @return the pin
     */
    std::string getShipPin() const
    {
        return pin;
    }

    /**
     * Sets the pin.
     *
     * @param pin
     *            the new pin
     */
    void setShipPin(const std::string& pin)
    {
        this->pin = pin;
    }

    /**
     * Gets the pin requirement.
     *
     * @return the pin requirement
     */
    std::string getShipPinRequirement() const
    {
        return pinRequirement;
    }

    /**
     * Sets the pin requirement.
     *
     * @param pinRequirement
     *            the new pin requirement
     */
    void setShipPinRequirement(const std::string& pinRequirement)
    {
        this->pinRequirement = pinRequirement;
    }

    /**
     * Gets the max connections.
     *
     * @return the max connections
     */
    int getMaxConnections() const
    {
        return maxConnections;
    }

    /**
     * Sets the max connections.
     *
     * @param maxConnections
     *            the new max connections
     */
    void setMaxConnections(int maxConnections)
    {
        this->maxConnections = maxConnections;
    }

    /**
     * Gets the brand.
     *
     * @return the brand
     */
    std::string getBrand() const
    {
        return brand;
    }

    /**
     * Sets the brand.
     *
     * @param brand
     *            the new brand
     */
    void setBrand(const std::string& brand)
    {
        this->brand = brand;
    }

    /**
     * Gets the type.
     *
     * @return the type
     */
    std::string getType() const
    {
        return type;
    }

    /**
     * Sets the type.
     *
     * @param type
     *            the new type
     */
    void setType(const std::string& type)
    {
        this->type = type;
    }

    /**
     * Gets the model.
     *
     * @return the model
     */
    std::string getModel() const
    {
        return model;
    }

    /**
     * Sets the model.
     *
     * @param model
     *            the new model
     */
    void setModel(const std::string& model)
    {
        this->model = model;
    }

    /**
     * Gets the instance name.
     *
     * @return the instance name
     */
    std::string getInstanceName() const
    {
        return instanceName;
    }

    /**
     * Sets the instance name.
     *
     * @param instanceName
     *            the new instance name
     */
    void setInstanceName(const std::string& instanceName)
    {
        this->instanceName = instanceName;
    }

    /**
     * Gets the ship configuration.
     *
     */
    keo_ship::ShipStackConfiguration getShipConfiguration() const;

private:
    /** The connection host. */
    std::string connectionHost;
    /** The connection port. */
    int connectionPort;
    /** The own certificate path. */
    std::string certificateFullFilename;
    /** The own private key path. */
    std::string privateKeyFullFilename;
    /** The trust store path. */
    std::string truststoreFullFilename;
    /** The ship id. */
    std::string shipId;
    /** The pin. */
    std::string pin;
    /** The pin. */
    std::string pinRequirement;
    /** The max connections. */
    int maxConnections;
    /** The brand. */
    std::string brand;
    /** The type. */
    std::string type;
    /** The model. */
    std::string model;
    /** The instance name. */
    std::string instanceName;
};

//! typedef for non-const smart pointer type ShipTransportConfiguration
typedef std::shared_ptr<ShipTransportConfiguration> ShipTransportConfigurationPtr;

//! typedef for const type ShipTransportConfiguration
typedef const ShipTransportConfiguration ShipTransportConfigurationConst;

//! typedef for const smart pointer type ShipTransportConfiguration
typedef std::shared_ptr<ShipTransportConfigurationConst> ShipTransportConfigurationConstPtr;

/** @} */ //  end of group

} /* namespace keo_default_ship_transport */

#endif /* KEO_SPINE_CONTROL_TRANSPORTCONFIGURATION_H_ */
