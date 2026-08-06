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

#ifndef KEO_FRAMEWORK_INCLUDE_KEO_SPINE_PRIMARYDEVICEINFORMATIONENTITY_H_
#define KEO_FRAMEWORK_INCLUDE_KEO_SPINE_PRIMARYDEVICEINFORMATIONENTITY_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */
#include <keo_spine/DeviceClassificationFeature.h>
#include <keo_spine/Entity.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>
/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <memory>
#include <string>

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

class PrimaryDeviceInformationEntity;
class PrimaryNodeManagementInterface;

//! typedef for non-const smart pointer type Entity
typedef std::shared_ptr<PrimaryDeviceInformationEntity> PrimaryDeviceInformationEntityPtr;

//! typedef for const type Entity
typedef const PrimaryDeviceInformationEntity PrimaryDeviceInformationEntityConst;

//! typedef for const smart pointer type Entity
typedef std::shared_ptr<PrimaryDeviceInformationEntityConst> PrimaryDeviceInformationEntityConstConstPtr;

class PrimaryDeviceInformationEntity : public Entity
{
public:
    /**
     * Constructor with a entity description
     *
     * @param description
     *            Entity description
     */
    explicit PrimaryDeviceInformationEntity(const keo_datagram::NetworkManagementEntityDescriptionData& description);

    /**
     * Virtual Destructor
     */
    virtual ~PrimaryDeviceInformationEntity();

    /**
     * Set this entity's PrimaryNodeManagementFeature.
     *
     * @param nodeManagementFeature
     *            the node management feature
     */
    void setNodeManagementFeature(const PrimaryNodeManagementFeaturePtr& nodeManagementFeature);

    /**
     * Get this entity's PrimaryNodeManagementFeature.
     *
     * @return the node management feature
     */
    PrimaryNodeManagementFeaturePtr getNodeManagementFeature();

    /**
     * Set this entity's DeviceClassificationFeature.
     * @param feature the device classification feature
     */
    void setDeviceClassificationFeature(const DeviceClassificationFeaturePtr& feature);

    /**
     * Get this entity's DeviceClassificationFeature.
     * @return the device classification feature
     */
    DeviceClassificationFeaturePtr getDeviceClassificationFeature();

    /**
     * @see Entity
     */
    bool addFeature(FeaturePtr feature) override;

    /**
     * @see Entity
     */
    bool validate() override;

    /**
     * @see Entity
     */
    bool removeFeature(keo_datagram::xs_unsignedInt featureAddress) override;

    /**
     * Setter of PrimaryNodeManagementInterface
     *
     * @param primaryNodeManagementInterface
     *            to set
     */
    void setPrimaryNodeManagementInterface(PrimaryNodeManagementInterface* primaryNodeManagementInterface);

    /**
     * Creates a basic device information entity to be used as the primary node
     * management instance of a device. Note, that this entity does not already
     * have a node management feature.
     *
     * @return a basic device information entity
     */
    static PrimaryDeviceInformationEntityPtr createBasicDeviceInformationEntity();

private:
    bool addNodeManagementFeature(PrimaryNodeManagementFeaturePtr feature);

protected:
    /**
     * The mandatory PrimaryNodeManagementFeature
     */
    PrimaryNodeManagementFeaturePtr nodeManagementFeature;

    /**
     * The mandatory DeviceClassificationFeature
     */
    DeviceClassificationFeaturePtr deviceClassificationFeature;

    PrimaryNodeManagementInterface* entityNodeManagementService;
    PrimaryNodeManagementInterface* deviceNodeManagementService;

    class EntityNodeManagementInterface;
};

} /* namespace keo_spine */

#endif /* KEO_FRAMEWORK_INCLUDE_KEO_SPINE_PRIMARYDEVICEINFORMATIONENTITY_H_ */
