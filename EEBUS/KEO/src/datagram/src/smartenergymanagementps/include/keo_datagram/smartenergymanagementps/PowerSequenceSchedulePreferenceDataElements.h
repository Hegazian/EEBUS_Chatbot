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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEPREFERENCEDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEPREFERENCEDATAELEMENTS_H_

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
 * Declaration PowerSequenceSchedulePreferenceDataElements
 */
class PowerSequenceSchedulePreferenceDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceSchedulePreferenceDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceIdIsSet the member to set
   * @param c_greenestIsSet the member to set
   * @param c_cheapestIsSet the member to set
   */
  PowerSequenceSchedulePreferenceDataElements(xs_boolean c_sequenceIdIsSet,
                                              xs_boolean c_greenestIsSet,
                                              xs_boolean c_cheapestIsSet);

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
  bool operator==(
      const PowerSequenceSchedulePreferenceDataElements &c_classObject) const;

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
  bool operator!=(
      const PowerSequenceSchedulePreferenceDataElements &c_classObject) const;

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

  /**
   * Set member Greenest.
   */
  void setGreenest();

  /**
   * Returns if member Greenest is set.
   * @retval true member Greenest is set
   * @retval false member Greenest is not set
   */
  bool getGreenestIsSet() const;

  /**
   * Unsets member Greenest
   */
  void cleanGreenest();

  /**
   * Set member Cheapest.
   */
  void setCheapest();

  /**
   * Returns if member Cheapest is set.
   * @retval true member Cheapest is set
   * @retval false member Cheapest is not set
   */
  bool getCheapestIsSet() const;

  /**
   * Unsets member Cheapest
   */
  void cleanCheapest();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_greenestIsSet;

  // ElementTag
  bool m_cheapestIsSet;
};

//! typedef for non-const smart pointer type
//! PowerSequenceSchedulePreferenceDataElements
using PowerSequenceSchedulePreferenceDataElementsPtr =
    std::shared_ptr<PowerSequenceSchedulePreferenceDataElements>;

//! typedef for const type PowerSequenceSchedulePreferenceDataElements
using PowerSequenceSchedulePreferenceDataElementsConst =
    const PowerSequenceSchedulePreferenceDataElements;

//! typedef for const type PowerSequenceSchedulePreferenceDataElements
using PowerSequenceSchedulePreferenceDataElementsConstPtr =
    std::shared_ptr<PowerSequenceSchedulePreferenceDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEPREFERENCEDATAELEMENTS_H_