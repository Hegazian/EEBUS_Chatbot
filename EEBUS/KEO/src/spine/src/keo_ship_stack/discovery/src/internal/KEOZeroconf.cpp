
#include <assert.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <mutex>
#include <net/if.h>
#include <netdb.h>
#include <stdio.h>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_util/KELogging.h>

#include "KEOZeroconf.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

KEOZeroconf::KEOZeroconf(
    const std::string& serviceType, KEOZeroconfCallbackIf* callbackIf, KEOZeroconfService::ProtocolType protocolType)
    : mServiceType(serviceType)
    , mCallbackIf(callbackIf)
    , mAvahiProtocol(mapProtocolType(protocolType))
    , mMutex()
    , mBrowseCalled(false)
    , mRegisterActive(false)
    , mThreadedPollActive(false)
    , mUnregisterService(false)
    , mAvahiThreadedPoll(NULL)
    , mAvahiClient(NULL)
    , mAvahiEntryGroup(NULL)
    , mAvahiServiceBrowser(NULL)
{
}

KEOZeroconf::~KEOZeroconf()
{
    if (NULL != mAvahiThreadedPoll)
    {
        avahi_threaded_poll_stop(mAvahiThreadedPoll);
    }

    if (NULL != mAvahiClient)
    {
        avahi_client_free(mAvahiClient);
    }

    if (NULL != mAvahiThreadedPoll)
    {
        avahi_threaded_poll_free(mAvahiThreadedPoll);
    }
}

bool KEOZeroconf::init()
{
    DEBUG_FUNC();

    bool bSuccess = true;

    if (NULL == mAvahiThreadedPoll)
    {
        mAvahiThreadedPoll = avahi_threaded_poll_new();
        if (NULL == mAvahiThreadedPoll)
        {
            LOG_ERROR() << "Error while initializing avahi threaded poll";
            bSuccess = false;
        }
    }

    if (bSuccess)
    {
        avahi_threaded_poll_lock(mAvahiThreadedPoll);
        if (NULL == mAvahiClient)
        {
            int error = 0;
            mAvahiClient = avahi_client_new(
                avahi_threaded_poll_get(mAvahiThreadedPoll), AVAHI_CLIENT_NO_FAIL, avahiClientCallback, this, &error);
            if (NULL == mAvahiClient)
            {
                LOG_ERROR() << "Error while initializing avahi client: " << avahi_strerror(error);
                bSuccess = false;
            }
        }
        avahi_threaded_poll_unlock(mAvahiThreadedPoll);
    }

    DEBUG_INFO() << __PRETTY_FUNCTION__ << ": " << bSuccess;
    return bSuccess;
}

bool KEOZeroconf::browseServices(bool bNeedsLocking)
{
    DEBUG_FUNC();

    bool bSuccess = true;

    std::string host;

    if (mService.mHost.size() > 0)
    {
        host = mService.mHost;
    }

    if (mBrowseCalled)
    {
        bSuccess = false;
    }

    if (bSuccess)
    {
        mBrowseCalled = true;

        if (bNeedsLocking)
        {
            avahi_threaded_poll_lock(mAvahiThreadedPoll);
        }
        if (NULL == mAvahiServiceBrowser && mAvahiClient != NULL
            && avahi_client_get_state(mAvahiClient) == AVAHI_CLIENT_S_RUNNING)
        {
            AvahiIfIndex ifIndex = getIfIndexFromAddress(host);
            mAvahiServiceBrowser = avahi_service_browser_new(mAvahiClient, ifIndex, mAvahiProtocol,
                mServiceType.c_str(), NULL, (AvahiLookupFlags)0, avahiBrowseCallback, this);
            if (mAvahiServiceBrowser == NULL)
            {
                LOG_ERROR() << "avahi_service_browser_new failed: " << avahi_strerror(avahi_client_errno(mAvahiClient));
                LOG_ERROR() << "mServiceType : " << mServiceType;
                bSuccess = false;
            }
        }
        if (bNeedsLocking)
        {
            avahi_threaded_poll_unlock(mAvahiThreadedPoll);
        }
    }

    DEBUG_INFO() << __PRETTY_FUNCTION__ << ": " << bSuccess;
    return bSuccess;
}

void KEOZeroconf::stopBrowseServices()
{
    DEBUG_FUNC();

    if (mBrowseCalled)
    {
        avahi_threaded_poll_lock(mAvahiThreadedPoll);
        if (NULL != mAvahiServiceBrowser)
        {

            avahi_service_browser_free(mAvahiServiceBrowser);
            mAvahiServiceBrowser = NULL;
        }
        deleteResolvers();
        avahi_threaded_poll_unlock(mAvahiThreadedPoll);

        mBrowseCalled = false;
    }
}

bool KEOZeroconf::registerService(const KEOZeroconfService& service, bool bUnregister, bool bNeedsLocking)
{
    DEBUG_FUNC();

    bool bSuccess = false;

    assert(mAvahiThreadedPoll);
    assert(mAvahiClient);

    mService = service;
    mService.mRemoved = false;
    mUnregisterService = bUnregister;

    /* If the server is currently running, we need to remove our
     * service and create it anew */
    if (bNeedsLocking)
    {
        avahi_threaded_poll_lock(mAvahiThreadedPoll);
    }
    AvahiClientState clientState = avahi_client_get_state(mAvahiClient);
    if (bNeedsLocking)
    {
        avahi_threaded_poll_unlock(mAvahiThreadedPoll);
    }

    if (AVAHI_CLIENT_S_RUNNING == clientState)
    {
        bSuccess = true;
        /* Remove the old service (if existing)*/
        if (bNeedsLocking)
        {
            avahi_threaded_poll_lock(mAvahiThreadedPoll);
        }
        if (NULL != mAvahiEntryGroup)
        {
            if (0 == avahi_entry_group_is_empty(mAvahiEntryGroup))
            {
                bSuccess = avahi_entry_group_reset(mAvahiEntryGroup) >= 0;

                if (bSuccess)
                {
                    mRegisterActive = false;
                }
                assert(bSuccess);
            }
        }
        if (bNeedsLocking)
        {
            avahi_threaded_poll_unlock(mAvahiThreadedPoll);
        }

        /* And create it again with the new name if not unregistering */
        if (bSuccess && !bUnregister)
        {
            if (bNeedsLocking)
            {
                avahi_threaded_poll_lock(mAvahiThreadedPoll);
            }
            bSuccess = createService(mAvahiClient, this);
            if (bNeedsLocking)
            {
                avahi_threaded_poll_unlock(mAvahiThreadedPoll);
            }
            if (bSuccess)
            {
                mRegisterActive = true;
            }
            assert(bSuccess);
        }
    }

    DEBUG_INFO() << __PRETTY_FUNCTION__ << ": " << bSuccess;

    return bSuccess;
}

bool KEOZeroconf::updateServiceTxtRecord(const KEOZeroconfService& service)
{
    DEBUG_FUNC();

    bool bSuccess = false;

    mService = service;
    AvahiStringList* txt = NULL;

    if (NULL != mAvahiClient)
    {
        for (auto reverseIt = service.mTxt.rbegin(); reverseIt != service.mTxt.rend(); ++reverseIt)
        {
            txt = avahi_string_list_add_pair(
                txt, reverseIt->first.c_str(), (reverseIt->second.length() > 0) ? reverseIt->second.c_str() : NULL);
        }
        avahi_threaded_poll_lock(mAvahiThreadedPoll);
        int ret = avahi_entry_group_update_service_txt_strlst(mAvahiEntryGroup, AVAHI_IF_UNSPEC, mAvahiProtocol,
            (AvahiPublishFlags)0, service.mName.c_str(), mServiceType.c_str(), service.mDomain.c_str(), txt);
        avahi_threaded_poll_unlock(mAvahiThreadedPoll);
        bSuccess = (AVAHI_OK == ret);
        avahi_string_list_free(txt);
    }

    DEBUG_INFO() << __PRETTY_FUNCTION__ << ": " << bSuccess;
    return bSuccess;
}

std::list<KEOZeroconfService> KEOZeroconf::getBrowsedServices() const
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mMutex);

    return mBrowsedServices;
}

