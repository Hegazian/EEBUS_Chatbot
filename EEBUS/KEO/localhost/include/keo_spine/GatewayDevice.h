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

#ifndef KEO_FRAMEWORK_INCLUDE_KEO_SPINE_GATEWAYDEVICE_H_
#define KEO_FRAMEWORK_INCLUDE_KEO_SPINE_GATEWAYDEVICE_H_


/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/DeviceCallbackInterface.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/NetworkManagementDeviceDescriptionData.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

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
 * A gateway device is a smart device with the NetworkFeatureSet: gateway
 *
 */
class GatewayDevice : public SmartDevice
{
public:
    /**
     * Constructor
     *
     * @param deviceDescription
     *            Description for the device
     * @param deviceCallbackInterface
     *            Callback interface
     */
    GatewayDevice(keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription,
            DeviceCallbackInterface* deviceCallbackInterface);
};

//! typedef for non-const smart pointer type GatewayDevice
typedef std::shared_ptr<GatewayDevice> GatewayDevicePtr;

//! typedef for const type GatewayDevice
typedef const GatewayDevice GatewayDeviceConst;

//! typedef for const smart pointer type GatewayDevice
typedef std::shared_ptr<GatewayDeviceConst> GatewayDeviceConstPtr;

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_INCLUDE_KEO_SPINE_GATEWAYDEVICE_H_ */
