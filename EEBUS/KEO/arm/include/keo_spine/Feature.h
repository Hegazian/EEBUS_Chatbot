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

#ifndef KEO_SPINE_FEATURE_H_
#define KEO_SPINE_FEATURE_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/DetailedDiscoveryPartial.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionData.h>
#include <keo_datagram/core/UseCaseDiscovery.h>
#include <keo_spine/DatagramMemo.h>
#include <keo_spine/DatagramRecord.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

#include <vector>
#include <mutex>
#include <string>

/******************************************************************************* *
 *  defines                                                                      *
 ******************************************************************************* */

/******************************************************************************* *
 *  types                                                                        *
 ******************************************************************************* */

/******************************************************************************* *
 *  class definition                                                             *
 ******************************************************************************* */

namespace keo_spine
{

class Entity;
class SendServiceInterface;

/** @ingroup framework
 * @{
 */

/**
 * Base of all features
 * <p>
 * For role 'client' see {@link ClientFeature}, for role 'server' see {@link ServerFeature}.
 * <p>
 * Several methods exist for sending datagrams.  A pending datagram is a datagram which needs a
 * response.  Received datagrams are handled by {@link handleDatagram()} and
 * {@link handlePendingDatagramResponse()}.  Pending datagrams which are not
 * replied to in time, are to be handled in {@link timeoutHandler()}.
 * <p>
 * If you need to react on DetailedDiscoveries and/or DestinationList updates, you can override
 * {@link #onDetailedDiscovery()}, {@link #onDetailedDiscoveryPartial()} and/or {@link
 * #onRemovedDevices()}.
 * <p>
 * Important: When your feature class uses some sort of lock to protect any of its resources, you
 * need to be careful about when to acquire and when to release the lock. Generally, you should
 * release all application locks before costly functions of the KEO SPINE framework are called (e.g.
 * before sending datagrams).
 */
class Feature
{
public:
    Feature();

    /**
     * Constructor
     *
     * @param featureDescription
     *            Description of the feature
     */
    explicit Feature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Virtual destructor
     */
    virtual ~Feature();

    /**
     * Add a possible operation to this feature (if it does not exist already).
     *
     * Refer to {@see ServerFeature} for predefined possible operations.
     *
     * Important: If this method is called after the associated device has been initialized, the device has to be
     * initialized again for the changes to be visible in the detailed discovery.
     *
     * @param function the function type
     * @param operations the possible operations
     */
    void addPossibleOperation(
        const keo_datagram::Function& function, const keo_datagram::PossibleOperations& operations);

    /**
     * Check if this feature has a possible operation.
     *
     * Refer to {@see ServerFeature} for predefined possible operations.
     *
     * @param function the function type
     * @param operations the possible operations
     * @return true, if this feature has the possible operation in its feature description
     */
    bool hasPossibleOperation(
        const keo_datagram::Function& function, const keo_datagram::PossibleOperations& operations);

    /**
     * Remove all possible operations of a certain function from this feature.
     *
     * Refer to {@see ServerFeature} for predefined possible operations.
     *
     * Important: If this method is called after the associated device has been initialized, the device has to be
     * initialized again for the changes to be visible in the detailed discovery.
     *
     * @param function the function type
     * @return true, if possible operations have been removed
     */
    bool removePossibleOperation(const keo_datagram::Function& function);

    /**
     * Sets the description of the Feature
     *
     * Note that using this method overwrites possible operations previously set by {@see
     * Feature#addPossibleOperation()}.
     *
     * @param featureDescription The description to set
     */
    void setFeatureDescription(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Get own feature description data
     *
     * @return own NetworkManagementFeatureDescriptionData
     */
    const keo_datagram::NetworkManagementFeatureDescriptionData& getFeatureDescription() const;

    /**
     * This method is called when a detailed discovery has been received
     * from a remote device.
     *
     * Overwrite this method if your feature needs to react on detailed
     * discoveries.
     *
     * @param deviceName
     *            Device name
     * @param detailedDiscovery
     *            Detailed discovery information
     */
    virtual void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery);

