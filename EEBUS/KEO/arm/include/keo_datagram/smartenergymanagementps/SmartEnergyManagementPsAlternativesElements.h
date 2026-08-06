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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSALTERNATIVESELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSALTERNATIVESELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesRelationElements.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsPowerSequenceElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsAlternativesElements
 */
class SmartEnergyManagementPsAlternativesElements
    : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsAlternativesElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_relation the member to set
   * @param c_powerSequence the member to set
   */
  SmartEnergyManagementPsAlternativesElements(
      const SmartEnergyManagementPsAlternativesRelationElements &c_relation,
      const SmartEnergyManagementPsPowerSequenceElements &c_powerSequence);

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
      const SmartEnergyManagementPsAlternativesElements &c_classObject) const;

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
      const SmartEnergyManagementPsAlternativesElements &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Relation.
   * @param c_relation Value to set
   */
  void setRelation(
      const SmartEnergyManagementPsAlternativesRelationElements &c_relation);

  /**
   * Returns const reference to member Relation.
   * @return const reference to member relation
   */
  const SmartEnergyManagementPsAlternativesRelationElements &
  getRelation() const;

  /**
   * Returns if member Relation is set.
   * @retval true member Relation is set
   * @retval false member Relation is not set
   */
  bool getRelationIsSet() const;

  /**
   * Unsets member Relation
   */
  void cleanRelation();

  /**
   * Set member PowerSequence.
   * @param c_powerSequence Value to set
   */
  void setPowerSequence(
      const SmartEnergyManagementPsPowerSequenceElements &c_powerSequence);

  /**
   * Returns const reference to member PowerSequence.
   * @return const reference to member powerSequence
   */
  const SmartEnergyManagementPsPowerSequenceElements &getPowerSequence() const;

  /**
   * Returns if member PowerSequence is set.
   * @retval true member PowerSequence is set
   * @retval false member PowerSequence is not set
   */
  bool getPowerSequenceIsSet() const;

  /**
   * Unsets member PowerSequence
   */
  void cleanPowerSequence();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_relationIsSet;
  SmartEnergyManagementPsAlternativesRelationElements m_relation;

  bool m_powerSequenceIsSet;
  SmartEnergyManagementPsPowerSequenceElements m_powerSequence;
};

//! typedef for non-const smart pointer type
//! SmartEnergyManagementPsAlternativesElements
using SmartEnergyManagementPsAlternativesElementsPtr =
    std::shared_ptr<SmartEnergyManagementPsAlternativesElements>;

//! typedef for const type SmartEnergyManagementPsAlternativesElements
using SmartEnergyManagementPsAlternativesElementsConst =
    const SmartEnergyManagementPsAlternativesElements;

//! typedef for const type SmartEnergyManagementPsAlternativesElements
using SmartEnergyManagementPsAlternativesElementsConstPtr =
    std::shared_ptr<SmartEnergyManagementPsAlternativesElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSALTERNATIVESELEMENTS_H_