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

#ifndef KEO_FRAMEWORK_SRC_PRIMARYNODEMANAGEMENTFEATURE_H_
#define KEO_FRAMEWORK_SRC_PRIMARYNODEMANAGEMENTFEATURE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                        *
 * ****************************************************************************** */

#include <keo_spine/DatagramRecord.h>
#include <keo_spine/PrimaryNodeManagementInterface.h>
#include <keo_spine/ServerFeature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/BindingManagementEntryData.h>
#include <keo_datagram/core/DestinationList.h>
#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/NodeManagementBindingData.h>
#include <keo_datagram/core/NodeManagementBindingDeleteCall.h>
#include <keo_datagram/core/NodeManagementBindingRequestCall.h>
#include <keo_datagram/core/NodeManagementSubscriptionData.h>
#include <keo_datagram/core/NodeManagementSubscriptionDeleteCall.h>
#include <keo_datagram/core/NodeManagementSubscriptionRequestCall.h>
#include <keo_datagram/core/NodeManagementUseCaseData.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <map>
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

class PrimaryNodeManagementFeature;

/**
 * typedef for non-const smart pointer type PrimaryNodeManagementFeature
 */
typedef std::shared_ptr<PrimaryNodeManagementFeature> PrimaryNodeManagementFeaturePtr;

/**
 * typedef for const type PrimaryNodeManagementFeature
 */
typedef const PrimaryNodeManagementFeature PrimaryNodeManagementFeatureConst;

/**
 * typedef for const smart pointer type PrimaryNodeManagementFeature
 */
typedef std::shared_ptr<PrimaryNodeManagementFeatureConst> PrimaryNodeManagementFeatureConstPtr;

/** @ingroup framework
 * @{
 */

/**
 * A basic implementation for a primary NodeManagement feature.
 *
 * This feature behaves differently depending on the list of supported functions. You can use {@link
 * createBasicNodeManagementFeature()} to create a primary NodeManagement feature with a list of supported functions
 * that we consider a reasonable default.
 * Or, if your requirements differ you have to create an instance of this class and set the supported
 * functions manually.
 *
 * <h3>Subscriptions and Bindings</h3>
 *
 * If the list of supported functions contains NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL
 * this feature is able to manage subscriptions (add NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL to be able to delete
 * subscriptions).
 * If the list of supported functions contains NODE_MANAGEMENT_BINDING_REQUEST_CALL this
 * feature is able to manage bindings (add NODE_MANAGEMENT_BINDING_DELETE_CALL
 * to be able to delete bindings).
 *
 * Just as with any other ServerFeature (although the primary NodeManagement feature has the type "Special"), you can
 * overwrite {@link allowBinding()} and {@link allowSubscription()} to only
 * allow bindings and subscriptions from certain clients.
 *
 * If the list of supported functions contains NODE_MANAGEMENT_SUBSCRIPTION_DATA and/or
 * NODE_MANAGEMENT_BINDING_DATA clients are able to read subscriptions and
 * bindings from all sibling features of this feature. Note that this feature will only reply with subscriptions and
 * bindings of the client that has sent the READ datagram.
 *
 * <h3>Extending this class</h3>
 *
 * If you need to extend this class, the easiest way is to overwrite one of the many specific handle methods (e.g.
 * handleDestinationListRead()). If there is no existing handle method for the type of datagram you need to react upon,
 * you can simply overwrite {@link handleDatagram()}, e.g. like this
 *
 *     bool MyPrimaryNodeManagementFeature::handleDatagram(DatagramRecordPtr datagramRecord)
 *     {
 *         if(!PrimaryNodeManagementFeature::handleDatagram(datagramRecord)
 *         {
 *            // do your handling here...
 *         }
 *     }
 *
 * The call to PrimaryNodeManagementFeature::handleDatagram() will dispatch the datagram to an existing handle method.
 * You only need to handle the new datagram in your overwritten method.
 *
 * @see keo_datagram::NetworkManagementFeatureDescriptionData#setSupportedFunction()
 *
 */
