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
#ifndef KEO_FRAMEWORK_TESTS_TESTSENDSERVICE_H_
#define KEO_FRAMEWORK_TESTS_TESTSENDSERVICE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_spine/DatagramMemo.h>
#include <keo_spine/SendServiceInterface.h>

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
#include <map>
#include <vector>
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
class TestSendService : public SendServiceInterface
{
public:
    TestSendService(const std::string& name);
    virtual ~TestSendService();

    virtual bool sendDatagram(DatagramRecord& datagramRecord) override;

    virtual keo_datagram::xs_unsignedLong sendPendingDatagram(DatagramRecord& datagramRecord) override;

    virtual keo_datagram::xs_unsignedLong sendPendingDatagram(
        DatagramRecord& datagramRecord, long timeout) override;

    virtual bool removeTimeoutByMsgCounter(keo_datagram::xs_unsignedLong msgCounter) override;

    virtual std::string getDeviceName() const override;

    virtual bool isConnected(const std::string& deviceName) const override;

    const std::vector<DatagramRecord>& getSentDatagrams();

    void clearAll();

private:
    std::vector<DatagramRecord> sentDatagrams;
    std::string deviceName;
};

#endif /* KEO_FRAMEWORK_TESTS_TESTSENDSERVICE_H_ */
