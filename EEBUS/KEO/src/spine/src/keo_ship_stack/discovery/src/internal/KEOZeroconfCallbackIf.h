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
 *     @brief      KEOZeroconfCallbackIf
 *
 *     @par        Abstract callback interface for class KEOZeroconf
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_ZEROCONF_INCLUDE_KEOZEROCONFCALLBACKIF_H_
#define KEO_ZEROCONF_INCLUDE_KEOZEROCONFCALLBACKIF_H_

/** @addtogroup TODO use doxygen group
 * @{
 */

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  project header files                                                          *
 * ****************************************************************************** */
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

class KEOZeroconfCallbackIf
{
public:
    /** Destructor */
    virtual ~KEOZeroconfCallbackIf();

    /** Method will be called when service browsing is finished or in case of any further changes */
    /** @param bSuccess */
    /**  True if no error occured */
    /** @param services */
    /**  List of services, either new or removed */
    virtual void browseService(bool bSuccess, const KEOZeroconfService& service);

    /** Method will be called when registering of a service is finished */
    /** @param bSuccess */
    /**  True if no error occured */
    /** @param service */
    /**  Service that has been registered */
    virtual void registerService(bool bSuccess, const KEOZeroconfService& service);

protected:
    /** @cond */
    KEOZeroconfCallbackIf(){};
    /** @endcond */
};

/** @}
 * end of file
 */

#endif /* KEO_ZEROCONF_INCLUDE_KEOZEROCONFCALLBACKIF_H_ */
