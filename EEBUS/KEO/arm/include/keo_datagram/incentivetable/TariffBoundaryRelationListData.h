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

#ifndef KEO_DATAGRAM_INCENTIVETABLE_TARIFFBOUNDARYRELATIONLISTDATA_H_
#define KEO_DATAGRAM_INCENTIVETABLE_TARIFFBOUNDARYRELATIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/incentivetable/TariffBoundaryRelationData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIncentiveTable
 * @{
 */

/**
 * Declaration TariffBoundaryRelationListData
 */
class TariffBoundaryRelationListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  TariffBoundaryRelationListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_tariffBoundaryRelationData the member to set
   */
  explicit TariffBoundaryRelationListData(
      const std::vector<TariffBoundaryRelationData>
          &c_tariffBoundaryRelationData);

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
  bool operator==(const TariffBoundaryRelationListData &c_classObject) const;

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
  bool operator!=(const TariffBoundaryRelationListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member TariffBoundaryRelationData.
   * @param c_tariffBoundaryRelationData Value to set
   */
  void
  setTariffBoundaryRelationData(const std::vector<TariffBoundaryRelationData>
                                    &c_tariffBoundaryRelationData);

  /**
   * Returns const reference to member TariffBoundaryRelationData.
   * @return const reference to member tariffBoundaryRelationData
   */
  const std::vector<TariffBoundaryRelationData> &
  getTariffBoundaryRelationData() const;

  /**
   * Returns if member TariffBoundaryRelationData is set.
   * @retval true member TariffBoundaryRelationData is set
   * @retval false member TariffBoundaryRelationData is not set
   */
  bool getTariffBoundaryRelationDataIsSet() const;

  /**
   * Unsets member TariffBoundaryRelationData
   */
  void cleanTariffBoundaryRelationData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_tariffBoundaryRelationDataIsSet;
  std::vector<TariffBoundaryRelationData> m_tariffBoundaryRelationData;
};

//! typedef for non-const smart pointer type TariffBoundaryRelationListData
using TariffBoundaryRelationListDataPtr =
    std::shared_ptr<TariffBoundaryRelationListData>;

//! typedef for const type TariffBoundaryRelationListData
using TariffBoundaryRelationListDataConst =
    const TariffBoundaryRelationListData;

//! typedef for const type TariffBoundaryRelationListData
using TariffBoundaryRelationListDataConstPtr =
    std::shared_ptr<TariffBoundaryRelationListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_INCENTIVETABLE_TARIFFBOUNDARYRELATIONLISTDATA_H_