class PrimaryNodeManagementFeature : public ServerFeature
{
public:
    /**
     * Constructor
     *
     * @param featureDescription
     *            Description of the feature
     */
    explicit PrimaryNodeManagementFeature(
        const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Destructor
     */
    virtual ~PrimaryNodeManagementFeature();

    /**
     * Create a basic primary node management feature. This feature will support
     * the following functions:
     *
     * - FUNCTION_NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA
     * - FUNCTION_NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL
     * - FUNCTION_NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL
     * - FUNCTION_NODE_MANAGEMENT_SUBSCRIPTION_DATA
     * - FUNCTION_NODE_MANAGEMENT_BINDING_REQUEST_CALL
     * - FUNCTION_NODE_MANAGEMENT_BINDING_DELETE_CALL
     * - FUNCTION_NODE_MANAGEMENT_BINDING_DATA
     *
     * If hasDestinationListServer is true, this feature will also support the
     * function FUNCTION_NODE_MANAGEMENT_DESTINATION_LIST_DATA.
     *
     * If automaticSpineDiscovery is true, this feature will automatically discover SPINE devices in the same network.
     * @see PrimaryNodeManagementFeature#setAutomaticSpineDiscovery
     *
     * @param hasDestinationListServer
     *            a flag specifying whether this node offers a destination list
     * @param automaticSpineDiscovery
     *            a flag specifying whether this node automatically discovers
     *            the whole SPINE network
     * @return a PrimaryNodeManagementFeature instance
     */
    static PrimaryNodeManagementFeaturePtr createBasicNodeManagementFeature(bool hasDestinationListServer,
                                                                            bool automaticSpineDiscovery);

    /**
     * Creates a node management detailed discovery request.
     *
     * Entity and feature is set to 0.
     *
     * @param sourceDevice
     *            Source device name or null
     * @param destinationDevice
     *            Destination device name or null
     * @return Node management detailed discovery request
     */
    static keo_datagram::Datagram
    createNodeManagementDetailedDiscoveryRequest(const std::string& sourceDevice, const std::string& destinationDevice);

    /**
     * Creates a node management destination list request.
     *
     * Entity and feature is set to 0.
     *
     * @param sourceDevice
     *            Source device name or null
     * @param destinationDevice
     *            Destination device name or null
     * @return Node management destination list request
     */
    static keo_datagram::Datagram
    createNodeManagementDestinationListRequest(const std::string& sourceDevice, const std::string& destinationDevice);

    /**
     * Returns the detailed discovery data of this device. The detailed
     * discovery data is valid after initialization of the device
     *
     * @return Detailed discovery data
     */
    keo_datagram::DetailedDiscoveryConstPtr getDetailedDiscovery() const;

    /**
     * Sets the detailed discovery data of this device.
     *
     * @param detailedDiscovery
     *            Detailed discovery data
     */
    void setDetailedDiscovery(const keo_datagram::DetailedDiscovery& detailedDiscovery);

    /**
     * Set this device's NodeManagementUseCaseData.
     *
     * This will send notifications to subscription partners if the data has changed.
     *
     * Important: This method will add an appropriate supported function to this feature's description. As a
     * consequence, if this method is called after the associated device has been initialized, the device has to be
     * initialized again.
     *
     * @param useCaseData the use case data to set
     */
    void setUseCaseData(const keo_datagram::NodeManagementUseCaseData& useCaseData);

    /**
     * Get this device's NodeManagementUseCaseData.
     * @return the use case data
     */
    const keo_datagram::NodeManagementUseCaseData& getUseCaseData() const;

    /**
     * Setter of primary node management interface
     *
     * This method is called internally.
     *
     * @param primaryNodeManagementInterface
     *            node management interface to set
     */
    void setPrimaryNodeManagementInterface(PrimaryNodeManagementInterface* primaryNodeManagementInterface);

    /**
     * Getter of primary node management interface
     *
     * @return Primary node management interface
     */
    PrimaryNodeManagementInterface* getPrimaryNodeManagementInterface();

    /**
     * Enable or disable the automatic SPINE discovery. If enabled, this feature
     * will automatically subscribe to primary node management features it finds.
     * Additionally it will send an initial READ to all destination list servers.
     * When a destination list is received, the detailed discoveries of all
     * devices in that destination list are requested.
     *
     * This ensure that this device is always aware of all SPINE devices in its
     * network.
     *
     * Note, that changing this flag after connections have been established
     * might result in inconsistent views on the network.
     *
     * @param automaticSpineDiscovery
     */
    void setAutomaticSpineDiscovery(bool automaticSpineDiscovery);

    /**
     * Returns whether the automatic SPINE discovery is enabled.
     *
     * @see PrimaryNodeManagementFeature#setAutomaticSpineDiscovery
     */
    bool getAutomaticSpineDiscovery();

    bool handleDatagram(const DatagramRecord& datagramRecord) override;

    bool handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo) override;

