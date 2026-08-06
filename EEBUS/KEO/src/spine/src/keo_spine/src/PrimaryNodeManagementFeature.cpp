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

#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/PrimaryNodeManagementFeature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/ResultData.h>
#include <keo_datagram/core/SpineResultErrors.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>

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

PrimaryNodeManagementFeature::PrimaryNodeManagementFeature(
    const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : ServerFeature(featureDescription)
    , pendingSubscriptions()
    , primaryNodeManagementInterface(nullptr)
    , ownDetailedDiscovery()
    , subDevices()
    , automaticSpineDiscovery(false)
    , destinationList()
    , nextSubscriptionId(0)
    , nextBindingId(0)
    , mtx()
{
}

PrimaryNodeManagementFeature::~PrimaryNodeManagementFeature()
{
}

PrimaryNodeManagementFeaturePtr PrimaryNodeManagementFeature::createBasicNodeManagementFeature(
    bool hasDestinationListServer, bool automaticSpineDiscovery)
{
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;
    keo_datagram::FeatureAddress featureAddress;
    featureAddress.setEntity(DeviceDefinition::EntityAddressZero.getEntity());
    featureAddress.setFeature(DeviceDefinition::FeatureAddressZero);
    featureDescription.setFeatureAddress(featureAddress);
    featureDescription.setRole(keo_datagram::Role::Value::SPECIAL);
    featureDescription.setFeatureType(keo_datagram::FeatureType(DeviceDefinition::EntityZeroFeatureZeroType));

    auto feature = std::make_shared<PrimaryNodeManagementFeature>(featureDescription);

    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA, ServerFeature::READ_ONLY);
    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL, ServerFeature::NO_OPERATIONS);
    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_BINDING_REQUEST_CALL, ServerFeature::NO_OPERATIONS);
    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL, ServerFeature::NO_OPERATIONS);
    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_BINDING_DELETE_CALL, ServerFeature::NO_OPERATIONS);

    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DATA, ServerFeature::READ_ONLY);
    feature->addPossibleOperation(
        keo_datagram::Function::Value::NODE_MANAGEMENT_BINDING_DATA, ServerFeature::READ_ONLY);

    if (hasDestinationListServer)
    {
        feature->addPossibleOperation(
            keo_datagram::Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA, ServerFeature::READ_ONLY);
    }

    feature->automaticSpineDiscovery = automaticSpineDiscovery;
    return feature;
}

keo_datagram::Datagram PrimaryNodeManagementFeature::createNodeManagementDetailedDiscoveryRequest(
    const std::string& sourceDevice, const std::string& destinationDevice)
{
    keo_datagram::Header header = keo_datagram::Header(
        keo_datagram::FeatureAddress(
            sourceDevice, DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero),
        keo_datagram::FeatureAddress(
            destinationDevice, DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero),
        keo_datagram::CmdClassifier::Value::READ);

    return keo_datagram::Datagram(
        header, keo_datagram::Cmd(keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE));
}

keo_datagram::Datagram PrimaryNodeManagementFeature::createNodeManagementDestinationListRequest(
    const std::string& sourceDevice, const std::string& destinationDevice)
{
    keo_datagram::Header header = keo_datagram::Header(
        keo_datagram::FeatureAddress(
            sourceDevice, DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero),
        keo_datagram::FeatureAddress(
            destinationDevice, DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero),
        keo_datagram::CmdClassifier::Value::READ);

    return keo_datagram::Datagram(
        header, keo_datagram::Cmd(keo_datagram::CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE));
}

keo_datagram::DetailedDiscoveryConstPtr PrimaryNodeManagementFeature::getDetailedDiscovery() const
{
    return ownDetailedDiscovery;
}

void PrimaryNodeManagementFeature::setUseCaseData(const keo_datagram::NodeManagementUseCaseData& useCaseData)
{
    std::unique_lock<std::mutex> locker(mtx);
    if (this->useCaseData != useCaseData)
    {
        this->useCaseData = useCaseData;

        if (!this->useCaseData.isEmpty())
        {
            addPossibleOperation(
                keo_datagram::Function::Value::NODE_MANAGEMENT_USE_CASE_DATA, ServerFeature::READ_ONLY);
        }
        else
        {
            removePossibleOperation(keo_datagram::Function::Value::NODE_MANAGEMENT_USE_CASE_DATA);
        }

        mtx.unlock();

        // Notify subscribers
        for (const Association& subscriber : getSubscriptions())
        {
            if (isConnected(subscriber.clientAddress.getDevice()))
            {
                keo_datagram::Datagram d(keo_datagram::CmdClassifier::Value::NOTIFY);
                d.setSourceAddress(getFullFeatureAddress());
                d.setDestinationAddress(subscriber.clientAddress);
                d.setCmd(keo_datagram::Cmd(std::make_shared<keo_datagram::NodeManagementUseCaseData>(useCaseData)));
                sendDatagram(d);
            }
        }
    }
}

const keo_datagram::NodeManagementUseCaseData& PrimaryNodeManagementFeature::getUseCaseData() const
{
    return this->useCaseData;
}

void PrimaryNodeManagementFeature::setDetailedDiscovery(const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    DEBUG_FUNC();

    keo_datagram::DetailedDiscoveryPartial detailedDiscoveryPartial;
    bool couldDiff = false;

    // If ownDetailedDiscovery is not empty at this point, we can send a partial update
    if (ownDetailedDiscovery && !ownDetailedDiscovery->isEmpty())
    {
        couldDiff
            = detailedDiscoveryPartial.setByDiffingDetailedDiscoveries(*ownDetailedDiscovery.get(), detailedDiscovery);

        if (!couldDiff)
        {
            LOG_WARN() << "Could not create partial detailed discovery, sending a complete update";
        }
    }

    ownDetailedDiscovery = std::make_shared<keo_datagram::DetailedDiscovery>(detailedDiscovery);

    // Notify subscribers
    for (const Association& subscriber : getSubscriptions())
    {
        if (isConnected(subscriber.clientAddress.getDevice()))
        {
            if (!couldDiff)
            {
                sendDatagram(createDetailedDiscoveryNotify(subscriber.clientAddress));
            }
            else if (!detailedDiscoveryPartial.isEmpty())
            {
                keo_datagram::Header header;
                header.setAddressSource(getFullFeatureAddress());
                header.setAddressDestination(subscriber.clientAddress);
                header.setCmdClassifier(keo_datagram::CmdClassifier::Value::NOTIFY);
                sendDatagram(detailedDiscoveryPartial.createPartialDetailedDiscoveryDatagram(header));
            }
        }
    }
}

void PrimaryNodeManagementFeature::setPrimaryNodeManagementInterface(
    PrimaryNodeManagementInterface* primaryNodeManagementCallback)
{
    primaryNodeManagementInterface = primaryNodeManagementCallback;
}

PrimaryNodeManagementInterface* PrimaryNodeManagementFeature::getPrimaryNodeManagementInterface()
{
    return primaryNodeManagementInterface;
}

void PrimaryNodeManagementFeature::setAutomaticSpineDiscovery(bool isAutomaticSpineDiscovery)
{
    automaticSpineDiscovery = isAutomaticSpineDiscovery;
}

bool PrimaryNodeManagementFeature::getAutomaticSpineDiscovery()
{
    return automaticSpineDiscovery;
}

bool PrimaryNodeManagementFeature::handleDatagram(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    if (!datagram.isEmpty())
    {
        const keo_datagram::Header& header = datagram.getHeader();
        if (header.getCmdClassifierIsSet())
        {
            switch (header.getCmdClassifier().getValue())
            {
                case keo_datagram::CmdClassifier::Value::READ:
                {
                    switch (datagram.getCmdDataType())
                    {
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE:
                        {
                            return handleNodeManagementDetailedDiscoveryRead(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE:
                        {
                            return handleNodeManagementDestinationListRead(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_BINDING_DATA_TYPE:
                        {
                            return handleNodeManagementBindingDataRead(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE:
                        {
                            return handleNodeManagementSubscriptionDataRead(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE:
                        {
                            return handleNodeManagementUseCaseDataRead(datagramRecord);
                        }

                        default:
                        {
                            LOG_WARN() << "Unexpected '" << datagram.getCmdClassifier().toString() << "' : '"
                                       << keo_datagram::CmdData::getStringFromType(datagram.getCmdDataType())
                                       << "'  at feature '" << getFullFeatureAddress().toString() << "'";
                        }
                    }
                    break;
                }
                case keo_datagram::CmdClassifier::Value::CALL:
                {
                    switch (datagram.getCmdDataType())
                    {
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE:
                        {
                            return handleNodeManagementBindingRequestCall(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE:
                        {
                            return handleNodeManagementBindingDeleteCall(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE:
                        {
                            return handleNodeManagementSubscriptionRequestCall(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE:
                        {
                            return handleNodeManagementSubscriptionDeleteCall(datagramRecord);
                        }
                        default:
                        {
                            LOG_WARN() << "Unexpected '" << datagram.getCmdClassifier().toString() << " at feature '"
                                       << getFullFeatureAddress().toString() << "' : '"
                                       << keo_datagram::CmdData::getStringFromType(datagram.getCmdDataType()) << "'";
                        }
                    }
                    break;
                }
                case keo_datagram::CmdClassifier::Value::NOTIFY:
                {
                    switch (datagram.getCmdDataType())
                    {
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE:
                        {
                            return handleNodeManagementDetailedDiscoveryNotify(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE:
                        {
                            return handleNodeManagementDestinationListNotify(datagramRecord);
                        }
                        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE:
                        {
                            return handleNodeManagementUseCaseDataNotify(datagramRecord);
                        }
                        default:
                        {
                            LOG_WARN() << "Unexpected '" << datagram.getCmdClassifier().toString() << "' : '"
                                       << keo_datagram::CmdData::getStringFromType(datagram.getCmdDataType())
                                       << "'  at feature '" << getFullFeatureAddress().toString() << "'";
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
        }
        else
        {
            LOG_WARN() << "Invalid datagram ( missing classifier ) received at feature '"
                       << getFullFeatureAddress().toString() << "'";
        }
    }
    else
    {
        LOG_WARN() << "Invalid datagram received at feature '" << getFullFeatureAddress().toString() << "'";
    }
    return false;
}

void PrimaryNodeManagementFeature::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    LOG_INFO() << "Received detailed discovery from " << deviceName;

    // Search for feature-specific timeouts
    for (auto entityAddress : detailedDiscovery.getEntities())
    {
        for (long featureId : detailedDiscovery.getFeatures(entityAddress))
        {
            auto featureInformation
                = detailedDiscovery.getDetailedDiscoveryFeatureInformation(entityAddress, featureId);
            if (nullptr != featureInformation && featureInformation->getDescriptionIsSet())
            {
                updateMaxResponseDelay(deviceName, featureInformation->getDescription());
            }
        }
    }

    if (automaticSpineDiscovery)
    {
        if (detailedDiscovery.hasFunction(keo_datagram::Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA))
        {
            // TODO should only send read (on top of initial read) if not subscribed
            sendDestinationListRead(detailedDiscovery.getDeviceName());
        }

        if (detailedDiscovery.hasFunction(keo_datagram::Function::Value::NODE_MANAGEMENT_USE_CASE_DATA))
        {
            // TODO should only send read (on top of initial read) if not subscribed
            sendRead(keo_datagram::FeatureAddress(detailedDiscovery.getDeviceName(),
                         DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero),
                keo_datagram::CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE);
        }

        // TODO should only subscribe if not subscribed
        subscribeToPrimaryNodeManagementFeature(deviceName);
    }
}

void PrimaryNodeManagementFeature::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscovery)
{
    LOG_INFO() << "Received detailed discovery update from " << deviceName;

    keo_datagram::FeatureAddress addressPrimaryNodeManagementFeature(
        "", DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);

    // Look for changes in remote primary node management feature
    if (automaticSpineDiscovery && detailedDiscovery.isFeatureModified(addressPrimaryNodeManagementFeature))
    {
        bool hasDestinationListFunction = false;
        for (auto featureInformation : detailedDiscovery.getModifiedFeatures())
        {
            auto& description = featureInformation.getDescription();
            if (description.getFeatureAddress().equalsWeak(addressPrimaryNodeManagementFeature))
            {
                for (auto& functionProperty : description.getSupportedFunction())
                {
                    if (functionProperty.getFunctionIsSet()
                        && functionProperty.getFunction().getValue()
                            == keo_datagram::Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA)
                    {
                        hasDestinationListFunction = true;
                        break;
                    }
                }
            }
            if (hasDestinationListFunction)
            {
                break;
            }
        }

        if (hasDestinationListFunction)
        {
            // TODO should only send destination list read if not yet subscribed. Determining whether a feature is
            // subscribed to the remote end is not as trivial as it seems. We have no clear concept on how to establish
            // this yet. So for now, the destination list is read every time we received a partial detailed discovery
            // containing the primary node management feature.
            sendDestinationListRead(detailedDiscovery.getDeviceName());
        }
    }
    else if (detailedDiscovery.isEntityRemoved(DeviceDefinition::EntityAddressZero)
        || detailedDiscovery.isFeatureRemoved(addressPrimaryNodeManagementFeature))
    {
        // TODO close connection?
        LOG_WARN() << deviceName << " has removed its primary node management feature";
    }

    // Update maxResponse delays
    for (auto iter = remoteFeatureTimeouts.begin(); iter != remoteFeatureTimeouts.end();)
    {
        // Copy feature address to remove the device part from it (detailed discovery only contains feature addresses
        // without device part set)
        keo_datagram::FeatureAddress featureAddress = iter->first;
        featureAddress.cleanDevice();

        if (detailedDiscovery.isFeatureRemoved(featureAddress)
            || detailedDiscovery.isEntityRemoved(keo_datagram::EntityAddress(featureAddress.getEntity())))
        {
            // Feature or parent entity removed
            std::lock_guard<std::mutex> locker(mtx);
            iter = remoteFeatureTimeouts.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    for (auto const& featureInformation : detailedDiscovery.getModifiedFeatures())
    {
        // Feature modified
        updateMaxResponseDelay(deviceName, featureInformation.getDescription());
    }

    for (auto const& featureInformation : detailedDiscovery.getAddedFeatures())
    {
        // Feature added
        updateMaxResponseDelay(deviceName, featureInformation.getDescription());
    }
}

void PrimaryNodeManagementFeature::onRemovedDevices(const std::vector<std::string>& removedDevices)
{
    // Remove all saved "remote feature timeouts" of the disconnected devices
    std::lock_guard<std::mutex> locker(mtx);

    for (const std::string& removedDevice : removedDevices)
    {
        for (auto iter = remoteFeatureTimeouts.begin(); iter != remoteFeatureTimeouts.end();)
        {
            if (iter->first.getDevice() == removedDevice)
            {
                iter = remoteFeatureTimeouts.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

long PrimaryNodeManagementFeature::getRemoteFeatureTimeout(const keo_datagram::FeatureAddress& remoteFeatureAddress)
{
    std::lock_guard<std::mutex> locker(mtx);
    if (remoteFeatureTimeouts.find(remoteFeatureAddress) != remoteFeatureTimeouts.end())
    {
        return remoteFeatureTimeouts[remoteFeatureAddress];
    }
    else
    {
        return 0;
    }
}

bool PrimaryNodeManagementFeature::hasRemoteFeatureTimeout(const keo_datagram::FeatureAddress& remoteFeatureAddress)
{
    std::lock_guard<std::mutex> locker(mtx);
    return remoteFeatureTimeouts.find(remoteFeatureAddress) != remoteFeatureTimeouts.end();
}

bool PrimaryNodeManagementFeature::sendDetailedDiscoveryRead(const std::string& destination)
{
    DEBUG_INFO() << "Sending DetailedDiscovery read to " << destination;
    return sendPendingDatagram(createNodeManagementDetailedDiscoveryRequest(getDeviceName(), destination)) > 0;
}

bool PrimaryNodeManagementFeature::sendDestinationListRead(const std::string& deviceName)
{
    DEBUG_INFO() << "Sending DestinationList read to " << deviceName;
    return sendPendingDatagram(createNodeManagementDestinationListRequest(getDeviceName(), deviceName)) > 0;
}

keo_datagram::Datagram PrimaryNodeManagementFeature::createDestinationListNotify()
{
    keo_datagram::Cmd cmd = *destinationList.createNotificationCmd().get();
    keo_datagram::Header header;
    header.setCmdClassifier(keo_datagram::CmdClassifier::Value::NOTIFY);
    header.setAddressSource(getFullFeatureAddress());
    return keo_datagram::Datagram(header, cmd);
}

void PrimaryNodeManagementFeature::sendDatagrams(
    const std::vector<Association>& allReceivers, const keo_datagram::Datagram& datagram)
{
    keo_datagram::Header headerRef = datagram.getHeader();
    keo_datagram::Payload payloadRef = datagram.getPayload();
    for (const auto& association : allReceivers)
    {
        keo_datagram::Header header = headerRef;
        header.setAddressDestination(association.clientAddress);
        sendDatagram(keo_datagram::Datagram(header, payloadRef));
    }
}

bool PrimaryNodeManagementFeature::addSubDevice(
    const std::vector<keo_datagram::NetworkManagementDeviceDescriptionData>& newSubDevices)
{
    bool isChanged = false;
    std::vector<keo_datagram::NodeManagementDestinationData> nodeManagementDestinationDataList;
    auto iterConst = newSubDevices.begin();
    auto iterConstEnd = newSubDevices.end();
    mtx.lock(); // TODO make addSubDevice not public
    for (; iterConst != iterConstEnd; ++iterConst)
    {
        std::string deviceName = iterConst->getDeviceAddress().getDevice();
        auto iter = subDevices.begin();
        auto iterEnd = subDevices.end();
        bool found = false;
        for (; iter != iterEnd; ++iter)
        {
            if (deviceName == iter->getDeviceAddress().getDevice())
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription(*iterConst);
            deviceDescription.setLastStateChange(keo_datagram::NetworkManagementStateChange::Value::ADDED);
            subDevices.push_back(deviceDescription);
            keo_datagram::NodeManagementDestinationData nodeManagementDestinationData;
            nodeManagementDestinationData.setDeviceDescription(deviceDescription);
            nodeManagementDestinationDataList.push_back(nodeManagementDestinationData);
            isChanged = true;
        }
    }
    mtx.unlock();
    if (isChanged)
    {
        auto nodeManagementDestinationListData = std::make_shared<keo_datagram::NodeManagementDestinationListData>();
        nodeManagementDestinationListData->setNodeManagementDestinationData(nodeManagementDestinationDataList);

        // Notify subscribers
        mtx.lock();
        destinationList.insertDestinationListInformation(nodeManagementDestinationListData);
        keo_datagram::Datagram datagram = createDestinationListNotify();
        destinationList.commit();
        mtx.unlock();
        sendDatagrams(getSubscriptions(), datagram);

        return true;
    }
    else
    {
        return false;
    }
}

bool PrimaryNodeManagementFeature::removeSubDevice(const std::vector<std::string>& deviceNames)
{
    std::vector<keo_datagram::NetworkManagementDeviceDescriptionData> removedDevices;
    auto iterConst = deviceNames.begin();
    auto iterConstEnd = deviceNames.end();
    mtx.lock();
    for (; iterConst != iterConstEnd; ++iterConst)
    {
        auto iter = subDevices.begin();
        auto iterEnd = subDevices.end();
        for (; iter != iterEnd; ++iter)
        {
            if (iterConst->compare(iter->getDeviceAddress().getDevice()) == 0)
            {
                removedDevices.push_back(*iter);
                subDevices.erase(iter);
                break;
            }
        }
    }
    mtx.unlock();
    if (!removedDevices.empty())
    {
        std::vector<keo_datagram::NodeManagementDestinationData> removedDevicesDestinationData;
        auto iter = removedDevices.begin();
        auto iterEnd = removedDevices.end();
        for (; iter != iterEnd; ++iter)
        {

            keo_datagram::NodeManagementDestinationData removedDevice;
            iter->setLastStateChange(keo_datagram::NetworkManagementStateChange::Value::REMOVED);
            removedDevice.setDeviceDescription(*iter);
            removedDevicesDestinationData.push_back(removedDevice);
        }
        auto nodeManagementDestinationListData
            = std::make_shared<keo_datagram::NodeManagementDestinationListData>(removedDevicesDestinationData);

        // Notify subscribers
        mtx.lock();
        destinationList.insertDestinationListInformation(nodeManagementDestinationListData);
        keo_datagram::Datagram datagram = createDestinationListNotify();
        destinationList.commit();
        mtx.unlock();
        sendDatagrams(getSubscriptions(), datagram);

        return true;
    }
    else
    {
        return false;
    }
}

keo_datagram::xs_unsignedLong PrimaryNodeManagementFeature::subscribeToPrimaryNodeManagementFeature(
    const std::string& deviceName)
{
    keo_datagram::FeatureAddress entityZero(
        deviceName, DeviceDefinition::EntityAddressZero.getEntity(), DeviceDefinition::FeatureAddressZero);
    keo_datagram::Header header
        = keo_datagram::Header(getFullFeatureAddress(), entityZero, keo_datagram::CmdClassifier::Value::CALL);
    keo_datagram::SubscriptionManagementRequestCall subscriptionRequest(getFullFeatureAddress(), entityZero,
        keo_datagram::FeatureType(keo_datagram::FeatureType::Value::NODE_MANAGEMENT));
    auto cmdData = std::make_shared<keo_datagram::NodeManagementSubscriptionRequestCall>(subscriptionRequest);
    keo_datagram::xs_unsignedLong result
        = sendPendingDatagram(keo_datagram::Datagram(header, keo_datagram::Cmd(cmdData)));
    if (result > 0)
    {
        std::lock_guard<std::mutex> locker(mtx);
        // TODO check if already present
        pendingSubscriptions.insert(
            std::pair<keo_datagram::xs_unsignedLong, keo_datagram::NodeManagementSubscriptionRequestCall>(
                header.getMsgCounter(), *cmdData.get()));
    }
    return result;
}

bool PrimaryNodeManagementFeature::handleNodeManagementSubscriptionDeleteCall(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    assert(datagram.getCmdDataType() == keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE);

    auto deleteCall
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementSubscriptionDeleteCallConst>(datagram.getCmdData());

    if (deleteCall && deleteCall->getSubscriptionDeleteIsSet())
    {
        keo_datagram::SubscriptionManagementDeleteCall deleteRequest = deleteCall->getSubscriptionDelete();
        if (deleteRequest.getClientAddressIsSet() && deleteRequest.getServerAddressIsSet())
        {
            // The device part of the client address is not mandatory, but is needed to uniquely identify
            // subscriptions, thus it is taken from the Header of the datagram
            keo_datagram::FeatureAddress clientAddress = deleteRequest.getClientAddress();
            clientAddress.setDevice(datagramRecord.getSourceDevice());
            deleteRequest.setClientAddress(clientAddress);

            if (primaryNodeManagementInterface->removeSubscription(deleteRequest))
            {
                sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
            }
            else
            {
                sendDatagram(datagram.createResult(
                    keo_datagram::SpineResultErrors::GENERAL_ERROR, "Removing subscription failed."));
            }
            return true;
        }
        else
        {
            LOG_WARN() << "Invalid subscription delete call. Server or client address is not set. in subscription "
                          "delete call at "
                       << this->toString();
        }
    }
    else
    {
        LOG_WARN() << "Invalid subscription delete call. SubscriptionDelete is not set at " << this->toString();
    }
    return false;
}

bool PrimaryNodeManagementFeature::handleNodeManagementSubscriptionRequestCall(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    assert(datagram.getCmdDataType() == keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE);

    auto subscriptionCall
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementSubscriptionRequestCallConst>(datagram.getCmdData());
    assert(subscriptionCall);
    if (subscriptionCall && subscriptionCall->getSubscriptionRequestIsSet())
    {
        keo_datagram::SubscriptionManagementRequestCall subscriptionRequest
            = subscriptionCall->getSubscriptionRequest();
        if (subscriptionRequest.getClientAddressIsSet() && subscriptionRequest.getServerAddressIsSet())
        {
            // The device part of the client address is not mandatory, but is needed to uniquely identify
            // subscriptions, thus it is taken from the Header of the datagram
            keo_datagram::FeatureAddress clientAddress = subscriptionRequest.getClientAddress();
            clientAddress.setDevice(datagramRecord.getSourceDevice());
            subscriptionRequest.setClientAddress(clientAddress);

            bool sendResponse = datagram.getHeader().getAckRequestIsSet() && datagram.getHeader().getAckRequest();

            // Synchronize access to nextSubscriptionId
            std::lock_guard<std::mutex> locker(mtx);

            if (primaryNodeManagementInterface->addSubscription(nextSubscriptionId, subscriptionRequest))
            {
                if (sendResponse)
                {
                    sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
                }
                nextSubscriptionId++;
            }
            else
            {
                if (sendResponse)
                {
                    sendDatagram(datagram.createResult(
                        keo_datagram::SpineResultErrors::GENERAL_ERROR, "Adding subscription failed"));
                }
            }
            return true;
        }
        else
        {
            LOG_WARN() << "Invalid subscription request call (server or client address is not set) at "
                       << this->toString();
        }
    }
    else
    {
        LOG_WARN() << "Invalid subscription request call (SubscriptionRequest is not set) at " << this->toString();
    }
    return false;
}

bool PrimaryNodeManagementFeature::handleNodeManagementBindingDeleteCall(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    assert(datagram.getCmdDataType() == keo_datagram::CmdData::Type::NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE);

    auto deleteCall
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementBindingDeleteCallConst>(datagram.getCmdData());

    if (deleteCall && deleteCall->getBindingDeleteIsSet())
    {
        keo_datagram::BindingManagementDeleteCall deleteRequest = deleteCall->getBindingDelete();
        if (deleteRequest.getClientAddressIsSet() && deleteRequest.getServerAddressIsSet())
        {
            // The device part of the client address is not mandatory, but is needed to uniquely identify bindings, thus
            // it is taken from the Header of the datagram
            keo_datagram::FeatureAddress clientAddress = deleteRequest.getClientAddress();
            clientAddress.setDevice(datagramRecord.getSourceDevice());
            deleteRequest.setClientAddress(clientAddress);

            bool sendResponse = datagram.getHeader().getAckRequestIsSet() && datagram.getHeader().getAckRequest();

            if (primaryNodeManagementInterface->removeBinding(deleteRequest))
            {
                if (sendResponse)
                {
                    sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
                }
            }
            else
            {
                if (sendResponse)
                {
                    sendDatagram(datagram.createResult(
                        keo_datagram::SpineResultErrors::GENERAL_ERROR, "Removing binding failed."));
                }
            }
            return true;
        }
        else
        {
            LOG_WARN() << "Invalid binding delete call. Server or client address is not set. in binding delete call at "
                       << this->toString();
        }
    }
    else
    {
        LOG_WARN() << "Invalid binding delete call. BindingDelete is not set at " << this->toString();
    }
    return false;
}

bool PrimaryNodeManagementFeature::handleNodeManagementBindingRequestCall(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    assert(datagram.getCmdDataType() == keo_datagram::CmdData::Type::NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE);

    auto bindingCall
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementBindingRequestCallConst>(datagram.getCmdData());
    assert(bindingCall);
    if (bindingCall && bindingCall->getBindingRequestIsSet())
    {
        keo_datagram::BindingManagementRequestCall bindingRequest = bindingCall->getBindingRequest();
        if (bindingRequest.getClientAddressIsSet() && bindingRequest.getServerAddressIsSet())
        {
            // The device part of the client address is not mandatory, but is needed to uniquely identify bindings, thus
            // it is taken from the Header of the datagram
            keo_datagram::FeatureAddress clientAddress = bindingRequest.getClientAddress();
            clientAddress.setDevice(datagramRecord.getSourceDevice());
            bindingRequest.setClientAddress(clientAddress);

            bool sendResponse = datagram.getHeader().getAckRequestIsSet() && datagram.getHeader().getAckRequest();

            // Synchronize access to nextBindingId
            std::lock_guard<std::mutex> locker(mtx);

            if (primaryNodeManagementInterface->addBinding(nextBindingId, bindingRequest))
            {
                if (sendResponse)
                {
                    sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
                }
                nextBindingId++;
            }
            else
            {
                if (sendResponse)
                {
                    sendDatagram(datagram.createResult(
                        keo_datagram::SpineResultErrors::GENERAL_ERROR, "Adding binding failed."));
                }
            }
            return true;
        }
        else
        {
            LOG_WARN() << "Invalid binding request call (server or client address is not set) at " << this->toString();
        }
    }
    else
    {
        LOG_WARN() << "Invalid binding request call (BindingRequest is not set) at " << this->toString();
    }
    return false;
}

bool PrimaryNodeManagementFeature::handleNodeManagementSubscriptionDataRead(const DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    keo_datagram::DetailedDiscoveryConstPtr detailedDiscovery = getDetailedDiscovery();
    if (detailedDiscovery
        && detailedDiscovery->hasFunction(keo_datagram::Function::Value::NODE_MANAGEMENT_SUBSCRIPTION_DATA))
    {
        std::vector<keo_datagram::SubscriptionManagementEntryData> subscriptionEntries;

        // Fetch all subscriptions of all server features of this device
        const std::map<keo_datagram::FeatureAddress, std::vector<Association>> subscriptions
            = primaryNodeManagementInterface->getSubscriptions();

        for (auto iter = subscriptions.begin(); iter != subscriptions.end(); ++iter)
        {
            const keo_datagram::FeatureAddress serverAddress = iter->first;
            const std::vector<Association> subscriptionsOfFeature = iter->second;

            for (auto subscriptionIter = subscriptionsOfFeature.begin();
                 subscriptionIter != subscriptionsOfFeature.end(); ++subscriptionIter)
            {
                if (subscriptionIter->clientAddress.getDevice() == datagramRecord.getSourceDevice())
                {
                    // Only include subscriptions from the client that has sent the READ datagram
                    keo_datagram::SubscriptionManagementEntryData subscriptionEntry;
                    subscriptionEntry.setSubscriptionId(subscriptionIter->id);
                    subscriptionEntry.setClientAddress(subscriptionIter->clientAddress);
                    subscriptionEntry.setDescription(subscriptionIter->description);
                    subscriptionEntry.setServerAddress(serverAddress);
                    subscriptionEntries.push_back(subscriptionEntry);
                }
            }
        }

        keo_datagram::NodeManagementSubscriptionData subscriptionListData(subscriptionEntries);
        auto entryListData = std::make_shared<keo_datagram::NodeManagementSubscriptionData>(subscriptionListData);
        auto replyRecord = std::make_shared<DatagramRecord>(datagramRecord.getDatagram().createReply(entryListData));

        sendDatagram(replyRecord);

        return true;
    }
    return false;
}

bool PrimaryNodeManagementFeature::handleNodeManagementBindingDataRead(const DatagramRecord& datagramRecord)
{
    DEBUG_FUNC();
    keo_datagram::DetailedDiscoveryConstPtr detailedDiscovery = getDetailedDiscovery();

    if (detailedDiscovery
        && detailedDiscovery->hasFunction(keo_datagram::Function::Value::NODE_MANAGEMENT_BINDING_DATA))
    {
        std::vector<keo_datagram::BindingManagementEntryData> bindingEntries;

        // Fetch all bindings of all server features of this device
        std::map<keo_datagram::FeatureAddress, std::vector<Association>> bindings
            = primaryNodeManagementInterface->getBindings();

        for (auto iter = bindings.begin(); iter != bindings.end(); ++iter)
        {
            const keo_datagram::FeatureAddress serverAddress = iter->first;
            const std::vector<Association> bindingsOfFeature = iter->second;

            for (auto bindingIter = bindingsOfFeature.begin(); bindingIter != bindingsOfFeature.end(); ++bindingIter)
            {
                if (bindingIter->clientAddress.getDevice() == datagramRecord.getSourceDevice())
                {
                    // Only include bindings from the client that has sent the READ datagram
                    keo_datagram::BindingManagementEntryData bindingEntry;
                    bindingEntry.setBindingId(bindingIter->id);
                    bindingEntry.setClientAddress(bindingIter->clientAddress);
                    bindingEntry.setDescription(bindingIter->description);
                    bindingEntry.setServerAddress(serverAddress);
                    bindingEntries.push_back(bindingEntry);
                }
            }
        }

        keo_datagram::NodeManagementBindingData bindingListData(bindingEntries);
        auto entryListData = std::make_shared<keo_datagram::NodeManagementBindingData>(bindingListData);
        auto replyRecord = std::make_shared<DatagramRecord>(
            datagramRecord.getDatagram().createReply(entryListData), datagramRecord.getTransportId());

        sendDatagram(replyRecord);

        return true;
    }
    return false;
}

bool PrimaryNodeManagementFeature::handleNodeManagementDestinationListRead(const DatagramRecord& datagramRecord)
{
    bool handled = false;
    if (getDetailedDiscovery()->hasFunction(keo_datagram::Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA))
    {
        auto replyRecord = std::make_shared<DatagramRecord>(
            createDestinationListResponse(datagramRecord.getDatagram()), datagramRecord.getTransportId());
        sendDatagram(replyRecord);
        handled = true;
    }
    return handled;
}

keo_datagram::DatagramPtr PrimaryNodeManagementFeature::createDestinationListResponse(
    const keo_datagram::Datagram& datagram)
{
    std::vector<keo_datagram::NodeManagementDestinationData> nodeManagementDestinationDataList;
    // Add self to DestinationList
    keo_datagram::NetworkManagementDeviceDescriptionData deviceDescription
        = getDetailedDiscovery()->getDeviceDescription();
    restrictToNetworkManagementDeviceDescriptionData(deviceDescription);
    nodeManagementDestinationDataList.push_back(keo_datagram::NodeManagementDestinationData(deviceDescription));
    mtx.lock();
    for (keo_datagram::NetworkManagementDeviceDescriptionData subDeviceDescription : subDevices)
    {
        // This always includes all subdevices
        restrictToNetworkManagementDeviceDescriptionData(subDeviceDescription);
        keo_datagram::NodeManagementDestinationData nodeManagementDestinationData;
        nodeManagementDestinationData.setDeviceDescription(subDeviceDescription);
        nodeManagementDestinationDataList.push_back(nodeManagementDestinationData);
    }
    mtx.unlock();
    auto nodeManagementDestinationListData
        = std::make_shared<keo_datagram::NodeManagementDestinationListData>(nodeManagementDestinationDataList);
    return std::make_shared<keo_datagram::Datagram>(datagram.createReply(nodeManagementDestinationListData));
}

void PrimaryNodeManagementFeature::restrictToNetworkManagementDeviceDescriptionData(
    keo_datagram::NetworkManagementDeviceDescriptionData& deviceDescription)
{
    deviceDescription.cleanDeviceType();
    deviceDescription.cleanNetworkManagementResponsibleAddress();
    deviceDescription.cleanNativeSetup();
    deviceDescription.cleanTechnologyAddress();
    deviceDescription.cleanMinimumTrustLevel();
    deviceDescription.cleanDescription();
}

bool PrimaryNodeManagementFeature::handleNodeManagementDetailedDiscoveryRead(const DatagramRecord& datagramRecord)
{
    auto replyRecord = std::make_shared<DatagramRecord>(
        createDetailedDiscoveryResponse(datagramRecord.getDatagram()), datagramRecord.getTransportId());
    sendDatagram(replyRecord);
    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementUseCaseDataRead(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    // TODO all of the usual SUPPORTED_FUNCTIONS that are handled in this class, are mandatory. Thus, we have never
    // checked if an incoming request is actually supported (according to this feature's feature description).
    // UseCaseData READs are optional. Thus, we need to check if it is currently supported, here. A "clean
    // implementation" would check it for all incoming requests. But that may drastically change existing
    // implementations, thus it is left as a TODO for now.
    if (isSupported(datagram))
    {
        sendDatagram(datagram.createReply(std::make_shared<keo_datagram::NodeManagementUseCaseData>(useCaseData)));
        return true;
    }
    else
    {
        return false;
    }
}

keo_datagram::Datagram PrimaryNodeManagementFeature::createDetailedDiscoveryResponse(
    const keo_datagram::Datagram& datagram)
{
    keo_datagram::NodeManagementDetailedDiscoveryDataPtr detailedDiscoveryData
        = getDetailedDiscovery()->getDetailedDiscoveryDataPtr();
    keo_datagram::Datagram reply = datagram.createReply(detailedDiscoveryData);
    keo_datagram::Header header = reply.getHeader();
    // set the source address to prevent 'simple' communication mode
    keo_datagram::FeatureAddress source = header.getAddressSource();
    source.setDevice(getDetailedDiscovery()->getDeviceName());
    header.setAddressSource(source);
    reply.setHeader(header);

    return reply;
}

keo_datagram::Datagram PrimaryNodeManagementFeature::createDetailedDiscoveryNotify(
    const keo_datagram::FeatureAddress& destination)
{
    keo_datagram::NodeManagementDetailedDiscoveryDataPtr detailedDiscoveryData
            = getDetailedDiscovery()->getDetailedDiscoveryDataPtr();
    keo_datagram::Header header;
    header.setAddressSource(getFullFeatureAddress());
    header.setAddressDestination(destination);
    header.setCmdClassifier(keo_datagram::CmdClassifier::Value::NOTIFY);
    return keo_datagram::Datagram(header, keo_datagram::Cmd(detailedDiscoveryData));
}

bool PrimaryNodeManagementFeature::handleNodeManagementDetailedDiscoveryNotify(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();

    if (datagram.requiresResponse())
    {
        sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
    }

    bool isPartialDetailedDiscovery = false;

    if (datagram.getCmd().getFilterIsSet())
    {
        std::vector<keo_datagram::Filter> filterList = datagram.getCmd().getFilter();
        for (auto filterListIter : filterList)
        {
            if (filterListIter.getCmdControlIsSet() && filterListIter.getCmdControl().getPartialIsSet())
            {
                isPartialDetailedDiscovery = true;
                break;
            }
        }
    }

    if (!isPartialDetailedDiscovery)
    {
        keo_datagram::DetailedDiscovery detailedDiscovery;
        detailedDiscovery.setDetailedDiscoveryData(
            *((keo_datagram::NodeManagementDetailedDiscoveryData*)datagram.getCmdData().get()));
        if (!detailedDiscovery.getDeviceName().empty())
        {
            primaryNodeManagementInterface->onDetailedDiscovery(detailedDiscovery.getDeviceName(), detailedDiscovery);
        }
        else
        {
            LOG_WARN() << "Got invalid detailed discovery from " << datagram.getSourceAddress().getDevice();
        }
    }
    else
    {
        keo_datagram::DetailedDiscoveryPartial detailedDiscoveryPartial;
        detailedDiscoveryPartial.setDetailedDiscoveryData(
            *((keo_datagram::NodeManagementDetailedDiscoveryData*)datagram.getCmdData().get()));
        if (!detailedDiscoveryPartial.getDeviceName().empty())
        {
            primaryNodeManagementInterface->onDetailedDiscoveryPartial(
                detailedDiscoveryPartial.getDeviceName(), detailedDiscoveryPartial);
        }
        else
        {
            LOG_WARN() << "Got invalid partial detailed discovery from " << datagram.getSourceAddress().getDevice();
        }
    }

    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementDestinationListNotify(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();

    if (datagram.requiresResponse())
    {
        sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
    }

    keo_datagram::DestinationList destinationList;
    auto nodeManagementDestinationListData
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementDestinationListDataConst>(datagram.getCmdData());
    destinationList.updateDestinationList(nodeManagementDestinationListData, datagram.getCmd().getFilter());
    std::string const& deviceName = datagram.getSourceAddress().getDevice();
    DEBUG_INFO() << "DestinationList from " << deviceName << "(" << destinationList.getNumberOfAddedDevices()
                 << " new devices, " << destinationList.getNumberOfRemovedDevices() << " removed devices)";

    std::vector<std::string> addedDevices = destinationList.getAddedDevicesList();
    std::vector<std::string> removedDevices = destinationList.getRemovedDevicesList();

    if (!addedDevices.empty())
    {
        primaryNodeManagementInterface->onNewDevices(addedDevices, datagramRecord.getTransportId());

        if (automaticSpineDiscovery)
        {
            // Request DetailedDiscoveries from all devices except the sender of the DestinationList and self
            for (std::string newDevice : addedDevices)
            {
                if (newDevice != deviceName && newDevice != getDeviceName())
                {
                    sendDetailedDiscoveryRead(newDevice);
                }
            }
        }
    }

    if (!removedDevices.empty())
    {
        primaryNodeManagementInterface->onRemovedDevices(removedDevices, datagramRecord.getTransportId());
    }

    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementUseCaseDataNotify(const DatagramRecord& datagramRecord)
{
    keo_datagram::Datagram const& datagram = datagramRecord.getDatagram();

    if (datagram.requiresResponse())
    {
        sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
    }

    std::string sourceDevice = datagram.getSourceAddress().getDevice();

    if (datagram.getCmd().hasFilters())
    {
        // Do full read
        LOG_INFO() << "Received partial UseCaseData notification from " << sourceDevice << ". Doing a full read...";
        keo_datagram::Header readHeader(
            getFullFeatureAddress(), datagram.getHeader().getAddressSource(), keo_datagram::CmdClassifier::Value::READ);
        keo_datagram::Datagram readDatagram(
            readHeader, keo_datagram::Cmd(std::make_shared<keo_datagram::NodeManagementUseCaseData>()));
        sendDatagram(readDatagram);
    }
    else
    {
        auto remoteUseCaseData
            = std::static_pointer_cast<keo_datagram::NodeManagementUseCaseData>(datagram.getCmdData());
        keo_datagram::UseCaseDiscovery useCaseDiscovery(useCaseData, *remoteUseCaseData.get());
        primaryNodeManagementInterface->onUseCaseDiscovery(sourceDevice, useCaseDiscovery);
    }

    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementDetailedDiscoveryReply(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();

    if (datagram.requiresResponse())
    {
        sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
    }

    keo_datagram::DetailedDiscovery detailedDiscovery;
    assert(datagram.getCmdDataType() == keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE);
    auto pDetailedDiscoveryData
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementDetailedDiscoveryDataConst>(datagram.getCmdData());

    assert(pDetailedDiscoveryData);
    detailedDiscovery.setDetailedDiscoveryData(*(pDetailedDiscoveryData.get()));
    if (!detailedDiscovery.getDeviceName().empty())
    {
        primaryNodeManagementInterface->onDetailedDiscovery(detailedDiscovery.getDeviceName(), detailedDiscovery);
        if (detailedDiscovery.hasFunction(keo_datagram::Function::Value::NODE_MANAGEMENT_DESTINATION_LIST_DATA))
        {
            sendDestinationListRead(detailedDiscovery.getDeviceName());
        }
    }
    else
    {
        LOG_WARN() << "Got invalid detailed discovery from " << datagram.getSourceAddress().getDevice();
    }

    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementDestinationListReply(const DatagramRecord& datagramRecord)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();

    if (datagram.requiresResponse())
    {
        sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
    }

    auto pDestinationListData
        = std::dynamic_pointer_cast<keo_datagram::NodeManagementDestinationListDataConst>(datagram.getCmdData());
    keo_datagram::DestinationList destinationList(pDestinationListData);
    std::string sourceDevice = datagram.getSourceAddress().getDevice();
    DEBUG_INFO() << "DestinationList from " << sourceDevice << " (" << destinationList.getListOfDestinations().size()
                 << " devices)";

    if (!destinationList.getListOfDestinations().empty())
    {
        std::vector<std::string> newDevices = destinationList.getListOfSmartDestinations();
        primaryNodeManagementInterface->onNewDevices(newDevices, datagramRecord.getTransportId());

        if (automaticSpineDiscovery)
        {
            // Request DetailedDiscoveries from all devices except the sender of the DestinationList and self
            for (std::string newDevice : newDevices)
            {
                if (sourceDevice.compare(newDevice) != 0 && newDevice.compare(getDeviceName()) != 0)
                {
                    sendDetailedDiscoveryRead(newDevice);
                }
            }
        }
    }

    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementUseCaseDataReply(const DatagramRecord& datagramRecord)
{
    keo_datagram::Datagram const& datagram = datagramRecord.getDatagram();

    if (datagram.requiresResponse())
    {
        sendDatagram(datagram.createResult(keo_datagram::SpineResultErrors::OK));
    }

    std::string sourceDevice = datagram.getSourceAddress().getDevice();
    auto remoteUseCaseData = std::dynamic_pointer_cast<keo_datagram::NodeManagementUseCaseData>(datagram.getCmdData());
    keo_datagram::UseCaseDiscovery useCaseDiscovery(useCaseData, *remoteUseCaseData.get());
    primaryNodeManagementInterface->onUseCaseDiscovery(sourceDevice, useCaseDiscovery);

    return true;
}

bool PrimaryNodeManagementFeature::handleNodeManagementSubscriptionRequestCallResult(
    const DatagramRecord& datagramRecord, const DatagramMemo& memo)
{
    std::lock_guard<std::mutex> locker(mtx);
    auto pendingCall = pendingSubscriptions.find(memo.getMsgCounter());

    if (pendingCall != pendingSubscriptions.end())
    {
        auto subcriptionResult
            = std::dynamic_pointer_cast<keo_datagram::ResultDataConst>(datagramRecord.getDatagram().getCmdData());

        if (subcriptionResult->getErrorNumber() == keo_datagram::SpineResultErrors::OK)
        {
            keo_datagram::SubscriptionManagementRequestCall pendingRequest
                = (*pendingCall).second.getSubscriptionRequest();

            /*
             * This primary node management feature does not remember which
             * other primary node management features it is subscribed to.
             * If this is needed at some point, keep track of the
             * subscriptions here.
             */

            DEBUG_INFO() << "Subscription to " << pendingRequest.getServerAddress().toString() << " has been accepted";
        }
        else
        {
            DEBUG_INFO() << "Subscription to " << memo.getDestination().toString() << " has been rejected";
        }

        pendingSubscriptions.erase(pendingCall);
    }
    else
    {
        LOG_WARN() << "Received subscription request response to unknown subscription request";
        return false;
    }

    return true;
}

bool PrimaryNodeManagementFeature::handlePendingDatagramResponse(
    const DatagramRecord& datagramRecord, const DatagramMemo& memo)
{
    const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
    if (datagram.isReply())
    {
        switch (datagram.getCmdDataType())
        {
            case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE:
                return handleNodeManagementDetailedDiscoveryReply(datagramRecord);
            case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE:
                return handleNodeManagementDestinationListReply(datagramRecord);
            case keo_datagram::CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE:
                return handleNodeManagementUseCaseDataReply(datagramRecord);
            default:
                break;
        }
    }
    else if (datagram.isResult())
    {
        switch (memo.getCmdType())
        {
            case keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE:
                return handleNodeManagementSubscriptionRequestCallResult(datagramRecord, memo);
            default:
                break;
        }
    }
    return false;
}

bool PrimaryNodeManagementFeature::timeoutHandler(const DatagramMemo& memo)
{
    switch (memo.getCmdType())
    {
        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE:
        {
            LOG_WARN() << "DetailedDiscovery read to " << memo.getDestination().getDevice() << " was not replied";
            return true;
        }
        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE:
        {
            LOG_WARN() << "DestinationList read to " << memo.getDestination().getDevice() << " was not replied";
            return true;
        }
        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_USE_CASE_DATA_TYPE:
        {
            LOG_WARN() << "UseCaseData read to " << memo.getDestination().getDevice() << " was not replied";
            return true;
        }
        case keo_datagram::CmdData::Type::NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE:
        {
            LOG_WARN() << "SubscriptionRequestCall to " << memo.getDestination().toString() << " was not replied";

            std::lock_guard<std::mutex> locker(mtx);
            auto pendingCall = pendingSubscriptions.find(memo.getMsgCounter());
            if (pendingCall != pendingSubscriptions.end())
            {
                pendingSubscriptions.erase(pendingCall);
            }
            return true;
        }
        default:
            break;
    }
    return false;
}

bool PrimaryNodeManagementFeature::allowBinding(const keo_datagram::FeatureAddress& clientAddress) const
{
    (void)clientAddress;
    return false;
}

bool PrimaryNodeManagementFeature::allowSubscription(const keo_datagram::FeatureAddress& clientAddress) const
{
    (void)clientAddress;
    return true;
}

void PrimaryNodeManagementFeature::updateMaxResponseDelay(
    const std::string& deviceName, const keo_datagram::NetworkManagementFeatureDescriptionData& description)
{
    keo_datagram::FeatureAddress fullFeatureAddress(
        deviceName, description.getFeatureAddress().getEntity(), description.getFeatureAddress().getFeature());

    assert(fullFeatureAddress.getDeviceIsSet());
    assert(fullFeatureAddress.getEntityIsSet());
    assert(fullFeatureAddress.getFeatureIsSet());

    if (description.getMaxResponseDelayIsSet())
    {
        unsigned long millies
            = description.getMaxResponseDelay().getAbsoluteMilliSeconds(keo_datagram::KeoDateTime::now());
        if (millies > DeviceDefinition::DatagramTimeoutDelay)
        {
            std::lock_guard<std::mutex> locker(mtx);
            remoteFeatureTimeouts[fullFeatureAddress] = millies;
        }
        else
        {
            // Remove old entry that cannot be overwritten because new value is invalid
            std::lock_guard<std::mutex> locker(mtx);
            remoteFeatureTimeouts.erase(fullFeatureAddress);
        }
    }
    else
    {
        // Remove out-dated entry
        std::lock_guard<std::mutex> locker(mtx);
        remoteFeatureTimeouts.erase(fullFeatureAddress);
    }
}

} /* namespace keo_spine */
