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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TIERLISTDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TIERLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TierData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TierListData
 */
class TierListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TierListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_tierData the member to set
   */
  explicit TierListData(const std::vector<TierData> &c_tierData);

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
  bool operator==(const TierListData &c_classObject) const;

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
  bool operator!=(const TierListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member TierData.
   * @param c_tierData Value to set
   */
  void setTierData(const std::vector<TierData> &c_tierData);

  /**
   * Returns const reference to member TierData.
   * @return const reference to member tierData
   */
  const std::vector<TierData> &getTierData() const;

  /**
   * Returns if member TierData is set.
   * @retval true member TierData is set
   * @retval false member TierData is not set
   */
  bool getTierDataIsSet() const;

  /**
   * Unsets member TierData
   */
  void cleanTierData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tierDataIsSet;
  std::vector<TierData> m_tierData;
};

//! typedef for non-const smart pointer type TierListData
using TierListDataPtr = std::shared_ptr<TierListData>;

//! typedef for const type TierListData
using TierListDataConst = const TierListData;

//! typedef for const type TierListData
using TierListDataConstPtr = std::shared_ptr<TierListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TIERLISTDATA_H_