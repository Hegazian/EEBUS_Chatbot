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
/**
 *     @brief      NodeManagementDeviceClassificationFeature class definition
 *
 *     @par        Module description
 *
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>
#include <keo_spine/DeviceClassificationFeature.h>

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

DeviceClassificationFeature::DeviceClassificationFeature(
    const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : ServerFeature(featureDescription)
{
}

DeviceClassificationFeature::~DeviceClassificationFeature()
{
}

DeviceClassificationFeaturePtr DeviceClassificationFeature::createBasicDeviceClassificationFeature(
    keo_datagram::FeatureAddress const& featureAddress)
{
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    featureDescription.setFeatureAddress(featureAddress);
    featureDescription.setRole(keo_datagram::Role::Value::SERVER);
    featureDescription.setFeatureType(keo_datagram::FeatureType::Value::DEVICE_CLASSIFICATION);

    std::vector<keo_datagram::FunctionProperty> supportedFunction;
    keo_datagram::PossibleOperations possibleOperationsReadOnly;
    possibleOperationsReadOnly.setRead(keo_datagram::PossibleOperationsRead());
    supportedFunction.push_back(keo_datagram::FunctionProperty(
        keo_datagram::Function::Value::DEVICE_CLASSIFICATION_MANUFACTURER_DATA, possibleOperationsReadOnly));
    featureDescription.setSupportedFunction(supportedFunction);
    return std::make_shared<DeviceClassificationFeature>(featureDescription);
}

void DeviceClassificationFeature::setDeviceClassificationManufacturerData(
    const keo_datagram::DeviceClassificationManufacturerData& deviceClassificationManufacturerData)
{
    this->deviceClassificationManufacturerData
        = std::make_shared<keo_datagram::DeviceClassificationManufacturerData>(deviceClassificationManufacturerData);
}

bool DeviceClassificationFeature::handleDatagram(const DatagramRecord& datagramRecord)
{
    bool handled = false;
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    if (datagram.isRead())
    {
        if (datagram.getCmdDataType() == keo_datagram::CmdData::Type::DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE)
        {
            handled = handleDeviceClassificationManufacturerRead(datagramRecord);
        }
    }
    return handled;
}

bool DeviceClassificationFeature::handlePendingDatagramResponse(
    const DatagramRecord& datagramRecord, const DatagramMemo& memo)
{
    (void)datagramRecord;
    (void)memo;
    // TODO insert warning here?
    return false;
}

bool DeviceClassificationFeature::timeoutHandler(const DatagramMemo& memo)
{
    (void)memo;
    return false;
}

bool DeviceClassificationFeature::handleDeviceClassificationManufacturerRead(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();

    DatagramRecord replyRecord
        = DatagramRecord(datagram.createReply(deviceClassificationManufacturerData), datagramRecord.getTransportId());

    // do not need a timeout
    sendDatagram(replyRecord);
    return true;
}

keo_datagram::Datagram DeviceClassificationFeature::createDeviceClassificationRequest(
    const keo_datagram::FeatureAddress& addressSource, const keo_datagram::FeatureAddress& addressDestination)
{
    keo_datagram::Header header
        = keo_datagram::Header(addressSource, addressDestination, keo_datagram::CmdClassifier::Value::READ);
    keo_datagram::Cmd cmd = keo_datagram::Cmd(std::make_shared<keo_datagram::DeviceClassificationManufacturerData>());
    return keo_datagram::Datagram(header, cmd);
}

bool DeviceClassificationFeature::allowBinding(const keo_datagram::FeatureAddress& clientAddress) const
{
    (void)clientAddress;
    return false;
}

bool DeviceClassificationFeature::allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const
{
    (void)clientAddress;
    return true;
}

} /* namespace keo_spine */
