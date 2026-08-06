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

#ifndef KEO_SPINE_SRC_SEND_SERVICE_INTERFACE_H_
#define KEO_SPINE_SRC_SEND_SERVICE_INTERFACE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/DatagramRecord.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <list>
#include <string>

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

/**
 * Interface for sending datagrams
 *
 */
class SendServiceInterface
{
public:
    /**
     * Virtual destructor
     */
    virtual ~SendServiceInterface()
    {
    }

    /**
     * Send a datagram (fire and forget).
     * <p>
     * Attention: This datagram does not expect a response. To send a datagram
     * that expects a response use a method for sending pending datagrams.
     *
     * Calling this method sets transportId in the DatagramRecord to the ID of the connection the datagram has been sent
     * on.
     *
     * @see #sendPendingDatagram(DatagramRecordPtr)
     * @see #sendPendingDatagram(DatagramRecordPtr, long)
     *
     * @param datagramRecord
     *            datagramRecord to send
     * @return true, if sending was successful
     */
    virtual bool sendDatagram(DatagramRecord& datagramRecord) = 0;

    /**
     * Send a datagram with an expected response. Either, the global default timeout {@link
     * DeviceDefinition::DatagramTimeoutDelay} or the timeout the remote feature has defined in its
     * {@link keo_datagram::NetworkManagementFeatureDescriptionData} is used.
     * <p>
     * Attention: Datagrams sent with this method expect a response. Received
     * responses are handled in
     * {@link #handlePendingDatagramResponse(DatagramRecord, DatagramMemo)}.
     *
     * Calling this method sets transportId in the DatagramRecord to the ID of the connection the datagram has been sent
     * on.
     *
     * The msgCounter returned by this method should match the msgCouter of the datagram that has
     * been passed in. Else, the sending is considered failed.
     *
     * @param datagramRecord
     *            datagramRecord to send with an expected response
     * @return messageCounter, which is greater zero if sending was successful
     */
    virtual keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecord& datagramRecord) = 0;

    /**
     * Send a datagram with an expected response. The default timeout is used.
     * <p>
     * Attention: Datagrams sent with this method expect a response. Received
     * responses are handled in
     * {@link #handlePendingDatagramResponse(DatagramRecord, DatagramMemo)}.
     *
     * Calling this method sets transportId in the DatagramRecord to the ID of the connection the datagram has been sent
     * on.
     *
     * @param datagramRecord
     *            datagramRecord to send with an expected response
     * @param timeout
     *            the timeout for the sent datagram
     * @return messageCounter of the sent datagram (>0 if sending was successful)
     */
    virtual keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecord& datagramRecord, long timeout) = 0;

    /**
     * Remove a timeout by msgCounter
     *
     * @param msgCounter
     *            MessageCounter of datagram
     * @return true, if removed
     */
    virtual bool removeTimeoutByMsgCounter(keo_datagram::xs_unsignedLong msgCounter) = 0;

    /**
     * Get the name of this device
     *
     * @return device name
     */
    virtual std::string getDeviceName() const = 0;

    /**
     * Returns whether a peer device is connected or not.
     *
     * @param deviceName
     *            Device name
     * @return True if device is reachable
     */
    virtual bool isConnected(const std::string& deviceName) const = 0;
};

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_SRC_SEND_SERVICE_INTERFACE_H_ */
