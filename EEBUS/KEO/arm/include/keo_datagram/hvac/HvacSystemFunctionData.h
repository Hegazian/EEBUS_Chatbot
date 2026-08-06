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

#ifndef KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDATA_H_
#define KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacSystemFunctionDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacSystemFunctionData
 */
class HvacSystemFunctionData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  HvacSystemFunctionData();

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
  bool operator==(const HvacSystemFunctionData &c_classObject) const;

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
  bool operator!=(const HvacSystemFunctionData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member SystemFunctionId.
   * @param c_systemFunctionId Value to set
   */
  void setSystemFunctionId(const xs_unsignedInt &c_systemFunctionId);

  /**
   * Returns const reference to member SystemFunctionId.
   * @return const reference to member systemFunctionId
   */
  const xs_unsignedInt &getSystemFunctionId() const;

  /**
   * Returns if member SystemFunctionId is set.
   * @retval true member SystemFunctionId is set
   * @retval false member SystemFunctionId is not set
   */
  bool getSystemFunctionIdIsSet() const;

  /**
   * Unsets member SystemFunctionId
   */
  void cleanSystemFunctionId();

  /**
   * Set member CurrentOperationModeId.
   * @param c_currentOperationModeId Value to set
   */
  void
  setCurrentOperationModeId(const xs_unsignedInt &c_currentOperationModeId);

  /**
   * Returns const reference to member CurrentOperationModeId.
   * @return const reference to member currentOperationModeId
   */
  const xs_unsignedInt &getCurrentOperationModeId() const;

  /**
   * Returns if member CurrentOperationModeId is set.
   * @retval true member CurrentOperationModeId is set
   * @retval false member CurrentOperationModeId is not set
   */
  bool getCurrentOperationModeIdIsSet() const;

  /**
   * Unsets member CurrentOperationModeId
   */
  void cleanCurrentOperationModeId();

  /**
   * Set member IsOperationModeIdChangeable.
   * @param c_isOperationModeIdChangeable Value to set
   */
  void setIsOperationModeIdChangeable(
      const xs_boolean &c_isOperationModeIdChangeable);

  /**
   * Returns const reference to member IsOperationModeIdChangeable.
   * @return const reference to member isOperationModeIdChangeable
   */
  const xs_boolean &getIsOperationModeIdChangeable() const;

  /**
   * Returns if member IsOperationModeIdChangeable is set.
   * @retval true member IsOperationModeIdChangeable is set
   * @retval false member IsOperationModeIdChangeable is not set
   */
  bool getIsOperationModeIdChangeableIsSet() const;

  /**
   * Unsets member IsOperationModeIdChangeable
   */
  void cleanIsOperationModeIdChangeable();

  /**
   * Set member CurrentSetpointId.
   * @param c_currentSetpointId Value to set
   */
  void setCurrentSetpointId(const xs_unsignedInt &c_currentSetpointId);

  /**
   * Returns const reference to member CurrentSetpointId.
   * @return const reference to member currentSetpointId
   */
  const xs_unsignedInt &getCurrentSetpointId() const;

  /**
   * Returns if member CurrentSetpointId is set.
   * @retval true member CurrentSetpointId is set
   * @retval false member CurrentSetpointId is not set
   */
  bool getCurrentSetpointIdIsSet() const;

  /**
   * Unsets member CurrentSetpointId
   */
  void cleanCurrentSetpointId();

  /**
   * Set member IsSetpointIdChangeable.
   * @param c_isSetpointIdChangeable Value to set
   */
  void setIsSetpointIdChangeable(const xs_boolean &c_isSetpointIdChangeable);

  /**
   * Returns const reference to member IsSetpointIdChangeable.
   * @return const reference to member isSetpointIdChangeable
   */
  const xs_boolean &getIsSetpointIdChangeable() const;

  /**
   * Returns if member IsSetpointIdChangeable is set.
   * @retval true member IsSetpointIdChangeable is set
   * @retval false member IsSetpointIdChangeable is not set
   */
  bool getIsSetpointIdChangeableIsSet() const;

  /**
   * Unsets member IsSetpointIdChangeable
   */
  void cleanIsSetpointIdChangeable();

  /**
   * Set member IsOverrunActive.
   * @param c_isOverrunActive Value to set
   */
  void setIsOverrunActive(const xs_boolean &c_isOverrunActive);

  /**
   * Returns const reference to member IsOverrunActive.
   * @return const reference to member isOverrunActive
   */
  const xs_boolean &getIsOverrunActive() const;

  /**
   * Returns if member IsOverrunActive is set.
   * @retval true member IsOverrunActive is set
   * @retval false member IsOverrunActive is not set
   */
  bool getIsOverrunActiveIsSet() const;

  /**
   * Unsets member IsOverrunActive
   */
  void cleanIsOverrunActive();

  /**
   * @copydoc CmdData::reduce()
   */
  HvacSystemFunctionData
  reduce(const HvacSystemFunctionDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_systemFunctionIdIsSet;
  xs_unsignedInt m_systemFunctionId;

  bool m_currentOperationModeIdIsSet;
  xs_unsignedInt m_currentOperationModeId;

  bool m_isOperationModeIdChangeableIsSet;
  xs_boolean m_isOperationModeIdChangeable;

  bool m_currentSetpointIdIsSet;
  xs_unsignedInt m_currentSetpointId;

  bool m_isSetpointIdChangeableIsSet;
  xs_boolean m_isSetpointIdChangeable;

  bool m_isOverrunActiveIsSet;
  xs_boolean m_isOverrunActive;
};

//! typedef for non-const smart pointer type HvacSystemFunctionData
using HvacSystemFunctionDataPtr = std::shared_ptr<HvacSystemFunctionData>;

//! typedef for const type HvacSystemFunctionData
using HvacSystemFunctionDataConst = const HvacSystemFunctionData;

//! typedef for const type HvacSystemFunctionData
using HvacSystemFunctionDataConstPtr =
    std::shared_ptr<HvacSystemFunctionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDATA_H_