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
 *  @brief ConnectionHello 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__ConnectionHello__H__
#define __SHIP__ConnectionHello__H__

/** @addtogroup ShipDataClass
 * @{
 */

#include "keo_ship/ConnectionHelloPhase.h"

#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 

/* ****************************************************************************** *
 *  class ConnectionHello: definition                                         
 * ****************************************************************************** */
/** Generated class for ConnectionHello **/

class ConnectionHello : public CShipDataClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	ConnectionHello();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_phase 
    * @param c_waiting 
    * @param c_prolongationRequest true=request waiting prolongation
    */
explicit ConnectionHello ( const ConnectionHelloPhase& c_phase, const xs_unsignedInt& c_waiting, const xs_boolean& c_prolongationRequest);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~ConnectionHello ();
	
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
	* @return ConnectionHelloPhase: value of the member
	*/
	ConnectionHelloPhase getPhase(void) const;

	/** getPhaseIsSet
	* Getter method to query if data member phase is set
	* @return bool: true if phase is set, else false
	*/
	bool getPhaseIsSet(void) const;

	/** getWaiting
	* Getter method for data member waiting
	* @return xs_unsignedInt: value of the member
	*/
	xs_unsignedInt getWaiting(void) const;

	/** getWaitingIsSet
	* Getter method to query if data member waiting is set
	* @return bool: true if waiting is set, else false
	*/
	bool getWaitingIsSet(void) const;

	/** getProlongationRequest
	* Getter method for data member prolongationRequest
	* @return xs_boolean: value of the member
	*/
	xs_boolean getProlongationRequest(void) const;

	/** getProlongationRequestIsSet
	* Getter method to query if data member prolongationRequest is set
	* @return bool: true if prolongationRequest is set, else false
	*/
	bool getProlongationRequestIsSet(void) const;


	/** setPhase
	* Setter method for data member phase
	* @param c_value value that will be assigned to the data member
	*/
	void setPhase(const ConnectionHelloPhase& c_value);

	/** cleanPhase
	* Cleaner for the phase member
	*/
	void cleanPhase(void);

	/** setWaiting
	* Setter method for data member waiting
	* @param c_value value that will be assigned to the data member
	*/
	void setWaiting(const xs_unsignedInt& c_value);

	/** cleanWaiting
	* Cleaner for the waiting member
	*/
	void cleanWaiting(void);

	/** setProlongationRequest
	* Setter method for data member prolongationRequest
	* @param c_value value that will be assigned to the data member
	*/
	void setProlongationRequest(const xs_boolean& c_value);

	/** cleanProlongationRequest
	* Cleaner for the prolongationRequest member
	*/
	void cleanProlongationRequest(void);

private:
	/** true, if the mandatory enum data member has been set, else false */
	unsigned char m_phaseIsSet:1;
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_waitingIsSet:1;
	/** optional elementary data member */
	unsigned char m_prolongationRequest:1;
	/** true, if the optional elementary data member has been set, else false */
	unsigned char m_prolongationRequestIsSet:1;

	/** mandatory enum data member */
	ConnectionHelloPhase m_phase;
	/** optional elementary data member */
	xs_unsignedInt m_waiting;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__ConnectionHello__H__

