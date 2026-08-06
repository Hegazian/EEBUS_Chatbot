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

#ifndef KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONLISTDATA_H_
#define KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/hvac/HvacOperationModeDescriptionData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramHVAC
 * @{
 */

/**
 * Declaration HvacOperationModeDescriptionListData
 */
class HvacOperationModeDescriptionListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  HvacOperationModeDescriptionListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_hvacOperationModeDescriptionData the member to set
   */
  explicit HvacOperationModeDescriptionListData(
      const std::vector<HvacOperationModeDescriptionData>
          &c_hvacOperationModeDescriptionData);

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
  operator==(const HvacOperationModeDescriptionListData &c_classObject) const;

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
  operator!=(const HvacOperationModeDescriptionListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member HvacOperationModeDescriptionData.
   * @param c_hvacOperationModeDescriptionData Value to set
   */
  void setHvacOperationModeDescriptionData(
      const std::vector<HvacOperationModeDescriptionData>
          &c_hvacOperationModeDescriptionData);

  /**
   * Returns const reference to member HvacOperationModeDescriptionData.
   * @return const reference to member hvacOperationModeDescriptionData
   */
  const std::vector<HvacOperationModeDescriptionData> &
  getHvacOperationModeDescriptionData() const;

  /**
   * Returns if member HvacOperationModeDescriptionData is set.
   * @retval true member HvacOperationModeDescriptionData is set
   * @retval false member HvacOperationModeDescriptionData is not set
   */
  bool getHvacOperationModeDescriptionDataIsSet() const;

  /**
   * Unsets member HvacOperationModeDescriptionData
   */
  void cleanHvacOperationModeDescriptionData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_hvacOperationModeDescriptionDataIsSet;
  std::vector<HvacOperationModeDescriptionData>
      m_hvacOperationModeDescriptionData;
};

//! typedef for non-const smart pointer type
//! HvacOperationModeDescriptionListData
using HvacOperationModeDescriptionListDataPtr =
    std::shared_ptr<HvacOperationModeDescriptionListData>;

//! typedef for const type HvacOperationModeDescriptionListData
using HvacOperationModeDescriptionListDataConst =
    const HvacOperationModeDescriptionListData;

//! typedef for const type HvacOperationModeDescriptionListData
using HvacOperationModeDescriptionListDataConstPtr =
    std::shared_ptr<HvacOperationModeDescriptionListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_HVAC_HVACOPERATIONMODEDESCRIPTIONLISTDATA_H_