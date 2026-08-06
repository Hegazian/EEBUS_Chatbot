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

#ifndef KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONTHRESHOLDRELATIONLISTDATA_H_
#define KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONTHRESHOLDRELATIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/supplycondition/SupplyConditionThresholdRelationData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSupplyCondition
 * @{
 */

/**
 * Declaration SupplyConditionThresholdRelationListData
 */
class SupplyConditionThresholdRelationListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  SupplyConditionThresholdRelationListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_supplyConditionThresholdRelationData the member to set
   */
  explicit SupplyConditionThresholdRelationListData(
      const std::vector<SupplyConditionThresholdRelationData>
          &c_supplyConditionThresholdRelationData);

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
      const SupplyConditionThresholdRelationListData &c_classObject) const;

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
      const SupplyConditionThresholdRelationListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member SupplyConditionThresholdRelationData.
   * @param c_supplyConditionThresholdRelationData Value to set
   */
  void setSupplyConditionThresholdRelationData(
      const std::vector<SupplyConditionThresholdRelationData>
          &c_supplyConditionThresholdRelationData);

  /**
   * Returns const reference to member SupplyConditionThresholdRelationData.
   * @return const reference to member supplyConditionThresholdRelationData
   */
  const std::vector<SupplyConditionThresholdRelationData> &
  getSupplyConditionThresholdRelationData() const;

  /**
   * Returns if member SupplyConditionThresholdRelationData is set.
   * @retval true member SupplyConditionThresholdRelationData is set
   * @retval false member SupplyConditionThresholdRelationData is not set
   */
  bool getSupplyConditionThresholdRelationDataIsSet() const;

  /**
   * Unsets member SupplyConditionThresholdRelationData
   */
  void cleanSupplyConditionThresholdRelationData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_supplyConditionThresholdRelationDataIsSet;
  std::vector<SupplyConditionThresholdRelationData>
      m_supplyConditionThresholdRelationData;
};

//! typedef for non-const smart pointer type
//! SupplyConditionThresholdRelationListData
using SupplyConditionThresholdRelationListDataPtr =
    std::shared_ptr<SupplyConditionThresholdRelationListData>;

//! typedef for const type SupplyConditionThresholdRelationListData
using SupplyConditionThresholdRelationListDataConst =
    const SupplyConditionThresholdRelationListData;

//! typedef for const type SupplyConditionThresholdRelationListData
using SupplyConditionThresholdRelationListDataConstPtr =
    std::shared_ptr<SupplyConditionThresholdRelationListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SUPPLYCONDITION_SUPPLYCONDITIONTHRESHOLDRELATIONLISTDATA_H_