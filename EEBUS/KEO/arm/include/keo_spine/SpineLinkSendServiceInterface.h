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

#ifndef KEO_SPINE_SRC_DEVICE_SEND_SERVICE_INTERFACE_H_
#define KEO_SPINE_SRC_DEVICE_SEND_SERVICE_INTERFACE_H_

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
 * Device -> SpineLink interface
 *
 */
class SpineLinkSendServiceInterface
{
public:
    /**
     * Virtual destructor
     */
    virtual ~SpineLinkSendServiceInterface()
    {
    }

    /**
     * Send a datagram
     * @param datagramRecord Datagram record to send
     * @return true if send
     */
    virtual bool sendDatagram(const DatagramRecord& datagramRecord) = 0;
};

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_SRC_DEVICE_SEND_SERVICE_INTERFACE_H_ */
