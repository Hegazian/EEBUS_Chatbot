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

#ifndef KEO_DATAGRAM_SENSING_SENSINGDATA_H_
#define KEO_DATAGRAM_SENSING_SENSINGDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/AbsoluteOrRelativeTime.h>
#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumber.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/sensing/SensingDataElements.h>
#include <keo_datagram/sensing/SensingState.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSensing
 * @{
 */

/**
 * Declaration SensingData
 */
class SensingData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  SensingData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timestamp the member to set
   * @param c_state the member to set
   * @param c_value the member to set
   */
  SensingData(const AbsoluteOrRelativeTime &c_timestamp,
              const SensingState &c_state, const ScaledNumber &c_value);

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
  bool operator==(const SensingData &c_classObject) const;

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
  bool operator!=(const SensingData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member Timestamp.
   * @param c_timestamp Value to set
   */
  void setTimestamp(const AbsoluteOrRelativeTime &c_timestamp);

  /**
   * Returns const reference to member Timestamp.
   * @return const reference to member timestamp
   */
  const AbsoluteOrRelativeTime &getTimestamp() const;

  /**
   * Returns if member Timestamp is set.
   * @retval true member Timestamp is set
   * @retval false member Timestamp is not set
   */
  bool getTimestampIsSet() const;

  /**
   * Unsets member Timestamp
   */
  void cleanTimestamp();

  /**
   * Set member State.
   * @param c_state Value to set
   */
  void setState(const SensingState &c_state);

  /**
   * Returns const reference to member State.
   * @return const reference to member state
   */
  const SensingState &getState() const;

  /**
   * Returns if member State is set.
   * @retval true member State is set
   * @retval false member State is not set
   */
  bool getStateIsSet() const;

  /**
   * Unsets member State
   */
  void cleanState();

  /**
   * Set member Value.
   * @param c_value Value to set
   */
  void setValue(const ScaledNumber &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumber &getValue() const;

  /**
   * Returns if member Value is set.
   * @retval true member Value is set
   * @retval false member Value is not set
   */
  bool getValueIsSet() const;

  /**
   * Unsets member Value
   */
  void cleanValue();

  /**
   * @copydoc CmdData::reduce()
   */
  SensingData reduce(const SensingDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_timestampIsSet;
  AbsoluteOrRelativeTime m_timestamp;

  bool m_stateIsSet;
  SensingState m_state;

  bool m_valueIsSet;
  ScaledNumber m_value;
};

//! typedef for non-const smart pointer type SensingData
using SensingDataPtr = std::shared_ptr<SensingData>;

//! typedef for const type SensingData
using SensingDataConst = const SensingData;

//! typedef for const type SensingData
using SensingDataConstPtr = std::shared_ptr<SensingDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SENSING_SENSINGDATA_H_