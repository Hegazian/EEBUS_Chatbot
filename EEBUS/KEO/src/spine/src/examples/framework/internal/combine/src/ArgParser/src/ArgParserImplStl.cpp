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

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <stdio.h>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ArgParserImplStl.h"
#include "CmdArgImplStl.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */
using namespace std;
using namespace keo_tool;

ArgParserImplStl::ArgParserImplStl(void)
    : m_longestLongName(0)
    , m_hasMandatoryArgs(false)
    , m_hasOptionalArgs(false)
    , m_valueIndicator("=VALUE")
{
}

ArgParserImplStl::~ArgParserImplStl()
{
    // Free allocated memory
    while (!m_argPointers.empty())
    {
        delete *(m_argPointers.begin());
        m_argPointers.erase(m_argPointers.begin());
    }
}

bool ArgParserImplStl::addArgument(const string& shortName, const string& longName, const string& help,
    const ArgParserStl::ArgType type, const vector<string>& andRelation, const vector<string>& xorRelation)
{
    bool ret = true;
    CmdArgImplStl* arg;

    // Check short name or long name have already been used
    // or if both, short name and long name are empty
    if (!shortName.empty() && m_argMap.find(shortName) != m_argMap.end())
    {
        ret = false;
    }
    else if (!longName.empty() && m_argMap.find(longName) != m_argMap.end())
    {
        ret = false;
    }
    else if (shortName.empty() && longName.empty())
    {
        ret = false;
    }

    if (ret)
    {
        // Instantiate a new arg class
        arg = new CmdArgImplStl();

        m_argPointers.push_back(arg);
        arg->setShortName(shortName);
        arg->setLongName(longName);

        // Add it to the map with short name as key
        if (!shortName.empty())
        {
            m_argMap.insert(std::pair<std::string, CmdArgImplStl*>(shortName, arg));
        }

        // Add it to the map with short name as key
        if (!longName.empty())
        {
            m_argMap.insert(std::pair<std::string, CmdArgImplStl*>(longName, arg));
        }

        arg->setFlag((type == ArgParserStl::FLAG) || (type == ArgParserStl::FLAG_OVERRIDING_MANDATORY));

        if (type == ArgParserStl::FLAG_OVERRIDING_MANDATORY)
        {
            arg->setOverridingMandatory();
        }

        // keep track of the longest name in order to format help properly
        size_t currLength = longName.length();

        if (!arg->isFlag())
        {
            currLength += m_valueIndicator.length();
        }

        if (currLength > m_longestLongName)
        {
            m_longestLongName = currLength;
        }

        arg->setHelpText(help);

        // It does not make sense to define a mandatory flag
        // But we leave this to the user ...
        bool bIsMandatory = (type == ArgParserStl::MANDATORY);
        arg->setMandatory(bIsMandatory);
        if (bIsMandatory)
        {
            setHasMandatoryArgs();
        }
        else
        {
            setHasOptionalArgs();
        }

        arg->setAndRelation(andRelation);
        arg->setXorRelation(xorRelation);
    }

    return (ret);
}

bool ArgParserImplStl::checkForAndRelations(const CmdArgImplStl* pArg, string& errorText)
{
    bool ret = true;

    vector<string>::const_iterator iter;
    vector<string> andRelation = pArg->getAndRelation();

    for (iter = andRelation.begin(); iter != andRelation.end(); iter++)
    {
        string andArgName = *(iter);

        if (m_argMap.find(andArgName) != m_argMap.end())
        {
            CmdArgImplStl* andArg = m_argMap[andArgName];
            if (pArg->isDefined() && !andArg->isDefined())
            {
                errorText.append("Error:\n");
                errorText.append(pArg->createNameString());
                errorText.append("  must be used together with ");
                errorText.append(andArgName);

                ret = false;
            }
        }
        else
        {
            // The application needs to be fixed
            errorText.append("Error:\n");
            errorText.append(pArg->createNameString());
            errorText.append("  : and related argument ");
            errorText.append(andArgName);
            errorText.append(" does not exist. This application needs to be fixed.");

            ret = false;
        }
    }

    return (ret);
}

