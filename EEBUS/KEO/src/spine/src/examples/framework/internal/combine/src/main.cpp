/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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

#include "SpineShipApplication.h"
#include <ArgParserStl.h>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <keo_util/KELogging.h>
#include <keo_util/KEVersion.h>
#include <random>
#include <signal.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include <keo_tool/KEFootprint.h>
#include <sstream>

template <typename T> std::string to_string(const T& value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

INITIALIZE_KELOGGING

using namespace keo_tool;
using namespace keo_util;
using namespace keo_spine_combine_app;

/** @ingroup framework_example_client
 * @{
 */

// global application running flag
bool gRunning = false;

/**
 * Show usage information, then exit
 * @param usageStr the string to print
 */
void usage(std::string const& usageStr)
{
    std::cerr << usageStr;
    exit(-1);
}

/*
 * Signal handler for CTRL-C and CTRL+\
 */
void signal_handler(int signum)
{
    (void)signum;
    static bool aborting = false;
    if (!aborting)
    {
        aborting = true;
        gRunning = false;
    }
}

void setParameters(ArgParserStl& parser)
{
    // feed arguments to argument parser

    struct TParameters
    {
        std::string const shortName;
        std::string const longName;
        std::string const help;
        const ArgParserStl::ArgType type;
        std::vector<std::string> const andRelation;
        std::vector<std::string> const xorRelation;
    };

    const TParameters params[] = {
        { std::string(), "--version", "Prints Version information and exits.", ArgParserStl::FLAG, {}, {} },
        { std::string(), "--spineid", "SPINE: Sets the SPINE Id. If not set, an unique Id will be generated.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--prefix", "SPINE: Sets prefix of the SPINE Id.", ArgParserStl::OPTIONAL, {},
            { "--spineid" } },
        { std::string(), "--shipid", "SHIP: Sets the SHIP Id. If not set, an unique Id will be generated.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--port", "SHIP: Sets the SHIP Server port number. If not set, an random number will be used.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--brand", "SHIP: Sets the optional brand of the device announced by the service.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--model", "SHIP: Sets the optional model of the device announced by the service.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--type",
            "SHIP: Sets the optional type (e.g. washer, dryer, ...) of the device announced by the service.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--instance", "SHIP: Sets the service instance (e.g. \"Dishwasher Bosch 498 SMI69T45EU\").",
            ArgParserStl::OPTIONAL, {}, {} },
        { "-o", "--override", "Override Certificate, Keyfile and Truststore.", ArgParserStl::FLAG, { "--spineid" },
            {} },
        { "-i", "--ignore", "SHIP: Ignore peer register flag.", ArgParserStl::FLAG, {}, {} },
        { "-n", "--no-server", "SHIP: No SHIP server. Incoming connections are not possible.", ArgParserStl::FLAG, {},
            {} },
        { "-p", "--publish", "SHIP: Publish the SHIP service via mDNS.", ArgParserStl::FLAG, {}, {} },
        { "-r", "--register", "SHIP: Sets the register flag to true.", ArgParserStl::FLAG, {}, {} },
        { "-s", "--server",
            "SPINE: Start a SPINE Measurement Server device. Default is a SPINE Measurement Client device.",
            ArgParserStl::FLAG, {}, {} },
        { std::string(), "--modify", "SPINE: Appends to the given timeout (in seconds) an entity to the device.",
            ArgParserStl::OPTIONAL, {}, {} },
        { std::string(), "--disconnect",
            "SHIP: Disconnects the connections at the given timeout and starts the reconnection.",
            ArgParserStl::OPTIONAL, {}, {} },
        { "-C", "--clean-up", "Remove certificate, key and trust store file on exit.", ArgParserStl::FLAG, {}, {} },
        { std::string(), "--log-config", "Filename for a logger configuration file.", ArgParserStl::OPTIONAL, {}, {} },
    };

    for (unsigned int i = 0; i < sizeof(params) / sizeof(*params); i++)
    {
        parser.addArgument(params[i].shortName, params[i].longName, params[i].help, params[i].type,
            params[i].andRelation, params[i].xorRelation);
    }

    parser.setHelpProlog("Some optional arguments are mandatory for the very first start.\n"
                         "As soon as they exist in the configuration file they can be omitted.\n");
}

void setApplicationParameter(SpineShipApplication* app, const std::string& shipId, ArgParserStl& parser)
{
    if (parser.isDefined("--instance"))
    {
        app->setShipDiscoveryInstanceLabel(parser.getValue("--instance"));
    }
    else
    {
        app->setShipDiscoveryInstanceLabel(shipId);
    }

    if (parser.isDefined("--port"))
    {
        app->setShipPort(::atoi(parser.getValue("--port").c_str()));
    }

    if (parser.isDefined("--model"))
    {
        app->setShipDiscoveryModel(parser.getValue("--model"));
    }

    if (parser.isDefined("--brand"))
    {
        app->setShipDiscoveryType(parser.getValue("--brand"));
    }

    if (parser.isDefined("--type"))
    {
        app->setShipDiscoveryBrand(parser.getValue("--type"));
    }

    if (parser.isDefined("-r"))
    {
        app->setShipDiscoveryRegisterFlag(true);
    }
    else
    {
        app->setShipDiscoveryRegisterFlag(false);
    }

    if (parser.isDefined("-p"))
    {
        app->setPublishShipService(true);
    }
    else
    {
        app->setPublishShipService(false);
    }

    if (parser.isDefined("-i"))
    {
        app->setShipDiscoveryIgnoreRegisterFlag(true);
    }
    else
    {
        app->setShipDiscoveryIgnoreRegisterFlag(false);
    }

    if (parser.isDefined("-n"))
    {
        app->setStartShipServer(false);
    }
    else
    {
        app->setStartShipServer(true);
    }

    if (parser.isDefined("-s"))
    {
        app->setSpineMeasurementServer(true);
    }
    else
    {
        app->setSpineMeasurementServer(false);
    }

    if (parser.isDefined("--modify"))
    {
        app->setDDModification(::atoi(parser.getValue("--modify").c_str()));
    }

    if (parser.isDefined("--disconnect"))
    {
        app->setDisconnectTimeout(::atoi(parser.getValue("--disconnect").c_str()));
    }
}

bool createKey(const std::string& prefix, const std::string& curve)
{
    if (!::system(0))
    {
        return false;
    }

    std::string subj = "\"/C=DE/ST=NRW/O=KEO/localityName=Cologne/organizationalUnitName=Development\"";

    std::string tmp = "openssl ecparam -out " + prefix + "params.pem -name " + curve + " -genkey";
    if (0 != ::system(tmp.c_str()))
    {
        return false;
    }
    tmp = "openssl req -new -batch -subj " + subj + " -x509 -newkey ec:" + prefix + "params.pem -keyform PEM -keyout "
        + prefix + "Key.pem -out " + prefix + "Cert.pem -outform PEM -days 3650 -set_serial 1234 -nodes";
    if (0 != ::system(tmp.c_str()))
    {
        return false;
    }
    tmp = "openssl x509 -in " + prefix + "Cert.pem -inform PEM -out " + prefix + "CertDER.bin -outform DER";
    if (0 != ::system(tmp.c_str()))
    {
        return false;
    }
    tmp = "openssl ec -in " + prefix + "Key.pem -outform DER -out " + prefix + "KeyDER.bin";
    if (0 != ::system(tmp.c_str()))
    {
        return false;
    }
    tmp = "rm -f " + prefix + "params.pem " + prefix + "Key.pem " + prefix + "Cert.pem";
    if (0 != ::system(tmp.c_str()))
    {
        return false;
    }
    return true;
}

inline bool fileExists(const std::string& name)
{
    struct stat buffer;
    return (::stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char** argv)
{
    DEBUG_FUNC();

    (void)argc;
    (void)argv;

    std::cout << "KEO framework application" << std::endl;

    signal(SIGQUIT, signal_handler);
    signal(SIGINT, signal_handler);

    ArgParserStl parser;
    setParameters(parser);

    std::string outputStr;
    std::string usageStr;
    bool showUsage = !parser.parse(argc, argv, outputStr);

    if (parser.isDefined("--version"))
    {
        keo_util::KEVersion versionInfo("  - #module-#version #hash (#tag)\n");
        std::cout << "Version Information:\n\n" << versionInfo.getVersionInfo() << std::endl;
        ::exit(0);
    }

    if (showUsage)
    {
        usage(outputStr);
    }

    std::string logConfigFileName;
    if (parser.isDefined("--log-config"))
    {
        logConfigFileName = parser.getValue("--log-config");
        std::cout << "Using log configuration file '" << logConfigFileName << "'" << std::endl;
    }

    std::string shipId;
    std::string spineId;
    int pid = ::getpid();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1024, 65535);

    std::string curve = "prime256v1";
    std::string prefix = "SpineApplication_" + to_string(pid) + "_" + to_string(dis(gen));

    if (parser.isDefined("--spineid"))
    {
        spineId = parser.getValue("--spineid");
        prefix = spineId;
        if (parser.isDefined("-o"))
        {
            ::remove(std::string(prefix + "CertDER.bin").c_str());
            ::remove(std::string(prefix + "KeyDER.bin").c_str());
            ::remove(std::string(prefix + "Truststore.json").c_str());
            if (!createKey(prefix, curve))
            {
                std::cout << "Cannot create Key/Certificate file!" << std::endl;
                ::exit(1);
            }
        }
        else
        {
            if (!fileExists(prefix + "CertDER.bin") && fileExists(prefix + "KeyDER.bin"))
            {
                std::cout << "Cannot find certification file!" << std::endl;
                ::exit(1);
            }
            else if (!fileExists(prefix + "KeyDER.bin") && fileExists(prefix + "CertDER.bin"))
            {
                std::cout << "Cannot find key file!" << std::endl;
                ::exit(1);
            }
            else if (!fileExists(prefix + "KeyDER.bin") && !fileExists(prefix + "CertDER.bin"))
            {
                if (!createKey(prefix, curve))
                {
                    std::cout << "Cannot create Key/Certificate file!" << std::endl;
                    ::exit(1);
                }
            }
        }
    }
    else if (parser.isDefined("--prefix"))
    {
        prefix = parser.getValue("--prefix") + "_" + to_string(pid);
        if (!createKey(prefix, curve))
        {
            std::cout << "Cannot create Key/Certificate file!" << std::endl;
            ::exit(1);
        }
        spineId = prefix;
    }
    else
    {
        if (!createKey(prefix, curve))
        {
            std::cout << "Cannot create Key/Certificate file!" << std::endl;
            ::exit(1);
        }
        spineId = "d:_i:47859_KEO-" + prefix;
    }

    if (parser.isDefined("--shipid"))
    {
        shipId = parser.getValue("--shipid");
    }
    else
    {
        shipId = prefix;
    }

    KELogger::loadConfig(logConfigFileName);

    SpineShipApplication* app = new SpineShipApplication();

    app->setSpineDeviceName(spineId);
    app->setShipId(shipId);

    setApplicationParameter(app, shipId, parser);

    if (app->start(prefix + "CertDER.bin", prefix + "KeyDER.bin", prefix + "Truststore.json"))
    {
        // do nothing special, just wait for termination
        gRunning = true;
        while (gRunning)
            ::pause();

        std::cout << std::endl << "Shutting-down application ..." << std::endl;
        app->stop();

        KEFootprint footprint;
        LOG_INFO() << footprint.getload();
    }
    else
    {
        LOG_ERROR() << "Cannot start application";
    }

    // cleanup
    delete app;

    if (parser.isDefined("--clean-up"))
    {
        ::remove(std::string(prefix + "CertDER.bin").c_str());
        ::remove(std::string(prefix + "KeyDER.bin").c_str());
        ::remove(std::string(prefix + "Truststore.json").c_str());
    }

    return 0;
}

/** @} */ //  end of group framework_example_client
