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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSDURATIONDATA_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSDURATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoDuration.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsDurationDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsDurationData
 */
class OperatingConstraintsDurationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsDurationData();

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
  bool operator==(const OperatingConstraintsDurationData &c_classObject) const;

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
  bool operator!=(const OperatingConstraintsDurationData &c_classObject) const;

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
   * Set member ActiveDurationMin.
   * @param c_activeDurationMin Value to set
   */
  void setActiveDurationMin(const xs_duration &c_activeDurationMin);

  /**
   * Returns const reference to member ActiveDurationMin.
   * @return const reference to member activeDurationMin
   */
  const xs_duration &getActiveDurationMin() const;

  /**
   * Returns if member ActiveDurationMin is set.
   * @retval true member ActiveDurationMin is set
   * @retval false member ActiveDurationMin is not set
   */
  bool getActiveDurationMinIsSet() const;

  /**
   * Unsets member ActiveDurationMin
   */
  void cleanActiveDurationMin();

  /**
   * Set member ActiveDurationMax.
   * @param c_activeDurationMax Value to set
   */
  void setActiveDurationMax(const xs_duration &c_activeDurationMax);

  /**
   * Returns const reference to member ActiveDurationMax.
   * @return const reference to member activeDurationMax
   */
  const xs_duration &getActiveDurationMax() const;

  /**
   * Returns if member ActiveDurationMax is set.
   * @retval true member ActiveDurationMax is set
   * @retval false member ActiveDurationMax is not set
   */
  bool getActiveDurationMaxIsSet() const;

  /**
   * Unsets member ActiveDurationMax
   */
  void cleanActiveDurationMax();

  /**
   * Set member PauseDurationMin.
   * @param c_pauseDurationMin Value to set
   */
  void setPauseDurationMin(const xs_duration &c_pauseDurationMin);

  /**
   * Returns const reference to member PauseDurationMin.
   * @return const reference to member pauseDurationMin
   */
  const xs_duration &getPauseDurationMin() const;

  /**
   * Returns if member PauseDurationMin is set.
   * @retval true member PauseDurationMin is set
   * @retval false member PauseDurationMin is not set
   */
  bool getPauseDurationMinIsSet() const;

  /**
   * Unsets member PauseDurationMin
   */
  void cleanPauseDurationMin();

  /**
   * Set member PauseDurationMax.
   * @param c_pauseDurationMax Value to set
   */
  void setPauseDurationMax(const xs_duration &c_pauseDurationMax);

  /**
   * Returns const reference to member PauseDurationMax.
   * @return const reference to member pauseDurationMax
   */
  const xs_duration &getPauseDurationMax() const;

  /**
   * Returns if member PauseDurationMax is set.
   * @retval true member PauseDurationMax is set
   * @retval false member PauseDurationMax is not set
   */
  bool getPauseDurationMaxIsSet() const;

  /**
   * Unsets member PauseDurationMax
   */
  void cleanPauseDurationMax();

  /**
   * Set member ActiveDurationSumMin.
   * @param c_activeDurationSumMin Value to set
   */
  void setActiveDurationSumMin(const xs_duration &c_activeDurationSumMin);

  /**
   * Returns const reference to member ActiveDurationSumMin.
   * @return const reference to member activeDurationSumMin
   */
  const xs_duration &getActiveDurationSumMin() const;

  /**
   * Returns if member ActiveDurationSumMin is set.
   * @retval true member ActiveDurationSumMin is set
   * @retval false member ActiveDurationSumMin is not set
   */
  bool getActiveDurationSumMinIsSet() const;

  /**
   * Unsets member ActiveDurationSumMin
   */
  void cleanActiveDurationSumMin();

  /**
   * Set member ActiveDurationSumMax.
   * @param c_activeDurationSumMax Value to set
   */
  void setActiveDurationSumMax(const xs_duration &c_activeDurationSumMax);

  /**
   * Returns const reference to member ActiveDurationSumMax.
   * @return const reference to member activeDurationSumMax
   */
  const xs_duration &getActiveDurationSumMax() const;

  /**
   * Returns if member ActiveDurationSumMax is set.
   * @retval true member ActiveDurationSumMax is set
   * @retval false member ActiveDurationSumMax is not set
   */
  bool getActiveDurationSumMaxIsSet() const;

  /**
   * Unsets member ActiveDurationSumMax
   */
  void cleanActiveDurationSumMax();

  /**
   * @copydoc CmdData::reduce()
   */
  OperatingConstraintsDurationData
  reduce(const OperatingConstraintsDurationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_activeDurationMinIsSet;
  xs_duration m_activeDurationMin;

  bool m_activeDurationMaxIsSet;
  xs_duration m_activeDurationMax;

  bool m_pauseDurationMinIsSet;
  xs_duration m_pauseDurationMin;

  bool m_pauseDurationMaxIsSet;
  xs_duration m_pauseDurationMax;

  bool m_activeDurationSumMinIsSet;
  xs_duration m_activeDurationSumMin;

  bool m_activeDurationSumMaxIsSet;
  xs_duration m_activeDurationSumMax;
};

//! typedef for non-const smart pointer type OperatingConstraintsDurationData
using OperatingConstraintsDurationDataPtr =
    std::shared_ptr<OperatingConstraintsDurationData>;

//! typedef for const type OperatingConstraintsDurationData
using OperatingConstraintsDurationDataConst =
    const OperatingConstraintsDurationData;

//! typedef for const type OperatingConstraintsDurationData
using OperatingConstraintsDurationDataConstPtr =
    std::shared_ptr<OperatingConstraintsDurationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSDURATIONDATA_H_