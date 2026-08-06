/*
 *     Copyright KEO GmbH 2019 - All rights reserved!
 *
 *     This software is protected by the inclusion of the above copyright
 * notice.
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

#ifndef KEO_DATAGRAM_DESTINATIONLIST_H_
#define KEO_DATAGRAM_DESTINATIONLIST_H_

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

#include <list>
#include <vector>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

#include <keo_datagram/core/Cmd.h>
#include <keo_datagram/core/NodeManagementDestinationData.h>
#include <keo_datagram/core/NodeManagementDestinationListData.h>

/* ************************************************************************** *
 *  defines                                                                   *
 * ************************************************************************** */

/* ************************************************************************** *
 *  types                                                                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *  class definition                                                          *
 * ************************************************************************** */

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/* ******************************************************************************
 * *
 *  class DestinationList: definition
 * ******************************************************************************
 */
/** Utility class to handle destination list **/
class DestinationList {
public:
  /**
   * Empty constructor
   */
  DestinationList();

  /**
   * Constructor with an initialized destination list information
   * @param listData Initialized information
   */
  DestinationList(NodeManagementDestinationListDataConstPtr listData);

  /**
   * Destructor
   */
  ~DestinationList();

  /**
   * Clears the DestinationList.
   */
  void clear();

  /**
   * Returns destinations information for all devices.
   *
   * @return Information for all destinations
   */
  NodeManagementDestinationListDataPtr getDestinationListInformation() const;

  /**
   * Returns destinations information for device address.
   * If the address doesn't exist in the list, the information is empty.
   *
   * @param deviceName
   *            Name of device
   * @return Information about this device
   */
  NodeManagementDestinationData
  getDestinationInformation(const xs_string &deviceName) const;

  /**
   * Returns the list of all stored addresses without removed entries.
   *
   * @return List of device names
   */
  std::vector<xs_string> getListOfDestinations() const;

  /**
   * Returns the list of all stored addresses with feature set SMALL, GATEWAY
   * or Router.
   *
   * @return List of device names
   */
  std::vector<xs_string> getListOfSmartDestinations() const;

  /**
   * Adds, modify or removes the destination information.
   * Removed entries will be considered. Existing entries will be overwritten.
   *
   * @param listData
   *            List with all modifications
   * @return true, if modified
   */
  bool insertDestinationListInformation(
      NodeManagementDestinationListDataConstPtr listData);

  /**
   * Adds, modify or removes the destination information.
   * Removed entries will be considered. Existing entries will be overwritten.
   *
   * @param data
   *            Modifications of a destination
   * @return true, if modified
   */
  bool insertDestinationInformation(const NodeManagementDestinationData &data);

  /**
   * Adds, modify or removes the destination information.
   * Removed entries will be considered. Existing entries will be overwritten.
   *
   * @param listData
   *            List with all modifications
   * @param cmdFilterList
   *            Filters of the modifications
   * @return true, if modified
   */
  bool updateDestinationList(NodeManagementDestinationListDataConstPtr listData,
                             const std::vector<Filter> &cmdFilterList);

  /**
   * Removes entry from destination list
   *
   * @param deviceName
   *            Device name to remove
   */
  void removeDestinationInformation(const xs_string &deviceName);

  /**
   * Returns old destinations information for removed devices.
   * If the address doesn't exist in the list, the information is empty.
   *
   * @param deviceName
   *            Name of device
   * @return Information about this device
   */
  NodeManagementDestinationData
  getDestinationInformationFromRemoved(const xs_string &deviceName);

  /**
   * Returns the number of modified entries since last call of
   * commit.
   *
   * @return Number of modified devices
   */
  int getNumberOfModifiedDevices() const;

  /**
   * Returns the list of modified entries since last call of commit.
   *
   * @return List of modified devices
   */
  std::vector<xs_string> getModifiedDevicesList() const;

  /**
   * Returns the number of added entries since last call of
   * commit.
   *
   * @return Number of added devices
   */
  int getNumberOfAddedDevices() const;

  /**
   * Returns the list of added entries since last call of commit.
   *
   * @return List of added devices
   */
  std::vector<xs_string> getAddedDevicesList() const;

  /**
   * Returns the number of removed entries since last call of commit.
   *
   * @return Number of removed devices
   */
  int getNumberOfRemovedDevices() const;
  /**
   * Returns the list of removed entries since last call of commit.
   *
   * @return List of removed devices
   */
  std::vector<xs_string> getRemovedDevicesList() const;

  /**
   * Removes added and removed status of the entries. Entries with removed
   * status are deleted.
   */
  void commit();

  /**
   * Each item in the other DestinationList that isn't already in this
   * DestinationList is inserted into this DestinationList.
   *
   * @note No entries will be marked as added.
   * @param other
   *            Another destination list
   */
  void unite(const DestinationList &other);

  /**
   * Removes all items from this DestinationList that are contained in the
   * other DestinationList.
   *
   * @note No entries will be marked as removed.
   * @param other
   *            Another destination list
   */
  void subtract(const DestinationList &other);

  /**
   * Adds (insert) the destinations information into this destinations
   * information without overwriting existing entries
   *
   * @param other
   *            Another destination list
   */
  void addIfNotExists(const DestinationList &other);

  /**
   * Remove entries of the other destinations information if entry exists in
   * this destinations information, except the entries in except list.
   *
   * @param other
   *            Another destination list
   * @param except
   *            Except list
   */
  void removeIfExists(const DestinationList &other,
                      const std::vector<xs_string> &except);

  /**
   * Returns the destinations information for all removed or added entries
   * since last call of commit.
   *
   * @param except
   *            Except device name
   * @return List with destination information
   */
  std::vector<NodeManagementDestinationData>
  getDestinationInformationUpdate(const xs_string &except = xs_string()) const;

  /// Returns the destinations information for all removed or added entries
  /// since last call of commit.
  NodeManagementDestinationListDataPtr getDestinationListInformationUpdate(
      const xs_string &except = xs_string()) const;

  /**
   * Create notification cmd.
   *
   * @return Cmd with destination modification
   */
  CmdPtr createNotificationCmd();

private:
  class DestinationListImpl;

  DestinationListImpl *d;
};

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_DESTINATIONLIST_H_