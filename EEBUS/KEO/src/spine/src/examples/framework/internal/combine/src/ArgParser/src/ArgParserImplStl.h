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
 *     @brief      Command line argument parser hidden implementation
 *
 *     @par        Command line argument parser (taken from Klaus G., eliminated Qt
 *                 dependency)
 *
 *     @author     KEO GmbH 2013 @n
 *                 All rights reserved !
 */

#ifndef ARGPARSER_IMPL_STL_H_
#define ARGPARSER_IMPL_STL_H_

/** @ingroup KEOToolsLibrary
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <map>
#include <string>
#include <vector>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ArgParserStl.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

namespace keo_tool
{

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */
class CmdArgImplStl;

/**
 * Argument Parser implementation
 */

class ArgParserImplStl
{
public:
    /**
     * Constructor
     */
    ArgParserImplStl(void);

    /**
     * Desctructor
     */
    virtual ~ArgParserImplStl();

    /**
     * Setter for member helpProlog_
     * @param text Value to set
     */
    void setHelpProlog(const std::string& text);

    /**
     * Setter for member helpEpilog_
     * @param text Value to set
     */
    void setHelpEpilog(const std::string& text);

    /**
     * Adds an argument
     * @param shortName Short name, e.g. '-o'
     * @param longName  Long name, e.g. '--output-file'
     * @param help Help string
     * @param type Type of the argument: Flag, Mandatory or Optional
     * @param andRelation List of argument names that needs also to
     *        be passed if this argument is given
     * @param xorRelation List of argument names that must not be passed if this argument is given
     *
     */
    bool addArgument(const std::string& shortName, const std::string& longName, const std::string& help,
        const ArgParserStl::ArgType type, const std::vector<std::string>& andRelation,
        const std::vector<std::string>& xorRelation);

    /**
     * After adding the arguments the function parse needs to be called before querying any argument values
     * If an argument with the same short name is added again the existing will be overwritten
     * @param arguments Arguments as returned by QCoreApplication::arguments()
     * The Argument Parser does not call QCoreApplication::instance()->arguments() on its own
     * @param output A string reference that will contain the output of the parser.
     * The parser does not print anything on its own. It's up to the user to print this message.
     * @return False if an error occurred or if '-h' or '--help' was found, else true.
     * If false is returned the user should take action, e.g. print the output and terminate the program
     */
    bool parse(const std::vector<std::string>& arguments, std::string& output);

    /**
     * Query if a parameter has been given of the command line. This needs to be done after parse() has been called.
     * @param name The short name or the long name of the argument.
     * @return True if the argument was given at the command line, else false.
     */
    bool isDefined(const std::string& name) const;

    /**
     * Query the value of a parameter. This needs to be done after parse() has been called.
     * @param name The short name or the long name of the argument.
     * @return The value of the argument. If the argument was not defined with addArgument()
     * or not given on the command line, an empty string is returned.
     */
    std::string getValue(const std::string& name) const;

    /**
     * Getter for member helpText_
     * @return Returns the value of the member
     */
    std::string getHelpText() const;

private:
    /**
     * Getter for member helpEpilog_
     * @return Returns the value of the member
     */
    std::string getHelpEpilog() const;

    /**
     * Getter for member helpProlog_
     * @return Returns the value of the member
     */
    std::string getHelpProlog() const;

    /**
     * Setter for member helpText_
     * @param helpText Value to set
     */
    void setHelpText(std::string helpText);

    /**
     * Helper that returns if at least one added argument is mandatory
     * @return Has at least one mandatory argument been added?
     */
    bool hasMandatoryArgs() const;

    /**
     * Setter for member hasMandatoryArgs_setHasMandatoryArgs
     * @param text Value to set
     */
    void setHasMandatoryArgs(void);

    /**
     * Helper that returns if at least one added argument is optional
     * @return Has at least one optional argument been added?
     */
    bool hasOptionalArgs() const;

    /**
     * Setter for member hasOptionalArgs_
     * @param text Value to set
     */
    void setHasOptionalArgs(void);

    /**
     * Creates the help string
     * @return The help string
     */
    const std::string generateHelp(void);

    /**
     * Checks if the And Relations are fulfilled
     * @param arg Argument instance to check
     * @param errorText Will contain an error text in case of an error
     * @return True on success, else false
     */
    bool checkForAndRelations(const CmdArgImplStl* pArg, std::string& errorText);

    /**
     * Checks if the Xor Relations are fulfilled
     * @param arg Argument instance to check
     * @param errorText Will contain an error text in case of an error
     * @return True on success, else false
     */
    bool checkForXorRelations(const CmdArgImplStl* pArg, std::string& errorText);

private:
    std::map<std::string, CmdArgImplStl*> m_argMap;
    std::vector<CmdArgImplStl*> m_argPointers;

    std::string m_helpProlog;
    std::string m_helpEpilog;
    std::string m_helpText;
    std::size_t m_longestLongName;
    std::vector<std::string> m_givenArgs;
    bool m_hasMandatoryArgs;
    bool m_hasOptionalArgs;
    const std::string m_valueIndicator;
};
}

/** @}
 * end of file
 */

#endif /* ARGPARSER_IMPL_STL_H_ */
