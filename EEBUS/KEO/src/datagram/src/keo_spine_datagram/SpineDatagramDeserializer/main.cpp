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
 *     @brief      Generator of random datagrams
 *
 *     @par        Module description
 *                 This file is a the main file.
 *
 */

#include <algorithm>
#include <iostream>
#include <libgen.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "keo_datagram/core/Datagram.h"
#include "keo_datagram/core/DatagramParserException.h"

#include "FileUtilities.h"

/* COLORS */
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

using namespace keo_datagram;

std::string base_name(std::string const& path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

void removeWhiteSpaces(std::string& s)
{
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " -f <json-file>" << std::endl;
        return 1;
    }
    std::string fileName;
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file")
        {
            if (i + 1 < argc)
            {
                fileName = argv[++i];
            }
            else
            {
                std::cerr << "-f option requires one argument." << std::endl;
                return 1;
            }
        }
    }

    printf("Testing %s: ", base_name(fileName).c_str());

    std::string inputJsonString = FileUtilities::readFile(fileName);

    removeWhiteSpaces(inputJsonString);

    try
    {
        Datagram datagram = Datagram::fromJsonThrows(inputJsonString);
        datagram.parsePayloadThrows();

        std::string outputJsonString = datagram.toJson();
        removeWhiteSpaces(outputJsonString);

        if (inputJsonString != outputJsonString)
        {
            printf(KRED "ERROR (diff):" RST "\n");
            printf(KRED "IN:  " RST "%s\n", inputJsonString.c_str());
            printf(KRED "OUT: " RST "%s\n", outputJsonString.c_str());
            return -1;
        }
        else
        {
            printf(KGRN "OK" RST "\n");
            return 0;
        }
    }
    catch (const DatagramParserException& e)
    {
        printf(KRED "ERROR (parse):\n%s" RST "\n", e.what());
        printf(KRED "IN: " RST "%s\n", inputJsonString.c_str());
        return -2;
    }
}
/** @}
 * end of file
 */
