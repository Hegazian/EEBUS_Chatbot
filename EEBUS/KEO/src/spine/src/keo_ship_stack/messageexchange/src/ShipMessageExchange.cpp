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
 *     @brief      Control the exchange of SHIP messages
 *
 *     @par        There are different kind of SHIP messages, which must be handled.
 *                 Furthermore there is closing, certificate verification and pin handling.
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "ShipMessageExchange.h"
#include "ShipControlTransformer.h"
#include "ShipDataTransformer.h"
#include "ShipMessageExchangeConnectionConfirmedListener.h"
#include "internal/NodeInfo.h"
#include <keo_ship/ShipStack.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <assert.h>
#include <keo_tool/KEJobRunner.h>
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

const int ShipMessageExchange::CLOSE_STATUS_CODE_ID_MISMATCH = 4450;
const int ShipMessageExchange::CLOSE_STATUS_CODE_CONNECTION_CLOSE_TIMEOUT = 4451;
const int ShipMessageExchange::CLOSE_STATUS_CODE_USER_UNTRUSTED = 4452;
const std::string SHIP_DATA_MESSAGE_HEADER = "{\"data\":[{\"header\":[{\"protocolId\":\"ee1.0\"}]},{\"payload\":";
const std::string SHIP_DATA_MESSAGE_FOOTER = "}]}";

// Thread to verify certificate from the application
class ShipMessageExchange::CertificateResultProcessor : public keo_tool::KEJobRunnerJob
{
public:
    CertificateResultProcessor(ShipMessageExchange& parent)
        : m_parent(parent)
    {
    }

    virtual void run()
    {
        if (NULL != m_parent.m_messageExchangeListener)
        {
            unsigned short result = m_parent.m_messageExchangeListener->onTrustCertificate(
                m_parent.m_shipSocket->getRemoteSki(), m_parent.m_shipSocket->getRemoteCertificate());
            m_parent.setUserTrust(result);
        }
    };

private:
    ShipMessageExchange& m_parent;
};

// Thread to verify pin from the application
class ShipMessageExchange::PinVerificationResultProcessor : public keo_tool::KEJobRunnerJob
{
public:
    PinVerificationResultProcessor(ShipMessageExchange& parent, const std::string& pinInput)
        : m_parent(parent)
        , m_pin(pinInput)
    {
    }

    virtual void run()
    {
        if (NULL != m_parent.m_messageExchangeListener)
        {
            unsigned short result = m_parent.m_messageExchangeListener->onValidatePin(m_pin);

            DEBUG_INFO() << m_parent.m_displayName << " Get pin verification, second factor trust " << result;

            m_parent.m_connectionStateHandler.setSecondFactorTrust(result);
            std::string nodeId = m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getId();

            if (!nodeId.empty())
            {
                TrustLevel trustLevel
                    = m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getTrustLevel();
                m_parent.m_securityHandler->setTrustlevel(nodeId, m_parent.m_shipSocket->getRemoteSki(),
                    m_parent.m_shipSocket->getRemoteCertificate(), trustLevel);
            }
        }
    };

private:
    ShipMessageExchange& m_parent;
    std::string m_pin;
};

// Thread to send data message to the application
class ShipMessageExchange::DataMessageExecutor : public keo_tool::KEJobRunnerJob
{
public:
    DataMessageExecutor(ShipMessageExchange& parent, const std::vector<char>& message)
        : m_parent(parent)
        , m_message(message)
    {
    }

    virtual void run()
    {
        if (NULL != m_parent.m_messageExchangeListener)
        {
            m_parent.m_messageExchangeListener->onMessage(m_message);
        }
    }

private:
    ShipMessageExchange& m_parent;
    std::vector<char> m_message;
};

// Thread to send DataExchangeEnable to the application
class ShipMessageExchange::SendDataExchangeEnableExecutor : public keo_tool::KEJobRunnerJob
{
public:
    SendDataExchangeEnableExecutor(ShipMessageExchange& parent)
        : m_parent(parent)
    {
    }