KEOZeroconfService::ProtocolType KEOZeroconf::mapProtocolType(AvahiProtocol protocolType)
{
    DEBUG_FUNC();

    switch (protocolType)
    {
        case AVAHI_PROTO_INET:
            return KEOZeroconfService::PROTOCOL_IPV4;

        case AVAHI_PROTO_INET6:
            return KEOZeroconfService::PROTOCOL_IPV6;

        default:
            return KEOZeroconfService::PROTOCOL_UNSPEC;
    }
}

AvahiProtocol KEOZeroconf::mapProtocolType(KEOZeroconfService::ProtocolType protocolType)
{
    DEBUG_FUNC();

    switch (protocolType)
    {
        case KEOZeroconfService::PROTOCOL_IPV4:
            return AVAHI_PROTO_INET;

        case KEOZeroconfService::PROTOCOL_IPV6:
            return AVAHI_PROTO_INET6;

        default:
            return AVAHI_PROTO_UNSPEC;
    }
}

bool KEOZeroconf::createService(AvahiClient* c, void* userdata)
{
    DEBUG_FUNC();

    KEOZeroconf* pThis = static_cast<KEOZeroconf*>(userdata);
    std::lock_guard<std::recursive_mutex> locker(pThis->mMutex);

    std::string domain;
    std::string host;
    bool bSuccess = true;

    assert(c == pThis->mAvahiClient);
    DEBUG_INFO() << "mAvahiClient: " << pThis->mAvahiClient;

    DEBUG_INFO() << "mAvahiEntryGroup:" << mAvahiEntryGroup;
    if (NULL == pThis->mAvahiEntryGroup)
    {

        pThis->mAvahiEntryGroup = avahi_entry_group_new(c, avahiEntryGroupCallback, userdata);
        assert(NULL != pThis->mAvahiEntryGroup);

        if (NULL == pThis->mAvahiEntryGroup)
        {
            LOG_ERROR() << "avahi_entry_group_new failed: " << avahi_strerror(avahi_client_errno(c));
            bSuccess = false;
            assert(bSuccess);
        }
    }
    DEBUG_INFO() << "mAvahiEntryGroup:" << mAvahiEntryGroup;

    if (bSuccess)
    {
        if (mService.mDomain.size() > 0)
        {
            domain = mService.mDomain;
        }

        if (mService.mHost.size() > 0)
        {
            host = mService.mHost;
        }

        AvahiStringList* txt = NULL;

        for (auto reverseIt = pThis->mService.mTxt.rbegin(); reverseIt != pThis->mService.mTxt.rend(); ++reverseIt)
        {
            txt = avahi_string_list_add_pair(
                txt, reverseIt->first.c_str(), (reverseIt->second.length() > 0) ? reverseIt->second.c_str() : NULL);
        }

        while (1)
        {
            AvahiIfIndex ifIndex = getIfIndexFromAddress(host);
            char ifName[100] = "";
            if_indextoname(ifIndex, ifName);
            DEBUG_INFO() << "Registering service on interface " << ifName;
            int ret
                = avahi_entry_group_add_service_strlst(mAvahiEntryGroup, ifIndex, mAvahiProtocol, (AvahiPublishFlags)0,
                    mService.mName.c_str(), mServiceType.c_str(), domain.c_str(), "", mService.mPort, txt);

            DEBUG_INFO() << "Result of service registration: " << ret;

            if (AVAHI_OK == ret)
            {
                break;
            }
            else if (AVAHI_ERR_COLLISION != ret)
            {
                bSuccess = false;
                break;
            }
            else
            {
                alternativeServiceName();
                LOG_INFO() << "AVAHI_ERR_COLLISION, renaming service to: " << mService.mName;
            }
        }

        avahi_string_list_free(txt);
    }

    if (bSuccess)
    {
        int ret = avahi_entry_group_commit(mAvahiEntryGroup);
        if (AVAHI_OK != ret)
        {
            assert(bSuccess);
            bSuccess = false;
        }
    }

    DEBUG_INFO() << __PRETTY_FUNCTION__ << ": " << bSuccess;
    return bSuccess;
}

void KEOZeroconf::alternativeServiceName()
{
    DEBUG_FUNC();

    char* newName = NULL;
    newName = avahi_alternative_service_name(mService.mName.c_str());
    assert(newName != NULL);
    mService.mName = newName;
    avahi_free(newName);
}

