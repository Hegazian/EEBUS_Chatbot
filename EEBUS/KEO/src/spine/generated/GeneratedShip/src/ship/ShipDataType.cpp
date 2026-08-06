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
#include "keo_ship/ShipDataType.h"

namespace keo_ship 
{

/// String of the Ship cmd types
const char* const ShipDataTypeAsString[ALL_DATA_TYPE_NUMBER] = { 
    "invalidData" 
  , "baseClass"  
  , "baseListClass"
  , "connectionHelloPhase"
  , "connectionHello"
  , "messageProtocolFormats"
  , "protocolHandshakeType"
  , "messageProtocolHandshake"
  , "classVersion"
  , "messageProtocolHandshakeError"
  , "pinState"
  , "pinInputPermission"
  , "connectionPinState"
  , "connectionPinInput"
  , "connectionPinError"
  , "header"
  , "extension"
  , "data"
  , "connectionClosePhase"
  , "connectionCloseReason"
  , "connectionClose"
  , "accessMethodsRequest"
  , "accessMethods"
  , "classDnsSdmDns"

}; 

/// Hash of the Ship cmd types
const int32_t ShipDataTypeAsHash[ALL_DATA_TYPE_NUMBER] = { 
    205317 
  , 56456
  , 906680
  , 108789145
  , 3538329
  , 470287051
  , 220806592
  , 425657344
  , 449415
  , 425671204
  , 26738
  , 28830562
  , 27458969
  , 29801881
  , 29244825
  , 6758
  , 56141
  , 1534
  , 108704153
  , 229159321
  , 3453337
  , 118796587
  , 897323
  , 1743367

}; 

const ShipDataType ShipDataTypeAsEnum[ALL_DATA_TYPE_NUMBER] = { 
    INVALID_DATA_TYPE
  , BASE_CLASS_TYPE
  , BASE_LIST_CLASS_TYPE
  , CONNECTION_HELLO_PHASE_TYPE
  , CONNECTION_HELLO_TYPE
  , MESSAGE_PROTOCOL_FORMATS_TYPE
  , PROTOCOL_HANDSHAKE_TYPE_TYPE
  , MESSAGE_PROTOCOL_HANDSHAKE_TYPE
  , CLASS_VERSION_TYPE
  , MESSAGE_PROTOCOL_HANDSHAKE_ERROR_TYPE
  , PIN_STATE_TYPE
  , PIN_INPUT_PERMISSION_TYPE
  , CONNECTION_PIN_STATE_TYPE
  , CONNECTION_PIN_INPUT_TYPE
  , CONNECTION_PIN_ERROR_TYPE
  , HEADER_TYPE
  , EXTENSION_TYPE
  , DATA_TYPE
  , CONNECTION_CLOSE_PHASE_TYPE
  , CONNECTION_CLOSE_REASON_TYPE
  , CONNECTION_CLOSE_TYPE
  , ACCESS_METHODS_REQUEST_TYPE
  , ACCESS_METHODS_TYPE
  , CLASS_DNS_SD_M_DNS_TYPE

}; 

/// String of the Ship data member names
const char* const ShipDataMemberNameArray[25] = {  
  "phase",
  "waiting",
  "prolongationRequest",
  "format",
  "handshakeType",
  "version",
  "formats",
  "major",
  "minor",
  "error",
  "pinState",
  "inputPermission",
  "pin",
  "protocolId",
  "extensionId",
  "binary",
  "string",
  "header",
  "payload",
  "extension",
  "maxTime",
  "reason",
  "id",
  "dnsSd_mDns",
  "dns",


}; 

} // namespace keo_ship