    virtual void run()
    {
        if (NULL != m_parent.m_messageExchangeListener)
        {
            m_parent.m_messageExchangeListener->onDataExchangeEnabled();
        }

        m_parent.m_confirmedListener->onConnectionConfirmed(
            m_parent.m_shipSocket, m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getId());
    }

private:
    ShipMessageExchange& m_parent;
};

ShipMessageExchange::ShipMessageExchange(ShipMessageExchangeListener* listener)
    : m_connectionStateListener(*this)
    , m_connectionStateHandler(&m_connectionStateListener)
    , m_messageExchangeListener(listener)
    , m_confirmedListener(0)
    , m_shipSocket(0)
    , m_securityHandler(0)
    , m_messageListMutex()
    , m_mtx()
    , m_shipDataExchangeEnabled(false)
    , m_payloadDataExchangeEnabled(false)
    , m_closeInTimer(std::bind(&ShipMessageExchange::closeInTimeout, this))
    , m_closed(true)
{
    jobRunner = keo_tool::KEJobRunner::start();
}

ShipMessageExchange::~ShipMessageExchange()
{
    DEBUG_FUNC() << (void*)this;
    onFinalize();

    if (jobRunner != 0)
    {
        delete jobRunner;
        jobRunner = 0;
    }
    m_messageExchangeListener = 0;
}

void ShipMessageExchange::onConnect(ShipMessageExchangeConnectionConfirmedListener* confirmedListener,
    ShipSocket* shipSocket, SecurityHandlerPtr securityHandler, const ShipStackConfiguration& shipStackConfiguration,
    const std::string& serverUri)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    if (m_closed && 0 == m_shipSocket)
    {
        m_closed = false;
        m_shipSocket = shipSocket;
        m_confirmedListener = confirmedListener;
        m_securityHandler = securityHandler;
        m_displayName = m_shipSocket->getRemoteSki();
        m_remoteSKI = m_shipSocket->getRemoteSki();

        DEBUG_INFO() << m_displayName << " New SHIP connection, current role " << (getIsClient() ? "client" : "server");

        NodeInfo nodeInfo;
        nodeInfo.setConnected(true);
        nodeInfo.setNeedUnrestrictedAccess(true);
        nodeInfo.setPinOwnRequirement(shipStackConfiguration.getPinRequirement());

        m_connectionStateHandler.setProtocolConfig(shipStackConfiguration.getProtocolConfig());
        m_connectionStateHandler.setDisplayName(m_displayName);

        // check certificate
        std::string remoteId = m_securityHandler->getId(m_shipSocket->getRemoteCertificate());

        if (!remoteId.empty())
        {
            nodeInfo.setPreliminaryId(remoteId);
            keo_ship::TrustLevel trustLevel = m_securityHandler->getTrustLevel(remoteId, m_shipSocket->getRemoteSki());
            nodeInfo.setTrustLevel(trustLevel);

            if (trustLevel.getSecondFactorTrust() > TrustLevel::TRUST_VALUE_2NDFACTOR_NONE)
            {
                nodeInfo.setPinOwnRequirement(PinRequirement::PIN_OK);
            }
        }

        m_connectionStateHandler.start(shipStackConfiguration.getShipId(), nodeInfo, getIsClient(), serverUri);

        if (remoteId.empty())
        {
            doCertificateVerification();
        }

        // Incoming messages from ShipSocket are unblocked from now on
        m_shipSocket->setShipSocketMessageListener(this);
    }
}

void ShipMessageExchange::onFinalize()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    if (!m_closed && 0 != m_shipSocket)
    {
        m_closed = true;
        m_closeInTimer.stop();

        if (jobRunner->isRunning())
        {
            m_mtx.unlock();
            keo_tool::KEJobRunner::stop(jobRunner);
            m_mtx.lock();
        }
        DEBUG_INFO() << m_displayName << " SME finalize";
    }
}

