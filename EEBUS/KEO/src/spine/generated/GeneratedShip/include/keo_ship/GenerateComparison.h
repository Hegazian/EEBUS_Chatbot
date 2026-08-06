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

#ifndef SHIP_GENERATE_COMPARISON__H__
#define SHIP_GENERATE_COMPARISON__H__

/** @addtogroup ShipDataClass
 * @{
 */

#include "keo_ship/ShipHeader.h"

namespace keo_ship { 

class GenerateComparison
{

public:

    /** compareConnectionHello
     *
     * Comparison function for ConnectionHello objects.
     * @param c_connectionHello_l left ConnectionHello object
     * @param c_connectionHello_r right ConnectionHello object
     * @return true, if both objects are equal
     */
static bool compareConnectionHello(const ConnectionHello& c_connectionHello_l, const ConnectionHello& c_connectionHello_r);
    /** compareMessageProtocolFormats
     *
     * Comparison function for MessageProtocolFormats objects.
     * @param c_messageProtocolFormats_l left MessageProtocolFormats object
     * @param c_messageProtocolFormats_r right MessageProtocolFormats object
     * @return true, if both objects are equal
     */
static bool compareMessageProtocolFormats(const MessageProtocolFormats& c_messageProtocolFormats_l, const MessageProtocolFormats& c_messageProtocolFormats_r);
    /** compareMessageProtocolHandshake
     *
     * Comparison function for MessageProtocolHandshake objects.
     * @param c_messageProtocolHandshake_l left MessageProtocolHandshake object
     * @param c_messageProtocolHandshake_r right MessageProtocolHandshake object
     * @return true, if both objects are equal
     */
static bool compareMessageProtocolHandshake(const MessageProtocolHandshake& c_messageProtocolHandshake_l, const MessageProtocolHandshake& c_messageProtocolHandshake_r);
    /** compareClassVersion
     *
     * Comparison function for ClassVersion objects.
     * @param c_classVersion_l left ClassVersion object
     * @param c_classVersion_r right ClassVersion object
     * @return true, if both objects are equal
     */
static bool compareClassVersion(const ClassVersion& c_classVersion_l, const ClassVersion& c_classVersion_r);
    /** compareMessageProtocolHandshakeError
     *
     * Comparison function for MessageProtocolHandshakeError objects.
     * @param c_messageProtocolHandshakeError_l left MessageProtocolHandshakeError object
     * @param c_messageProtocolHandshakeError_r right MessageProtocolHandshakeError object
     * @return true, if both objects are equal
     */
static bool compareMessageProtocolHandshakeError(const MessageProtocolHandshakeError& c_messageProtocolHandshakeError_l, const MessageProtocolHandshakeError& c_messageProtocolHandshakeError_r);
    /** compareConnectionPinState
     *
     * Comparison function for ConnectionPinState objects.
     * @param c_connectionPinState_l left ConnectionPinState object
     * @param c_connectionPinState_r right ConnectionPinState object
     * @return true, if both objects are equal
     */
static bool compareConnectionPinState(const ConnectionPinState& c_connectionPinState_l, const ConnectionPinState& c_connectionPinState_r);
    /** compareConnectionPinInput
     *
     * Comparison function for ConnectionPinInput objects.
     * @param c_connectionPinInput_l left ConnectionPinInput object
     * @param c_connectionPinInput_r right ConnectionPinInput object
     * @return true, if both objects are equal
     */
static bool compareConnectionPinInput(const ConnectionPinInput& c_connectionPinInput_l, const ConnectionPinInput& c_connectionPinInput_r);
    /** compareConnectionPinError
     *
     * Comparison function for ConnectionPinError objects.
     * @param c_connectionPinError_l left ConnectionPinError object
     * @param c_connectionPinError_r right ConnectionPinError object
     * @return true, if both objects are equal
     */
static bool compareConnectionPinError(const ConnectionPinError& c_connectionPinError_l, const ConnectionPinError& c_connectionPinError_r);
    /** compareHeader
     *
     * Comparison function for Header objects.
     * @param c_header_l left Header object
     * @param c_header_r right Header object
     * @return true, if both objects are equal
     */
static bool compareHeader(const Header& c_header_l, const Header& c_header_r);
    /** compareExtension
     *
     * Comparison function for Extension objects.
     * @param c_extension_l left Extension object
     * @param c_extension_r right Extension object
     * @return true, if both objects are equal
     */
static bool compareExtension(const Extension& c_extension_l, const Extension& c_extension_r);
    /** compareData
     *
     * Comparison function for Data objects.
     * @param c_data_l left Data object
     * @param c_data_r right Data object
     * @return true, if both objects are equal
     */
static bool compareData(const Data& c_data_l, const Data& c_data_r);
    /** compareConnectionClose
     *
     * Comparison function for ConnectionClose objects.
     * @param c_connectionClose_l left ConnectionClose object
     * @param c_connectionClose_r right ConnectionClose object
     * @return true, if both objects are equal
     */
static bool compareConnectionClose(const ConnectionClose& c_connectionClose_l, const ConnectionClose& c_connectionClose_r);
    /** compareAccessMethodsRequest
     *
     * Comparison function for AccessMethodsRequest objects.
     * @param c_accessMethodsRequest_l left AccessMethodsRequest object
     * @param c_accessMethodsRequest_r right AccessMethodsRequest object
     * @return true, if both objects are equal
     */
static bool compareAccessMethodsRequest(const AccessMethodsRequest& c_accessMethodsRequest_l, const AccessMethodsRequest& c_accessMethodsRequest_r);
    /** compareAccessMethods
     *
     * Comparison function for AccessMethods objects.
     * @param c_accessMethods_l left AccessMethods object
     * @param c_accessMethods_r right AccessMethods object
     * @return true, if both objects are equal
     */
static bool compareAccessMethods(const AccessMethods& c_accessMethods_l, const AccessMethods& c_accessMethods_r);
    /** compareClassDnsSd_mDns
     *
     * Comparison function for ClassDnsSd_mDns objects.
     * @param c_classDnsSd_mDns_l left ClassDnsSd_mDns object
     * @param c_classDnsSd_mDns_r right ClassDnsSd_mDns object
     * @return true, if both objects are equal
     */
static bool compareClassDnsSd_mDns(const ClassDnsSd_mDns& c_classDnsSd_mDns_l, const ClassDnsSd_mDns& c_classDnsSd_mDns_r);


private:

    // Empty Constructor //
    GenerateComparison();
    // Empty Destructor //
    ~GenerateComparison();
};
} // end namespace keo_ship
/** @}
 */
#endif

