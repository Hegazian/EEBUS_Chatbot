#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "KEOZeroconf.h"

#include <keo_util/KELogging.h>
INITIALIZE_KELOGGING

#ifndef WS_PROTOCOL
#define WS_PROTOCOL "shiptest"
#endif

using namespace std;

const int NUM_PUBLISHED_JOBS = 100;
const int RUNS = 10;
const bool bSameName = true;

class myCallbackIf : public KEOZeroconfCallbackIf
{
public:
    myCallbackIf()
    {
    }
    virtual void registerService(bool bSuccess, const KEOZeroconfService& service);
};

void myCallbackIf::registerService(bool bSuccess, const KEOZeroconfService& service)
{
    LOG_INFO() << "CALLBACK\t" << __FUNCTION__;
    LOG_INFO() << "\tbSuccess  " << bSuccess;
    LOG_INFO() << "\tmDomain   " << service.mDomain;
    LOG_INFO() << "\tmHost     " << service.mHost;
    LOG_INFO() << "\tmName     " << service.mName;
    LOG_INFO() << "\tmPort     " << dec << service.mPort;
    LOG_INFO() << "\tmRemoved  " << service.mRemoved;

    LOG_INFO() << "\tmTxt";
    for (list<pair<string, string> >::const_iterator it = service.mTxt.begin(); it != service.mTxt.end(); ++it)
    {
        LOG_INFO() << "\t\t" << it->first << " = " << it->second;
    }

    (void)bSuccess;
    (void)service;
}

void sleepProgress(const int seconds)
{
    for (int i = seconds * 10; i != 0; i--)
    {
        if ((10 == i) || (0 == i % 10))
        {
            LOG_INFO() << "Waiting for " << dec << i / 10 << " second" << ((i != 10) ? "s" : "") << "...";
        }
        usleep(100 * 1000);
    }
}

int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;

    keo_util::KELogger::setDefaultLevel(keo_util::KELogger::Level::WARNING);


    const string serviceType = string("_") + string(WS_PROTOCOL) + string("._tcp");
    const string name = "Dishwasher Bosch SMI69T45EU";
    const string domain = "";
    const string host = "";
    const unsigned int port = 51000;
    const bool bRemoved = false;

    list<pair<string, string> > txt;

    txt.push_back(pair<string, string>("txtvers", "1"));
    txt.push_back(pair<string, string>("id", "BSHG-SMI69T45EU-001122334455"));
    txt.push_back(pair<string, string>("path", "/ship/"));
    txt.push_back(pair<string, string>("register", "true"));

    txt.push_back(pair<string, string>("brand", "Bosch"));
    txt.push_back(pair<string, string>("type", "Dishwasher"));
    txt.push_back(pair<string, string>("model", "SMI69T45EU"));

    KEOZeroconfCallbackIf* ci = new myCallbackIf();
    KEOZeroconfService service(name, domain, host, port, txt, bRemoved);
    KEOZeroconf* zc[NUM_PUBLISHED_JOBS];

    const int runs = RUNS;

    int run = 0;
    do
    {
        for (int i = 0; i < NUM_PUBLISHED_JOBS; i++)
        {
            service.mPort++;
            if (!bSameName)
            {
                stringstream serviceName;
                serviceName << name << " " << dec << i;
                service.mName = serviceName.str();
            }

            LOG_INFO() << "Trying to register...";
            LOG_INFO() << "\tserviceType  " << serviceType;
            LOG_INFO() << "\tname         " << service.mName;
            LOG_INFO() << "\tdomain       " << service.mDomain;
            LOG_INFO() << "\thost         " << service.mHost;
            LOG_INFO() << "\tport         " << service.mPort;
            LOG_INFO() << "\tbRemoved     " << service.mRemoved;
            LOG_INFO() << "\ttxt" << endl;
            for (list<pair<string, string> >::const_iterator it = service.mTxt.begin(); it != service.mTxt.end(); ++it)
            {
                LOG_INFO() << "\t\t" << it->first << " = " << it->second;
            }

            // create objects
            zc[i] = new KEOZeroconf(serviceType, ci);

            // init objects
            if (!zc[i]->init())
            {
                LOG_ERROR() << "Error while initiliazing Zeroconf implementation: " << i;
            }

            // register
            zc[i]->registerService(service);
        }

        // wait 10s
        sleepProgress(10);

        // unregister
        for (int i = 0; i < NUM_PUBLISHED_JOBS; i++)
        {
            LOG_INFO() << "unregister...";
            zc[i]->registerService(service, true);
        }

        // wait 10s
        sleepProgress(10);

        service.mPort = port;
        for (int i = 0; i < NUM_PUBLISHED_JOBS; i++)
        {
            service.mPort++;
            if (!bSameName)
            {
                stringstream serviceName;
                serviceName << name << " " << dec << i;
                service.mName = serviceName.str();
            }

            LOG_INFO() << "re-register...";
            zc[i]->registerService(service);
        }

        // wait 10s
        sleepProgress(10);

        // destroy objects
        for (int i = 0; i < NUM_PUBLISHED_JOBS; i++)
        {
            LOG_INFO() << "destroying...";
            delete zc[i];
        }

        run++;
    } while (run < runs);

    delete ci;
    return EXIT_SUCCESS;
}
