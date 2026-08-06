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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCENODESCHEDULEINFORMATIONDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCENODESCHEDULEINFORMATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceNodeScheduleInformationData
 */
class PowerSequenceNodeScheduleInformationData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceNodeScheduleInformationData();

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
      const PowerSequenceNodeScheduleInformationData &c_classObject) const;

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
      const PowerSequenceNodeScheduleInformationData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member NodeRemoteControllable.
   * @param c_nodeRemoteControllable Value to set
   */
  void setNodeRemoteControllable(const xs_boolean &c_nodeRemoteControllable);

  /**
   * Returns const reference to member NodeRemoteControllable.
   * @return const reference to member nodeRemoteControllable
   */
  const xs_boolean &getNodeRemoteControllable() const;

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
   * @param c_supportsSingleSlotSchedulingOnly Value to set
   */
  void setSupportsSingleSlotSchedulingOnly(
      const xs_boolean &c_supportsSingleSlotSchedulingOnly);

  /**
   * Returns const reference to member SupportsSingleSlotSchedulingOnly.
   * @return const reference to member supportsSingleSlotSchedulingOnly
   */
  const xs_boolean &getSupportsSingleSlotSchedulingOnly() const;

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
   * @param c_alternativesCount Value to set
   */
  void setAlternativesCount(const xs_unsignedInt &c_alternativesCount);

  /**
   * Returns const reference to member AlternativesCount.
   * @return const reference to member alternativesCount
   */
  const xs_unsignedInt &getAlternativesCount() const;

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
   * @param c_totalSequencesCountMax Value to set
   */
  void
  setTotalSequencesCountMax(const xs_unsignedInt &c_totalSequencesCountMax);

  /**
   * Returns const reference to member TotalSequencesCountMax.
   * @return const reference to member totalSequencesCountMax
   */
  const xs_unsignedInt &getTotalSequencesCountMax() const;

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
   * @param c_supportsReselection Value to set
   */
  void setSupportsReselection(const xs_boolean &c_supportsReselection);

  /**
   * Returns const reference to member SupportsReselection.
   * @return const reference to member supportsReselection
   */
  const xs_boolean &getSupportsReselection() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_nodeRemoteControllableIsSet;
  xs_boolean m_nodeRemoteControllable;

  bool m_supportsSingleSlotSchedulingOnlyIsSet;
  xs_boolean m_supportsSingleSlotSchedulingOnly;

  bool m_alternativesCountIsSet;
  xs_unsignedInt m_alternativesCount;

  bool m_totalSequencesCountMaxIsSet;
  xs_unsignedInt m_totalSequencesCountMax;

  bool m_supportsReselectionIsSet;
  xs_boolean m_supportsReselection;
};

//! typedef for non-const smart pointer type
//! PowerSequenceNodeScheduleInformationData
using PowerSequenceNodeScheduleInformationDataPtr =
    std::shared_ptr<PowerSequenceNodeScheduleInformationData>;

//! typedef for const type PowerSequenceNodeScheduleInformationData
using PowerSequenceNodeScheduleInformationDataConst =
    const PowerSequenceNodeScheduleInformationData;

//! typedef for const type PowerSequenceNodeScheduleInformationData
using PowerSequenceNodeScheduleInformationDataConstPtr =
    std::shared_ptr<PowerSequenceNodeScheduleInformationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCENODESCHEDULEINFORMATIONDATA_H_