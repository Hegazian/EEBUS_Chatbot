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


#include <cstring>
#include <stdio.h>
#include <ShipStringUtil.h>

#ifdef __linux__

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>

#elif _WIN32

#if (_MSC_VER >= 1600)
#include <inttypes.h>
#else

#define PRIx64 "lx"
#define PRIu64 "lu"

#endif

#else

#endif

#include <sstream>

//#include <limits>
namespace keo_ship
{

/*

In QString::number and printf, the flags have the following meanings:
Format    Meaning
e    format as [-]9.9e[+|-]999
E    format as [-]9.9E[+|-]999
f    format as [-]9.9
g    use e or f format, whichever is the most concise
G    use E or f format, whichever is the most concise
 *
 A precision is also specified with the argument format. For the 'e', 'E', and 'f' formats,
 the precision represents the number of digits after the decimal point.

 For the 'g' and 'G' formats, the precision represents the maximum number
 of significant digits (trailing zeroes are omitted).

 */
std::string ShipStringUtil::dnumber(const double& num, char frm, int prec)
{
    const int maxLength = 48;
    char buf[maxLength];

    size_t i = 0;
    if (prec > 15)
    {
        prec = 15;
    }
    // first build the sprintf format string out of arguments:
    char format[6] = { '%', '\0', '\0', '\0', '\0', '\0' };
    switch (frm)
    {
        case 'g':
        case 'G':
        case 'e':
        case 'E':
        case 'f':
            format[1] = '.';
            if (prec < 10)
            {
                format[2] = (char)'0' + prec;
                i = 3;
            }
            else if (prec < 100)
            {
                format[3] = (char)'0' + (prec % 10);
                format[2] = (char)'0' + (prec / 10);
                i = 4;
            }
            format[i] = frm;
            // -> "%.6f" "%.3G" "%.12E" etc.
            break;
        default:
            format[1] = 'f'; // -> "%f"
            break;
    }
    snprintf(buf, maxLength, (const char*)format, num);
    return std::string(buf);
}

std::string ShipStringUtil::number(int32_t num, int numBase)
{
    // signed!
    char buf[32];
    if (numBase == 16)
        sprintf(buf, "%lx", (unsigned long)num); // hex numbers not negative
    else
        sprintf(buf, "%d", num);
    return std::string(buf);
}

std::string ShipStringUtil::lnumber(int64_t num, int numBase)
{
    std::string valueStr;
    if (numBase == 16)
    {
        valueStr = static_cast<std::ostringstream*>(&(std::ostringstream() << std::hex << num))->str();
    }
    else
    {
        valueStr = static_cast<std::ostringstream*>(&(std::ostringstream() << num))->str();
    }
    return valueStr;
}

std::string ShipStringUtil::unumber(uint32_t num, int numBase)
{
    // unsigned!
    char buf[32];
    if (numBase == 16)
        sprintf(buf, "%x", num);
    else
        sprintf(buf, "%u", num);
    return std::string(buf);
}

std::string ShipStringUtil::ulnumber(uint64_t num, int numBase)
{
    const int maxLength = 32;
    char buf[maxLength];

    if (numBase == 16)
    {
        snprintf(buf, maxLength, "%" PRIx64, num);
    }
    else
    {
        snprintf(buf, maxLength, "%" PRIu64, num); // TODO not really portable...
    }
    return std::string(buf);
}

double ShipStringUtil::toDouble(const char* str)
{
    if (str == NULL)
    {
        return 0; // or NaN?
    }
    else
    {
        double tmp = 0;
        if (sscanf(str, "%lf", &tmp))
        {
            return tmp;
        }
        else
        {
            return 0;
        }
    }
}
uint32_t ShipStringUtil::toUint32(const char* str)
{
    if (str == NULL)
    {
        return 0; // or NaN?
    }
    else
    {
        uint32_t tmp = 0;
        if (sscanf(str, "%u", &tmp))
        {
            return tmp & 0xffffffff;
        }
        else
        {
            return 0;
        }
    }
}

uint16_t ShipStringUtil::toUint16(const char* str)
{

    if (str == NULL)
    {
        return 0; // or NaN?
    }
    else
    {
        unsigned int tmp = 0;
        if (sscanf(str, "%u", &tmp))
        {
            return (uint16_t)tmp & 0xffff;
        }
        else
        {
            return 0;
        }
    }
}

uint64_t ShipStringUtil::toUint64(const char* str)
{

    if (str == NULL)
    {
        return 0; // or NaN?
    }
    else
    {
        uint64_t tmp = 0;
        if (sscanf(str, "%" PRIu64, &tmp))
        {
            return (uint64_t)tmp & 0xffffffffffffffffULL;
        }
        else
        {
            return 0;
        }
    }
}

int64_t ShipStringUtil::toInt64(const char* str)
{
    int64_t ret = 0;
    if (str != NULL)
    {
        std::stringstream ss(str);
        ss >> ret;
    }
    return (ret);
}

int32_t ShipStringUtil::toInt32(const char* str)
{
    if (str == NULL)
    {
        return 0; // or NaN?
    }
    else
    {
        int32_t tmp = 0;
        if (sscanf(str, "%d", &tmp))
        {
            return tmp;
        }
        else
        {
            return 0;
        }
    }
}

int16_t ShipStringUtil::toInt16(const char* str)
{
    if (str == NULL)
    {
        return 0; // or NaN?
    }
    else
    {
        int16_t tmp = 0;
        if (sscanf(str, "%hd", &tmp))
        {
            return tmp;
        }
        else
        {
            return 0;
        }
    }
}



}
