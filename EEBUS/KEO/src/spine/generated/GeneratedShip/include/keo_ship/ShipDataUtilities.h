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
#ifndef SHIP__UTILITIES__H__
#define SHIP__UTILITIES__H__

/** @addtogroup ShipMessageLibrary
 * @{
 */

#include "keo_ship/ShipHeader.h"
#include "keo_ship/ShipDataType.h"
#include "keo_ship/CShipDataClass.h"

namespace keo_ship { 
/* ****************************************************************************** *
 *  class ShipDataUtilities: definition                                             *
 * ****************************************************************************** */
class ShipDataUtilities
{
public:

    /** getDataTypeFromString
     * 
     * get the enum type of a messageType represented as string
     * @param c_messageTypeString messageType as string
     * @return enum type of messageType
     */
static keo_ship::ShipDataType getDataTypeFromString(const std::string& c_messageTypeString);

    /** createShipDataFromDataType
     * create a Ship data object based on the data type.
     * @param c_type data type
     * @return created data object or NULL
     */
static CShipDataClass* createShipDataFromDataType(const keo_ship::ShipDataType c_type);

    /** getHashFromString
     * 
     * Generates a long hash value from a string.
     * @param c_string string to compute hash from
     * @return hash value
     */
static int32_t getHashFromString(const std::string &c_string);

private:

    // Empty Constructor //
    ShipDataUtilities();
    // Empty Destructor //
    ~ShipDataUtilities();
};
} // end namespace keo_ship
/** @}
 */
#endif

