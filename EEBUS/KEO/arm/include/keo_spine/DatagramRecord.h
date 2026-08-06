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

#ifndef KEO_SPINE_DATAGRAMRECORD_H_
#define KEO_SPINE_DATAGRAMRECORD_H_

/******************************************************************************* *
 * keo_spine header files                                                        *
 ******************************************************************************* */

/******************************************************************************* *
 * KEO header files                                 ,                            *
 ******************************************************************************* */

#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/SpineDatagram.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */
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

/** @ingroup framework
 * @{
 */

typedef std::string TransportId;

/**
 * A datagram record is a SPINE datagram with additional meta data. This meta data consists of the transportId on which
 * the datagram has been received or should be sent.
 */
class DatagramRecord
{

public:
    /**
     * Default constructor
     */
    DatagramRecord();

    /**
     * Constructor
     *
     * @deprecated Use constructor DatagramRecord(const keo_datagram::Datagram& datagram) instead.
     *
     * @param datagram stored datagram
     */
    explicit DatagramRecord(const keo_datagram::DatagramPtr datagram);

    /**
     * Constructor
     *
     * @param datagram stored datagram
     */
    explicit DatagramRecord(const keo_datagram::Datagram& datagram);

    /**
     * Constructor
     *
     * @deprecated Use constructor DatagramRecord(const keo_datagram::Datagram& datagram, const TransportId&
     * transportId) instead.
     *
     * @param datagram stored datagram
     * @param transportId Transport Id
     */
    DatagramRecord(const keo_datagram::DatagramPtr datagram, const TransportId& transportId);

    /**
     * Constructor
     *
     * @param datagram stored datagram
     * @param transportId Transport Id
     */
    DatagramRecord(const keo_datagram::Datagram& datagram, const TransportId& transportId);

    /**
     * @param transportId
     *            the transportId to set
     */
    void setTransportId(const TransportId& transportId);

    /**
     * @return the transport id
     */
    const TransportId& getTransportId() const;

    /**
     * @param datagram
     */
    void setDatagram(const keo_datagram::Datagram& datagram);

    /**
     * @return the datagram
     */
    const keo_datagram::Datagram& getDatagram() const;

    /**
     * @return the datagram
     */
    keo_datagram::Datagram& getDatagram();

    /**
     * @return Destination device
     */
    std::string getDestinationDevice() const;

    /**
     * @return Source device
     */
    std::string getSourceDevice() const;

    /**
     * @return the json representation of the datagram
     */
    std::string toJson() const;

private:
    keo_datagram::Datagram datagram;

    TransportId transportId;
};

/** @} */ //  end of group framework_util

/* ****************************************************************************** *
 *  typedef for shared data pointer                                               *
 * ****************************************************************************** */

//! typedef for non-const smart pointer type DatagramRecord
typedef std::shared_ptr<DatagramRecord> DatagramRecordPtr;

//! typedef for const type DatagramRecord
typedef const DatagramRecord DatagramRecordConst;

//! typedef for const smart pointer type DatagramRecord
typedef std::shared_ptr<DatagramRecordConst> DatagramRecordConstPtr;

} /* namespace keo_spine */

#endif /* KEO_SPINE_DATAGRAMRECORD_H_ */
