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

#ifndef KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATELISTDATA_H_
#define KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATELISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/loadcontrol/LoadControlStateData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramLoadControl
 * @{
 */

/**
 * Declaration LoadControlStateListData
 */
class LoadControlStateListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  LoadControlStateListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_loadControlStateData the member to set
   */
  explicit LoadControlStateListData(
      const std::vector<LoadControlStateData> &c_loadControlStateData);

  /**
   * Equality operator
   *
   * Two objects a and b are considered equal if and only if
   *     - all members that are set in a are also set in b
   *     - all members that are set in b are also set in a
   *     - all members that are set in a and b are equal
   *
   * @param c_classObject the object to compare to
   * @return true if the objects are equal
   */
  bool operator==(const LoadControlStateListData &c_classObject) const;

  /**
   * Inequality operator
   *
   * Two objects a and b are considered not equal if and only if
   *     - at least one member that is set in a is not set in b
   *     - at least one member that is set in b is not set in a
   *     - at least one member that is set in a and b differs
   *
   * @param c_classObject the object to compare to
   * @return true, if the objects are not equal
   */
  bool operator!=(const LoadControlStateListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member LoadControlStateData.
   * @param c_loadControlStateData Value to set
   */
  void setLoadControlStateData(
      const std::vector<LoadControlStateData> &c_loadControlStateData);

  /**
   * Returns const reference to member LoadControlStateData.
   * @return const reference to member loadControlStateData
   */
  const std::vector<LoadControlStateData> &getLoadControlStateData() const;

  /**
   * Returns if member LoadControlStateData is set.
   * @retval true member LoadControlStateData is set
   * @retval false member LoadControlStateData is not set
   */
  bool getLoadControlStateDataIsSet() const;

  /**
   * Unsets member LoadControlStateData
   */
  void cleanLoadControlStateData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_loadControlStateDataIsSet;
  std::vector<LoadControlStateData> m_loadControlStateData;
};

//! typedef for non-const smart pointer type LoadControlStateListData
using LoadControlStateListDataPtr = std::shared_ptr<LoadControlStateListData>;

//! typedef for const type LoadControlStateListData
using LoadControlStateListDataConst = const LoadControlStateListData;

//! typedef for const type LoadControlStateListData
using LoadControlStateListDataConstPtr =
    std::shared_ptr<LoadControlStateListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_LOADCONTROL_LOADCONTROLSTATELISTDATA_H_