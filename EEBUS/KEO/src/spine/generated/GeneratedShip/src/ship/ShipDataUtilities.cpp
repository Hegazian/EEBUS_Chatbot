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
#include "keo_ship/ShipDataUtilities.h"

using namespace keo_ship;

// get the enum type of a message represented as string //
ShipDataType ShipDataUtilities::getDataTypeFromString(const std::string& c_messageTypeString)
{
    int32_t hash = getHashFromString(c_messageTypeString);
	for(unsigned int i = 0; i < ALL_DATA_TYPE_NUMBER; i++) {
        // use compare to get cmd type from an extended string list
        if(hash == ShipDataTypeAsHash[i]) {
			if(c_messageTypeString.compare(ShipDataTypeAsString[i]) == 0) {
				return ShipDataTypeAsEnum[i];
			}
			return INVALID_DATA_TYPE;
        }
    }
	return INVALID_DATA_TYPE;
}
// create a Ship data object based on the data type //
CShipDataClass* ShipDataUtilities::createShipDataFromDataType(const ShipDataType c_type)
{
	switch(c_type) {
		case CONNECTION_HELLO_TYPE : 
			return new (std::nothrow) ConnectionHello();
		case MESSAGE_PROTOCOL_HANDSHAKE_TYPE : 
			return new (std::nothrow) MessageProtocolHandshake();
		case MESSAGE_PROTOCOL_HANDSHAKE_ERROR_TYPE : 
			return new (std::nothrow) MessageProtocolHandshakeError();
		case CONNECTION_PIN_STATE_TYPE : 
			return new (std::nothrow) ConnectionPinState();
		case CONNECTION_PIN_INPUT_TYPE : 
			return new (std::nothrow) ConnectionPinInput();
		case CONNECTION_PIN_ERROR_TYPE : 
			return new (std::nothrow) ConnectionPinError();
		case ACCESS_METHODS_REQUEST_TYPE : 
			return new (std::nothrow) AccessMethodsRequest();
		case ACCESS_METHODS_TYPE : 
			return new (std::nothrow) AccessMethods();
		case CONNECTION_CLOSE_TYPE : 
			return new (std::nothrow) ConnectionClose();
		case DATA_TYPE : 
			return new (std::nothrow) Data();

		default: {
			//DBG_MODULE_WARN("Unkown data type for messages");
		}
	}
	return NULL;
}
int32_t ShipDataUtilities::getHashFromString(const std::string &c_string)
{
    std::string::const_iterator iter = c_string.begin();
    std::string::const_iterator iterEnd = c_string.end();
    int32_t returnLong = 0;
    int shift = 0;
    for(;iter !=iterEnd;++iter){
    	returnLong += (((uint16_t)*iter) << shift);
        if(shift++ > 20) {
            shift = 0;
        }
    }
    return returnLong;
}

