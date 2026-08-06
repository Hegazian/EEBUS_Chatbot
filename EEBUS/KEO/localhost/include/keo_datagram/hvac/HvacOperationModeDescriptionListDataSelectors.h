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

#ifndef KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/hvac/HvacOperationModeDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOperationModeDescriptionListDataSelectors
 */
class HvacOperationModeDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  HvacOperationModeDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_operationModeId the member to set
   */
  explicit HvacOperationModeDescriptionListDataSelectors(
      const xs_unsignedInt &c_operationModeId);

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
      const HvacOperationModeDescriptionListDataSelectors &c_classObject) const;

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
      const HvacOperationModeDescriptionListDataSelectors &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const HvacOperationModeDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_operationModeIdIsSet;
  xs_unsignedInt m_operationModeId;
};

//! typedef for non-const smart pointer type
//! HvacOperationModeDescriptionListDataSelectors
using HvacOperationModeDescriptionListDataSelectorsPtr =
    std::shared_ptr<HvacOperationModeDescriptionListDataSelectors>;

//! typedef for const type HvacOperationModeDescriptionListDataSelectors
using HvacOperationModeDescriptionListDataSelectorsConst =
    const HvacOperationModeDescriptionListDataSelectors;

//! typedef for const type HvacOperationModeDescriptionListDataSelectors
using HvacOperationModeDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<HvacOperationModeDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONLISTDATASELECTORS_H_