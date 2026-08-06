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

#include "ExampleServerApplication.h"

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

using namespace keo_util;
using namespace keo_spine_example_server;

INITIALIZE_KELOGGING

/** @ingroup framework_example_server
 * @{
 */

static std::atomic_bool shutdown(false);

void signal_handler(int)
{
    shutdown = true;
}

int main(int, char**)
{
    DEBUG_FUNC();

    std::cout << "KEO framework example server" << std::endl;
    std::cout << "Versions: " << std::endl;
    std::cout << keo_util::KEVersion(" - Framework: #version - #postfix").getModuleVersionInfo("framework") << std::endl;
    std::cout << keo_util::KEVersion(" - Spine:     #version - #postfix").getModuleVersionInfo("spine") << std::endl;

    signal(SIGQUIT, signal_handler);
    signal(SIGINT, signal_handler);

    KELogger::loadConfig("logging_server.conf");

    ExampleServerApplication example;
    if (example.start("server.cfg"))
    {
        while (!shutdown)
        {
            pause();
        }

        LOG_INFO() << "Shutting down example server ...";
        example.close();
    }
    else
    {
        LOG_ERROR() << "Cannot start example server";
    }

    return 0;
}
/** @} */ //  end of group framework_example_server
