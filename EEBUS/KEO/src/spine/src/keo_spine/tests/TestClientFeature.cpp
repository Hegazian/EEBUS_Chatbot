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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "TestClientFeature.h"

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
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine
{

TestClientFeature::TestClientFeature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : ClientFeature(featureDescription)
{
}

TestClientFeature::TestClientFeature(long entity, long feature)
    : ClientFeature(keo_datagram::NetworkManagementFeatureDescriptionData())
{
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setFeatureAddress(keo_datagram::FeatureAddress("SHOULD_BE_REMOVED_IN_DD", entity, feature));
    featureDescription.setFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::GENERIC));
    featureDescription.setRole(keo_datagram::Role::Value::CLIENT);
    featureDescription.setDescription("TestFeature");
    ClientFeature::setFeatureDescription(featureDescription);
}

bool TestClientFeature::handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo)
{
    // ToDo: Implement me
    (void)datagramRecord;
    (void)memo;
    return true;
}

bool TestClientFeature::handleDatagram(const DatagramRecord& datagramRecord)
{
    // ToDo: Implement me
    (void)datagramRecord;
    return true;
}

bool TestClientFeature::timeoutHandler(const DatagramMemo& memo)
{
    // ToDo: Implement me
    (void)memo;
    return true;
}

} /* namespace keo_spine */