bool ArgParserImplStl::checkForXorRelations(const CmdArgImplStl* pArg, string& errorText)
{
    bool ret = true;

    vector<string>::const_iterator iter;
    vector<string> xorRelation = pArg->getXorRelation();

    for (iter = xorRelation.begin(); iter != xorRelation.end(); iter++)
    {
        string xorArgName = (*iter);
        if (m_argMap.find(xorArgName) != m_argMap.end())
        {
            CmdArgImplStl* xorArg = m_argMap[xorArgName];

            if (pArg->isDefined() && xorArg->isDefined())
            {
                errorText.append("Error:\n");
                errorText.append(pArg->createNameString());
                errorText.append("  must not be used together with ");
                errorText.append(xorArgName);

                ret = false;
            }
        }
        else
        {
            // The application needs to be fixed
            errorText.append("Error:\n");
            errorText.append(pArg->createNameString());
            errorText.append("  : xor related argument ");
            errorText.append(xorArgName);
            errorText.append(" does not exist. This application needs to be fixed.");

            ret = false;
        }
    }

    return (ret);
}

bool ArgParserImplStl::parse(const vector<string>& arguments, string& output)
{
    bool bNeedToPrintHelp = false;
    m_givenArgs = arguments;

    output = "";

    // Don't deal with no args
    if (m_argMap.size() > 0)
    {

        // Scan for '-h' or '--help'
        if (m_givenArgs.size() > 1)
        {
            string firstArg = m_givenArgs.at(1);
            if ((firstArg.find("-h") == 0) || (firstArg.find("--help") == 0))
            {
                bNeedToPrintHelp = true;
            }
        }

        // Only go through the arguments if not only help was requested
        if (!bNeedToPrintHelp)
        {
            bool bFoundOverridingMandatory = false;

            // Iterate over all added arguments
            vector<CmdArgImplStl*>::const_iterator iter;
            for (iter = m_argPointers.begin(); iter != m_argPointers.end(); iter++)
            {
                CmdArgImplStl* arg = *(iter);
                string ignored;
                arg->parse(m_givenArgs, ignored);

                if (arg->isDefined() && arg->isOverridingMandatory())
                {
                    bFoundOverridingMandatory = true;
                }
            }

            if (bFoundOverridingMandatory)
            {
                vector<CmdArgImplStl*>::const_iterator iter_;
                for (iter_ = m_argPointers.begin(); iter_ != m_argPointers.end(); iter_++)
                {
                    CmdArgImplStl* arg = *(iter_);
                    arg->setMandatory(false);
                    arg->setAndRelation(vector<string>());
                    arg->setXorRelation(vector<string>());
                }
            }

            // Iterate over all added arguments
            vector<CmdArgImplStl*>::const_iterator iter_;
            for (iter_ = m_argPointers.begin(); iter_ != m_argPointers.end(); iter_++)
            {
                CmdArgImplStl* arg = *(iter_);
                string errorText;
                if (!arg->parse(m_givenArgs, errorText))
                {
                    output.append("Invalid argument: " + errorText + "\n");
                    bNeedToPrintHelp = true;
                }
            }
        }

        // If no error so far,check for the relations
        if (!bNeedToPrintHelp)
        {
            // Iterate over all added arguments
            vector<CmdArgImplStl*>::const_iterator iter_;
            for (iter_ = m_argPointers.begin(); iter_ != m_argPointers.end(); iter_++)
            {
                CmdArgImplStl* arg = *(iter_);
                string errorText;
                if (!checkForAndRelations(arg, errorText))
                {
                    output.append(errorText + "\n");
                    bNeedToPrintHelp = true;
                }

                if (!checkForXorRelations(arg, errorText))
                {
                    output.append(errorText + "\n");
                    bNeedToPrintHelp = true;
                }
            }
        }

        generateHelp();

        // Add help to output if needed
        if (bNeedToPrintHelp)
        {
            output.append(getHelpText());
        }
    }

    return (!bNeedToPrintHelp);
}

