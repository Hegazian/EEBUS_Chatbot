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

#ifndef KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVERYINTERFACEINTERNAL_H_
#define KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVERYINTERFACEINTERNAL_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
#include <keo_ship_discovery/ShipDiscovery.h>

#include "KEOZeroconfCallbackIf.h"
#include "KEOZeroconfService.h"

/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_ship_discovery
{

class ShipDiscoveryInterface;

class ShipDiscoveryInterfaceInternal : public KEOZeroconfCallbackIf
{
public:
    ShipDiscoveryInterfaceInternal(ShipDiscoveryInterface* discoveryInterface);
    virtual ~ShipDiscoveryInterfaceInternal();

private:
    virtual void registerService(bool bSuccess, const KEOZeroconfService& service);
    virtual void browseService(bool bSuccess, const KEOZeroconfService& service);

    ShipDiscoveryInterface* discoveryInterface;
};

} /* namespace keo_ship_discovery */

/** @}
 * end of file
 */

#endif /* KEO_SHIP_STACK_DISCOVERY_SRC_INTERNAL_SHIPDISCOVERYINTERFACEINTERNAL_H_ */