void KEOZeroconf::deleteResolvers()
{
    DEBUG_FUNC();

    for (auto resolverIt = mResolverList.begin(); resolverIt != mResolverList.end(); resolverIt++)
    {
        avahi_service_resolver_free(*resolverIt);
    }
    mResolverList.clear();
}

/* CALLBACKS */
void KEOZeroconf::browseServicesCallback(bool bSuccess, const std::list<KEOZeroconfService>& services)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mMutex);

    if (bSuccess)
    {
        for (auto servicesIt = services.begin(); servicesIt != services.end(); ++servicesIt)
        {
            bool bServiceFound = false;

            for (auto browsedServicesIt = mBrowsedServices.begin(); browsedServicesIt != mBrowsedServices.end();
                 ++browsedServicesIt)
            {
                if (browsedServicesIt->isEqualHeader(*servicesIt))
                {
                    bServiceFound = true;

                    if (browsedServicesIt->mInterfaceId == servicesIt->mInterfaceId)
                    {
                        if ((*servicesIt).mRemoved
                            && (browsedServicesIt->mProtocolType == servicesIt->mProtocolType
                                   || KEOZeroconfService::PROTOCOL_UNSPEC == servicesIt->mProtocolType))
                        {
                            browsedServicesIt->mRemoved = true;
                            mCallbackIf->browseService(bSuccess, *browsedServicesIt);
                            mBrowsedServices.remove(*browsedServicesIt);
                            break;
                        }
                        else if (!(*servicesIt).mRemoved && !browsedServicesIt->isEqualContent(*servicesIt))
                        {
                            browsedServicesIt->copyContent(*servicesIt);
                            mCallbackIf->browseService(bSuccess, *browsedServicesIt);
                            break;
                        }
                    }
                }
            }
            if (!bServiceFound && !servicesIt->mRemoved)
            {
                mBrowsedServices.push_front(*servicesIt);
                mCallbackIf->browseService(bSuccess, *servicesIt);
            }
        }
    }
    else
    {
        for (auto servicesIt = services.begin(); servicesIt != services.end(); ++servicesIt)
        {
            mCallbackIf->browseService(bSuccess, *servicesIt);
        }
    }
}

void KEOZeroconf::registerServiceCallback(bool bSuccess, const KEOZeroconfService& service)
{
    DEBUG_FUNC();
    std::lock_guard<std::recursive_mutex> locker(mMutex);

    if (bSuccess)
    {
        mRegisteredServices.push_back(service);
        mRegisteredServices.unique();
    }
    mCallbackIf->registerService(bSuccess, service);
}

void KEOZeroconf::avahiClientCallback(AvahiClient* c, AvahiClientState state, void* userdata)
{
    DEBUG_FUNC();

    assert(NULL != c);
    assert(NULL != userdata);

    KEOZeroconf* pThis = static_cast<KEOZeroconf*>(userdata);

    switch (state)
    {
        case AVAHI_CLIENT_S_RUNNING:
            if (!pThis->mThreadedPollActive)
            {
                if (avahi_threaded_poll_start(pThis->mAvahiThreadedPoll) < 0)
                {
                    LOG_ERROR() << "Error while starting avahi threaded poll";
                    return;
                }
                else
                {
                    pThis->mThreadedPollActive = true;
                }
            }

            if (pThis->mBrowseCalled)
            {
                pThis->browseServices(false);
            }
            if (pThis->mRegisterActive)
            {
                pThis->registerService(pThis->mService, pThis->mUnregisterService, false);
            }
            /* The server has startup successfully and registered its host
             * name on the network */
            DEBUG_INFO() << "AVAHI_CLIENT_S_RUNNING";
            break;

        case AVAHI_CLIENT_FAILURE:
            LOG_ERROR() << "AVAHI_CLIENT_FAILURE: " << avahi_strerror(avahi_client_errno(c));
            break;

        case AVAHI_CLIENT_S_COLLISION:
            /* Let's drop our registered services. When the server is back
             * in AVAHI_SERVER_RUNNING state we will register them
             * again with the new host name. */
            DEBUG_INFO() << "AVAHI_CLIENT_S_COLLISION";
        // fall through
        // no break
        case AVAHI_CLIENT_S_REGISTERING:
            /* The server records are now being established. This
             * might be caused by a host name change. We need to wait
             * for our own records to register until the host name is
             * properly established. */
            DEBUG_INFO() << "AVAHI_CLIENT_S_REGISTERING";
            if (pThis->mAvahiEntryGroup != NULL)
            {
                avahi_entry_group_reset(pThis->mAvahiEntryGroup);
            }
            break;

        case AVAHI_CLIENT_CONNECTING:
            DEBUG_INFO() << "AVAHI_CLIENT_CONNECTING";
            break;
    }
}

