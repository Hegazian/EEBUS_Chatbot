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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFTIERRELATIONLISTDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFTIERRELATIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TariffTierRelationData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffTierRelationListData
 */
class TariffTierRelationListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TariffTierRelationListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_tariffTierRelationData the member to set
   */
  explicit TariffTierRelationListData(
      const std::vector<TariffTierRelationData> &c_tariffTierRelationData);

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
  bool operator==(const TariffTierRelationListData &c_classObject) const;

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
  bool operator!=(const TariffTierRelationListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member TariffTierRelationData.
   * @param c_tariffTierRelationData Value to set
   */
  void setTariffTierRelationData(
      const std::vector<TariffTierRelationData> &c_tariffTierRelationData);

  /**
   * Returns const reference to member TariffTierRelationData.
   * @return const reference to member tariffTierRelationData
   */
  const std::vector<TariffTierRelationData> &getTariffTierRelationData() const;

  /**
   * Returns if member TariffTierRelationData is set.
   * @retval true member TariffTierRelationData is set
   * @retval false member TariffTierRelationData is not set
   */
  bool getTariffTierRelationDataIsSet() const;

  /**
   * Unsets member TariffTierRelationData
   */
  void cleanTariffTierRelationData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffTierRelationDataIsSet;
  std::vector<TariffTierRelationData> m_tariffTierRelationData;
};

//! typedef for non-const smart pointer type TariffTierRelationListData
using TariffTierRelationListDataPtr =
    std::shared_ptr<TariffTierRelationListData>;

//! typedef for const type TariffTierRelationListData
using TariffTierRelationListDataConst = const TariffTierRelationListData;

//! typedef for const type TariffTierRelationListData
using TariffTierRelationListDataConstPtr =
    std::shared_ptr<TariffTierRelationListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFTIERRELATIONLISTDATA_H_