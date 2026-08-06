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

#include <ShipTimer.h>

keo_ship::ShipTimerController keo_ship::ShipTimer::controller_;

keo_ship::ShipTimer::ShipTimer()
    : start_timeout_(0)
    , periodic_timeout_(0)
{
}

keo_ship::ShipTimer::ShipTimer(Callback on_timeout_cb)
    : start_timeout_(0)
    , periodic_timeout_(0)
    , on_timeout_cb_(on_timeout_cb)
{
}

keo_ship::ShipTimer::~ShipTimer()
{
    controller_.stop(this);
}

void keo_ship::ShipTimer::onTimeout()
{
    if (on_timeout_cb_)
    {
        on_timeout_cb_(*this);
    }
}

void keo_ship::ShipTimer::start(uint32_t start_timeout, uint32_t periodic_timeout)
{
    start_timeout_ = start_timeout;
    periodic_timeout_ = periodic_timeout;
    controller_.start(this);
}

void keo_ship::ShipTimer::stop()
{
    start_timeout_ = 0;
    periodic_timeout_ = 0;
    controller_.stop(this);
}

void keo_ship::ShipTimer::getTimouts(uint32_t& start_timeout, uint32_t& periodic_timeout)
{
    start_timeout = start_timeout_;
    periodic_timeout = periodic_timeout_;
}

void keo_ship::ShipTimer::setCallback(Callback cb)
{
    on_timeout_cb_ = cb;
}
