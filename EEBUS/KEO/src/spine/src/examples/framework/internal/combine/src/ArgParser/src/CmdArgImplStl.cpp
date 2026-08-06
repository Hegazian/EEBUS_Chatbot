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
 *     @brief      Separation of of command line arguments
 *
 *     @par        Separation of of command line arguments
 *                 Separate command line arguments and create corresponding objects
 *
 *     @author     KEO GmbH 2013 @n
 *                 All rights reserved !
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <algorithm>

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "ArgParserStl.h"
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

CmdArgImplStl::CmdArgImplStl()
    : m_bFlag(false)
    , m_bOverridingMandatory(false)
    , m_bMandatory(false)
    , m_bDefined(false)
    , m_shortName("    ")
    , m_longName("    ")
{
}

CmdArgImplStl::~CmdArgImplStl()
{
}

bool CmdArgImplStl::isFlag() const
{
    return m_bFlag;
}

void CmdArgImplStl::setFlag(bool flag)
{
    m_bFlag = flag;
}

bool CmdArgImplStl::isOverridingMandatory() const
{
    return m_bOverridingMandatory;
}

void CmdArgImplStl::setOverridingMandatory(void)
{
    m_bOverridingMandatory = true;
}

string CmdArgImplStl::getLongName() const
{
    return m_longName;
}

void CmdArgImplStl::setLongName(const string& longName)
{
    m_longName = longName;
}

string CmdArgImplStl::getShortName() const
{
    return m_shortName;
}

void CmdArgImplStl::setShortName(const string& shortName)
{
    // todo: plausibility checks for leading "-" and length 2
    m_shortName = shortName;
}

string CmdArgImplStl::getHelpText() const
{
    string andText;
    string xorText;

    if (!getAndRelation().empty())
    {
        andText.append("\n");
        andText.append("If this argument is given, the following arguments need also to be given:\n");

        vector<string>::const_iterator iter;
        for (iter = getAndRelation().begin(); iter != getAndRelation().end(); iter++)
        {
            string andArg = *(iter);

            andText.append("  ");
            andText.append(andArg);
            andText.append("\n");
        }
    }

    if (!getXorRelation().empty())
    {
        xorText.append("\n");
        xorText.append("If this argument is given, the following arguments must not be given:\n");
        vector<string>::const_iterator iter;
        for (iter = getXorRelation().begin(); iter != getXorRelation().end(); iter++)
        {
            string xorArg = *(iter);
            xorText.append(xorArg);
            xorText.append("\n");
        }
    }
    return m_helpText + andText + xorText;
}

void CmdArgImplStl::setHelpText(const string& help)
{
    m_helpText = help;
}

string CmdArgImplStl::getValue() const
{
    return m_value;
}

void CmdArgImplStl::setValue(const string& value)
{
    m_value = value;
    m_value.erase(std::remove(m_value.begin(), m_value.end(), '\"'), m_value.end());
    m_value.erase(std::remove(m_value.begin(), m_value.end(), '\''), m_value.end());
}

bool CmdArgImplStl::isDefined() const
{
    return m_bDefined;
}

void CmdArgImplStl::setDefined(bool value)
{
    m_bDefined = value;
}

bool CmdArgImplStl::isMandatory() const
{
    return m_bMandatory;
}

void CmdArgImplStl::setMandatory(const bool mandatory)
{
    m_bMandatory = mandatory;
}

bool CmdArgImplStl::parse(const vector<string>& args, string& errorText)
{
    bool bSuccess = false;
    string arg;
    string removePart;

    int idx;

    // search for the argument with vector<string>.indexOf()
    // start with index 1 because we don't want to parse the program name
    vector<string>::const_iterator iter;

    for (iter = args.begin() + 1, idx = 1; iter != args.end(); iter++, idx++)
    {
        string arg = *(iter);
        if (arg == getShortName())
        {
            removePart = getShortName();
            break;
        }
    }

    if (iter == args.end())
    {
        for (iter = args.begin() + 1, idx = 1; iter != args.end(); iter++, idx++)
        {
            string arg = *(iter);
            if (arg == getLongName())
            {
                removePart = getLongName();
                break;
            }
        }
    }

    if (iter == args.end())
    {
        idx = -1;
        // then vector<string>.indexOf() method cannot be used
        for (int i = 1; i < static_cast<int>(args.size()); ++i)
        {
            if (args.at(i).find(getShortName() + "=") == 0)
            {
                idx = i;
                removePart = getShortName();
                break;
            }
            else if (args.at(i).find(getLongName() + "=") == 0)
            {
                idx = i;
                removePart = getLongName();
                break;
            }
        }
    }

    if (-1 != idx)
    {
        setDefined(true);

        // the argument was given on the command line
        if (isFlag())
        {
            // flags are simple to deal with
            setValue("1");
            bSuccess = true;
        }
        else
        {
            string val = args.at(idx);

            // if an arg is given in the form "-a=value" or "--arg=value"
            // then "-a=" or "--arg=" needs to be removed to find the value part
            val.erase(0, removePart.size());

            // check if the form "--key=value" has been used
            if (val.find('=') == 0)
            {
                val.erase(0, 1);
                if (!val.empty())
                {
                    setValue(val);
                    bSuccess = true;
                }
            }
            // check if the form "--key value" has been used
            // be careful at the end of the list
            else if (idx < static_cast<int>(args.size() - 1))
            {
                val = args.at(idx + 1);
                if ((val.find('-') == string::npos) || (val.find('-') != 0))
                {
                    setValue(val);
                    bSuccess = true;
                }
                else
                {
                    // we don't allow values for negative numbers without the "="
                    errorText = removePart + " invalid value " + val;
                }
            }
            else
            {
                // not found
                errorText = removePart + " value missing";
            }
        }
    }
    else if (isMandatory())
    {
        if (!getShortName().empty())
        {
            errorText = "mandatory argument " + getShortName() + " or " + getLongName() + " missing";
        }
        else
        {
            errorText = "mandatory argument " + getLongName() + " missing";
        }
    }
    else
    {
        if (isFlag())
        {
            // flags are false if not given
            setValue("");
        }

        // optional argument missing: success
        bSuccess = true;
    }

    return bSuccess;
}

vector<string> const& CmdArgImplStl::getAndRelation() const
{
    return m_andRelation;
}

void CmdArgImplStl::setAndRelation(vector<string> andRelation)
{
    this->m_andRelation = andRelation;
}

vector<string> const& CmdArgImplStl::getXorRelation() const
{
    return m_xorRelation;
}

void CmdArgImplStl::setXorRelation(vector<string> xorRelation)
{
    this->m_xorRelation = xorRelation;
}

string CmdArgImplStl::createNameString(void) const
{
    string ret;

    ret.append(getShortName());

    if (!getLongName().empty())
    {
        ret.append(", ");
        ret.append(getLongName());
    }

    return (ret);
}
