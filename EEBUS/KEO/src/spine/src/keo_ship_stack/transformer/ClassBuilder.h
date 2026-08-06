/*
 *     Copyright KEO GmbH 2013 - All rights reserved!
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
 *          The ClassBuilder creates data classes from JSON input
 *
 */

#ifndef KEO_SHIP_STACK_TRANSFORMER_SRC_CLASS_BUILDER_H
#define KEO_SHIP_STACK_TRANSFORMER_SRC_CLASS_BUILDER_H

#include "JsonParser.h"
#include "keo_ship/CShipDataClass.h"

namespace keo_ship
{
/* ****************************************************************************** *
 *  class ClassBuilder: definition                                                *
 * ****************************************************************************** */
class JsonParser;

class ClassBuilder
{
public:
    /** Constructor
     * Constructor of empty class.
     */
    ClassBuilder();

    /** Create a SHIP data class form a JSON message
     *
     * @return true, if created
     */
    bool createDataClassMessage(const std::vector<char>& c_jsonArray, keo_ship::CShipDataClass*& p_dataClass);

private:
    /** checks if the JSON message comes with the checkToken next
     *
     * @return true, if token coming next
     */
    bool checkNextToken(const std::vector<char>& c_jsonArray, std::size_t& r_index, JsonParser::JsonToken c_checkToken);

    /** handle a complex structure
     *
     * @return true, if handled
     */
    bool handleObject(const std::vector<char>& c_jsonArray, std::size_t& r_index);

    /** handle JSON token
     *
     * @return true, if handled
     */
    bool handleToken(JsonParser::JsonToken c_token, const std::string& c_tokenValue);

    /** create a hash value from a string
     *
     * @return hash value
     */
    int32_t getHashValue(const std::string& c_string);

    // JSON parser
    JsonParser m_parser;

    // hierarchy level inside the JSON structure
    std::vector<bool> m_jsonHierarchy;

    // flag to indicate that the parser get an empty error
    bool m_isEmptyArray;

    // helper list for JSON lists
    std::vector<keo_ship::ShipDataType> m_listDataTypeList;

    // helper list for remember each class in each hierarchy level
    std::vector<keo_ship::CShipDataClass*> m_baseDataClassList;

    // flag, if JSON object is an array
    bool m_isArrayElement;

    // key name as hash value (faster string compare)
    int32_t m_hashKeyName;

    // value string for a key
    std::string m_value;

    // active data class
    keo_ship::CShipDataClass* m_lastObjectPtr;
};
} // end namespace keo_ship
/** @}
 */

#endif
