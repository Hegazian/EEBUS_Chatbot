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

#ifndef KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONSETPOINTRELATIONDATA_H_
#define KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONSETPOINTRELATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacSystemFunctionSetpointRelationData
 */
class HvacSystemFunctionSetpointRelationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  HvacSystemFunctionSetpointRelationData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_systemFunctionId the member to set
   * @param c_operationModeId the member to set
   * @param c_setpointId the member to set
   */
  HvacSystemFunctionSetpointRelationData(
      const xs_unsignedInt &c_systemFunctionId,
      const xs_unsignedInt &c_operationModeId,
      const std::vector<xs_unsignedInt> &c_setpointId);

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
  operator==(const HvacSystemFunctionSetpointRelationData &c_classObject) const;

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
  operator!=(const HvacSystemFunctionSetpointRelationData &c_classObject) const;

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
   * Set member OperationModeId.
   * @param c_operationModeId Value to set
   */
  void setOperationModeId(const xs_unsignedInt &c_operationModeId);

  /**
   * Returns const reference to member OperationModeId.
   * @return const reference to member operationModeId
   */
  const xs_unsignedInt &getOperationModeId() const;

  /**
   * Returns if member OperationModeId is set.
   * @retval true member OperationModeId is set
   * @retval false member OperationModeId is not set
   */
  bool getOperationModeIdIsSet() const;

  /**
   * Unsets member OperationModeId
   */
  void cleanOperationModeId();

  /**
   * Set member SetpointId.
   * @param c_setpointId Value to set
   */
  void setSetpointId(const std::vector<xs_unsignedInt> &c_setpointId);

  /**
   * Returns const reference to member SetpointId.
   * @return const reference to member setpointId
   */
  const std::vector<xs_unsignedInt> &getSetpointId() const;

  /**
   * Returns if member SetpointId is set.
   * @retval true member SetpointId is set
   * @retval false member SetpointId is not set
   */
  bool getSetpointIdIsSet() const;

  /**
   * Unsets member SetpointId
   */
  void cleanSetpointId();

  /**
   * @copydoc CmdData::reduce()
   */
  HvacSystemFunctionSetpointRelationData
  reduce(const HvacSystemFunctionSetpointRelationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_systemFunctionIdIsSet;
  xs_unsignedInt m_systemFunctionId;

  bool m_operationModeIdIsSet;
  xs_unsignedInt m_operationModeId;

  bool m_setpointIdIsSet;
  std::vector<xs_unsignedInt> m_setpointId;
};

//! typedef for non-const smart pointer type
//! HvacSystemFunctionSetpointRelationData
using HvacSystemFunctionSetpointRelationDataPtr =
    std::shared_ptr<HvacSystemFunctionSetpointRelationData>;

//! typedef for const type HvacSystemFunctionSetpointRelationData
using HvacSystemFunctionSetpointRelationDataConst =
    const HvacSystemFunctionSetpointRelationData;

//! typedef for const type HvacSystemFunctionSetpointRelationData
using HvacSystemFunctionSetpointRelationDataConstPtr =
    std::shared_ptr<HvacSystemFunctionSetpointRelationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONSETPOINTRELATIONDATA_H_