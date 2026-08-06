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

#ifndef KEO_FRAMEWORK_INCLUDE_KEO_SPINE_SPINELINKRECEIVESERVICEINTERFACE_H_
#define KEO_FRAMEWORK_INCLUDE_KEO_SPINE_SPINELINKRECEIVESERVICEINTERFACE_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

#include <keo_spine/DatagramRecord.h>

/******************************************************************************* *
 * KEO header files                                 ,                            *
 ******************************************************************************* */

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

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
 * SpineLink -> device - interface
 *
 */
class SpineLinkReceiveServiceInterface
{

public:
    virtual ~SpineLinkReceiveServiceInterface()
    {
    }

    /**
     * Announce a new connection
     *
     * @param transportId
     *            Transport id
     */
    virtual void addConnection(TransportId transportId) = 0;

    /**
     * Remove a connection
     *
     * @param transportId
     *            Transport id
     */
    virtual void removeConnection(TransportId transportId) = 0;

    /**
     * Receive a datagram
     *
     * @param record
     *            Datagram record; Includes datagram and transport identifier
     */
    virtual void onDatagram(DatagramRecord& record) = 0;
};

typedef std::weak_ptr<SpineLinkReceiveServiceInterface> SpineLinkReceiveServiceInterfaceWeakPtr;

/** @} */ //  end of group framework_util

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_INCLUDE_KEO_SPINE_SPINELINKRECEIVESERVICEINTERFACE_H_ */
