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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPERMITTEDVALUESETDATAELEMENTS_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPERMITTEDVALUESETDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/ScaledNumberSetElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionPermittedValueSetDataElements
 */
class ElectricalConnectionPermittedValueSetDataElements : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionPermittedValueSetDataElements();

  /**
   * Construct an instance of this class and set its member.
   * @param c_electricalConnectionIdIsSet the member to set
   * @param c_parameterIdIsSet the member to set
   * @param c_permittedValueSet the member to set
   */
  ElectricalConnectionPermittedValueSetDataElements(
      xs_boolean c_electricalConnectionIdIsSet, xs_boolean c_parameterIdIsSet,
      const ScaledNumberSetElements &c_permittedValueSet);

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
  bool operator==(const ElectricalConnectionPermittedValueSetDataElements
                      &c_classObject) const;

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
  bool operator!=(const ElectricalConnectionPermittedValueSetDataElements
                      &c_classObject) const;

  bool isEmpty() const override;

  DataElements::Type getDataType() const override;
  DataElementsPtr clone() const override;

  /**
   * Set member ElectricalConnectionId.
   */
  void setElectricalConnectionId();

  /**
   * Returns if member ElectricalConnectionId is set.
   * @retval true member ElectricalConnectionId is set
   * @retval false member ElectricalConnectionId is not set
   */
  bool getElectricalConnectionIdIsSet() const;

  /**
   * Unsets member ElectricalConnectionId
   */
  void cleanElectricalConnectionId();

  /**
   * Set member ParameterId.
   */
  void setParameterId();

  /**
   * Returns if member ParameterId is set.
   * @retval true member ParameterId is set
   * @retval false member ParameterId is not set
   */
  bool getParameterIdIsSet() const;

  /**
   * Unsets member ParameterId
   */
  void cleanParameterId();

  /**
   * Set member PermittedValueSet.
   * @param c_permittedValueSet Value to set
   */
  void setPermittedValueSet(const ScaledNumberSetElements &c_permittedValueSet);

  /**
   * Returns const reference to member PermittedValueSet.
   * @return const reference to member permittedValueSet
   */
  const ScaledNumberSetElements &getPermittedValueSet() const;

  /**
   * Returns if member PermittedValueSet is set.
   * @retval true member PermittedValueSet is set
   * @retval false member PermittedValueSet is not set
   */
  bool getPermittedValueSetIsSet() const;

  /**
   * Unsets member PermittedValueSet
   */
  void cleanPermittedValueSet();

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_electricalConnectionIdIsSet;

  // ElementTag
  bool m_parameterIdIsSet;

  bool m_permittedValueSetIsSet;
  ScaledNumberSetElements m_permittedValueSet;
};

//! typedef for non-const smart pointer type
//! ElectricalConnectionPermittedValueSetDataElements
using ElectricalConnectionPermittedValueSetDataElementsPtr =
    std::shared_ptr<ElectricalConnectionPermittedValueSetDataElements>;

//! typedef for const type ElectricalConnectionPermittedValueSetDataElements
using ElectricalConnectionPermittedValueSetDataElementsConst =
    const ElectricalConnectionPermittedValueSetDataElements;

//! typedef for const type ElectricalConnectionPermittedValueSetDataElements
using ElectricalConnectionPermittedValueSetDataElementsConstPtr =
    std::shared_ptr<ElectricalConnectionPermittedValueSetDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPERMITTEDVALUESETDATAELEMENTS_H_