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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATAELEMENTS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationDataElements.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternativesElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsDataElements
 */
class SmartEnergyManagementPsDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_nodeScheduleInformation the member to set
   * @param c_alternatives the member to set
   */
  SmartEnergyManagementPsDataElements(
      const PowerSequenceNodeScheduleInformationDataElements
          &c_nodeScheduleInformation,
      const SmartEnergyManagementPsAlternativesElements &c_alternatives);

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
  operator==(const SmartEnergyManagementPsDataElements &c_classObject) const;

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
  operator!=(const SmartEnergyManagementPsDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member NodeScheduleInformation.
   * @param c_nodeScheduleInformation Value to set
   */
  void setNodeScheduleInformation(
      const PowerSequenceNodeScheduleInformationDataElements
          &c_nodeScheduleInformation);

  /**
   * Returns const reference to member NodeScheduleInformation.
   * @return const reference to member nodeScheduleInformation
   */
  const PowerSequenceNodeScheduleInformationDataElements &
  getNodeScheduleInformation() const;

  /**
   * Returns if member NodeScheduleInformation is set.
   * @retval true member NodeScheduleInformation is set
   * @retval false member NodeScheduleInformation is not set
   */
  bool getNodeScheduleInformationIsSet() const;

  /**
   * Unsets member NodeScheduleInformation
   */
  void cleanNodeScheduleInformation();

  /**
   * Set member Alternatives.
   * @param c_alternatives Value to set
   */
  void setAlternatives(
      const SmartEnergyManagementPsAlternativesElements &c_alternatives);

  /**
   * Returns const reference to member Alternatives.
   * @return const reference to member alternatives
   */
  const SmartEnergyManagementPsAlternativesElements &getAlternatives() const;

  /**
   * Returns if member Alternatives is set.
   * @retval true member Alternatives is set
   * @retval false member Alternatives is not set
   */
  bool getAlternativesIsSet() const;

  /**
   * Unsets member Alternatives
   */
  void cleanAlternatives();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_nodeScheduleInformationIsSet;
  PowerSequenceNodeScheduleInformationDataElements m_nodeScheduleInformation;

  bool m_alternativesIsSet;
  SmartEnergyManagementPsAlternativesElements m_alternatives;
};

//! typedef for non-const smart pointer type SmartEnergyManagementPsDataElements
using SmartEnergyManagementPsDataElementsPtr =
    std::shared_ptr<SmartEnergyManagementPsDataElements>;

//! typedef for const type SmartEnergyManagementPsDataElements
using SmartEnergyManagementPsDataElementsConst =
    const SmartEnergyManagementPsDataElements;

//! typedef for const type SmartEnergyManagementPsDataElements
using SmartEnergyManagementPsDataElementsConstPtr =
    std::shared_ptr<SmartEnergyManagementPsDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATAELEMENTS_H_