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

#include <vector>

#include "ClassBuilder.h"
#include "JsonParser.h"
#include "keo_ship/CShipListClass.h"
#include "keo_ship/ShipDataUtilities.h"

using namespace keo_ship;

const int RESERVE_VECTOR_SIZE_FOR_HIERARCHY_PARSER = 6;

// Constructor of empty class //
ClassBuilder::ClassBuilder()
    : m_parser()
    , m_jsonHierarchy()
    , m_isEmptyArray(false)
    , m_listDataTypeList()
    , m_baseDataClassList()
    , m_isArrayElement(false)
    , m_hashKeyName(0)
    , m_value()
    , m_lastObjectPtr(NULL)
{
    m_jsonHierarchy.reserve(RESERVE_VECTOR_SIZE_FOR_HIERARCHY_PARSER);
}
bool ClassBuilder::createDataClassMessage(const std::vector<char>& c_pJsonArray, keo_ship::CShipDataClass*& p_dataClass)
{
    std::size_t index = 0;
    if (c_pJsonArray.size() == 0 || c_pJsonArray.size() < index)
    {
        return false;
    }
    index++;
    if (!checkNextToken(c_pJsonArray, index, JsonParser::START_OBJECT))
    {
        return false;
    }
    m_jsonHierarchy.push_back(1);

    if (!checkNextToken(c_pJsonArray, index, JsonParser::KEY_NAME))
    {
        return false;
    }
    keo_ship::ShipDataType messageDataType = keo_ship::ShipDataUtilities::getDataTypeFromString(m_parser.getCurrentString());
    p_dataClass = keo_ship::ShipDataUtilities::createShipDataFromDataType(messageDataType);
    if (!p_dataClass)
    {
        return false;
    }
    m_lastObjectPtr = p_dataClass;
    m_baseDataClassList.push_back(p_dataClass);

    if (!checkNextToken(c_pJsonArray, index, JsonParser::START_ARRAY))
    {
        return false;
    }

    keo_ship::JsonParser::JsonToken cmdToken = m_parser.nextToken(c_pJsonArray, index);
    if (cmdToken == JsonParser::START_OBJECT)
    {
        m_jsonHierarchy.push_back(0);
        m_jsonHierarchy.push_back(1);
        if (!handleObject(c_pJsonArray, index))
        {
            return false;
        }
    }
    else if (cmdToken != JsonParser::END_ARRAY)
    {
        return false;
    }

    bool status = true;
    status &= checkNextToken(c_pJsonArray, index, JsonParser::END_OBJECT);
    status &= checkNextToken(c_pJsonArray, index, JsonParser::END_PARSING);

    return status;
}
bool ClassBuilder::checkNextToken(
    const std::vector<char>& c_jsonArray, std::size_t& r_index, JsonParser::JsonToken c_checkToken)
{
    if (m_parser.nextToken(c_jsonArray, r_index) != c_checkToken)
    {
        return false;
    }
    return true;
}
bool ClassBuilder::handleObject(const std::vector<char>& c_jsonArray, std::size_t& r_index)
{
    size_t returnSize = m_jsonHierarchy.size() - 1;
    do
    {
        JsonParser::JsonToken token = m_parser.nextToken(c_jsonArray, r_index);
        std::string value = m_parser.getCurrentString();
        if (handleToken(token, value))
        {
            switch (token)
            {
                case JsonParser::START_ARRAY:
                {
                    m_jsonHierarchy.push_back(0);
                    break;
                }
                case JsonParser::START_OBJECT:
                {
                    m_jsonHierarchy.push_back(1);
                    break;
                }
                case JsonParser::END_ARRAY:
                {
                    if (m_jsonHierarchy.back() == 0)
                    {
                        m_jsonHierarchy.pop_back();
                    }
                    else
                    {
                        return false;
                    }
                    break;
                }
                case JsonParser::END_OBJECT:
                {
                    if (m_jsonHierarchy.back() == 1)
                    {
                        m_jsonHierarchy.pop_back();
                    }
                    else
                    {
                        return false;
                    }
                    break;
                }
                case JsonParser::END_PARSING:
                {
                    m_jsonHierarchy.pop_back();
                    break;
                }
                default:
                {
                }
            }
        }
        else
        {
            return false;
        }
    } while (m_jsonHierarchy.size() >= returnSize);
    return true;
}
bool ClassBuilder::handleToken(JsonParser::JsonToken c_token, const std::string& c_tokenValue)
{
    switch (c_token)
    {
        case JsonParser::END_ARRAY:
        {
            if (m_isArrayElement)
            {
                m_isArrayElement = false;
            }
            if (m_parser.getLastToken() == JsonParser::START_ARRAY)
            {
                m_isEmptyArray = true;
                return true;
            }
            if (m_listDataTypeList.size())
            {
                if (!m_lastObjectPtr)
                {
                    return false;
                }
                if (m_listDataTypeList.back() == m_lastObjectPtr->getDataType())
                {
                    keo_ship::CShipDataClass* listPtr = m_baseDataClassList.back();
                    // listPtr->addListElement(m_lastObjectPtr);
                    m_lastObjectPtr = listPtr;
                    m_isArrayElement = true;
                    m_listDataTypeList.pop_back();
                    m_baseDataClassList.pop_back();
                    return true;
                }
            }
            return true;
        }
        case JsonParser::END_OBJECT:
        {
            if (m_parser.getLastToken() == JsonParser::END_ARRAY)
            {
                if (m_isEmptyArray)
                {
                    if (!m_lastObjectPtr)
                    {
                        return false;
                    }
                    m_lastObjectPtr->setSimpleMemberAsString(m_hashKeyName, "", keo_ship::VALUE_EMPTY_LIST);
                    m_isEmptyArray = false;
                    return true;
                }
                if (!m_baseDataClassList.size())
                {
                    return false;
                }
                m_lastObjectPtr = m_baseDataClassList.back();
                m_baseDataClassList.pop_back();
            }
            return true;
        }
        case JsonParser::KEY_NAME:
        {
            if (m_parser.getLastToken() == JsonParser::START_ARRAY || m_isArrayElement)
            {
                if (!m_lastObjectPtr)
                {
                    return false;
                }
                m_isArrayElement = true;
                static_cast<keo_ship::CShipListClass*>(m_lastObjectPtr)->appendListElement(c_tokenValue);
                return true;
            }
            m_hashKeyName = getHashValue(c_tokenValue);
            return true;
        }
        case JsonParser::START_ARRAY:
        {
            if (m_parser.getLastToken() == JsonParser::START_ARRAY)
            {
                m_isArrayElement = true;
            }
            return true;
        }
        case JsonParser::START_OBJECT:
        {
            if (m_parser.getLastToken() != JsonParser::START_ARRAY)
            {
                return true;
            }
            if (!m_lastObjectPtr)
            {
                return false;
            }
            keo_ship::CShipDataClass* objectPtr;
            if (m_isArrayElement)
            {
                // objectPtr = static_cast<keo_ship::CShipDataClass*>(m_lastObjectPtr)->appendEmptyListElement();
                // m_listDataTypeList.push_back(objectPtr->getDataType());
                m_isArrayElement = false;
            }
            else
            {
                objectPtr = m_lastObjectPtr->SetMemberIsSetAndReturnPointer(m_hashKeyName);
                m_baseDataClassList.push_back(m_lastObjectPtr);
                m_lastObjectPtr = objectPtr;
            }
            return true;
        }
        case JsonParser::VALUE_FALSE:
        case JsonParser::VALUE_TRUE:
        case JsonParser::VALUE_NULL:
        {
            m_value.clear();
            if (!m_lastObjectPtr)
            {
                return false;
            }
            m_lastObjectPtr->setSimpleMemberAsString(m_hashKeyName, m_value.c_str(), (keo_ship::ValueType)c_token);
            return true;
        }
        case JsonParser::VALUE_NUMBER:
        case JsonParser::VALUE_STRING:
        {
            m_value.assign(c_tokenValue);
            if (!m_lastObjectPtr)
            {
                return false;
            }
            m_lastObjectPtr->setSimpleMemberAsString(m_hashKeyName, m_value.c_str(), (keo_ship::ValueType)c_token);
            return true;
        }
        case JsonParser::END_PARSING:
        {
            return false;
        }
        default:
        {
            m_hashKeyName = 0;
        }
    }
    return false;
}
int32_t ClassBuilder::getHashValue(const std::string& c_string)
{
    std::string::const_iterator iter = c_string.begin();
    std::string::const_iterator iterEnd = c_string.end();
    int32_t returnHash = 0;
    int shift = 0;
    for (; iter != iterEnd; ++iter)
    {
        returnHash += (*iter << shift);
        if (shift++ > 20)
        {
            shift = 0;
        }
    }
    return returnHash;
}
