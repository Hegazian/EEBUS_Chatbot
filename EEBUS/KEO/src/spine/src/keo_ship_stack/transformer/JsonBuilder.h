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
 *  @brief Class structure
 *
 *  @par    Module description
 *          JsonBuilder creates from a SHIP data class the corresponding JSON text
 *
 */

#ifndef KEO_SHIP_STACK_TRANSFORMER_SRC_JSON_BUILDER_H
#define KEO_SHIP_STACK_TRANSFORMER_SRC_JSON_BUILDER_H

/** @addtogroup keo_ship_stack
 * @{
 */

#include "keo_ship/CShipDataClass.h"
#include <string>
#include <vector>

namespace keo_ship
{
/* ****************************************************************************** *
 *  class JsonBuilder: definition                                                *
 * ****************************************************************************** */

/** Builder for the json */
class JsonBuilder
{
public:
    /** Constructor
     * Constructor of empty class.
     */
    JsonBuilder();

    /** reset JsonBuilder
     */
    void reset();

    /** getJsonFromClass
     *
     * @param pDataClass input class
     * @param r_jsonArray reference to the resulting json array
     * @return true, if message is complete build
     */
    bool getJsonFromClass(keo_ship::CShipDataClass* pDataClass, std::vector<char>& r_jsonArray, char messageType);

    static int32_t getHashValue(const std::string& c_string);
    static void writeKey(const std::string& c_key, std::vector<char>& r_jsonArray);
    static void writeEmptyArray(const std::string& c_key, std::vector<char>& r_jsonArray);
    static void writeNull(const std::string& c_key, std::vector<char>& r_jsonArray);
    static void writeValueString(const std::string& c_key, const std::string& c_value, std::vector<char>& r_jsonArray);
    static void writeValue(const std::string& c_key, const std::string& c_value, std::vector<char>& r_jsonArray);
    static void writeObjectBegin(std::vector<char>& r_jsonArray);
    static void writeObjectBegin(const std::string& c_key, std::vector<char>& r_jsonArray);
    static void writeArrayBegin(std::vector<char>& r_jsonArray);
    static void writeArrayBegin(const std::string& c_key, std::vector<char>& r_jsonArray);
    static void writeObjectEnd(std::vector<char>& r_jsonArray);
    static void writeArrayEnd(std::vector<char>& r_jsonArray);

private:
    // handle not simple JSON objects - can be called recursive
    void handleDataClass(keo_ship::CShipDataClass* p_dataClass, std::vector<char>& r_jsonArray);

    void writeStartObject(std::vector<char>& r_jsonArray);
    void writeStartObject(const std::string& c_key, std::vector<char>& r_jsonArray);
    void writeStartArray(std::vector<char>& r_jsonArray);
    void writeStartArray(const std::string& c_key, std::vector<char>& r_jsonArray);
    void writeEnd(std::vector<char>& r_jsonArray);

    // helper to count the different brackets (Object = 0, Array = 1)
    std::vector<bool> m_isStartObjectList;
};
} // end namespace keo_ship
/** @}
 */

#endif