void KEOZeroconf::avahiEntryGroupCallback(AvahiEntryGroup* g, AvahiEntryGroupState state, void* userdata)
{
    DEBUG_FUNC();

    assert(NULL != userdata);

    KEOZeroconf* pThis = static_cast<KEOZeroconf*>(userdata);

    assert(g == pThis->mAvahiEntryGroup || NULL == pThis->mAvahiEntryGroup);
    pThis->mAvahiEntryGroup = g;

    switch (state)
    {
        case AVAHI_ENTRY_GROUP_UNCOMMITED:
            DEBUG_INFO() << "AVAHI_ENTRY_GROUP_UNCOMMITED";
            if (pThis->mUnregisterService)
            {
                pThis->mService.mRemoved = true;
                pThis->registerServiceCallback(true, pThis->mService);
                pThis->mService.mRemoved = false;
            }
            break;

        case AVAHI_ENTRY_GROUP_REGISTERING:
            DEBUG_INFO() << "AVAHI_ENTRY_GROUP_REGISTERING";
            break;

        case AVAHI_ENTRY_GROUP_ESTABLISHED:
            DEBUG_INFO() << "AVAHI_ENTRY_GROUP_ESTABLISHED";
            pThis->mService.mHost = avahi_client_get_host_name_fqdn(pThis->mAvahiClient);
            pThis->registerServiceCallback(true, pThis->mService);
            break;

        case AVAHI_ENTRY_GROUP_COLLISION:
            pThis->alternativeServiceName();
            LOG_INFO() << "AVAHI_ENTRY_GROUP_COLLISION, renaming service to: " << pThis->mService.mName;
            pThis->createService(pThis->mAvahiClient, userdata);
            break;

        case AVAHI_ENTRY_GROUP_FAILURE:
            LOG_ERROR() << "AVAHI_ENTRY_GROUP_FAILURE";
            pThis->mService.mRemoved = true;
            pThis->registerServiceCallback(false, pThis->mService);
            pThis->mService.mRemoved = false;
            break;
    }
}

void KEOZeroconf::avahiBrowseCallback(AvahiServiceBrowser* b, AvahiIfIndex interface, AvahiProtocol protocol,
    AvahiBrowserEvent event, const char* name, const char* type, const char* domain, AvahiLookupResultFlags flags,
    void* userdata)
{
    DEBUG_FUNC();

    assert(NULL != userdata);

    KEOZeroconf* pThis = static_cast<KEOZeroconf*>(userdata);

    assert(b == pThis->mAvahiServiceBrowser);

    KEOZeroconfService service;

    switch (event)
    {
        case AVAHI_BROWSER_FAILURE:
        {
            LOG_ERROR() << "AVAHI_BROWSER_FAILURE: "
                        << avahi_strerror(avahi_client_errno(avahi_service_browser_get_client(b)));
        }
        break;

        case AVAHI_BROWSER_NEW:
        {
            DEBUG_INFO() << "AVAHI_BROWSER_NEW";

            assert(name);
            assert(type);
            assert(domain);

            AvahiServiceResolver* resolver = avahi_service_resolver_new(pThis->mAvahiClient, interface, protocol, name,
                type, domain, pThis->mAvahiProtocol, (AvahiLookupFlags)0, avahiResolveCallback, userdata);

            if (NULL == resolver)
            {
                LOG_ERROR() << "avahi_service_resolver_new failed: "
                            << avahi_strerror(avahi_client_errno(pThis->mAvahiClient));
            }
            else
            {
                pThis->mResolverList.push_back(resolver);
            }
        }
        break;

        case AVAHI_BROWSER_REMOVE:
        {
            DEBUG_INFO() << "AVAHI_BROWSER_REMOVE";

            service.mName = name;
            service.mDomain = domain;
            service.mRemoved = true;
            service.mInterfaceId = interface;
            service.mProtocolType = pThis->mapProtocolType(protocol);
            pThis->browseServicesCallback(true, std::list<KEOZeroconfService>(1, service));
        }
        break;

        case AVAHI_BROWSER_ALL_FOR_NOW:
        {
            DEBUG_INFO() << "AVAHI_BROWSER_ALL_FOR_NOW";
        }
        break;

        case AVAHI_BROWSER_CACHE_EXHAUSTED:
        {
            DEBUG_INFO() << "AVAHI_BROWSER_CACHE_EXHAUSTED";
        }
        break;
    }

    (void)flags;
}

