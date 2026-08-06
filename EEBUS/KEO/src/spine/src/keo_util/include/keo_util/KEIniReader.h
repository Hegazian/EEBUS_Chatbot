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
 *     @file       KEIniReader.h
 *     @brief      A class for reading standard ini and unix configuration files
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef _KEO_UTIL_KEINIREADER_H_
#define _KEO_UTIL_KEINIREADER_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <list>
#include <map>
#include <sstream>
#include <stdint.h>
#include <string>

/** @ingroup KEToolsLibrary
 * @{
 */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_util
{

/**
 * @class KEIniReader
 * @brief A class for reading standard ini and unix configuration files
 * @ingroup keo_util
 */
class KEIniReader
{
public:
    /**
     */
    KEIniReader();

    /**
     * Destructor
     */
    ~KEIniReader()
    {
    }

    /**
     * Parse the given config file
     * @param filname
     *          Config file to parse
     * @return
     *          true on success, false on file open or parse errors
     */
    bool parse(std::string const& filename);

    /**
     * Get parse error code (line of the error)
     * @return Error code.
     */
    int getLastError(void);

    /**
     * Has a section item
     * @param section
     *          Section where this item belongs to
     * @return
     *          true if available otherwise false
     */
    bool hasSection(std::string const& section) const;

    /**
     * Has a config item
     * @param section
     *          Section where this item belongs to
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          true if available otherwise false
     */
    bool has(std::string const& section, std::string const& name) const;

    /**
     * Has a config item with no/global section
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          true if available otherwise false
     */
    bool has(std::string const& name) const
    {
        return has("", name);
    }

    /**
     * Get a config item
     * @param section
     *          Section where this item belongs to
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    std::string get(std::string const& section, std::string const& name, std::string const& default_value) const;

    /**
     * Get a config item from global section
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    std::string get(std::string const& name, std::string const& default_value) const
    {
        return get("", name, default_value);
    }

    /**
     * Get a config item from global section
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    std::string get(std::string const& name) const
    {
        return get("", name, "");
    }

    /**
     * Get a config item from global section
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    bool getBool(std::string const& section, std::string const& name, bool default_value) const;

    /**
     * Get a config item from global section
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    bool getBool(std::string const& name, bool default_value) const
    {
        return getBool("", name, default_value);
    }

    /**
     * Get a config item from global section
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    bool getBool(std::string const& name) const
    {
        return getBool("", name, false);
    }

    /**
     * Get a config item
     * @param section
     *          Section where this item belongs to
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    template <typename T> T get(std::string const& section, std::string const& name, T const& default_value) const
    {
        T value = default_value;
        if (has(section, name))
        {
            std::istringstream ss(get(section, name, ""));
            ss >> value;
        }
        return value;
    }

    /**
     * Get a config item from global section
     * @param section
     *          Section where this item belongs to
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    template <typename T> T get(std::string const& name, T const& default_value) const
    {
        return get<T>("", name, default_value);
    }

    /**
     * Get a config item from global section
     * @param section
     *          Section where this item belongs to
     * @param name
     *          Name of the item
     * @param default_value
     *          default value fpor this item
     * @return
     *          The value, if item is not available the default_value
     */
    template <typename T> T get(std::string const& name) const
    {
        return get<T>("", name, 0);
    }

    /**
     * Get the list of all available sections
     * @return
     *          The list of sections
     */
    std::list<std::string> getSections(void) const;

    /**
     * Get the list of all available keys of a dedicated section
     * @param section
     *          The section
     *          If no section is given, only keys that are not assigned to a specific section are listed (not all keys).
     * @return
     *          The list of key
     */
    std::list<std::string> getKeys(std::string const& section = "") const;

private:
    static int staticHandler(void* user, const char* section, const char* name, const char* value);

private:
    mutable std::map<std::string, std::map<std::string, std::string> > m_values;

    int m_parseError;
};
}
/** @}
 */

#endif /* _KEO_UTIL_KEINIREADER_H_ */