std::string ShipMessageExchange::getId() const
{
    return m_connectionStateHandler.getNodeProtocolInfoReference().getId();
}

PinRequirement ShipMessageExchange::getPinRequirement() const
{
    return m_connectionStateHandler.getNodeProtocolInfoReference().getPinRequirement();
}

std::string ShipMessageExchange::getSki() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return m_remoteSKI;
}

std::string ShipMessageExchange::getIpAddress() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);

    if (nullptr != m_shipSocket && !m_closed)
    {
        return m_shipSocket->getIP();
    }
    return std::string();
}

int ShipMessageExchange::getIpPort() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    if (nullptr != m_shipSocket && !m_closed)
    {
        return m_shipSocket->getPort();
    }
    return 0;
}

TrustLevel ShipMessageExchange::getTrustLevel() const
{
    return m_connectionStateHandler.getNodeProtocolInfoReference().getTrustLevel();
}

bool ShipMessageExchange::getIsClient() const
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    return (m_shipSocket != 0 ? (m_shipSocket->getRole() == ShipSocket::SocketRole::ROLE_CLIENT) : false);
}

/**
 * Send SHIP message to core.
 *
 * @param message
 *            SHIP message
 * @return True if successful sent to core
 */
bool ShipMessageExchange::sendMessage(const std::vector<char>& payload)
{
    if (!m_closed)
    {
        std::lock_guard<std::recursive_mutex> locker(m_mtx);
        DEBUG_FUNC();
        if (m_shipSocket != 0 && !payload.empty() && m_payloadDataExchangeEnabled)
        {
            LOG_TRACE() << m_displayName << " Send message of type '" << ShipMessageType::MESSAGE_TYPE_DATA
                        << "' with size " << payload.size();

            std::vector<char> dataMessage;
            dataMessage.push_back(ShipMessageType::MESSAGE_TYPE_DATA);
            dataMessage.insert(dataMessage.end(), SHIP_DATA_MESSAGE_HEADER.begin(), SHIP_DATA_MESSAGE_HEADER.end());
            dataMessage.insert(dataMessage.end(), payload.begin(), payload.end());
            dataMessage.insert(dataMessage.end(), SHIP_DATA_MESSAGE_FOOTER.begin(), SHIP_DATA_MESSAGE_FOOTER.end());

            return sendToPeer(dataMessage);
        }
    }
    return false;
}

void ShipMessageExchange::close(int statusCode, const std::string& reason)
{
    if (!m_closed)
    {
        std::lock_guard<std::recursive_mutex> locker(m_mtx);
        if (m_shipSocket != 0)
        {
            DEBUG_FUNC() << " " << m_displayName << " Close connection " << statusCode << reason.c_str();
            m_closeInTimer.stop();
            m_shipSocket->close(statusCode, reason);
        }
    }
}

void ShipMessageExchange::closeIn(int maxTimeMilliSeconds, bool isRemovedConnection)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    if (m_shipSocket != 0 || !m_payloadDataExchangeEnabled)
    {
        return;
    }
    keo_ship::ConnectionCloseReason reason = isRemovedConnection
        ? keo_ship::ConnectionCloseReason::CONNECTIONCLOSEREASON_REMOVEDCONNECTION
        : keo_ship::ConnectionCloseReason::CONNECTIONCLOSEREASON_UNSPECIFIC;

    LOG_WARNING() << m_displayName << " Close connection in " << maxTimeMilliSeconds << " " << reason.getDataString();

    m_connectionStateHandler.closeAnnounce(maxTimeMilliSeconds, reason);

    m_closeReason = reason.getDataString();
    m_closeInTimer.start(maxTimeMilliSeconds);
}

void ShipMessageExchange::closeInConfirm()
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    if (!m_payloadDataExchangeEnabled)
    {
        return;
    }
    DEBUG_INFO() << m_displayName << " Confirm close connection";
    m_connectionStateHandler.closeAnnounceConfirm();
}

