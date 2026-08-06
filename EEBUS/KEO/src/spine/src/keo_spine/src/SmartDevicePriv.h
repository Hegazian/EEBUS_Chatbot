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

#ifndef KEO_FRAMEWORK_SMARTDEVICEPRIV_H_
#define KEO_FRAMEWORK_SMARTDEVICEPRIV_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                        *
 * ****************************************************************************** */

#include <keo_spine/SendServiceInterface.h>
#include <keo_spine/SmartDevice.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include "DeviceTransportIdHandler.h"
#include "EntityHandler.h"
#include "TimeoutService.h"

#include <keo_tool/KEJobRunner.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <mutex>
#include <string>
#include <vector>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

class SmartDevice::SmartDevicePriv : private EntityHandler::EntityHandlerInterface
{
private:
    /** Spine Link and transport id handling */
    class SpineLinkService : public SpineLinkReceiveServiceInterface, private TimeoutServiceInterface
    {
    public:
        SpineLinkService(SmartDevicePriv& smartDevice, std::recursive_mutex& mtx)
            : smartDevice(smartDevice)
            , spineLinkSendService(0)
            , timeoutService(this)
            , mtx(mtx)
        {
            jobRunner = keo_tool::KEJobRunner::start();
        }

        virtual ~SpineLinkService()
        {
            if (jobRunner->isRunning())
            {
                keo_tool::KEJobRunner::stop(jobRunner);
            }
            delete jobRunner;
        }

        SpineLinkService(const SpineLinkService& that) = delete;
        SpineLinkService& operator=(const SpineLinkService&) = delete;

        inline void setSpineLinkSendService(SpineLinkSendServiceInterface* spineLinkSendService);

        inline bool isSpineLinkSendServiceSet() const;

        bool containsTransportIdForDevice(const std::string& deviceName) const;

        TransportId getTransportIdForDevice(const std::string& deviceName) const;

        std::vector<std::string> getDevicesForTransportId(const TransportId& transportId) const;

        std::map<std::string, std::vector<TransportId>> getDeviceTransportIds() const;

        std::vector<TransportId> getTransportIds() const;

        void addDeviceTransportId(const std::string& deviceName, const TransportId& transportId);

        bool isDirectlyConnectedDevice(const std::string& deviceName) const;

        void removeDeviceTransportId(const std::string& deviceName, const TransportId& transportId);

        void addDirectlyConnectedDevice(const std::string& deviceName, const std::string& transportId);

        void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId);

        void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId);

        bool sendDatagramRecordToTransportConnection(const DatagramRecord& datagramRecord);

    private:
        void handleParseError(const DatagramRecord& record);

        void rewriteDatagramHeaderAddress(keo_datagram::Datagram& datagram, const TransportId& transportId);

        bool handleNodeManagementDetailedDiscoveryReply(const DatagramRecord& datagramRecord);

        // TimeoutServiceInterface
        void timeout(keo_datagram::xs_unsignedLong msgCounter) override;

        // SpineLinkReceiveServiceInterface
        virtual void addConnection(TransportId transportId) override;

        // SpineLinkReceiveServiceInterface
        virtual void removeConnection(TransportId transportId) override;

        // SpineLinkReceiveServiceInterface
        virtual void onDatagram(DatagramRecord& record) override;

        void distributeDatagram(const DatagramRecord& record);

    private:
        SmartDevicePriv& smartDevice;
        SpineLinkSendServiceInterface* spineLinkSendService;
        DeviceTransportIdHandler deviceTransportIdHandler;
        std::map<keo_datagram::xs_unsignedLong, TransportId> pendingDetailedDiscovery;
        TimeoutService timeoutService;
        keo_tool::KEJobRunner* jobRunner;
        std::recursive_mutex& mtx;
        // A map for buffering incoming datagrams while the DetailedDiscovery on a connection is still pending
        std::map<TransportId, std::vector<DatagramRecord>> bufferedDatagrams;
    };

private:
    /** Sub-Device handling */
    class SubDeviceHandler : public SpineLinkSendServiceInterface
    {
    public:
        SubDeviceHandler(SmartDevicePriv& smartDevice, std::recursive_mutex& mtx)
            : smartDevice(smartDevice)
            , mtx(mtx)
        {
        }

        virtual ~SubDeviceHandler();

        bool addSubDevice(SmartDevicePtr subDevice);

        SmartDevicePtr removeSubDevice(const std::string& deviceName);

        std::vector<SmartDevicePtr> getSubDevices() const;

        void onNewDevices(const std::vector<std::string>& devices);

        void onRemovedDevices(const std::vector<std::string>& devices);

        void onDetailedDiscovery(
            const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery);

        void onDetailedDiscoveryPartial(
            const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial);

        void onUseCaseDiscovery(const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery);

        keo_datagram::xs_unsignedInt onDatagram(DatagramRecord& datagramRecord);

        void close();

    private:
        // SpineLinkSendServiceInterface
        virtual bool sendDatagram(const DatagramRecord& datagramRecord) override;

    private:
        SmartDevicePriv& smartDevice;
        std::map<std::string, SmartDevicePtr> subDevices;
        std::recursive_mutex& mtx;
    };

