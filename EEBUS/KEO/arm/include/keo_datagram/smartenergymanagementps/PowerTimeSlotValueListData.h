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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTVALUELISTDATA_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTVALUELISTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/smartenergymanagementps/PowerTimeSlotValueData.h>

#include <keo_datagram/core/Filter.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerTimeSlotValueListData
 */
class PowerTimeSlotValueListData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  PowerTimeSlotValueListData();

  /**
   * Construct an instance of this class and set its only member.
   * @param c_powerTimeSlotValueData the member to set
   */
  explicit PowerTimeSlotValueListData(
      const std::vector<PowerTimeSlotValueData> &c_powerTimeSlotValueData);

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
  bool operator==(const PowerTimeSlotValueListData &c_classObject) const;

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
  bool operator!=(const PowerTimeSlotValueListData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member PowerTimeSlotValueData.
   * @param c_powerTimeSlotValueData Value to set
   */
  void setPowerTimeSlotValueData(
      const std::vector<PowerTimeSlotValueData> &c_powerTimeSlotValueData);

  /**
   * Returns const reference to member PowerTimeSlotValueData.
   * @return const reference to member powerTimeSlotValueData
   */
  const std::vector<PowerTimeSlotValueData> &getPowerTimeSlotValueData() const;

  /**
   * Returns if member PowerTimeSlotValueData is set.
   * @retval true member PowerTimeSlotValueData is set
   * @retval false member PowerTimeSlotValueData is not set
   */
  bool getPowerTimeSlotValueDataIsSet() const;

  /**
   * Unsets member PowerTimeSlotValueData
   */
  void cleanPowerTimeSlotValueData();

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_powerTimeSlotValueDataIsSet;
  std::vector<PowerTimeSlotValueData> m_powerTimeSlotValueData;
};

//! typedef for non-const smart pointer type PowerTimeSlotValueListData
using PowerTimeSlotValueListDataPtr =
    std::shared_ptr<PowerTimeSlotValueListData>;

//! typedef for const type PowerTimeSlotValueListData
using PowerTimeSlotValueListDataConst = const PowerTimeSlotValueListData;

//! typedef for const type PowerTimeSlotValueListData
using PowerTimeSlotValueListDataConstPtr =
    std::shared_ptr<PowerTimeSlotValueListDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERTIMESLOTVALUELISTDATA_H_