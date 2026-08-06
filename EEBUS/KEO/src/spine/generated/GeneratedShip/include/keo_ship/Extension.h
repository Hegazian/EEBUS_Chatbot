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
 *  @brief Extension 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__Extension__H__
#define __SHIP__Extension__H__

/** @addtogroup ShipDataClass
 * @{
 */


#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class Extension: definition                                         
 * ****************************************************************************** */
/** Generated class for Extension **/

class Extension : public CShipDataClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	Extension();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_extensionId 
    * @param c_binary 
    * @param c_string 
    */
	Extension ( const xs_string& c_extensionId, const xs_hexBinary& c_binary, const xs_string& c_string);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~Extension ();
	
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

	/** getExtensionId
	* Getter method for data member extensionId
	* @return xs_string: value of the member
	*/
	xs_string getExtensionId(void) const;

	/** getExtensionIdIsSet
	* Getter method to query if data member extensionId is set
	* @return bool: true if extensionId is set, else false
	*/
	bool getExtensionIdIsSet(void) const;

	/** getBinary
	* Getter method for data member binary
	* @return xs_hexBinary: value of the member
	*/
	xs_hexBinary getBinary(void) const;

	/** getBinaryIsSet
	* Getter method to query if data member binary is set
	* @return bool: true if binary is set, else false
	*/
	bool getBinaryIsSet(void) const;

	/** getString
	* Getter method for data member string
	* @return xs_string: value of the member
	*/
	xs_string getString(void) const;

	/** getStringIsSet
	* Getter method to query if data member string is set
	* @return bool: true if string is set, else false
	*/
	bool getStringIsSet(void) const;


	/** setExtensionId
	* Setter method for data member extensionId
	* @param c_value value that will be assigned to the data member
	*/
	void setExtensionId(const xs_string& c_value);

	/** cleanExtensionId
	* Cleaner for the extensionId member
	*/
	void cleanExtensionId(void);

	/** setBinary
	* Setter method for data member binary
	* @param c_value value that will be assigned to the data member
	*/
	void setBinary(const xs_hexBinary& c_value);

	/** cleanBinary
	* Cleaner for the binary member
	*/
	void cleanBinary(void);

	/** setString
	* Setter method for data member string
	* @param c_value value that will be assigned to the data member
	*/
	void setString(const xs_string& c_value);

	/** cleanString
	* Cleaner for the string member
	*/
	void cleanString(void);

private:
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_extensionIdIsSet:1;
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_binaryIsSet:1;
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_stringIsSet:1;

	/** optional elementary data member */
	xs_string m_extensionId;
	/** optional elementary data member */
	xs_hexBinary m_binary;
	/** optional elementary data member */
	xs_string m_string;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__Extension__H__

