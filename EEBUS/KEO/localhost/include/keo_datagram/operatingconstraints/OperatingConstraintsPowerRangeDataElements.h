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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERRANGEDATAELEMENTS_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERRANGEDATAELEMENTS_H_

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
 * Declaration OperatingConstraintsPowerRangeDataElements
 */
class OperatingConstraintsPowerRangeDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsPowerRangeDataElements();

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
      const OperatingConstraintsPowerRangeDataElements &c_classObject) const;

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
      const OperatingConstraintsPowerRangeDataElements &c_classObject) const;

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
   * Set member PowerMin.
   * @param c_powerMin Value to set
   */
  void setPowerMin(const ScaledNumberElements &c_powerMin);

  /**
   * Returns const reference to member PowerMin.
   * @return const reference to member powerMin
   */
  const ScaledNumberElements &getPowerMin() const;

  /**
   * Returns if member PowerMin is set.
   * @retval true member PowerMin is set
   * @retval false member PowerMin is not set
   */
  bool getPowerMinIsSet() const;

  /**
   * Unsets member PowerMin
   */
  void cleanPowerMin();

  /**
   * Set member PowerMax.
   * @param c_powerMax Value to set
   */
  void setPowerMax(const ScaledNumberElements &c_powerMax);

  /**
   * Returns const reference to member PowerMax.
   * @return const reference to member powerMax
   */
  const ScaledNumberElements &getPowerMax() const;

  /**
   * Returns if member PowerMax is set.
   * @retval true member PowerMax is set
   * @retval false member PowerMax is not set
   */
  bool getPowerMaxIsSet() const;

  /**
   * Unsets member PowerMax
   */
  void cleanPowerMax();

  /**
   * Set member EnergyMin.
   * @param c_energyMin Value to set
   */
  void setEnergyMin(const ScaledNumberElements &c_energyMin);

  /**
   * Returns const reference to member EnergyMin.
   * @return const reference to member energyMin
   */
  const ScaledNumberElements &getEnergyMin() const;

  /**
   * Returns if member EnergyMin is set.
   * @retval true member EnergyMin is set
   * @retval false member EnergyMin is not set
   */
  bool getEnergyMinIsSet() const;

  /**
   * Unsets member EnergyMin
   */
  void cleanEnergyMin();

  /**
   * Set member EnergyMax.
   * @param c_energyMax Value to set
   */
  void setEnergyMax(const ScaledNumberElements &c_energyMax);

  /**
   * Returns const reference to member EnergyMax.
   * @return const reference to member energyMax
   */
  const ScaledNumberElements &getEnergyMax() const;

  /**
   * Returns if member EnergyMax is set.
   * @retval true member EnergyMax is set
   * @retval false member EnergyMax is not set
   */
  bool getEnergyMaxIsSet() const;

  /**
   * Unsets member EnergyMax
   */
  void cleanEnergyMax();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_sequenceIdIsSet;

  bool m_powerMinIsSet;
  ScaledNumberElements m_powerMin;

  bool m_powerMaxIsSet;
  ScaledNumberElements m_powerMax;

  bool m_energyMinIsSet;
  ScaledNumberElements m_energyMin;

  bool m_energyMaxIsSet;
  ScaledNumberElements m_energyMax;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsPowerRangeDataElements
using OperatingConstraintsPowerRangeDataElementsPtr =
    std::shared_ptr<OperatingConstraintsPowerRangeDataElements>;

//! typedef for const type OperatingConstraintsPowerRangeDataElements
using OperatingConstraintsPowerRangeDataElementsConst =
    const OperatingConstraintsPowerRangeDataElements;

//! typedef for const type OperatingConstraintsPowerRangeDataElements
using OperatingConstraintsPowerRangeDataElementsConstPtr =
    std::shared_ptr<OperatingConstraintsPowerRangeDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERRANGEDATAELEMENTS_H_