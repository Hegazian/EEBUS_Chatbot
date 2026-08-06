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

#ifndef KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERDESCRIPTIONLISTDATA_H_
#define KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERDESCRIPTIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/operatingconstraints/OperatingConstraintsPowerDescriptionData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramOperatingConstraints
 * @{
 */

/**
 * Declaration OperatingConstraintsPowerDescriptionListData
 */
class OperatingConstraintsPowerDescriptionListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  OperatingConstraintsPowerDescriptionListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_operatingConstraintsPowerDescriptionData the member to set
   */
  explicit OperatingConstraintsPowerDescriptionListData(
      const std::vector<OperatingConstraintsPowerDescriptionData>
          &c_operatingConstraintsPowerDescriptionData);

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
      const OperatingConstraintsPowerDescriptionListData &c_classObject) const;

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
      const OperatingConstraintsPowerDescriptionListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member OperatingConstraintsPowerDescriptionData.
   * @param c_operatingConstraintsPowerDescriptionData Value to set
   */
  void setOperatingConstraintsPowerDescriptionData(
      const std::vector<OperatingConstraintsPowerDescriptionData>
          &c_operatingConstraintsPowerDescriptionData);

  /**
   * Returns const reference to member OperatingConstraintsPowerDescriptionData.
   * @return const reference to member operatingConstraintsPowerDescriptionData
   */
  const std::vector<OperatingConstraintsPowerDescriptionData> &
  getOperatingConstraintsPowerDescriptionData() const;

  /**
   * Returns if member OperatingConstraintsPowerDescriptionData is set.
   * @retval true member OperatingConstraintsPowerDescriptionData is set
   * @retval false member OperatingConstraintsPowerDescriptionData is not set
   */
  bool getOperatingConstraintsPowerDescriptionDataIsSet() const;

  /**
   * Unsets member OperatingConstraintsPowerDescriptionData
   */
  void cleanOperatingConstraintsPowerDescriptionData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_operatingConstraintsPowerDescriptionDataIsSet;
  std::vector<OperatingConstraintsPowerDescriptionData>
      m_operatingConstraintsPowerDescriptionData;
};

//! typedef for non-const smart pointer type
//! OperatingConstraintsPowerDescriptionListData
using OperatingConstraintsPowerDescriptionListDataPtr =
    std::shared_ptr<OperatingConstraintsPowerDescriptionListData>;

//! typedef for const type OperatingConstraintsPowerDescriptionListData
using OperatingConstraintsPowerDescriptionListDataConst =
    const OperatingConstraintsPowerDescriptionListData;

//! typedef for const type OperatingConstraintsPowerDescriptionListData
using OperatingConstraintsPowerDescriptionListDataConstPtr =
    std::shared_ptr<OperatingConstraintsPowerDescriptionListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_OPERATINGCONSTRAINTS_OPERATINGCONSTRAINTSPOWERDESCRIPTIONLISTDATA_H_