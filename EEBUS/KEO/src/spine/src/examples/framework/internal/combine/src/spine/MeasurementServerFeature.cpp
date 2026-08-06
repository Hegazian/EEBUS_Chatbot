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

#include "MeasurementServerFeature.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/KeoScaledNumber.h>
#include <keo_datagram/measurement/Measurement_All.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <algorithm>
#include <assert.h>
#include <stdlib.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
namespace keo_spine_combine_app
{

MeasurementServerFeature::MeasurementServerFeature(
    const std::vector<keo_datagram::xs_unsignedInt>& entity, int measurementUpdateTimeout)
    : ServerFeature()
    , timer(this)
    , measurementUpdateTimeout(measurementUpdateTimeout)
{
    DEBUG_FUNC();

    keo_datagram::FeatureAddress featureAddress("", entity, 1LL);

    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setFeatureAddress(featureAddress);
    featureDescription.setRole(keo_datagram::Role::Value::SERVER);
    featureDescription.setFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::MEASUREMENT));
    featureDescription.setDescription("Measurement test server feature");

    setFeatureDescription(featureDescription);

    addPossibleOperation(keo_datagram::Function::Value::MEASUREMENT_LIST_DATA, ServerFeature::READ_ONLY);

    // Use some arbitrary values as measurement data
    data.push_back(1.0);
    data.push_back(1.2);
    data.push_back(1.3);
    data.push_back(1.5);

    // Start a timer that periodically changes the data
    timer.start(measurementUpdateTimeout * 1000);

    // Seed the random number generator
    srand(42U);
}

MeasurementServerFeature::~MeasurementServerFeature()
{
    DEBUG_FUNC();

    timer.stop();
}

bool MeasurementServerFeature::timeoutHandler(const keo_spine::DatagramMemo& memo)
{
    DEBUG_FUNC();
    (void)memo;

    // The server does not send pending datagrams, hence no timeout handling is necessary
    return false;
}

bool MeasurementServerFeature::handleDatagram(const keo_spine::DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    const keo_datagram::Datagram datagram = datagramRecord.getDatagram();
    switch (datagram.getCmdClassifier().getValue())
    {
        case keo_datagram::CmdClassifier::Value::READ:
        {
            switch (datagram.getCmdDataType())
            {
                case keo_datagram::CmdData::Type::MEASUREMENT_LIST_DATA_TYPE:
                {
                    return handleMeasurementListDataRead(datagramRecord);
                }

                default:
                {
                    LOG_WARN() << "Unexpected '" << datagram.getCmdClassifier().toString() << "' : '"
                               << static_cast<int>(datagram.getCmdDataType()) << "'  at feature '"
                               << getFullFeatureAddress().toString() << "'";
                }
            }
            break;
        }
        default:
        {
            LOG_WARN() << "Unexpected classifier '" << datagram.getCmdClassifier().toString() << "' : '"
                       << static_cast<int>(datagram.getCmdDataType()) << "' at feature '"
                       << getFullFeatureAddress().toString() << "'";
            break;
        }
    }
    return false;
}

bool MeasurementServerFeature::handleMeasurementListDataRead(const keo_spine::DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();

    keo_datagram::Header replyHeader = keo_datagram::Header(datagramRecord.getDatagram().getHeader());
    replyHeader.changeToResponse(keo_datagram::CmdClassifier::Value::REPLY);

    keo_datagram::Datagram pDatagram = createMeasurementListData(replyHeader);

    return sendDatagram(pDatagram) > 0;
}

void MeasurementServerFeature::handleTimer(keo_util::Timer::id_t timerId)
{
    (void)timerId;
    updateMeasurements();
    timer.start(measurementUpdateTimeout * 1000);
}

void MeasurementServerFeature::updateMeasurements()
{
    DEBUG_FUNC();
    DEBUG_INFO() << "Updating the measurement data array";

    // Update the measurement data
    for (size_t i = 0; i < data.size(); i++)
    {
        double randomValue = (rand() % 10) / 10.0;
        if (rand() & 1)
        {
            data[i] += randomValue;
        }
        else
        {
            data[i] -= randomValue;
        }
    }

    // Send a NOTIFY message to all subscribed clients
    for (const auto& subscription : getSubscriptions())
    {
        if (isConnected(subscription.clientAddress.getDevice()))
        {
            keo_datagram::Header header = keo_datagram::Header(
                getFullFeatureAddress(), subscription.clientAddress, keo_datagram::CmdClassifier::Value::NOTIFY);
            sendDatagram(createMeasurementListData(header));
        }
    }
}

bool MeasurementServerFeature::handlePendingDatagramResponse(
    const keo_spine::DatagramRecord& datagramRecord, const keo_spine::DatagramMemo& memo)
{
    DEBUG_FUNC();
    (void)datagramRecord;
    (void)memo;
    // The server does not send pending datagrams, hence no handling of pending datagram responses is necessary
    return false;
}

keo_datagram::Datagram MeasurementServerFeature::createMeasurementListData(const keo_datagram::Header& header)
{
    DEBUG_FUNC();
    keo_datagram::MeasurementListDataPtr measurementListData(new keo_datagram::MeasurementListData);

    LOG_INFO() << "===========" << std::endl
               << "Current measurement data: [" << std::dec << data[0] << " " << data[1] << " " << data[2] << " "
               << data[3] << "]" << std::endl
               << "===========";

    std::vector<keo_datagram::MeasurementData> measurementDataList;
    for (size_t i = 0; i < data.size(); i++)
    {
        keo_datagram::MeasurementData measurementData;
        keo_datagram::KeoScaledNumber sn = keo_datagram::KeoScaledNumber::fromDouble(data[i], 2);
        measurementData.setValue(keo_datagram::ScaledNumber(sn.getNumberType(), sn.getScaleType()));
        measurementDataList.push_back(measurementData);
    }

    measurementListData->setMeasurementData(measurementDataList);

    keo_datagram::Cmd cmd = keo_datagram::Cmd(measurementListData);

    return keo_datagram::Datagram(header, cmd);
}

bool MeasurementServerFeature::allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const
{
    DEBUG_FUNC();
    (void)clientAddress;
    // Allow everyone that wants to subscribe to this feature
    return true;
}
}
