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
 *     @brief      Defines a JSON parser. It creates a data class from a JSON input.
 *
 *     @par        Module description
 *                 TODO module description
 *
 *     @author     KEO GmbH 2014 @n
 *                 All rights reserved !
 */

#ifndef KEO_SHIP_STACK_TRANSFORMER_SRC_JSON_PARSER_H
#define KEO_SHIP_STACK_TRANSFORMER_SRC_JSON_PARSER_H

#include <string>
#include <vector>

namespace keo_ship
{
/* ****************************************************************************** *
 *  class JsonParser: definition                                                *
 * ****************************************************************************** */

/** Parser for the json */
class JsonParser
{
public:
    enum JsonToken
    {
        VALUE_FALSE,
        VALUE_TRUE,
        VALUE_NULL,
        VALUE_NUMBER,
        VALUE_STRING,
        END_ARRAY,
        END_OBJECT,
        KEY_NAME,
        START_ARRAY,
        START_OBJECT,
        END_PARSING
    };

    /** Constructor
     * Constructor of empty class.
     */
    JsonParser();

    /** reset JsonParser
     */
    void reset();

    /** nextToken
     *
     * @return next token
     */
    JsonToken nextToken(const std::vector<char>& c_pJsonArray, std::size_t& r_index);

    /** getCurrentToken
     *
     * @return current token
     */
    JsonToken getCurrentToken() const;

    /** getLastToken
     *
     * @return last token
     */
    JsonToken getLastToken() const;

    /** getCurrentString
     *
     * @return current string
     */
    const std::string& getCurrentString();

private:
    enum ExpectedToken
    {
        EXPECT_COLON,
        EXPECT_KEYNAME,
        EXPECT_VALUE,
        EXPECT_ENDING
    };

    // parsed string
    std::string m_parsedString;
    // saved string contains parsed strings if message is fragmented
    std::string m_savedString;
    // flag to count the quotation marks
    bool m_insideString;
    // length of parsed string
    size_t m_parsedStringIndex;
    // expected token
    ExpectedToken m_expectedToken;
    // current token
    JsonToken m_currentToken;
    // last token
    JsonToken m_lastToken;
};
} // end namespace keo_ship
/** @}
 */

#endif
