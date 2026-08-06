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

#include "ExampleClientApplication.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

#include <keo_util/KELogging.h>
#include <keo_util/KEVersion.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <atomic>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

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

using namespace keo_util;
using namespace keo_spine_example_client;

/** @ingroup framework_example_client
 * @{
 */

static std::atomic_bool shutdown(false);

void signal_handler(int signum)
{
    (void)signum;
    shutdown = true;
}

int main(int argc, char** argv)
{
    DEBUG_FUNC();

    (void)argc;
    (void)argv;

    std::cout << "KEO framework example client" << std::endl;
    std::cout << "Versions: " << std::endl;
    std::cout << keo_util::KEVersion(" - Framework: #version - #postfix").getModuleVersionInfo("framework") << std::endl;
    std::cout << keo_util::KEVersion(" - Spine:     #version - #postfix").getModuleVersionInfo("spine") << std::endl;

    signal(SIGQUIT, signal_handler);
    signal(SIGINT, signal_handler);

    KELogger::loadConfig("logging_client.conf");

    ExampleClientApplication example;
    if (example.start("client.cfg"))
    {
        while (!shutdown)
        {
            pause();
        }

        LOG_INFO() << "Shutting down example client ...";
        example.stop();
    }
    else
    {
        LOG_ERROR() << "Cannot start example client";
    }

    return 0;
}

/** @} */ //  end of group framework_example_client
