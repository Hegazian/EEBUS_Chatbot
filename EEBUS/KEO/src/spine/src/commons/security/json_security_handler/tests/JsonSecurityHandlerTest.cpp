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
#include <keo_json_security_handler/JsonSecurityHandler.h>

#include "KEByteArray.h"

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */
#include <gtest/gtest.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <cstdio>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
class JsonSecurityHandlerTest : public ::testing::Test
{
protected:
    keo_json_security_handler::JsonSecurityHandler handler;
};

TEST_F(JsonSecurityHandlerTest, InitFailsIfBothFilesDoNotExist)
{
    bool success = handler.init(std::string(TC_SAMPLES_DIR) + "keys/nosuchkey.bin",
        std::string(TC_SAMPLES_DIR) + "keys/nosuchcert.bin", std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_FALSE(success);
}

TEST_F(JsonSecurityHandlerTest, InitFailsIfCertFileDoesNotExist)
{
    bool success = handler.init(std::string(TC_SAMPLES_DIR) + "keys/nosuchcert.bin",
        std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1KeyDER.bin",
        std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_FALSE(success);
}

TEST_F(JsonSecurityHandlerTest, InitFailsIfKeyFileDoesNotExist)
{
    bool success = handler.init(std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1CertDER.bin",
        std::string(TC_SAMPLES_DIR) + "keys/nosuchkey.bin", std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_FALSE(success);
}

TEST_F(JsonSecurityHandlerTest, InitSucceedsIfTrustStoreFileDoesNotExist)
{
    // (the trust store file will be created)
    bool success = handler.init(std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1CertDER.bin",
        std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1KeyDER.bin",
        std::string(TC_SAMPLES_DIR) + "no_such_trust_store.json");
    EXPECT_TRUE(success);

    // delete the file
    std::remove((std::string(TC_SAMPLES_DIR) + "no_such_trust_store.json").c_str());
}

TEST_F(JsonSecurityHandlerTest, InitSucceedsIfAllFilesExist)
{
    bool success = handler.init(std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1CertDER.bin",
        std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1KeyDER.bin",
        std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_TRUE(success);
}

TEST_F(JsonSecurityHandlerTest, SKIIsRetrievedCorrectly)
{
    handler.init(std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1CertDER.bin",
        std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1KeyDER.bin",
        std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");

    std::string expectedSKI = "c90b2c2c08630e217d5df673302df97e1fe4f7a3";
    EXPECT_EQ(expectedSKI, handler.getOwnSKI());
    // ToDo Adapt test to new SKI class as soon as it has moved to keo_trustcenter
}

TEST_F(JsonSecurityHandlerTest, ShipIDIsEmptyIfNodeIsUnknown)
{
    handler.init(std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1CertDER.bin",
        std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1KeyDER.bin",
        std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");

    std::vector<unsigned char> certVector = KEByteArray::fromHex("abcdef").toVectorUnsigned();
    keo_ship::X509Certificate cert(certVector);
    std::string id = handler.getId(cert);
    EXPECT_EQ("", id);
}

TEST_F(JsonSecurityHandlerTest, ShipIDIsCorrectIfNodeIsKnown)
{
    handler.init(std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1CertDER.bin",
        std::string(TC_SAMPLES_DIR) + "keys/skiTest_secp256r1KeyDER.bin",
        std::string(TC_SAMPLES_DIR) + "filled_trust_entries_with_cert.json");

    std::vector<unsigned char> certVector = KEByteArray::fromHex("ffee003acdaa").toVectorUnsigned();
    keo_ship::X509Certificate cert(certVector);
    std::string id = handler.getId(cert);
    EXPECT_EQ("TestGateway", id);
}
