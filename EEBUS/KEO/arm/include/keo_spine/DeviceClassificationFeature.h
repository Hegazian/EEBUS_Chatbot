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

#ifndef KEO_FRAMEWORK_DEVICE_SRC_DEVICECLASSIFICATIONFEATURE_H_
#define KEO_FRAMEWORK_DEVICE_SRC_DEVICECLASSIFICATIONFEATURE_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include <keo_spine/DatagramRecord.h>
#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/ServerFeature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/DeviceClassificationManufacturerData.h>
#include <keo_datagram/core/NetworkManagementFeatureDescriptionData.h>

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

class DeviceClassificationFeature;

/* ****************************************************************************** *
 *  typedef for shared data pointer                                               *
 * ****************************************************************************** */

//! typedef for non-const smart pointer type DeviceClassificationFeature
typedef std::shared_ptr<DeviceClassificationFeature> DeviceClassificationFeaturePtr;

//! typedef for const type DeviceClassificationFeature
typedef const DeviceClassificationFeature DeviceClassificationFeatureConst;

//! typedef for const smart pointer type DeviceClassificationFeature
typedef std::shared_ptr<DeviceClassificationFeatureConst> DeviceClassificationFeatureConstPtr;

/** @ingroup framework
 * @{
 */

/**
 * A device classification feature. This feature will automatically respond to READs on
 * DeviceClassificationManufacturerData, if the data has been set using
 * DeviceClassificationFeature::setDeviceClassificationManufacturerData(
 *       const keo_datagram::DeviceClassificationManufacturerData& deviceClassificationManufacturerData);
 */
class DeviceClassificationFeature : public ServerFeature
{
public:
    /**
     * Constructor
     * @param featureDescription
     *         Description of the feature
     */
    explicit DeviceClassificationFeature(
        const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription);

    /**
     * Virtual destructor
     */
    virtual ~DeviceClassificationFeature();

    /**
     * Create this feature
     * @param featureAddress the address of the feature
     * @return a DeviceClassificationFeature
     */
    static DeviceClassificationFeaturePtr createBasicDeviceClassificationFeature(
        keo_datagram::FeatureAddress const& featureAddress = keo_datagram::FeatureAddress(
            "", DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressOne));

    /**
     * Set DeviceClassificationManufacturerData
     *
     * @param deviceClassificationManufacturerData
     *            Data to set
     */
    void setDeviceClassificationManufacturerData(
        const keo_datagram::DeviceClassificationManufacturerData& deviceClassificationManufacturerData);

protected:
    /**
     * Handle DeviceClassificationManufacturer read
     *
     * @param datagramRecord
     *            Received datagram
     * @return true, if handled
     */
    bool handleDeviceClassificationManufacturerRead(const DatagramRecord& datagramRecord);

    /**
     * Create a datagram request for device classification
     *
     * @param addressSource
     *            Source address
     * @param addressDestination
     *            Destination address
     * @return Device Classification Manufacturer Data read datagram
     */
    static keo_datagram::Datagram createDeviceClassificationRequest(
        const keo_datagram::FeatureAddress& addressSource, const keo_datagram::FeatureAddress& addressDestination);

    bool allowBinding(const keo_datagram::FeatureAddress& clientAddress) const override;

    bool allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const override;

private:
    /**
     * Handles device classification manufacturer read data
     *
     * @param datagramRecord datagram data to be handled
     * @return true, if handled
     */
    bool handleDatagram(const DatagramRecord& datagramRecord) override;

    /**
     * The default implementation does nothing and returns always false.
     *
     * This method can be overwritten by applications.
     *
     * @param datagramRecord Datagram data to handle
     * @param memo additional information
     * @return Default implementation returns always false
     */
    bool handlePendingDatagramResponse(const DatagramRecord& datagramRecord, const DatagramMemo& memo) override;

    /**
     * Handles a timeout
     *
     * The default implementation does nothing and returns always false.
     * This method can be overwritten by applications.
     *
     * @param memo information about the related datagram
     * @return Default implementation returns always false
     */
    bool timeoutHandler(const DatagramMemo& memo) override;

private:
    keo_datagram::DeviceClassificationManufacturerDataPtr deviceClassificationManufacturerData;
};

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_SRC_DEVICECLASSIFICATIONFEATURE_H_ */
