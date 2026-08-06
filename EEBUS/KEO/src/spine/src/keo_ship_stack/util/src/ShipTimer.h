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

#ifndef SHIPTIMER_SHIPTIMER_H__
#define SHIPTIMER_SHIPTIMER_H__

#include <cstdint>

#include <chrono>
#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>
#include <thread>

namespace keo_ship
{

/** @addtogroup keo_ship_stack
 * @{
 */

class ShipTimerController;

/**
 * @class ShipTimer
 * Implements a simple class handline timer callbacks.
 * Derive from this class or use std::bind for getting callback information.
 * @note
 * Example 1:
 *  class MyTimer : public timer::ShipTimer
 *  {
 *  public:
 *      MyTimer()
 *          : timer::ShipTimer(control)
 *      {
 *      }
 *
 *      virtual void onTimeout() override
 *      {
 *          // Add some functionality here
 *      }
 *  };
 *
 *     Usage:
 *       MyTimer t();
 *       t.Start(100);
 *       // After 100ms OnTimeout is called.
 *
 * Example 2:
 *  class MyTimerExample
 *  {
 *  public:
 *      MyTimerExample()
 *          : timer1(std::bind(&MyTimerExample::Timeout_1, this))
 *          , timer2(std::bind(&MyTimerExample::Timeout_2, this))
 *      {}
 *
 *      void Timeout_1(timer::Timer& timer)
 *      {
 *          // Add some functionality here
 *      }
 *      void Timeout_2(timer::Timer& timer)
 *      {
 *          // Add some functionality here
 *      }
 *      void StartTimer1(uint32_t timout_ms)
 *      {
 *          timer1.Start(timout_ms);
 *      }
 *      void StartTimer2(uint32_t timout_ms)
 *      {
 *          timer2.Start(timout_ms);
 *      }
 *  protected:
 *      timer::ShipTimer timer1;
 *      timer::ShipTimer timer2;
 *
 *  };
 *
 *     Usage:
 *       MyTimerExample timer_example;
 *       timer_example.StartTheTimer1(100);
 *       timer_example.StartTheTimer2(1500, 5000);
 *
 *       MyTimerExample::Timeout_1 is called after 100ms.
 *       MyTimerExample::Timeout_2 is called after 1500ms and repeatedly called every 5 seconds.
 */
class ShipTimer
{
    friend class ShipTimerController;

public:
    /**
     * Callback for timouts
     */
    typedef std::function<void(ShipTimer&)> Callback;

    /**
     * Constructor
     * @param control
     *        Timer controller, handling timeout
     */
    ShipTimer(void);

    /**
     * Constructor
     * @param control
     *        Timer controller, handling timeout
     */
    ShipTimer(Callback cb);

    /**
     * Destructor
     */
    virtual ~ShipTimer();

    /**
     * Timout method called on timeout event occurs
     */
    virtual void onTimeout();

    /**
     * Start a timer, one shot or periodic.
     * Initial start delay is 'start_timeout' following
     * the periodic delay of 'periodic_timeout' ms.
     * If 'periodic_timeout' is equal to zero, the configured timer
     * is a one shot timer.
     *
     * @param start_timeout
     *              initial timeout in milliseconds
     * @param periodic_timeout
     *              periodic timnout in milliseconds
     *              0 if one shot timer otherwise
     *              peridicity in milliseconds
     */
    void start(uint32_t start_timeout, uint32_t periodic_timeout = 0);

    /**
     * Stop a timeout
     */
    void stop();

    /**
     * Get the timeout values.
     * @see Start
     * @param start_timeout
     *              initial timeout in milliseconds
     * @param periodic_timeout
     *              periodic timnout in milliseconds
     *              0 if one shot timer otherwise
     *              peridicity in milliseconds
     */
    void getTimouts(uint32_t& start_timeout, uint32_t& periodic_timeout);

    /**
     * Set callback function
     * @see Callback
     * @param cb
     *              Callback if an timeout occours
     */
    void setCallback(Callback cb);

protected:
    uint32_t start_timeout_;
    uint32_t periodic_timeout_;

    Callback on_timeout_cb_;

private:
    std::chrono::time_point<std::chrono::steady_clock> timeout_;

    static ShipTimerController controller_;
};

/**
 * @class TimerController
 * This class handles all timer requests and perform the callback in case an timout occours.
 * Once instantiated it works in an seperate thread in the background. Take care, that all
 * timeout callbacks are called within a different thread context.
 */
class ShipTimerController
{
    friend class ShipTimer;

public:
    /**
     * Constructor
     */
    ShipTimerController(void);

    /**
     * Destructor
     */
    virtual ~ShipTimerController();

protected:
    /**
     * Start a timer
     * @param timer Timer parameter (timeouts, callback, ...)
     */
    void start(ShipTimer* timer);

    /**
     * Stop a timout
     * @param timer Timer parameter (timeouts, callback, ...)
     */
    void stop(ShipTimer* timer);

    /**
     * Worker thread
     */
    void workerThread(void);

    /**
     * Worker thread
     */
    void enqueTimer(ShipTimer* timer);

    /**
     * Worker thread
     */
    void dequeTimer(ShipTimer* timer);

private:
    bool run_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::list<ShipTimer*> timer_;
    std::thread worker_;
};

/** @}
 * end of file
 */

} // namespace ship

#endif /* SHIPTIMER_SHIPTIMER_H__ */
