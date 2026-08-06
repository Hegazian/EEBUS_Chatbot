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

#ifndef _MEASUREMENTCLIENT_H_
#define _MEASUREMENTCLIENT_H_

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_spine/DeviceCallbackInterface.h>
#include <keo_spine/SmartDevice.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <string>

namespace keo_spine_combine_app
{

class SpineMeasurement
{
public:

    static keo_spine::SmartDevicePtr createSmartDeviceMeasurementClient(const std::string& deviceName,
        keo_spine::DeviceCallbackInterface* deviceCallbackHandler);

    static keo_spine::SmartDevicePtr createSmartDeviceMeasurementServer(const std::string& deviceName,
        keo_spine::DeviceCallbackInterface* deviceCallbackHandler);

    static keo_spine::EntityPtr createGenericEntityWithMeasurementClientFeature(
        const keo_datagram::xs_unsignedInt entityNo);

    static keo_spine::EntityPtr createGenericEntityWithMeasurementServerFeature(
        const keo_datagram::xs_unsignedInt entityNo);

private:

    static keo_spine::SmartDevicePtr createSmartDevice(const std::string& deviceName,
        keo_spine::DeviceCallbackInterface* deviceCallbackHandler);
    static void addNetworkManagementEntity(keo_spine::SmartDevicePtr device);

};

}


#endif /* _MEASUREMENTCLIENT_H_ */
