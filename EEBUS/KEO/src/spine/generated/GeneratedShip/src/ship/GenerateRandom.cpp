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
 *  @brief Generate random Ship data class elements 
 *
 *  @par    This is an automatically generated class
 *
 */

#include <limits>
#include <ctime>

#include "keo_ship/RandomGeneratorUtilities.h"
#include "xs_types.h"
#include "keo_ship/GenerateRandom.h"

using namespace keo_ship;

void GenerateRandom::initialiseBasicTypeLimits(bool booleanAlwaysTrue)
{
    RandomGeneratorUtilities::BooleanAlwaysTrue = booleanAlwaysTrue;

	RandomGeneratorUtilities::MinByte = std::numeric_limits<xs_byte>::min();
	RandomGeneratorUtilities::MaxByte = std::numeric_limits<xs_byte>::max();
	RandomGeneratorUtilities::MinUByte = std::numeric_limits<xs_unsignedByte>::min();
	RandomGeneratorUtilities::MaxUByte = std::numeric_limits<xs_unsignedByte>::max();
	RandomGeneratorUtilities::MinUShort = std::numeric_limits<xs_unsignedShort>::min();
	RandomGeneratorUtilities::MaxUShort = std::numeric_limits<xs_unsignedShort>::max();
	RandomGeneratorUtilities::MinShort = std::numeric_limits<xs_short>::min();
	RandomGeneratorUtilities::MaxShort = std::numeric_limits<xs_short>::max();
	RandomGeneratorUtilities::MinUInt = std::numeric_limits<xs_unsignedInt>::min();
	RandomGeneratorUtilities::MaxUInt = std::numeric_limits<xs_unsignedInt>::max();
	RandomGeneratorUtilities::MinULong = std::numeric_limits<xs_unsignedLong>::min();
	RandomGeneratorUtilities::MaxULong = std::numeric_limits<xs_unsignedLong>::max();
	RandomGeneratorUtilities::MinInt = std::numeric_limits<xs_integer>::min();
	RandomGeneratorUtilities::MaxInt = std::numeric_limits<xs_integer>::max();
	RandomGeneratorUtilities::MinDouble = std::numeric_limits<xs_double>::min();
	RandomGeneratorUtilities::MaxDouble = std::numeric_limits<xs_double>::max();
	RandomGeneratorUtilities::MaxStringSize = 1024;
	RandomGeneratorUtilities::MaxHexBinarySize = 1024;
	RandomGeneratorUtilities::StartTime = std::time(0);
	RandomGeneratorUtilities::MaxElapsedTime = 24*60*60; // in seconds
	RandomGeneratorUtilities::MinTime = std::numeric_limits<time_t>::min();
	RandomGeneratorUtilities::MaxTime = std::numeric_limits<time_t>::max();

	RandomGeneratorUtilities::inititalizeRandomGenerator();
}
void GenerateRandom::setMaximumForInteger(int c_maxInt)
{
    RandomGeneratorUtilities::MaxInt = c_maxInt;
}
CShipDataClass* GenerateRandom::getRandomDataFromDataType(ShipDataType c_type, bool c_generateInvalid)
{
	switch(c_type) {
		case CONNECTION_HELLO_TYPE: return new (std::nothrow) ConnectionHello(GenerateRandom::generateConnectionHello(c_generateInvalid));
		case MESSAGE_PROTOCOL_FORMATS_TYPE: return new (std::nothrow) MessageProtocolFormats(GenerateRandom::generateMessageProtocolFormats(c_generateInvalid));
		case MESSAGE_PROTOCOL_HANDSHAKE_TYPE: return new (std::nothrow) MessageProtocolHandshake(GenerateRandom::generateMessageProtocolHandshake(c_generateInvalid));
		case CLASS_VERSION_TYPE: return new (std::nothrow) ClassVersion(GenerateRandom::generateClassVersion(c_generateInvalid));
		case MESSAGE_PROTOCOL_HANDSHAKE_ERROR_TYPE: return new (std::nothrow) MessageProtocolHandshakeError(GenerateRandom::generateMessageProtocolHandshakeError(c_generateInvalid));
		case CONNECTION_PIN_STATE_TYPE: return new (std::nothrow) ConnectionPinState(GenerateRandom::generateConnectionPinState(c_generateInvalid));
		case CONNECTION_PIN_INPUT_TYPE: return new (std::nothrow) ConnectionPinInput(GenerateRandom::generateConnectionPinInput(c_generateInvalid));
		case CONNECTION_PIN_ERROR_TYPE: return new (std::nothrow) ConnectionPinError(GenerateRandom::generateConnectionPinError(c_generateInvalid));
		case HEADER_TYPE: return new (std::nothrow) Header(GenerateRandom::generateHeader(c_generateInvalid));
		case EXTENSION_TYPE: return new (std::nothrow) Extension(GenerateRandom::generateExtension(c_generateInvalid));
		case DATA_TYPE: return new (std::nothrow) Data(GenerateRandom::generateData(c_generateInvalid));
		case CONNECTION_CLOSE_TYPE: return new (std::nothrow) ConnectionClose(GenerateRandom::generateConnectionClose(c_generateInvalid));
		case ACCESS_METHODS_REQUEST_TYPE: return new (std::nothrow) AccessMethodsRequest(GenerateRandom::generateAccessMethodsRequest(c_generateInvalid));
		case ACCESS_METHODS_TYPE: return new (std::nothrow) AccessMethods(GenerateRandom::generateAccessMethods(c_generateInvalid));
		case CLASS_DNS_SD_M_DNS_TYPE: return new (std::nothrow) ClassDnsSd_mDns(GenerateRandom::generateClassDnsSd_mDns(c_generateInvalid));
	
		default : {
			return NULL;
		}
	}
}
ConnectionHelloPhase GenerateRandom::generateConnectionHelloPhase(bool c_generateInvalid)
{
	ConnectionHelloPhase r_connectionHelloPhase;
	std::vector<std::string> enumList_enum;
	enumList_enum.push_back("aborted");
	enumList_enum.push_back("ready");
	enumList_enum.push_back("pending");
	xs_string v_enum = RandomGeneratorUtilities::generateEnumerationString(enumList_enum,c_generateInvalid);
	r_connectionHelloPhase.setFromString(v_enum);		
	return r_connectionHelloPhase;
}
ConnectionHello GenerateRandom::generateConnectionHello(bool c_generateInvalid)
{
	ConnectionHello r_connectionHello;
	r_connectionHello.setPhase(generateConnectionHelloPhase(c_generateInvalid));
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_unsignedInt v_waiting = RandomGeneratorUtilities::generateXsUnsignedInt(RandomGeneratorUtilities::MinUInt,RandomGeneratorUtilities::MaxUInt,c_generateInvalid);
	r_connectionHello.setWaiting(v_waiting);
	}
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_boolean v_prolongationRequest = RandomGeneratorUtilities::generateXsBoolean();
	r_connectionHello.setProlongationRequest(v_prolongationRequest);
	}
	return r_connectionHello;
}
MessageProtocolFormats GenerateRandom::generateMessageProtocolFormats(bool c_generateInvalid)
{
	MessageProtocolFormats r_messageProtocolFormats;
	std::vector<xs_string> formatList;
	int count_format = RandomGeneratorUtilities::generateXsInteger(1,RandomGeneratorUtilities::MaxInt,c_generateInvalid);
	for (int i = 0; i < count_format; i++) {
		xs_string v_format = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
		formatList.push_back(v_format);
	}
	r_messageProtocolFormats.setFormat(formatList);		
	return r_messageProtocolFormats;
}
ProtocolHandshakeType GenerateRandom::generateProtocolHandshakeType(bool c_generateInvalid)
{
	ProtocolHandshakeType r_protocolHandshakeType;
	std::vector<std::string> enumList_enum;
	enumList_enum.push_back("select");
	enumList_enum.push_back("announceMax");
	xs_string v_enum = RandomGeneratorUtilities::generateEnumerationString(enumList_enum,c_generateInvalid);
	r_protocolHandshakeType.setFromString(v_enum);		
	return r_protocolHandshakeType;
}
MessageProtocolHandshake GenerateRandom::generateMessageProtocolHandshake(bool c_generateInvalid)
{
	MessageProtocolHandshake r_messageProtocolHandshake;
	r_messageProtocolHandshake.setHandshakeType(generateProtocolHandshakeType(c_generateInvalid));
	r_messageProtocolHandshake.setVersion(generateClassVersion(c_generateInvalid));
	r_messageProtocolHandshake.setFormats(generateMessageProtocolFormats(c_generateInvalid));
	return r_messageProtocolHandshake;
}
ClassVersion GenerateRandom::generateClassVersion(bool c_generateInvalid)
{
	ClassVersion r_classVersion;
	xs_unsignedShort v_major = RandomGeneratorUtilities::generateXsUnsignedShort(RandomGeneratorUtilities::MinUShort,RandomGeneratorUtilities::MaxUShort,c_generateInvalid);
	r_classVersion.setMajor(v_major);
	xs_unsignedShort v_minor = RandomGeneratorUtilities::generateXsUnsignedShort(RandomGeneratorUtilities::MinUShort,RandomGeneratorUtilities::MaxUShort,c_generateInvalid);
	r_classVersion.setMinor(v_minor);
	return r_classVersion;
}
MessageProtocolHandshakeError GenerateRandom::generateMessageProtocolHandshakeError(bool c_generateInvalid)
{
	MessageProtocolHandshakeError r_messageProtocolHandshakeError;
	xs_unsignedByte v_error = RandomGeneratorUtilities::generateXsUnsignedByte(RandomGeneratorUtilities::MinUByte,RandomGeneratorUtilities::MaxUByte,c_generateInvalid);
	r_messageProtocolHandshakeError.setError(v_error);
	return r_messageProtocolHandshakeError;
}
PinState GenerateRandom::generatePinState(bool c_generateInvalid)
{
	PinState r_pinState;
	std::vector<std::string> enumList_enum;
	enumList_enum.push_back("none");
	enumList_enum.push_back("pinOk");
	enumList_enum.push_back("optional");
	enumList_enum.push_back("required");
	xs_string v_enum = RandomGeneratorUtilities::generateEnumerationString(enumList_enum,c_generateInvalid);
	r_pinState.setFromString(v_enum);		
	return r_pinState;
}
PinInputPermission GenerateRandom::generatePinInputPermission(bool c_generateInvalid)
{
	PinInputPermission r_pinInputPermission;
	std::vector<std::string> enumList_enum;
	enumList_enum.push_back("ok");
	enumList_enum.push_back("busy");
	xs_string v_enum = RandomGeneratorUtilities::generateEnumerationString(enumList_enum,c_generateInvalid);
	r_pinInputPermission.setFromString(v_enum);		
	return r_pinInputPermission;
}
ConnectionPinState GenerateRandom::generateConnectionPinState(bool c_generateInvalid)
{
	ConnectionPinState r_connectionPinState;
	r_connectionPinState.setPinState(generatePinState(c_generateInvalid));
	r_connectionPinState.setInputPermission(generatePinInputPermission(c_generateInvalid));
	return r_connectionPinState;
}
ConnectionPinInput GenerateRandom::generateConnectionPinInput(bool c_generateInvalid)
{
	ConnectionPinInput r_connectionPinInput;
	xs_string v_pin = RandomGeneratorUtilities::generateXsStringWithPattern("[0-9a-fA-F]{8,16}");
	r_connectionPinInput.setPin(v_pin);
	return r_connectionPinInput;
}
ConnectionPinError GenerateRandom::generateConnectionPinError(bool c_generateInvalid)
{
	ConnectionPinError r_connectionPinError;
	xs_unsignedByte v_error = RandomGeneratorUtilities::generateXsUnsignedByte(RandomGeneratorUtilities::MinUByte,RandomGeneratorUtilities::MaxUByte,c_generateInvalid);
	r_connectionPinError.setError(v_error);
	return r_connectionPinError;
}
Header GenerateRandom::generateHeader(bool c_generateInvalid)
{
	Header r_header;
	xs_string v_protocolId = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
	r_header.setProtocolId(v_protocolId);
	return r_header;
}
Extension GenerateRandom::generateExtension(bool c_generateInvalid)
{
	Extension r_extension;
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_string v_extensionId = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
	r_extension.setExtensionId(v_extensionId);
	}
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_hexBinary v_binary = RandomGeneratorUtilities::generateXsHexBinary(0,RandomGeneratorUtilities::MaxHexBinarySize,c_generateInvalid);
	r_extension.setBinary(v_binary);
	}
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_string v_string = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
	r_extension.setString(v_string);
	}
	return r_extension;
}
Data GenerateRandom::generateData(bool c_generateInvalid)
{
	Data r_data;
	r_data.setHeader(generateHeader(c_generateInvalid));
	xs_string v_payload = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
	r_data.setPayload(v_payload);
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
		r_data.setExtension(generateExtension(c_generateInvalid));
	}
	return r_data;
}
ConnectionClosePhase GenerateRandom::generateConnectionClosePhase(bool c_generateInvalid)
{
	ConnectionClosePhase r_connectionClosePhase;
	std::vector<std::string> enumList_enum;
	enumList_enum.push_back("confirm");
	enumList_enum.push_back("announce");
	xs_string v_enum = RandomGeneratorUtilities::generateEnumerationString(enumList_enum,c_generateInvalid);
	r_connectionClosePhase.setFromString(v_enum);		
	return r_connectionClosePhase;
}
ConnectionCloseReason GenerateRandom::generateConnectionCloseReason(bool c_generateInvalid)
{
	ConnectionCloseReason r_connectionCloseReason;
	std::vector<std::string> enumList_enum;
	enumList_enum.push_back("removedConnection");
	enumList_enum.push_back("unspecific");
	xs_string v_enum = RandomGeneratorUtilities::generateEnumerationString(enumList_enum,c_generateInvalid);
	r_connectionCloseReason.setFromString(v_enum);		
	return r_connectionCloseReason;
}
ConnectionClose GenerateRandom::generateConnectionClose(bool c_generateInvalid)
{
	ConnectionClose r_connectionClose;
	r_connectionClose.setPhase(generateConnectionClosePhase(c_generateInvalid));
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_unsignedInt v_maxTime = RandomGeneratorUtilities::generateXsUnsignedInt(RandomGeneratorUtilities::MinUInt,RandomGeneratorUtilities::MaxUInt,c_generateInvalid);
	r_connectionClose.setMaxTime(v_maxTime);
	}
	r_connectionClose.setReason(generateConnectionCloseReason(c_generateInvalid));
	return r_connectionClose;
}
AccessMethodsRequest GenerateRandom::generateAccessMethodsRequest(bool c_generateInvalid)
{
	AccessMethodsRequest r_accessMethodsRequest;
	(void)c_generateInvalid;
	return r_accessMethodsRequest;
}
AccessMethods GenerateRandom::generateAccessMethods(bool c_generateInvalid)
{
	AccessMethods r_accessMethods;
	xs_string v_id = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
	r_accessMethods.setId(v_id);
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
		r_accessMethods.setDnsSd_mDns();
	}
	if( RandomGeneratorUtilities::generateXsBoolean() ) {
	xs_string v_dns = RandomGeneratorUtilities::generateXsString(0,RandomGeneratorUtilities::MaxStringSize,c_generateInvalid);
	r_accessMethods.setDns(v_dns);
	}
	return r_accessMethods;
}
ClassDnsSd_mDns GenerateRandom::generateClassDnsSd_mDns(bool c_generateInvalid)
{
	ClassDnsSd_mDns r_classDnsSd_mDns;
	(void)c_generateInvalid;
	return r_classDnsSd_mDns;
}


