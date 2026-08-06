/*
 *     Copyright KEO GmbH 2013 - All rights reserved!
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
 */

/**
 *  @brief Ship List Class
 *
 *  @par    Module description
 *          All generated list data classes are derived from this base class
 *
 *  @defgroup ShipDataClass ShipDataClass
 */

#ifndef __SHIP_LISTCLASS_H__
#define __SHIP_LISTCLASS_H__

/** @addtogroup keo_ship_stack
 * @{
 */

#include "keo_ship/CShipDataClass.h"

namespace keo_ship
{

/* ****************************************************************************** *
 *  class CShipListClass: definition                                             *
 * ****************************************************************************** */
class CShipListClass : public CShipDataClass
{
public:
    /** Constructor
     *
     * This method creates an instance of the class.
     */
    CShipListClass();

    /** Empty Destructor
     */
    virtual ~CShipListClass();

    /** Assignment operator
     */
    CShipListClass& operator=(const CShipListClass& c_classObject)
    {
        (void)c_classObject;
        return *this;
    }

    /** isSet
     * Return the set flag
     * @return If the class was set with parameters it return true
     */
    virtual bool isSet(void) const = 0;

    /** getDataType
     * Return the type of the data class
     * @return data class enum type
     */
    virtual ShipDataType getDataType(void) const = 0;

    /** getListOfSetMembers
     *
     * Return a list of numbers that refers to eebus::ShipDataMemberNameArray
     * Override the base functionality
     * @return list of member name number
     */
    std::vector<int32_t> getListOfSetMembers() const = 0;

    /** SetMemberIsSetAndReturnPointer
     *
     * Return a reference from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the member class enum type
     * @return data class reference
     */
    virtual CShipDataClass* SetMemberIsSetAndReturnPointer(int c_hashKey) = 0;

    /** getSimpleMemberAsString
     *
     * Get the value string from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the member class enum type
     * @param r_valueString reference to the output string
     * @return type of string value
     */
    virtual ValueType getSimpleMemberAsString(int c_hashKey, std::string& r_valueString) = 0;

    /** setSimpleMemberAsString
     *
     * Return a reference from the selected member
     * Override the base functionality
     * @param c_hashKey hash value of the member class enum type
     * @param c_stringValue value as string
     * @param c_valueType type of value
     */
    virtual void setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType) = 0;

    /** appendListElement
     *
     * Append an list element
     * Override the base functionality
     * @param c_stringValue value as string
     */
    virtual void appendListElement(const std::string& c_stringValue) = 0;

    /** getListElementPointer
     *
     * Get a list element at its index, NULL if not existing
     * Override the base functionality
     * @return list element
     */
    virtual xs_string getListElement(uint32_t c_index) = 0;
};

} // end namespace keo_ship
/** @}
 */
#endif
