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

#ifndef KELOGGERCONSOLECONSUMER_H
#define KELOGGERCONSOLECONSUMER_H

#include <keo_util/KEIniReader.h>
#include <keo_util/KELogger.h>
#include <map>
#include <mutex>
#include <string>

namespace keo_util
{

/**
 * class KELoggerConsoleConsumer
 *
 * A simple consumer for log messages. Output will be written to console and/or to file.
 * For setting the log levels a configuration file is supported.
 *
 * Configuration file format (ini):
 * The configuration is split into two separate sections, the global section and the module section.
 *
 * Possible log levels:
 * FATAL,ERROR,WARNING,INFO,TRACE,DEBUG,VERB_0,VERB_1,VERB_2,VERB_3,VERB_4,VERB_5,VERB_6,VERB_7,VERB_8,VERB_9
 *
 * Global section possible values:
 * level=<log level>        Global log level used as default value if no other configuration is set.
 *                          all log messages with a higher level will be filtered out.
 * to_file=<true/false>     Defines weather file output is enabled or not
 * filename=<filename>      File path for storing log messages to file.
 * to_console=<true/false>  Defines weather console output is enabled or not
 *
 * Module section:
 * level=<log level>        log level for this module, all log messages with a higher level will be filtered out.
 *                          e.g. level=INFO all log message with the level FATAL,ERROR,WARNING,INFO will be preinted
 *                          all other messages are filtered out.
 * <log level>=<true/false> Activate/Deactivate this log level and overrides the global level.
 *
 * Example:
 *
 *     # Global section
 *     level=INFO
 *     to_file=true
 *     filename=~/log/app.log
 *
 *     to_console=true
 *
 *     # Module section
 *     [keo_ship]
 *     level=INFO
 *     DEBUG=true
 *
 *     [keo_framework]
 *     level=DEBUG
 *     VERB_1=true
 *
 */
class KELoggerConsoleConsumer : public KELogger::ConsumerInterface
{
public:
    /**
     * @brief Constructor, constructs a logger console consumer that is able to print colored log messages on the
     * console
     * as well as write all message to a dedicated file.
     */
    KELoggerConsoleConsumer();

    /**
     * @brief destructor
     */
    ~KELoggerConsoleConsumer();

    /**
     * @brief getDefaultLevel Get the default logging level.
     * @return The log level used for filtering log output.
     */
    virtual KELogger::Level getDefaultLevel() override;
    /**
     * @brief setDefaultLevel Set the default logging level.
     * All levels higher and equal to the given one will be activated, all other wil lbe deactivated.
     * @param level The log level.
     *
     */
    virtual void setDefaultLevel(KELogger::Level level) override;

    /**
     * @brief isLevelActive Get a logging level for a dedicated module.
     *        If no level is set the 'default' level will be taken.
     * @param module Different modules like stack, framework, utils, ... are able to produce log message.
     *               This variable describes the module which produces the log.
     * @return The log level used for leveling.
     */
    virtual bool isLevelActive(const char* module, KELogger::Level level) override;

    /**
     * @brief setLevel Set a logging level for a dedicated module.
     * All levels higher and equal to the given one will be activated, all other wil lbe deactivated.
     * @param module Different modules like stack, framework, utils, ... are able to produce log message.
     *               This variable describes the module which produces the log.
     * @param level The log level
     * @param  The log level used for leveling.
     */
    virtual void setLevel(const char* module, KELogger::Level level) override;

    /**
     * @brief onLog Callback that is called by the logger API of the KEO framework.
     * @param level The log level for this message
     * @param time The local timestamp of this message
     * @param module The module prefix for this message
     * @param message The text message itself
     */
    virtual void onLog(KELogger::Level level, std::time_t time, const char* module, const char* message) override;

    /**
     * @brief loadConfig Load the configuration and set all level for all configured modules.
     * @param filename Path to the configuration file.
     * @return true if the file coule be opened and parsed, otherwise false.
     */
    bool loadConfig(std::string const& filename) override;

protected:
    std::mutex mutex;
    KELogger::Level defaultLevel;
    bool toConsole;
    bool useColors;
    bool toFile;
    std::string fileName;
    std::map<std::string, std::map<KELogger::Level, bool> > config;

    static const char* logLevel2String[static_cast<std::size_t>(KELogger::Level::SIZE)];
    static const char* logLevel2Color[static_cast<std::size_t>(KELogger::Level::SIZE)];
    static const char* logLevel2ColorReset;

    KELogger::Level getLogLevelFromString(const char* str);
    const char* getStringFromLogLevel(KELogger::Level level);

    struct literals
    {
        static const char* level;
        static const char* to_console;
        static const char* use_colors;
        static const char* to_file;
        static const char* filename;
    };
};
}

#endif // KECONSOLELOGGERCONSUMER_H
