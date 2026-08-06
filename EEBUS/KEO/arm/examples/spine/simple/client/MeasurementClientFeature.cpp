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

#include "MeasurementClientFeature.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/KeoScaledNumber.h>
#include <keo_datagram/core/ResultData.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <algorithm>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_spine_example_client
{

MeasurementClientFeature::MeasurementClientFeature()
    : ClientFeature()
{
    DEBUG_FUNC();

    keo_datagram::FeatureAddress featureAddress("", { 1L }, 1L);

    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setFeatureAddress(featureAddress);
    featureDescription.setRole(keo_datagram::Role::Value::CLIENT);
    featureDescription.setFeatureType(keo_datagram::FeatureType::Value::MEASUREMENT);
    featureDescription.setDescription("Measurement test client feature");

    setFeatureDescription(featureDescription);

    data[0] = 0.0;
    data[1] = 0.0;
    data[2] = 0.0;
    data[3] = 0.0;
}

MeasurementClientFeature::~MeasurementClientFeature()
{
    DEBUG_FUNC();
}

bool MeasurementClientFeature::timeoutHandler(const keo_spine::DatagramMemo& memo)
{
    DEBUG_FUNC();
    switch (memo.getCmdType())
    {
        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE:
        {
            LOG_ERROR() << "Timeout! Subscription request to '" << memo.getDestination().getDevice()
                        << "' failed. Try to subscribe later again.";
            return true;
        }
        case keo_datagram::CmdData::Type::MEASUREMENT_LIST_DATA_TYPE:
        {
            LOG_WARNING() << "MeasurementList request to '" << memo.getDestination().getDevice() << "' is not replied";
            return true;
        }
        default:
        {
            break;
        }
    }
    return false;
}

bool MeasurementClientFeature::handleDatagram(const keo_spine::DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    switch (datagram.getCmdClassifier().getValue())
    {
        case keo_datagram::CmdClassifier::Value::NOTIFY:
        {
            switch (datagram.getCmdDataType())
            {
                case keo_datagram::CmdData::Type::MEASUREMENT_LIST_DATA_TYPE:
                {
                    return handleMeasurementListNotify(datagramRecord);
                }
                default:
                {
                    LOG_WARNING() << "Unexpected '" << datagram.getCmdClassifier().toString() << "' : '"
                                  << keo_datagram::CmdData::getStringFromType(datagram.getCmdDataType())
                                  << "' at feature '" << getFullFeatureAddress().toString() << "'";
                }
            }
            break;
        }
        default:
        {
            LOG_WARN() << "Unexpected classifier '" << datagram.getCmdClassifier().toString() << "' : '"
                       << keo_datagram::CmdData::getStringFromType(datagram.getCmdDataType()) << "' at feature '"
                       << getFullFeatureAddress().toString() << "'";
            break;
        }
    }
    return false;
}

bool MeasurementClientFeature::handleMeasurementListNotify(const keo_spine::DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    if (subscriptionMap.find(datagramRecord.getDatagram().getSourceAddress()) != subscriptionMap.end())
    {
        LOG_INFO() << "MeasurementListNotify '" << datagramRecord.getDatagram().getSourceAddress().toString() << "'";
        handleMeasurementListData(std::dynamic_pointer_cast<keo_datagram::MeasurementListDataConst>(
            datagramRecord.getDatagram().getCmdData()));
    }
    else
    {
        LOG_WARNING() << "Subscription for '" << datagramRecord.getDatagram().getSourceAddress().toString()
                      << "' not found";
    }
    return true;
}

bool MeasurementClientFeature::handlePendingDatagramResponse(
    const keo_spine::DatagramRecord& datagramRecord, const keo_spine::DatagramMemo& memo)
{
    DEBUG_FUNC();
    const keo_datagram::Datagram datagram = datagramRecord.getDatagram();
    switch (datagram.getCmdClassifier().getValue())
    {
        case keo_datagram::CmdClassifier::Value::RESULT:
        {
            return handleResult(datagramRecord, memo);
        }
        case keo_datagram::CmdClassifier::Value::REPLY:
        {
            switch (datagram.getCmdDataType())
            {
                case keo_datagram::CmdData::Type::MEASUREMENT_LIST_DATA_TYPE:
                {
                    handleMeasurementListData(
                        std::dynamic_pointer_cast<keo_datagram::MeasurementListDataConst>(datagram.getCmdData()));
                    return true;
                }
                default:
                {
                    break;
                }
            }
        }
        break;
        default:
        {
            break;
        }
    }
    return false;
}

bool MeasurementClientFeature::handleResult(
    const keo_spine::DatagramRecord& datagramRecord, const keo_spine::DatagramMemo& memo)
{
    DEBUG_FUNC();
    if (memo.getCmdType() == keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE)
    {
        auto subscriptionReply
            = std::dynamic_pointer_cast<keo_datagram::ResultDataConst>(datagramRecord.getDatagram().getCmdData());
        keo_datagram::NodeManagementSubscriptionRequestCallPtr subscriptionRequestCall
            = killPendingSubscription(memo.getMsgCounter());
        if (subscriptionReply->getErrorNumber() == 0)
        {
            if (subscriptionRequestCall)
            {
                const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest
                    = subscriptionRequestCall->getSubscriptionRequest();
                subscriptionMap.insert(std::make_pair(subscriptionRequest.getServerAddress(), subscriptionRequestCall));

                LOG_INFO() << "Subscription of type '" << subscriptionRequest.getServerFeatureType().toString()
                           << "' from client '" << subscriptionRequest.getClientAddress().toString() << "' to server '"
                           << subscriptionRequest.getServerAddress().toString() << "' accepted.";

                // When the subscription is accepted the resource can safely be read
                keo_datagram::Datagram request
                    = createMeasurementListDataReadDatagram(subscriptionRequest.getServerAddress());
                sendPendingDatagram(request);
            }
        }
        else
        {
            LOG_WARNING() << "Subscription has been rejected by server";
        }
        return true;
    }
    return false;
}

keo_datagram::Datagram MeasurementClientFeature::createMeasurementListDataReadDatagram(
    const keo_datagram::FeatureAddress& destination)
{
    DEBUG_FUNC();
    keo_datagram::Header header
        = keo_datagram::Header(getFullFeatureAddress(), destination, keo_datagram::CmdClassifier::Value::READ);
    keo_datagram::Cmd cmd = keo_datagram::Cmd(keo_datagram::CmdData::Type::MEASUREMENT_LIST_DATA_TYPE);
    return keo_datagram::Datagram(header, cmd);
}

void MeasurementClientFeature::handleMeasurementListData(keo_datagram::MeasurementListDataConstPtr measurementListData)
{
    DEBUG_FUNC();
    const std::vector<keo_datagram::MeasurementData>& listData = measurementListData->getMeasurementData();
    if (!listData.empty())
    {
        int end = std::min<int>((int)listData.size(), (int)4);
        for (int i = 0; i < end; i++)
        {
            if (listData[i].getValueIsSet())
            {
                const keo_datagram::ScaledNumber& sn = listData[i].getValue();
                keo_datagram::KeoScaledNumber sna(sn.getNumber(), sn.getScale());
                data[i] = sna.toDouble();
            }
        }
        LOG_INFO() << "===========" << std::endl
                   << "Got measurement data: [" << std::dec << data[0] << " " << data[1] << " " << data[2] << " "
                   << data[3] << "]" << std::endl
                   << "===========";
    }
}

void MeasurementClientFeature::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    DEBUG_FUNC();
    if (detailedDiscovery.containsFeatureType(keo_datagram::FeatureType(keo_datagram::FeatureType::Value::MEASUREMENT)))
    {
        std::vector<std::vector<keo_datagram::xs_unsignedInt>> entityList = detailedDiscovery.getEntitiesByFeatureType(
            keo_datagram::FeatureType(keo_datagram::FeatureType::Value::MEASUREMENT));
        std::vector<std::vector<keo_datagram::xs_unsignedInt>>::iterator entityIter = entityList.begin();
        for (; entityIter != entityList.end(); ++entityIter)
        {
            std::vector<keo_datagram::xs_unsignedInt> featureList = detailedDiscovery.getFeaturesByFeatureType(
                *entityIter, keo_datagram::FeatureType(keo_datagram::FeatureType::Value::MEASUREMENT));
            std::vector<keo_datagram::xs_unsignedInt>::iterator featureIter = featureList.begin();
            for (; featureIter != featureList.end(); ++featureIter)
            {
                if (detailedDiscovery.getDetailedDiscoveryFeatureInformation(*entityIter, *featureIter)
                        ->getDescription()
                        .getRole()
                    == keo_datagram::Role::Value::SERVER)
                {
                    keo_datagram::FeatureAddress destination(deviceName, *entityIter, *featureIter);
                    ClientFeature::subscribe(destination, keo_datagram::FeatureType::Value::MEASUREMENT);
                }
            }
        }
    }
}

} // namespace keo_spine_example_client
