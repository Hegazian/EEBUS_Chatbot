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
#ifndef SHIP__TYPES__H__
#define SHIP__TYPES__H__

/** @addtogroup ShipMessageLibrary
 * @{
 */

#include <vector>
#include "xs_types.h"

/// Ship namespace
namespace keo_ship 
{

	/// Enumeration of the Ship data types
    enum ShipDataType
    {
        INVALID_DATA_TYPE = 0
	  , BASE_CLASS_TYPE = 1
	  , BASE_LIST_CLASS_TYPE = 2
      , CONNECTION_HELLO_PHASE_TYPE = 3
      , CONNECTION_HELLO_TYPE = 4
      , MESSAGE_PROTOCOL_FORMATS_TYPE = 5
      , PROTOCOL_HANDSHAKE_TYPE_TYPE = 6
      , MESSAGE_PROTOCOL_HANDSHAKE_TYPE = 7
      , CLASS_VERSION_TYPE = 8
      , MESSAGE_PROTOCOL_HANDSHAKE_ERROR_TYPE = 9
      , PIN_STATE_TYPE = 10
      , PIN_INPUT_PERMISSION_TYPE = 11
      , CONNECTION_PIN_STATE_TYPE = 12
      , CONNECTION_PIN_INPUT_TYPE = 13
      , CONNECTION_PIN_ERROR_TYPE = 14
      , HEADER_TYPE = 15
      , EXTENSION_TYPE = 16
      , DATA_TYPE = 17
      , CONNECTION_CLOSE_PHASE_TYPE = 18
      , CONNECTION_CLOSE_REASON_TYPE = 19
      , CONNECTION_CLOSE_TYPE = 20
      , ACCESS_METHODS_REQUEST_TYPE = 21
      , ACCESS_METHODS_TYPE = 22
      , CLASS_DNS_SD_M_DNS_TYPE = 23
      , ALL_DATA_TYPE_NUMBER = 24
    }; 
      	      	
    extern const char* const ShipDataTypeAsString[ALL_DATA_TYPE_NUMBER];

    extern const int32_t ShipDataTypeAsHash[ALL_DATA_TYPE_NUMBER];

    extern const ShipDataType ShipDataTypeAsEnum[ALL_DATA_TYPE_NUMBER];

	/// String of the Ship data member names
    extern const char* const ShipDataMemberNameArray[25]; 

}
     
/** @}
 */
                  
#endif //SHIP__TYPES__H__

