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

#ifndef KEO_SPINE_LINK_SRC_H_
#define KEO_SPINE_LINK_SRC_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/DatagramRecord.h>
#include <keo_spine/SpineLinkDevice.h>
#include <keo_spine/TransportConnection.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <list>
#include <map>
#include <set>
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

namespace keo_spine
{

/**
 * @ingroup framework
 * @{
 */

/**
 * This class defines an abstract interface for SPINE connection handling.
 * The interface is to be implemented by an application. It is called by
 * a 'transport connection unit'.
 * A SPINE connection is defined as a physical transport connection which
 * is ready to be used for SPINE data exchange.
 * A SPINE connection is uniquely identified by a so called 'interface ID'.
 *
 */
class TransportConnectionHandler
{
public:
    /**
     * Destructor
     */
    virtual ~TransportConnectionHandler()
    {
    }

    /**
     * Add a new transport connection.
     *
     * This method is called by a 'transport connection unit', in case a new
     * connection is established and ready to be used for SPINE communication.
     *
     * @param transportConnection
     *        Representation of a transport connection, including an transport ID.
     */
    virtual void addConnection(TransportConnectionWeakPtr transportConnection) = 0;

    /**
     * Remove an existing transport connection.
     *
     * This method is called by a 'transport connection unit', in case an existing
     * connection is disconnected and can no longer be used for SPINE data exchange.
     *
     * @param transportId
     *        Unique identifier representing the SPINE connection.
     */
    virtual void removeConnection(const TransportId& transportId) = 0;

    /**
     * Datagram received on a connection.
     *
     * This method is called, by a 'transport connection unit', in case of an incoming
     * SPINE datagram.
     *
     * @param datagram
     *        the received datagram
     * @param transportId
     *        Unique identifier representing the SPINE connection, the datagram
     *        has been received from
     */
    virtual bool onDatagram(const keo_datagram::Datagram& datagram, const TransportId& transportId) = 0;
};

/**
 * @ingroup framework
 * @{
 */
/**
 * This class represents the junction point between the SPINE address schema and the transport connection address
 * schema.
 * The most simple scenario consists of 1 transport connection linked to a SPINE device model including 1 SPINE device
 * (and its entities and features).
 * A more complex scenario consists of 1..n transport connections linked to a SPINE device model including 1..n SPINE
 * devices (and its entities and features).
 * In both scenarios a 'mainDevice' must be defined, representing the one and only SPINE device that is directly linked
 * to 1..n transport connections.
 * All other devices (in the second scenario) are so called 'subDevices'.
 * - A mainDevice exclusively answers an initial incoming DetailedDiscovery read request from a remote SPINE device
 * (with destinationAddress set to "/0/0").
 * - A mainDevice announces a SubDevice in its DestinationList.
 *  - In this case a mainDevice must support the DestinationList functionality.
 * - A subDevice can be addressed by remote SPINE devices in the same way as a mainDevice.
 * - A subDevice can address a remote SPINE device in the same way as a mainDevice.
 * - A subDevice may also provide further subDevices.
 *  - In this case a subDevice must support the DestinationList functionality.
 */
class SpineLink
{
public:
    /**
     * Default constructor
     */
    SpineLink();

    /**
     * Destructor
     */
    ~SpineLink();

    /**
     * Set the main device for SpineLink
     *
     * @param device
     *            Main SmartDevice
     */
    void setMainDevice(SpineLinkDevicePtr device);

    /**
     * Close all TransportConnections and all local devices
     */
    void close();

    /**
     * Retrieve the current transport connection handler.
     *
     * @return transport connection handler.
     */
    TransportConnectionHandler* getConnectionHandler();

private:
    SpineLink(const SpineLink&);
    SpineLink& operator=(const SpineLink&);

private:
    class SpineLinkPriv;
    SpineLinkPriv* p;
};

//! typedef for non-const smart pointer type SpineLink
typedef std::shared_ptr<SpineLink> SpineLinkPtr;

//! typedef for const type SpineLink
typedef const SpineLink SpineLinkConst;

//! typedef for const smart pointer type SpineLink
typedef std::shared_ptr<SpineLinkConst> SpineLinkConstPtr;

/** @} */ //  end of group framework
} /* namespace keo_spine */

#endif /* KEO_SPINE_LINK_SRC_H_ */
