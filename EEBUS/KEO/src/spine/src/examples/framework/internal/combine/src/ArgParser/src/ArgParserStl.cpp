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

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ArgParserStl.h"
#include "ArgParserImplStl.h"

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

ArgParserStl::ArgParserStl()
{
    d = new ArgParserImplStl();
}

ArgParserStl::~ArgParserStl()
{
    if (d)
    {
        delete d;
    }

    d = 0;
}

bool ArgParserStl::addArgument(const string& shortName, const string& longName, const string& help, const ArgType type,
    const vector<string>& andRelation, const vector<string>& xorRelation)
{
    return (d->addArgument(shortName, longName, help, type, andRelation, xorRelation));
}

void ArgParserStl::setHelpProlog(const string& text)
{
    d->setHelpProlog(text);
}

void ArgParserStl::setHelpEpilog(const string& text)
{
    d->setHelpEpilog(text);
}

bool ArgParserStl::parse(const int argc, char* const argv[], string& output)
{
    bool ret = false;
    if (argv != 0)
    {
        vector<string> args;
        for (int i = 0; i < argc; i++)
        {
            args.push_back(argv[i]);
        }

        ret = parse(args, output);
    }
    return (ret);
}

bool ArgParserStl::parse(vector<string> const& args, string& output)
{
    return (d->parse(args, output));
}

bool ArgParserStl::isDefined(const string& name) const
{
    return d->isDefined(name);
}

string ArgParserStl::getValue(const string& name) const
{
    return d->getValue(name);
}

string ArgParserStl::getHelpText(void) const
{
    return d->getHelpText();
}
