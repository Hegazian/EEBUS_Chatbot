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

#ifndef KEO_DATAGRAM_TIMEINFORMATION_TIMEDISTRIBUTORDATAELEMENTS_H_
#define KEO_DATAGRAM_TIMEINFORMATION_TIMEDISTRIBUTORDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramTimeInformation
 * @{
 */

/**
 * Declaration TimeDistributorDataElements
 */
class TimeDistributorDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  TimeDistributorDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_isTimeDistributorIsSet the member to set
   * @param c_distributorPriorityIsSet the member to set
   */
  TimeDistributorDataElements(xs_boolean c_isTimeDistributorIsSet,
                              xs_boolean c_distributorPriorityIsSet);

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
  bool operator==(const TimeDistributorDataElements &c_classObject) const;

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
  bool operator!=(const TimeDistributorDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member IsTimeDistributor.
   */
  void setIsTimeDistributor();

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
   */
  void setDistributorPriority();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_isTimeDistributorIsSet;

  // ElementTag
  bool m_distributorPriorityIsSet;
};

//! typedef for non-const smart pointer type TimeDistributorDataElements
using TimeDistributorDataElementsPtr =
    std::shared_ptr<TimeDistributorDataElements>;

//! typedef for const type TimeDistributorDataElements
using TimeDistributorDataElementsConst = const TimeDistributorDataElements;

//! typedef for const type TimeDistributorDataElements
using TimeDistributorDataElementsConstPtr =
    std::shared_ptr<TimeDistributorDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_TIMEINFORMATION_TIMEDISTRIBUTORDATAELEMENTS_H_