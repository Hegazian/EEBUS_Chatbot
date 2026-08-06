/*
 *     Copyright KEO GmbH 2016 - All rights reserved!
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
 *     @file       KELogging.h
 *     @brief      Logging header wrapper
 *     @author     KEO GmbH 2015 @n
 *                 All rights reserved !
 */

#ifndef _KEO_LOGGING_H_
#define _KEO_LOGGING_H_
#include <keo_util/KELogger.h>

#define LOG_VERBOSE(level) keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::VERB_##level
#define LOG_DEBUG() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::DEBUG
#define LOG_TRACE() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::TRACE
/** Log/report informational data */
#define LOG_INFO() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::INFO
/** Log/report warning problems */
#define LOG_WARN() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::WARNING
#define LOG_WARNING() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::WARNING
/** Log/report error problems */
#define LOG_ERROR() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::ERROR
/** Log/report fatal problems */
#define LOG_FATAL() keo_util::KELogger(LOGGER_ID) << keo_util::KELogger::Level::FATAL

/** Debug output for informational data */
#define DEBUG_INFO() LOG_DEBUG()
/** Debug output for functions */
#define DEBUG_FUNC() LOG_DEBUG() << __PRETTY_FUNCTION__
#define DEBUG_FUNCTION() LOG_DEBUG() << __PRETTY_FUNCTION__

#include <keo_util/KELoggerConsoleConsumer.h>
#define INITIALIZE_KELOGGING keo_util::KELoggerConsoleConsumer keoConsoleConsumer;
#define DEINITIALIZE_KELOGGING KELogger::unregisterConsumer(&keoConsoleConsumer);
extern keo_util::KELoggerConsoleConsumer keoConsoleConsumer;

#endif /* _KEO_LOGGING_H_ */
