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
 *     @brief      Argument Parser
 *
 *     @par        Module description
 *                 An argument parser for Qt
 *
 *     @ifnot change_history
 *
 *     @author     KEO GmbH 2013 @n
 *                 All rights reserved !
 *
 *     @else
 *
 *     @par        Change history
 *
 *     @author     Klaus Gysbers
 *     @date       2013-06-06
 *     @version    01.00.00
 *     @n          Initial version
 *
 *
 *     @endif
 */

/** @ingroup KEToolsLibrary
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ArgParser.h"
#include "ArgParserImpl.h"

/* ****************************************************************************** *
 *  class ArgParser: implementation                                               *
 * ****************************************************************************** */

ArgParser::ArgParser()
{
    d = new ArgParserImpl();
}

ArgParser::~ArgParser()
{
    if (d)
    {
        delete d;
    }

    d = NULL;
}

bool ArgParser::addArgument(const QString& shortName, const QString& longName, const QString& help, const ArgType type,
    const QStringList& andRelation, const QStringList& xorRelation)
{
    return (d->addArgument(shortName, longName, help, type, andRelation, xorRelation));
}

void ArgParser::setHelpProlog(const QString& text)
{
    d->setHelpProlog(text);
}

void ArgParser::setHelpEpilog(const QString& text)
{
    d->setHelpEpilog(text);
}

bool ArgParser::parse(const QStringList& args, QString& output)
{
    return (d->parse(args, output));
}

bool ArgParser::isDefined(const QString& name) const
{
    return d->isDefined(name);
}

QVariant ArgParser::getValue(const QString& name) const
{
    return d->getValue(name);
}

QString ArgParser::getHelpText(void) const
{
    return d->getHelpText();
}

/** @}
 * end of file
 */
