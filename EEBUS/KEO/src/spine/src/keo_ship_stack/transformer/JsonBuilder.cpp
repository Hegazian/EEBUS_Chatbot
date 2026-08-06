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
 *  @brief Class structure
 *
 *  @par    Module description
 *          JsonBuilder creates from a SHIP data class the corresponding JSON text
 *
 */

#include "JsonBuilder.h"
#include "keo_ship/CShipListClass.h"

using namespace keo_ship;

JsonBuilder::JsonBuilder()
    : m_isStartObjectList()
{
}
void JsonBuilder::reset()
{
    m_isStartObjectList.clear();
}
bool JsonBuilder::getJsonFromClass(keo_ship::CShipDataClass* pDataClass, std::vector<char>& r_jsonArray, char messageType)
{
    r_jsonArray.push_back(messageType);
    keo_ship::ShipDataType dataType = pDataClass->getDataType();
    writeStartObject(r_jsonArray);
    if (dataType == keo_ship::ACCESS_METHODS_REQUEST_TYPE)
    {
        // only class if an empty array
        writeEmptyArray(keo_ship::ShipDataTypeAsString[dataType], r_jsonArray);
    }
    else
    {
        writeStartArray(keo_ship::ShipDataTypeAsString[dataType], r_jsonArray);
        handleDataClass(pDataClass, r_jsonArray);
        writeEnd(r_jsonArray);
    }
    r_jsonArray.pop_back();
    writeEnd(r_jsonArray);
    r_jsonArray.pop_back();
    return true;
}
void JsonBuilder::handleDataClass(keo_ship::CShipDataClass* p_dataClass, std::vector<char>& r_jsonArray)
{
    std::vector<int32_t> setMemberList = p_dataClass->getListOfSetMembers();
    std::vector<int32_t>::iterator iter = setMemberList.begin();
    std::vector<int32_t>::iterator iterEnd = setMemberList.end();
    std::string valueString;
    for (; iter != iterEnd; ++iter)
    {
        writeStartObject(r_jsonArray);
        int32_t hash = getHashValue(keo_ship::ShipDataMemberNameArray[*iter]);
        keo_ship::CShipDataClass* pMemberClass = p_dataClass->SetMemberIsSetAndReturnPointer(hash);
        if (pMemberClass)
        {
            writeStartArray(keo_ship::ShipDataMemberNameArray[*iter], r_jsonArray);
            handleDataClass(pMemberClass, r_jsonArray);
            writeEnd(r_jsonArray);
        }
        else
        {
            switch (p_dataClass->getSimpleMemberAsString(hash, valueString))
            {
                case keo_ship::VALUE_NULL:
                {
                    writeNull(keo_ship::ShipDataMemberNameArray[*iter], r_jsonArray);
                    break;
                }
                case keo_ship::VALUE_FALSE:
                case keo_ship::VALUE_TRUE:
                case keo_ship::VALUE_NUMBER:
                {
                    writeValue(keo_ship::ShipDataMemberNameArray[*iter], valueString, r_jsonArray);
                    break;
                }
                case keo_ship::VALUE_STRING:
                {
                    writeValueString(keo_ship::ShipDataMemberNameArray[*iter], valueString, r_jsonArray);
                    break;
                }
                case keo_ship::VALUE_LIST:
                {
                    writeStartArray(keo_ship::ShipDataMemberNameArray[*iter], r_jsonArray);
                    int index = 0;
                    std::string element = static_cast<keo_ship::CShipListClass*>(p_dataClass)->getListElement(index);
                    while (!element.empty())
                    {
                        r_jsonArray.push_back('\"');
                        std::copy(element.begin(), element.end(), std::back_inserter(r_jsonArray));
                        r_jsonArray.push_back('\"');
                        r_jsonArray.push_back(',');
                        index++;
                        element = static_cast<keo_ship::CShipListClass*>(p_dataClass)->getListElement(index);
                    }
                    writeEnd(r_jsonArray);
                    break;
                }
                case keo_ship::VALUE_EMPTY_LIST:
                {
                    writeEmptyArray(keo_ship::ShipDataMemberNameArray[*iter], r_jsonArray);
                    break;
                }
                default:
                {
                }
            }
        }
        writeEnd(r_jsonArray);
    }
}
void JsonBuilder::writeStartObject(std::vector<char>& r_jsonArray)
{
    writeObjectBegin(r_jsonArray);
    m_isStartObjectList.push_back(true);
}
void JsonBuilder::writeStartObject(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    writeObjectBegin(c_key, r_jsonArray);
    m_isStartObjectList.push_back(true);
}
void JsonBuilder::writeStartArray(std::vector<char>& r_jsonArray)
{
    writeArrayBegin(r_jsonArray);
    m_isStartObjectList.push_back(false);
}
void JsonBuilder::writeStartArray(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    writeArrayBegin(c_key, r_jsonArray);
    m_isStartObjectList.push_back(false);
}
void JsonBuilder::writeEnd(std::vector<char>& r_jsonArray)
{
    if (m_isStartObjectList.empty())
    {
        r_jsonArray.push_back(',');
        return;
    }
    if (r_jsonArray.back() == ',')
    {
        r_jsonArray.pop_back();
    }
    if (m_isStartObjectList.back())
    {
        r_jsonArray.push_back('}');
    }
    else
    {
        r_jsonArray.push_back(']');
    }
    r_jsonArray.push_back(',');
    m_isStartObjectList.pop_back();
}
int32_t JsonBuilder::getHashValue(const std::string& c_string)
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
void JsonBuilder::writeKey(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    r_jsonArray.push_back('\"');
    std::copy(c_key.begin(), c_key.end(), std::back_inserter(r_jsonArray));
    r_jsonArray.push_back('\"');
    r_jsonArray.push_back(':');
}
void JsonBuilder::writeEmptyArray(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    writeKey(c_key, r_jsonArray);
    r_jsonArray.push_back('[');
    r_jsonArray.push_back(']');
    r_jsonArray.push_back(',');
}
void JsonBuilder::writeNull(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    writeKey(c_key, r_jsonArray);
    r_jsonArray.push_back('n');
    r_jsonArray.push_back('u');
    r_jsonArray.push_back('l');
    r_jsonArray.push_back('l');
    r_jsonArray.push_back(',');
}
void JsonBuilder::writeValueString(const std::string& c_key, const std::string& c_value, std::vector<char>& r_jsonArray)
{
    writeKey(c_key, r_jsonArray);
    r_jsonArray.push_back('\"');
    std::copy(c_value.begin(), c_value.end(), std::back_inserter(r_jsonArray));
    r_jsonArray.push_back('\"');
    r_jsonArray.push_back(',');
}
void JsonBuilder::writeValue(const std::string& c_key, const std::string& c_value, std::vector<char>& r_jsonArray)
{
    writeKey(c_key, r_jsonArray);
    std::copy(c_value.begin(), c_value.end(), std::back_inserter(r_jsonArray));
    r_jsonArray.push_back(',');
}
void JsonBuilder::writeObjectBegin(std::vector<char>& r_jsonArray)
{
    r_jsonArray.push_back('{');
}
void JsonBuilder::writeObjectBegin(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    writeKey(c_key, r_jsonArray);
    r_jsonArray.push_back('{');
}
void JsonBuilder::writeArrayBegin(std::vector<char>& r_jsonArray)
{
    r_jsonArray.push_back('[');
}
void JsonBuilder::writeArrayBegin(const std::string& c_key, std::vector<char>& r_jsonArray)
{
    writeKey(c_key, r_jsonArray);
    r_jsonArray.push_back('[');
}
void JsonBuilder::writeObjectEnd(std::vector<char>& r_jsonArray)
{
    if (r_jsonArray.back() == ',')
    {
        r_jsonArray.pop_back();
    }
    r_jsonArray.push_back('}');
    r_jsonArray.push_back(',');
}
void JsonBuilder::writeArrayEnd(std::vector<char>& r_jsonArray)
{
    if (r_jsonArray.back() == ',')
    {
        r_jsonArray.pop_back();
    }
    r_jsonArray.push_back(']');
    r_jsonArray.push_back(',');
}
