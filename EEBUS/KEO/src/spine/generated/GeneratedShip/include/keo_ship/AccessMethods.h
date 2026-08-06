/*
 *     Copyright KEO GmbH 2014 - All rights reserved!
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
 *
 *     http://docs.eebus.org/ship/exp/V1_0_draft_eV/xsd
 */
/**
 *  @brief AccessMethods 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__AccessMethods__H__
#define __SHIP__AccessMethods__H__

/** @addtogroup ShipDataClass
 * @{
 */


#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class AccessMethods: definition                                         
 * ****************************************************************************** */
/** Generated class for AccessMethods **/

class AccessMethods : public CShipDataClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	AccessMethods();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_id 
    * @param c_dnsSd_mDns 
    * @param c_dns 
    */
	AccessMethods ( const xs_string& c_id, bool c_dnsSd_mDnsIsSet, const xs_string& c_dns);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~AccessMethods ();
	
    /** isSet
     * 
     * Return if all members are set correctly
     * Override the base functionality
     * @return true, if set correctly
     */
	bool isSet(void) const;

    /** getDataType
     * 
     * Return the type of the data class
     * Override the base functionality
     * @return data class enum type
     */
	ShipDataType getDataType(void) const;

    /** getListOfSetMembers
     * 
     * Return a list of numbers that refers to keo_ship::ShipDataMemberNameArray
     * Override the base functionality
     * @return vector of member name number
     */
	std::vector<int32_t> getListOfSetMembers() const;

    /** SetMemberIsSetAndReturnPointer
     * 
     * Return a pointer from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the memberclass enum type
     * @return data class pointer
     */
	CShipDataClass* SetMemberIsSetAndReturnPointer(int c_hashKey);
	
    /** getSimpleMemberAsString
     * 
     * Get the value string from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the memberclass enum type
     * @param r_valueString reference to the output string
     * @return type of string value
     */
	ValueType getSimpleMemberAsString(int c_hashKey, std::string& r_valueString);
	
    /** setSimpleMemberAsString
     * 
     * Return a reference from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the memberclass enum type
     * @param c_stringValue value as string
     * @param c_valueType type of value
     */
	void setSimpleMemberAsString(int c_hashKey, const char* c_stringValue,  ValueType c_valueType);

	/** getId
	* Getter method for data member id
	* @return xs_string: value of the member
	*/
	xs_string getId(void) const;

	/** getIdIsSet
	* Getter method to query if data member id is set
	* @return bool: true if id is set, else false
	*/
	bool getIdIsSet(void) const;

	/** getDnsSd_mDnsIsSet
	* Getter method to query if data member dnsSd_mDns is set
	* @return bool: true if dnsSd_mDns is set, else false
	*/
	bool getDnsSd_mDnsIsSet(void) const;

	/** getDns
	* Getter method for data member dns
	* @return xs_string: value of the member
	*/
	xs_string getDns(void) const;

	/** getDnsIsSet
	* Getter method to query if data member dns is set
	* @return bool: true if dns is set, else false
	*/
	bool getDnsIsSet(void) const;


	/** setId
	* Setter method for data member id
	* @param c_value value that will be assigned to the data member
	*/
	void setId(const xs_string& c_value);

	/** cleanId
	* Cleaner for the id member
	*/
	void cleanId(void);

	/** setDnsSd_mDns
	* Setter method for data member dnsSd_mDns
	*/
	void setDnsSd_mDns();

	/** cleanDnsSd_mDns
	* Cleaner for the dnsSd_mDns member
	*/
	void cleanDnsSd_mDns(void);

	/** setDns
	* Setter method for data member dns
	* @param c_value value that will be assigned to the data member
	*/
	void setDns(const xs_string& c_value);

	/** cleanDns
	* Cleaner for the dns member
	*/
	void cleanDns(void);

private:
	/** true, if the mandatory elementary data member has been set, else false */
	unsigned char m_idIsSet:1;
	/** true, if the dummy data member has been set, else false */
	unsigned char m_dnsSd_mDnsIsSet:1;
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_dnsIsSet:1;

	/** mandatory elementary data member */
	xs_string m_id;
	/** optional elementary data member */
	xs_string m_dns;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__AccessMethods__H__

