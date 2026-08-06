/*
 *     Copyright KEO GmbH 2015 - All rights reserved!
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
 *     @file       KEVersion.cpp
 *     @brief      KEVersion class definition
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */


#include <keo_util/KEVersion.h>
#include <algorithm>
#include <sstream>
#include <string.h>

#include <keo_spineVersion.h>

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_util
{

struct version_item_t
{
    char const* items[6];
};
#define STRINGIFY(x)              #x
#define TOSTRING(x)               STRINGIFY(x)
#define keo_spine_VERSION_STR     TOSTRING(keo_spine_VERSION_MAJOR) "." TOSTRING(keo_spine_VERSION_MINOR) "." TOSTRING(keo_spine_VERSION_REVISION)
static const version_item_t ke_module_version[] = {
    {{ "framework", keo_spine_VERSION_STR,
            keo_spine_VERSION_POSTFIX, keo_spine_VERSION_BUILD_NUMBER, keo_spine_VERSION_VCS_COMMIT_ID, keo_spine_VERSION_GIT_TAG_NAME }},
    {{ "spine",     SPINE_VERSION_STRING,
            SPINE_VERSION_POSTFIX,     keo_spine_VERSION_BUILD_NUMBER, keo_spine_VERSION_VCS_COMMIT_ID, keo_spine_VERSION_GIT_TAG_NAME}},

    {{ NULL, NULL, NULL, NULL, NULL, NULL }}
};

static const char* ke_version_names[] = { "#module", "#version", "#postfix", "#build", "#hash", "#tag" };

KEVersion::KEVersion(const std::string& format)
    : m_format(format)
{
}

std::string KEVersion::ReplaceAll(std::string str, const std::string& from, const std::string& to) const
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

size_t KEVersion::getNumVersions() const
{
    return sizeof(ke_module_version) / sizeof(ke_module_version[0]);
}

std::string KEVersion::getVersionByIndex(size_t i) const
{
    unsigned j;
    std::string result;
    if (i < getNumVersions())
    {
        std::string str(m_format);
        for (j = 0; j < sizeof(ke_version_names) / sizeof(ke_version_names[0]); ++j)
        {
            if (ke_module_version[i].items[j])
            {
                str = ReplaceAll(str, ke_version_names[j], ke_module_version[i].items[j]);
            }
        }
        result.append(str);
    }
    return result;
}

std::string KEVersion::getVersionInfo() const
{
    std::string result;

    int i, j;
    i = j = 0;
    // walk through all versions
    while (ke_module_version[i].items[0] != NULL)
    {
        result.append(getVersionByIndex(i));
        ++i;
    }
    return result;
}

std::string KEVersion::getModuleVersionInfo(const std::string& module) const
{
    std::string result;
    int i, j;
    i = j = 0;
    while (ke_module_version[i].items[0] != NULL)
    {
        if (module.compare(ke_module_version[i].items[0]) == 0)
        {
            return getVersionByIndex(i);
        }
        ++i;
    }
    return std::string();
}
}
