/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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

#include "ConnectionStateHandlerListenerImpl.h"
#include "ShipControlTransformer.h"
#include "ShipMessageType.h"
#include "keo_ship/ShipHeader.h"

using namespace keo_ship;

ConnectionStateHandlerListenerImpl::ConnectionStateHandlerListenerImpl()
{
}
bool ConnectionStateHandlerListenerImpl::sendToShipTransport(const std::vector<char>& message)
{
    if (message.size() > 0)
    {
        ShipMessageType state = static_cast<ShipMessageType>(message[0]);
        switch (state)
        {
            case MESSAGE_TYPE_INIT:
            {
                m_sentData.push_back(message);
                return true;
            }
            case MESSAGE_TYPE_CONTROL:
            case MESSAGE_TYPE_END:
            {
                CShipDataClass* pDataClass = ShipControlTransformer::createDataClassFromCommissioningMessage(message);
                if (pDataClass)
                {
                    switch (pDataClass->getDataType())
                    {
                        case CONNECTION_HELLO_TYPE:
                        {
                            keo_ship::ConnectionHello* hello = static_cast<ConnectionHello*>(pDataClass);
                            m_sentClasses.push_back(hello);
                            break;
                        }
                        case MESSAGE_PROTOCOL_HANDSHAKE_TYPE:
                        {
                            MessageProtocolHandshake* messageHand = static_cast<MessageProtocolHandshake*>(pDataClass);
                            m_sentClasses.push_back(messageHand);
                            break;
                        }
                        case CONNECTION_PIN_STATE_TYPE:
                        {
                            ConnectionPinState* pin = static_cast<ConnectionPinState*>(pDataClass);
                            m_sentClasses.push_back(pin);
                            break;
                        }
                        case CONNECTION_PIN_INPUT_TYPE:
                        {
                            ConnectionPinInput* pin = static_cast<ConnectionPinInput*>(pDataClass);
                            m_sentClasses.push_back(pin);
                            break;
                        }
                        case ACCESS_METHODS_REQUEST_TYPE:
                        {
                            AccessMethodsRequest* accessRequest = static_cast<AccessMethodsRequest*>(pDataClass);
                            m_sentClasses.push_back(accessRequest);
                            break;
                        }
                        case ACCESS_METHODS_TYPE:
                        {
                            AccessMethods* access = static_cast<AccessMethods*>(pDataClass);
                            m_sentClasses.push_back(access);
                            break;
                        }
                        case CONNECTION_CLOSE_TYPE:
                        {
                            ConnectionClose* closeMessage = static_cast<ConnectionClose*>(pDataClass);
                            m_sentClasses.push_back(closeMessage);
                            break;
                        }
                        default:
                        {
                        }
                    }
                    return true;
                }
                break;
            }
            case MESSAGE_TYPE_DATA:
            {
                // todo
            }
            break;
            case MESSGAE_TYPE_RFU:
            {
                // todo
            }
            break;
        }
    }
    return false;
}
void ConnectionStateHandlerListenerImpl::announceEvent(keo_ship::NodeEvent event, const std::string& data)
{
    (void)data;
    m_sentEvent.push_back(event);
}
void ConnectionStateHandlerListenerImpl::closeConnection(int statusCode, const std::string& reason)
{
    (void)statusCode;
    (void)reason;
    // empty
}
std::vector<CShipDataClass*> ConnectionStateHandlerListenerImpl::getSentClasses()
{
    return m_sentClasses;
}
std::vector<std::vector<char> > ConnectionStateHandlerListenerImpl::getSentData()
{
    return m_sentData;
}
std::vector<NodeEvent> ConnectionStateHandlerListenerImpl::getSentEvent()
{
    return m_sentEvent;
}
void ConnectionStateHandlerListenerImpl::clear()
{
    std::vector<CShipDataClass*>::iterator iter = m_sentClasses.begin();
    std::vector<CShipDataClass*>::iterator iterEnd = m_sentClasses.end();
    for (; iter != iterEnd; ++iter)
    {
        delete *iter;
    }
    m_sentClasses.clear();
    m_sentData.clear();
    m_sentEvent.clear();
}
