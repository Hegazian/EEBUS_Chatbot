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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSRESUMEIMPLICATIONDATAELEMENTS_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSRESUMEIMPLICATIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsResumeImplicationDataElements
 */
class OperatingConstraintsResumeImplicationDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsResumeImplicationDataElements();

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
  bool operator==(const OperatingConstraintsResumeImplicationDataElements
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
  bool operator!=(const OperatingConstraintsResumeImplicationDataElements
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

  /**
   * Set member ResumeEnergyEstimated.
   * @param c_resumeEnergyEstimated Value to set
   */
  void
  setResumeEnergyEstimated(const ScaledNumberElements &c_resumeEnergyEstimated);

  /**
   * Returns const reference to member ResumeEnergyEstimated.
   * @return const reference to member resumeEnergyEstimated
   */
  const ScaledNumberElements &getResumeEnergyEstimated() const;

  /**
   * Returns if member ResumeEnergyEstimated is set.
   * @retval true member ResumeEnergyEstimated is set
   * @retval false member ResumeEnergyEstimated is not set
   */
  bool getResumeEnergyEstimatedIsSet() const;

  /**
   * Unsets member ResumeEnergyEstimated
   */
  void cleanResumeEnergyEstimated();

  /**
   * Set member EnergyUnit.
   */
  void setEnergyUnit();

  /**
   * Returns if member EnergyUnit is set.
   * @retval true member EnergyUnit is set
   * @retval false member EnergyUnit is not set
   */
  bool getEnergyUnitIsSet() const;

  /**
   * Unsets member EnergyUnit
   */
  void cleanEnergyUnit();

  /**
   * Set member ResumeCostEstimated.
   * @param c_resumeCostEstimated Value to set
   */
  void
  setResumeCostEstimated(const ScaledNumberElements &c_resumeCostEstimated);

  /**
   * Returns const reference to member ResumeCostEstimated.
   * @return const reference to member resumeCostEstimated
   */
  const ScaledNumberElements &getResumeCostEstimated() const;

  /**
   * Returns if member ResumeCostEstimated is set.
   * @retval true member ResumeCostEstimated is set
   * @retval false member ResumeCostEstimated is not set
   */
  bool getResumeCostEstimatedIsSet() const;

  /**
   * Unsets member ResumeCostEstimated
   */
  void cleanResumeCostEstimated();

  /**
   * Set member Currency.
   */
  void setCurrency();

  /**
   * Returns if member Currency is set.
   * @retval true member Currency is set
   * @retval false member Currency is not set
   */
  bool getCurrencyIsSet() const;

  /**
   * Unsets member Currency
   */
  void cleanCurrency();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  bool m_resumeEnergyEstimatedIsSet;
  ScaledNumberElements m_resumeEnergyEstimated;

  // ElementTag
  bool m_energyUnitIsSet;

  bool m_resumeCostEstimatedIsSet;
  ScaledNumberElements m_resumeCostEstimated;

  // ElementTag
  bool m_currencyIsSet;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsResumeImplicationDataElements
using OperatingConstraintsResumeImplicationDataElementsPtr =
    std::shared_ptr<OperatingConstraintsResumeImplicationDataElements>;

//! typedef for const type OperatingConstraintsResumeImplicationDataElements
using OperatingConstraintsResumeImplicationDataElementsConst =
    const OperatingConstraintsResumeImplicationDataElements;

//! typedef for const type OperatingConstraintsResumeImplicationDataElements
using OperatingConstraintsResumeImplicationDataElementsConstPtr =
    std::shared_ptr<OperatingConstraintsResumeImplicationDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSRESUMEIMPLICATIONDATAELEMENTS_H_