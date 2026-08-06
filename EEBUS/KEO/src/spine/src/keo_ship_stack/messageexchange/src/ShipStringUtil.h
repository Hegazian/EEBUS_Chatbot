/*
 *     Copyright KEO GmbH 2018 - All rights reserved!
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


#ifndef SHIPSTRINGUTIL_H_
#define SHIPSTRINGUTIL_H_

#include <stdint.h>
#include <string>
#include <vector>

/** @addtogroup keo_ship_stack
 * @{
 */

namespace keo_ship
{

/**
 * Some static helper functions for std::string
 */
class ShipStringUtil
{
public:
    ShipStringUtil() = delete;

    /**
     * This function is a frontend to the standard sprintf.
     *
     * @param num  number
     * @param frm  format char. It is the same as in sprintf for float values (e, E, g, G, f). Default 'g'
     * @param prec precision (see sprintf). Limited to 15
     * @return The resulting string
     */
    static std::string dnumber(const double& num, char frm = 'g', int prec = 6); // ???
    /**
     * Creates a string from number
     * Only base 10 and 16 supported.
     * @param num Input number
     * @param numBase Base default: 10
     * @return The resulting string
     */
    static std::string number(int32_t num, int numBase = 10);

    /**
     * Creates a string from number
     * Only base 10 and 16 supported.
     * @param num Input number
     * @param numBase Base default: 10
     * @return The resulting string
     */
    static std::string lnumber(int64_t num, int numBase = 10);

    /**
     * Creates a string from number
     * Only base 10 and 16 supported.
     * @param num
     * @param numBase default: 10
     * @return
     */
    static std::string unumber(uint32_t num, int numBase = 10); // ???

    /**
     * Creates a string from number
     * Only base 10 and 16 supported.
     * @param num Input number
     * @param numBase Base default: 10
     * @return The resulting string
     */
    static std::string ulnumber(uint64_t num, int numBase = 10); // ???

    /**
     * Creates a number from string
     * @param str Input string with containing double value.
     * @return The double value converted from string.
     */
    static double toDouble(const char* str);

    /**
     * Creates a number from string
     * @param str Input string with containing value.
     * @return The value converted from string.
     */
    static uint32_t toUint32(const char* str);

    /**
     * Creates a number from string
     * @param str Input string with containing value.
     * @return The value converted from string.
     */
    static uint16_t toUint16(const char* str);

    /**
     * Creates a number from string
     * @param str Input string with containing value.
     * @return The value converted from string.
     */
    static uint64_t toUint64(const char* str);

    /**
     * Creates a number from string
     * @param str Input string with containing value.
     * @return The value converted from string.
     */
    static int64_t toInt64(const char* str);

    /**
     * Creates a number from string
     * @param str Input string with containing value.
     * @return The value converted from string.
     */
    static int32_t toInt32(const char* str);

    /**
     * Creates a number from string
     * @param str Input string with containing value.
     * @return The value converted from string.
     */
    static int16_t toInt16(const char* str);

};
}

/** @}
 */

#endif /* SHIPSTRINGUTIL_H_ */
