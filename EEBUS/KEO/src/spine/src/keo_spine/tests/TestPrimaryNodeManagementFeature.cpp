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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "TestPrimaryNodeManagementFeature.h"
#include <keo_util/KELogging.h>

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

TestPrimaryNodeManagementFeature::TestPrimaryNodeManagementFeature(
    const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : PrimaryNodeManagementFeature(featureDescription)
{
    DEBUG_FUNC();
}

TestPrimaryNodeManagementFeature::~TestPrimaryNodeManagementFeature()
{
    DEBUG_FUNC();
}

TestPrimaryNodeManagementFeaturePtr TestPrimaryNodeManagementFeature::createBasicNodeManagementFeature(
    bool hasDestinationListServer, bool automaticSpineDiscovery)
{
    PrimaryNodeManagementFeaturePtr nodeManagementFeature
        = PrimaryNodeManagementFeature::createBasicNodeManagementFeature(
            hasDestinationListServer, automaticSpineDiscovery);

    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription
        = nodeManagementFeature->getFeatureDescription();

    TestPrimaryNodeManagementFeaturePtr feature
        = std::make_shared<TestPrimaryNodeManagementFeature>(featureDescription);
    return feature;
}

bool TestPrimaryNodeManagementFeature::handlePendingDatagramResponsePublic(
    const DatagramRecord& datagramRecord, const DatagramMemo& memo)
{
    return handlePendingDatagramResponse(datagramRecord, memo);
}
