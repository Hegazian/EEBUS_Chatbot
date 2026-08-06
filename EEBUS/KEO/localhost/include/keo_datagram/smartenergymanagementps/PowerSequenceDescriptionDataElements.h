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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEDESCRIPTIONDATAELEMENTS_H_

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
 * Declaration PowerSequenceDescriptionDataElements
 */
class PowerSequenceDescriptionDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceDescriptionDataElements();

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
  operator==(const PowerSequenceDescriptionDataElements &c_classObject) const;

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
  operator!=(const PowerSequenceDescriptionDataElements &c_classObject) const;

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
   * Set member Description.
   */
  void setDescription();

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
   */
  void setPositiveEnergyDirection();

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
   */
  void setPowerUnit();

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
   * Set member ValueSource.
   */
  void setValueSource();

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
   */
  void setScope();

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
   */
  void setTaskIdentifier();

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
   */
  void setRepetitionsTotal();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  // ElementTag
  bool m_descriptionIsSet;

  // ElementTag
  bool m_positiveEnergyDirectionIsSet;

  // ElementTag
  bool m_powerUnitIsSet;

  // ElementTag
  bool m_energyUnitIsSet;

  // ElementTag
  bool m_valueSourceIsSet;

  // ElementTag
  bool m_scopeIsSet;

  // ElementTag
  bool m_taskIdentifierIsSet;

  // ElementTag
  bool m_repetitionsTotalIsSet;
};

//! typedef for non-const smart pointer type
//! PowerSequenceDescriptionDataElements
using PowerSequenceDescriptionDataElementsPtr =
    std::shared_ptr<PowerSequenceDescriptionDataElements>;

//! typedef for const type PowerSequenceDescriptionDataElements
using PowerSequenceDescriptionDataElementsConst =
    const PowerSequenceDescriptionDataElements;

//! typedef for const type PowerSequenceDescriptionDataElements
using PowerSequenceDescriptionDataElementsConstPtr =
    std::shared_ptr<PowerSequenceDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEDESCRIPTIONDATAELEMENTS_H_