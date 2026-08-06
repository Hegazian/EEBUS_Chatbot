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

#ifndef KEO_FRAMEWORK_DEVICE_TESTS_TESTFEATURE_H_
#define KEO_FRAMEWORK_DEVICE_TESTS_TESTFEATURE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "keo_spine/ClientFeature.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

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

class TestClientFeature : public keo_spine::ClientFeature
{
public:
    TestClientFeature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);
    TestClientFeature(long entity, long feature);

    bool handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo) override;
    bool handleDatagram(const DatagramRecord& datagramRecord) override;
    bool timeoutHandler(const DatagramMemo& memo) override;
};

//! typedef for non-const smart pointer type TestFeature
typedef std::shared_ptr<TestClientFeature> TestFeaturePtr;

//! typedef for const type TestFeature
typedef const TestClientFeature TestFeatureConst;

//! typedef for const smart pointer type TestFeature
typedef std::shared_ptr<TestFeatureConst> TestFeatureConstPtr;

} /* namespace keo_spine */

#endif /* #ifndef KEO_FRAMEWORK_DEVICE_TESTS_TESTFEATURE_H_ */
