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

#ifndef KEO_SHIP_STACK_TRANSFORMER_SRC_SHIP_DATA_TRANSFORMER_H_
#define KEO_SHIP_STACK_TRANSFORMER_SRC_SHIP_DATA_TRANSFORMER_H_

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include "keo_ship/Data.h"
/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */

namespace keo_ship
{

// class EEBusTransformer;
/* *****************************************************************************  *
 *  class ShipDataTransformer: definition                                         *
 * ****************************************************************************** */
class ShipDataTransformer
{
public:
    /**
     * Parse JSON message from input data.
     * @param c_jsonArray json message data.
     * @return ship data message.
     */
    static keo_ship::Data* createShipDataMessageFromJson(const std::vector<char>& c_jsonArray);

    /**
     * Create the json representation from a complete ship message data with EEBus payload.
     * @param c_messageData ship message data.
     * @param c_messageData ship message data.
     * @return true, if created.
     */
    static bool getJsonFromMessageData(const keo_ship::Data& c_messageData, std::vector<char>& r_jsonArray);

private:
    ShipDataTransformer(){};
};
} // end namespace keo_ship

#endif /* KEO_SHIP_STACK_TRANSFORMER_SRC_SHIP_DATA_TRANSFORMER_H_ */
