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
 */

/**
 *  @brief Ship Data Class
 *
 *  @par    Module description
 *          All generated data classes are derived from this base class
 *
 */

#include "keo_ship/CShipListClass.h"

using namespace keo_ship;

// This method creates an instance of the class //
CShipListClass::CShipListClass()
    : CShipDataClass()
{
}
CShipListClass::~CShipListClass()
{
}
// Return the set flag //
bool CShipListClass::isSet(void) const
{
    return false;
}
// Return the type of the data class //
ShipDataType CShipListClass::getDataType(void) const
{
    return BASE_LIST_CLASS_TYPE;
}
// Override the base functionality //
std::vector<int32_t> CShipListClass::getListOfSetMembers() const
{
    return std::vector<int32_t>();
}
// Override the base functionality //
CShipDataClass* CShipListClass::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
    (void)c_hashKey;
    return NULL;
}
// Override the base functionality //
ValueType CShipListClass::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
    (void)c_hashKey;
    (void)r_valueString;
    return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void CShipListClass::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
    (void)c_hashKey;
    (void)c_stringValue;
    (void)c_valueType;
}
// Override the base functionality //
xs_string CShipListClass::getListElement(uint32_t c_index)
{
    (void)c_index;
    return xs_string();
}
void CShipListClass::appendListElement(const std::string& c_stringValue)
{
    (void)c_stringValue;
}
