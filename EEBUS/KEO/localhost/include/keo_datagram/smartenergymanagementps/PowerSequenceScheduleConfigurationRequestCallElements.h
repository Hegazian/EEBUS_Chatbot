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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONFIGURATIONREQUESTCALLELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONFIGURATIONREQUESTCALLELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceScheduleConfigurationRequestCallElements
 */
class PowerSequenceScheduleConfigurationRequestCallElements
    : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceScheduleConfigurationRequestCallElements();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_sequenceIdIsSet the member to set
   */
  explicit PowerSequenceScheduleConfigurationRequestCallElements(
      const xs_boolean &c_sequenceIdIsSet);

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
  bool operator==(const PowerSequenceScheduleConfigurationRequestCallElements
                      &c_classObject) const;

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
  bool operator!=(const PowerSequenceScheduleConfigurationRequestCallElements
                      &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member SequenceId.
   */
  void setSequenceId();

  /**
   * Returns if member SequenceId is set.
   * @retval true member SequenceId is set
   * @retval false member SequenceId is not set
   */
  bool getSequenceIdIsSet() const;

  /**
   * Unsets member SequenceId
   */
  void cleanSequenceId();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;
};

//! typedef for non-const smart pointer type
//! PowerSequenceScheduleConfigurationRequestCallElements
using PowerSequenceScheduleConfigurationRequestCallElementsPtr =
    std::shared_ptr<PowerSequenceScheduleConfigurationRequestCallElements>;

//! typedef for const type PowerSequenceScheduleConfigurationRequestCallElements
using PowerSequenceScheduleConfigurationRequestCallElementsConst =
    const PowerSequenceScheduleConfigurationRequestCallElements;

//! typedef for const type PowerSequenceScheduleConfigurationRequestCallElements
using PowerSequenceScheduleConfigurationRequestCallElementsConstPtr =
    std::shared_ptr<PowerSequenceScheduleConfigurationRequestCallElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULECONFIGURATIONREQUESTCALLELEMENTS_H_