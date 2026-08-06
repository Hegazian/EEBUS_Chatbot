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

#ifndef KEO_SPINE_DEVICE_SRC_DEVICEDEFINITION_H_
#define KEO_SPINE_DEVICE_SRC_DEVICEDEFINITION_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

/******************************************************************************* *
 * KEO header files                                                         *
 ******************************************************************************* */

#include <keo_datagram/core/EntityAddress.h>
#include <keo_datagram/core/EntityType.h>
#include <keo_datagram/core/FeatureType.h>
#include <keo_datagram/core/xs_types.h>

/******************************************************************************* *
 * standard header files                                                         *
 ******************************************************************************* */

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

/**
 * @ingroup framework
 * @{
 */
struct DeviceDefinition
{
    /**
     * Address of entity zero
     */
    static const keo_datagram::EntityAddress EntityAddressZero;

    /**
     * Address of feature zero
     */
    static const keo_datagram::xs_unsignedInt FeatureAddressZero;

    /**
     * Address of feature one
     */
    static const keo_datagram::xs_unsignedInt FeatureAddressOne;

    /**
     * Type of entity zero feature zero
     */
    static const keo_datagram::FeatureType EntityZeroFeatureZeroType;

    /**
     * Type of entity zero feature one
     */
    static const keo_datagram::FeatureType EntityZeroFeatureOneType;

    /**
     * Type of entity zero
     */
    static const keo_datagram::EntityType EntityZeroEntityType;

    /**
     * Timeout delay for datagrams in milliseconds
     */
    static const keo_datagram::xs_unsignedLong DatagramTimeoutDelay;
};

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_DEVICE_SRC_DEVICEDEFINITION_H_ */
