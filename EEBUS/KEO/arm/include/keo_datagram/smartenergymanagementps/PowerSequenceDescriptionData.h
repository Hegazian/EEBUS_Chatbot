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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/EnergyDirection.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/measurement/MeasurementValueSource.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceDescriptionDataElements.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceScope.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceDescriptionData
 */
class PowerSequenceDescriptionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceDescriptionData();

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
  bool operator==(const PowerSequenceDescriptionData &c_classObject) const;

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
  bool operator!=(const PowerSequenceDescriptionData &c_classObject) const;

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
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * Set member PositiveEnergyDirection.
   * @param c_positiveEnergyDirection Value to set
   */
  void
  setPositiveEnergyDirection(const EnergyDirection &c_positiveEnergyDirection);

  /**
   * Returns const reference to member PositiveEnergyDirection.
   * @return const reference to member positiveEnergyDirection
   */
  const EnergyDirection &getPositiveEnergyDirection() const;

  /**
   * Returns if member PositiveEnergyDirection is set.
   * @retval true member PositiveEnergyDirection is set
   * @retval false member PositiveEnergyDirection is not set
   */
  bool getPositiveEnergyDirectionIsSet() const;

  /**
   * Unsets member PositiveEnergyDirection
   */
  void cleanPositiveEnergyDirection();

  /**
   * Set member PowerUnit.
   * @param c_powerUnit Value to set
   */
  void setPowerUnit(const UnitOfMeasurement &c_powerUnit);

  /**
   * Returns const reference to member PowerUnit.
   * @return const reference to member powerUnit
   */
  const UnitOfMeasurement &getPowerUnit() const;

  /**
   * Returns if member PowerUnit is set.
   * @retval true member PowerUnit is set
   * @retval false member PowerUnit is not set
   */
  bool getPowerUnitIsSet() const;

  /**
   * Unsets member PowerUnit
   */
  void cleanPowerUnit();

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
   * Set member ValueSource.
   * @param c_valueSource Value to set
   */
  void setValueSource(const MeasurementValueSource &c_valueSource);

  /**
   * Returns const reference to member ValueSource.
   * @return const reference to member valueSource
   */
  const MeasurementValueSource &getValueSource() const;

  /**
   * Returns if member ValueSource is set.
   * @retval true member ValueSource is set
   * @retval false member ValueSource is not set
   */
  bool getValueSourceIsSet() const;

  /**
   * Unsets member ValueSource
   */
  void cleanValueSource();

  /**
   * Set member Scope.
   * @param c_scope Value to set
   */
  void setScope(const PowerSequenceScope &c_scope);

  /**
   * Returns const reference to member Scope.
   * @return const reference to member scope
   */
  const PowerSequenceScope &getScope() const;

  /**
   * Returns if member Scope is set.
   * @retval true member Scope is set
   * @retval false member Scope is not set
   */
  bool getScopeIsSet() const;

  /**
   * Unsets member Scope
   */
  void cleanScope();

  /**
   * Set member TaskIdentifier.
   * @param c_taskIdentifier Value to set
   */
  void setTaskIdentifier(const xs_unsignedInt &c_taskIdentifier);

  /**
   * Returns const reference to member TaskIdentifier.
   * @return const reference to member taskIdentifier
   */
  const xs_unsignedInt &getTaskIdentifier() const;

  /**
   * Returns if member TaskIdentifier is set.
   * @retval true member TaskIdentifier is set
   * @retval false member TaskIdentifier is not set
   */
  bool getTaskIdentifierIsSet() const;

  /**
   * Unsets member TaskIdentifier
   */
  void cleanTaskIdentifier();

  /**
   * Set member RepetitionsTotal.
   * @param c_repetitionsTotal Value to set
   */
  void setRepetitionsTotal(const xs_unsignedInt &c_repetitionsTotal);

  /**
   * Returns const reference to member RepetitionsTotal.
   * @return const reference to member repetitionsTotal
   */
  const xs_unsignedInt &getRepetitionsTotal() const;

  /**
   * Returns if member RepetitionsTotal is set.
   * @retval true member RepetitionsTotal is set
   * @retval false member RepetitionsTotal is not set
   */
  bool getRepetitionsTotalIsSet() const;

  /**
   * Unsets member RepetitionsTotal
   */
  void cleanRepetitionsTotal();

  /**
   * @copydoc CmdData::reduce()
   */
  PowerSequenceDescriptionData
  reduce(const PowerSequenceDescriptionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;

  bool m_descriptionIsSet;
  xs_string m_description;

  bool m_positiveEnergyDirectionIsSet;
  EnergyDirection m_positiveEnergyDirection;

  bool m_powerUnitIsSet;
  UnitOfMeasurement m_powerUnit;

  bool m_energyUnitIsSet;
  UnitOfMeasurement m_energyUnit;

  bool m_valueSourceIsSet;
  MeasurementValueSource m_valueSource;

  bool m_scopeIsSet;
  PowerSequenceScope m_scope;

  bool m_taskIdentifierIsSet;
  xs_unsignedInt m_taskIdentifier;

  bool m_repetitionsTotalIsSet;
  xs_unsignedInt m_repetitionsTotal;
};

//! typedef for non-const smart pointer type PowerSequenceDescriptionData
using PowerSequenceDescriptionDataPtr =
    std::shared_ptr<PowerSequenceDescriptionData>;

//! typedef for const type PowerSequenceDescriptionData
using PowerSequenceDescriptionDataConst = const PowerSequenceDescriptionData;

//! typedef for const type PowerSequenceDescriptionData
using PowerSequenceDescriptionDataConstPtr =
    std::shared_ptr<PowerSequenceDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEDESCRIPTIONDATA_H_