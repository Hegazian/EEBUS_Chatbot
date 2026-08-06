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

#ifndef GENERATE_RANDOM__H__
#define GENERATE_RANDOM__H__

/** @addtogroup ShipMessageLibrary
 * @{
 */
#include "keo_ship/ShipHeader.h"

namespace keo_ship {

class GenerateRandom
{

public:

    /** initialiseBasicTypeLimits
     *
     * Initialise the min and max values for the basic types.
     * @param booleanAlwaysTrue if generate always true for Boolean (useful for isSet)
     */
static void initialiseBasicTypeLimits(bool booleanAlwaysTrue = false);

    /** setMaximumForInteger
     *
     * Set the maximum for integer which is used to generate random lists.
     * High values have the problem 
     * that unit test with random objects takes very long
     * @param c_maxInt Maximum value to set
     */
static void setMaximumForInteger(int c_maxInt);

    /** getRandomDataFromDataType
     *
     * Create a data class and fills with random data.
     * @param c_type type to generate random data for
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object pointer
     */
static CShipDataClass* getRandomDataFromDataType(ShipDataType c_type, bool c_generateInvalid = false);

    /** generateConnectionHelloPhase
     *
     * Random generation of a ConnectionHelloPhase object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionHelloPhase generateConnectionHelloPhase(bool c_generateInvalid = false);

    /** generateConnectionHello
     *
     * Random generation of a ConnectionHello object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionHello generateConnectionHello(bool c_generateInvalid = false);

    /** generateMessageProtocolFormats
     *
     * Random generation of a MessageProtocolFormats object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static MessageProtocolFormats generateMessageProtocolFormats(bool c_generateInvalid = false);

    /** generateProtocolHandshakeType
     *
     * Random generation of a ProtocolHandshakeType object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ProtocolHandshakeType generateProtocolHandshakeType(bool c_generateInvalid = false);

    /** generateMessageProtocolHandshake
     *
     * Random generation of a MessageProtocolHandshake object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static MessageProtocolHandshake generateMessageProtocolHandshake(bool c_generateInvalid = false);

    /** generateClassVersion
     *
     * Random generation of a ClassVersion object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ClassVersion generateClassVersion(bool c_generateInvalid = false);

    /** generateMessageProtocolHandshakeError
     *
     * Random generation of a MessageProtocolHandshakeError object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static MessageProtocolHandshakeError generateMessageProtocolHandshakeError(bool c_generateInvalid = false);

    /** generatePinState
     *
     * Random generation of a PinState object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static PinState generatePinState(bool c_generateInvalid = false);

    /** generatePinInputPermission
     *
     * Random generation of a PinInputPermission object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static PinInputPermission generatePinInputPermission(bool c_generateInvalid = false);

    /** generateConnectionPinState
     *
     * Random generation of a ConnectionPinState object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionPinState generateConnectionPinState(bool c_generateInvalid = false);

    /** generateConnectionPinInput
     *
     * Random generation of a ConnectionPinInput object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionPinInput generateConnectionPinInput(bool c_generateInvalid = false);

    /** generateConnectionPinError
     *
     * Random generation of a ConnectionPinError object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionPinError generateConnectionPinError(bool c_generateInvalid = false);

    /** generateHeader
     *
     * Random generation of a Header object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static Header generateHeader(bool c_generateInvalid = false);

    /** generateExtension
     *
     * Random generation of a Extension object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static Extension generateExtension(bool c_generateInvalid = false);

    /** generateData
     *
     * Random generation of a Data object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static Data generateData(bool c_generateInvalid = false);

    /** generateConnectionClosePhase
     *
     * Random generation of a ConnectionClosePhase object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionClosePhase generateConnectionClosePhase(bool c_generateInvalid = false);

    /** generateConnectionCloseReason
     *
     * Random generation of a ConnectionCloseReason object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionCloseReason generateConnectionCloseReason(bool c_generateInvalid = false);

    /** generateConnectionClose
     *
     * Random generation of a ConnectionClose object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ConnectionClose generateConnectionClose(bool c_generateInvalid = false);

    /** generateAccessMethodsRequest
     *
     * Random generation of a AccessMethodsRequest object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static AccessMethodsRequest generateAccessMethodsRequest(bool c_generateInvalid = false);

    /** generateAccessMethods
     *
     * Random generation of a AccessMethods object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static AccessMethods generateAccessMethods(bool c_generateInvalid = false);

    /** generateClassDnsSd_mDns
     *
     * Random generation of a ClassDnsSd_mDns object.
     * @param c_generateInvalid if true, it generates an invalid object
     * @return generated random object
     */
static ClassDnsSd_mDns generateClassDnsSd_mDns(bool c_generateInvalid = false);



private:
    // Empty Constructor //
    GenerateRandom();
    // Empty Destructor //
    ~GenerateRandom();
};
} // end namespace keo_ship
/** @}
 */
#endif

