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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCENODESCHEDULEINFORMATIONDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCENODESCHEDULEINFORMATIONDATAELEMENTS_H_

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
 * Declaration PowerSequenceNodeScheduleInformationDataElements
 */
class PowerSequenceNodeScheduleInformationDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceNodeScheduleInformationDataElements();

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
  bool operator==(const PowerSequenceNodeScheduleInformationDataElements
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
  bool operator!=(const PowerSequenceNodeScheduleInformationDataElements
                      &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member NodeRemoteControllable.
   */
  void setNodeRemoteControllable();

  /**
   * Returns if member NodeRemoteControllable is set.
   * @retval true member NodeRemoteControllable is set
   * @retval false member NodeRemoteControllable is not set
   */
  bool getNodeRemoteControllableIsSet() const;

  /**
   * Unsets member NodeRemoteControllable
   */
  void cleanNodeRemoteControllable();

  /**
   * Set member SupportsSingleSlotSchedulingOnly.
   */
  void setSupportsSingleSlotSchedulingOnly();

  /**
   * Returns if member SupportsSingleSlotSchedulingOnly is set.
   * @retval true member SupportsSingleSlotSchedulingOnly is set
   * @retval false member SupportsSingleSlotSchedulingOnly is not set
   */
  bool getSupportsSingleSlotSchedulingOnlyIsSet() const;

  /**
   * Unsets member SupportsSingleSlotSchedulingOnly
   */
  void cleanSupportsSingleSlotSchedulingOnly();

  /**
   * Set member AlternativesCount.
   */
  void setAlternativesCount();

  /**
   * Returns if member AlternativesCount is set.
   * @retval true member AlternativesCount is set
   * @retval false member AlternativesCount is not set
   */
  bool getAlternativesCountIsSet() const;

  /**
   * Unsets member AlternativesCount
   */
  void cleanAlternativesCount();

  /**
   * Set member TotalSequencesCountMax.
   */
  void setTotalSequencesCountMax();

  /**
   * Returns if member TotalSequencesCountMax is set.
   * @retval true member TotalSequencesCountMax is set
   * @retval false member TotalSequencesCountMax is not set
   */
  bool getTotalSequencesCountMaxIsSet() const;

  /**
   * Unsets member TotalSequencesCountMax
   */
  void cleanTotalSequencesCountMax();

  /**
   * Set member SupportsReselection.
   */
  void setSupportsReselection();

  /**
   * Returns if member SupportsReselection is set.
   * @retval true member SupportsReselection is set
   * @retval false member SupportsReselection is not set
   */
  bool getSupportsReselectionIsSet() const;

  /**
   * Unsets member SupportsReselection
   */
  void cleanSupportsReselection();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_nodeRemoteControllableIsSet;

  // ElementTag
  bool m_supportsSingleSlotSchedulingOnlyIsSet;

  // ElementTag
  bool m_alternativesCountIsSet;

  // ElementTag
  bool m_totalSequencesCountMaxIsSet;

  // ElementTag
  bool m_supportsReselectionIsSet;
};

//! typedef for non-const smart pointer type
//! PowerSequenceNodeScheduleInformationDataElements
using PowerSequenceNodeScheduleInformationDataElementsPtr =
    std::shared_ptr<PowerSequenceNodeScheduleInformationDataElements>;

//! typedef for const type PowerSequenceNodeScheduleInformationDataElements
using PowerSequenceNodeScheduleInformationDataElementsConst =
    const PowerSequenceNodeScheduleInformationDataElements;

//! typedef for const type PowerSequenceNodeScheduleInformationDataElements
using PowerSequenceNodeScheduleInformationDataElementsConstPtr =
    std::shared_ptr<PowerSequenceNodeScheduleInformationDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCENODESCHEDULEINFORMATIONDATAELEMENTS_H_