void ShipMessageExchange::onShipMessage(const std::vector<char>& message)
{
    if (!m_closed)
    {
        shipMessage(message);
    }
}

void ShipMessageExchange::setPin(const std::string& pin)
{
    m_connectionStateHandler.setPin(pin);
}

void ShipMessageExchange::setPinPenaltyTime(long penaltyTime)
{
    m_connectionStateHandler.setPinPenaltyTime(penaltyTime);
}

void ShipMessageExchange::closeInTimeout()
{
    close(CLOSE_STATUS_CODE_CONNECTION_CLOSE_TIMEOUT, m_closeReason);
}

void ShipMessageExchange::doCertificateVerification()
{
    DEBUG_INFO() << m_displayName << " Get certificate verification";

    CertificateResultProcessor* job = new CertificateResultProcessor(*this);

    if (0 != jobRunner->addJob(job))
    {
        delete job;
        LOG_FATAL() << m_displayName << ": Cannot add job at doCertificateVerification()";
        //exit(EXIT_FAILURE);
    }
}

void ShipMessageExchange::shipMessage(const std::vector<char>& data)
{
    std::lock_guard<std::recursive_mutex> locker(m_mtx);
    DEBUG_INFO() << m_displayName << " shipMessage received";
    if (data.size())
    {
        std::string dataString(data.begin() + 1, data.end());
        LOG_VERBOSE(9) << m_displayName << " Message " << data[0] << dataString;
    }
    if (data.size() > 0)
    {
        ShipMessageType shipMessageType = static_cast<ShipMessageType>(data[0]);
        switch (shipMessageType)
        {

            case MESSAGE_TYPE_INIT:
                DEBUG_INFO() << m_displayName << " CMI_Init";
                m_connectionStateHandler.receiveCMIInitMessage(data);
                break;

            case MESSAGE_TYPE_CONTROL:
            {
                keo_ship::CShipDataClass* pDataClass
                    = ShipControlTransformer::createDataClassFromCommissioningMessage(data);
                m_connectionStateHandler.receiveCMIControlMessage(pDataClass);
                if (pDataClass != NULL)
                {
                    delete pDataClass;
                }
                break;
            }

            case MESSAGE_TYPE_END:
            {
                keo_ship::CShipDataClass* pDataClass
                    = ShipControlTransformer::createDataClassFromCommissioningMessage(data);
                m_connectionStateHandler.receiveEndMessage(pDataClass);
                if (pDataClass != NULL)
                {
                    delete pDataClass;
                }
                break;
            }
            case MESSAGE_TYPE_DATA:
                DEBUG_INFO() << m_displayName << " CMI_Data";
                handleCmiData(data);
                break;

            default:
                LOG_WARN() << m_displayName << " Unknown CMI code, discarding message.";
                break;
        }
    }
    else
    {
        LOG_WARN() << m_displayName << " Empty message received!";
    }
}
void ShipMessageExchange::handleCmiData(const std::vector<char>& data)
{
    keo_ship::Data* dataMessage = ShipDataTransformer::createShipDataMessageFromJson(data);
    if (dataMessage)
    {
        if (m_payloadDataExchangeEnabled)
        {
            sendDataExchangeMessage(dataMessage->getPayload().getPayload());
        }
        else if (m_shipDataExchangeEnabled)
        {
            std::lock_guard<std::recursive_mutex> locker(m_messageListMutex);
            DEBUG_INFO() << m_displayName << " Payload data exchange not enabled. Enqueue data.";
            m_messageList.push_back(dataMessage->getPayload().getPayload());
        }
        else
        {
            LOG_WARN() << m_displayName << " Message received, dataExchange not enabled. Discarding message!";
        }
        delete dataMessage;
    }
    else
    {
        LOG_WARN() << m_displayName
                   << " Could not create SHIP message from JSON: " << std::string(data.begin() + 1, data.end());
    }
}

bool ShipMessageExchange::sendToPeer(const std::vector<char>& message)
{
    DEBUG_INFO() << m_displayName << " Send message";
    if (message.size())
    {
        std::string dataString(message.begin() + 1, message.end());
        LOG_VERBOSE(9) << m_displayName << " sendToPeer " << dataString;
    }

    return m_shipSocket->sendMessage(message);
}

void ShipMessageExchange::sendDataExchangeMessage(const std::vector<char>& message)
{
    DEBUG_FUNC();
    if (!m_closed)
    {
        DataMessageExecutor* job = new DataMessageExecutor(*this, message);

        int result = jobRunner->addJob(job);
        if (result == -1)
        {
            delete job;
            LOG_FATAL() << m_displayName << ": Cannot add null-job at sendDataExchangeMessage()";
            //exit(EXIT_FAILURE);
        }
        else if (result == -2)
        {
            LOG_WARN() << "Job rejected. JobRunner is terminating or not running.";
            delete job;
        }
    }
    else
    {
        DEBUG_INFO()
            << "ShipMessageExchange::sendDataExchangeMessage Could not send DataExchangeMessage because closing";
    }
}

void ShipMessageExchange::setUserTrust(unsigned short userTrust)
{
    if (!m_closed)
    {
        DEBUG_INFO() << m_displayName << " Certificate verification done, trust level is " << userTrust;
        if (userTrust == keo_ship::TrustLevel::TRUST_VALUE_USER_UNTRUSTED)
        {
            close(CLOSE_STATUS_CODE_USER_UNTRUSTED, "Node rejected by application.");
        }
        else
        {
            m_connectionStateHandler.setUserTrust(userTrust);
        }
    }
}

ShipMessageExchange::ConnectionStateListener::ConnectionStateListener(ShipMessageExchange& parent)
    : m_parent(parent)
{
}

bool ShipMessageExchange::ConnectionStateListener::sendToShipTransport(const std::vector<char>& message)
{
    return m_parent.sendToPeer(message);
}

void ShipMessageExchange::ConnectionStateListener::announceEvent(NodeEvent event, const std::string& data)
{
    DEBUG_FUNC();
    switch (event)
    {
        case NODE_EVENT_ENABLE_DATA_EXCHANGE:
            DEBUG_INFO() << m_parent.m_displayName << " Enable data exchange"; // debug
            m_parent.m_shipDataExchangeEnabled = true;
            break;

        case NODE_EVENT_RECEIVED_ID:
            handleEventReceivedId();
            break;

        case NODE_EVENT_PIN_RECEIVED:
            doPinVerification(data);
            break;

        case NODE_EVENT_PIN_INPUT_READY:
            if (NULL != m_parent.m_messageExchangeListener)
            {
                m_parent.m_messageExchangeListener->onPinRequest();
            }
            break;

        case NODE_EVENT_PIN_RECALL_TIMEOUT:
            if (NULL != m_parent.m_messageExchangeListener)
            {
                m_parent.m_messageExchangeListener->onPinRecallTimeout();
            }
            break;

        case NODE_EVENT_WRONG_PIN:
            if (NULL != m_parent.m_messageExchangeListener)
            {
                m_parent.m_messageExchangeListener->onPinWrong();
            }
            break;

        case NODE_EVENT_CLOSE_ANNOUNCE:
        {
            std::size_t index = data.find(" ");
            std::string reason;
            int time = 0;
            if (index != std::string::npos)
            {
                time = std::stoi(data.substr(0, index));
                reason = data.substr(index++);
            }
            else
            {
                reason = data;
            }
            bool isRemovedConnection
                = reason.compare(ConnectionCloseReason(ConnectionCloseReason::CONNECTIONCLOSEREASON_REMOVEDCONNECTION)
                                     .getDataString())
                    == 0
                ? true
                : false;
            if (NULL != m_parent.m_messageExchangeListener)
            {
                m_parent.m_messageExchangeListener->onCloseAnnounce(time, isRemovedConnection);
            }
            break;
        }
        case NODE_EVENT_CLOSE_ANNOUNCE_CONFIRM:
            if (NULL != m_parent.m_messageExchangeListener)
            {
                m_parent.m_messageExchangeListener->onCloseAnnounceConfirm();
            }
            break;

        default:
            break;
    }
}

