/*
 *     Copyright KEO GmbH 2019 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright
 * notice.
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

#ifndef KEO_DATAGRAM_CORE_SPINERESULTERRORS_H_
#define KEO_DATAGRAM_CORE_SPINERESULTERRORS_H_

#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * SPINE result error codes, taken from EEBus SPINE Ressource Specification.
 */
namespace SpineResultErrors {

/** \brief OK = 0
 * No error occurred, datagram has been transmitted successfully
 */
extern const xs_unsignedInt OK;

/** \brief General error = 1
 * A problem occurred that does not fit to any of the classes below.
 * Re-sending this datagram does not make sense.
 */
extern const xs_unsignedInt GENERAL_ERROR;

/** \brief Timeout = 2
 * The datagram could not be sent to the receiver due to a temporary failure.
 * Possible reasons for this error are:
 *     - A timeout occurred
 *     - A transmission error occurred
 * Re-sending this datagram does make sense.
 * The application is responsible to implement a retry mechanism.
 */
extern const xs_unsignedInt TIMEOUT;

/** \brief Overload = 3
 * The datagram could not be sent to the receiver due to a temporary failure.
 * Re-sending this datagram does make sense.
 * The application is responsible to implement a retry mechanism.
 */
extern const xs_unsignedInt OVERLOAD;

/** \brief Destination unknown = 4
 * The destination feature for the datagram could not be found.
 * Re-sending this datagram does not make sense.
 */
extern const xs_unsignedInt DESTINATION_UNKNOWN;

/** \brief Destination unreachable = 5
 * A receiver for the datagram could not be reached.
 * Possible reasons for this error are:
 *     - The destination address could not be found
 *     - No application has been registered for the classId on the destination
 * node
 * Re-sending this datagram does not make sense.
 */
extern const xs_unsignedInt DESTINATION_UNREACHABLE;

/** \brief Command not supported = 6
 * The receiver could not handle this command, because the destination feature
 * does not support the operation.
 * Re-sending this datagram does not make sense.
 */
extern const xs_unsignedInt COMMAND_NOT_SUPPORTED;

/** \brief Datagram rejected = 7
 * The receiver could not handle this command, because it could not be parsed.
 * Re-sending this datagram does not make sense.
 */
extern const xs_unsignedInt COMMAND_REJECTED;

/** \brief Restricted function exchange combination not supported = 8
 * The restricted function exchange combination is not supported. Refer to the
 * EEBus SPINE
 * Protocol Specficiation for more information.
 * Re-sending this datagram does not make sense.
 */
extern const xs_unsignedInt
    RESTRICTED_FUNCTION_EXCHANGE_COMBINATION_NOT_SUPPORTED;

/** \brief A binding is neccessary for the sent command = 9
 * The command that has been sent before, requires the sender to have a binding
 * on the target
 * feature.
 * Re-sending this datagram makes sense.
 */
extern const xs_unsignedInt BINDING_IS_NECCESSARY_FOR_THIS_COMMAND;
}

/** @}
 */

} // end namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_SPINERESULTERRORS_H_