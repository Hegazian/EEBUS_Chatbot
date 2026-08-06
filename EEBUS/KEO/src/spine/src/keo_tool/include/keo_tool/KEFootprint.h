/*
 *     Copyright KEO GmbH 2015 - All rights reserved!
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
 *     @file       Thread_pthread.h
 *     @brief      Thread class declaration
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#ifndef _KEO_UTIL_FOOTPRINT_H_
#define _KEO_UTIL_FOOTPRINT_H_

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string>

/** @ingroup KEOToolsLibrary
 * @{
 */

namespace keo_tool
{

/**
 * @class KEFootprint
 * @brief Manages one KEFootprint.
 * @ingroup     keo_util
 */
class KEFootprint
{
public:
    KEFootprint();
    virtual ~KEFootprint();

public:
    /**
     *  Returns information about memory and cpu usage
     *  @return On success, execute() returns 0; on error, it returns an error
     */

    const std::string& getload();

private:
    int addOutput(const char* format, ...);
    int getloadavg(double loadavg[], int nelem);
    int parseLine(char* line);
    int getVirtualMemCurrProcessHelper(const char*);
    int getVirtualMemCurrProcess();
    int getPeakVirtualMemCurrProcess();
    int getPhysicalMemCurrProcess();

    std::string m_output;
};

} // namespace

/** @}
 * end of file
 */
#endif /* _KEO_UTIL_FOOTPRINT_H_ */
