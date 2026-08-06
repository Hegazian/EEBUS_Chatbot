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

#ifndef CMDARGIMPL_H_
#define CMDARGIMPL_H_

/** @ingroup KEOToolsLibrary
 * @{
 */

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

namespace keo_tool
{

class CmdArgImplStl
{
public:
    /**
     * Constructor
     */
    CmdArgImplStl();

    /**
     * Desctructor
     */
    virtual ~CmdArgImplStl();

    /**
     * Getter for member bFlag_
     * @return Returns the value of the member
     */
    bool isFlag() const;

    /**
     * Setter for member bFlag_
     * @param flag Value to set
     */
    void setFlag(bool flag);

    /**
     * Setter for member bOverridingMandatory_
     */
    void setOverridingMandatory(void);

    /**
     * Getter for property is overriding mandatory
     * @return Returns true if this argument overrides the mandatory
     * property of all other arguments (e.g. for --version)
     */
    bool isOverridingMandatory() const;

    /**
     * Getter for member longName_
     * @return Returns the value of the member
     */
    std::string getLongName() const;

    /**
     * Setter for member longName_
     * @param longName Value to set
     */
    void setLongName(const std::string& longName);

    /**
     * Getter for member shortName_
     * @return Returns the value of the member
     */
    std::string getShortName() const;

    /**
     * Setter for member longName_
     * @param shortName Value to set
     */
    void setShortName(const std::string& shortName);

    /**
     * Getter for member helpText_
     * @return Returns the value of the member
     */
    std::string getHelpText() const;

    /**
     * Setter for member helpText_
     * @param help Value to set
     */
    void setHelpText(const std::string& help);

    /**
     * Getter for member value_
     * @return Returns the value of the member
     */
    std::string getValue() const;

    /**
     * Setter for member value_
     * @param value Value to set
     */
    void setValue(const std::string& value);

    /**
     * Getter for member defined_
     * @return Returns the value of the member
     */
    bool isDefined() const;

    /**
     * Setter for member defined_
     * @param value Value to set
     */
    void setDefined(bool value);

    /**
     * Getter for member bMandatory_
     * @return Returns the value of the member
     */
    bool isMandatory() const;

    /**
     * Setter for member bMandatory_
     * @param mandatory Value to set
     */
    void setMandatory(const bool mandatory);

    /**
     * Parses the arguments for itself
     * @param args Arguments to parse as returned be QCoreApplication::arguments()
     * @param errorText Will contain an error text in case of an error
     * @return True on success, else false
     */
    bool parse(const std::vector<std::string>& args, std::string& errorText);

    /**
     * Getter for member andRelation_
     * @return Returns the value of the member
     */
    std::vector<std::string> const& getAndRelation() const;

    /**
     * Setter for member andRelation_
     * @param andRelation Value to set
     */
    void setAndRelation(std::vector<std::string> andRelation);

    /**
     * Getter for member xorRelation_
     * @return Returns the value of the member
     */
    std::vector<std::string> const& getXorRelation() const;

    /**
     * Setter for member xorRelation_
     * @param xorRelation Value to set
     */
    void setXorRelation(std::vector<std::string> xorRelation);

    /**
     * Small helper that returns a string consisting of short name and long name
     * @return Name string
     */
    std::string createNameString(void) const;

private:
    bool m_bFlag;
    bool m_bOverridingMandatory;
    bool m_bMandatory;
    bool m_bDefined;
    std::string m_shortName;
    std::string m_longName;
    std::string m_helpText;
    std::string m_value;
    std::vector<std::string> m_andRelation;
    std::vector<std::string> m_xorRelation;
};
}

/** @}
 * end of file
 */

#endif /* CMDARGIMPL_H_ */
