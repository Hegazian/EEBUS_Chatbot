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

#ifndef KEO_SPINE_DEVICE_TIMEOUT_SERVICE_INTERFACE_H_
#define KEO_SPINE_DEVICE_TIMEOUT_SERVICE_INTERFACE_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

/******************************************************************************* *
 * KEO header files                                                         *
 ******************************************************************************* */

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */
#include <stdint.h>
/******************************************************************************* *
 *  defines                                                                       *
 ******************************************************************************* */

/******************************************************************************* *
 *  types                                                                         *
 ******************************************************************************* */

/******************************************************************************* *
 *  class definition                                                              *
 ******************************************************************************* */

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

/**
 * TimeoutService interface
 *
 */
class TimeoutServiceInterface
{
public:
    virtual ~TimeoutServiceInterface()
    {
    }

    /**
     * Callback if a timeout occurs
     *
     * @param msgCounter
     *            Message counter of sent datagram
     */
    virtual void timeout(uint64_t msgCounter) = 0;
};

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_DEVICE_TIMEOUT_SERVICE_INTERFACE_H_ */
