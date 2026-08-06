/*****************************************************************************
    Copyright (C) Kellendonk Elektronik GmbH, GERMANY 2012
*****************************************************************************/

#define DBG_MODUL_NAME "KELogger Test"
#include <gtest/gtest.h>

// project includes
#include <keo_util/KELogger.h>

using namespace keo_util;

void logSomething(std::string const& s)
{
    KELogger l;
    l << s;
}

// #2097
TEST(KELogger, LoggingSomethingThatIsAPrintfFormatStringDoesNotCrash)
{
    logSomething("%n");
    logSomething("%1$s");
    SUCCEED();
}
