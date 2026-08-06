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

#ifndef KEO_SPINE_ENTITY_H_
#define KEO_SPINE_ENTITY_H_

/******************************************************************************* *
 * keo_spine header files                                                          *
 ******************************************************************************* */

#include <keo_spine/DatagramRecord.h>
#include <keo_spine/Feature.h>
#include <keo_spine/SendServiceInterface.h>

/******************************************************************************* *
 * KEO header files                                                              *
 ******************************************************************************* */

#include <keo_datagram/core/NetworkManagementEntityDescriptionData.h>
#include <keo_datagram/core/xs_types.h>

/******************************************************************************* *
 * std header files                                                              *
 ******************************************************************************* */

#include <vector>
#include <map>

/******************************************************************************* *
 *  defines                                                                      *
 ******************************************************************************* */

/******************************************************************************* *
 *  types                                                                        *
 ******************************************************************************* */

/******************************************************************************* *
 *  class definition                                                             *
 ******************************************************************************* */

namespace keo_spine
{

/** @ingroup framework
 * @{
 */

/**
 * An entity groups its features.
 * Each entity has its own entity description
 *
 */
class Entity
{
public:
    /**
     * Constructor
     * @param entity Address of the entity
     * @param entityType Type of the entity
     */
    Entity(const std::vector<keo_datagram::xs_unsignedInt>& entity, const keo_datagram::EntityType& entityType);

    /**
     * Constructor
     * @param entityDescription Description of the entity
     */
    explicit Entity(const keo_datagram::NetworkManagementEntityDescriptionData& entityDescription);

    /**
     * Virtual Destructor
     */
    virtual ~Entity();

    /**
     * Get the name of this device
     *
     * @return device name
     */
    std::string getDeviceName() const;

    /**
     * Set a send service for datagrams
     *
     * @param sendService
     *            Service to send datagrams for this device
     */
    void setSendService(SendServiceInterface* sendService);

    /**
     * Get the entity description
     *
     * @return Entity description
     */
    const keo_datagram::NetworkManagementEntityDescriptionData& getEntityDescription() const;

    /**
     * Get the entity list number of this entity
     *
     * @return List of its entity numbers
     */
    std::vector<keo_datagram::xs_unsignedInt> getEntity() const;

    /**
     * Close this entity and also its features
     */
    void onClose();

    /**
     * Add a feature to this entity.
     *
     * Attention: Calling this method will not update the device's detailed discovery. After adding features to an
     * entity, {@link SmartDevice::initialize()} has to be called to create a new detailed discovery.
     *
     * @param feature
     *            Feature class
     * @return true, if the feature class has its needed parameters
     */
    virtual bool addFeature(FeaturePtr feature);

    /**
     * Remove a feature from this entity
     *
     * Attention: Calling this method will not update the device's detailed discovery. After removing features from an
     * entity, {@link SmartDevice::initialize()} has to be called to create a new detailed discovery.
     *
     * @param feature
     *            Feature number
     * @return true, if feature was contained by this entity
     */
    virtual bool removeFeature(keo_datagram::xs_unsignedInt feature);

    /**
     * Get all features from this entity
     *
     * Attention: Some features might be uninitialized and not present in the device's detailed discovery.
     *
     * @return List of all features
     */
    std::vector<FeaturePtr> getFeatures() const;

    /**
     * Get the feature class from this entity.
     *
     * Attention: The feature might be uninitialized and not present in the
     * device's detailed discovery.
     *
     * @param feature
     *            Feature number
     * @return Shared pointer to the feature if it was found, shared pointer
     *         without managed object otherwise
     */
    FeaturePtr getFeature(keo_datagram::xs_unsignedInt feature) const;

    /**
     * Handle a datagram
     *
     * @param datagramRecord
     *            Received datagram
     * @param feature
     *            Feature number
     * @return SpineResultErrors: Destination unknown if feature didn't exists,
     *         datagram not supported if feature did not handle this datagram or
     *         OK if datagram is handled.
     */
    keo_datagram::xs_unsignedInt handleDatagram(const DatagramRecord& datagramRecord, keo_datagram::xs_unsignedInt feature);

    /**
     * Handle a response datagram
     *
     * @param datagramRecord
     *            Received datagram
     * @param feature
     *            Feature number
     * @return SpineResultErrors.OK if handled
     */
    keo_datagram::xs_unsignedInt handleDatagramResponse(const DatagramRecord& datagramRecord, keo_datagram::xs_unsignedInt feature);

    /**
     * Timeout handling for datagrams which were not responded
     *
     * @param address
     *            Feature address of the sender of the datagram
     * @param msgCounter
     *            MessageCounter of the sent datagram
     */
    void handleTimeout(const keo_datagram::FeatureAddress& address, keo_datagram::xs_unsignedLong msgCounter);

    /**
     * Validate this entity. This sets the correct entity address in all
     * features that have been added to this Entity.
     *
     * @return true, if all required attributes are set
     */
    virtual bool validate();

    /**
     * Converts the entity address of this entity to a string
     * @return entity address string
     */
    std::string addressToString() const;

    /**
     * Creates a string representation of this entity.
     * @return a string representation of this entity
     */
    std::string toString() const;

private:
    Entity(const Entity&);

    Entity& operator=(const Entity&);

private:
    class EntityPriv;
    EntityPriv* p;
};

//! typedef for non-const smart pointer type Entity
typedef std::shared_ptr<Entity> EntityPtr;

//! typedef for const type Entity
typedef const Entity EntityConst;

//! typedef for const smart pointer type Entity
typedef std::shared_ptr<EntityConst> EntityConstPtr;

/** @} */ //  end of group framework

} /* namespace keo_spine */

#endif /* KEO_SPINE_ENTITY_H_ */
