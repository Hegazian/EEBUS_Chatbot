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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATASELECTORS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotScheduleListDataSelectors.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueListDataSelectors.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsDataSelectors
 */
class SmartEnergyManagementPsDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsDataSelectors();

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
  operator==(const SmartEnergyManagementPsDataSelectors &c_classObject) const;

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
  operator!=(const SmartEnergyManagementPsDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member AlternativesRelation.
   * @param c_alternativesRelation Value to set
   */
  void setAlternativesRelation(
      const PowerSequenceAlternativesRelationListDataSelectors
          &c_alternativesRelation);

  /**
   * Returns const reference to member AlternativesRelation.
   * @return const reference to member alternativesRelation
   */
  const PowerSequenceAlternativesRelationListDataSelectors &
  getAlternativesRelation() const;

  /**
   * Returns if member AlternativesRelation is set.
   * @retval true member AlternativesRelation is set
   * @retval false member AlternativesRelation is not set
   */
  bool getAlternativesRelationIsSet() const;

  /**
   * Unsets member AlternativesRelation
   */
  void cleanAlternativesRelation();

  /**
   * Set member PowerSequenceDescription.
   * @param c_powerSequenceDescription Value to set
   */
  void
  setPowerSequenceDescription(const PowerSequenceDescriptionListDataSelectors
                                  &c_powerSequenceDescription);

  /**
   * Returns const reference to member PowerSequenceDescription.
   * @return const reference to member powerSequenceDescription
   */
  const PowerSequenceDescriptionListDataSelectors &
  getPowerSequenceDescription() const;

  /**
   * Returns if member PowerSequenceDescription is set.
   * @retval true member PowerSequenceDescription is set
   * @retval false member PowerSequenceDescription is not set
   */
  bool getPowerSequenceDescriptionIsSet() const;

  /**
   * Unsets member PowerSequenceDescription
   */
  void cleanPowerSequenceDescription();

  /**
   * Set member PowerTimeSlotSchedule.
   * @param c_powerTimeSlotSchedule Value to set
   */
  void setPowerTimeSlotSchedule(
      const PowerTimeSlotScheduleListDataSelectors &c_powerTimeSlotSchedule);

  /**
   * Returns const reference to member PowerTimeSlotSchedule.
   * @return const reference to member powerTimeSlotSchedule
   */
  const PowerTimeSlotScheduleListDataSelectors &
  getPowerTimeSlotSchedule() const;

  /**
   * Returns if member PowerTimeSlotSchedule is set.
   * @retval true member PowerTimeSlotSchedule is set
   * @retval false member PowerTimeSlotSchedule is not set
   */
  bool getPowerTimeSlotScheduleIsSet() const;

  /**
   * Unsets member PowerTimeSlotSchedule
   */
  void cleanPowerTimeSlotSchedule();

  /**
   * Set member PowerTimeSlotValue.
   * @param c_powerTimeSlotValue Value to set
   */
  void setPowerTimeSlotValue(
      const PowerTimeSlotValueListDataSelectors &c_powerTimeSlotValue);

  /**
   * Returns const reference to member PowerTimeSlotValue.
   * @return const reference to member powerTimeSlotValue
   */
  const PowerTimeSlotValueListDataSelectors &getPowerTimeSlotValue() const;

  /**
   * Returns if member PowerTimeSlotValue is set.
   * @retval true member PowerTimeSlotValue is set
   * @retval false member PowerTimeSlotValue is not set
   */
  bool getPowerTimeSlotValueIsSet() const;

  /**
   * Unsets member PowerTimeSlotValue
   */
  void cleanPowerTimeSlotValue();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_alternativesRelationIsSet;
  PowerSequenceAlternativesRelationListDataSelectors m_alternativesRelation;

  bool m_powerSequenceDescriptionIsSet;
  PowerSequenceDescriptionListDataSelectors m_powerSequenceDescription;

  bool m_powerTimeSlotScheduleIsSet;
  PowerTimeSlotScheduleListDataSelectors m_powerTimeSlotSchedule;

  bool m_powerTimeSlotValueIsSet;
  PowerTimeSlotValueListDataSelectors m_powerTimeSlotValue;
};

//! typedef for non-const smart pointer type
//! SmartEnergyManagementPsDataSelectors
using SmartEnergyManagementPsDataSelectorsPtr =
    std::shared_ptr<SmartEnergyManagementPsDataSelectors>;

//! typedef for const type SmartEnergyManagementPsDataSelectors
using SmartEnergyManagementPsDataSelectorsConst =
    const SmartEnergyManagementPsDataSelectors;

//! typedef for const type SmartEnergyManagementPsDataSelectors
using SmartEnergyManagementPsDataSelectorsConstPtr =
    std::shared_ptr<SmartEnergyManagementPsDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATASELECTORS_H_