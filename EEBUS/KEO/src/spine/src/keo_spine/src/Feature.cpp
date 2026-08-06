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
 *     @brief      Feature class definition
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

#include <keo_spine/DeviceDefinition.h>
#include <keo_spine/Entity.h>
#include <keo_spine/Feature.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <assert.h>
#include <sstream>

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

class Feature::FeaturePriv
{
public:
    FeaturePriv()
        : pendingDatagram()
        , sendService(nullptr)
        , mtx()
    {
    }

    ~FeaturePriv()
    {
    }

    /**
     * Description of the feature. Used also for the detailed discovery
     */
    keo_datagram::NetworkManagementFeatureDescriptionData featureDescription;

    /**
     * Messages needing a reply Stored in a map with messageCounter (key) and datagram
     * summary (value)
     */
    std::map<keo_datagram::xs_unsignedLong, DatagramMemo> pendingDatagram;

    /**
     * Send service interface
     */
    SendServiceInterface* sendService;
    std::mutex mtx;

    std::string toString() const;
};

Feature::Feature()
    : p(new FeaturePriv())
{
}

Feature::Feature(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
    : p(new FeaturePriv())
{
    p->featureDescription = featureDescription;
}

Feature::~Feature()
{
    delete p;
}

void Feature::addPossibleOperation(
    const keo_datagram::Function& function, const keo_datagram::PossibleOperations& operations)
{
    if (!hasPossibleOperation(function, operations))
    {
        std::vector<keo_datagram::FunctionProperty> supportedFunctions;
        if (p->featureDescription.getSupportedFunctionIsSet())
        {
            // As there are no access methods to the supported functions, we need to copy the vector first and put it
            // back into the description
            supportedFunctions
                = std::vector<keo_datagram::FunctionProperty>(p->featureDescription.getSupportedFunction());
        }

        supportedFunctions.push_back(keo_datagram::FunctionProperty(keo_datagram::Function(function), operations));
        p->featureDescription.setSupportedFunction(supportedFunctions);
    }
}

bool Feature::hasPossibleOperation(
    const keo_datagram::Function& function, const keo_datagram::PossibleOperations& operations)
{
    if (p->featureDescription.getSupportedFunctionIsSet())
    {
        for (const auto& supportedFunction : p->featureDescription.getSupportedFunction())
        {
            if (supportedFunction.getFunction() == function && supportedFunction.getPossibleOperations() == operations)
            {
                return true;
            }
        }
    }
    return false;
}

bool Feature::removePossibleOperation(const keo_datagram::Function& function)
{
    bool removedOne = false;
    if (p->featureDescription.getSupportedFunctionIsSet())
    {
        // As there are no access methods to the supported functions, we need to copy the vector first and put it back
        // into the description
        std::vector<keo_datagram::FunctionProperty> supportedFunctions
            = std::vector<keo_datagram::FunctionProperty>(p->featureDescription.getSupportedFunction());
        for (auto it = supportedFunctions.begin(); it != supportedFunctions.end();)
        {
            if (it->getFunction() == function)
            {
                it = supportedFunctions.erase(it);
                removedOne = true;
            }
            else
            {
                ++it;
            }
        }
        if (!supportedFunctions.empty())
        {
            p->featureDescription.setSupportedFunction(supportedFunctions);
        }
        else
        {
            p->featureDescription.cleanSupportedFunction();
        }
    }
    return removedOne;
}

void Feature::setFeatureDescription(const keo_datagram::NetworkManagementFeatureDescriptionData& featureDescription)
{
    p->featureDescription = featureDescription;
}

const keo_datagram::NetworkManagementFeatureDescriptionData& Feature::getFeatureDescription() const
{
    return p->featureDescription;
}

void Feature::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery)
{
    (void)deviceName;
    (void)detailedDiscovery;
}

void Feature::onDetailedDiscoveryPartial(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& detailedDiscoveryPartial)
{
    (void)deviceName;
    (void)detailedDiscoveryPartial;
}

void Feature::onUseCaseDiscovery(const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery)
{
    (void)deviceName;
    (void)useCaseDiscovery;
}

void Feature::onRemovedDevices(const std::vector<std::string>& devices)
{
    (void)devices;
}

void Feature::setSendService(SendServiceInterface* sendServiceInterface)
{
    assert(nullptr != sendServiceInterface);
    p->sendService = sendServiceInterface;
}

std::string Feature::getDeviceName() const
{
    if (nullptr != p->sendService)
    {
        return p->sendService->getDeviceName();
    }
    else
    {
        LOG_WARN() << "Cannot get deviceName for feature, SendServiceInterface is not set!";
        return std::string();
    }
}

keo_datagram::FeatureAddress Feature::getFullFeatureAddress() const
{
    keo_datagram::FeatureAddress addr = p->featureDescription.getFeatureAddress();
    const std::string& deviceName = getDeviceName();
    if (!deviceName.empty())
    {
        addr.setDevice(deviceName);
    }
    return addr;
}

bool Feature::equalsFeatureAddress(const keo_datagram::FeatureAddress& otherAddress) const
{
    bool equal = true; // assumption

    if (otherAddress.getDeviceIsSet() && otherAddress.getDevice().compare(getDeviceName()) != 0)
    {
        equal = false;
    }
    else
    {
        const keo_datagram::FeatureAddress& descriptionFeatureAddress = p->featureDescription.getFeatureAddress();

        if (otherAddress.getEntity() != descriptionFeatureAddress.getEntity())
        {
            equal = false;
        }
        else
        {
            if (otherAddress.getFeature() != descriptionFeatureAddress.getFeature())
            {
                equal = false;
            }
        }
    }
    return equal;
}

void Feature::onClose()
{
    killAllPendingTimeouts();
}

bool Feature::validate()
{
    bool success = true;
    if (!p->featureDescription.getFeatureAddressIsSet())
    {
        LOG_WARN() << this->toString() << " could not be validated, it does not have feature address";
        success = false;
    }
    else if (!p->featureDescription.getFeatureAddress().getEntityIsSet())
    {
        LOG_WARN() << this->toString()
                   << " could not be validated, it does not have an entity part set in its feature address";
        success = false;
    }
    else if (!p->featureDescription.getFeatureAddress().getFeatureIsSet())
    {
        LOG_WARN() << this->toString()
                   << " could not be validated, it does not have a feature part set in its feature address";
        success = false;
    }
    else if (!p->featureDescription.getFeatureTypeIsSet())
    {
        LOG_WARN() << this->toString() << " could not be validated, it does not have a feature type set";
        success = false;
    }
    else if (!p->featureDescription.getRoleIsSet())
    {
        LOG_WARN() << this->toString() << " could not be validated, it does not have a role set";
        success = false;
    }
    return success;
}

bool Feature::isConnected(const std::string& deviceName)
{
    if (nullptr != p->sendService)
    {
        return p->sendService->isConnected(deviceName);
    }
    LOG_WARN() << "Cannot check if connected, SendServiceInterface is not set!";
    return false;
}

keo_datagram::xs_unsignedLong Feature::sendRead(
    const keo_datagram::FeatureAddress& destination, const keo_datagram::Cmd& cmd)
{
    keo_datagram::FeatureAddress source(getDeviceName(), p->featureDescription.getFeatureAddress().getEntity(),
        p->featureDescription.getFeatureAddress().getFeature());
    keo_datagram::Header header = keo_datagram::Header(source, destination, keo_datagram::CmdClassifier::Value::READ);
    keo_datagram::Datagram datagram(header, cmd);
    if (0 != sendPendingDatagram(datagram))
    {
        return datagram.getMsgCounter();
    }
    return 0;
}

keo_datagram::xs_unsignedLong Feature::send(const keo_datagram::FeatureAddress& destination,
    const keo_datagram::Cmd& cmd, const keo_datagram::CmdClassifier& cmdClassifier, bool ackRequest)
{
    keo_datagram::FeatureAddress source(getDeviceName(), p->featureDescription.getFeatureAddress().getEntity(),
        p->featureDescription.getFeatureAddress().getFeature());
    keo_datagram::Header header = keo_datagram::Header(source, destination, cmdClassifier.getValue());
    if (ackRequest)
    {
        header.setAckRequest(ackRequest);
    }
    keo_datagram::Datagram datagram = keo_datagram::Datagram(header, cmd);

    if (ackRequest)
    {
        if (0 != sendPendingDatagram(datagram))
        {
            return datagram.getMsgCounter();
        }
    }
    else
    {
        if (sendDatagram(datagram))
        {
            return datagram.getMsgCounter();
        }
    }
    return 0;
}

bool Feature::handlePendingDatagramResponse(const DatagramRecord& datagramRecord)
{
    if (!datagramRecord.getDatagram().isEmpty())
    {
        const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
        keo_datagram::xs_unsignedLong msgCounterReference = datagram.getMsgCounterReference();
        DatagramMemo memo = removePendingDatagramByMsgCounter(msgCounterReference);
        if (!memo.isEmpty())
        {
            LOG_INFO() << "Handling pending datagram at feature '" << getFullFeatureAddress().toString()
                       << "'. Message counter: " << memo.getMsgCounter();
            return handlePendingDatagramResponse(datagramRecord, memo);
        }
        else
        {
            LOG_WARN() << "Cannot handle pending datagram at feature '" << getFullFeatureAddress().toString()
                       << "'. Message counter reference " << msgCounterReference << " is unknown.";
            return true;
        }
    }
    else
    {
        LOG_WARN() << "Cannot handle datagram at feature '" << getFullFeatureAddress().toString()
                   << "'. DatagramRecord is invalid.";
    }
    return false;
}

bool Feature::sendDatagram(const keo_datagram::Datagram& datagram) const
{
    DatagramRecord record(datagram);
    return sendDatagram(record);
}

bool Feature::sendDatagram(DatagramRecord& datagramRecord) const
{
    if (nullptr != p->sendService)
    {
        if (datagramRecord.getDatagram().isHeaderValid() && datagramRecord.getDatagram().isPayloadValid())
        {
            return p->sendService->sendDatagram(datagramRecord);
        }
        else
        {
            LOG_WARN() << "Cannot sendDatagram from " << this->toString();
        }
    }
    else
    {
        LOG_WARN() << "Cannot sendDatagram for feature" << p->featureDescription.getFeatureAddress().toString()
                   << ", SendServiceInterface is not set!";
    }
    return false;
}

bool Feature::sendDatagram(DatagramRecordPtr datagramRecord) const
{
    return sendDatagram(*(datagramRecord.get()));
}

keo_datagram::xs_unsignedLong Feature::sendPendingDatagram(const keo_datagram::Datagram& datagram)
{
    keo_datagram::xs_unsignedLong msgCounter = 0;
    if (datagram.isHeaderValid() && datagram.isPayloadValid())
    {
        msgCounter = datagram.getMsgCounter();
        if (msgCounter > 0)
        {
            p->mtx.lock();
            if (p->pendingDatagram.find(msgCounter) == p->pendingDatagram.end())
            {
                p->pendingDatagram[msgCounter] = DatagramMemo(datagram);
                p->mtx.unlock();
                if (nullptr != p->sendService)
                {
                    DatagramRecord record(datagram);
                    auto finalMsgCounter = p->sendService->sendPendingDatagram(record);

                    if (finalMsgCounter != msgCounter)
                    {
                        // Sending was not successful -> remove pending datagram
                        std::lock_guard<std::mutex> locker(p->mtx);
                        p->pendingDatagram.erase(msgCounter);
                        msgCounter = 0;
                    }
                }
                else
                {
                    LOG_WARN() << "Cannot sendDatagram from " << this->toString()
                               << " (SendServiceInterface is not set)";
                }
            }
            else
            {
                p->mtx.unlock();
                LOG_ERROR() << "MessageCounter " << msgCounter << " already exist at " << this->toString();
            }
        }
    }
    if (msgCounter == 0)
    {
        LOG_WARN() << "Cannot sendDatagram from " << this->toString();
    }
    return msgCounter;
}

keo_datagram::xs_unsignedLong Feature::sendPendingDatagram(
    const DatagramRecordPtr datagramRecord, long datagramTimeoutDelay)
{
    return sendPendingDatagram(*(datagramRecord.get()), datagramTimeoutDelay);
}

keo_datagram::xs_unsignedLong Feature::sendPendingDatagram(
    DatagramRecord& datagramRecord, long datagramTimeoutDelay)
{
    keo_datagram::xs_unsignedLong msgCounter = 0;
    if (datagramRecord.getDatagram().isHeaderValid() && datagramRecord.getDatagram().isPayloadValid())
    {
        const keo_datagram::Datagram& datagram = datagramRecord.getDatagram();
        msgCounter = datagram.getMsgCounter();
        if (msgCounter > 0)
        {
            p->mtx.lock();
            if (p->pendingDatagram.find(msgCounter) == p->pendingDatagram.end())
            {
                p->pendingDatagram[msgCounter] = DatagramMemo(datagramRecord.getDatagram());
                p->mtx.unlock();
                if (nullptr != p->sendService)
                {
                    auto finalMsgCounter = p->sendService->sendPendingDatagram(datagramRecord, datagramTimeoutDelay);

                    if (finalMsgCounter != msgCounter)
                    {
                        // Sending was not successful -> remove pending datagram
                        std::lock_guard<std::mutex> locker(p->mtx);
                        p->pendingDatagram.erase(msgCounter);
                        msgCounter = 0;
                    }
                }
                else
                {
                    LOG_WARN() << "Cannot sendDatagram from " << this->toString()
                               << " (SendServiceInterface is not set)";
                }
            }
            else
            {
                p->mtx.unlock();
                LOG_ERROR() << "MessageCounter " << msgCounter << " already exist at " << this->toString();
            }
        }
    }
    if (msgCounter == 0)
    {
        LOG_WARN() << "Cannot sendDatagram from " << this->toString();
    }
    return msgCounter;
}

DatagramMemo Feature::removePendingDatagramByMsgCounter(keo_datagram::xs_unsignedLong msgCounter)
{
    std::lock_guard<std::mutex> locker(p->mtx);
    auto it = p->pendingDatagram.find(msgCounter);
    DatagramMemo memo;
    if (it != p->pendingDatagram.end())
    {
        memo = it->second;
        if (nullptr != p->sendService)
        {
            p->sendService->removeTimeoutByMsgCounter(msgCounter);
        }
        else
        {
            LOG_WARN() << "SendServiceInterface is not initialized at feature '" << getFullFeatureAddress().toString()
                       << "'";
        }
        p->pendingDatagram.erase(it);
    }
    else
    {
        LOG_WARN() << "Could not remove pending datagram with messageCounter=" << msgCounter << " (not found)";
    }
    return memo;
}

void Feature::killAllPendingTimeouts()
{
    std::lock_guard<std::mutex> locker(p->mtx);
    for (auto nextIter = p->pendingDatagram.begin(); nextIter != p->pendingDatagram.end();)
    {
        auto actIter = nextIter++;
        if (nullptr != p->sendService)
        {
            p->sendService->removeTimeoutByMsgCounter(actIter->first);
        }
        else
        {
            LOG_WARN() << "SendServiceInterface is not initialized at feature '"
                       << p->featureDescription.getFeatureAddress().toString() << "'";
        }
        p->pendingDatagram.erase(actIter);
    }
}

bool Feature::killPendingTimeout(keo_datagram::xs_unsignedLong msgCounter)
{
    bool killed = false;
    if (nullptr != p->sendService)
    {
        p->sendService->removeTimeoutByMsgCounter(msgCounter);
        LOG_WARN() << "SendServiceInterface is not initialized at feature '"
                   << p->featureDescription.getFeatureAddress().toString() << "'";
    }
    std::lock_guard<std::mutex> locker(p->mtx);
    auto it = p->pendingDatagram.find(msgCounter);
    if (it != p->pendingDatagram.end())
    {
        DatagramMemo memoPtr = it->second;
        p->pendingDatagram.erase(it);
        killed = true;
    }
    else
    {
        LOG_WARN() << "Could not remove pending datagram with messageCounter=" << msgCounter << " (not found)";
    }
    return killed;
}

void Feature::timeout(keo_datagram::xs_unsignedLong msgCounter)
{
    p->mtx.lock();
    auto it = p->pendingDatagram.find(msgCounter);
    if (it != p->pendingDatagram.end())
    {
        const auto memo = it->second;
        p->pendingDatagram.erase(it);
        p->mtx.unlock();
        if (!timeoutHandler(memo))
        {
            LOG_WARN() << "Timeout messageCounter '" << msgCounter << "' not handled at feature '"
                       << p->featureDescription.getFeatureAddress().toString() << "'";
        }
    }
    else
    {
        p->mtx.unlock();
        LOG_WARN() << "Could not handle timeout with messageCounter=" << msgCounter << " (not found)";
    }
}

std::string Feature::FeaturePriv::toString() const
{
    // Example String: "Feature 0 (Measurement, role: client)"
    std::stringstream ss;
    ss << "Feature";
    if (featureDescription.getFeatureAddressIsSet())
    {
        ss << " " << featureDescription.getFeatureAddress().getFeature();
    }
    if (featureDescription.getFeatureTypeIsSet() && featureDescription.getRoleIsSet())
    {
        ss << " (" + featureDescription.getFeatureType().toString();
        ss << ", role: " << featureDescription.getRole().toString() << ")";
    }
    else if (featureDescription.getFeatureTypeIsSet() || featureDescription.getRoleIsSet())
    {
        ss << " (";
        ss << (featureDescription.getFeatureTypeIsSet() ? featureDescription.getFeatureType().toString()
                                                        : "role: " + featureDescription.getRole().toString());
        ss << ")";
    }
    return ss.str();
}

std::string Feature::toString() const
{
    return p->toString();
}

} /* namespace keo_spine */
