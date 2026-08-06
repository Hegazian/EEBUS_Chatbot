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
 *     @file       KEFootprint.cpp
 *     @brief      KEFootprint class definitions
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#include <keo_tool/KEFootprint.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

#include <keo_util/KELogging.h>

namespace keo_tool
{

KEFootprint::KEFootprint()
    : m_output("")
{
}

KEFootprint::~KEFootprint()
{
}

int KEFootprint::getloadavg(double loadavg[], int nelem)
{
    int ret = 0;
    int fd;

    fd = open("/proc/loadavg", O_RDONLY);
    if (fd < 0)
    {
        ret = -1;
    }
    else
    {
        char buf[65], *p;
        ssize_t nread;
        int i;

        nread = read(fd, buf, sizeof buf - 1);
        close(fd);
        if (nread <= 0)
        {
            ret = -1;
        }
        else
        {
            buf[nread - 1] = '\0';

            if (nelem > 3)
            {
                nelem = 3;
            }
            p = buf;
            for (i = 0; i < nelem; ++i)
            {
                char* endp;
                loadavg[i] = strtod(p, &endp);
                if (endp == p)
                {
                    /* This should not happen.  The format of /proc/loadavg
                       must have changed.  Don't return with what we have,
                       signal an error.  */
                    ret = -1;
                    break;
                }
                p = endp;
            }
            ret = i;
        }
    }

    return ret;
}

int KEFootprint::parseLine(char* line)
{
    int i = strlen(line);
    while (*line < '0' || *line > '9')
        line++;
    line[i - 3] = '\0';
    i = atoi(line);
    return i;
}

int KEFootprint::getVirtualMemCurrProcessHelper(const char* token)
{
    // Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, token, strlen(token)) == 0)
        {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int KEFootprint::getVirtualMemCurrProcess()
{
    return getVirtualMemCurrProcessHelper("VmSize:");
}

int KEFootprint::getPeakVirtualMemCurrProcess()
{
    return getVirtualMemCurrProcessHelper("VmPeak:");
}

int KEFootprint::getPhysicalMemCurrProcess()
{
    // Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, "VmRSS:", 6) == 0)
        {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int KEFootprint::addOutput(const char* format, ...)
{
    char buf[1024];
    va_list ap;

    va_start(ap, format);
    int ret = vsnprintf(buf, sizeof(buf), format, ap);
    m_output.append(buf);
    va_end(ap);

    return ret;
}

const std::string& KEFootprint::getload()
{
    // struct rusage usage;
    // ret = getrusage(RUSAGE_SELF, &usage);
    // if (0 == ret)
    // {
    //      addOutput("rusage: ru_utime : %ld.%ld s\n"
    //             , usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    //      addOutput("rusage: ru_stime : %ld.%ld s\n"
    //             , usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    //      addOutput("rusage: ru_maxrss: %ld kb\n"
    //             , usage.ru_maxrss);
    // }
    // else
    // {
    //      addOutput("getrusage() returned errno %d\n", errno);
    // }

    addOutput("\n");
    char filename[2048] = { 0 };
    ssize_t bytes = readlink("/proc/self/exe", filename, sizeof(filename));
    addOutput("Footprint information:\n\n");
    addOutput("ROM:\n----\n");
    if (bytes)
    {
        struct stat st;
        if (stat(filename, &st) == -1)
        {
            addOutput("stat error: errno is %d\n", errno);
        }
        else
        {
            addOutput("%s %d Kb\n", filename, st.st_size / 1024);
        }
    }
    else
    {
        addOutput("Could not determine size of file %s\n", filename);
    }
    addOutput("\n\n");
    struct sysinfo memInfo;

    sysinfo(&memInfo);
    long long totalVirtualMem = memInfo.totalram;
    // Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
    // force kilo bytes
    totalVirtualMem /= 1024;

    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    // Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
    // force kilo bytes
    virtualMemUsed /= 1024;

    long long virtualMemCurrProcess = getVirtualMemCurrProcess();
    long long peakVirtualMemCurrProcess = getPeakVirtualMemCurrProcess();

    long long totalPhysMem = memInfo.totalram;
    // Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;
    // force kilo bytes
    totalPhysMem /= 1024;

    long long physicalMemCurrProcess = getPhysicalMemCurrProcess();

    addOutput("RAM:\n----\n");
    addOutput("Machine:\n");
    addOutput("%-16s: %8lld Kb\n", "Virtual total", totalVirtualMem);
    addOutput("%-16s: %8lld Kb\n", "Virtual used", virtualMemUsed);
    addOutput("%-16s: %8lld Kb\n", "Physical", totalPhysMem);
    addOutput("\n");
    addOutput("Current process:\n");
    // addOutput("-----------------------------------------------------\n");
    addOutput("%-16s: %8lld Kb (%8.4f%%)\n", "Virtual used", virtualMemCurrProcess,
        (100.0 * virtualMemCurrProcess) / totalVirtualMem);
    addOutput("%-16s: %8lld Kb (%8.4f%%)\n", "Virtual peak", peakVirtualMemCurrProcess,
        (100.0 * peakVirtualMemCurrProcess) / totalVirtualMem);
    addOutput("%-16s: %8lld Kb (%8.4f%%)\n", "Physical", physicalMemCurrProcess,
        (100.0 * physicalMemCurrProcess) / totalPhysMem);
    addOutput("\n\n");

    double loadavg[5];

    addOutput("Load:\n-----\n");
    int ret = getloadavg(loadavg, sizeof(loadavg) / sizeof(double));
    if (3 == ret)
    {
        addOutput("Loadavg: %f %f %f\n", loadavg[0], loadavg[1], loadavg[2]);
    }
    else
    {
        addOutput("getloadavg() returned unexpected number of values: %d\n", ret);
    }
    addOutput("\n");

    return m_output;
}
} // namespace keo_util
