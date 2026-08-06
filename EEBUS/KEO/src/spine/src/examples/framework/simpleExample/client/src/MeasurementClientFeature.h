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

#ifndef KEO_FRAMEWORK_EXAMPLE_CLIENT_SRC_MEASUREMENTCLIENTFEATURE_H_
#define KEO_FRAMEWORK_EXAMPLE_CLIENT_SRC_MEASUREMENTCLIENTFEATURE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/Core_All.h>
#include <keo_datagram/measurement/Measurement_All.h>
#include <keo_spine/ClientFeature.h>
#include <keo_spine/DatagramMemo.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <map>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

/**
 * @addtogroup framework_example_client
 * @{
 */

class MeasurementClientFeature;
//! typedef for non-const smart pointer type MeasurementClientFeature
typedef std::shared_ptr<MeasurementClientFeature> MeasurementClientFeaturePtr;

/**
 * MeasurementClientFeature receives notifications from a connected server feature.
 * The received measurement values are simply printed out on the console.
 */
class MeasurementClientFeature : public keo_spine::ClientFeature
{
public:
    /**
     * Constructor
     */
    MeasurementClientFeature();

    /**
     * Destructor
     */
    virtual ~MeasurementClientFeature();

    void onDetailedDiscovery(
        const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery) override;

protected:
    bool timeoutHandler(const keo_spine::DatagramMemo& memo) override;
    bool handleDatagram(const keo_spine::DatagramRecord& datagramRecord) override;
    bool handlePendingDatagramResponse(
        const keo_spine::DatagramRecord& datagramRecord, const keo_spine::DatagramMemo& memo) override;

private:
    bool handleMeasurementListNotify(const keo_spine::DatagramRecord& datagramRecord);
    bool handleResult(const keo_spine::DatagramRecord& datagramRecord, const keo_spine::DatagramMemo& memo);
    keo_datagram::Datagram createMeasurementListDataReadDatagram(const keo_datagram::FeatureAddress& destination);
    void handleMeasurementListData(keo_datagram::MeasurementListDataConstPtr measurementListData);

    // Primitive data holder
    double data[4];
    // Hold all successful subscriptions requests
    std::map<keo_datagram::FeatureAddress, keo_datagram::NodeManagementSubscriptionRequestCallPtr> subscriptionMap;
};

/** @} */ //  end of group framework_example_client

} // namespace keo_spine_example_client

#endif /* KEO_FRAMEWORK_EXAMPLE_CLIENT_SRC_MEASUREMENTCLIENTFEATURE_H_ */
