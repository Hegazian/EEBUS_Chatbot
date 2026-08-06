/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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

#ifndef KEO_DATAGRAM_VERSION_UTILITIES__H__
#define KEO_DATAGRAM_VERSION_UTILITIES__H__

#include <keo_datagram/core/SpineDataType.h>
#include <keo_datagram/core/xs_types.h>
#include <string>

namespace keo_datagram
{

/** @addtogroup SpineDatagramCore
 * @{
 */

/* ****************************************************************************** *
 *  class SpineVersionUtilities: definition                                             *
 * ****************************************************************************** */
/** Utilities for SPINE datagrams **/
class SpineVersionUtilities
{
public:
    /** getAllSpineDataTypes
     *
     * Get all data types that are supported
     * @return list of data types names
     */
    static std::vector<std::string> getAllSpineDataTypes();

    /** getClassIdFromString
     *
     * get the enum type of a classId represented as string
     * @param c_classIdString classId as string
     * @return enum type of classId
     */
    static SpineClassId getClassIdFromString(const std::string& c_classIdString);

    /** getClassIdAsString
     *
     * get the string representation of a classId type
     * @param c_classId classId type
     * @return string representation
     */
    static std::string getClassIdAsString(SpineClassId c_classId);

    /** getAllClassIds
     *
     * Get all class ids that are supported
     * @return list of class ids names
     */
    static std::vector<std::string> getAllClassIds();

private:
    static int32_t getHashFromString(const std::string& c_string);

    // Empty Constructor //
    SpineVersionUtilities();
    // Empty Destructor //
    ~SpineVersionUtilities();
};
/** @}
 */
} // end namespace keo_datagram
#endif
