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
#include <JsonTrustStore.h>
#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include "KEByteArray.h"

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */
#include <gtest/gtest.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <cstdio>
#include <fstream>
#include <string>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
// class TrustStoreTest : public ::testing::Test
//{
// protected:
//    example::TrustStore t;
//};

TEST(JsonTrustStoreTest, InitSucceedsIfFileDoesNotExistButCanBeCreated)
{
    std::string filename = std::string(TC_SAMPLES_DIR) + "nosuchfile";

    keo_json_security_handler::JsonTrustStore t(filename);
    EXPECT_TRUE(t.init());

    std::remove(filename.c_str());
}

TEST(JsonTrustStoreTest, InitFailsIfFileDoesNotExistAndCannotBeCreated)
{
    keo_json_security_handler::JsonTrustStore t("/no/such/file");
    EXPECT_FALSE(t.init());
}

TEST(JsonTrustStoreTest, InitFailsIfTruststoreFileIsEmpty)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "emptyfile");
    EXPECT_FALSE(t.init());
}

TEST(JsonTrustStoreTest, ReadSucceedsIfTruststoreContainsNothing)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_TRUE(t.init());
}

// Trustlevel tests
TEST(JsonTrustStoreTest, GetTrustLevelReturns0IfNoMatchingEntryExists)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_TRUE(t.init());
    EXPECT_EQ(
        keo_ship::TrustLevel::TRUST_VALUE_USER_UNTRUSTED, t.getTrustLevel("TestGateway.imaginarySKI").getUserTrust());
}

TEST(JsonTrustStoreTest, GetTrustLevelReturnsCorrectValueIfMatchingEntryExists)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "filled_trust_entries.json");
    EXPECT_TRUE(t.init());
    EXPECT_EQ(5U, t.getTrustLevel("TestGateway.imaginarySKI").getUserTrust());
    EXPECT_EQ(80U, t.getTrustLevel("TestGateway.imaginarySKI").getPkiTrust());
    EXPECT_EQ(911U, t.getTrustLevel("TestGateway.imaginarySKI").getSecondFactorTrust());
}

TEST(JsonTrustStoreTest, SetTrustLevelWorksForValidValues)
{
    std::string filename = "/tmp/truststoretest.temporary.json";
    keo_json_security_handler::JsonTrustStore t(filename);
    EXPECT_TRUE(t.init());

    t.setTrustLevel("TestGateway.imaginarySKI", keo_ship::X509Certificate(), keo_ship::TrustLevel(64, 200, 32));
    EXPECT_EQ(64U, t.getTrustLevel("TestGateway.imaginarySKI").getUserTrust());
    EXPECT_EQ(200U, t.getTrustLevel("TestGateway.imaginarySKI").getPkiTrust());
    EXPECT_EQ(32U, t.getTrustLevel("TestGateway.imaginarySKI").getSecondFactorTrust());

    std::remove(filename.c_str());
}

TEST(JsonTrustStoreTest, SetTrustLevelSetsInvalidValuesToZero)
{
    std::string filename = "/tmp/truststoretest.temporary.json";
    keo_json_security_handler::JsonTrustStore t(filename);
    EXPECT_TRUE(t.init());

    // 100 > 96 (max user trust), pki trust can use the full range of unsigned short, 33 > 32 (max 2nd factor trust)
    t.setTrustLevel("TestGateway.imaginarySKI", keo_ship::X509Certificate(), keo_ship::TrustLevel(100, 60000, 33));

    EXPECT_EQ(0U, t.getTrustLevel("TestGateway.imaginarySKI").getUserTrust());
    EXPECT_EQ(60000U, t.getTrustLevel("TestGateway.imaginarySKI").getPkiTrust());
    EXPECT_EQ(0U, t.getTrustLevel("TestGateway.imaginarySKI").getSecondFactorTrust());

    std::remove(filename.c_str());
}

//// Certificate tests
TEST(JsonTrustStoreTest, GetCertificateReturnsEmptyCertificateIfEntryDoesNotExist)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_TRUE(t.init());
    keo_ship::X509Certificate cert = t.getCertificate("TestGateway.noSuchSKI");
    EXPECT_EQ(cert.getData(), std::vector<unsigned char>());
}

TEST(JsonTrustStoreTest, GetCertificateReturnsEmptyCertificateIfEntryExistsWithoutCertificate)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "filled_trust_entries.json");
    EXPECT_TRUE(t.init());
    keo_ship::X509Certificate cert = t.getCertificate("TestGateway.imaginarySKI");
    EXPECT_EQ(cert.getData(), std::vector<unsigned char>());
}

TEST(JsonTrustStoreTest, GetCertificateReturnsCertificateIfEntryExistsWithCertificate)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "filled_trust_entries_with_cert.json");
    EXPECT_TRUE(t.init());

    std::string expectedCert = "ffee003acdaa";
    std::vector<unsigned char> certVector = KEByteArray::fromHex(expectedCert).toVectorUnsigned();
    keo_ship::X509Certificate cert = t.getCertificate("TestGateway.imaginarySKI");
    EXPECT_EQ(cert.getData(), certVector);
}

TEST(JsonTrustStoreTest, GetKeyByCertificateReturnsEmptyStringIfTrustStoreIsEmpty)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "empty_trust_entries.json");
    EXPECT_TRUE(t.init());

    std::vector<unsigned char> certVector
        = KEByteArray::fromHex("112233445566778899aabbccddeeff").toVectorUnsigned();
    keo_ship::X509Certificate certificate(certVector);
    std::string id = t.getKeyByCertificate(certificate);
    EXPECT_EQ("", id);
}

TEST(JsonTrustStoreTest, GetKeyByCertificateReturnsEmptyStringIfNoMatchingTrustStoreEntryExists)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "filled_trust_entries_with_cert.json");
    EXPECT_TRUE(t.init());

    std::vector<unsigned char> certVector
        = KEByteArray::fromHex("112233445566778899aabbccddeeff").toVectorUnsigned();
    keo_ship::X509Certificate certificate(certVector);
    std::string id = t.getKeyByCertificate(certificate);
    EXPECT_EQ("", id);
}

TEST(JsonTrustStoreTest, GetKeyByCertificateReturnsCorrectIdIfMatchingTrustStoreEntryExists)
{
    keo_json_security_handler::JsonTrustStore t(std::string(TC_SAMPLES_DIR) + "filled_trust_entries_with_cert.json");
    EXPECT_TRUE(t.init());

    // Test for 2nd trust store entry
    std::vector<unsigned char> certVector = KEByteArray::fromHex("badeaffe").toVectorUnsigned();
    keo_ship::X509Certificate certificateSecondEntry(certVector);
    std::string id = t.getKeyByCertificate(certificateSecondEntry);
    EXPECT_EQ("TestGateway.anotherImaginarySKI", id);

    // Test for 1st trust store entry
    certVector = KEByteArray::fromHex("ffee003acdaa").toVectorUnsigned();
    keo_ship::X509Certificate certificateFirstEntry(certVector);
    id = t.getKeyByCertificate(certificateFirstEntry);
    EXPECT_EQ("TestGateway.imaginarySKI", id);
}

TEST(JsonTrustStoreTest, SetTrustLevelWorksForNonExistingEntry)
{
    std::string filename = "/tmp/truststoretest.temporary.json";
    keo_json_security_handler::JsonTrustStore t(filename);
    EXPECT_TRUE(t.init());

    std::string entryId = "someEntry.someSKI";

    std::vector<unsigned char> certVector = KEByteArray::fromHex("deadc0def000").toVectorUnsigned();
    keo_ship::X509Certificate certificate(certVector);
    t.setTrustLevel(entryId, certificate, keo_ship::TrustLevel(64));

    EXPECT_EQ(certificate.getData(), t.getCertificate(entryId).getData());
    EXPECT_EQ(64U, t.getTrustLevel(entryId).getUserTrust());
    EXPECT_EQ(0U, t.getTrustLevel(entryId).getPkiTrust());
    EXPECT_EQ(0U, t.getTrustLevel(entryId).getSecondFactorTrust());

    std::remove(filename.c_str());
}

TEST(JsonTrustStoreTest, SetTrustLevelOverwritesExistingEntry)
{
    std::string tmpFilename = "/tmp/test_truststore.json";

    std::ifstream src(std::string(TC_SAMPLES_DIR) + "filled_trust_entries_with_cert.json", std::ios::binary);
    std::ofstream dst(tmpFilename, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    keo_json_security_handler::JsonTrustStore t(tmpFilename);
    EXPECT_TRUE(t.init());

    std::string entryId = "TestGateway.anotherImaginarySKI";
    std::string expectedInitialCert = "badeaffe";

    // precondition: values are set according to the file contents
    EXPECT_EQ(
        KEByteArray::fromHex(expectedInitialCert).toVectorUnsigned(), t.getCertificate(entryId).getData());
    EXPECT_EQ(42U, t.getTrustLevel(entryId).getUserTrust());

    // update the trust data
    std::vector<unsigned char> certVector = KEByteArray::fromHex("deadc0def000").toVectorUnsigned();
    keo_ship::X509Certificate certificate(certVector);
    t.setTrustLevel(entryId, certificate, keo_ship::TrustLevel(64));

    // postcondition: original values have been overwritten
    EXPECT_EQ(certificate.getData(), t.getCertificate(entryId).getData());
    EXPECT_EQ(64U, t.getTrustLevel(entryId).getUserTrust());

    std::remove(tmpFilename.c_str());
}

TEST(JsonTrustStoreTest, RevokeTrustRemovesTrust)
{
    std::string tmpFilename = "/tmp/test_truststore.json";

    std::ifstream src(std::string(TC_SAMPLES_DIR) + "filled_trust_entries_with_cert.json");
    std::ofstream dst(tmpFilename, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    keo_json_security_handler::JsonTrustStore t(tmpFilename);
    EXPECT_TRUE(t.init());

    std::string entryId = "TestGateway.anotherImaginarySKI";

    std::string expectedInitialCert = "badeaffe";
    // precondition: values are set according to the file contents
    EXPECT_EQ(
        KEByteArray::fromHex(expectedInitialCert).toVectorUnsigned(), t.getCertificate(entryId).getData());
    EXPECT_EQ(42U, t.getTrustLevel(entryId).getUserTrust());

    t.revokeTrust(entryId);

    // postcondition 1: cert retrieved is empty & trustlevel is 0
    EXPECT_TRUE(t.getCertificate(entryId).getData().empty());
    EXPECT_EQ(0U, t.getTrustLevel(entryId).getUserTrust());

    // postcondition 2: reading the file yields the same results as in postcondition 1
    keo_json_security_handler::JsonTrustStore t2(tmpFilename);
    EXPECT_TRUE(t2.init());

    EXPECT_TRUE(t2.getCertificate(entryId).getData().empty());
    EXPECT_EQ(0U, t2.getTrustLevel(entryId).getUserTrust());

    std::remove(tmpFilename.c_str());
}
