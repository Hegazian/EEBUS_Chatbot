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
#ifndef KEO_FRAMEWORK_TESTS_DEVICECALLBACKLISTENER_H_
#define KEO_FRAMEWORK_TESTS_DEVICECALLBACKLISTENER_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_spine/DeviceCallbackInterface.h>
/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_datagram/core/Core_All.h>

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */

#include <gtest/gtest.h>

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
class DeviceCallbackListener : public DeviceCallbackInterface
{
public:
    DeviceCallbackListener();
    virtual ~DeviceCallbackListener();

    virtual void onConnect(const TransportId& transportId);

    virtual void onDisconnect(const TransportId& transportId);

    virtual void onDetailedDiscoveryFailed(const TransportId& transportId);

    virtual void onNewDevices(const std::list<std::string>& devices);

    virtual void onRemovedDevices(const std::list<std::string>& devices);

    virtual void onDetailedDiscovery(const std::string& deviceName, const DetailedDiscovery& detailedDiscovery);

    std::list<std::string> connectedDevices;
    std::list<std::string> disconnectedDevices;
};

#endif /* KEO_FRAMEWORK_TESTS_DEVICECALLBACKLISTENER_H_ */
