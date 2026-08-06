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
#ifndef KEO_FRAMEWORK_TESTS_SMARTDEVICEHELPER_H_
#define KEO_FRAMEWORK_TESTS_SMARTDEVICEHELPER_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "DeviceCallbackListener.h"
#include "EntityHandler.h"
#include "GenericClientFeature.h"
#include "keo_spine/SmartDevice.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/Core_All.h>

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */

#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */
using namespace keo_spine;
using namespace keo_datagram;
/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

class SmartDeviceHelper
{
public:
    static NetworkManagementDeviceDescriptionData getNetworkManagementDeviceDescriptionData(
        const std::string& deviceName);

    static NetworkManagementEntityDescriptionData getNetworkManagementEntityDescriptionData();

    static NetworkManagementFeatureDescriptionData getNetworkManagementEntitFeatureDescriptionData(
        FeatureAddress featureAddress, FeatureType featureType);

    static GenericClientFeaturePtr setNetworkManagementEntity(
        SmartDevicePtr device, PrimaryDeviceInformationEntityPtr entityNull);

    static SmartDevicePtr createSimpleSmartDevice(
        const std::string& deviceName, DeviceCallbackListener* deviceCallbackListener);

    static GenericClientFeaturePtr addGenericClientEntity(SmartDevicePtr device);

private:
    SmartDeviceHelper();
    virtual ~SmartDeviceHelper();
};

#endif /* KEO_FRAMEWORK_TESTS_SMARTDEVICEHELPER_H_ */
