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

#ifndef KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_SHIPMESSAGEEXCHANGE_H_
#define KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_SHIPMESSAGEEXCHANGE_H_

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include "ConnectionStateHandlerListener.h"
#include "internal/ConnectionStateHandler.h"
#include <ShipSocket.h>
#include <ShipTimer.h>
#include <keo_ship/ShipSecurity.h>
#include <keo_ship/ShipStack.h>

#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <atomic>
#include <list>
#include <mutex>
#include <stddef.h>
#include <vector>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */
namespace keo_tool
{
class KEJobRunner;
}

namespace keo_ship
{

class ShipMessageExchangeConnectionConfirmedListener;
class ShipSocketConnection;

class ShipMessageExchange : public keo_ship::ShipSocketMessageListener
{
public:
    explicit ShipMessageExchange(ShipMessageExchangeListener* listener);

    virtual ~ShipMessageExchange();

    void onFinalize();

    void onConnect(ShipMessageExchangeConnectionConfirmedListener* confirmedListener, ShipSocket* shipSocket,
        SecurityHandlerPtr securityHandler, const ShipStackConfiguration& shipStackConfiguration,
        const std::string& serverUri);

    void setUserTrust(short userTrust);

    std::string getId() const;

    PinRequirement getPinRequirement() const;

    std::string getSki() const;

    std::string getIpAddress() const;

    int getIpPort() const;

    TrustLevel getTrustLevel() const;

    bool getIsClient() const;

    /**
     * Send SHIP message to core.
     *
     * @param message
     *            SHIP message
     * @return True if successful sent to core
     */
    bool sendMessage(const std::vector<char>& payload);

    void close(int statusCode, const std::string& reason);

    void closeIn(int maxTimeMilliSeconds, bool isRemovedConnection);

    void closeInConfirm();

    void onShipMessage(const std::vector<char>& message);

    void setPin(const std::string& pin);

    void setPinPenaltyTime(long penaltyTime);

protected:
    void closeInTimeout();

    // Listener for datagrams
    class ConnectionStateListener : public ConnectionStateHandlerListener
    {
    public:
        ConnectionStateListener(ShipMessageExchange& parent);

        bool sendToShipTransport(const std::vector<char>& message) override;

        void announceEvent(keo_ship::NodeEvent event, const std::string& data) override;

        void closeConnection(int statusCode, const std::string& reason) override;

    private:
        void handleEventReceivedId();
        void doPinVerification(const std::string& pin);
        void sendDataExchangeEnable();

        ShipMessageExchange& m_parent;
    };

private:
    void doCertificateVerification();
    void shipMessage(const std::vector<char>& data);
    void handleCmiData(const std::vector<char>& data);
    bool sendToPeer(const std::vector<char>& message);
    void sendDataExchangeMessage(const std::vector<char>& message);
    void setUserTrust(unsigned short userTrust);

private:
    class CertificateResultProcessor;
    class PinVerificationResultProcessor;
    class DataMessageExecutor;
    class SendDataExchangeEnableExecutor;

private:
    static const int CLOSE_STATUS_CODE_ID_MISMATCH;
    static const int CLOSE_STATUS_CODE_CONNECTION_CLOSE_TIMEOUT;
    static const int CLOSE_STATUS_CODE_USER_UNTRUSTED;

    ConnectionStateListener m_connectionStateListener;
    ConnectionStateHandler m_connectionStateHandler;

    ShipMessageExchangeListener* m_messageExchangeListener;
    ShipMessageExchangeConnectionConfirmedListener* m_confirmedListener;
    ShipSocket* m_shipSocket;
    SecurityHandlerPtr m_securityHandler;
    std::list<std::vector<char> > m_messageList;
    mutable std::recursive_mutex m_messageListMutex;
    mutable std::recursive_mutex m_mtx;

    bool m_shipDataExchangeEnabled;
    bool m_payloadDataExchangeEnabled;
    ShipTimer m_closeInTimer;
    std::string m_closeReason;
    std::string m_displayName;
    std::string m_remoteSKI;

    keo_tool::KEJobRunner* jobRunner;
    std::atomic_bool m_closed;
};

} /* namespace keo_ship */

#endif /* KEO_SHIP_STACK_MESSAGEEXCHANGE_SRC_SHIPMESSAGEEXCHANGE_H_ */
