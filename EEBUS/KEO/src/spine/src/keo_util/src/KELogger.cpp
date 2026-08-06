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

#include <fstream>
#include <unistd.h>

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <list>
#include <mutex>
#include <thread>

#include <cstdarg>
#include <cstdint>

#include <keo_util/KELogger.h>

std::hash<std::thread::id> hasher;

#ifndef KEO_LOG_MAX_MESSAGE_COUNT
#define KEO_LOG_MAX_MESSAGE_COUNT 8192
#endif

#ifndef KEO_LOG_MAX_MODULE_NAME_SIZE
#define KEO_LOG_MAX_MODULE_NAME_SIZE 32
#endif

namespace keo_util
{

class LogQueue
{
public:
    struct Buffer
    {
        enum
        {
            FREE = 0,
            ALLOC = 1,
            USED = 2
        };
        std::atomic<int> used;

        struct payload_t
        {
            std::mutex m;
            KELogger::Level level;
            std::time_t time;
            char module[KEO_LOG_MAX_MODULE_NAME_SIZE + 1] = { 0 };
            char* message;
        } payload;
    };

    LogQueue()
        : inIdx(0)
        , outIdx(0)
    {
        for (size_t i = 0; i < KEO_LOG_MAX_MESSAGE_COUNT; ++i)
        {
            queue[i].used.store(LogQueue::Buffer::FREE);
        }
    }

    ~LogQueue()
    {
    }

    bool has()
    {
        int out = outIdx.load(std::memory_order_acquire);
        int in = inIdx.load(std::memory_order_acquire);
        return (in != out);
    }

    void push(LogQueue::Buffer* buffer)
    {
        int expected = LogQueue::Buffer::ALLOC;
        while (!buffer->used.compare_exchange_weak(expected, LogQueue::Buffer::USED))
        {
            ;
        }
    }

    void release(LogQueue::Buffer* buffer)
    {
        int expected = LogQueue::Buffer::USED;
        while (!buffer->used.compare_exchange_weak(expected, LogQueue::Buffer::FREE))
        {
            ;
        }
    }

    Buffer* alloc()
    {
        LogQueue::Buffer* result = nullptr;
        while (true)
        {
            int in = inIdx.load(std::memory_order_acquire);
            int out = outIdx.load(std::memory_order_acquire);
            int newIn = (in + 1) % (KEO_LOG_MAX_MESSAGE_COUNT);

            if (newIn == out)
            {
                // overflow
                return result;
            }

            newIn %= (KEO_LOG_MAX_MESSAGE_COUNT);
            if (inIdx.compare_exchange_weak(in, newIn, std::memory_order_acq_rel))
            {
                result = &queue[newIn];

                int expected = LogQueue::Buffer::FREE;
                while (!result->used.compare_exchange_weak(expected, LogQueue::Buffer::ALLOC))
                {
                    ;
                }
                return result;
            }
        }
    }

    Buffer* pop()
    {
        while (true)
        {
            int out = outIdx.load(std::memory_order_acquire);
            int in = inIdx.load(std::memory_order_acquire);

            if (in == out)
            {
                break;
            }

            int newOut = (out + 1) % (KEO_LOG_MAX_MESSAGE_COUNT);

            int used = queue[newOut].used.load(std::memory_order_acquire);
            if (used != LogQueue::Buffer::USED)
            {
                break;
            }

            if (outIdx.compare_exchange_weak(out, newOut, std::memory_order_acq_rel))
            {
                return &queue[newOut];
            }
        }
        return nullptr;
    }

protected:
    Buffer queue[KEO_LOG_MAX_MESSAGE_COUNT];
    std::atomic<int> inIdx;
    std::atomic<int> outIdx;
};

class KELoggerHandler
{

public:
    KELoggerHandler()
        : logQueue()
        , missedLogCounter(0)
        , dataMutex()
        , notifyMutex()
        , condition()
        , logConsumer()
        , done(false)
    {
        thread = std::thread(&KELoggerHandler::handlerThread, this);
    }

    virtual ~KELoggerHandler()
    {
        notifyMutex.lock();
        done = true;
        condition.notify_one();
        notifyMutex.unlock();

        if (thread.joinable())
        {
            thread.join();
        }
    }

    void registerConsumer(KELogger::ConsumerInterface* consumer)
    {
        dataMutex.lock();
        logConsumer.push_front(consumer);
        logConsumer.unique();
        dataMutex.unlock();

        notifyMutex.lock();
        condition.notify_one();
        notifyMutex.unlock();
    }

    void unregisterConsumer(KELogger::ConsumerInterface* consumer)
    {
        while (logQueue.has())
        {
            notifyMutex.lock();
            condition.notify_one();
            notifyMutex.unlock();
            std::this_thread::yield();
            sleep(1);
        }

        dataMutex.lock();
        logConsumer.remove(consumer);
        dataMutex.unlock();
    }

    bool log(KELogger::Level level, std::string const& module, std::string const& message)
    {
        bool ret = false;

        size_t buffer_size = message.length() + 1;
        char* log_message = new (std::nothrow) char[buffer_size];
        if (log_message != nullptr)
        {
            LogQueue::Buffer* m = logQueue.alloc();
            if (m != nullptr)
            {
                m->payload.m.lock();

                m->payload.level = level;
                m->payload.time = std::time(nullptr);
                std::strncpy(m->payload.module, module.c_str(), KEO_LOG_MAX_MODULE_NAME_SIZE);
                std::strncpy(log_message, message.c_str(), buffer_size);
                m->payload.message = log_message;

                m->payload.m.unlock();
                logQueue.push(m);
                ret = true;
            }
            else
            {
                ++missedLogCounter;
            }
        }

        notifyMutex.lock();
        condition.notify_one();
        notifyMutex.unlock();
        return ret;
    }

    void onLog(KELogger::Level level, std::time_t time, const char* module, const char* message)
    {
        std::unique_lock<std::mutex> dataLock(dataMutex);
        for (KELogger::ConsumerInterface* consumer : logConsumer)
        {
            consumer->onLog(level, time, module, message);
        }
    }

    bool loadConfig(std::string const& filename)
    {
        std::unique_lock<std::mutex> dataLock(dataMutex);
        bool ret = true;
        for (KELogger::ConsumerInterface* consumer : logConsumer)
        {
            ret &= consumer->loadConfig(filename);
        }
        return ret;
    }

    bool isLevelActive(const char* module, KELogger::Level level)
    {
        std::unique_lock<std::mutex> dataLock(dataMutex);
        bool ret = true;
        for (KELogger::ConsumerInterface* consumer : logConsumer)
        {
            ret &= consumer->isLevelActive(module, level);
        }
        return ret;
    }

    void setLevel(const char* module, KELogger::Level level)
    {
        std::unique_lock<std::mutex> dataLock(dataMutex);
        for (KELogger::ConsumerInterface* consumer : logConsumer)
        {
            consumer->setLevel(module, level);
        }
    }

    KELogger::Level getDefaultLevel()
    {
        std::unique_lock<std::mutex> dataLock(dataMutex);
        KELogger::Level ret(KELogger::Level::FATAL);
        for (KELogger::ConsumerInterface* consumer : logConsumer)
        {
            KELogger::Level level(consumer->getDefaultLevel());
            if (level > ret)
            {
                ret = level;
            }
        }
        return ret;
    }

    void setDefaultLevel(KELogger::Level level)
    {
        std::unique_lock<std::mutex> dataLock(dataMutex);
        for (KELogger::ConsumerInterface* consumer : logConsumer)
        {
            consumer->setDefaultLevel(level);
        }
    }

    void handlerThread(void)
    {
        std::unique_lock<std::mutex> notifyLock(notifyMutex);
        uint32_t counter;
        while (!done)
        {
            LogQueue::Buffer* m;

            condition.wait(notifyLock);
            notifyLock.unlock();

            {
                while ((m = logQueue.pop()) != nullptr)
                {
                    m->payload.m.lock();
                    if (m->payload.message)
                    {
                        onLog(m->payload.level, m->payload.time, m->payload.module, m->payload.message);
                        free(m->payload.message);
                        m->payload.message = nullptr;
                    }
                    m->payload.m.unlock();
                    logQueue.release(m);

                    if ((counter = missedLogCounter.exchange(0)) != 0)
                    {
                        char buffer[256];
                        snprintf(buffer, sizeof(buffer), "%i skipped log messages.", counter);
                        onLog(KELogger::Level::DEBUG, std::time(nullptr), "logger", buffer);
                    }
                }
            }
            notifyLock.lock();
        }
    }

protected:
    LogQueue logQueue;
    std::atomic<uint32_t> missedLogCounter;
    std::mutex dataMutex;
    std::mutex notifyMutex;
    std::condition_variable condition;
    std::list<KELogger::ConsumerInterface*> logConsumer;
    std::thread thread;
    std::atomic<bool> done;
};

static KELoggerHandler staticLoggerHandler;

KELogger::KELogger(const char* module)
    : moduleName(module)
    , logLevel(Level::DEBUG)
    , ss()
{
}

KELogger::~KELogger()
{
    std::string message = ss.str();
    if (!message.empty())
    {
        output(logLevel, message);
    }
}

bool KELogger::output(Level level, std::string const& message)
{
    return staticLoggerHandler.log(level, moduleName, message);
}

KELogger& KELogger::operator<<(const KELogger::Level& level)
{
    logLevel = level;
    return *this;
}
KELogger& KELogger::operator<<(StandardEndLine /*manip*/)
{
    output(logLevel, ss.str());
    ss.str(std::string());
    return *this;
}

void KELogger::registerConsumer(KELogger::ConsumerInterface* consumer)
{
    staticLoggerHandler.registerConsumer(consumer);
}

void KELogger::unregisterConsumer(KELogger::ConsumerInterface* consumer)
{
    staticLoggerHandler.unregisterConsumer(consumer);
}

bool KELogger::isLevelActive(const char* module, KELogger::Level level)
{
    return staticLoggerHandler.isLevelActive(module, level);
}

void KELogger::setLevel(const char* module, KELogger::Level level)
{
    staticLoggerHandler.setLevel(module, level);
}

KELogger::Level KELogger::getDefaultLevel()
{
    return staticLoggerHandler.getDefaultLevel();
}

void KELogger::setDefaultLevel(KELogger::Level level)
{
    staticLoggerHandler.setDefaultLevel(level);
}

bool KELogger::loadConfig(std::string const& filename)
{
    return staticLoggerHandler.loadConfig(filename);
}

KELogger::ConsumerInterface::ConsumerInterface()
{
}

KELogger::ConsumerInterface::~ConsumerInterface()
{
}
}