    /**
     * This method is called when a partial detailed discovery has been received
     * from a remote device.
     *
     * Overwrite this method if your feature needs to react on partial detailed
     * discoveries.
     *
     * @param deviceName
     *            Device name
     * @param detailedDiscoveryPartial
     *            Partial detailed discovery information
     */
    virtual void onDetailedDiscoveryPartial(
        const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial);

    /**
     * Callback to announce use case data of another device.
     *
     * @param deviceName
     *            Name of the device of the UseCaseData
     * @param useCaseDiscovery
     *            a UseCaseDiscovery object containing local and remote NodeManagementUseCaseData
     */
    virtual void onUseCaseDiscovery(
        const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery);

    /**
     * This method is called when one or more indirectly connected devices are not reachable anymore.
     *
     * Overwrite this method if your feature needs to react on disconnected
     * devices.
     *
     * @param devices
     *            List of removed devices
     */
    virtual void onRemovedDevices(const std::vector<std::string>& devices);

    /**
     * Set the send service interface
     *
     * @param sendService
     *            The send service interface
     */
    void setSendService(SendServiceInterface* sendService);

    /**
     * Return the device name of this device.
     *
     * @return the device Name
     */
    std::string getDeviceName() const;

    /**
     * Get the full feature address.
     *
     * @return the full feature address
     */
    keo_datagram::FeatureAddress getFullFeatureAddress() const;

    /**
     * Check if feature address equals the parameter If device is set, also the
     * device name is compared
     *
     * @param otherAddress
     *            Feature address to compare
     * @return true, if equal
     */
    bool equalsFeatureAddress(const keo_datagram::FeatureAddress& otherAddress) const;

    /**
     * Cleanup the feature.
     *
     * Use this to close resources that were opened by your feature.
     *
     * This method is called by the framework when the device shuts down.
     * When overriding this method, make sure to call {@link Feature::onClose} in your implementation.
     */
    virtual void onClose();

    /**
     * Check whether all required attributes are set on this feature.
     *
     * The required attributes are set if and only if all of the following
     * conditions are met:
     * - The feature description has a complete feature address, i.e. one where
     *   entity and feature are set
     * - The feature type is set in the feature description
     * - The role is set in the feature description
     *
     * @return true if all required attributes are set, false otherwise.
     */
    bool validate();

    /**
     * Returns whether a remote device is connected or not.
     *
     * @param deviceName
     *            Device name
     * @return true, if device is reachable
     */
    bool isConnected(const std::string& deviceName);

    /**
     * Send a read datagram
     *
     * @param destination
     *            Datagram destination
     * @param dataType
     *            Command type of the datagram
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    keo_datagram::xs_unsignedLong sendRead(
        const keo_datagram::FeatureAddress& destination, keo_datagram::CmdData::Type dataType);

    /**
     * Send a read datagram
     *
     * @param destination
     *            Datagram destination
     * @param cmd
     *            Read command of the datagram
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    keo_datagram::xs_unsignedLong sendRead(
        const keo_datagram::FeatureAddress& destination, const keo_datagram::Cmd& cmd);

    /**
     * Send a read datagram
     * @deprecated Use keo_datagram::xs_unsignedLong Feature::sendRead(const keo_datagram::FeatureAddress& destination,
     * const keo_datagram::Cmd& cmd) instead.
     * @param destination Datagram destination
     * @param cmd Read command of the datagram
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    keo_datagram::xs_unsignedLong sendRead(const keo_datagram::FeatureAddress& destination, keo_datagram::CmdPtr cmd);

    /**
     * Send a datagram
     *
     * @param destination
     *            Datagram destination
     * @param cmd
     *            Command of the datagram
     * @param cmdClassifier
     *            Classifier of the datagram
     * @param ackRequest
     *            Flag if an ack is needed
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    keo_datagram::xs_unsignedLong send(const keo_datagram::FeatureAddress& destination, const keo_datagram::Cmd& cmd,
        const keo_datagram::CmdClassifier& cmdClassifier, bool ackRequest);

    /**
     * Send a datagram
     * @deprecated Use keo_datagram::xs_unsignedLong Feature::send(const keo_datagram::FeatureAddress& destination,
     * const keo_datagram::Cmd& cmd, const keo_datagram::CmdClassifier& cmdClassifier, bool ackRequest)
     * @param destination Datagram destination
     * @param cmd Command of the datagram
     * @param cmdClassifier Classifier of the datagram
     * @param ackRequest Flag if an ack is needed
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    keo_datagram::xs_unsignedLong send(const keo_datagram::FeatureAddress& destination, keo_datagram::CmdPtr cmd,
        const keo_datagram::CmdClassifier& cmdClassifier, bool ackRequest);

    /**
     * Handle the response to a previously sent pending datagram.
     * <p>
     * This method is called internally.
     *
     * @param datagramRecord
     *            Received datagram
     * @return true, if handled
     */
    bool handlePendingDatagramResponse(const DatagramRecord& datagramRecord);

    /**
     * Callback for when a timeout occurs.
     *
     * @param msgCounter
     *            MessageCounter of the sent datagram
     */
    void timeout(keo_datagram::xs_unsignedLong msgCounter);

    /**
     * Creates a string representation of this feature.
     * @return a string representation of this features
     */
    std::string toString() const;

protected:
    /**
     * Handle a datagram.
     *
     * If the datagram is not supported by your feature, make sure to not send an answer from this method and return
     * false. The framework will send a DATAGRAM_NOT_SUPPORTED reply for every datagram that has not been handled.
     * If you reply to the datagram from this method, true should be returned.
     *
     * @param datagramRecord
     *            Received datagram
     * @return true, if handled
     */
    virtual bool handleDatagram(const DatagramRecord& datagramRecord) = 0;

    /**
     * Handle the response to a previously sent pending datagram.
     *
     * If the datagram is not supported by your feature, make sure to not send an answer from this method and return
     * false. The framework will send a DATAGRAM_NOT_SUPPORTED reply for every datagram that has not been handled.
     * If you reply to the datagram from this method, true should be returned.
     *
     * @param datagramRecord
     *            Received datagram
     * @param memo
     *            Information about the sent datagram
     * @return true, if handled
     */
    virtual bool handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo) = 0;

    /**
     * The timeout handler. This method is called, when the response to a
     * pending datagram did not arrive in time.
     *
     * @param memo
     *            Information about the sent pending datagram
     * @return true, if handled
     */
    virtual bool timeoutHandler(const DatagramMemo& memo) = 0;

    /**
     * Send a datagram (fire and forget).
     * <p>
     * Attention: This datagram does not expect a response. To send a datagram
     * that expects a response use a method for sending pending datagrams.
     *
     * @see sendPendingDatagram(Datagram)
     * @see sendPendingDatagram(DatagramRecord, long)
     *
     * @param datagram
     *            Datagram to send
     * @return true, if sending was successful
     */
    bool sendDatagram(const keo_datagram::Datagram& datagram) const;

    /// @deprecated Use bool Feature::sendDatagram(const keo_datagram::Datagram& datagram) const instead.
    bool sendDatagram(keo_datagram::DatagramPtr datagram) const;

    /**
     * Send a datagram (fire and forget).
     * <p>
     * Attention: This datagram does not expect a response. To send a datagram
     * that expects a response use a method for sending pending datagrams.
     *
     * Calling this method sets transportId in the DatagramRecord to the ID of the connection the datagram has been sent
     * on.
     *
     * @see sendPendingDatagram(Datagram)
     * @see sendPendingDatagram(DatagramRecord, long)
     *
     * @param datagramRecord
     *            Datagram to send
     * @return true, if sending was successful
     */
    bool sendDatagram(DatagramRecord& datagramRecord) const;

    /// @deprecated Use bool Feature::sendDatagram(const DatagramRecord& datagramRecord) const instead.
    bool sendDatagram(DatagramRecordPtr datagramRecord) const;

    /**
     * Send a datagram with an expected response. Either, the global default timeout {@link
     * DeviceDefinition::DatagramTimeoutDelay} or the timeout the remote feature has defined in its
     * {@link keo_datagram::NetworkManagementFeatureDescriptionData} is used.
     * <p>
     * Attention: Datagrams sent with this method expect a response. Received
     * responses are handled in
     * {@link #handlePendingDatagramResponse()}.
     *
     * @param datagram
     *            Datagram to send with an expected response
     * @return messageCounter of the sent datagram (>0 if sending was successful, 0 upon failure)
     */
    keo_datagram::xs_unsignedLong sendPendingDatagram(const keo_datagram::Datagram& datagram);

