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

#ifndef KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDESCRIPTIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDESCRIPTIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/hvac/HvacSystemFunctionDescriptionData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacSystemFunctionDescriptionListDataSelectors
 */
class HvacSystemFunctionDescriptionListDataSelectors : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  HvacSystemFunctionDescriptionListDataSelectors();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_systemFunctionId the member to set
   */
  explicit HvacSystemFunctionDescriptionListDataSelectors(
      const xs_unsignedInt &c_systemFunctionId);

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
  bool operator==(const HvacSystemFunctionDescriptionListDataSelectors
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
  bool operator!=(const HvacSystemFunctionDescriptionListDataSelectors
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
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const HvacSystemFunctionDescriptionData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_systemFunctionIdIsSet;
  xs_unsignedInt m_systemFunctionId;
};

//! typedef for non-const smart pointer type
//! HvacSystemFunctionDescriptionListDataSelectors
using HvacSystemFunctionDescriptionListDataSelectorsPtr =
    std::shared_ptr<HvacSystemFunctionDescriptionListDataSelectors>;

//! typedef for const type HvacSystemFunctionDescriptionListDataSelectors
using HvacSystemFunctionDescriptionListDataSelectorsConst =
    const HvacSystemFunctionDescriptionListDataSelectors;

//! typedef for const type HvacSystemFunctionDescriptionListDataSelectors
using HvacSystemFunctionDescriptionListDataSelectorsConstPtr =
    std::shared_ptr<HvacSystemFunctionDescriptionListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACSYSTEMFUNCTIONDESCRIPTIONLISTDATASELECTORS_H_