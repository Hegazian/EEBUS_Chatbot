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

#ifndef KEO_DATAGRAM_ACTUATOR_ACTUATORLEVELDATA_H_
#define KEO_DATAGRAM_ACTUATOR_ACTUATORLEVELDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/actuator/ActuatorLevelFct.h>
#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramActuator
 * @{
 */

/**
 * Declaration ActuatorLevelData
 */
class ActuatorLevelData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  ActuatorLevelData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_function the member to set
   * @param c_value the member to set
   */
  ActuatorLevelData(const ActuatorLevelFct &c_function,
                    const ScaledNumber &c_value);

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
  bool operator==(const ActuatorLevelData &c_classObject) const;

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
  bool operator!=(const ActuatorLevelData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member Function.
   * @param c_function Value to set
   */
  void setFunction(const ActuatorLevelFct &c_function);

  /**
   * Returns const reference to member Function.
   * @return const reference to member function
   */
  const ActuatorLevelFct &getFunction() const;

  /**
   * Returns if member Function is set.
   * @retval true member Function is set
   * @retval false member Function is not set
   */
  bool getFunctionIsSet() const;

  /**
   * Unsets member Function
   */
  void cleanFunction();

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumber &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumber &getValue() const;

  /**
   * Returns if member Value is set.
   * @retval true member Value is set
   * @retval false member Value is not set
   */
  bool getValueIsSet() const;

  /**
   * Unsets member Value
   */
  void cleanValue();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_functionIsSet;
  ActuatorLevelFct m_function;

  bool m_valueIsSet;
  ScaledNumber m_value;
};

//! typedef for non-const smart pointer type ActuatorLevelData
using ActuatorLevelDataPtr = std::shared_ptr<ActuatorLevelData>;

//! typedef for const type ActuatorLevelData
using ActuatorLevelDataConst = const ActuatorLevelData;

//! typedef for const type ActuatorLevelData
using ActuatorLevelDataConstPtr = std::shared_ptr<ActuatorLevelDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ACTUATOR_ACTUATORLEVELDATA_H_