    /// @deprecated Use keo_datagram::xs_unsignedLong Feature::sendPendingDatagram(const keo_datagram::Datagram&
    /// datagram) instead.
    keo_datagram::xs_unsignedLong sendPendingDatagram(keo_datagram::DatagramPtr datagram);

    /**
     * Send a datagram with an expected response.
     * <p>
     * Attention: Datagrams sent with this method expect a response. Received
     * responses are handled in {@link #handlePendingDatagramResponse()}.
     * If the destination of this request replies a delayed acknowledgement,
     * this delayed acknowledgement is not delivered to a feature, but is
     * considered to fire correct timeouts to {#timeoutHandler(DatagramMemoPtr)
     * (refer to the section on "Delayed acknowledgement" in the SPINE protocol
     * specification to learn more).
     *
     * Calling this method sets transportId in the DatagramRecord to the ID of the connection the datagram has been sent
     * on.
     *
     * @param datagramRecord
     *            Datagram to send with an expected response
     * @param datagramTimeoutDelay
     *            Timeout for pending datagram
     * @return messageCounter of the sent datagram (>0 if sending was successful, 0 upon failure)
     */
    keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecord& datagramRecord, long datagramTimeoutDelay);

    /// @deprecated Use keo_datagram::xs_unsignedLong Feature::sendPendingDatagram(const DatagramRecord& datagramRecord,
    /// long datagramTimeoutDelay) instead.
    keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecordPtr datagramRecord, long datagramTimeoutDelay);

    /**
     * Remove a pending datagram by msgCounter
     *
     * @param msgCounter
     *            messageCounter to identify the datagram
     * @return true, if datagram exists and remove
     */
    DatagramMemo removePendingDatagramByMsgCounter(keo_datagram::xs_unsignedLong msgCounter);

    /**
     * Clear all pending timeouts
     */
    void killAllPendingTimeouts();

    /**
     * Kill a pending timeout timer by msgCounter
     *
     * @param msgCounter
     *            Identifier to datagram
     * @return true, if timer is found and cancel
     */
    bool killPendingTimeout(keo_datagram::xs_unsignedLong msgCounter);

private:
    Feature(const Feature&);

    Feature& operator=(const Feature&);

private:
    keo_datagram::xs_unsignedLong sendDatagram(DatagramRecordPtr datagramRecord, long datagramTimeoutDelay);

    friend class Entity;
    class FeaturePriv;
    FeaturePriv* p;
};

inline keo_datagram::xs_unsignedLong Feature::sendRead(
    const keo_datagram::FeatureAddress& destination, keo_datagram::CmdData::Type dataType)
{
    return sendRead(destination, keo_datagram::Cmd(dataType));
}

inline keo_datagram::xs_unsignedLong Feature::sendRead(
    const keo_datagram::FeatureAddress& destination, keo_datagram::CmdPtr cmd)
{
    return sendRead(destination, *cmd.get());
}

inline keo_datagram::xs_unsignedLong Feature::send(const keo_datagram::FeatureAddress& destination,
    keo_datagram::CmdPtr cmd, const keo_datagram::CmdClassifier& cmdClassifier, bool ackRequest)
{
    return send(destination, *cmd.get(), cmdClassifier, ackRequest);
}

inline keo_datagram::xs_unsignedLong Feature::sendPendingDatagram(keo_datagram::DatagramPtr datagram)
{
    return sendPendingDatagram(*datagram.get());
}

inline bool Feature::sendDatagram(keo_datagram::DatagramPtr datagram) const
{
    return sendDatagram(*datagram.get());
}

//! typedef for non-const smart pointer type Feature
typedef std::shared_ptr<Feature> FeaturePtr;

//! typedef for const type Feature
typedef const Feature FeatureConst;

//! typedef for const smart pointer type Feature
typedef std::shared_ptr<FeatureConst> FeatureConstPtr;

/** @} */ //  end of group framework
} /* namespace keo_spine */

#endif /* KEO_SPINE_FEATURE_H_ */
