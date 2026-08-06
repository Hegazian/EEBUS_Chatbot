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

#ifndef KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONLISTDATA_H_
#define KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONLISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/identification/IdentificationData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramIdentification
 * @{
 */

/**
 * Declaration IdentificationListData
 */
class IdentificationListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  IdentificationListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_identificationData the member to set
   */
  explicit IdentificationListData(
      const std::vector<IdentificationData> &c_identificationData);

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
  bool operator==(const IdentificationListData &c_classObject) const;

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
  bool operator!=(const IdentificationListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member IdentificationData.
   * @param c_identificationData Value to set
   */
  void setIdentificationData(
      const std::vector<IdentificationData> &c_identificationData);

  /**
   * Returns const reference to member IdentificationData.
   * @return const reference to member identificationData
   */
  const std::vector<IdentificationData> &getIdentificationData() const;

  /**
   * Returns if member IdentificationData is set.
   * @retval true member IdentificationData is set
   * @retval false member IdentificationData is not set
   */
  bool getIdentificationDataIsSet() const;

  /**
   * Unsets member IdentificationData
   */
  void cleanIdentificationData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_identificationDataIsSet;
  std::vector<IdentificationData> m_identificationData;
};

//! typedef for non-const smart pointer type IdentificationListData
using IdentificationListDataPtr = std::shared_ptr<IdentificationListData>;

//! typedef for const type IdentificationListData
using IdentificationListDataConst = const IdentificationListData;

//! typedef for const type IdentificationListData
using IdentificationListDataConstPtr =
    std::shared_ptr<IdentificationListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_IDENTIFICATION_IDENTIFICATIONLISTDATA_H_