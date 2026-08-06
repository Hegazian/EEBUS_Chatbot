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
/**
 *     @brief      Module for handling the state sequence action.
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_CONNECTION_STATE_HANDLER_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_CONNECTION_STATE_HANDLER_H_

/** @addtogroup keo_ship_stack
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <string>
#include <vector>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ActionState.h"
#include "ConnectionStateHandlerListener.h"
#include "NodeEvent.h"
#include "NodeInfo.h"
#include "ShipMessageType.h"
#include "ShipTimer.h"
#include "SmeConnectionState.h"
#include "StateInfo.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */
namespace keo_ship
{
class CShipDataClass;
}
// forward declaration of the base class for state dependent ConnectionStateHandler handler
class EventActionBase;

namespace keo_ship
{
class ActionModuleStateBase;

/**
 * Handling of connection states
 */
class ConnectionStateHandler
{
private:
    static char const CMI_MESSAGE_DATA_VALUE;
    static uint16_t const CLOSE_STATUS_CODE;
    static uint8_t const PIN_NO_PENALTY;
    static uint8_t const PIN_SHORT_PENALTY;
    static size_t const PIN_NEEDED_LENGTH;
    static size_t const COMMISSIONING_TIMER_INTERVAL;

public:
    explicit ConnectionStateHandler(ConnectionStateHandlerListener* actionModuleListener);

    ~ConnectionStateHandler();

    void setDisplayName(const std::string& displayName);

    void start(const std::string& id, const NodeInfo& nodeInfo, bool isClient, const std::string& serverUri);

    const NodeInfo& getNodeProtocolInfoReference() const;

    void setUserTrust(unsigned short userTrust);

    void setSecondFactorTrust(unsigned short pinTrustLevel);

    void setPin(const std::string& pin);

    void setPinPenaltyTime(long penaltyTime);

    void closeAnnounce(int maxTimeMilliSeconds, keo_ship::ConnectionCloseReason reason);

    void closeAnnounceConfirm();

    void receiveCMIInitMessage(const std::vector<char>& data);

    void receiveCMIControlMessage(keo_ship::CShipDataClass* pDataClass);

    void receiveEndMessage(keo_ship::CShipDataClass* pDataClass);

    void setProtocolConfig(const ProtocolConfig& protocolConfig);

    const ProtocolConfig getProtocolConfig();

protected:
    // Only used for testing
    ConnectionStateHandler(const std::string& id, const NodeInfo& nodeInfo, bool isClient,
        ConnectionStateHandlerListener* actionModuleListener, const std::string& serverUri);

    void start();

    /**
     * Execute an action
     * An action is one step defined in the SHIP exchange message protocol
     * @param action Action to execute
     */
    void doAction(ActionState action);

    void startTimer();

private:
    void handleTimer();
    void stopTimerIfPossible();
    bool cmiToShipTransport(const std::vector<char>& cmiMessage);
    bool toShipTransport(ShipMessageType cmiState, keo_ship::CShipDataClass* shipData);
    static uint32_t timerElapsedAfterUpdate(uint32_t timer, uint32_t elapsedTicks);
    /**
      * Checks if this PIN is a valid PIN according to the SHIP v1.0.0
      * specification.
      *
      * @param pin
      *            the PIN to check
      * @return true, if the PIN is valid
      */
    static bool isPinFormatValid(const std::string& pin);

protected:
    NodeInfo m_nodeInfo;

    StateInfo m_stateInfo;

private:
    // Action module user.
    ConnectionStateHandlerListener* m_actionModuleListener;

    std::string m_id;

    ShipTimer m_timeoutTimer;
    long int m_lastTime;

    mutable std::recursive_mutex m_mtx;

    std::string m_displayName;

    std::string m_serverUri;

    ProtocolConfig m_protocolConfig;
};
}
/** @}
 * end of file
 */

#endif /* KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_INTERNAL_CONNECTION_STATE_HANDLER_H_ */
