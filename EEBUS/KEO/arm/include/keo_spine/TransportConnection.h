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

#ifndef KEO_FRAMEWORK_INCLUDE_KEO_SPINE_TRANSPORTCONNECTION_H_
#define KEO_FRAMEWORK_INCLUDE_KEO_SPINE_TRANSPORTCONNECTION_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/core/SpineDatagram.h>
#include <keo_datagram/core/Datagram.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

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

/**
 * @ingroup framework
 * @{
 */

class TransportConnection
{
public:
    /**
     * Destructor
     */
    virtual ~TransportConnection()
    {
    }

    /**
     * Get the connection id
     *
     * The connection Id shall be unique for every connection (even for connections that have the same endpoint).
     *
     * @return connection id
     */
    virtual std::string getId() const = 0;

    /**
     * Sends a datagram to the transport layer
     * @param datagram Datagram to send
     */
    virtual void sendDatagram(const keo_datagram::Datagram& datagram) = 0;

    /**
     * Closes the connection
     */
    virtual void closeConnection() = 0;
};

/** @} */ //  end of group framework

//! typedef for smart pointer type TransportConnection
typedef std::weak_ptr<TransportConnection> TransportConnectionWeakPtr;

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_INCLUDE_KEO_SPINE_TRANSPORTCONNECTION_H_ */
