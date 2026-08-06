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

#ifndef KEO_DATAGRAM_ACTUATOR_ACTUATORLEVELDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_ACTUATOR_ACTUATORLEVELDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/UnitOfMeasurement.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramActuator
 * @{
 */

/**
 * Declaration ActuatorLevelDescriptionData
 */
class ActuatorLevelDescriptionData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  ActuatorLevelDescriptionData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_label the member to set
   * @param c_description the member to set
   * @param c_levelDefaultUnit the member to set
   */
  ActuatorLevelDescriptionData(const xs_string &c_label,
                               const xs_string &c_description,
                               const UnitOfMeasurement &c_levelDefaultUnit);

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
  bool operator==(const ActuatorLevelDescriptionData &c_classObject) const;

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
  bool operator!=(const ActuatorLevelDescriptionData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member Label.
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

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
   * Set member LevelDefaultUnit.
   * @param c_levelDefaultUnit Value to set
   */
  void setLevelDefaultUnit(const UnitOfMeasurement &c_levelDefaultUnit);

  /**
   * Returns const reference to member LevelDefaultUnit.
   * @return const reference to member levelDefaultUnit
   */
  const UnitOfMeasurement &getLevelDefaultUnit() const;

  /**
   * Returns if member LevelDefaultUnit is set.
   * @retval true member LevelDefaultUnit is set
   * @retval false member LevelDefaultUnit is not set
   */
  bool getLevelDefaultUnitIsSet() const;

  /**
   * Unsets member LevelDefaultUnit
   */
  void cleanLevelDefaultUnit();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;

  bool m_levelDefaultUnitIsSet;
  UnitOfMeasurement m_levelDefaultUnit;
};

//! typedef for non-const smart pointer type ActuatorLevelDescriptionData
using ActuatorLevelDescriptionDataPtr =
    std::shared_ptr<ActuatorLevelDescriptionData>;

//! typedef for const type ActuatorLevelDescriptionData
using ActuatorLevelDescriptionDataConst = const ActuatorLevelDescriptionData;

//! typedef for const type ActuatorLevelDescriptionData
using ActuatorLevelDescriptionDataConstPtr =
    std::shared_ptr<ActuatorLevelDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ACTUATOR_ACTUATORLEVELDESCRIPTIONDATA_H_