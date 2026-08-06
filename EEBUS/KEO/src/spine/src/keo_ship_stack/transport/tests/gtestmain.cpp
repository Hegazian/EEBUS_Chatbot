#include "gtest/gtest.h"

#include <keo_util/KELogging.h>
INITIALIZE_KELOGGING

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();

    return ret;
}
