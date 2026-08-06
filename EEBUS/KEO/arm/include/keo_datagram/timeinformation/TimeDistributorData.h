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

#ifndef KEO_DATAGRAM_TIMEINFORMATION_TIMEDISTRIBUTORDATA_H_
#define KEO_DATAGRAM_TIMEINFORMATION_TIMEDISTRIBUTORDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeInformation
 * @{
 */

/**
 * Declaration TimeDistributorData
 */
class TimeDistributorData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TimeDistributorData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_isTimeDistributor the member to set
   * @param c_distributorPriority the member to set
   */
  TimeDistributorData(const xs_boolean &c_isTimeDistributor,
                      const xs_unsignedInt &c_distributorPriority);

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
  bool operator==(const TimeDistributorData &c_classObject) const;

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
  bool operator!=(const TimeDistributorData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member IsTimeDistributor.
   * @param c_isTimeDistributor Value to set
   */
  void setIsTimeDistributor(const xs_boolean &c_isTimeDistributor);

  /**
   * Returns const reference to member IsTimeDistributor.
   * @return const reference to member isTimeDistributor
   */
  const xs_boolean &getIsTimeDistributor() const;

  /**
   * Returns if member IsTimeDistributor is set.
   * @retval true member IsTimeDistributor is set
   * @retval false member IsTimeDistributor is not set
   */
  bool getIsTimeDistributorIsSet() const;

  /**
   * Unsets member IsTimeDistributor
   */
  void cleanIsTimeDistributor();

  /**
   * Set member DistributorPriority.
   * @param c_distributorPriority Value to set
   */
  void setDistributorPriority(const xs_unsignedInt &c_distributorPriority);

  /**
   * Returns const reference to member DistributorPriority.
   * @return const reference to member distributorPriority
   */
  const xs_unsignedInt &getDistributorPriority() const;

  /**
   * Returns if member DistributorPriority is set.
   * @retval true member DistributorPriority is set
   * @retval false member DistributorPriority is not set
   */
  bool getDistributorPriorityIsSet() const;

  /**
   * Unsets member DistributorPriority
   */
  void cleanDistributorPriority();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_isTimeDistributorIsSet;
  xs_boolean m_isTimeDistributor;

  bool m_distributorPriorityIsSet;
  xs_unsignedInt m_distributorPriority;
};

//! typedef for non-const smart pointer type TimeDistributorData
using TimeDistributorDataPtr = std::shared_ptr<TimeDistributorData>;

//! typedef for const type TimeDistributorData
using TimeDistributorDataConst = const TimeDistributorData;

//! typedef for const type TimeDistributorData
using TimeDistributorDataConstPtr = std::shared_ptr<TimeDistributorDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMEINFORMATION_TIMEDISTRIBUTORDATA_H_