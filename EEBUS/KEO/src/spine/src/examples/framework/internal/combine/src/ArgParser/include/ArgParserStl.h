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
 *     @brief      Command line argument parser
 *
 *     @par        Command line argument parser (taken from Klaus G., eliminated Qt
 *                 dependency)
 *
 *     @author     KEO GmbH 2013 @n
 *                 All rights reserved !
 */

#ifndef ARGPARSER_STL_H_
#define ARGPARSER_STL_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <string>
#include <vector>

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

/** @ingroup KEOToolsLibrary
 * @{
 */

namespace keo_tool
{

/// forward declaration
class ArgParserImplStl;

class ArgParserStl
{
public:
    /**
     * ArgType: FLAG, FLAG_OVERRIDING_MANDATORY, MANDATORY, OPTIONAL.
     * FLAG arguments are true if given on the command line, else false.
     * FLAG_OVERRIDING_MANDATORY arguments override the mandatory flag of other arguments
     * MANDATORY and OPTIONAL arguments need a value, e.g. \"--arg=value\" or \"--arg value\".
     */
    enum ArgType
    {
        FLAG, /// Boolean flag, true if given, else false.
        FLAG_OVERRIDING_MANDATORY, /// Boolean flag, if given, all other arguments are treated as optional (needed for
                                   /// --version)
        MANDATORY, /// Argument with value, mandatory.
        OPTIONAL, /// Argument with value, optional.
    };

public:
    /**
     * Constructor
     */
    ArgParserStl(void);

    /**
     * Desctructor
     */
    virtual ~ArgParserStl();

    /**
     * Sets a string that will appear in the help text before the parameters.
     * @param text The help prolog string.
     *
     */
    void setHelpProlog(std::string const& text);

    /**
     * Sets a string that will appear at the bottom of the help text.
     * @param text The help epilog string.
     *
     */
    void setHelpEpilog(std::string const& text);

    /**
     * Adds an argument.
     * @param shortName Short name, e.g. '-o'. Can be empty if longName is not empty.
     * @param longName  Long name, e.g. '--output-file'.  Can be empty if shortName is not empty.
     * @param help Help string.
     * @param type Type of the argument.
     *
     * The logical correctness of the and and xor relations will not be checked.
     */
    bool addArgument(std::string const& shortName, std::string const& longName, std::string const& help,
        const ArgType type, const std::vector<std::string>& andRelation = std::vector<std::string>(),
        const std::vector<std::string>& xorRelation = std::vector<std::string>());

    /**
     * After adding the arguments the function parse() needs to be called before querying any argument values.
     * @param argc
     *        Number of arguments
     * @param argv
     *        Pointer to argument list
     * @param output
     *        A string reference that will contain the output of the parser.
     *        The parser does not print anything on its own. It's up to the user to print this message.
     * @return
     *        False if an error occurred or if '-h' or '--help' was found, else true.
     *        If false is returned the user should take action, e.g. print the output and terminate the program.
     */
    bool parse(int const argc, char* const argv[], std::string& output);

    /**
     * After adding the arguments the function parse() needs to be called before querying any argument values.
     * @param args
     *        List of arguments
     * @param output
     *        A string reference that will contain the output of the parser.
     *        The parser does not print anything on its own. It's up to the user to print this message.
     * @return
     *        False if an error occurred or if '-h' or '--help' was found, else true.
     *        If false is returned the user should take action, e.g. print the output and terminate the program.
     */
    bool parse(std::vector<std::string> const& args, std::string& output);

    /**
     * Query if a parameter has been given of the command line. This needs to be done after parse() has been called.
     * @param name The short name or the long name of the argument.
     * @return True if the argument was given at the command line, else false.
     */
    bool isDefined(std::string const& name) const;

    /**
     * Query the value of a parameter. This needs to be done after parse() has been called.
     * This function can be called if isDefined() returns true.
     * @param name
     *        The short name or the long name of the argument.
     * @return
     *        The value of the argument. If the argument was not defined with addArgument()
     *        or not given on the command line, an empty string is returned.
     */
    std::string getValue(std::string const& name) const;

    /**
     * Query the help text. Should be called after parse().
     * @return Help text
     */
    std::string getHelpText(void) const;

private:
    /**
     * Pointer to hidden implementation class (pimpl).
     */
    ArgParserImplStl* d;
};
}

#endif /* ARGPARSER_STL_H_ */
