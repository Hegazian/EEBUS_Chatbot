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
 *  @brief MessageProtocolHandshakeError 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__MessageProtocolHandshakeError__H__
#define __SHIP__MessageProtocolHandshakeError__H__

/** @addtogroup ShipDataClass
 * @{
 */


#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class MessageProtocolHandshakeError: definition                                         
 * ****************************************************************************** */
/** Generated class for MessageProtocolHandshakeError **/

class MessageProtocolHandshakeError : public CShipDataClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	MessageProtocolHandshakeError();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_error 
    */
	MessageProtocolHandshakeError ( const xs_unsignedByte& c_error);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~MessageProtocolHandshakeError ();
	
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

	/** getError
	* Getter method for data member error
	* @return xs_unsignedByte: value of the member
	*/
	xs_unsignedByte getError(void) const;

	/** getErrorIsSet
	* Getter method to query if data member error is set
	* @return bool: true if error is set, else false
	*/
	bool getErrorIsSet(void) const;


	/** setError
	* Setter method for data member error
	* @param c_value value that will be assigned to the data member
	*/
	void setError(const xs_unsignedByte& c_value);

	/** cleanError
	* Cleaner for the error member
	*/
	void cleanError(void);

private:
	/** true, if the mandatory elementary data member has been set, else false */
	unsigned char m_errorIsSet:1;

	/** mandatory elementary data member */
	xs_unsignedByte m_error;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__MessageProtocolHandshakeError__H__

