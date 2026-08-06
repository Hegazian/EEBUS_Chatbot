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
 *     @file       KEIniReader.cpp
 *     @brief      A class for reading standard ini and unix configuration files
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <list>

#include <keo_util/KEIniReader.h>
#include "ini.h"

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
using namespace keo_util;

KEIniReader::KEIniReader()
{
}

bool KEIniReader::parse(std::string const& filename)
{
    m_parseError = ini_parse(filename.c_str(), staticHandler, this);
    return (m_parseError == 0);
}

int KEIniReader::getLastError()
{
    return m_parseError;
}

bool KEIniReader::hasSection(std::string const& section) const
{
    return (m_values.count(section) != 0);
}

bool KEIniReader::has(std::string const& section, std::string const& name) const
{
    if (hasSection(section))
    {
        return (m_values[section].count(name) != 0);
    }
    return false;
}

std::string KEIniReader::get(
    std::string const& section, std::string const& name, std::string const& default_value) const
{
    std::string ret = default_value;
    if (hasSection(section))
    {
        if (has(section, name))
        {
            ret = m_values[section].find(name)->second;
        }
    }
    return ret;
}

bool KEIniReader::getBool(std::string const& section, std::string const& name, bool default_value) const
{
    bool ret = default_value;
    if (hasSection(section))
    {
        if (has(section, name))
        {
            std::string valstr = m_values[section].find(name)->second;

            std::transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);

            if (valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1")
            {
                ret = true;
            }
            else if (valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0")
            {
                ret = false;
            }
        }
    }
    return ret;
}

std::list<std::string> KEIniReader::getSections(void) const
{
    std::map<std::string, std::map<std::string, std::string> >::const_iterator iter;

    std::list<std::string> res;

    for (iter = m_values.begin(); iter != m_values.end(); ++iter)
    {
        res.push_back(iter->first);
    }
    res.unique();
    return res;
}

std::list<std::string> KEIniReader::getKeys(std::string const& section) const
{
    std::list<std::string> res;
    if (hasSection(section))
    {
        std::map<std::string, std::string>::const_iterator iter;
        for (iter = m_values[section].begin(); iter != m_values[section].end(); ++iter)
        {
            res.push_back(iter->first);
        }
    }
    res.unique();
    return res;
}

int KEIniReader::staticHandler(void* user, const char* section, const char* name, const char* value)
{
    KEIniReader* reader = (KEIniReader*)user;
    if (reader->m_values[section][name].size() > 0)
    {
        reader->m_values[section][name] += "\n";
    }
    reader->m_values[section][name] += value;
    return 1;
}
