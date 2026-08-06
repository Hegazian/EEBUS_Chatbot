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

#include "ShipControlTransformer.h"
#include "ClassBuilder.h"
#include "JsonBuilder.h"

#define DBG_MODULE_NAME "ShipControlTransformer"

using namespace keo_ship;

keo_ship::CShipDataClass* ShipControlTransformer::createDataClassFromCommissioningMessage(const std::vector<char>& c_data)
{
    ClassBuilder classBuilder;
    keo_ship::CShipDataClass* pShipDataClass = NULL;
    if (classBuilder.createDataClassMessage(c_data, pShipDataClass))
    {
        return pShipDataClass;
    }
    return NULL;
}
bool ShipControlTransformer::getJsonFromDataClass(
    keo_ship::CShipDataClass* pDataClass, std::vector<char>& r_jsonArray, char messageType)
{
    JsonBuilder jsonBuilder;
    return jsonBuilder.getJsonFromClass(pDataClass, r_jsonArray, messageType);
}
