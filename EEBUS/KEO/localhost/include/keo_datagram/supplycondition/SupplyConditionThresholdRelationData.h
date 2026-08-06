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

#ifndef KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONTHRESHOLDRELATIONDATA_H_
#define KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONTHRESHOLDRELATIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSupplyCondition
 * @{
 */

/**
 * Declaration SupplyConditionThresholdRelationData
 */
class SupplyConditionThresholdRelationData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SupplyConditionThresholdRelationData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_conditionId the member to set
   * @param c_thresholdId the member to set
   */
  SupplyConditionThresholdRelationData(
      const xs_unsignedInt &c_conditionId,
      const std::vector<xs_unsignedInt> &c_thresholdId);

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
  operator==(const SupplyConditionThresholdRelationData &c_classObject) const;

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
  operator!=(const SupplyConditionThresholdRelationData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member ConditionId.
   * @param c_conditionId Value to set
   */
  void setConditionId(const xs_unsignedInt &c_conditionId);

  /**
   * Returns const reference to member ConditionId.
   * @return const reference to member conditionId
   */
  const xs_unsignedInt &getConditionId() const;

  /**
   * Returns if member ConditionId is set.
   * @retval true member ConditionId is set
   * @retval false member ConditionId is not set
   */
  bool getConditionIdIsSet() const;

  /**
   * Unsets member ConditionId
   */
  void cleanConditionId();

  /**
   * Set member ThresholdId.
   * @param c_thresholdId Value to set
   */
  void setThresholdId(const std::vector<xs_unsignedInt> &c_thresholdId);

  /**
   * Returns const reference to member ThresholdId.
   * @return const reference to member thresholdId
   */
  const std::vector<xs_unsignedInt> &getThresholdId() const;

  /**
   * Returns if member ThresholdId is set.
   * @retval true member ThresholdId is set
   * @retval false member ThresholdId is not set
   */
  bool getThresholdIdIsSet() const;

  /**
   * Unsets member ThresholdId
   */
  void cleanThresholdId();

  /**
   * @copydoc CmdData::reduce()
   */
  SupplyConditionThresholdRelationData
  reduce(const SupplyConditionThresholdRelationDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_conditionIdIsSet;
  xs_unsignedInt m_conditionId;

  bool m_thresholdIdIsSet;
  std::vector<xs_unsignedInt> m_thresholdId;
};

//! typedef for non-const smart pointer type
//! SupplyConditionThresholdRelationData
using SupplyConditionThresholdRelationDataPtr =
    std::shared_ptr<SupplyConditionThresholdRelationData>;

//! typedef for const type SupplyConditionThresholdRelationData
using SupplyConditionThresholdRelationDataConst =
    const SupplyConditionThresholdRelationData;

//! typedef for const type SupplyConditionThresholdRelationData
using SupplyConditionThresholdRelationDataConstPtr =
    std::shared_ptr<SupplyConditionThresholdRelationDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONTHRESHOLDRELATIONDATA_H_