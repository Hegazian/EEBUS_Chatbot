/*
 *     Copyright KEO GmbH 2016 - All rights reserved!
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

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

#include "keo_ship/ShipSecurity.h"

/* ****************************************************************************** *
 *  KEO header files                                                              *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  definition                                                                    *
 * ****************************************************************************** */

namespace keo_ship
{

const unsigned short TrustLevel::TRUST_VALUE_USER_UNTRUSTED = 0;
const unsigned short TrustLevel::TRUST_VALUE_USER_AUTO_ACCEPT = 8;
const unsigned short TrustLevel::TRUST_VALUE_USER_USER_VERIFIED = 32;
const unsigned short TrustLevel::TRUST_VALUE_USER_COMMISSIONED_MIN = 32;
const unsigned short TrustLevel::TRUST_VALUE_USER_COMMISSIONED_MAX = 96;
const unsigned short TrustLevel::TRUST_VALUE_USER_USER_INPUT = 64;

const unsigned short TrustLevel::TRUST_VALUE_PKI_SELF_SIGNED = 0;
const unsigned short TrustLevel::TRUST_VALUE_PKI_SIGNED_MIN = 0;
const unsigned short TrustLevel::TRUST_VALUE_PKI_SIGNED_MAX = 65535;

const unsigned short TrustLevel::TRUST_VALUE_2NDFACTOR_NONE = 0;
const unsigned short TrustLevel::TRUST_VALUE_2NDFACTOR_PIN = 16;
const unsigned short TrustLevel::TRUST_VALUE_2NDFACTOR_PIN_SPECIAL = 32;

} /* namespace keo_ship */