bool ArgParserImplStl::isDefined(const string& name) const
{
    bool ret = false;
    map<string, CmdArgImplStl*>::const_iterator iter;
    iter = m_argMap.find(name);
    if (iter != m_argMap.end())
    {
        ret = iter->second->isDefined();
    }
    return ret;
}

string ArgParserImplStl::getValue(const string& name) const
{
    // Return empty string if argument was not given

    string ret = "";
    map<string, CmdArgImplStl*>::const_iterator iter;
    iter = m_argMap.find(name);
    if (iter != m_argMap.end())
    {
        ret = iter->second->getValue();
    }
    return ret;
}

void ArgParserImplStl::setHelpProlog(const string& text)
{
    m_helpProlog = text;
}

void ArgParserImplStl::setHelpEpilog(const string& text)
{
    m_helpEpilog = text;
}

string ArgParserImplStl::getHelpEpilog() const
{
    return m_helpEpilog;
}

string ArgParserImplStl::getHelpProlog() const
{
    return m_helpProlog;
}

string ArgParserImplStl::getHelpText() const
{
    return m_helpText;
}

void ArgParserImplStl::setHelpText(string helpText)
{
    m_helpText = helpText;
}

const string ArgParserImplStl::generateHelp(void)
{
    string name = m_givenArgs.at(0);
    string mandatoryPart;
    string mandatoryArgs;
    string tmpHelp;

    // Put the required parts into the help string
    if (hasMandatoryArgs())
    {
        mandatoryPart = "\nMandatory arguments:\n";
        mandatoryArgs = " mandatoryArguments";
    }

    string optionalPart;
    string optionalArgs;

    if (hasOptionalArgs())
    {
        optionalPart = "\nOptional arguments:\n";
        optionalArgs = " [optionalArguments]";
    }

    // Start with the "Usage" line
    tmpHelp.append("\nUsage:\n" + name + mandatoryArgs + optionalArgs + "\n");
    if (!getHelpProlog().empty())
    {
        tmpHelp.append("\n" + getHelpProlog() + "\n");
    }

    vector<CmdArgImplStl*>::const_iterator iter;
    for (iter = m_argPointers.begin(); iter != m_argPointers.end(); iter++)
    {
        CmdArgImplStl* arg = *(iter);
        string argHelp = arg->getHelpText();
        string helpText("  ");

        if (!arg->getShortName().empty())
        {
            helpText.append(arg->getShortName());
            helpText.append(", ");
        }
        else
        {
            helpText.append("    ");
        }

        string longName = arg->getLongName();
        if (!arg->isFlag())
        {
            longName.append(m_valueIndicator);
        }

        // Format according to the longest long name
        helpText.append(longName);
        helpText.append(m_longestLongName - longName.size(), ' ');
        helpText.append("   ");

        // reformat line breaks
        string repl;
        repl = '\n';
        repl.append(helpText.size(), ' ');

        size_t pos = 0;
        while ((pos = argHelp.find('\n', pos)) != string::npos)
        {
            argHelp.replace(pos, 1, repl.c_str());
            pos++;
        }

        helpText.append(argHelp);

        // Store the line for the argument in the appropriate intermediate string
        if (arg->isMandatory())
        {
            mandatoryPart.append(helpText + "    \n");
        }
        else
        {
            optionalPart.append(helpText + "    \n");
        }
    }

    // Put the pieces together
    tmpHelp.append(mandatoryPart);
    tmpHelp.append(optionalPart);
    if (!getHelpEpilog().empty())
    {
        tmpHelp.append("\n" + getHelpEpilog() + "\n");
    }

    setHelpText(tmpHelp);

    return (getHelpText());
}

bool ArgParserImplStl::hasMandatoryArgs() const
{
    return m_hasMandatoryArgs;
}

void ArgParserImplStl::setHasMandatoryArgs(void)
{
    m_hasMandatoryArgs = true;
}

bool ArgParserImplStl::hasOptionalArgs() const
{
    return m_hasOptionalArgs;
}

void ArgParserImplStl::setHasOptionalArgs(void)
{
    m_hasOptionalArgs = true;
}
