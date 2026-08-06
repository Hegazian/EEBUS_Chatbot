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

#include "ConnectionStateHandlerExtend.h"

using namespace keo_ship;

ConnectionStateHandlerExtend::ConnectionStateHandlerExtend(const std::string& id, const NodeInfo& nodeInfo,
    bool isClient, ConnectionStateHandlerListener* actionModuleListener, const std::string& serverUri)
    : ConnectionStateHandler(id, nodeInfo, isClient, actionModuleListener, serverUri)
{
}
NodeInfo* ConnectionStateHandlerExtend::getNodeInfo()
{
    return &m_nodeInfo;
}
void ConnectionStateHandlerExtend::setNodeInfo(const NodeInfo& nodeInfo)
{
    m_nodeInfo = nodeInfo;
}
StateInfo* ConnectionStateHandlerExtend::getStateInfo()
{
    return &m_stateInfo;
}
void ConnectionStateHandlerExtend::setStateInfo(const StateInfo& stateInfo)
{
    m_stateInfo = stateInfo;
}
void ConnectionStateHandlerExtend::startTimer()
{
    ConnectionStateHandler::startTimer();
}
