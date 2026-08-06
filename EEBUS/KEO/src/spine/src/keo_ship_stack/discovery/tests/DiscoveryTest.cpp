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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_ship_discovery/ShipDiscovery.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include <keo_util/KELogging.h>

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */
#include "gtest/gtest.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <mutex>
#include <unistd.h>
/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */
#define GLOBALTIMEOUT 5

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using namespace keo_ship_discovery;

static std::mutex gMutex;

static bool gServiceAddedCalled;
static bool gCopyServiceAdded;
static ShipService gServiceAdded;

static bool gServiceRemovedCalled;
static bool gCopyServiceRemoved;
static ShipService gServiceRemoved;

static bool gOwnServiceRegisteredCalled;
static bool gCopyOwnServiceRegistered;
static ShipService gOwnServiceRegistered;

static bool gOwnServiceRemovedCalled;
static bool gCopyOwnServiceRemoved;
static ShipService gOwnServiceRemoved;

void copyService(ShipService& globalVar, ShipService value)
{
    gMutex.lock();
    globalVar = value;
    gMutex.unlock();
}

ShipService getService(const ShipService& globalVar)
{
    ShipService ret;
    gMutex.lock();
    ret = globalVar;
    gMutex.unlock();
    return ret;
}

void clear(bool& globalVar)
{
    gMutex.lock();
    globalVar = false;
    gMutex.unlock();
}

void set(bool& globalVar)
{
    gMutex.lock();
    globalVar = true;
    gMutex.unlock();
}

bool get(bool& globalVar)
{
    bool ret;
    gMutex.lock();
    ret = globalVar;
    gMutex.unlock();
    return ret;
}

class ShipDiscoveryCallback : public ShipDiscoveryInterface
{
public:
    ShipDiscoveryCallback(){};

    virtual ~ShipDiscoveryCallback(){};

    virtual void onServiceAdded(const ShipService& service)
    {
        DEBUG_FUNC();
        LOG_INFO() << "ShipDiscoveryCallback serviceAdded";
        ShipDiscovery::logDiscoveredService(service);

        if (get(gCopyServiceAdded))
        {
            copyService(gServiceAdded, service);
            clear(gCopyServiceAdded);
        }
        set(gServiceAddedCalled);
    }

    virtual void onServiceRemoved(const ShipService& service)
    {
        DEBUG_FUNC();
        LOG_INFO() << "ShipDiscoveryCallback serviceRemoved";
        ShipDiscovery::logDiscoveredService(service);

        if (get(gCopyServiceRemoved))
        {
            copyService(gServiceRemoved, service);
            clear(gCopyServiceRemoved);
        }
        set(gServiceRemovedCalled);
    }

    virtual void onOwnServiceRegistered(const ShipService& service)
    {
        DEBUG_FUNC();
        LOG_INFO() << "ShipDiscoveryCallback ownServiceRegistered";
        ShipDiscovery::logDiscoveredService(service);

        if (get(gCopyOwnServiceRegistered))
        {
            copyService(gOwnServiceRegistered, service);
            clear(gCopyOwnServiceRegistered);
        }
        set(gOwnServiceRegisteredCalled);
    }

    virtual void onOwnServiceRemoved(const ShipService& service)
    {
        DEBUG_FUNC();
        LOG_INFO() << "ShipDiscoveryCallback ownServiceRemoved";
        ShipDiscovery::logDiscoveredService(service);

        if (get(gCopyOwnServiceRemoved))
        {
            copyService(gOwnServiceRemoved, service);
            clear(gCopyOwnServiceRemoved);
        }
        set(gOwnServiceRemovedCalled);
    }
};

class DiscoveryTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        gServiceAddedCalled = false;
        gCopyServiceAdded = false;

        gServiceRemovedCalled = false;
        gCopyServiceRemoved = false;

        gOwnServiceRegisteredCalled = false;
        gCopyOwnServiceRegistered = false;

        discoveryCallback = new ShipDiscoveryCallback();

        discoveryRegister = new ShipDiscovery("_shiptest._tcp", "local", discoveryCallback);
        discoveryBrowse = new ShipDiscovery("_shiptest._tcp", "local", discoveryCallback);
        identifier = "DiscoveryTest";
        wssPath = "/ship/";
        port = 4711;
        ski = "ffeeddccbbaa99887766554433221100badc0de1";
        brand = "brand";
        type = "type";
        model = "model";

        discoveryRegister->setTxtRecordBrand(brand);
        discoveryRegister->setTxtRecordType(type);
        discoveryRegister->setTxtRecordModel(model);
    }

    virtual void TearDown()
    {
        delete discoveryBrowse;
        delete discoveryRegister;
        delete discoveryCallback;
    }

    bool waitForHandler(bool& handlerCalled, unsigned int waitSeconds)
    {
        waitSeconds *= 10;
        while (0 != waitSeconds)
        {
            if (get(handlerCalled))
            {
                break;
            }
            usleep(100000); // 100ms
            waitSeconds--;
        }

        return get(handlerCalled);
    }

    ShipDiscoveryCallback* discoveryCallback;
    ShipDiscovery* discoveryRegister;
    ShipDiscovery* discoveryBrowse;

    std::string identifier;
    std::string wssPath;
    unsigned short port;
    std::string ski;
    std::string brand;
    std::string type;
    std::string model;
};

