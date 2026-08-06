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
#include <keo_ship/ShipSecurity.h>

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */
#include "ShipByteArray.h"

/* ****************************************************************************** *
 *  test header files                                                             *
 * ****************************************************************************** */
#include <gtest/gtest.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <fstream>

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */
class X509CertificateTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::ifstream ifs(
            std::string(X509_SAMPLES_DIR) + "skiTest_secp256r1CertDER.bin", std::ios::in | std::ios::binary);
        std::vector<unsigned char> bufferCert(
            (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        this->cert = keo_ship::X509Certificate(bufferCert);
        ifs.close();
    }

    keo_ship::X509Certificate cert;
};

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

TEST_F(X509CertificateTest, ConstructionAndDestructionWorks)
{
    keo_ship::X509Certificate certObject;

    keo_ship::X509Certificate* certPtr = new keo_ship::X509Certificate();
    delete certPtr;
}

TEST_F(X509CertificateTest, EmptyDataYieldsInvalidCertificate)
{
    keo_ship::X509Certificate c;
    EXPECT_FALSE(c.isValid());

    c.setData(std::vector<unsigned char>());
    EXPECT_FALSE(c.isValid());
}

TEST_F(X509CertificateTest, InvalidDataYieldsInvalidCertificate)
{
    std::vector<unsigned char> data;
    data.push_back('F');
    data.push_back('0');

    keo_ship::X509Certificate c(data);
    EXPECT_FALSE(c.isValid());
}

TEST_F(X509CertificateTest, ValidDataYieldsValidCertificate) {
    EXPECT_TRUE(cert.isValid());
}

TEST_F(X509CertificateTest, PublicKeyIsRetrievedCorrectly)
{
    std::string expectedPublicKey = "04229443b8b6bbc0326639a99163487b3ca25ac0f764fe13a877961c75dbf585489414ffd0a4f38127"
                                    "b0cb49fac858f157e2294233a1e24ff49b3a39b91e05d7d9";
    EXPECT_EQ(expectedPublicKey, keo_ship::ShipByteArray(cert.getPublicKey()).toHex());
}

TEST_F(X509CertificateTest, SerialIsRetrievedCorrectly)
{
    std::string expectedSerial = "1234";

    // FIXME this is the encoding that openssl bignum uses. Maybe we can beautify this at some point.
    std::string expectedSerialHex = "04D2";

    EXPECT_EQ(expectedSerial, cert.getSerial());
    EXPECT_EQ(expectedSerialHex, cert.getSerial(true));
}

TEST_F(X509CertificateTest, IssuerIsRetrievedCorrectly)
{
    std::string expectedIssuer
        = "C = DE, ST = NRW, O = KEO, L = Cologne, OU = Development, emailAddress = devel@kellendonk.de";

    EXPECT_EQ(expectedIssuer, cert.getIssuer());
}

// FIXME create a certificate that is not a CA certificate (so that issuer != subject)
TEST_F(X509CertificateTest, SubjectIsRetrievedCorrectly)
{
    std::string expectedSubject
        = "C = DE, ST = NRW, O = KEO, L = Cologne, OU = Development, emailAddress = devel@kellendonk.de";

    EXPECT_EQ(expectedSubject, cert.getSubject());
}

TEST_F(X509CertificateTest, SKIIsRetrievedCorrectly)
{
    EXPECT_EQ("c90b2c2c08630e217d5df673302df97e1fe4f7a3", cert.getSki());
}

TEST_F(X509CertificateTest, TemporalValidity)
{
    // $ openssl x509 -startdate -enddate -noout -inform der -in skiTest_secp256r1CertDER.bin
    //    notBefore = Nov 15 14:13:01 2016 GMT
    //    notAfter = Nov 13 14:13:01 2026 GMT

    struct tm* timeinfo;
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    timeinfo->tm_year = 2017 - 1900;
    timeinfo->tm_mon = 1;
    timeinfo->tm_mday = 20;
    time_t t = mktime(timeinfo);
    ASSERT_TRUE(cert.isValidAt(&t));

    timeinfo->tm_year = 2015 - 1900;
    t = mktime(timeinfo);
    ASSERT_FALSE(cert.isValidAt(&t));

    timeinfo->tm_year = 2028 - 1900;
    t = mktime(timeinfo);
    ASSERT_FALSE(cert.isValidAt(&t));
}
