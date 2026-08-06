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

#ifndef KEO_DATAGRAM_SENSING_SENSINGDATAELEMENTS_H_
#define KEO_DATAGRAM_SENSING_SENSINGDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSensing
 * @{
 */

/**
 * Declaration SensingDataElements
 */
class SensingDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  SensingDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_timestampIsSet the member to set
   * @param c_stateIsSet the member to set
   * @param c_value the member to set
   */
  SensingDataElements(xs_boolean c_timestampIsSet, xs_boolean c_stateIsSet,
                      const ScaledNumberElements &c_value);

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
  bool operator==(const SensingDataElements &c_classObject) const;

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
  bool operator!=(const SensingDataElements &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member Timestamp.
   */
  void setTimestamp();

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
   */
  void setState();

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
  void setValue(const ScaledNumberElements &c_value);

  /**
   * Returns const reference to member Value.
   * @return const reference to member value
   */
  const ScaledNumberElements &getValue() const;

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_timestampIsSet;

  // ElementTag
  bool m_stateIsSet;

  bool m_valueIsSet;
  ScaledNumberElements m_value;
};

//! typedef for non-const smart pointer type SensingDataElements
using SensingDataElementsPtr = std::shared_ptr<SensingDataElements>;

//! typedef for const type SensingDataElements
using SensingDataElementsConst = const SensingDataElements;

//! typedef for const type SensingDataElements
using SensingDataElementsConstPtr = std::shared_ptr<SensingDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SENSING_SENSINGDATAELEMENTS_H_