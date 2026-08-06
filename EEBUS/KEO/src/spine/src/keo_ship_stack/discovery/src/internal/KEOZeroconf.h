
#ifndef KEO_ZEROCONF_INCLUDE_KEOZEROCONF_H_
#define KEO_ZEROCONF_INCLUDE_KEOZEROCONF_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <list>
#include <mutex>
#include <string>

#include <avahi-client/lookup.h>
#include <avahi-client/publish.h>
#include <avahi-common/alternative.h>
#include <avahi-common/error.h>
#include <avahi-common/malloc.h>
#include <avahi-common/thread-watch.h>
#include <avahi-common/timeval.h>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "KEOZeroconfCallbackIf.h"
#include "KEOZeroconfService.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

class KEOZeroconf
{
public:
    KEOZeroconf(const std::string& serviceType, KEOZeroconfCallbackIf* callbackIf,
        KEOZeroconfService::ProtocolType protocolType = KEOZeroconfService::PROTOCOL_UNSPEC);
    virtual ~KEOZeroconf();

    bool init();
    bool browseServices(bool bNeedsLocking = true);
    void stopBrowseServices();
    bool registerService(const KEOZeroconfService& service, bool bUnregister = false, bool bNeedsLocking = true);
    bool updateServiceTxtRecord(const KEOZeroconfService& service);
    std::list<KEOZeroconfService> getBrowsedServices() const;

    void browseServicesCallback(bool bSuccess, const std::list<KEOZeroconfService>& services);
    void registerServiceCallback(bool bSuccess, const KEOZeroconfService& service);

private:
    KEOZeroconfService::ProtocolType mapProtocolType(AvahiProtocol protocolType);
    AvahiProtocol mapProtocolType(KEOZeroconfService::ProtocolType protocolType);
    bool createService(AvahiClient* c, void* userdata);
    void alternativeServiceName();
    void deleteResolvers();

    static void avahiClientCallback(AvahiClient* c, AvahiClientState state, void* userdata);
    static void avahiEntryGroupCallback(AvahiEntryGroup* g, AvahiEntryGroupState state, void* userdata);
    static void avahiBrowseCallback(AvahiServiceBrowser* b, AvahiIfIndex interface, AvahiProtocol protocol,
        AvahiBrowserEvent event, const char* name, const char* type, const char* domain, AvahiLookupResultFlags flags,
        void* userdata);
    static void avahiResolveCallback(AvahiServiceResolver* r, AvahiIfIndex interface, AvahiProtocol protocol,
        AvahiResolverEvent event, const char* name, const char* type, const char* domain, const char* host_name,
        const AvahiAddress* address, uint16_t port, AvahiStringList* txt, AvahiLookupResultFlags flags, void* userdata);

    AvahiIfIndex getIfIndexFromAddress(const std::string& address);

    std::string mServiceType;
    KEOZeroconfCallbackIf* mCallbackIf;
    AvahiProtocol mAvahiProtocol;

    mutable std::recursive_mutex mMutex;

    bool mBrowseCalled;
    bool mRegisterActive;
    bool mThreadedPollActive;

    KEOZeroconfService mService;
    bool mUnregisterService;
    std::list<AvahiServiceResolver*> mResolverList;

    AvahiThreadedPoll* mAvahiThreadedPoll;
    AvahiClient* mAvahiClient;
    AvahiEntryGroup* mAvahiEntryGroup;
    AvahiServiceBrowser* mAvahiServiceBrowser;

    std::list<KEOZeroconfService> mBrowsedServices;
    std::list<KEOZeroconfService> mRegisteredServices;
};

/** @}
 * end of file
 */

#endif /* KEO_ZEROCONF_INCLUDE_KEOZEROCONF_H_ */
