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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerSequenceNodeScheduleInformationData.h>
#include <keo_datagram/smartenergymanagementps/SmartEnergyManagementPsAlternatives.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration SmartEnergyManagementPsData
 */
class SmartEnergyManagementPsData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  SmartEnergyManagementPsData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_nodeScheduleInformation the member to set
   * @param c_alternatives the member to set
   */
  SmartEnergyManagementPsData(
      const PowerSequenceNodeScheduleInformationData &c_nodeScheduleInformation,
      const std::vector<SmartEnergyManagementPsAlternatives> &c_alternatives);

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
  bool operator==(const SmartEnergyManagementPsData &c_classObject) const;

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
  bool operator!=(const SmartEnergyManagementPsData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member NodeScheduleInformation.
   * @param c_nodeScheduleInformation Value to set
   */
  void setNodeScheduleInformation(const PowerSequenceNodeScheduleInformationData
                                      &c_nodeScheduleInformation);

  /**
   * Returns const reference to member NodeScheduleInformation.
   * @return const reference to member nodeScheduleInformation
   */
  const PowerSequenceNodeScheduleInformationData &
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
      const std::vector<SmartEnergyManagementPsAlternatives> &c_alternatives);

  /**
   * Returns const reference to member Alternatives.
   * @return const reference to member alternatives
   */
  const std::vector<SmartEnergyManagementPsAlternatives> &
  getAlternatives() const;

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_nodeScheduleInformationIsSet;
  PowerSequenceNodeScheduleInformationData m_nodeScheduleInformation;

  bool m_alternativesIsSet;
  std::vector<SmartEnergyManagementPsAlternatives> m_alternatives;
};

//! typedef for non-const smart pointer type SmartEnergyManagementPsData
using SmartEnergyManagementPsDataPtr =
    std::shared_ptr<SmartEnergyManagementPsData>;

//! typedef for const type SmartEnergyManagementPsData
using SmartEnergyManagementPsDataConst = const SmartEnergyManagementPsData;

//! typedef for const type SmartEnergyManagementPsData
using SmartEnergyManagementPsDataConstPtr =
    std::shared_ptr<SmartEnergyManagementPsDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_SMARTENERGYMANAGEMENTPSDATA_H_