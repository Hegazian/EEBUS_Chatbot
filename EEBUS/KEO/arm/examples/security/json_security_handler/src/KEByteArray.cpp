/*
 *     Copyright KEO GmbH 2013 - All rights reserved!
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
 * \file KEByteArray.cpp
 *
 *  Created on: 09.09.2013
 *      Author: habiger
 */

#include <iostream>
#include "KEByteArray.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


KEByteArray::KEByteArray(const std::string& s)
{
    m_data.assign(s.begin(), s.end());
}

KEByteArray::KEByteArray(const char* s)
{
    setContent(s, strlen(s));
}

KEByteArray::KEByteArray(const std::vector<char>& s)
{
    m_data.assign(s.begin(), s.end());
}

KEByteArray::KEByteArray(const std::vector<unsigned char>& s)
{
    m_data.assign(s.begin(), s.end());
}

KEByteArray::KEByteArray(const char* content, size_t sz)
{
    setContent(content, sz);
}

void KEByteArray::setContent(const char* s, size_t sz)
{
    if (s)
    {
        m_data.assign(s, s + sz);
    }
}

bool KEByteArray::isHexChar(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

KEByteArray KEByteArray::fromHex(const char* hexString)
{
    if (hexString == NULL)
    {
        return KEByteArray();
    }

    size_t len = strlen(hexString);

    if (len < 2)
    {
        return KEByteArray();
    }

    if ((len % 1) == 1)
    {
        return KEByteArray(); // must be even count of characters (2 hex chars per byte)
    }

    KEByteArray returnHex;
    returnHex.fill(len / 2, '\0');
    unsigned int parsedChar;
    char buf[3] = { '\0', '\0', '\0' };
    bool fail = false;

    size_t j = 0;
    for (size_t i = 0; i < len && !fail; i++)
    {
        buf[0] = hexString[i];
        buf[1] = hexString[++i];
        fail = !KEByteArray::isHexChar(buf[0]) || !KEByteArray::isHexChar(buf[1]);
        if (!fail)
        {
            if (sscanf((const char*)buf, "%02x", &parsedChar) > 0)
            {
                returnHex.m_data[j++] = ((char)parsedChar);
            }
        }
    }
    if (fail)
    {
        returnHex.m_data.clear();
        return returnHex;
    }
    else
    {
        return returnHex;
    }
}

void KEByteArray::fill(size_t size, char fillChar)
{
    m_data.assign(size, fillChar);
}

KEByteArray::KEByteArray(size_t size, char fillChar)
{
    fill(size, fillChar);
}

void KEByteArray::set(size_t index, char c)
{
    if (index < m_data.size())
    {
        m_data[index] = c;
    }
}

bool KEByteArray::equals(const KEByteArray& other) const
{
    return (m_data == other.m_data);
}

size_t KEByteArray::length(void) const
{
    return m_data.size();
}

std::string KEByteArray::toHex(void) const
{
    std::string retVal;
    retVal.reserve(m_data.size() * 2);
    char buf[3];
    for (size_t i = 0; i < m_data.size(); i++)
    {
        sprintf(buf, "%02x", (uint8_t)m_data.at(i));
        retVal.append(buf);
    }
    return retVal;
}

std::string KEByteArray::toString(void) const
{
    std::string str(m_data.begin(), m_data.end());
    return str;
}

std::vector<char> KEByteArray::toVector(void) const
{
    return m_data;
}

std::vector<unsigned char> KEByteArray::toVectorUnsigned() const
{
    return std::vector<unsigned char>(m_data.begin(), m_data.end());
}

KEByteArray& KEByteArray::operator=(const KEByteArray& other)
{
    if (this == &other)
        return *this;
    m_data = other.m_data;
    return *this;
}

KEByteArray::KEByteArray()
{
}

KEByteArray KEByteArray::fromHex(const std::string& hexString)
{
    return KEByteArray::fromHex(hexString.c_str());
}

const char* KEByteArray::constData() const
{
    if (m_data.size())
    {
        return reinterpret_cast<const char*>(&m_data[0]);
    }
    return NULL;
}

void KEByteArray::clear(void)
{
    m_data.clear();
}
