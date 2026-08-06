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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEPREFERENCEDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEPREFERENCEDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceSchedulePreferenceDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceSchedulePreferenceData
 */
class PowerSequenceSchedulePreferenceData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceSchedulePreferenceData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_sequenceId the member to set
   * @param c_greenest the member to set
   * @param c_cheapest the member to set
   */
  PowerSequenceSchedulePreferenceData(const xs_unsignedInt &c_sequenceId,
                                      const xs_boolean &c_greenest,
                                      const xs_boolean &c_cheapest);

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
  bool
  operator==(const PowerSequenceSchedulePreferenceData &c_classObject) const;

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
  bool
  operator!=(const PowerSequenceSchedulePreferenceData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SequenceId.
   * @param c_sequenceId Value to set
   */
  void setSequenceId(const xs_unsignedInt &c_sequenceId);

  /**
   * Returns const reference to member SequenceId.
   * @return const reference to member sequenceId
   */
  const xs_unsignedInt &getSequenceId() const;

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
   * @param c_greenest Value to set
   */
  void setGreenest(const xs_boolean &c_greenest);

  /**
   * Returns const reference to member Greenest.
   * @return const reference to member greenest
   */
  const xs_boolean &getGreenest() const;

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
   * @param c_cheapest Value to set
   */
  void setCheapest(const xs_boolean &c_cheapest);

  /**
   * Returns const reference to member Cheapest.
   * @return const reference to member cheapest
   */
  const xs_boolean &getCheapest() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  PowerSequenceSchedulePreferenceData
  reduce(const PowerSequenceSchedulePreferenceDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_greenestIsSet;
  xs_boolean m_greenest;

  bool m_cheapestIsSet;
  xs_boolean m_cheapest;
};

//! typedef for non-const smart pointer type PowerSequenceSchedulePreferenceData
using PowerSequenceSchedulePreferenceDataPtr =
    std::shared_ptr<PowerSequenceSchedulePreferenceData>;

//! typedef for const type PowerSequenceSchedulePreferenceData
using PowerSequenceSchedulePreferenceDataConst =
    const PowerSequenceSchedulePreferenceData;

//! typedef for const type PowerSequenceSchedulePreferenceData
using PowerSequenceSchedulePreferenceDataConstPtr =
    std::shared_ptr<PowerSequenceSchedulePreferenceDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCESCHEDULEPREFERENCEDATA_H_