/*
 *     Copyright KEO GmbH 2017 - All rights reserved!
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
 *     @brief      Interface for a logging consumer
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */
#include <ctime>
#include <iostream>
#include <ostream>
#include <unistd.h>

#include <fstream>
#include <regex>

#include <string.h>

#include <keo_util/KEIniReader.h>
#include <keo_util/KELoggerConsoleConsumer.h>

namespace keo_util
{
const char* KELoggerConsoleConsumer::literals::level = "level";
const char* KELoggerConsoleConsumer::literals::to_console = "to_console";
const char* KELoggerConsoleConsumer::literals::use_colors = "use_colors";
const char* KELoggerConsoleConsumer::literals::to_file = "to_file";
const char* KELoggerConsoleConsumer::literals::filename = "filename";

const char* KELoggerConsoleConsumer::logLevel2String[static_cast<std::size_t>(KELogger::Level::SIZE)] = {
    [static_cast<int>(KELogger::Level::FATAL)] = "FATAL",
    [static_cast<int>(KELogger::Level::ERROR)] = "ERROR",
    [static_cast<int>(KELogger::Level::WARNING)] = "WARNING",
    [static_cast<int>(KELogger::Level::INFO)] = "INFO",
    [static_cast<int>(KELogger::Level::TRACE)] = "TRACE",
    [static_cast<int>(KELogger::Level::DEBUG)] = "DEBUG",
    [static_cast<int>(KELogger::Level::VERB_0)] = "VERB_0",
    [static_cast<int>(KELogger::Level::VERB_1)] = "VERB_1",
    [static_cast<int>(KELogger::Level::VERB_2)] = "VERB_2",
    [static_cast<int>(KELogger::Level::VERB_3)] = "VERB_3",
    [static_cast<int>(KELogger::Level::VERB_4)] = "VERB_4",
    [static_cast<int>(KELogger::Level::VERB_5)] = "VERB_5",
    [static_cast<int>(KELogger::Level::VERB_6)] = "VERB_6",
    [static_cast<int>(KELogger::Level::VERB_7)] = "VERB_7",
    [static_cast<int>(KELogger::Level::VERB_8)] = "VERB_8",
    [static_cast<int>(KELogger::Level::VERB_9)] = "VERB_9",
};

const char* KELoggerConsoleConsumer::logLevel2Color[static_cast<std::size_t>(KELogger::Level::SIZE)] = {
    [static_cast<int>(KELogger::Level::FATAL)] = "\x1B[1;31m", /* red */
    [static_cast<int>(KELogger::Level::ERROR)] = "\x1B[31m", /* red */
    [static_cast<int>(KELogger::Level::WARNING)] = "\x1B[33m", /* orange */
    [static_cast<int>(KELogger::Level::INFO)] = "\x1B[36m", /* cyan */
    [static_cast<int>(KELogger::Level::TRACE)] = "\x1B[1;32m", /* green */
    [static_cast<int>(KELogger::Level::DEBUG)] = "\x1B[32m", /* cyan */
    [static_cast<int>(KELogger::Level::VERB_0)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_1)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_2)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_3)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_4)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_5)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_6)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_7)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_8)] = "\x1B[37m", /* white */
    [static_cast<int>(KELogger::Level::VERB_9)] = "\x1B[37m", /* white */
};

const char* KELoggerConsoleConsumer::logLevel2ColorReset = "\x1B[0m";

KELogger::Level KELoggerConsoleConsumer::getLogLevelFromString(const char* str)
{
    for (size_t i = 0; i < static_cast<std::size_t>(KELogger::Level::SIZE); ++i)
    {
        if (strcasecmp(str, logLevel2String[i]) == 0)
        {
            return static_cast<KELogger::Level>(i);
        }
    }
    return defaultLevel;
}

const char* KELoggerConsoleConsumer::getStringFromLogLevel(KELogger::Level level)
{
    if (static_cast<std::size_t>(level) >= static_cast<std::size_t>(KELogger::Level::SIZE))
    {
        level = defaultLevel;
    }
    return logLevel2String[static_cast<std::size_t>(level)];
}

KELoggerConsoleConsumer::KELoggerConsoleConsumer()
    : mutex()
    , defaultLevel(KELogger::Level::INFO)
    , toConsole(true)
    , useColors(true)
    , toFile(false)
    , fileName()
{
    KELogger::registerConsumer(this);
}

KELoggerConsoleConsumer::~KELoggerConsoleConsumer()
{
    KELogger::unregisterConsumer(this);
}

bool KELoggerConsoleConsumer::isLevelActive(const char* module, KELogger::Level level)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (config.count(module))
    {
        if (config[module].count(level))
        {
            return config[module][level];
        }
    }
    return (level <= defaultLevel) ? true : false;
}

void KELoggerConsoleConsumer::setLevel(const char* module, KELogger::Level level)
{
    std::lock_guard<std::mutex> lock(mutex);
    for (auto const& str : logLevel2String)
    {
        config[module][getLogLevelFromString(str)] = (getLogLevelFromString(str) <= level) ? true : false;
    }
}

KELogger::Level KELoggerConsoleConsumer::getDefaultLevel()
{
    std::lock_guard<std::mutex> lock(mutex);
    return defaultLevel;
}

void KELoggerConsoleConsumer::setDefaultLevel(KELogger::Level level)
{
    std::lock_guard<std::mutex> lock(mutex);
    defaultLevel = level;
}

bool KELoggerConsoleConsumer::loadConfig(std::string const& filename)
{
    bool success = false;

    KEIniReader ini;
    if (ini.parse(filename))
    {
        std::unique_lock<std::mutex> lock(mutex);

        std::string strDefaultLevel(getStringFromLogLevel(defaultLevel));
        toConsole = ini.getBool("", literals::to_console, true);
        useColors = ini.getBool("", literals::use_colors, true);
        toFile = ini.getBool("", literals::to_file, false);
        fileName = ini.get<std::string>("", literals::filename, "");
        if (toFile && fileName.empty())
        {
            std::cout << "Logging to file is enabled, but the log file name is empty. Disabling logging to file."
                      << std::endl;
            toFile = false;
        }
        defaultLevel = getLogLevelFromString(ini.get<std::string>("", literals::level, strDefaultLevel).c_str());
        lock.unlock();

        for (std::string const& sec : ini.getSections())
        {
            setLevel(sec.c_str(),
                getLogLevelFromString(ini.get<std::string>(sec, literals::level, strDefaultLevel).c_str()));
            for (auto const& str : logLevel2String)
            {
                if (ini.has(sec, str))
                {
                    lock.lock();
                    config[sec][getLogLevelFromString(str)] = ini.getBool(sec, str, false);
                    lock.unlock();
                }
            }
        }

        success = true;
    }

    return success;
}

void KELoggerConsoleConsumer::onLog(KELogger::Level level, std::time_t time, const char* module, const char* message)
{
    if (isLevelActive(module, level))
    {
        char timeString[80];
        std::strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&time));

        if (toConsole)
        {
            if (useColors)
            {
                std::cout << logLevel2Color[static_cast<unsigned>(level)];
            }

            std::cout << "[" << module << "] " << timeString << " " << logLevel2String[static_cast<unsigned>(level)]
                      << " " << message;

            if (useColors)
            {
                std::cout << logLevel2ColorReset;
            }

            std::cout << std::endl;
        }

        if (toFile)
        {
            std::ofstream outFile;
            outFile.open(fileName, std::ios::app);
            if (outFile.is_open())
            {
                outFile << "[" << module << "] " << timeString << " " << logLevel2String[static_cast<unsigned>(level)]
                        << " " << message << std::endl;

                outFile.close();
            }
        }
    }
}
}
