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
 *  @brief ClassDnsSd_mDns 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__ClassDnsSd_mDns__H__
#define __SHIP__ClassDnsSd_mDns__H__

/** @addtogroup ShipDataClass
 * @{
 */


#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class ClassDnsSd_mDns: definition                                         
 * ****************************************************************************** */
/** Generated class for ClassDnsSd_mDns **/

class ClassDnsSd_mDns : public CShipDataClass
{
public:

	/** Constructor
	*
	* This method creates an instance of the class with values.
    */
	ClassDnsSd_mDns ( );   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~ClassDnsSd_mDns ();
	
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


private:

};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__ClassDnsSd_mDns__H__

