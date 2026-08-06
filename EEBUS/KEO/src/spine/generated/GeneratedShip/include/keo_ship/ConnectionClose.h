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
 *  @brief ConnectionClose 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__ConnectionClose__H__
#define __SHIP__ConnectionClose__H__

/** @addtogroup ShipDataClass
 * @{
 */

#include "keo_ship/ConnectionClosePhase.h"
#include "keo_ship/ConnectionCloseReason.h"

#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class ConnectionClose: definition                                         
 * ****************************************************************************** */
/** Generated class for ConnectionClose **/

class ConnectionClose : public CShipDataClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	ConnectionClose();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_phase 
    * @param c_maxTime 
    * @param c_reason 
    */
	ConnectionClose ( const ConnectionClosePhase& c_phase, const xs_unsignedInt& c_maxTime, const ConnectionCloseReason& c_reason);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~ConnectionClose ();
	
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

	/** getPhase
	* Getter method for data member phase
	* @return ConnectionClosePhase: value of the member
	*/
	ConnectionClosePhase getPhase(void) const;

	/** getPhaseIsSet
	* Getter method to query if data member phase is set
	* @return bool: true if phase is set, else false
	*/
	bool getPhaseIsSet(void) const;

	/** getMaxTime
	* Getter method for data member maxTime
	* @return xs_unsignedInt: value of the member
	*/
	xs_unsignedInt getMaxTime(void) const;

	/** getMaxTimeIsSet
	* Getter method to query if data member maxTime is set
	* @return bool: true if maxTime is set, else false
	*/
	bool getMaxTimeIsSet(void) const;

	/** getReason
	* Getter method for data member reason
	* @return ConnectionCloseReason: value of the member
	*/
	ConnectionCloseReason getReason(void) const;

	/** getReasonIsSet
	* Getter method to query if data member reason is set
	* @return bool: true if reason is set, else false
	*/
	bool getReasonIsSet(void) const;


	/** setPhase
	* Setter method for data member phase
	* @param c_value value that will be assigned to the data member
	*/
	void setPhase(const ConnectionClosePhase& c_value);

	/** cleanPhase
	* Cleaner for the phase member
	*/
	void cleanPhase(void);

	/** setMaxTime
	* Setter method for data member maxTime
	* @param c_value value that will be assigned to the data member
	*/
	void setMaxTime(const xs_unsignedInt& c_value);

	/** cleanMaxTime
	* Cleaner for the maxTime member
	*/
	void cleanMaxTime(void);

	/** setReason
	* Setter method for data member reason
	* @param c_value value that will be assigned to the data member
	*/
	void setReason(const ConnectionCloseReason& c_value);

	/** cleanReason
	* Cleaner for the reason member
	*/
	void cleanReason(void);

private:
	/** true, if the mandatory enum data member has been set, else false */
	unsigned char m_phaseIsSet:1;
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_maxTimeIsSet:1;
	/** true, if the optional enum data member has been set, else false */
	unsigned char m_reasonIsSet:1;

	/** mandatory enum data member */
	ConnectionClosePhase m_phase;
	/** optional elementary data member */
	xs_unsignedInt m_maxTime;
	/** optional enum data member */
	ConnectionCloseReason m_reason;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__ConnectionClose__H__

