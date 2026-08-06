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
 *
 */
/**
 *  @brief Data
 *
 *  @par    This is an automatically generated class
 */

#ifndef __SHIP__Data__H__
#define __SHIP__Data__H__

/** @addtogroup keo_ship_stack
 * @{
 */

#include "keo_ship/Extension.h"
#include "keo_ship/Header.h"

#include "keo_ship/CShipDataClass.h"

namespace keo_ship
{
// Class forward declarations
class Header;
class Extension;

class Payload
{
public:
    /** Simple Constructor
    *
    * This method creates an instance of the class.
    */
    Payload();

    /** Desctructor
    * Empty destructor.
    */
    virtual ~Payload();

    void setPayload(std::vector<char>& p);

    std::vector<char> getPayload(void) const;

private:
    std::vector<char> m_payload;
};

/* ****************************************************************************** *
 *  class Data: definition
 * ****************************************************************************** */
/** Generated class for Data **/

class Data : public CShipDataClass
{
public:
    /** Simple Constructor
    *
    * This method creates an instance of the class.
    */
    Data();

    /** Constructor
    *
    * This method creates an instance of the class with values.
    * @param c_header
    * @param c_payload
    * @param c_extension
    */
    Data(const Header& c_header, const Payload& c_payload, const Extension& c_extension);

    /** Desctructor
    * Empty destructor.
    */
    virtual ~Data();

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
     * @param c_hashKey hash value of the member class enum type
     * @return data class pointer
     */
    CShipDataClass* SetMemberIsSetAndReturnPointer(int c_hashKey);

    /** getSimpleMemberAsString
     *
     * Get the value string from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the member class enum type
     * @param r_valueString reference to the output string
     * @return type of string value
     */
    ValueType getSimpleMemberAsString(int c_hashKey, std::string& r_valueString);

    /** setSimpleMemberAsString
     *
     * Return a reference from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the member class enum type
     * @param c_stringValue value as string
     * @param c_valueType type of value
     */
    void setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType);

    /** getHeader
    * Getter method for data member header
    * @return Header: value of the member
    */
    Header getHeader(void) const;

    /** getHeaderIsSet
    * Getter method to query if data member header is set
    * @return bool: true if header is set, else false
    */
    bool getHeaderIsSet(void) const;

    /** setHeader
    * Setter method for data member header
    * @param c_value value that will be assigned to the data member
    */
    void setHeader(const Header& c_value);

    /** cleanHeader
    * Cleaner for the header member
    */
    void cleanHeader(void);

    /** getPayload
    * Getter method for payload
    * @return JSON payload
    */
    Payload getPayload(void) const;

    /** setPayload
    * Setter method for the payload
    * @param c_payload value that will be assigned to the payload
    */
    void setPayload(const Payload& c_payload);

    /** cleanPayload
    * Cleaner for the payload member
    */
    void cleanPayload(void);

    /** getExtension
    * Getter method for data member extension
    * @return Extension: value of the member
    */
    Extension getExtension(void) const;

    /** getExtensionIsSet
    * Getter method to query if data member extension is set
    * @return bool: true if extension is set, else false
    */
    bool getExtensionIsSet(void) const;

    /** setExtension
    * Setter method for data member extension
    * @param c_value value that will be assigned to the data member
    */
    void setExtension(const Extension& c_value);

    /** cleanExtension
    * Cleaner for the extension member
    */
    void cleanExtension(void);

private:
    /** true, if the mandatory data member has been set, else false */
    unsigned char m_headerIsSet;
    /** true, if the optional data member has been set, else false */
    unsigned char m_extensionIsSet;
    /** mandatory data member */
    Header m_header;
    /** mandatory payload */
    Payload m_payload;
    /** optional data member */
    Extension m_extension;
};

} // end namespace keo_ship
/** @}
 */
#endif //__SHIP__Data__H__
