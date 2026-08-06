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
 *     @file       KEVersion.h
 *     @brief      KEVersion class declaration
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#ifndef _KEO_UTIL_KEVERSION_H_
#define _KEO_UTIL_KEVERSION_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

#include <map>
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
 * @class KEVersion
 * @brief Accessing Version uinformation of all modules
 *
 * @ingroup keo_util
 */
class KEVersion
{
    /** @brief Default Version string format */
    static constexpr const char* default_format = "#module\t\t#version-#postfix\t(#build - #tag - #hash)\n";
public:
    /**
     * \brief initialize a version info object
     * \param format Format the output string
     *               #module Name
     *               #version Version (1.2.3)
     *               #build Build number
     *               #hash Hash
     *               #tag Tag
     *               Example: "#module: #version-#hash\n" Result: "tools: 1.2.3-abcdef12"
     */
    KEVersion(const std::string& format = default_format);

    /**
     * Destructor
     */
    ~KEVersion()
    {
    }

    /**
     * \brief Get versin info of all used modules
     *        Valid modules: framework, spine
     * \return Formated string of all versions
     */
    std::string getVersionInfo() const;

    /**
     * \brief Get versin info for a dedicated module
     *        Valid modules: framework, spine
     * \param module Name of the Module
     * \return Formated string of the modules version
     */
    std::string getModuleVersionInfo(const std::string& module) const;

private:
    /**
     * \brief Get versin info of all used modules
     * \param index index of the version infmations internal table
     */
    std::string getVersionByIndex(size_t index) const;

    /**
     * \brief Get number of modules/version informations
     * \return  number of version informations
     */
    size_t getNumVersions() const;

    /**
     * \brief Stirng function, replace all occurence of from with the string in to.
     * \return  String with the replaced text.
     */
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) const;

private:
    /**
     * \brief Format configuration
     *               #module Name
     *               #version Version (1.2.3)
     *               #build Build number
     *               #hash Hash
     *               #tag Tag
     *               Example: "#module: #version-#hash\n" Result: "tools: 1.2.3-abcdef12"
     */
    std::string m_format;
};
}

/** @}
 */

#endif /* _KEO_UTIL_KEDate_H_ */