    bool timeoutHandler(const DatagramMemo& memo) override;

    bool allowBinding(const keo_datagram::FeatureAddress& clientAddress) const override;

    bool allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const override;

    void onDetailedDiscovery(const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery) override;

    void onDetailedDiscoveryPartial(const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscovery) override;

    void onRemovedDevices(const std::vector<std::string>& removedDevices) override;

    /**
     * Send a DetailedDiscovery request
     *
     * @param destination
     *            Destination device
     * @return true if sent successfully
     */
    bool sendDetailedDiscoveryRead(const std::string& destination);

    /**
     * Send a DestinationList request
     *
     * @param deviceName
     *            Destination device
     * @return true, if send
     */
    bool sendDestinationListRead(const std::string& deviceName);

    /**
     * Create a DestinationList notify datagram
     * @return created datagram
     */
    keo_datagram::Datagram createDestinationListNotify();

    /**
     * Add sub devices.
     *
     * This method is called internally.
     *
     * @param subDeviceList
     *            Descriptions of the added devices
     * @return true, if added
     */
    bool addSubDevice(const std::vector<keo_datagram::NetworkManagementDeviceDescriptionData>& subDeviceList);

    /**
     * Remove sub devices.
     *
     * This method is called internally.
     *
     * @param deviceNames
     *            Name of the devices to remove
     * @return true, if removed
     */
    bool removeSubDevice(const std::vector<std::string>& deviceNames);

    /**
     * Send a subscription request to another PrimaryNodeManagementFeature
     *
     * @param deviceName
     *            Name of the device to subscribe to
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    keo_datagram::xs_unsignedLong subscribeToPrimaryNodeManagementFeature(const std::string& deviceName);

    /**
     * Get the timeout (maxResponseDelay) of a remote feature.
     * @param remoteFeatureAddress the address of the remote feature
     * @return the timeout (maxResponseDelay) or 0 if no timeout is specified for the feature
     */
    long getRemoteFeatureTimeout(const keo_datagram::FeatureAddress& remoteFeatureAddress);

