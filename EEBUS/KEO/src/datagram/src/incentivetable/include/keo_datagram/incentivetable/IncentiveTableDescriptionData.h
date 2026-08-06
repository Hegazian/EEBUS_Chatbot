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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/IncentiveTableDescription.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration IncentiveTableDescriptionData
 */
class IncentiveTableDescriptionData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  IncentiveTableDescriptionData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_incentiveTableDescription the member to set
   */
  explicit IncentiveTableDescriptionData(
      const std::vector<IncentiveTableDescription>
          &c_incentiveTableDescription);

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
  bool operator==(const IncentiveTableDescriptionData &c_classObject) const;

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
  bool operator!=(const IncentiveTableDescriptionData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member IncentiveTableDescription.
   * @param c_incentiveTableDescription Value to set
   */
  void setIncentiveTableDescription(const std::vector<IncentiveTableDescription>
                                        &c_incentiveTableDescription);

  /**
   * Returns const reference to member IncentiveTableDescription.
   * @return const reference to member incentiveTableDescription
   */
  const std::vector<IncentiveTableDescription> &
  getIncentiveTableDescription() const;

  /**
   * Returns if member IncentiveTableDescription is set.
   * @retval true member IncentiveTableDescription is set
   * @retval false member IncentiveTableDescription is not set
   */
  bool getIncentiveTableDescriptionIsSet() const;

  /**
   * Unsets member IncentiveTableDescription
   */
  void cleanIncentiveTableDescription();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_incentiveTableDescriptionIsSet;
  std::vector<IncentiveTableDescription> m_incentiveTableDescription;
};

//! typedef for non-const smart pointer type IncentiveTableDescriptionData
using IncentiveTableDescriptionDataPtr =
    std::shared_ptr<IncentiveTableDescriptionData>;

//! typedef for const type IncentiveTableDescriptionData
using IncentiveTableDescriptionDataConst = const IncentiveTableDescriptionData;

//! typedef for const type IncentiveTableDescriptionData
using IncentiveTableDescriptionDataConstPtr =
    std::shared_ptr<IncentiveTableDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_INCENTIVETABLEDESCRIPTIONDATA_H_