private:
    /** Send service for features */
    class SmartDeviceSendService : public SendServiceInterface, private TimeoutServiceInterface
    {
    public:
        SmartDeviceSendService(SmartDevicePriv& smartDevice, std::recursive_mutex& mtx)
            : smartDevice(smartDevice)
            , timeoutService(this)
            , mtx(mtx)
        {
        }

        virtual ~SmartDeviceSendService()
        {
        }

    private:
        bool canSendDatagram(const DatagramRecord& datagramRecord);

        bool setTransportId(DatagramRecord& datagramRecord);

        void addAckRequest(DatagramRecord& datagramRecord);

    private:
        // TimeoutServiceInterface
        void timeout(keo_datagram::xs_unsignedLong msgCounter) override;

        // SendServiceInterface
        virtual std::string getDeviceName() const override;

        // SendServiceInterface
        virtual bool sendDatagram(DatagramRecord& datagramRecord) override;

        // SendServiceInterface
        virtual keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecord& datagramRecord) override;

        // SendServiceInterface
        virtual keo_datagram::xs_unsignedLong sendPendingDatagram(
            DatagramRecord& datagramRecord, long timeout) override;

        // SendServiceInterface
        virtual bool removeTimeoutByMsgCounter(keo_datagram::xs_unsignedLong msgCounter) override;

        // SendServiceInterface
        virtual bool isConnected(const std::string& deviceName) const override;

    private:
        SmartDevicePriv& smartDevice;
        TimeoutService timeoutService;

        friend SmartDevice;

        /*
         *  Maps message counters to a pair [sender feature address, transport Id the datagrams has been sent on]
         */
        std::map<keo_datagram::xs_unsignedLong, std::pair<keo_datagram::FeatureAddress, TransportId>>
            pendingTimeoutsByMessageCounter;

        std::recursive_mutex& mtx;
    };

public:
    SmartDevicePriv();

    virtual ~SmartDevicePriv();

    typedef std::shared_ptr<SpineLinkService> SpineLinkServicePtr;
    typedef std::weak_ptr<SpineLinkService> SpineLinkServiceWeakPtr;

    inline void setSpineLinkSendService(SpineLinkSendServiceInterface* spineLinkSendService);

    inline void setDeviceCallbackListener(DeviceCallbackInterface* deviceCallbackInterface);

    inline void setPrimaryDeviceInformationEntity(PrimaryDeviceInformationEntityPtr entity);

    inline void setUnhandledDatagramInterface(UnhandledDatagramInterface* unhandledDatagramHandler);

    bool initialize();

    void close();

    inline bool addSubDevice(SmartDevicePtr subDevice);

    inline SmartDevicePtr removeSubDevice(const std::string& deviceName);

    inline std::vector<SmartDevicePtr> getSubDevices() const;

    inline keo_datagram::DetailedDiscoveryConstPtr getDetailedDiscovery() const;

    std::string getDeviceName() const;

    inline bool addEntity(EntityPtr entity);

    inline void removeEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity);

    inline EntityPtr getEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity) const;

    inline std::vector<EntityPtr> getEntities() const;

    void ensureInitializedDevice() const;

    bool isInitialized() const;

    bool validate();

    inline bool sendSmartDeviceDatagram(const DatagramRecord& datagramRecord);

    inline SpineLinkServiceWeakPtr getSpineLinkService();

    std::string toString() const;

    inline void setDeviceDescription(const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription);

    inline const keo_datagram::NetworkManagementDeviceDescriptionData& getDeviceDescription() const;

private:
    // EntityHandlerInterface
    void onNewDevices(const std::vector<std::string>& devices, const TransportId& transportId) override;

    // EntityHandlerInterface
    void onRemovedDevices(const std::vector<std::string>& devices, const TransportId& transportId) override;

    // EntityHandlerInterface
    void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery) override;

    // EntityHandlerInterface
    void onDetailedDiscoveryPartial(
        const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial) override;

    // EntityHandlerInterface
    void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery) override;

    bool addEntity(EntityPtr entity, bool entityZero);

