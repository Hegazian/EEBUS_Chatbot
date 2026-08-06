/**
 *  @brief SPINE Datagram helper functions
 *
 *  @par    Module description
 *            Some helper functions to work with SPINE datagrams
 *
 */

#include "SpineClassIdReferences_p.h"
#include "SpineReferences_p.h"
#include "SpineStringReferences_p.h"
#include <keo_datagram/core/SpineVersionUtilities.h>

namespace keo_datagram
{


std::vector<std::string> SpineVersionUtilities::getAllSpineDataTypes()
{
    std::vector<std::string> dataTypeList;
    for (unsigned int i = 1; i < keo_datagram::SPINE_DATA_TYPE_COUNT; i++)
    {
        dataTypeList.push_back(SpineDataTypeAsString[i]);
    }
    return dataTypeList;
}
keo_datagram::SpineClassId SpineVersionUtilities::getClassIdFromString(const std::string& c_classIdString)
{
    uint32_t hash = getHashFromString(c_classIdString);
    for (unsigned int i = 0; i < keo_datagram::SPINE_CLASS_ID_COUNT; i++)
    {
        if (hash == SpineClassIdAsHash[i])
        {
            if (c_classIdString.compare(SpineClassIdAsString[i]) == 0)
            {
                return static_cast<SpineClassId>(i);
            }
            return CLASSID_INVALID;
        }
    }
    return CLASSID_INVALID;
}
std::string SpineVersionUtilities::getClassIdAsString(keo_datagram::SpineClassId c_classId)
{
    for (unsigned int i = 0; i < keo_datagram::SPINE_CLASS_ID_COUNT; i++)
    {
        if (c_classId == SpineClassIdAsEnum[i])
        {
            return SpineClassIdAsString[i];
        }
    }
    return SpineClassIdAsString[0];
}
std::vector<std::string> SpineVersionUtilities::getAllClassIds()
{
    std::vector<std::string> classIdList;
    for (unsigned int i = 2; i < keo_datagram::SPINE_CLASS_ID_COUNT; i++)
    {
        classIdList.push_back(SpineClassIdAsString[i]);
    }
    return classIdList;
}
int32_t SpineVersionUtilities::getHashFromString(const std::string& c_string)
{
    std::string::const_iterator iter = c_string.begin();
    std::string::const_iterator iterEnd = c_string.end();
    int32_t returnLong = 0;
    int shift = 0;
    for (; iter != iterEnd; ++iter)
    {
        returnLong += (static_cast<uint16_t>(*iter) << shift);
        if (shift++ > 20)
        {
            shift = 0;
        }
    }
    return returnLong;
}
}
