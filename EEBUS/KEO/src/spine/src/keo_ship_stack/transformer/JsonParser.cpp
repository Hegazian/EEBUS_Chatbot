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

#include "JsonParser.h"

using namespace keo_ship;

JsonParser::JsonParser()
    : m_parsedString()
    , m_savedString()
    , m_insideString(false)
    , m_parsedStringIndex(1)
    , m_expectedToken(EXPECT_KEYNAME)
    , m_currentToken(END_OBJECT)
    , m_lastToken(END_PARSING)
{
    m_parsedString.reserve(32);
    m_savedString.reserve(32);
}
void JsonParser::reset()
{
    m_parsedString = std::string();
    m_savedString = std::string();
    m_insideString = false;
    m_parsedStringIndex = 1;
    m_expectedToken = EXPECT_KEYNAME;
    m_currentToken = END_OBJECT;
    m_lastToken = END_PARSING;
}
JsonParser::JsonToken JsonParser::getCurrentToken() const
{
    return m_currentToken;
}
JsonParser::JsonToken JsonParser::getLastToken() const
{
    return m_lastToken;
}
const std::string& JsonParser::getCurrentString()
{
    return m_parsedString;
}
JsonParser::JsonToken JsonParser::nextToken(const std::vector<char>& c_pJsonArray, std::size_t& r_index)
{
    const std::size_t fullLength = c_pJsonArray.size();
    if (fullLength <= r_index)
    {
        m_lastToken = m_currentToken;
        m_currentToken = END_PARSING;
        return END_PARSING;
    }
    const unsigned char* data = (const unsigned char*)&(c_pJsonArray[0]);
    const unsigned char* start = data + r_index;
    const unsigned char* position = start;
    const unsigned char* end = data + fullLength;
    m_parsedString.assign(m_savedString);
    m_parsedString.resize(16 + m_savedString.size());
    unsigned char* parsedData = (unsigned char*)&m_parsedString[m_savedString.size()];
    std::size_t reservedString = 16 + m_savedString.size();
    m_parsedStringIndex = m_savedString.size() + 1;
    m_savedString.clear();
    while (position != end)
    {
        r_index++;
        if (m_insideString)
        {
            if (*position == '"')
            { // string tag
                m_insideString = false;
                m_parsedString.resize(m_parsedStringIndex - 1);
                m_parsedStringIndex = 1;
                if (m_expectedToken == EXPECT_KEYNAME)
                {
                    m_expectedToken = EXPECT_COLON;
                    m_lastToken = m_currentToken;
                    m_currentToken = KEY_NAME;
                    return m_currentToken;
                }
                if (m_expectedToken == EXPECT_ENDING)
                {
                    m_expectedToken = EXPECT_KEYNAME;
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_STRING;
                    return m_currentToken;
                }
                ++position; // error if here
                start = position;
            }
            *parsedData = *position;
            parsedData++;
            m_parsedStringIndex++;
            if (m_parsedStringIndex >= reservedString)
            { // we have to allocate more memory
                reservedString += 16;
                m_parsedString.resize(reservedString);
                parsedData = (unsigned char*)&m_parsedString[0] + (m_parsedStringIndex - 1);
            }
            ++position;
            continue;
        }
        if (*position == '{')
        { // CurlyOpen
            m_expectedToken = EXPECT_KEYNAME;
            m_lastToken = m_currentToken;
            m_currentToken = START_OBJECT;
            return m_currentToken;
        }
        if (*position == '[')
        { // SquaredOpen
            m_expectedToken = EXPECT_KEYNAME;
            m_lastToken = m_currentToken;
            m_currentToken = START_ARRAY;
            return m_currentToken;
        }
        if (*position == '}')
        { // CurlyClose
            if (m_expectedToken == EXPECT_ENDING)
            {
                m_parsedString.resize(m_parsedStringIndex - 1);
                m_parsedStringIndex = 1;
                m_expectedToken = EXPECT_KEYNAME;
                if (m_parsedString.size() == 5 && m_parsedString.compare("false") == 0)
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_FALSE;
                }
                else if (m_parsedString.size() == 4 && m_parsedString.compare("true") == 0)
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_TRUE;
                }
                else if (m_parsedString.size() == 4 && m_parsedString.compare("null") == 0)
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_NULL;
                }
                else
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_NUMBER;
                }
                r_index--;
                return m_currentToken;
            }
            m_lastToken = m_currentToken;
            m_currentToken = END_OBJECT;
            return m_currentToken;
        }
        if (*position == ']')
        { // SquaredClose
            m_lastToken = m_currentToken;
            m_currentToken = END_ARRAY;
            return m_currentToken;
        }
        if (*position == '"')
        { // string tag
            ++position;
            m_insideString = true;
            continue;
        }
        if (m_expectedToken == EXPECT_COLON)
        {
            if (*position == ':')
            { // colon
                m_expectedToken = EXPECT_ENDING;
                ++position;
                continue;
            }
        }
        if (m_expectedToken == EXPECT_ENDING)
        {
            if (*position == ' ')
            { // space
                ++position;
                continue;
            }
            if (*position == ',')
            { // comma
                m_parsedString.resize(m_parsedStringIndex - 1);
                m_parsedStringIndex = 1;
                m_expectedToken = EXPECT_KEYNAME;
                if (m_parsedString.size() == 5 && m_parsedString.compare("false") == 0)
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_FALSE;
                }
                else if (m_parsedString.size() == 4 && m_parsedString.compare("true") == 0)
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_TRUE;
                }
                else if (m_parsedString.size() == 4 && m_parsedString.compare("null") == 0)
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_NULL;
                }
                else
                {
                    m_lastToken = m_currentToken;
                    m_currentToken = VALUE_NUMBER;
                }
                return m_currentToken;
            }
            *parsedData = *position;
            parsedData++;
            m_parsedStringIndex++;
            if (m_parsedStringIndex >= reservedString)
            { // we have to allocate more memory
                reservedString += 16;
                m_parsedString.resize(reservedString);
                parsedData = (unsigned char*)&m_parsedString[0] + (m_parsedStringIndex - 1);
            }
            ++position;
            continue;
        }
        ++position;
    }
    if (m_insideString)
    {
        m_parsedString.resize(m_parsedStringIndex - 1);
        m_savedString.assign(m_parsedString);
    }
    else if (m_expectedToken == EXPECT_ENDING)
    {
        m_parsedString.resize(m_parsedStringIndex - 1);
        m_savedString.assign(m_parsedString);
    }
    m_lastToken = m_currentToken;
    m_currentToken = END_PARSING;
    return m_currentToken;
}
