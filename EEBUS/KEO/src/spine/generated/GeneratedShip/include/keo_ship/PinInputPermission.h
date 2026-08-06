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
 *  @brief PinInputPermission 
 *
 *  @par    This is an automatically generated class
 */


#ifndef __SHIP__PinInputPermission__H__
#define __SHIP__PinInputPermission__H__

/** @addtogroup ShipDataClass
 * @{
 */

#include <string>

namespace keo_ship { 

class PinInputPermission
{
public:

	enum enumPinInputPermission { 
		PININPUTPERMISSION_UNDEFINED__ = -1 
		, PININPUTPERMISSION_OK
		, PININPUTPERMISSION_BUSY
	};

	PinInputPermission()
        : m_data(PININPUTPERMISSION_UNDEFINED__)
    { };

	PinInputPermission(enumPinInputPermission c_data)
        : m_data(c_data)
    { };

	PinInputPermission(const std::string& c_text);

    /** fromString
     * 
     * Function to generate an enum object from string
     * @param string for the enumeration object
	 * @return enumeration object
     */
    static enumPinInputPermission fromString(const std::string& c_text);

    /** setFromString
     * 
     * Function to generate an enum object from string
     * @param string for the enumeration object
     */
    void setFromString(const std::string& c_text);

    /** getData
     * 
     * Return enumeration object
	 * @return enumeration object
     */
	enumPinInputPermission getData() const; 

    /** getDataString
     * 
     * Return enumeration object as string
 	 * @return enumeration object as string
     */
	std::string getDataString() const; 

	
private:
	
	enumPinInputPermission m_data;
	
	// Strings of the enum data type
    static const char* enumString[2]; 
 
};
 
} // end namespace keo_ship
/** @}
 */
#endif
 //__SHIP__PinInputPermission__H__