TEST(DiscoveredServiceTest, copyDiscoveredServiceByConstructor)
{
    ShipService serviceSrc;
    serviceSrc.setIdentifier("srcIdentifier");

    ShipService serviceCopy(serviceSrc);

    ASSERT_EQ(serviceSrc.getIdentifier(), "srcIdentifier");
    ASSERT_EQ(serviceCopy.getIdentifier(), "srcIdentifier");
    ASSERT_EQ(serviceCopy.getIdentifier(), serviceSrc.getIdentifier());

    serviceCopy.setIdentifier("copyIdentifier");
    ASSERT_EQ(serviceSrc.getIdentifier(), "srcIdentifier");
    ASSERT_EQ(serviceCopy.getIdentifier(), "copyIdentifier");
    ASSERT_NE(serviceCopy.getIdentifier(), serviceSrc.getIdentifier());
}

TEST(DiscoveredServiceTest, copyDiscoveredServiceByAssignment)
{
    ShipService serviceSrc;
    serviceSrc.setIdentifier("srcIdentifier");

    ShipService serviceCopy;
    serviceCopy = serviceSrc;

    ASSERT_EQ(serviceSrc.getIdentifier(), "srcIdentifier");
    ASSERT_EQ(serviceCopy.getIdentifier(), "srcIdentifier");
    ASSERT_EQ(serviceCopy.getIdentifier(), serviceSrc.getIdentifier());

    serviceCopy.setIdentifier("copyIdentifier");
    ASSERT_EQ(serviceSrc.getIdentifier(), "srcIdentifier");
    ASSERT_EQ(serviceCopy.getIdentifier(), "copyIdentifier");
    ASSERT_NE(serviceCopy.getIdentifier(), serviceSrc.getIdentifier());
}

TEST_F(DiscoveryTest, registerService)
{
    discoveryRegister->registerService(identifier, wssPath, ski, port);
    ASSERT_TRUE(waitForHandler(gOwnServiceRegisteredCalled, GLOBALTIMEOUT));
}

TEST_F(DiscoveryTest, unregisterService)
{
    discoveryBrowse->startServiceResolver();

    clear(gServiceAddedCalled);
    discoveryRegister->registerService(identifier, wssPath, ski, port);
    ASSERT_TRUE(waitForHandler(gServiceAddedCalled, GLOBALTIMEOUT));

    clear(gServiceRemovedCalled);
    clear(gOwnServiceRemovedCalled);
    discoveryRegister->unregisterService();
    ASSERT_TRUE(waitForHandler(gServiceRemovedCalled, GLOBALTIMEOUT));
    ASSERT_TRUE(waitForHandler(gOwnServiceRemovedCalled, GLOBALTIMEOUT));
}

TEST_F(DiscoveryTest, browseService)
{
    discoveryRegister->registerService(identifier, wssPath, ski, port);

    discoveryBrowse->startServiceResolver();
    ASSERT_TRUE(waitForHandler(gServiceAddedCalled, GLOBALTIMEOUT));
}

TEST_F(DiscoveryTest, changeRegisterFlagToFalse)
{
    discoveryBrowse->startServiceResolver();

    discoveryRegister->setTxtRecordRegister(true);
    ASSERT_TRUE(discoveryRegister->getTxtRecordRegister());

    clear(gServiceAddedCalled);
    set(gCopyServiceAdded);
    discoveryRegister->registerService(identifier, wssPath, ski, port);

    ASSERT_TRUE(waitForHandler(gServiceAddedCalled, GLOBALTIMEOUT));
    ShipDiscovery::logDiscoveredService(getService(gServiceAdded));
    ASSERT_TRUE(getService(gServiceAdded).isRegister());

    clear(gServiceAddedCalled);
    set(gCopyServiceAdded);
    discoveryRegister->setTxtRecordRegister(false);
    ASSERT_TRUE(waitForHandler(gServiceAddedCalled, GLOBALTIMEOUT));
    ShipDiscovery::logDiscoveredService(getService(gServiceAdded));
    ASSERT_FALSE(getService(gServiceAdded).isRegister());
}

TEST_F(DiscoveryTest, changeRegisterFlagToTrue)
{
    discoveryBrowse->startServiceResolver();

    discoveryRegister->setTxtRecordRegister(false);
    ASSERT_FALSE(discoveryRegister->getTxtRecordRegister());

    clear(gServiceAddedCalled);
    set(gCopyServiceAdded);
    discoveryRegister->registerService(identifier, wssPath, ski, port);

    ASSERT_TRUE(waitForHandler(gServiceAddedCalled, GLOBALTIMEOUT));
    ShipDiscovery::logDiscoveredService(getService(gServiceAdded));
    ASSERT_FALSE(getService(gServiceAdded).isRegister());

    clear(gServiceAddedCalled);
    set(gCopyServiceAdded);
    discoveryRegister->setTxtRecordRegister(true);

    ASSERT_TRUE(waitForHandler(gServiceAddedCalled, GLOBALTIMEOUT));
    ShipDiscovery::logDiscoveredService(getService(gServiceAdded));
    ASSERT_TRUE(getService(gServiceAdded).isRegister());
}
