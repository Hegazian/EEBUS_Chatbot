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
 *  @brief MessageProtocolFormats 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__MessageProtocolFormats__H__
#define __SHIP__MessageProtocolFormats__H__

/** @addtogroup ShipDataClass
 * @{
 */


#include "keo_ship/CShipListClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class MessageProtocolFormats: definition                                         
 * ****************************************************************************** */
/** Generated class for MessageProtocolFormats **/

class MessageProtocolFormats : public CShipListClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	MessageProtocolFormats();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_format 
    */
	MessageProtocolFormats ( const std::vector<xs_string>& c_format);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~MessageProtocolFormats ();
	
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
     * Return a reference from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the memberclass enum type
     * @return data class reference
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

    /** appendListElement
     * 
     * Append an list element
     * Override the base functionality
     * @param c_stringValue value as string
     */
	void appendListElement(const std::string& c_stringValue);
	
    /** getListElement
     * 
     * Get a list element at its index
     * Override the base functionality
     * @return list element
     */
	xs_string getListElement(uint32_t c_index);

	/** getFormat
	* Getter method for data member format
	* @return std::vector<xs_string>: value of the member
	*/
	std::vector<xs_string> getFormat(void) const;

	/** getFormatIsSet
	* Getter method to query if data member format is set
	* @return bool: true if format is set, else false
	*/
	bool getFormatIsSet(void) const;


	/** setFormat
	* Setter method for data member format
	* @param c_value value that will be assigned to the data member
	*/
	void setFormat(const std::vector<xs_string>& c_value);

	/** cleanFormat
	* Cleaner for the format member
	*/
	void cleanFormat(void);

private:
	/** true, if the mandatory list data member has been set, else false */
	unsigned char m_formatIsSet:1;

	/** mandatory list data member */
	std::vector<xs_string> m_format;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__MessageProtocolFormats__H__

