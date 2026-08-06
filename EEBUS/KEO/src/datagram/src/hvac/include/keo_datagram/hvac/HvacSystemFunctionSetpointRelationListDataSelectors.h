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

#ifndef KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONSETPOINTRELATIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONSETPOINTRELATIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/hvac/HvacSystemFunctionSetpointRelationData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacSystemFunctionSetpointRelationListDataSelectors
 */
class HvacSystemFunctionSetpointRelationListDataSelectors
    : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  HvacSystemFunctionSetpointRelationListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_systemFunctionId the member to set
   * @param c_operationModeId the member to set
   */
  HvacSystemFunctionSetpointRelationListDataSelectors(
      const xs_unsignedInt &c_systemFunctionId,
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
  bool operator==(const HvacSystemFunctionSetpointRelationListDataSelectors
                      &c_classObject) const;

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
  bool operator!=(const HvacSystemFunctionSetpointRelationListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const HvacSystemFunctionSetpointRelationData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_systemFunctionIdIsSet;
  xs_unsignedInt m_systemFunctionId;

  bool m_operationModeIdIsSet;
  xs_unsignedInt m_operationModeId;
};

//! typedef for non-const smart pointer type
//! HvacSystemFunctionSetpointRelationListDataSelectors
using HvacSystemFunctionSetpointRelationListDataSelectorsPtr =
    std::shared_ptr<HvacSystemFunctionSetpointRelationListDataSelectors>;

//! typedef for const type HvacSystemFunctionSetpointRelationListDataSelectors
using HvacSystemFunctionSetpointRelationListDataSelectorsConst =
    const HvacSystemFunctionSetpointRelationListDataSelectors;

//! typedef for const type HvacSystemFunctionSetpointRelationListDataSelectors
using HvacSystemFunctionSetpointRelationListDataSelectorsConstPtr =
    std::shared_ptr<HvacSystemFunctionSetpointRelationListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONSETPOINTRELATIONLISTDATASELECTORS_H_