void KEOZeroconf::avahiResolveCallback(AvahiServiceResolver* r, AvahiIfIndex interface, AvahiProtocol protocol,
    AvahiResolverEvent event, const char* name, const char* type, const char* domain, const char* host_name,
    const AvahiAddress* address, uint16_t port, AvahiStringList* txt, AvahiLookupResultFlags flags, void* userdata)
{
    DEBUG_FUNC();

    assert(NULL != r);

    KEOZeroconf* pThis = static_cast<KEOZeroconf*>(userdata);
    std::lock_guard<std::recursive_mutex> locker(pThis->mMutex);

    KEOZeroconfService service;
    service.mName = name;
    service.mDomain = domain;
    service.mPort = port;
    service.mRemoved = false;
    service.mInterfaceId = (int)interface;
    service.mProtocolType = pThis->mapProtocolType(protocol);
    service.mOwnService = (flags & AVAHI_LOOKUP_RESULT_OUR_OWN) ? true : false;
    service.mTxt.clear();

    switch (event)
    {
        case AVAHI_RESOLVER_FAILURE:
        {
            DEBUG_INFO() << "AVAHI_RESOLVER_FAILURE: " << avahi_strerror(avahi_client_errno(pThis->mAvahiClient));
            avahi_service_resolver_free(r);
            pThis->mResolverList.remove(r);
            break;
        }
        case AVAHI_RESOLVER_FOUND:
        {
            DEBUG_INFO() << "AVAHI_RESOLVER_FOUND";

            assert(NULL != name);
            assert(NULL != type);
            assert(NULL != domain);

            char a[AVAHI_ADDRESS_STR_MAX];
            avahi_address_snprint(a, sizeof(a), address);
            service.mAddress = a;
            service.mHost = host_name;

            char* t = avahi_string_list_to_string(txt);
            avahi_free(t);

            int txtLen = avahi_string_list_length(txt);

            for (int i = 0; i < txtLen; i++)
            {
                char* key = NULL;
                char* value = NULL;

                avahi_string_list_get_pair(txt, &key, &value, NULL);
                service.mTxt.push_front(
                    std::pair<std::string, std::string>(key, (value != NULL) ? value : std::string()));

                if (NULL != key)
                {
                    avahi_free(key);
                }

                if (NULL != value)
                {
                    avahi_free(value);
                }

                if (i < txtLen - 1)
                {
                    txt = avahi_string_list_get_next(txt);
                }
            }

            pThis->browseServicesCallback(true, std::list<KEOZeroconfService>(1, service));
            break;
        }
    }

    (void)type;
    (void)host_name;
}

AvahiIfIndex KEOZeroconf::getIfIndexFromAddress(const std::string& address)
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    char host[NI_MAXHOST];
    AvahiIfIndex interfaceIndex = -1;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return -1;
    }

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++)
    {
        if (ifa->ifa_addr == NULL)
        {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET || family == AF_INET6)
        {
            s = getnameinfo(ifa->ifa_addr,
                (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL,
                0, NI_NUMERICHOST);
            if (s == 0 && host == address)
            {
                interfaceIndex = if_nametoindex(ifa->ifa_name);
                break;
            }
        }
    }
    freeifaddrs(ifaddr);
    return interfaceIndex;
}
