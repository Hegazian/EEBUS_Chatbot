/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <gtest/gtest.h>
#include <iostream>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <core/src/KeoJsonTransformation.h>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

using namespace keo_datagram;

Json::Value strToJson(std::string const& str)
{
    Json::CharReaderBuilder builder;
    Json::Value json;
    std::string parserErrors;
    std::istringstream ss(str);
    Json::parseFromStream(builder, ss, &json, &parserErrors);
    return json;
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess1)
{
    auto json = strToJson(R"([{ "a": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess2)
{
    auto json = strToJson(R"([{ "b": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess3)
{
    auto json = strToJson(R"([{ "c": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess4)
{
    auto json = strToJson(R"([{ "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess5)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess6)
{
    auto json = strToJson(R"([{ "a": 0 }, { "c": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess7)
{
    auto json = strToJson(R"([{ "a": 0 }, { "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess8)
{
    auto json = strToJson(R"([{ "b": 0 }, { "c": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess9)
{
    auto json = strToJson(R"([{ "b": 0 }, { "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess10)
{
    auto json = strToJson(R"([{ "c": 0 }, { "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess11)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }, { "c": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess12)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }, { "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess13)
{
    auto json = strToJson(R"([{ "a": 0 }, { "c": 0 }, { "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess14)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }, { "c": 0 }, { "d": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess15)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }, { "x": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderSuccess16)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }, { "x": 0 }, { "y": 0 }])");
    ASSERT_TRUE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail)
{
    auto json = strToJson(R"([{ "b": 0 }, { "a": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail1)
{
    auto json = strToJson(R"([{ "c": 0 }, { "a": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail2)
{
    auto json = strToJson(R"([{ "c": 0 }, { "b": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail3)
{
    auto json = strToJson(R"([{ "d": 0 }, { "a": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail4)
{
    auto json = strToJson(R"([{ "d": 0 }, { "b": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail5)
{
    auto json = strToJson(R"([{ "d": 0 }, { "c": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail6)
{
    auto json = strToJson(R"([{ "b": 0 }, { "a": 0 }, { "c": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail7)
{
    auto json = strToJson(R"([{ "b": 0 }, { "c": 0 }, { "a": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail8)
{
    auto json = strToJson(R"([{ "b": 0 }, { "d": 0 }, { "a": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail9)
{
    auto json = strToJson(R"([{ "a": 0 }, { "b": 0 }, { "d": 0 }, { "c": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail10)
{
    auto json = strToJson(R"([{ "a": 0 }, { "c": 0 }, { "b": 0 }, { "d": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail11)
{
    auto json = strToJson(R"([{ "a": 0 }, { "c": 0 }, { "d": 0 }, { "b": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail12)
{
    auto json = strToJson(R"([{ "d": 0 }, { "a": 0 }, { "b": 0 }, { "c": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail13)
{
    auto json = strToJson(R"([{ "d": 0 }, { "b": 0 }, { "a": 0 }, { "c": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail14)
{
    auto json = strToJson(R"([{ "d": 0 }, { "c": 0 }, { "a": 0 }, { "b": 0 }])");
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c", "d" }));
}

TEST(KeoJsonTransformationTests, testHasCorrectOrderFail15)
{
    auto json = strToJson(R"([{ "d": 0 }, { "x": 0 }, { "b": 0 }])"); // no additional fields in between
    ASSERT_FALSE(KeoJsonTransformation::hasCorrectOrder(&json, { "a", "b", "c" }));
}
