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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSRESUMEIMPLICATIONDATA_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSRESUMEIMPLICATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/Currency.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsResumeImplicationDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsResumeImplicationData
 */
class OperatingConstraintsResumeImplicationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsResumeImplicationData();

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
      const OperatingConstraintsResumeImplicationData &c_classObject) const;

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
      const OperatingConstraintsResumeImplicationData &c_classObject) const;

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
   * Set member ResumeEnergyEstimated.
   * @param c_resumeEnergyEstimated Value to set
   */
  void setResumeEnergyEstimated(const ScaledNumber &c_resumeEnergyEstimated);

  /**
   * Returns const reference to member ResumeEnergyEstimated.
   * @return const reference to member resumeEnergyEstimated
   */
  const ScaledNumber &getResumeEnergyEstimated() const;

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
   * @param c_energyUnit Value to set
   */
  void setEnergyUnit(const UnitOfMeasurement &c_energyUnit);

  /**
   * Returns const reference to member EnergyUnit.
   * @return const reference to member energyUnit
   */
  const UnitOfMeasurement &getEnergyUnit() const;

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
  void setResumeCostEstimated(const ScaledNumber &c_resumeCostEstimated);

  /**
   * Returns const reference to member ResumeCostEstimated.
   * @return const reference to member resumeCostEstimated
   */
  const ScaledNumber &getResumeCostEstimated() const;

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
   * @param c_currency Value to set
   */
  void setCurrency(const Currency &c_currency);

  /**
   * Returns const reference to member Currency.
   * @return const reference to member currency
   */
  const Currency &getCurrency() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  OperatingConstraintsResumeImplicationData reduce(
      const OperatingConstraintsResumeImplicationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_resumeEnergyEstimatedIsSet;
  ScaledNumber m_resumeEnergyEstimated;

  bool m_energyUnitIsSet;
  UnitOfMeasurement m_energyUnit;

  bool m_resumeCostEstimatedIsSet;
  ScaledNumber m_resumeCostEstimated;

  bool m_currencyIsSet;
  Currency m_currency;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsResumeImplicationData
using OperatingConstraintsResumeImplicationDataPtr =
    std::shared_ptr<OperatingConstraintsResumeImplicationData>;

//! typedef for const type OperatingConstraintsResumeImplicationData
using OperatingConstraintsResumeImplicationDataConst =
    const OperatingConstraintsResumeImplicationData;

//! typedef for const type OperatingConstraintsResumeImplicationData
using OperatingConstraintsResumeImplicationDataConstPtr =
    std::shared_ptr<OperatingConstraintsResumeImplicationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSRESUMEIMPLICATIONDATA_H_