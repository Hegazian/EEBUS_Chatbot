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
 *  @brief MessageProtocolHandshake 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__MessageProtocolHandshake__H__
#define __SHIP__MessageProtocolHandshake__H__

/** @addtogroup ShipDataClass
 * @{
 */

#include "keo_ship/ProtocolHandshakeType.h"
#include "keo_ship/ClassVersion.h"
#include "keo_ship/MessageProtocolFormats.h"

#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 
// Class forward declarations
class ClassVersion;
class MessageProtocolFormats;

/* ****************************************************************************** *
 *  class MessageProtocolHandshake: definition                                         
 * ****************************************************************************** */
/** Generated class for MessageProtocolHandshake **/

class MessageProtocolHandshake : public CShipDataClass
{
public:

	/** Simple Constructor
	*
	* This method creates an instance of the class.
	*/
	MessageProtocolHandshake();

	/** Constructor
	*
	* This method creates an instance of the class with values.
    * @param c_handshakeType 
    * @param c_version 
    * @param c_formats 
    */
	MessageProtocolHandshake ( const ProtocolHandshakeType& c_handshakeType, const ClassVersion& c_version, const MessageProtocolFormats& c_formats);   


    /** Desctructor
    * Empty destructor.
    */
	virtual ~MessageProtocolHandshake ();
	
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

	/** getHandshakeType
	* Getter method for data member handshakeType
	* @return ProtocolHandshakeType: value of the member
	*/
	ProtocolHandshakeType getHandshakeType(void) const;

	/** getHandshakeTypeIsSet
	* Getter method to query if data member handshakeType is set
	* @return bool: true if handshakeType is set, else false
	*/
	bool getHandshakeTypeIsSet(void) const;

	/** getVersion
	* Getter method for data member version
	* @return ClassVersion: value of the member
	*/
	ClassVersion getVersion(void) const;

	/** getVersionIsSet
	* Getter method to query if data member version is set
	* @return bool: true if version is set, else false
	*/
	bool getVersionIsSet(void) const;

	/** getFormats
	* Getter method for data member formats
	* @return MessageProtocolFormats: value of the member
	*/
	MessageProtocolFormats getFormats(void) const;

	/** getFormatsIsSet
	* Getter method to query if data member formats is set
	* @return bool: true if formats is set, else false
	*/
	bool getFormatsIsSet(void) const;


	/** setHandshakeType
	* Setter method for data member handshakeType
	* @param c_value value that will be assigned to the data member
	*/
	void setHandshakeType(const ProtocolHandshakeType& c_value);

	/** cleanHandshakeType
	* Cleaner for the handshakeType member
	*/
	void cleanHandshakeType(void);

	/** setVersion
	* Setter method for data member version
	* @param c_value value that will be assigned to the data member
	*/
	void setVersion(const ClassVersion& c_value);

	/** cleanVersion
	* Cleaner for the version member
	*/
	void cleanVersion(void);

	/** setFormats
	* Setter method for data member formats
	* @param c_value value that will be assigned to the data member
	*/
	void setFormats(const MessageProtocolFormats& c_value);

	/** cleanFormats
	* Cleaner for the formats member
	*/
	void cleanFormats(void);

private:
	/** true, if the mandatory enum data member has been set, else false */
	unsigned char m_handshakeTypeIsSet:1;
	/** true, if the mandatory data member has been set, else false */
	unsigned char m_versionIsSet:1;
	/** true, if the mandatory data member has been set, else false */
	unsigned char m_formatsIsSet:1;

	/** mandatory enum data member */
	ProtocolHandshakeType m_handshakeType;
	/** mandatory data member */
	ClassVersion m_version;
	/** mandatory data member */
	MessageProtocolFormats m_formats;


};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__MessageProtocolHandshake__H__

