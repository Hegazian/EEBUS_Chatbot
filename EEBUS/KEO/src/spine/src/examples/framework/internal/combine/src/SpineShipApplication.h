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

#ifndef _SPINESHIPAPPLICATION_H_
#define _SPINESHIPAPPLICATION_H_

#include <keo_spine/SpineLink.h>
#include <keo_ship_discovery/ShipDiscovery.h>
#include <keo_simple_ship_transport/SimpleShipTransportConnector.h>
#include <keo_json_security_handler/JsonSecurityHandler.h>
#include <keo_util/KETimer.h>

#include "spine/SpineMeasurement.h"

namespace keo_spine_combine_app
{

class SpineShipApplication final : public keo_simple_ship_transport::SimpleShipTransportConnectorHandler,
                                   public keo_ship_discovery::ShipDiscoveryInterface,
                                   public keo_spine::DeviceCallbackInterface,
                                   public keo_util::TimerHandlerInterface
{
public:
    SpineShipApplication();

    virtual ~SpineShipApplication();

    void setSpineDeviceName(const std::string& deviceName);

    void setShipId(const std::string& shipId);

    bool start(const std::string& certificateFullFilename, const std::string& privateKeyFullFilename,
               const std::string& truststoreFullFilename);

    void stop();

    void setShipDiscoveryRegisterFlag(bool registerFlag);

    void setShipDiscoveryBrand(const std::string& brand);

    void setShipDiscoveryModel(const std::string& model);

    void setShipDiscoveryType(const std::string& type);

    void setShipDiscoveryInstanceLabel(const std::string& instanceLabel);

    void setShipDiscoveryIgnoreRegisterFlag(bool ignoreRegisterFlag);

    void setPublishShipService(bool publishShipService);

    void setStartShipServer(bool startShipServer);

    void setShipPort(int port);

    void setSpineMeasurementServer(bool measurementServer);

    void setDDModification(int timeoutInSec);

    void setDisconnectTimeout(int timeoutInSec);

private:
    unsigned short onTrustCertificate(keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection,
                                      const std::string& ski, const keo_ship::X509Certificate& certificate) override;

    void onPinRequest(keo_simple_ship_transport::ShipTransportConnectionWeakPtr connection) override;
    void onServiceAdded(const keo_ship_discovery::ShipService& service) override;
    void onServiceRemoved(const keo_ship_discovery::ShipService& service) override;
    void onOwnServiceRegistered(const keo_ship_discovery::ShipService& service) override;
    void onOwnServiceRemoved(const keo_ship_discovery::ShipService& service) override;

private:
    void onConnected(const std::string& transportId) override;
    void onDisconnect(const std::string& transportId) override;
    void onDetailedDiscoveryFailed(const std::string& transportId) override;
    void onNewDevices(const std::vector<std::string>& devices) override;
    void onRemovedDevices(const std::vector<std::string>& devices) override;
    void onDetailedDiscovery(const std::string& deviceName,
                             const keo_datagram::DetailedDiscovery& detailedDiscovery) override;
    void onDetailedDiscoveryPartial(const std::string& deviceName,
                                    const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override;

private:
    void handleTimer(keo_util::Timer::id_t timerId) override;

private:
    keo_json_security_handler::JsonSecurityHandlerPtr shipSecurityHandler;
    keo_ship_discovery::ShipDiscovery shipDiscovery;
    keo_simple_ship_transport::SimpleShipTransportConnector shipConnector;
    keo_spine::SpineLink spineLink;
    std::string deviceName;
    std::string shipId;
    std::string brand;
    std::string model;
    std::string type;
    std::string instanceLabel;
    bool publishShipService;
    int shipPort;
    bool registerFlag;
    bool ignoreRegisterFlag;
    bool startShipServer;
    bool measurementServer;
    int modifyDDTimeoutInSec;
    int disconnectTimeoutInSec;
    keo_spine::SmartDevicePtr device;
    keo_util::Timer timer;
    keo_util::Timer::id_t modifyDDTimerId;
    keo_util::Timer::id_t disconnectTimerId;
};

inline void SpineShipApplication::setSpineDeviceName(const std::string& deviceName)
{
    this->deviceName = deviceName;
}

inline void SpineShipApplication::setShipId(const std::string& shipId)
{
    this->shipId = shipId;
}

inline void SpineShipApplication::setShipDiscoveryRegisterFlag(bool registerFlag)
{
    this->registerFlag = registerFlag;
}

inline void SpineShipApplication::setShipDiscoveryBrand(const std::string& brand)
{
    this->brand = brand;
}

inline void SpineShipApplication::setShipDiscoveryModel(const std::string& model)
{
    this->model = model;
}

inline void SpineShipApplication::setShipDiscoveryType(const std::string& type)
{
    this->type = type;
}

inline void SpineShipApplication::setShipDiscoveryInstanceLabel(const std::string& instanceLabel)
{
    this->instanceLabel = instanceLabel;
}

inline void SpineShipApplication::setPublishShipService(bool publishShipService)
{
    this->publishShipService = publishShipService;
}

inline void SpineShipApplication::setShipPort(int port)
{
    shipPort = port;
}

inline void SpineShipApplication::setShipDiscoveryIgnoreRegisterFlag(bool ignoreRegisterFlag)
{
    this->ignoreRegisterFlag = ignoreRegisterFlag;
}

inline void SpineShipApplication::setStartShipServer(bool startShipServer)
{
    this->startShipServer = startShipServer;
}

inline void SpineShipApplication::setSpineMeasurementServer(bool measurementServer)
{
    this->measurementServer = measurementServer;
}

inline void SpineShipApplication::setDDModification(int timeoutInSec)
{
    modifyDDTimeoutInSec = timeoutInSec;
}

inline void SpineShipApplication::setDisconnectTimeout(int timeoutInSec)
{
    disconnectTimeoutInSec = timeoutInSec;
}
}

#endif /* _SPINESHIPAPPLICATION_H_ */
