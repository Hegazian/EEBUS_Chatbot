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
 *  @brief Generate comparison Ship data class functions 
 *
 *  @par    This is an automatically generated class
 *
 */

#include <QDebug>
#include "keo_ship/GenerateComparison.h"
// for std::abs:
#include <cmath>

using namespace keo_ship;
bool GenerateComparison::compareConnectionHello(const ConnectionHello& c_connectionHello_l, const ConnectionHello& c_connectionHello_r)
{
	if(c_connectionHello_l.getPhaseIsSet() != c_connectionHello_r.getPhaseIsSet()) {
		qWarning() << "c_connectionHello_l.getPhaseIsSet() != c_connectionHello_r.getPhaseIsSet()";
		return false;
	}
	if(c_connectionHello_l.getPhaseIsSet()) {
		if(c_connectionHello_l.getPhase().getData() != c_connectionHello_r.getPhase().getData()) {
			qWarning() << "c_connectionHello_l.getPhase().getData() != c_connectionHello_r.getPhase().getData()";
			return false;
		}
	}
	if(c_connectionHello_l.getWaitingIsSet() != c_connectionHello_r.getWaitingIsSet()) {
		qWarning() << "c_connectionHello_l.getWaitingIsSet() != c_connectionHello_r.getWaitingIsSet()";
		return false;
	}
	if(c_connectionHello_l.getWaitingIsSet()) {
		if(c_connectionHello_l.getWaiting() != c_connectionHello_r.getWaiting()) {
			qWarning() << "c_connectionHello_l.getWaiting() != c_connectionHello_r.getWaiting()";
			return false;
		}
	}
	if(c_connectionHello_l.getProlongationRequestIsSet() != c_connectionHello_r.getProlongationRequestIsSet()) {
		qWarning() << "c_connectionHello_l.getProlongationRequestIsSet() != c_connectionHello_r.getProlongationRequestIsSet()";
		return false;
	}
	if(c_connectionHello_l.getProlongationRequestIsSet()) {
		if(c_connectionHello_l.getProlongationRequest() != c_connectionHello_r.getProlongationRequest()) {
			qWarning() << "c_connectionHello_l.getProlongationRequest() != c_connectionHello_r.getProlongationRequest()";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareMessageProtocolFormats(const MessageProtocolFormats& c_messageProtocolFormats_l, const MessageProtocolFormats& c_messageProtocolFormats_r)
{
	return true;
}
bool GenerateComparison::compareMessageProtocolHandshake(const MessageProtocolHandshake& c_messageProtocolHandshake_l, const MessageProtocolHandshake& c_messageProtocolHandshake_r)
{
	if(c_messageProtocolHandshake_l.getHandshakeTypeIsSet() != c_messageProtocolHandshake_r.getHandshakeTypeIsSet()) {
		qWarning() << "c_messageProtocolHandshake_l.getHandshakeTypeIsSet() != c_messageProtocolHandshake_r.getHandshakeTypeIsSet()";
		return false;
	}
	if(c_messageProtocolHandshake_l.getHandshakeTypeIsSet()) {
		if(c_messageProtocolHandshake_l.getHandshakeType().getData() != c_messageProtocolHandshake_r.getHandshakeType().getData()) {
			qWarning() << "c_messageProtocolHandshake_l.getHandshakeType().getData() != c_messageProtocolHandshake_r.getHandshakeType().getData()";
			return false;
		}
	}
	if(c_messageProtocolHandshake_l.getVersionIsSet() != c_messageProtocolHandshake_r.getVersionIsSet()) {
		qWarning() << "c_messageProtocolHandshake_l.getVersionIsSet() != c_messageProtocolHandshake_r.getVersionIsSet()";
		return false;
	}
	if(c_messageProtocolHandshake_l.getVersionIsSet()) {
		if(!compareClassVersion(c_messageProtocolHandshake_l.getVersion(), c_messageProtocolHandshake_r.getVersion())) {
			qWarning() << "!compareClassVersion(c_messageProtocolHandshake_l.getVersion(), c_messageProtocolHandshake_r.getVersion())";
			return false;
		}
	}
	if(c_messageProtocolHandshake_l.getFormatsIsSet() != c_messageProtocolHandshake_r.getFormatsIsSet()) {
		qWarning() << "c_messageProtocolHandshake_l.getFormatsIsSet() != c_messageProtocolHandshake_r.getFormatsIsSet()";
		return false;
	}
	if(c_messageProtocolHandshake_l.getFormatsIsSet()) {
		if(!compareMessageProtocolFormats(c_messageProtocolHandshake_l.getFormats(), c_messageProtocolHandshake_r.getFormats())) {
			qWarning() << "!compareMessageProtocolFormats(c_messageProtocolHandshake_l.getFormats(), c_messageProtocolHandshake_r.getFormats())";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareClassVersion(const ClassVersion& c_classVersion_l, const ClassVersion& c_classVersion_r)
{
	if(c_classVersion_l.getMajorIsSet() != c_classVersion_r.getMajorIsSet()) {
		qWarning() << "c_classVersion_l.getMajorIsSet() != c_classVersion_r.getMajorIsSet()";
		return false;
	}
	if(c_classVersion_l.getMajorIsSet()) {
		if(c_classVersion_l.getMajor() != c_classVersion_r.getMajor()) {
			qWarning() << "c_classVersion_l.getMajor() != c_classVersion_r.getMajor()";
			return false;
		}
	}
	if(c_classVersion_l.getMinorIsSet() != c_classVersion_r.getMinorIsSet()) {
		qWarning() << "c_classVersion_l.getMinorIsSet() != c_classVersion_r.getMinorIsSet()";
		return false;
	}
	if(c_classVersion_l.getMinorIsSet()) {
		if(c_classVersion_l.getMinor() != c_classVersion_r.getMinor()) {
			qWarning() << "c_classVersion_l.getMinor() != c_classVersion_r.getMinor()";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareMessageProtocolHandshakeError(const MessageProtocolHandshakeError& c_messageProtocolHandshakeError_l, const MessageProtocolHandshakeError& c_messageProtocolHandshakeError_r)
{
	if(c_messageProtocolHandshakeError_l.getErrorIsSet() != c_messageProtocolHandshakeError_r.getErrorIsSet()) {
		qWarning() << "c_messageProtocolHandshakeError_l.getErrorIsSet() != c_messageProtocolHandshakeError_r.getErrorIsSet()";
		return false;
	}
	if(c_messageProtocolHandshakeError_l.getErrorIsSet()) {
		if(c_messageProtocolHandshakeError_l.getError() != c_messageProtocolHandshakeError_r.getError()) {
			qWarning() << "c_messageProtocolHandshakeError_l.getError() != c_messageProtocolHandshakeError_r.getError()";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareConnectionPinState(const ConnectionPinState& c_connectionPinState_l, const ConnectionPinState& c_connectionPinState_r)
{
	if(c_connectionPinState_l.getPinStateIsSet() != c_connectionPinState_r.getPinStateIsSet()) {
		qWarning() << "c_connectionPinState_l.getPinStateIsSet() != c_connectionPinState_r.getPinStateIsSet()";
		return false;
	}
	if(c_connectionPinState_l.getPinStateIsSet()) {
		if(c_connectionPinState_l.getPinState().getData() != c_connectionPinState_r.getPinState().getData()) {
			qWarning() << "c_connectionPinState_l.getPinState().getData() != c_connectionPinState_r.getPinState().getData()";
			return false;
		}
	}
	if(c_connectionPinState_l.getInputPermissionIsSet() != c_connectionPinState_r.getInputPermissionIsSet()) {
		qWarning() << "c_connectionPinState_l.getInputPermissionIsSet() != c_connectionPinState_r.getInputPermissionIsSet()";
		return false;
	}
	if(c_connectionPinState_l.getInputPermissionIsSet()) {
		if(c_connectionPinState_l.getInputPermission().getData() != c_connectionPinState_r.getInputPermission().getData()) {
			qWarning() << "c_connectionPinState_l.getInputPermission().getData() != c_connectionPinState_r.getInputPermission().getData()";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareConnectionPinInput(const ConnectionPinInput& c_connectionPinInput_l, const ConnectionPinInput& c_connectionPinInput_r)
{
	if(c_connectionPinInput_l.getPinIsSet() != c_connectionPinInput_r.getPinIsSet()) {
		qWarning() << "c_connectionPinInput_l.getPinIsSet() != c_connectionPinInput_r.getPinIsSet()";
		return false;
	}
	if(c_connectionPinInput_l.getPinIsSet()) {
		if((c_connectionPinInput_l.getPin().length() != c_connectionPinInput_r.getPin().length()) || (c_connectionPinInput_l.getPin().compare(c_connectionPinInput_r.getPin()) != 0)) {
			qWarning() << "(c_connectionPinInput_l.getPin().length() != c_connectionPinInput_r.getPin().length()) || (c_connectionPinInput_l.getPin().compare(c_connectionPinInput_r.getPin()) != 0)";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareConnectionPinError(const ConnectionPinError& c_connectionPinError_l, const ConnectionPinError& c_connectionPinError_r)
{
	if(c_connectionPinError_l.getErrorIsSet() != c_connectionPinError_r.getErrorIsSet()) {
		qWarning() << "c_connectionPinError_l.getErrorIsSet() != c_connectionPinError_r.getErrorIsSet()";
		return false;
	}
	if(c_connectionPinError_l.getErrorIsSet()) {
		if(c_connectionPinError_l.getError() != c_connectionPinError_r.getError()) {
			qWarning() << "c_connectionPinError_l.getError() != c_connectionPinError_r.getError()";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareHeader(const Header& c_header_l, const Header& c_header_r)
{
	if(c_header_l.getProtocolIdIsSet() != c_header_r.getProtocolIdIsSet()) {
		qWarning() << "c_header_l.getProtocolIdIsSet() != c_header_r.getProtocolIdIsSet()";
		return false;
	}
	if(c_header_l.getProtocolIdIsSet()) {
		if((c_header_l.getProtocolId().length() != c_header_r.getProtocolId().length()) || (c_header_l.getProtocolId().compare(c_header_r.getProtocolId()) != 0)) {
			qWarning() << "(c_header_l.getProtocolId().length() != c_header_r.getProtocolId().length()) || (c_header_l.getProtocolId().compare(c_header_r.getProtocolId()) != 0)";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareExtension(const Extension& c_extension_l, const Extension& c_extension_r)
{
	if(c_extension_l.getExtensionIdIsSet() != c_extension_r.getExtensionIdIsSet()) {
		qWarning() << "c_extension_l.getExtensionIdIsSet() != c_extension_r.getExtensionIdIsSet()";
		return false;
	}
	if(c_extension_l.getExtensionIdIsSet()) {
		if((c_extension_l.getExtensionId().length() != c_extension_r.getExtensionId().length()) || (c_extension_l.getExtensionId().compare(c_extension_r.getExtensionId()) != 0)) {
			qWarning() << "(c_extension_l.getExtensionId().length() != c_extension_r.getExtensionId().length()) || (c_extension_l.getExtensionId().compare(c_extension_r.getExtensionId()) != 0)";
			return false;
		}
	}
	if(c_extension_l.getBinaryIsSet() != c_extension_r.getBinaryIsSet()) {
		qWarning() << "c_extension_l.getBinaryIsSet() != c_extension_r.getBinaryIsSet()";
		return false;
	}
	if(c_extension_l.getBinaryIsSet()) {
		if(c_extension_l.getBinary() != c_extension_r.getBinary()) {
			qWarning() << "c_extension_l.getBinary() != c_extension_r.getBinary()";
			return false;
		}
	}
	if(c_extension_l.getStringIsSet() != c_extension_r.getStringIsSet()) {
		qWarning() << "c_extension_l.getStringIsSet() != c_extension_r.getStringIsSet()";
		return false;
	}
	if(c_extension_l.getStringIsSet()) {
		if((c_extension_l.getString().length() != c_extension_r.getString().length()) || (c_extension_l.getString().compare(c_extension_r.getString()) != 0)) {
			qWarning() << "(c_extension_l.getString().length() != c_extension_r.getString().length()) || (c_extension_l.getString().compare(c_extension_r.getString()) != 0)";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareData(const Data& c_data_l, const Data& c_data_r)
{
	if(c_data_l.getHeaderIsSet() != c_data_r.getHeaderIsSet()) {
		qWarning() << "c_data_l.getHeaderIsSet() != c_data_r.getHeaderIsSet()";
		return false;
	}
	if(c_data_l.getHeaderIsSet()) {
		if(!compareHeader(c_data_l.getHeader(), c_data_r.getHeader())) {
			qWarning() << "!compareHeader(c_data_l.getHeader(), c_data_r.getHeader())";
			return false;
		}
	}
	if(c_data_l.getPayloadIsSet() != c_data_r.getPayloadIsSet()) {
		qWarning() << "c_data_l.getPayloadIsSet() != c_data_r.getPayloadIsSet()";
		return false;
	}
	if(c_data_l.getPayloadIsSet()) {
		if((c_data_l.getPayload().length() != c_data_r.getPayload().length()) || (c_data_l.getPayload().compare(c_data_r.getPayload()) != 0)) {
			qWarning() << "(c_data_l.getPayload().length() != c_data_r.getPayload().length()) || (c_data_l.getPayload().compare(c_data_r.getPayload()) != 0)";
			return false;
		}
	}
	if(c_data_l.getExtensionIsSet() != c_data_r.getExtensionIsSet()) {
		qWarning() << "c_data_l.getExtensionIsSet() != c_data_r.getExtensionIsSet()";
		return false;
	}
	if(c_data_l.getExtensionIsSet()) {
		if(!compareExtension(c_data_l.getExtension(), c_data_r.getExtension())) {
			qWarning() << "!compareExtension(c_data_l.getExtension(), c_data_r.getExtension())";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareConnectionClose(const ConnectionClose& c_connectionClose_l, const ConnectionClose& c_connectionClose_r)
{
	if(c_connectionClose_l.getPhaseIsSet() != c_connectionClose_r.getPhaseIsSet()) {
		qWarning() << "c_connectionClose_l.getPhaseIsSet() != c_connectionClose_r.getPhaseIsSet()";
		return false;
	}
	if(c_connectionClose_l.getPhaseIsSet()) {
		if(c_connectionClose_l.getPhase().getData() != c_connectionClose_r.getPhase().getData()) {
			qWarning() << "c_connectionClose_l.getPhase().getData() != c_connectionClose_r.getPhase().getData()";
			return false;
		}
	}
	if(c_connectionClose_l.getMaxTimeIsSet() != c_connectionClose_r.getMaxTimeIsSet()) {
		qWarning() << "c_connectionClose_l.getMaxTimeIsSet() != c_connectionClose_r.getMaxTimeIsSet()";
		return false;
	}
	if(c_connectionClose_l.getMaxTimeIsSet()) {
		if(c_connectionClose_l.getMaxTime() != c_connectionClose_r.getMaxTime()) {
			qWarning() << "c_connectionClose_l.getMaxTime() != c_connectionClose_r.getMaxTime()";
			return false;
		}
	}
	if(c_connectionClose_l.getReasonIsSet() != c_connectionClose_r.getReasonIsSet()) {
		qWarning() << "c_connectionClose_l.getReasonIsSet() != c_connectionClose_r.getReasonIsSet()";
		return false;
	}
	if(c_connectionClose_l.getReasonIsSet()) {
		if(c_connectionClose_l.getReason().getData() != c_connectionClose_r.getReason().getData()) {
			qWarning() << "c_connectionClose_l.getReason().getData() != c_connectionClose_r.getReason().getData()";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareAccessMethodsRequest(const AccessMethodsRequest& c_accessMethodsRequest_l, const AccessMethodsRequest& c_accessMethodsRequest_r)
{
	(void)c_accessMethodsRequest_l;
	(void)c_accessMethodsRequest_r;
	return true;
}
bool GenerateComparison::compareAccessMethods(const AccessMethods& c_accessMethods_l, const AccessMethods& c_accessMethods_r)
{
	if(c_accessMethods_l.getIdIsSet() != c_accessMethods_r.getIdIsSet()) {
		qWarning() << "c_accessMethods_l.getIdIsSet() != c_accessMethods_r.getIdIsSet()";
		return false;
	}
	if(c_accessMethods_l.getIdIsSet()) {
		if((c_accessMethods_l.getId().length() != c_accessMethods_r.getId().length()) || (c_accessMethods_l.getId().compare(c_accessMethods_r.getId()) != 0)) {
			qWarning() << "(c_accessMethods_l.getId().length() != c_accessMethods_r.getId().length()) || (c_accessMethods_l.getId().compare(c_accessMethods_r.getId()) != 0)";
			return false;
		}
	}
	if(c_accessMethods_l.getDnsSd_mDnsIsSet() != c_accessMethods_r.getDnsSd_mDnsIsSet()) {
			qWarning() << "c_accessMethods_l.getDnsSd_mDnsIsSet()";
		return false;
	}
	if(c_accessMethods_l.getDnsIsSet() != c_accessMethods_r.getDnsIsSet()) {
		qWarning() << "c_accessMethods_l.getDnsIsSet() != c_accessMethods_r.getDnsIsSet()";
		return false;
	}
	if(c_accessMethods_l.getDnsIsSet()) {
		if((c_accessMethods_l.getDns().length() != c_accessMethods_r.getDns().length()) || (c_accessMethods_l.getDns().compare(c_accessMethods_r.getDns()) != 0)) {
			qWarning() << "(c_accessMethods_l.getDns().length() != c_accessMethods_r.getDns().length()) || (c_accessMethods_l.getDns().compare(c_accessMethods_r.getDns()) != 0)";
			return false;
		}
	}
	return true;
}
bool GenerateComparison::compareClassDnsSd_mDns(const ClassDnsSd_mDns& c_classDnsSd_mDns_l, const ClassDnsSd_mDns& c_classDnsSd_mDns_r)
{
	(void)c_classDnsSd_mDns_l;
	(void)c_classDnsSd_mDns_r;
	return true;
}


