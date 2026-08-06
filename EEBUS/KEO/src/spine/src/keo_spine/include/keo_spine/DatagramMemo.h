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

#ifndef KEO_SPINE_DATAGRAMMEMO_H_
#define KEO_SPINE_DATAGRAMMEMO_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

/******************************************************************************* *
 * KEO header files                                                              *
 ******************************************************************************* */

#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/Datagram.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

#include <memory>

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

/** @ingroup framework
 * @{
 */

/**
 * Information about a pending datagram sent to another device.
 * <p>
 * This is used when handling the result of a pending datagram. The result can
 * either be a received datagram representing the reply to the pending datagram,
 * or a timeout event, when the pending datagram was not replied to in time. In
 * both cases the DatagramMemo can be used to gather information about the
 * purpose of the initial pending datagram.
 */
class DatagramMemo
{
public:
    DatagramMemo();

    /**
     * Constructor
     *
     * @param datagram
     *            Sent datagram
     */
    explicit DatagramMemo(const keo_datagram::Datagram& datagram);

    /**
     * Constructor
     *
     * @param destination
     *            Datagram destination
     * @param msgCounter
     *            Datagram message counter
     * @param type
     *            Command type of the datagram
     */
    DatagramMemo(const keo_datagram::FeatureAddress& destination, keo_datagram::xs_unsignedLong msgCounter,
        keo_datagram::CmdData::Type type);

    /**
     * Destructor
     */
    virtual ~DatagramMemo();

    /**
     * Getter for destination
     *
     * @return destination
     */
    keo_datagram::FeatureAddress getDestination() const;

    /**
     * Setter for destination
     *
     * @param destination
     *            Value to set
     */
    void setDestination(const keo_datagram::FeatureAddress& destination);

    /**
     * Getter for msgCounter
     *
     * @return msgCounter
     */
    keo_datagram::xs_unsignedLong getMsgCounter() const;

    /**
     * Setter for msgCounter
     *
     * @param msgCounter
     *            Value to set
     */
    void setMsgCounter(keo_datagram::xs_unsignedLong msgCounter);

    /**
     * Getter for cmdType
     *
     * @return cmdType
     */
    keo_datagram::CmdData::Type getCmdType() const;

    /**
     * Setter for cmdType
     *
     * @param type
     *            Value to set
     */
    void setCmdType(keo_datagram::CmdData::Type cmdType);

    bool isEmpty() const;

private:
    // datagram destination
    keo_datagram::FeatureAddress destination;
    // datagram message counter
    keo_datagram::xs_unsignedLong msgCounter;
    // command type of the datagram
    keo_datagram::CmdData::Type cmdType;
};

//! typedef for non-const smart pointer type DatagramMemo
typedef std::shared_ptr<DatagramMemo> DatagramMemoPtr;

//! typedef for const type DatagramMemo
typedef const DatagramMemo DatagramMemoConst;

//! typedef for const smart pointer type DatagramMemo
typedef std::shared_ptr<DatagramMemoConst> DatagramMemoConstPtr;

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_DATAGRAMMEMO_H_ */