void ShipMessageExchange::ConnectionStateListener::closeConnection(int statusCode, const std::string& reason)
{
    DEBUG_INFO() << m_parent.m_displayName << " SME close connection " << statusCode << reason;
    m_parent.close(statusCode, reason);
}

void ShipMessageExchange::ConnectionStateListener::doPinVerification(const std::string& pin)
{
    DEBUG_INFO() << m_parent.m_displayName << " Get pin verification";

    PinVerificationResultProcessor* job = new PinVerificationResultProcessor(m_parent, pin);

    if (0 != m_parent.jobRunner->addJob(job))
    {
        delete job;
        LOG_FATAL() << m_parent.m_displayName << ": Cannot add job at doPinVerification()";
        //exit(EXIT_FAILURE);
    }
}

void ShipMessageExchange::ConnectionStateListener::handleEventReceivedId()
{
    std::string id = m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getId();
    std::string preliminary = m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getPreliminaryId();

    DEBUG_INFO() << m_parent.m_displayName << " Peer ID received "
                 << m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getId().c_str();

    if (preliminary.empty())
    {
        m_parent.m_displayName = id;
        m_parent.m_shipSocket->setDisplayName(id);
        m_parent.m_connectionStateHandler.setDisplayName(m_parent.m_displayName);
        m_parent.m_payloadDataExchangeEnabled = true;

        TrustLevel trustLevel = m_parent.m_connectionStateHandler.getNodeProtocolInfoReference().getTrustLevel();
        // TODO PIN handling
        m_parent.m_securityHandler->setTrustlevel(
            id, m_parent.m_shipSocket->getRemoteSki(), m_parent.m_shipSocket->getRemoteCertificate(), trustLevel);
    }
    else if (preliminary.compare(id) == 0)
    { // TODO equalsIgnoreCase(id)) {
        m_parent.m_displayName = id;
        m_parent.m_shipSocket->setDisplayName(id);
        m_parent.m_connectionStateHandler.setDisplayName(m_parent.m_displayName);
        m_parent.m_payloadDataExchangeEnabled = true;
    }
    else
    { // TODO if (!preliminary.equalsIgnoreCase(id)) {
        LOG_WARN() << m_parent.m_displayName << " Id mismatch! Expected " << preliminary.c_str() << ", received "
                   << id.c_str() << ". Closing connection!";
        m_parent.m_shipSocket->close(CLOSE_STATUS_CODE_ID_MISMATCH, "SHIP id mismatch");
    }

    if (m_parent.m_payloadDataExchangeEnabled)
    {
        // switch to data exchange enabled
        sendDataExchangeEnable();

        std::lock_guard<std::recursive_mutex> locker(m_parent.m_messageListMutex);
        while (!m_parent.m_messageList.empty())
        {
            std::vector<char> message = *(m_parent.m_messageList.begin());
            m_parent.sendDataExchangeMessage(message);
            m_parent.m_messageList.erase(m_parent.m_messageList.begin());
        }
    }
}

void ShipMessageExchange::ConnectionStateListener::sendDataExchangeEnable()
{
    SendDataExchangeEnableExecutor* job = new SendDataExchangeEnableExecutor(m_parent);

    if (0 != m_parent.jobRunner->addJob(job))
    {
        delete job;
        LOG_FATAL() << m_parent.m_displayName << ": Cannot add job at sendDataExchangeEnable()";
        //exit(EXIT_FAILURE);
    }
}

} /* namespace keo_ship */
