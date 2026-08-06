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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSDURATIONDATAELEMENTS_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSDURATIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsDurationDataElements
 */
class OperatingConstraintsDurationDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsDurationDataElements();

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
      const OperatingConstraintsDurationDataElements &c_classObject) const;

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
      const OperatingConstraintsDurationDataElements &c_classObject) const;

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
   * Set member ActiveDurationMin.
   */
  void setActiveDurationMin();

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
   */
  void setActiveDurationMax();

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
   */
  void setPauseDurationMin();

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
   */
  void setPauseDurationMax();

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
   */
  void setActiveDurationSumMin();

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
   */
  void setActiveDurationSumMax();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_activeDurationMinIsSet;

  // ElementTag
  bool m_activeDurationMaxIsSet;

  // ElementTag
  bool m_pauseDurationMinIsSet;

  // ElementTag
  bool m_pauseDurationMaxIsSet;

  // ElementTag
  bool m_activeDurationSumMinIsSet;

  // ElementTag
  bool m_activeDurationSumMaxIsSet;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsDurationDataElements
using OperatingConstraintsDurationDataElementsPtr =
    std::shared_ptr<OperatingConstraintsDurationDataElements>;

//! typedef for const type OperatingConstraintsDurationDataElements
using OperatingConstraintsDurationDataElementsConst =
    const OperatingConstraintsDurationDataElements;

//! typedef for const type OperatingConstraintsDurationDataElements
using OperatingConstraintsDurationDataElementsConstPtr =
    std::shared_ptr<OperatingConstraintsDurationDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSDURATIONDATAELEMENTS_H_