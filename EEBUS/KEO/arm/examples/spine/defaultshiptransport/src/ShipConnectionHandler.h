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
 *     @brief      ShipConnectionInterface class declaration
 *
 *     @author     KEO GmbH 2016 @n
 *                 All rights reserved !
 */

#ifndef KEO_FRAMEWORK_SHIPTRANSPORT_SRC_SHIPCONNECTIONCREATOR_H_
#define KEO_FRAMEWORK_SHIPTRANSPORT_SRC_SHIPCONNECTIONCREATOR_H_

/* ****************************************************************************** *
 *  keo_spine header files                                                          *
 * ****************************************************************************** */

#include "ShipConnectionImplementation.h"

/* ****************************************************************************** *
 *  standard header files                                                         *
 * ****************************************************************************** */
#include <mutex>
/* ****************************************************************************** *
 *  defines                                                                       *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  types                                                                         *
 * ****************************************************************************** */

/* ****************************************************************************** *
 *  class definition                                                              *
 * ****************************************************************************** */

namespace keo_default_ship_transport
{

/**
 * @ingroup keo_default_ship_transport
 */
class ShipConnectionHandler
{
public:
    /**
     * Constructor
     * @param connectionHandler
     *            Interface to the SHIP connection handler
     * @param shipListener
     *            Interface to SHIP control
     */
    ShipConnectionHandler(keo_spine::TransportConnectionHandler* connectionHandler, ShipControlInterface* shipListener);

    /// Destructor
    ~ShipConnectionHandler();

    /**
     * Getter for the SHIP node factory
     */
    keo_ship::ShipNodeFactoryPtr getShipNodeFactory();

    /**
     * Close all SHIP connection
     */
    void closeConnections();

    /**
     * Remove a SHIP connection
     * @param node
     *            Pointer to ship connection object
     * @param dataExchangeEnabled
     *            Indication if connection has reached data exchanged enabled state
     */
    void removeConnection(ShipConnection* node, bool dataExchangeEnabled);

    /** Handle data exchange enabled
     *
     * @param node
     *            Pointer to ship connection object
     */
    void onDataExchangeEnabled(ShipConnection* node);

    /**
     * Close a SHIP connection
     * @param id
     *            id of the SHIP connection to close
     */
    void closeConnection(const std::string& id);

protected:
    // Factory for ship connections
    class ShipConnectionNodeFactory : public keo_ship::ShipNodeFactory
    {
        ShipConnectionHandler& parent;

    public:
        ShipConnectionNodeFactory(ShipConnectionHandler& creator);

        /**
         * Create shipNode
         */
        virtual keo_ship::ShipNodePtr createShipNode();
    }; // ShipConnectionNodeFactory

    //! typedef for non-const smart pointer type ShipConnectionNodeFactory
    typedef std::shared_ptr<ShipConnectionHandler::ShipConnectionNodeFactory> ShipConnectionNodeFactoryPtr;

    //! typedef for const type ShipConnectionNodeFactory
    typedef const ShipConnectionHandler::ShipConnectionNodeFactory ShipConnectionNodeFactoryConst;

    //! typedef for const smart pointer type ShipConnectionNodeFactory
    typedef std::shared_ptr<ShipConnectionNodeFactoryConst> ShipConnectionNodeFactoryConstPtr;

private:
    // Handler for connections
    keo_spine::TransportConnectionHandler* connectionHandler;
    // Listener for SHIP callbacks
    ShipControlInterface* shipListener;
    // Collection for all connections
    std::vector<ShipConnectionImplementationPtr> transportConnections;
    // Factory for SHIP connections
    ShipConnectionNodeFactoryPtr shipNodeFactory;
    std::mutex mtx; /// guard
};

/** @} */ //  end of group framework_shiptransport

//! typedef for non-const smart pointer type ShipConnectionCreator
typedef std::shared_ptr<ShipConnectionHandler> ShipConnectionHandlerPtr;

//! typedef for const type ShipConnectionCreator
typedef const ShipConnectionHandler ShipConnectionCreatorConst;

//! typedef for const smart pointer type ShipConnectionCreator
typedef std::shared_ptr<ShipConnectionCreatorConst> ShipConnectionHandlerConstPtr;

} /* namespace keo_default_ship_transport */

#endif /* KEO_SPINE_SHIPCONNECTION_SRC_SHIPCONNECTIONCREATOR_H_ */
