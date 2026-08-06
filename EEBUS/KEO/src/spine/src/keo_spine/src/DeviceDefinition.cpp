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
/**
 *     @brief      DeviceDefinition class definition
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/DeviceDefinition.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine
{

const keo_datagram::xs_unsignedInt DeviceDefinition::FeatureAddressZero = 0;
const keo_datagram::xs_unsignedInt DeviceDefinition::FeatureAddressOne = 1;
const keo_datagram::EntityAddress DeviceDefinition::EntityAddressZero(std::string(), 0);
const keo_datagram::EntityType DeviceDefinition::EntityZeroEntityType(keo_datagram::EntityType::Value::DEVICE_INFORMATION);
const keo_datagram::FeatureType DeviceDefinition::EntityZeroFeatureZeroType(keo_datagram::FeatureType::Value::NODE_MANAGEMENT);
const keo_datagram::FeatureType DeviceDefinition::EntityZeroFeatureOneType(
    keo_datagram::FeatureType::Value::DEVICE_CLASSIFICATION);
const keo_datagram::xs_unsignedLong DeviceDefinition::DatagramTimeoutDelay = 10 * 1000;

} /* namespace keo_spine */
