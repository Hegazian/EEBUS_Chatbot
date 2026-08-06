#include "ShipStringUtil.h"
#include "ShipByteArray.h"
/**
 *  @brief ConnectionHello 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionHello.h"

using namespace keo_ship;

ConnectionHello::ConnectionHello ()
    : CShipDataClass() 
	,m_phaseIsSet(false)
	,m_waitingIsSet(false)
	,m_prolongationRequest(false)
	,m_prolongationRequestIsSet(false)
	,m_phase(ConnectionHelloPhase())
	,m_waiting(0)
{ 
}

ConnectionHello::ConnectionHello (const ConnectionHelloPhase& c_phase, const xs_unsignedInt& c_waiting, const xs_boolean& c_prolongationRequest)
    : CShipDataClass() 
{
	setPhase(c_phase);
	setWaiting(c_waiting);
	setProlongationRequest(c_prolongationRequest);
}

ConnectionHello::~ConnectionHello ()
{
}
// Override the base functionality //
bool ConnectionHello::isSet(void) const
{
	return true;
}
// Override the base functionality //
ShipDataType ConnectionHello::getDataType(void) const
{
	return CONNECTION_HELLO_TYPE;
}
// Override the base functionality //
CShipDataClass* ConnectionHello::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ConnectionHello::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_phaseIsSet) {
		returnList.push_back(0);
	}
	if(m_waitingIsSet) {
		returnList.push_back(1);
	}
	if(m_prolongationRequestIsSet) {
		returnList.push_back(2);
	}
	return returnList;
}
// Override the base functionality //
ValueType ConnectionHello::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 3244) {
		r_valueString = m_phase.getDataString();
		return VALUE_STRING;
	}
	if(c_hashKey == 13453) {
		r_valueString = ShipStringUtil::unumber(m_waiting);
		return VALUE_NUMBER;
	}
	if(c_hashKey == 59397984) {
		r_valueString = m_prolongationRequest ? "true" : "false";
		return m_prolongationRequest ? VALUE_FALSE : VALUE_TRUE;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ConnectionHello::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 3244) {
		setPhase(ConnectionHelloPhase(c_stringValue));
		return;
	}
	if(c_hashKey == 13453) {
		setWaiting(ShipStringUtil::toUint32(c_stringValue));
		return;
	}
	if(c_hashKey == 59397984) {
		setProlongationRequest(c_valueType == m_prolongationRequest ? false : true);
		return;
	}
}
ConnectionHelloPhase ConnectionHello::getPhase(void) const
{
	if(m_phaseIsSet) {
		return m_phase;
	}
	return ConnectionHelloPhase();
}
bool ConnectionHello::getPhaseIsSet(void) const
{
	return m_phaseIsSet;
}
xs_unsignedInt ConnectionHello::getWaiting(void) const
{
	if(m_waitingIsSet) {
		return m_waiting;
	}
	return xs_unsignedInt();
}
bool ConnectionHello::getWaitingIsSet(void) const
{
	return m_waitingIsSet;
}
xs_boolean ConnectionHello::getProlongationRequest(void) const
{
	if(m_prolongationRequestIsSet) {
		return m_prolongationRequest;
	}
	return xs_boolean();
}
bool ConnectionHello::getProlongationRequestIsSet(void) const
{
	return m_prolongationRequestIsSet;
}

void ConnectionHello::setPhase(const ConnectionHelloPhase& c_value)
{
	m_phase = c_value;
	m_phaseIsSet = true;
}
void ConnectionHello::cleanPhase(void)
{
	m_phase = ConnectionHelloPhase();
	m_phaseIsSet = false;
}
void ConnectionHello::setWaiting(const xs_unsignedInt& c_value)
{
	m_waiting = c_value;
	m_waitingIsSet = true;
}
void ConnectionHello::cleanWaiting(void)
{
	m_waiting = xs_unsignedInt();
	m_waitingIsSet = false;
}
void ConnectionHello::setProlongationRequest(const xs_boolean& c_value)
{
	m_prolongationRequest = c_value;
	m_prolongationRequestIsSet = true;
}
void ConnectionHello::cleanProlongationRequest(void)
{
	m_prolongationRequest = xs_boolean();
	m_prolongationRequestIsSet = false;
}

/**
 *  @brief MessageProtocolFormats 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/MessageProtocolFormats.h"

using namespace keo_ship;

MessageProtocolFormats::MessageProtocolFormats ()
    : CShipListClass() 
	,m_formatIsSet(false)
	,m_format(std::vector<xs_string>())
{ 
}

MessageProtocolFormats::MessageProtocolFormats (const std::vector<xs_string>& c_format)
    : CShipListClass() 
{
	setFormat(c_format);
}

MessageProtocolFormats::~MessageProtocolFormats ()
{
}
// Override the base functionality //
bool MessageProtocolFormats::isSet(void) const
{
	return m_formatIsSet;
}
// Override the base functionality //
ShipDataType MessageProtocolFormats::getDataType(void) const
{
	return MESSAGE_PROTOCOL_FORMATS_TYPE;
}
// Override the base functionality //
std::vector<int32_t> MessageProtocolFormats::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_formatIsSet) {
		returnList.push_back(3);
	}
	return returnList;
}
// Override the base functionality //
CShipDataClass* MessageProtocolFormats::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
    (void)c_hashKey;
    return NULL;
}
// Override the base functionality //
ValueType MessageProtocolFormats::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 6916) {
		r_valueString = "";
		return VALUE_LIST;
	}
	return keo_ship::VALUE_NOT_DEFINED;
}
// Override the base functionality //
void MessageProtocolFormats::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
	(void)c_hashKey;(void)c_stringValue;(void)c_valueType;
}
// Override the base functionality //
void MessageProtocolFormats::appendListElement(const std::string& c_stringValue)
{
	m_format.push_back(c_stringValue);
	m_formatIsSet = true;

}
// Override the base functionality //
xs_string MessageProtocolFormats::getListElement(uint32_t c_index)
{
	if(c_index < m_format.size()) {
		return m_format[c_index];
	}
	return xs_string();
}
std::vector<xs_string> MessageProtocolFormats::getFormat(void) const
{
	if(m_formatIsSet) {
		return m_format;
	}
	return std::vector<xs_string>();
}
bool MessageProtocolFormats::getFormatIsSet(void) const
{
	return m_formatIsSet;
}

void MessageProtocolFormats::setFormat(const std::vector<xs_string>& c_value)
{
	m_format = c_value;
	m_formatIsSet = true;
}
void MessageProtocolFormats::cleanFormat(void)
{
	m_format = std::vector<xs_string>();
	m_formatIsSet = false;
}

/**
 *  @brief MessageProtocolHandshake 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/MessageProtocolHandshake.h"

using namespace keo_ship;

MessageProtocolHandshake::MessageProtocolHandshake ()
    : CShipDataClass() 
	,m_handshakeTypeIsSet(false)
	,m_versionIsSet(false)
	,m_formatsIsSet(false)
	,m_handshakeType(ProtocolHandshakeType())
	,m_version(ClassVersion())
	,m_formats(MessageProtocolFormats())
{ 
}

MessageProtocolHandshake::MessageProtocolHandshake (const ProtocolHandshakeType& c_handshakeType, const ClassVersion& c_version, const MessageProtocolFormats& c_formats)
    : CShipDataClass() 
{
	setHandshakeType(c_handshakeType);
	setVersion(c_version);
	setFormats(c_formats);
}

MessageProtocolHandshake::~MessageProtocolHandshake ()
{
}
// Override the base functionality //
bool MessageProtocolHandshake::isSet(void) const
{
	return m_versionIsSet && m_formatsIsSet;
}
// Override the base functionality //
ShipDataType MessageProtocolHandshake::getDataType(void) const
{
	return MESSAGE_PROTOCOL_HANDSHAKE_TYPE;
}
// Override the base functionality //
CShipDataClass* MessageProtocolHandshake::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	if(c_hashKey == 13968) {
		m_versionIsSet = true;
		return &m_version;
	}
	if(c_hashKey == 14276) {
		m_formatsIsSet = true;
		return &m_formats;
	}
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> MessageProtocolHandshake::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_handshakeTypeIsSet) {
		returnList.push_back(4);
	}
	if(m_versionIsSet) {
		returnList.push_back(5);
	}
	if(m_formatsIsSet) {
		returnList.push_back(6);
	}
	return returnList;
}
// Override the base functionality //
ValueType MessageProtocolHandshake::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 862450) {
		r_valueString = m_handshakeType.getDataString();
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void MessageProtocolHandshake::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 862450) {
		setHandshakeType(ProtocolHandshakeType(c_stringValue));
		return;
	}
}
ProtocolHandshakeType MessageProtocolHandshake::getHandshakeType(void) const
{
	if(m_handshakeTypeIsSet) {
		return m_handshakeType;
	}
	return ProtocolHandshakeType();
}
bool MessageProtocolHandshake::getHandshakeTypeIsSet(void) const
{
	return m_handshakeTypeIsSet;
}
ClassVersion MessageProtocolHandshake::getVersion(void) const
{
	if(m_versionIsSet) {
		return m_version;
	}
	return ClassVersion();
}
bool MessageProtocolHandshake::getVersionIsSet(void) const
{
	return m_versionIsSet;
}
MessageProtocolFormats MessageProtocolHandshake::getFormats(void) const
{
	if(m_formatsIsSet) {
		return m_formats;
	}
	return MessageProtocolFormats();
}
bool MessageProtocolHandshake::getFormatsIsSet(void) const
{
	return m_formatsIsSet;
}

void MessageProtocolHandshake::setHandshakeType(const ProtocolHandshakeType& c_value)
{
	m_handshakeType = c_value;
	m_handshakeTypeIsSet = true;
}
void MessageProtocolHandshake::cleanHandshakeType(void)
{
	m_handshakeType = ProtocolHandshakeType();
	m_handshakeTypeIsSet = false;
}
void MessageProtocolHandshake::setVersion(const ClassVersion& c_value)
{
	m_version = c_value;
	m_versionIsSet = true;
}
void MessageProtocolHandshake::cleanVersion(void)
{
	m_version = ClassVersion();
	m_versionIsSet = false;
}
void MessageProtocolHandshake::setFormats(const MessageProtocolFormats& c_value)
{
	m_formats = c_value;
	m_formatsIsSet = true;
}
void MessageProtocolHandshake::cleanFormats(void)
{
	m_formats = MessageProtocolFormats();
	m_formatsIsSet = false;
}

/**
 *  @brief ClassVersion 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ClassVersion.h"

using namespace keo_ship;

ClassVersion::ClassVersion ()
    : CShipDataClass() 
	,m_majorIsSet(false)
	,m_minorIsSet(false)
	,m_major(0)
	,m_minor(0)
{ 
}

ClassVersion::ClassVersion (const xs_unsignedShort& c_major, const xs_unsignedShort& c_minor)
    : CShipDataClass() 
{
	setMajor(c_major);
	setMinor(c_minor);
}

ClassVersion::~ClassVersion ()
{
}
// Override the base functionality //
bool ClassVersion::isSet(void) const
{
	return m_majorIsSet && m_minorIsSet;
}
// Override the base functionality //
ShipDataType ClassVersion::getDataType(void) const
{
	return CLASS_VERSION_TYPE;
}
// Override the base functionality //
CShipDataClass* ClassVersion::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ClassVersion::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_majorIsSet) {
		returnList.push_back(7);
	}
	if(m_minorIsSet) {
		returnList.push_back(8);
	}
	return returnList;
}
// Override the base functionality //
ValueType ClassVersion::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 3439) {
		r_valueString = ShipStringUtil::unumber(m_major);
		return VALUE_NUMBER;
	}
	if(c_hashKey == 3471) {
		r_valueString = ShipStringUtil::unumber(m_minor);
		return VALUE_NUMBER;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ClassVersion::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 3439) {
		setMajor(ShipStringUtil::toUint16(c_stringValue));
		return;
	}
	if(c_hashKey == 3471) {
		setMinor(ShipStringUtil::toUint16(c_stringValue));
		return;
	}
}
xs_unsignedShort ClassVersion::getMajor(void) const
{
	if(m_majorIsSet) {
		return m_major;
	}
	return xs_unsignedShort();
}
bool ClassVersion::getMajorIsSet(void) const
{
	return m_majorIsSet;
}
xs_unsignedShort ClassVersion::getMinor(void) const
{
	if(m_minorIsSet) {
		return m_minor;
	}
	return xs_unsignedShort();
}
bool ClassVersion::getMinorIsSet(void) const
{
	return m_minorIsSet;
}

void ClassVersion::setMajor(const xs_unsignedShort& c_value)
{
	m_major = c_value;
	m_majorIsSet = true;
}
void ClassVersion::cleanMajor(void)
{
	m_major = xs_unsignedShort();
	m_majorIsSet = false;
}
void ClassVersion::setMinor(const xs_unsignedShort& c_value)
{
	m_minor = c_value;
	m_minorIsSet = true;
}
void ClassVersion::cleanMinor(void)
{
	m_minor = xs_unsignedShort();
	m_minorIsSet = false;
}

/**
 *  @brief MessageProtocolHandshakeError 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/MessageProtocolHandshakeError.h"

using namespace keo_ship;

MessageProtocolHandshakeError::MessageProtocolHandshakeError ()
    : CShipDataClass() 
	,m_errorIsSet(false)
	,m_error(0)
{ 
}

MessageProtocolHandshakeError::MessageProtocolHandshakeError (const xs_unsignedByte& c_error)
    : CShipDataClass() 
{
	setError(c_error);
}

MessageProtocolHandshakeError::~MessageProtocolHandshakeError ()
{
}
// Override the base functionality //
bool MessageProtocolHandshakeError::isSet(void) const
{
	return m_errorIsSet;
}
// Override the base functionality //
ShipDataType MessageProtocolHandshakeError::getDataType(void) const
{
	return MESSAGE_PROTOCOL_HANDSHAKE_ERROR_TYPE;
}
// Override the base functionality //
CShipDataClass* MessageProtocolHandshakeError::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> MessageProtocolHandshakeError::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_errorIsSet) {
		returnList.push_back(9);
	}
	return returnList;
}
// Override the base functionality //
ValueType MessageProtocolHandshakeError::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 3497) {
		r_valueString = ShipStringUtil::unumber(m_error);
		return VALUE_NUMBER;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void MessageProtocolHandshakeError::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 3497) {
		setError(ShipStringUtil::toUint16(c_stringValue));
		return;
	}
}
xs_unsignedByte MessageProtocolHandshakeError::getError(void) const
{
	if(m_errorIsSet) {
		return m_error;
	}
	return xs_unsignedByte();
}
bool MessageProtocolHandshakeError::getErrorIsSet(void) const
{
	return m_errorIsSet;
}

void MessageProtocolHandshakeError::setError(const xs_unsignedByte& c_value)
{
	m_error = c_value;
	m_errorIsSet = true;
}
void MessageProtocolHandshakeError::cleanError(void)
{
	m_error = xs_unsignedByte();
	m_errorIsSet = false;
}

/**
 *  @brief ConnectionPinState 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionPinState.h"

using namespace keo_ship;

ConnectionPinState::ConnectionPinState ()
    : CShipDataClass() 
	,m_pinStateIsSet(false)
	,m_inputPermissionIsSet(false)
	,m_pinState(PinState())
	,m_inputPermission(PinInputPermission())
{ 
}

ConnectionPinState::ConnectionPinState (const PinState& c_pinState, const PinInputPermission& c_inputPermission)
    : CShipDataClass() 
{
	setPinState(c_pinState);
	setInputPermission(c_inputPermission);
}

ConnectionPinState::~ConnectionPinState ()
{
}
// Override the base functionality //
bool ConnectionPinState::isSet(void) const
{
	return true;
}
// Override the base functionality //
ShipDataType ConnectionPinState::getDataType(void) const
{
	return CONNECTION_PIN_STATE_TYPE;
}
// Override the base functionality //
CShipDataClass* ConnectionPinState::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ConnectionPinState::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_pinStateIsSet) {
		returnList.push_back(10);
	}
	if(m_inputPermissionIsSet) {
		returnList.push_back(11);
	}
	return returnList;
}
// Override the base functionality //
ValueType ConnectionPinState::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 26738) {
		r_valueString = m_pinState.getDataString();
		return VALUE_STRING;
	}
	if(c_hashKey == 3603757) {
		r_valueString = m_inputPermission.getDataString();
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ConnectionPinState::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 26738) {
		setPinState(PinState(c_stringValue));
		return;
	}
	if(c_hashKey == 3603757) {
		setInputPermission(PinInputPermission(c_stringValue));
		return;
	}
}
PinState ConnectionPinState::getPinState(void) const
{
	if(m_pinStateIsSet) {
		return m_pinState;
	}
	return PinState();
}
bool ConnectionPinState::getPinStateIsSet(void) const
{
	return m_pinStateIsSet;
}
PinInputPermission ConnectionPinState::getInputPermission(void) const
{
	if(m_inputPermissionIsSet) {
		return m_inputPermission;
	}
	return PinInputPermission();
}
bool ConnectionPinState::getInputPermissionIsSet(void) const
{
	return m_inputPermissionIsSet;
}

void ConnectionPinState::setPinState(const PinState& c_value)
{
	m_pinState = c_value;
	m_pinStateIsSet = true;
}
void ConnectionPinState::cleanPinState(void)
{
	m_pinState = PinState();
	m_pinStateIsSet = false;
}
void ConnectionPinState::setInputPermission(const PinInputPermission& c_value)
{
	m_inputPermission = c_value;
	m_inputPermissionIsSet = true;
}
void ConnectionPinState::cleanInputPermission(void)
{
	m_inputPermission = PinInputPermission();
	m_inputPermissionIsSet = false;
}

/**
 *  @brief ConnectionPinInput 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionPinInput.h"

using namespace keo_ship;

ConnectionPinInput::ConnectionPinInput ()
    : CShipDataClass() 
	,m_pinIsSet(false)
	,m_pin(xs_string())
{ 
}

ConnectionPinInput::ConnectionPinInput (const xs_string& c_pin)
    : CShipDataClass() 
{
	setPin(c_pin);
}

ConnectionPinInput::~ConnectionPinInput ()
{
}
// Override the base functionality //
bool ConnectionPinInput::isSet(void) const
{
	return m_pinIsSet;
}
// Override the base functionality //
ShipDataType ConnectionPinInput::getDataType(void) const
{
	return CONNECTION_PIN_INPUT_TYPE;
}
// Override the base functionality //
CShipDataClass* ConnectionPinInput::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ConnectionPinInput::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_pinIsSet) {
		returnList.push_back(12);
	}
	return returnList;
}
// Override the base functionality //
ValueType ConnectionPinInput::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 762) {
		r_valueString = m_pin;
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ConnectionPinInput::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 762) {
		setPin(c_stringValue);
		return;
	}
}
xs_string ConnectionPinInput::getPin(void) const
{
	if(m_pinIsSet) {
		return m_pin;
	}
	return xs_string();
}
bool ConnectionPinInput::getPinIsSet(void) const
{
	return m_pinIsSet;
}

void ConnectionPinInput::setPin(const xs_string& c_value)
{
	m_pin = c_value;
	m_pinIsSet = true;
}
void ConnectionPinInput::cleanPin(void)
{
	m_pin = xs_string();
	m_pinIsSet = false;
}

/**
 *  @brief ConnectionPinError 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionPinError.h"

using namespace keo_ship;

ConnectionPinError::ConnectionPinError ()
    : CShipDataClass() 
	,m_errorIsSet(false)
	,m_error(0)
{ 
}

ConnectionPinError::ConnectionPinError (const xs_unsignedByte& c_error)
    : CShipDataClass() 
{
	setError(c_error);
}

ConnectionPinError::~ConnectionPinError ()
{
}
// Override the base functionality //
bool ConnectionPinError::isSet(void) const
{
	return m_errorIsSet;
}
// Override the base functionality //
ShipDataType ConnectionPinError::getDataType(void) const
{
	return CONNECTION_PIN_ERROR_TYPE;
}
// Override the base functionality //
CShipDataClass* ConnectionPinError::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ConnectionPinError::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_errorIsSet) {
		returnList.push_back(9);
	}
	return returnList;
}
// Override the base functionality //
ValueType ConnectionPinError::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 3497) {
		r_valueString = ShipStringUtil::unumber(m_error);
		return VALUE_NUMBER;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ConnectionPinError::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 3497) {
		setError(ShipStringUtil::toUint16(c_stringValue));
		return;
	}
}
xs_unsignedByte ConnectionPinError::getError(void) const
{
	if(m_errorIsSet) {
		return m_error;
	}
	return xs_unsignedByte();
}
bool ConnectionPinError::getErrorIsSet(void) const
{
	return m_errorIsSet;
}

void ConnectionPinError::setError(const xs_unsignedByte& c_value)
{
	m_error = c_value;
	m_errorIsSet = true;
}
void ConnectionPinError::cleanError(void)
{
	m_error = xs_unsignedByte();
	m_errorIsSet = false;
}

/**
 *  @brief Header 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/Header.h"

using namespace keo_ship;

Header::Header ()
    : CShipDataClass() 
	,m_protocolIdIsSet(false)
	,m_protocolId(xs_string())
{ 
}

Header::Header (const xs_string& c_protocolId)
    : CShipDataClass() 
{
	setProtocolId(c_protocolId);
}

Header::~Header ()
{
}
// Override the base functionality //
bool Header::isSet(void) const
{
	return m_protocolIdIsSet;
}
// Override the base functionality //
ShipDataType Header::getDataType(void) const
{
	return HEADER_TYPE;
}
// Override the base functionality //
CShipDataClass* Header::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> Header::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_protocolIdIsSet) {
		returnList.push_back(13);
	}
	return returnList;
}
// Override the base functionality //
ValueType Header::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 97472) {
		r_valueString = m_protocolId;
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void Header::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 97472) {
		setProtocolId(c_stringValue);
		return;
	}
}
xs_string Header::getProtocolId(void) const
{
	if(m_protocolIdIsSet) {
		return m_protocolId;
	}
	return xs_string();
}
bool Header::getProtocolIdIsSet(void) const
{
	return m_protocolIdIsSet;
}

void Header::setProtocolId(const xs_string& c_value)
{
	m_protocolId = c_value;
	m_protocolIdIsSet = true;
}
void Header::cleanProtocolId(void)
{
	m_protocolId = xs_string();
	m_protocolIdIsSet = false;
}

/**
 *  @brief Extension 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/Extension.h"

using namespace keo_ship;

Extension::Extension ()
    : CShipDataClass() 
	,m_extensionIdIsSet(false)
	,m_binaryIsSet(false)
	,m_stringIsSet(false)
	,m_extensionId(xs_string())
	,m_binary(xs_hexBinary())
	,m_string(xs_string())
{ 
}

Extension::Extension (const xs_string& c_extensionId, const xs_hexBinary& c_binary, const xs_string& c_string)
    : CShipDataClass() 
{
	setExtensionId(c_extensionId);
	setBinary(c_binary);
	setString(c_string);
}

Extension::~Extension ()
{
}
// Override the base functionality //
bool Extension::isSet(void) const
{
	return true;
}
// Override the base functionality //
ShipDataType Extension::getDataType(void) const
{
	return EXTENSION_TYPE;
}
// Override the base functionality //
CShipDataClass* Extension::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> Extension::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_extensionIdIsSet) {
		returnList.push_back(14);
	}
	if(m_binaryIsSet) {
		returnList.push_back(15);
	}
	if(m_stringIsSet) {
		returnList.push_back(16);
	}
	return returnList;
}
// Override the base functionality //
ValueType Extension::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 195917) {
		r_valueString = m_extensionId;
		return VALUE_STRING;
	}
	if(c_hashKey == 7220) {
		r_valueString = m_binary.toHex();
		return VALUE_STRING;
	}
	if(c_hashKey == 6699) {
		r_valueString = m_string;
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void Extension::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 195917) {
		setExtensionId(c_stringValue);
		return;
	}
	if(c_hashKey == 7220) {
		setBinary(ShipByteArray::fromHex(c_stringValue));
		return;
	}
	if(c_hashKey == 6699) {
		setString(c_stringValue);
		return;
	}
}
xs_string Extension::getExtensionId(void) const
{
	if(m_extensionIdIsSet) {
		return m_extensionId;
	}
	return xs_string();
}
bool Extension::getExtensionIdIsSet(void) const
{
	return m_extensionIdIsSet;
}
xs_hexBinary Extension::getBinary(void) const
{
	if(m_binaryIsSet) {
		return m_binary;
	}
	return xs_hexBinary();
}
bool Extension::getBinaryIsSet(void) const
{
	return m_binaryIsSet;
}
xs_string Extension::getString(void) const
{
	if(m_stringIsSet) {
		return m_string;
	}
	return xs_string();
}
bool Extension::getStringIsSet(void) const
{
	return m_stringIsSet;
}

void Extension::setExtensionId(const xs_string& c_value)
{
	m_extensionId = c_value;
	m_extensionIdIsSet = true;
}
void Extension::cleanExtensionId(void)
{
	m_extensionId = xs_string();
	m_extensionIdIsSet = false;
}
void Extension::setBinary(const xs_hexBinary& c_value)
{
	m_binary = c_value;
	m_binaryIsSet = true;
}
void Extension::cleanBinary(void)
{
	m_binary = xs_hexBinary();
	m_binaryIsSet = false;
}
void Extension::setString(const xs_string& c_value)
{
	m_string = c_value;
	m_stringIsSet = true;
}
void Extension::cleanString(void)
{
	m_string = xs_string();
	m_stringIsSet = false;
}

/**
 *  @brief ConnectionClose 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionClose.h"

using namespace keo_ship;

ConnectionClose::ConnectionClose ()
    : CShipDataClass() 
	,m_phaseIsSet(false)
	,m_maxTimeIsSet(false)
	,m_reasonIsSet(false)
	,m_phase(ConnectionClosePhase())
	,m_maxTime(0)
	,m_reason(ConnectionCloseReason())
{ 
}

ConnectionClose::ConnectionClose (const ConnectionClosePhase& c_phase, const xs_unsignedInt& c_maxTime, const ConnectionCloseReason& c_reason)
    : CShipDataClass() 
{
	setPhase(c_phase);
	setMaxTime(c_maxTime);
	setReason(c_reason);
}

ConnectionClose::~ConnectionClose ()
{
}
// Override the base functionality //
bool ConnectionClose::isSet(void) const
{
	return true;
}
// Override the base functionality //
ShipDataType ConnectionClose::getDataType(void) const
{
	return CONNECTION_CLOSE_TYPE;
}
// Override the base functionality //
CShipDataClass* ConnectionClose::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ConnectionClose::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_phaseIsSet) {
		returnList.push_back(0);
	}
	if(m_maxTimeIsSet) {
		returnList.push_back(20);
	}
	if(m_reasonIsSet) {
		returnList.push_back(21);
	}
	return returnList;
}
// Override the base functionality //
ValueType ConnectionClose::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 3244) {
		r_valueString = m_phase.getDataString();
		return VALUE_STRING;
	}
	if(c_hashKey == 13087) {
		r_valueString = ShipStringUtil::unumber(m_maxTime);
		return VALUE_NUMBER;
	}
	if(c_hashKey == 6920) {
		r_valueString = m_reason.getDataString();
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ConnectionClose::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 3244) {
		setPhase(ConnectionClosePhase(c_stringValue));
		return;
	}
	if(c_hashKey == 13087) {
		setMaxTime(ShipStringUtil::toUint32(c_stringValue));
		return;
	}
	if(c_hashKey == 6920) {
		setReason(ConnectionCloseReason(c_stringValue));
		return;
	}
}
ConnectionClosePhase ConnectionClose::getPhase(void) const
{
	if(m_phaseIsSet) {
		return m_phase;
	}
	return ConnectionClosePhase();
}
bool ConnectionClose::getPhaseIsSet(void) const
{
	return m_phaseIsSet;
}
xs_unsignedInt ConnectionClose::getMaxTime(void) const
{
	if(m_maxTimeIsSet) {
		return m_maxTime;
	}
	return xs_unsignedInt();
}
bool ConnectionClose::getMaxTimeIsSet(void) const
{
	return m_maxTimeIsSet;
}
ConnectionCloseReason ConnectionClose::getReason(void) const
{
	if(m_reasonIsSet) {
		return m_reason;
	}
	return ConnectionCloseReason();
}
bool ConnectionClose::getReasonIsSet(void) const
{
	return m_reasonIsSet;
}

void ConnectionClose::setPhase(const ConnectionClosePhase& c_value)
{
	m_phase = c_value;
	m_phaseIsSet = true;
}
void ConnectionClose::cleanPhase(void)
{
	m_phase = ConnectionClosePhase();
	m_phaseIsSet = false;
}
void ConnectionClose::setMaxTime(const xs_unsignedInt& c_value)
{
	m_maxTime = c_value;
	m_maxTimeIsSet = true;
}
void ConnectionClose::cleanMaxTime(void)
{
	m_maxTime = xs_unsignedInt();
	m_maxTimeIsSet = false;
}
void ConnectionClose::setReason(const ConnectionCloseReason& c_value)
{
	m_reason = c_value;
	m_reasonIsSet = true;
}
void ConnectionClose::cleanReason(void)
{
	m_reason = ConnectionCloseReason();
	m_reasonIsSet = false;
}

/**
 *  @brief AccessMethodsRequest 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/AccessMethodsRequest.h"

using namespace keo_ship;

AccessMethodsRequest::AccessMethodsRequest ()
    : CShipDataClass() 
{ 
}


AccessMethodsRequest::~AccessMethodsRequest ()
{
}
// Override the base functionality //
bool AccessMethodsRequest::isSet(void) const
{
	return true;
}
// Override the base functionality //
ShipDataType AccessMethodsRequest::getDataType(void) const
{
	return ACCESS_METHODS_REQUEST_TYPE;
}
// Override the base functionality //
CShipDataClass* AccessMethodsRequest::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> AccessMethodsRequest::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	return returnList;
}
// Override the base functionality //
ValueType AccessMethodsRequest::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	(void)c_hashKey;(void)r_valueString;
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void AccessMethodsRequest::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	(void)c_hashKey;(void)c_stringValue;(void)c_valueType;
}


/**
 *  @brief AccessMethods 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/AccessMethods.h"

using namespace keo_ship;

AccessMethods::AccessMethods ()
    : CShipDataClass() 
	,m_idIsSet(false)
	,m_dnsSd_mDnsIsSet(false)
	,m_dnsIsSet(false)
	,m_id(xs_string())
	,m_dns(xs_string())
{ 
}

AccessMethods::AccessMethods (const xs_string& c_id, bool c_dnsSd_mDnsIsSet, const xs_string& c_dns)
    : CShipDataClass() 
{
	setId(c_id);
	m_dnsSd_mDnsIsSet = c_dnsSd_mDnsIsSet;
	setDns(c_dns);
}

AccessMethods::~AccessMethods ()
{
}
// Override the base functionality //
bool AccessMethods::isSet(void) const
{
	return m_idIsSet;
}
// Override the base functionality //
ShipDataType AccessMethods::getDataType(void) const
{
	return ACCESS_METHODS_TYPE;
}
// Override the base functionality //
CShipDataClass* AccessMethods::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> AccessMethods::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	if(m_idIsSet) {
		returnList.push_back(22);
	}
	if(m_dnsSd_mDnsIsSet) {
		returnList.push_back(23);
	}
	if(m_dnsIsSet) {
		returnList.push_back(24);
	}
	return returnList;
}
// Override the base functionality //
ValueType AccessMethods::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	if(c_hashKey == 305) {
		r_valueString = m_id;
		return VALUE_STRING;
	}
	if(c_hashKey == 108804) {
		r_valueString = "";
		return VALUE_EMPTY_LIST;
	}
	if(c_hashKey == 780) {
		r_valueString = m_dns;
		return VALUE_STRING;
	}
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void AccessMethods::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	if(c_hashKey == 305) {
		setId(c_stringValue);
		return;
	}
	if(c_hashKey == 108804) {
		setDnsSd_mDns();
		return;
	}
	if(c_hashKey == 780) {
		setDns(c_stringValue);
		return;
	}
}
xs_string AccessMethods::getId(void) const
{
	if(m_idIsSet) {
		return m_id;
	}
	return xs_string();
}
bool AccessMethods::getIdIsSet(void) const
{
	return m_idIsSet;
}
bool AccessMethods::getDnsSd_mDnsIsSet(void) const
{
	return m_dnsSd_mDnsIsSet;
}
xs_string AccessMethods::getDns(void) const
{
	if(m_dnsIsSet) {
		return m_dns;
	}
	return xs_string();
}
bool AccessMethods::getDnsIsSet(void) const
{
	return m_dnsIsSet;
}

void AccessMethods::setId(const xs_string& c_value)
{
	m_id = c_value;
	m_idIsSet = true;
}
void AccessMethods::cleanId(void)
{
	m_id = xs_string();
	m_idIsSet = false;
}
void AccessMethods::setDnsSd_mDns()
{
	m_dnsSd_mDnsIsSet = true;
}
void AccessMethods::cleanDnsSd_mDns(void)
{
	m_dnsSd_mDnsIsSet = false;
}
void AccessMethods::setDns(const xs_string& c_value)
{
	m_dns = c_value;
	m_dnsIsSet = true;
}
void AccessMethods::cleanDns(void)
{
	m_dns = xs_string();
	m_dnsIsSet = false;
}

/**
 *  @brief ClassDnsSd_mDns 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ClassDnsSd_mDns.h"

using namespace keo_ship;

ClassDnsSd_mDns::ClassDnsSd_mDns ()
    : CShipDataClass() 
{ 
}


ClassDnsSd_mDns::~ClassDnsSd_mDns ()
{
}
// Override the base functionality //
bool ClassDnsSd_mDns::isSet(void) const
{
	return true;
}
// Override the base functionality //
ShipDataType ClassDnsSd_mDns::getDataType(void) const
{
	return CLASS_DNS_SD_M_DNS_TYPE;
}
// Override the base functionality //
CShipDataClass* ClassDnsSd_mDns::SetMemberIsSetAndReturnPointer(int c_hashKey)
{
	(void)c_hashKey;
	return NULL;
}
// Override the base functionality //
std::vector<int32_t> ClassDnsSd_mDns::getListOfSetMembers() const
{
	std::vector<int32_t> returnList;
	return returnList;
}
// Override the base functionality //
ValueType ClassDnsSd_mDns::getSimpleMemberAsString(int c_hashKey, std::string& r_valueString)
{
	(void)c_hashKey;(void)r_valueString;
	return VALUE_NOT_DEFINED;
}
// Override the base functionality //
void ClassDnsSd_mDns::setSimpleMemberAsString(int c_hashKey, const char* c_stringValue, ValueType c_valueType)
{
(void)c_valueType;
	(void)c_hashKey;(void)c_stringValue;(void)c_valueType;
}


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
 *  @brief ConnectionHelloPhase 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionHelloPhase.h"

using namespace keo_ship;

// Strings of the enum data type
const char* ConnectionHelloPhase::enumString[3] = { 
	"aborted"
	,"ready"
	,"pending"
    
};
ConnectionHelloPhase::ConnectionHelloPhase(const std::string& c_text)
{
	setFromString(c_text);
}
ConnectionHelloPhase::enumConnectionHelloPhase ConnectionHelloPhase::fromString(const std::string& c_text)
{
    for(int i = 0; i < 3; i++) {
        if(c_text.compare(ConnectionHelloPhase::enumString[i]) == 0) {
            return (ConnectionHelloPhase::enumConnectionHelloPhase)i;
        }
    }
	return ConnectionHelloPhase::CONNECTIONHELLOPHASE_UNDEFINED__;
}
void ConnectionHelloPhase::setFromString(const std::string& c_text)
{
	m_data = ConnectionHelloPhase::fromString(c_text);
}
ConnectionHelloPhase::enumConnectionHelloPhase ConnectionHelloPhase::getData() const
{
	return m_data;
}
std::string ConnectionHelloPhase::getDataString() const
{
	if(m_data>=0) {
		return ConnectionHelloPhase::enumString[m_data];
	}
	return "";
}
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
 *  @brief ProtocolHandshakeType 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ProtocolHandshakeType.h"

using namespace keo_ship;

// Strings of the enum data type
const char* ProtocolHandshakeType::enumString[2] = { 
	"select"
	,"announceMax"
    
};
ProtocolHandshakeType::ProtocolHandshakeType(const std::string& c_text)
{
	setFromString(c_text);
}
ProtocolHandshakeType::enumProtocolHandshakeType ProtocolHandshakeType::fromString(const std::string& c_text)
{
    for(int i = 0; i < 2; i++) {
        if(c_text.compare(ProtocolHandshakeType::enumString[i]) == 0) {
            return (ProtocolHandshakeType::enumProtocolHandshakeType)i;
        }
    }
	return ProtocolHandshakeType::PROTOCOLHANDSHAKETYPE_UNDEFINED__;
}
void ProtocolHandshakeType::setFromString(const std::string& c_text)
{
	m_data = ProtocolHandshakeType::fromString(c_text);
}
ProtocolHandshakeType::enumProtocolHandshakeType ProtocolHandshakeType::getData() const
{
	return m_data;
}
std::string ProtocolHandshakeType::getDataString() const
{
	if(m_data>=0) {
		return ProtocolHandshakeType::enumString[m_data];
	}
	return "";
}
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
 *  @brief PinState 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/PinState.h"

using namespace keo_ship;

// Strings of the enum data type
const char* PinState::enumString[4] = { 
	"none"
	,"pinOk"
	,"optional"
	,"required"
    
};
PinState::PinState(const std::string& c_text)
{
	setFromString(c_text);
}
PinState::enumPinState PinState::fromString(const std::string& c_text)
{
    for(int i = 0; i < 4; i++) {
        if(c_text.compare(PinState::enumString[i]) == 0) {
            return (PinState::enumPinState)i;
        }
    }
	return PinState::PINSTATE_UNDEFINED__;
}
void PinState::setFromString(const std::string& c_text)
{
	m_data = PinState::fromString(c_text);
}
PinState::enumPinState PinState::getData() const
{
	return m_data;
}
std::string PinState::getDataString() const
{
	if(m_data>=0) {
		return PinState::enumString[m_data];
	}
	return "";
}
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

#include "keo_ship/PinInputPermission.h"

using namespace keo_ship;

// Strings of the enum data type
const char* PinInputPermission::enumString[2] = { 
	"ok"
	,"busy"
    
};
PinInputPermission::PinInputPermission(const std::string& c_text)
{
	setFromString(c_text);
}
PinInputPermission::enumPinInputPermission PinInputPermission::fromString(const std::string& c_text)
{
    for(int i = 0; i < 2; i++) {
        if(c_text.compare(PinInputPermission::enumString[i]) == 0) {
            return (PinInputPermission::enumPinInputPermission)i;
        }
    }
	return PinInputPermission::PININPUTPERMISSION_UNDEFINED__;
}
void PinInputPermission::setFromString(const std::string& c_text)
{
	m_data = PinInputPermission::fromString(c_text);
}
PinInputPermission::enumPinInputPermission PinInputPermission::getData() const
{
	return m_data;
}
std::string PinInputPermission::getDataString() const
{
	if(m_data>=0) {
		return PinInputPermission::enumString[m_data];
	}
	return "";
}
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
 *  @brief ConnectionClosePhase 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionClosePhase.h"

using namespace keo_ship;

// Strings of the enum data type
const char* ConnectionClosePhase::enumString[2] = { 
	"confirm"
	,"announce"
    
};
ConnectionClosePhase::ConnectionClosePhase(const std::string& c_text)
{
	setFromString(c_text);
}
ConnectionClosePhase::enumConnectionClosePhase ConnectionClosePhase::fromString(const std::string& c_text)
{
    for(int i = 0; i < 2; i++) {
        if(c_text.compare(ConnectionClosePhase::enumString[i]) == 0) {
            return (ConnectionClosePhase::enumConnectionClosePhase)i;
        }
    }
	return ConnectionClosePhase::CONNECTIONCLOSEPHASE_UNDEFINED__;
}
void ConnectionClosePhase::setFromString(const std::string& c_text)
{
	m_data = ConnectionClosePhase::fromString(c_text);
}
ConnectionClosePhase::enumConnectionClosePhase ConnectionClosePhase::getData() const
{
	return m_data;
}
std::string ConnectionClosePhase::getDataString() const
{
	if(m_data>=0) {
		return ConnectionClosePhase::enumString[m_data];
	}
	return "";
}
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
 *  @brief ConnectionCloseReason 
 *
 *  @par    This is an automatically generated class
 */

#include "keo_ship/ConnectionCloseReason.h"

using namespace keo_ship;

// Strings of the enum data type
const char* ConnectionCloseReason::enumString[2] = { 
	"removedConnection"
	,"unspecific"
    
};
ConnectionCloseReason::ConnectionCloseReason(const std::string& c_text)
{
	setFromString(c_text);
}
ConnectionCloseReason::enumConnectionCloseReason ConnectionCloseReason::fromString(const std::string& c_text)
{
    for(int i = 0; i < 2; i++) {
        if(c_text.compare(ConnectionCloseReason::enumString[i]) == 0) {
            return (ConnectionCloseReason::enumConnectionCloseReason)i;
        }
    }
	return ConnectionCloseReason::CONNECTIONCLOSEREASON_UNDEFINED__;
}
void ConnectionCloseReason::setFromString(const std::string& c_text)
{
	m_data = ConnectionCloseReason::fromString(c_text);
}
ConnectionCloseReason::enumConnectionCloseReason ConnectionCloseReason::getData() const
{
	return m_data;
}
std::string ConnectionCloseReason::getDataString() const
{
	if(m_data>=0) {
		return ConnectionCloseReason::enumString[m_data];
	}
	return "";
}

