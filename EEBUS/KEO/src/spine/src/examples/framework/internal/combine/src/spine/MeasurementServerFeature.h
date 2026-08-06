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

#ifndef KEO_FRAMEWORK_EXAMPLE_SERVER_SRC_MEASUREMENTSERVERFEATURE_H_
#define KEO_FRAMEWORK_EXAMPLE_SERVER_SRC_MEASUREMENTSERVERFEATURE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_spine/DatagramMemo.h>
#include <keo_spine/ServerFeature.h>
#include <keo_util/KETimer.h>

#include <keo_datagram/core/Core_All.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <map>
#include <vector>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

#define DEFAULT_MEASUREMET_VALUE_UPDATE_TIMEOUT (15)

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_spine_combine_app
{

/**
 * @addtogroup framework_example_server
 * @{
 */

class MeasurementServerFeature;

//! typedef for non-const smart pointer type MeasurementServerFeature
typedef std::shared_ptr<MeasurementServerFeature> MeasurementServerFeaturePtr;

/**
 * The measurement server feature periodically sends notifications to subscribers.
 * The measurement values are randomly generated.
 */
class MeasurementServerFeature : public keo_spine::ServerFeature, public keo_util::TimerHandlerInterface
{
public:
    /**
     * Constructor
     */
    explicit MeasurementServerFeature(const std::vector<keo_datagram::xs_unsignedInt>& entity,
        int measurementUpdateTimeout = DEFAULT_MEASUREMET_VALUE_UPDATE_TIMEOUT);

    /**
     * Virtual destructor
     */
    virtual ~MeasurementServerFeature();

protected:
    bool timeoutHandler(const keo_spine::DatagramMemo& memo) override;

    bool handleDatagram(const keo_spine::DatagramRecord& datagramRecord) override;

    void handleTimer(keo_util::Timer::id_t timerId) override;

    /**
     * Update measurements
     */
    void updateMeasurements();

    /**
     *
     */
    virtual bool handlePendingDatagramResponse(
        const keo_spine::DatagramRecord& datagramRecord, const keo_spine::DatagramMemo& memo) override;

    /**
     * Check whether a subscription to this feature should be accepted.
     *
     * @param clientAddress
     *            Feature address of the client
     * @return true, if the subscription is allowed
     */
    virtual bool allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const override;

private:
    /**
     * Create MeasurementList command
     *
     * @return MeasurementList command
     */
    keo_datagram::Datagram createMeasurementListData(const keo_datagram::Header& header);

    /**
     * Handle MeasurementList read
     *
     * @param datagram
     *            Received datagram
     * @return true
     */
    bool handleMeasurementListDataRead(const keo_spine::DatagramRecord& datagramRecord);

    // Example server data
    std::vector<double> data;

    // Timer for updating the measurement data
    keo_util::Timer timer;

    // Update measurement timout in sec
    int measurementUpdateTimeout;
};

/** @} */ //  end of group framework_example_server

} // namespace keo_spine_combine_app

#endif /* KEO_FRAMEWORK_EXAMPLE_SERVER_SRC_MEASUREMENTSERVERFEATURE_H_ */
