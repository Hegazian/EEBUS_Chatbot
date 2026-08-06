#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>

#include "KEOZeroconf.h"

#include <keo_util/KELogging.h>
INITIALIZE_KELOGGING

#ifndef WS_PROTOCOL
#define WS_PROTOCOL "shiptest"
#endif

using namespace std;

class myCallbackIf : public KEOZeroconfCallbackIf
{
public:
    myCallbackIf()
    {
    }
    virtual void browseService(bool bSuccess, const KEOZeroconfService& service);
};

void myCallbackIf::browseService(bool bSuccess, const KEOZeroconfService& service)
{
    cout << endl << "CALLBACK\t" << __FUNCTION__;
    cout << "\tbSuccess  " << bSuccess << endl;
    if (!service.mDomain.empty())
        cout << "\tmDomain   " << service.mDomain << endl;

    if (!service.mHost.empty())
        cout << "\tmHost     " << service.mHost << endl;

    if (!service.mName.empty())
        cout << "\tmName     " << service.mName << endl;

    if (service.mPort)
        cout << "\tmPort     " << dec << service.mPort << endl;

    cout << "\tmRemoved  " << service.mRemoved << endl;

    if (service.mTxt.size() > 0)
    {
        cout << "\tmTxt" << endl;
        for (list<pair<string, string> >::const_iterator it = service.mTxt.begin(); it != service.mTxt.end(); ++it)
        {
            cout << "\t\t" << it->first << " = " << it->second << endl;
        }
    }
}

int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;

    keo_util::KELogger::setDefaultLevel(keo_util::KELogger::Level::WARNING);

    const string serviceType = string("_") + string(WS_PROTOCOL) + string("._tcp");
    cout << "Browsing for service type '" + serviceType + "'" << endl;

    KEOZeroconfCallbackIf* ci = new myCallbackIf();
    KEOZeroconf* zc = new KEOZeroconf(serviceType, ci);

    if (!zc->init())
    {
        LOG_ERROR() << "Error while initiliazing Zeroconf implementation";
    }
    zc->browseServices();

    while (1)
    {
        sleep(100 * 1000);
    }

    return EXIT_SUCCESS;
}
