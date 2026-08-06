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

/** @ingroup KEOToolsLibrary
 * @{
 */

/**
 *     @brief      Argument Parser Implementation
 *
 *     @par        Module description
 *                 An argument parser for Qt
 *
 *     @author     KEO GmbH 2013 @n
 *                 All rights reserved !
 */

#ifndef ARGPARSERIMPL_H_
#define ARGPARSERIMPL_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ArgParser.h"
#include "CmdArgImpl.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class ArgParserImpl: definition                                               *
 * ****************************************************************************** */

class ArgParser::ArgParserImpl
{
public:
    /**
     * Constructor
     */
    ArgParserImpl(void);

    /**
     * Desctructor
     */
    virtual ~ArgParserImpl();

    /**
     * Setter for member helpProlog_
     * @param text Value to set
     */
    void setHelpProlog(const QString& text);

    /**
     * Setter for member helpEpilog_
     * @param text Value to set
     */
    void setHelpEpilog(const QString& text);

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
    bool addArgument(const QString& shortName, const QString& longName, const QString& help,
        const ArgParser::ArgType type, const QStringList& andRelation, const QStringList& xorRelation);

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
    bool parse(const QStringList& arguments, QString& output);

    /**
     * Query if a parameter has been given of the command line. This needs to be done after parse() has been called.
     * @param name The short name or the long name of the argument.
     * @return True if the argument was given at the command line, else false.
     */
    bool isDefined(const QString& name) const;

    /**
     * Query the value of a parameter. This needs to be done after parse() has been called.
     * @param name The short name or the long name of the argument.
     * @return The value of the argument. If the argument was not defined with addArgument()
     * or not given on the command line, a QVariant() is returned.
     */
    QVariant getValue(const QString& name) const;

    /**
     * Getter for member helpText_
     * @return Returns the value of the member
     */
    QString getHelpText() const;

private:
    /**
     * Getter for member helpEpilog_
     * @return Returns the value of the member
     */
    QString getHelpEpilog() const;

    /**
     * Getter for member helpProlog_
     * @return Returns the value of the member
     */
    QString getHelpProlog() const;

    /**
     * Setter for member helpText_
     * @param helpText Value to set
     */
    void setHelpText(QString helpText);

    /**
     * Helper that returns if at least one added argument is mandatory
     * @return Has at least one mandatory argument been added?
     */
    bool hasMandatoryArgs() const;

    /**
     * Setter for member hasMandatoryArgs_
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
    const QString generateHelp(void);

    /**
     * Checks if the And Relations are fulfilled
     * @param arg Argument instance to check
     * @param errorText Will contain an error text in case of an error
     * @return True on success, else false
     */
    bool checkForAndRelations(const CmdArgImpl* pArg, QString& errorText);

    /**
     * Checks if the Xor Relations are fulfilled
     * @param arg Argument instance to check
     * @param errorText Will contain an error text in case of an error
     * @return True on success, else false
     */
    bool checkForXorRelations(const CmdArgImpl* pArg, QString& errorText);

private:
    QMap<QString, CmdArgImpl*> m_argMap;
    QList<CmdArgImpl*> m_argPointers;

    QString m_helpProlog;
    QString m_helpEpilog;
    QString m_helpText;
    int m_longestLongName;
    QStringList m_givenArgs;
    bool m_hasMandatoryArgs;
    bool m_hasOptionalArgs;
    const QString m_valueIndicator;
};

#endif /* ARGPARSERIMPL_H_ */

/** @}
 * end of file
 */
