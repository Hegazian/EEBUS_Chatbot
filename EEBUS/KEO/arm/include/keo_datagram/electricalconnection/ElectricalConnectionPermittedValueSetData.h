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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPERMITTEDVALUESETDATA_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPERMITTEDVALUESETDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScaledNumberSet.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionPermittedValueSetDataElements.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionPermittedValueSetData
 */
class ElectricalConnectionPermittedValueSetData : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionPermittedValueSetData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_electricalConnectionId the member to set
   * @param c_parameterId the member to set
   * @param c_permittedValueSet the member to set
   */
  ElectricalConnectionPermittedValueSetData(
      const xs_unsignedInt &c_electricalConnectionId,
      const xs_unsignedInt &c_parameterId,
      const std::vector<ScaledNumberSet> &c_permittedValueSet);

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
      const ElectricalConnectionPermittedValueSetData &c_classObject) const;

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
      const ElectricalConnectionPermittedValueSetData &c_classObject) const;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  bool isEmpty() const;

  /**
   * Set member ElectricalConnectionId.
   * @param c_electricalConnectionId Value to set
   */
  void
  setElectricalConnectionId(const xs_unsignedInt &c_electricalConnectionId);

  /**
   * Returns const reference to member ElectricalConnectionId.
   * @return const reference to member electricalConnectionId
   */
  const xs_unsignedInt &getElectricalConnectionId() const;

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
   * @param c_parameterId Value to set
   */
  void setParameterId(const xs_unsignedInt &c_parameterId);

  /**
   * Returns const reference to member ParameterId.
   * @return const reference to member parameterId
   */
  const xs_unsignedInt &getParameterId() const;

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
  void
  setPermittedValueSet(const std::vector<ScaledNumberSet> &c_permittedValueSet);

  /**
   * Returns const reference to member PermittedValueSet.
   * @return const reference to member permittedValueSet
   */
  const std::vector<ScaledNumberSet> &getPermittedValueSet() const;

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

  /**
   * @copydoc CmdData::reduce()
   */
  ElectricalConnectionPermittedValueSetData reduce(
      const ElectricalConnectionPermittedValueSetDataElements &elements) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_electricalConnectionIdIsSet;
  xs_unsignedInt m_electricalConnectionId;

  bool m_parameterIdIsSet;
  xs_unsignedInt m_parameterId;

  bool m_permittedValueSetIsSet;
  std::vector<ScaledNumberSet> m_permittedValueSet;
};

//! typedef for non-const smart pointer type
//! ElectricalConnectionPermittedValueSetData
using ElectricalConnectionPermittedValueSetDataPtr =
    std::shared_ptr<ElectricalConnectionPermittedValueSetData>;

//! typedef for const type ElectricalConnectionPermittedValueSetData
using ElectricalConnectionPermittedValueSetDataConst =
    const ElectricalConnectionPermittedValueSetData;

//! typedef for const type ElectricalConnectionPermittedValueSetData
using ElectricalConnectionPermittedValueSetDataConstPtr =
    std::shared_ptr<ElectricalConnectionPermittedValueSetDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPERMITTEDVALUESETDATA_H_