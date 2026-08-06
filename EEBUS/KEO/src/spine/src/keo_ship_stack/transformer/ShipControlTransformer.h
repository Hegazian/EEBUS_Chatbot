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
 *     @brief      Defines a transformer object. It uses to parse and build JSON messages.
 *
 *     @par        Module description
 *                 TODO module description
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_TRANSFORMER_SRC_SHIP_CONTROL_TRANSFORMER_H_
#define KEO_SHIP_STACK_TRANSFORMER_SRC_SHIP_CONTROL_TRANSFORMER_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <vector>
/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include "keo_ship/CShipDataClass.h"

namespace keo_ship
{
/* ****************************************************************************** *
 *  class JsonParser: definition                                                *
 * ****************************************************************************** */

class ShipControlTransformer
{
public:
    /**
     * Parse JSON message from input data.
     * @param c_data json message data.
     * @return resulting data class
     */
    static keo_ship::CShipDataClass* createDataClassFromCommissioningMessage(const std::vector<char>& c_data);

    /**
     * Build JSON message form data class.
     * @param pDataClass ship data class pointer.
     * @param r_jsonArray reference to the resulting json array
     * @param c_type SME Message type is first bit of message
     * @return true, if message is complete build
     */
    static bool getJsonFromDataClass(
        keo_ship::CShipDataClass* pDataClass, std::vector<char>& r_jsonArray, char messageType);

private:
    ShipControlTransformer(){};
};
} // end namespace keo_ship

#endif /* KEO_SHIP_STACK_TRANSFORMER_SRC_SHIP_CONTROL_TRANSFORMER_H_ */
