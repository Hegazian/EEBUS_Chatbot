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

#ifndef KELOGGER_H
#define KELOGGER_H

#include <ctime>
#include <sstream>
#include <string>

namespace keo_util
{
/**
 * @brief KELogger A class providing logger functionality for the KEO Framework.
 * It is implemented in a non blocking way to minimize the influence of log messages and timings
 * on the KEO Framework functionality.
 *
 * For the user there is a consumer interface @see KELogger::ConsumerInterface that
 * can be used to map the KEO Framework log messages to any logger used by the customer.
 *
 * By default a simple console consumer @see KELoggerConsoleConsumer is delivered.
 * This consumer can be configured via a simple config file and produces colored console output.
 * For more information please refer to @see KELoggerConsoleConsumer.
 */
class KELogger
{

public:
    /**
     * @brief Level describes the different logging levels that can be used by the KEO Framework.
     */
    enum class Level : uint32_t
    {
        FATAL = 0,
        ERROR,
        WARNING,
        INFO,
        TRACE,
        DEBUG,
        VERB_0,
        VERB_1,
        VERB_2,
        VERB_3,
        VERB_4,
        VERB_5,
        VERB_6,
        VERB_7,
        VERB_8,
        VERB_9,
        SIZE
    };

    /**
     * @brief Constructor, create a logger instance with a dedicated module identifier
     * @param module The module identifier
     */
    KELogger(const char* module = "default");

    /**
     * @brief Destructor
     */
    virtual ~KELogger();

    /**
     * @brief Streaming operator, for logger used with streaming
     * @param msg The logger message.
     */
    template <class T> KELogger& operator<<(const T& msg)
    {
        ss << msg;
        return *this;
    }

    /**
     * @brief Streaming operator specialization for the log level
     * @param level Log level
     */
    KELogger& operator<<(const KELogger::Level& level);

    /**
     * @brief Define the type of std::cout
     */
    typedef std::basic_ostream<char, std::char_traits<char>> CoutType;

    /**
     * @brief The function signature of std::endl
     */
    typedef CoutType& (*StandardEndLine)(CoutType&);

    /**
     * @brief Define an operator<< to take in std::endl
     */
    KELogger& operator<<(StandardEndLine /*manip*/);

    /**
     * @brief Output a log message
     * @param level Log level
     * @param message The message
     */
    bool output(KELogger::Level level, std::string const& message);

    /**
     * @brief The LoggerConsumerInterface class can be used to map the KEO log messages to the logging system used by
     * the customer.
     * It must be implemented by the customer and user of the KEO framework.
     * @see keo_util::KELogger
     * @see keo_util::KELogger::RegisterConsumer
     */
    class ConsumerInterface
    {
    public:
        /**
         * @brief LogConsumerInterface
         */
        ConsumerInterface();

        /**
         * @brief ~LogConsumerInterface
         */
        virtual ~ConsumerInterface();

        /**
         * @brief loadConfig Load the configuration and set all filter for all configured modules.
         * @param filename Path to the configuration file.
         * @return true if the file could be opened and parsed, otherwise false.
         */
        virtual bool loadConfig(std::string const& filename) = 0;

        /**
         * @brief getDefaultLevel Get the default logging filter.
         * @return The log level used for filtering.
         */
        virtual KELogger::Level getDefaultLevel() = 0;

        /**
         * @brief setDefaultLevel Set the default logging filter.
         */
        virtual void setDefaultLevel(KELogger::Level level) = 0;

        /**
         * @brief isLevelActive Get a logging filter for a dedicated module.
         *        If no filter is set the 'default' filter will be taken.
         * @param module Different modules like stack, framework, utils, ... are able to produce log message.
         *               This variable describes the module which produces the log.
         * @return The log level used for filtering.
         */
        virtual bool isLevelActive(const char* module, KELogger::Level level) = 0;

        /**
         * @brief setLevel Set a logging filter for a dedicated module.
         * @param module Different modules like stack, framework, utils, ... are able to produce log message.
         *               This variable describes the module which produces the log.
         * @param  The log level used for filtering.
         */
        virtual void setLevel(const char* module, KELogger::Level level) = 0;

        /**
         * @brief onLog is called every time a log message is produced by the KEO Framework.
         * @param level Describes the level of the log messages
         * @param module Different modules like stack, framework, utils, ... are able to produce log message.
         *               This variable describes the module which produces the log.
         * @param message The special log message for this module.
         */
        virtual void onLog(KELogger::Level level, std::time_t time, const char* module, const char* message) = 0;
    };

    /**
     * @brief registerConsumer Register a consumer for log messages.
     * @param consumer Pointer to the consumer interface @see KELoggerConsumerInterface
     */
    static void registerConsumer(ConsumerInterface* consumer);

    /**
     * @brief unregisterConsumer Unregister a consumer for log messages.
     * @param consumer Pointer to the consumer interface @see KELoggerConsumerInterface
     */
    static void unregisterConsumer(ConsumerInterface* consumer);

    /**
     * @brief loadConfig Load the configuration and set all filters for all configured modules.
     * Please note, all consumers will be called for loading their configuration.
     * @param filename Path to the configuration file.
     * @return true if the file coule be opened and parsed, otherwise false.
     */
    static bool loadConfig(std::string const& filename);

    /**
     * @brief setLevel Set a logging filter for a dedicated module.
     * @param module Different modules like stack, framework, utils, ... are able to produce log message.
     *               This variable describes the module which produces the log.
     * @param  The log level used for filtering.
     */
    static void setLevel(const char* module, KELogger::Level level);

    /**
     * @brief isLevelActive Is the log level active or not
     * @param module Different modules like stack, framework, utils, ... are able to produce log message.
     *               This variable describes the module which produces the log.
     * @param level The log level used for filtering.
     * @return true in case the level is active.
     */

    bool isLevelActive(const char* module, KELogger::Level level);

    /**
     * @brief getDefaultLevel Get the default logging filter.
     * @return The log level used for filtering.
     */
    KELogger::Level getDefaultLevel();
    /**
     * @brief setDefaultLevel Set the default logging filter.
     */
    static void setDefaultLevel(KELogger::Level level);

private:
    std::string moduleName;
    Level logLevel;
    std::stringstream ss;
};
}

#endif // KELOGGER_H
