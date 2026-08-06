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

#ifndef KEO_DATAGRAM_DESTINATIONLISTIMPL_H_
#define KEO_DATAGRAM_DESTINATIONLISTIMPL_H_

/** @addtogroup SpineDatagram
 * @{
 */

/* ************************************************************************** *
 *  standard header files                                                     *
 * ************************************************************************** */

#include <map>

/* ************************************************************************** *
 *  project header files                                                      *
 * ************************************************************************** */

#include <keo_datagram/core/DestinationList.h>

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

class DestinationList::DestinationListImpl {
public:
  /**
   * Empty constructor
   */
  DestinationListImpl();

  /**
   * Constructor with an initialized destination list information
   * @param listData Initialized information
   */
  DestinationListImpl(NodeManagementDestinationListDataConstPtr listData);

  /**
   * Clears the DestinationList.
   */
  void clear();

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
   * Create notification cmd.
   *
   * @return Cmd with destination modification
   */
  CmdPtr createNotificationCmd();

  /**
   * Helper function if contain destination information.
   *
   * @return true, if information for deviceName found
   */
  bool contains(const xs_string &deviceName) const;

private:
  using informationData_MapType =
      std::map<xs_string, NodeManagementDestinationData>;

  /// information data for addressDevice
  informationData_MapType m_informationData;

  /// information data for removed devices since last call of commit
  informationData_MapType m_informationDataRemoved;

  using dataModified_ListType = std::vector<xs_string>;

  /// all modified devices since last call of commit
  dataModified_ListType m_dataModified;
  /// all added devices since last call of commit
  dataModified_ListType m_dataAdded;
};

inline int
DestinationList::DestinationListImpl::getNumberOfModifiedDevices() const {
  return m_dataModified.size();
}

inline std::vector<xs_string>
DestinationList::DestinationListImpl::getModifiedDevicesList() const {
  return m_dataModified;
}

inline int
DestinationList::DestinationListImpl::getNumberOfAddedDevices() const {
  return m_dataAdded.size();
}

inline std::vector<xs_string>
DestinationList::DestinationListImpl::getAddedDevicesList() const {
  return m_dataAdded;
}

inline int
DestinationList::DestinationListImpl::getNumberOfRemovedDevices() const {
  return m_informationDataRemoved.size();
}

} // end namespace keo_datagram

/** @}
 * end of file
 */

#endif // KEO_DATAGRAM_DESTINATIONLISTIMPL_H_