/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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
/**
 *     @brief      Defines a transformer object. It uses to parse and build JSON messages.
 *
 *     @par        Module description
 *                 TODO module description
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef STRING_HELPER_H_
#define STRING_HELPER_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <stdint.h>
#include <stdio.h>
#include <string>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

namespace keo_ship
{
/* ****************************************************************************** *
 *  class StringHelper: definition                                                *
 * ****************************************************************************** */

class StringHelper
{
public:
    /**
     * Creates a string from number
     * @param num
     * @return
     */
    static std::string unumber(uint32_t num)
    {
        char buf[32];
        sprintf(buf, "%u", num);
        return std::string(buf);
    }

    /**
     * Creates a number from string
     * @param str
     * @return
     */
    static uint32_t toUint32(const char* str)
    {
        if (str != NULL)
        {
            uint32_t tmp = 0;
            if (sscanf(str, "%u", &tmp))
            {
                return tmp & 0xffffffff;
            }
        }
        return 0;
    }

    /**
     * Creates a number from string
     * @param str
     * @return
     */
    static uint16_t toUint16(const char* str)
    {
        if (str != NULL)
        {
            uint32_t tmp = 0;
            if (sscanf(str, "%u", &tmp))
            {
                return (uint16_t)tmp & 0xffff;
            }
        }
        return 0;
    }

private:
    StringHelper()
    {
    }
};
} // end namespace keo_ship

#endif /* STRING_HELPER_H_ */
