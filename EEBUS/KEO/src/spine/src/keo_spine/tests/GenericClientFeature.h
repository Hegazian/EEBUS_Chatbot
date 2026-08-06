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
#ifndef KEO_FRAMEWORK_TESTS_GENERICCLIENTFEATURE_H_
#define KEO_FRAMEWORK_TESTS_GENERICCLIENTFEATURE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_spine/ClientFeature.h>
#include <keo_spine/DatagramMemo.h>

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
class GenericClientFeature;

//! typedef for non-const smart pointer type GenericClientFeature
typedef std::shared_ptr<GenericClientFeature> GenericClientFeaturePtr;

//! typedef for const type GenericClientFeature
typedef const GenericClientFeature GenericClientFeatureConst;

//! typedef for const smart pointer type GenericClientFeature
typedef std::shared_ptr<GenericClientFeatureConst> GenericClientFeatureConstPtr;


class GenericClientFeature : public ClientFeature
{
public:
    GenericClientFeature();
    virtual ~GenericClientFeature();

    /**
     * Constructor
     *
     * @param featureDescription
     *            Description of the feature
     */
    GenericClientFeature(const NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Create the description for the measurement client feature
     *
     * @return MeasurementClientFeature description
     */
    static GenericClientFeaturePtr createGenericClientFeature();

    /*
     * (non-Javadoc)
     *
     * @see de.keo.spine.framework.device.Feature#handleDatagram(de.keo.spine.
     * framework.event.DatagramRecord)
     */
    virtual bool handleDatagram(const DatagramRecord& datagramRecord);

    /*
     * (non-Javadoc)
     *
     * @see
     * de.keo.spine.framework.device.Feature#handlePendingDatagram(de.keo.spine.
     * framework.event.DatagramRecord,
     * de.keo.spine.framework.device.DatagramMemo)
     */
    virtual bool handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo);

    /*
     * (non-Javadoc)
     *
     * @see de.keo.spine.framework.device.Feature#timeoutHandler(de.keo.spine.
     * framework.device.DatagramMemo)
     */
    virtual bool timeoutHandler(const DatagramMemo& memo);
};

#endif /* KEO_FRAMEWORK_TESTS_GENERICCLIENTFEATURE_H_ */
