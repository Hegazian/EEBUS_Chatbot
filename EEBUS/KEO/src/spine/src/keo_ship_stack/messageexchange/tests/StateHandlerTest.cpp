/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2014
*****************************************************************************/

#define DBG_MODUL_NAME "StateHandler Test"
#include <gtest/gtest.h>
// ASSERT_TRUE
// ASSERT_EQ

#include "StateHandler.h"
#include "StateInfo.h"
#include <keo_util/KELogging.h>

using namespace keo_ship;
static char const* const mapSubstate[] = {
#define MACRO_CMI_STATE(x, y) #x,
#define MACRO_SME_STATE_HELLO(x, y) #x,
#define MACRO_SME_PROT_H_STATE(x, y) #x,
#define MACRO_SME_PIN_STATE(x, y) #x,
#define MACRO_ACCESS_METHODS(x, y) #x,
#define MACRO_STATE_CONNECTION_TERMINATION(x, y) #x,

#include "SmeConnectionState.h"

#undef MACRO_CMI_STATE
#undef MACRO_SME_STATE_HELLO
#undef MACRO_SME_PROT_H_STATE
#undef MACRO_SME_PIN_STATE
#undef MACRO_ACCESS_METHODS
#undef MACRO_STATE_CONNECTION_TERMINATION
};

char const* getSmeSubstateStr(keo_ship::SmeConnectionState state)
{
    keo_ship::SmeConnectionState stateSme = (keo_ship::SmeConnectionState)(state & 0xFF);
    if (stateSme < keo_ship::SME_SUBSTATE_LAST)
    {
        return (mapSubstate[stateSme]);
    }
    return ("undefined");
}

static char const* const mapSmeState[] = {
#define MACRO_STATE_OVERVIEW(x) #x,
#include "SmeConnectionStateOverview.h"
#undef MACRO_STATE_OVERVIEW
};

char const* getSmeStateStr(keo_ship::SmeConnectionState sme_state)
{
    SmeConnectionStateOverview overwiev = (SmeConnectionStateOverview)(sme_state >> SME_STATUS_TYPE_SHIFT);
    // assert((sizeof(mapSmeState) / sizeof(mapSmeState[0])) == keo_ship::SME_STATE_LAST);
    if (overwiev < keo_ship::SME_STATE_OVERVIEW_LAST)
    {
        return (mapSmeState[overwiev]);
    }
    return ("undefined");
}

TEST(StateHandlerTest, forClientsTheStateIsInitializedAccordingly)
{
    keo_ship::StateInfo stateInfo;
    stateInfo.setClient(true);

    ActionState state = keo_ship::StateHandler::initState(&stateInfo);
    ASSERT_EQ(state, ActionState::ACTION_CLIENT_SEND_CMI_MESSAGE_AND_START_CMI_TIMER);
    ASSERT_EQ(stateInfo.getState(), SmeConnectionState::CMI_STATE_CLIENT_SEND);
}

TEST(StateHandlerTest, forNonClientsTheStateIsInitializedAccordingly)
{
    keo_ship::StateInfo stateInfo;
    stateInfo.setClient(false);

    ActionState state = keo_ship::StateHandler::initState(&stateInfo);
    ASSERT_EQ(state, ActionState::ACTION_SERVER_START_CMI_TIMER);
    ASSERT_EQ(stateInfo.getState(), SmeConnectionState::CMI_INIT_STATE);
}

TEST(StateHandlerTest, testStates)
{
    {
        SmeConnectionState state = CMI_STATE_CLIENT_WAIT;
        SmeConnectionStateOverview overview = (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
        ASSERT_EQ(overview, STATE_OVERVIEW_CONNECTION_MODE_INITIALISATION);
    }
    {
        SmeConnectionState state = SME_HELLO_STATE_PENDING_INIT;
        SmeConnectionStateOverview overview = (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
        ASSERT_EQ(overview, STATE_OVERVIEW_CONNECTION_STATE_HELLO);
    }
    {
        SmeConnectionState state = SME_PROT_H_STATE_SERVER_OK;
        SmeConnectionStateOverview overview = (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
        ASSERT_EQ(overview, STATE_OVERVIEW_CONNECTION_STATE_PROTOCOL_HANDSHAKE);
    }
    {
        SmeConnectionState state = SME_PIN_STATE_CHECK_BUSY_WAIT;
        SmeConnectionStateOverview overview = (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
        ASSERT_EQ(overview, STATE_OVERVIEW_CONNECTION_PIN_VERIFICATION);
    }
    {
        SmeConnectionState state = STATE_ACCESS_METHODS;
        SmeConnectionStateOverview overview = (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
        ASSERT_EQ(overview, STATE_OVERVIEW_ACCESS_METHODS);
    }
    {
        SmeConnectionState state = STATE_ANNOUNCE_CLOSE_CONNECTION;
        SmeConnectionStateOverview overview = (SmeConnectionStateOverview)(state >> SME_STATUS_TYPE_SHIFT);
        ASSERT_EQ(overview, STATE_OVERVIEW_CLOSE_CONNECTION);
    }
}
TEST(StateHandlerTest, printTest)
{
    SmeConnectionState state = CMI_INIT_STATE;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = CMI_STATE_CLIENT_WAIT;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = CMI_STATE_CLIENT_SEND;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = CMI_STATE_CLIENT_EVALUATE;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = CMI_STATE_SERVER_WAIT;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = CMI_STATE_SERVER_EVALUATE;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = SME_PIN_STATE_ASK_PROCESS;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
    state = SME_PIN_STATE_CHECK_LISTEN;
    LOG_INFO() << "' in state '" << getSmeStateStr(state) << "' substate '" << getSmeSubstateStr(state);
}