private:
    std::recursive_mutex mtx;
    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription;
    DeviceCallbackInterface* deviceCallbackInterface;
    UnhandledDatagramInterface* unhandledDatagramHandler;
    EntityHandler entityHandler;
    SpineLinkServicePtr spineLinkService;
    SubDeviceHandler subDeviceHandler;
    SmartDeviceSendService smartDeviceSendService;
    std::atomic_bool initialized;
    std::string deviceName;
};

inline void SmartDevice::SmartDevicePriv::setDeviceDescription(
    const keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription)
{
    if (isInitialized())
    {
        LOG_ERROR() << "Cannot set device description on already initialized " << this->toString();
    }
    this->deviceDescription = deviceDescription;
}

inline const keo_datagram::NetworkManagementDeviceDescriptionData&
SmartDevice::SmartDevicePriv::getDeviceDescription() const
{
    return deviceDescription;
}

inline void SmartDevice::SmartDevicePriv::setSpineLinkSendService(SpineLinkSendServiceInterface* spineLinkSendService)
{
    spineLinkService->setSpineLinkSendService(spineLinkSendService);
}

inline void SmartDevice::SmartDevicePriv::setDeviceCallbackListener(DeviceCallbackInterface* deviceCallbackInterface)
{
    this->deviceCallbackInterface = deviceCallbackInterface;
}

inline void SmartDevice::SmartDevicePriv::setPrimaryDeviceInformationEntity(PrimaryDeviceInformationEntityPtr entity)
{
    entity->setPrimaryNodeManagementInterface(&entityHandler);
    addEntity(entity, true);
}

inline void SmartDevice::SmartDevicePriv::setUnhandledDatagramInterface(
    UnhandledDatagramInterface* unhandledDatagramHandler)
{
    this->unhandledDatagramHandler = unhandledDatagramHandler;
}

inline bool SmartDevice::SmartDevicePriv::addSubDevice(SmartDevicePtr subDevice)
{
    if (!isInitialized())
    {
        LOG_ERROR() << "Cannot add " << subDevice->toString() << " to uninitialized " << this->toString();
        return false;
    }
    else if (!subDevice->isInitialized())
    {
        LOG_ERROR() << "Cannot add uninitialized " << subDevice->toString() << " to " << this->toString();
        return false;
    }

    return subDeviceHandler.addSubDevice(subDevice);
}

inline SmartDevicePtr SmartDevice::SmartDevicePriv::removeSubDevice(const std::string& deviceName)
{
    return subDeviceHandler.removeSubDevice(deviceName);
}

inline std::vector<SmartDevicePtr> SmartDevice::SmartDevicePriv::getSubDevices() const
{
    return subDeviceHandler.getSubDevices();
}

inline keo_datagram::DetailedDiscoveryConstPtr SmartDevice::SmartDevicePriv::getDetailedDiscovery() const
{
    DEBUG_FUNC();
    return entityHandler.getDetailedDiscovery(deviceDescription);
}

inline bool SmartDevice::SmartDevicePriv::addEntity(EntityPtr entity)
{
    return addEntity(entity, false);
}

inline void SmartDevice::SmartDevicePriv::removeEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity)
{
    entityHandler.removeEntity(entity);
}

inline EntityPtr SmartDevice::SmartDevicePriv::getEntity(const std::vector<keo_datagram::xs_unsignedInt>& entity) const
{
    return entityHandler.getEntity(entity);
}

inline std::vector<EntityPtr> SmartDevice::SmartDevicePriv::getEntities() const
{
    return entityHandler.getEntities();
}

inline bool SmartDevice::SmartDevicePriv::sendSmartDeviceDatagram(const DatagramRecord& datagramRecord)
{
    std::lock_guard<std::recursive_mutex> locker(mtx);
    return spineLinkService->sendDatagramRecordToTransportConnection(datagramRecord);
}

inline SmartDevice::SmartDevicePriv::SpineLinkServiceWeakPtr SmartDevice::SmartDevicePriv::getSpineLinkService()
{
    return spineLinkService;
}

inline void SmartDevice::SmartDevicePriv::SpineLinkService::setSpineLinkSendService(
    SpineLinkSendServiceInterface* spineLinkSendService)
{
    this->spineLinkSendService = spineLinkSendService;
}

inline bool SmartDevice::SmartDevicePriv::SpineLinkService::isSpineLinkSendServiceSet() const
{
    return 0 != spineLinkSendService;
}

inline void SmartDevice::SmartDevicePriv::close()
{
    entityHandler.close();
    subDeviceHandler.close();
    initialized = false;
}

/** @} */ //  end of group framework

} // namespace keo_spine

#endif /* KEO_FRAMEWORK_SMARTDEVICEPRIV_H_ */