    /**
     * Checks whether a remote feature has communicated a maxResponseDelay.
     * @param remoteFeatureAddress the address of the feature
     * @return true, if a timeout is specified
     */
    bool hasRemoteFeatureTimeout(const keo_datagram::FeatureAddress& remoteFeatureAddress);

protected:
    /**
     * Handle a NodeManagementSubscriptionDeleteCall
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementSubscriptionDeleteCall
     * @return true, if handled
     */
    virtual bool handleNodeManagementSubscriptionDeleteCall(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementSubscriptionRequestCall
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementSubscriptionRequestCall
     * @return true, if handled
     */
    virtual bool handleNodeManagementSubscriptionRequestCall(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementBindingDeleteCall
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementBindingDeleteCall
     * @return true, if handled
     */
    virtual bool handleNodeManagementBindingDeleteCall(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementBindingRequestCall
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementBindingRequestCall
     * @return true, if handled
     */
    virtual bool handleNodeManagementBindingRequestCall(const DatagramRecord& datagramRecord);

    /**
     * Handle a SubscriptionManagementEntryListDataRead
     *
     * @param datagramRecord
     *            Datagram with a SubscriptionManagementEntryListDataRead
     * @return true, if handled
     */
    virtual bool handleNodeManagementSubscriptionDataRead(const DatagramRecord& datagramRecord);

    /**
     * Handle a BindingManagementEntryListDataRead
     *
     * @param datagramRecord
     *            Datagram with a BindingManagementEntryListDataRead
     * @return true, if handled
     */
    virtual bool handleNodeManagementBindingDataRead(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementDestinationListRead
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementDestinationListRead
     * @return true, if handled
     */
    virtual bool handleNodeManagementDestinationListRead(const DatagramRecord& datagramRecord);

    /**
     * Create a destination list response from a destination list request.
     *
     * @param datagram
     *            Datagram to create the reply to
     * @return Response of destination list
     */
    keo_datagram::DatagramPtr createDestinationListResponse(const keo_datagram::Datagram& datagram);

    /**
     * Handle a NodeManagementDetailedDiscoveryRead
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementDetailedDiscoveryRead
     * @return true, if handled
     */
    virtual bool handleNodeManagementDetailedDiscoveryRead(const DatagramRecord& datagramRecord);

    /**
     * Create a detailed discovery response from a detailed discovery request
     *
     * @param datagram
     *            Datagram to create the reply to
     * @return Response of detailed discovery
     */
    keo_datagram::Datagram createDetailedDiscoveryResponse(const keo_datagram::Datagram& datagram);

    /**
     * Create a DetailedDiscovery notify.
     *
     * @param destination
     *            the destination of the notify
     * @return a SPINE datagram
     */
    keo_datagram::Datagram createDetailedDiscoveryNotify(const keo_datagram::FeatureAddress& destination);

    /**
     * Handle a NodeManagementDetailedDiscoveryNotify
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementDetailedDiscoveryNotify
     * @return true, if handled
     */
    virtual bool handleNodeManagementDetailedDiscoveryNotify(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementDestinationListNotify
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementDestinationListNotify
     * @return true, if handled
     */
    virtual bool handleNodeManagementDestinationListNotify(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementUseCaseDataNotify
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementUseCaseDataNotify
     * @return true, if handled
     */
    virtual bool handleNodeManagementUseCaseDataNotify(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementDetailedDiscoveryReply
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementDetailedDiscoveryReply
     * @return true, if handled
     */
    virtual bool handleNodeManagementDetailedDiscoveryReply(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementDestinationListReply
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementDestinationListReply
     * @return true, if handled
     */
    virtual bool handleNodeManagementDestinationListReply(const DatagramRecord& datagramRecord);

    /**
     * Handle a NodeManagementUseCaseDataReply
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementUseCaseDataReply
     * @return true, if handled
     */
    virtual bool handleNodeManagementUseCaseDataReply(const DatagramRecord& datagramRecord);

    /**
     * Handle the result of a NodeManagementSubscriptionRequestCall
     *
     * Currently, if you need to persist the subscriptions of this feature, override this method.
     *
     * @param datagramRecord
     *            the incoming datagram
     * @param memo
     *            the initially sent datagram
     * @return true, if handled
     */
    virtual bool handleNodeManagementSubscriptionRequestCallResult(const DatagramRecord& datagramRecord,
                                                                   const DatagramMemo& memo);

    /**
     * Handle a NodeManagementUseCaseDataRead
     *
     * @param datagramRecord
     *            Datagram with a NodeManagementUseCaseDataRead
     * @return true, if handled
     */
    virtual bool handleNodeManagementUseCaseDataRead(const DatagramRecord& datagramRecord);

private:
    /**
     * Updates the local information about a remote feature's maxResponseDelay
     */
    void updateMaxResponseDelay(
        const std::string& deviceName, const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    void sendDatagrams(const std::vector<Association>& allReceivers, const keo_datagram::Datagram& datagram);

    void restrictToNetworkManagementDeviceDescriptionData(
        keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription);

    /**
     * All pending subscriptions this feature has initiated
     */
    std::map<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementSubscriptionRequestCall> pendingSubscriptions;

    PrimaryNodeManagementInterface* primaryNodeManagementInterface;

    /** Detailed discovery data for this device */
    keo_datagram::DetailedDiscoveryPtr ownDetailedDiscovery;

    std::vector<keo_datagram::NetworkManagementDeviceDescriptionData> subDevices;

    /**
     * Flag that specifies if a SPINE network is discovered automatically.
     */
    bool automaticSpineDiscovery;

    /**
     * DestinationList for this device
     */
    keo_datagram::DestinationList destinationList;

    /**
     * This device's use case data
     */
    keo_datagram::NodeManagementUseCaseData useCaseData;

    unsigned int nextSubscriptionId;
    unsigned int nextBindingId;

    /**
     * Maps remote feature addresses to timeouts (maxResponseDelay) that the remote has communicated via its detailed
     * discovery.
     */
    std::map<keo_datagram::FeatureAddress, unsigned long> remoteFeatureTimeouts;

    std::mutex mtx;
};

/** @} */ //  end of group framework
} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_SRC_PRIMARYNODEMANAGEMENTFEATURE_H_ */
