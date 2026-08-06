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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPARAMETERDESCRIPTIONDATA_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPARAMETERDESCRIPTIONDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/ScopeType.h>
#include <keo_datagram/core/xs_types.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionAcMeasurementType.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionMeasurandVariant.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionParameterDescriptionDataElements.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionPhaseName.h>
#include <keo_datagram/electricalconnection/ElectricalConnectionVoltageType.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionParameterDescriptionData
 */
class ElectricalConnectionParameterDescriptionData
    : public KeoJsonTransformable {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionParameterDescriptionData();

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
      const ElectricalConnectionParameterDescriptionData &c_classObject) const;

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
      const ElectricalConnectionParameterDescriptionData &c_classObject) const;

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
   * Set member MeasurementId.
   * @param c_measurementId Value to set
   */
  void setMeasurementId(const xs_unsignedInt &c_measurementId);

  /**
   * Returns const reference to member MeasurementId.
   * @return const reference to member measurementId
   */
  const xs_unsignedInt &getMeasurementId() const;

  /**
   * Returns if member MeasurementId is set.
   * @retval true member MeasurementId is set
   * @retval false member MeasurementId is not set
   */
  bool getMeasurementIdIsSet() const;

  /**
   * Unsets member MeasurementId
   */
  void cleanMeasurementId();

  /**
   * Set member VoltageType.
   * @param c_voltageType Value to set
   */
  void setVoltageType(const ElectricalConnectionVoltageType &c_voltageType);

  /**
   * Returns const reference to member VoltageType.
   * @return const reference to member voltageType
   */
  const ElectricalConnectionVoltageType &getVoltageType() const;

  /**
   * Returns if member VoltageType is set.
   * @retval true member VoltageType is set
   * @retval false member VoltageType is not set
   */
  bool getVoltageTypeIsSet() const;

  /**
   * Unsets member VoltageType
   */
  void cleanVoltageType();

  /**
   * Set member AcMeasuredPhases.
   * @param c_acMeasuredPhases Value to set
   */
  void
  setAcMeasuredPhases(const ElectricalConnectionPhaseName &c_acMeasuredPhases);

  /**
   * Returns const reference to member AcMeasuredPhases.
   * @return const reference to member acMeasuredPhases
   */
  const ElectricalConnectionPhaseName &getAcMeasuredPhases() const;

  /**
   * Returns if member AcMeasuredPhases is set.
   * @retval true member AcMeasuredPhases is set
   * @retval false member AcMeasuredPhases is not set
   */
  bool getAcMeasuredPhasesIsSet() const;

  /**
   * Unsets member AcMeasuredPhases
   */
  void cleanAcMeasuredPhases();

  /**
   * Set member AcMeasuredInReferenceTo.
   * @param c_acMeasuredInReferenceTo Value to set
   */
  void setAcMeasuredInReferenceTo(
      const ElectricalConnectionPhaseName &c_acMeasuredInReferenceTo);

  /**
   * Returns const reference to member AcMeasuredInReferenceTo.
   * @return const reference to member acMeasuredInReferenceTo
   */
  const ElectricalConnectionPhaseName &getAcMeasuredInReferenceTo() const;

  /**
   * Returns if member AcMeasuredInReferenceTo is set.
   * @retval true member AcMeasuredInReferenceTo is set
   * @retval false member AcMeasuredInReferenceTo is not set
   */
  bool getAcMeasuredInReferenceToIsSet() const;

  /**
   * Unsets member AcMeasuredInReferenceTo
   */
  void cleanAcMeasuredInReferenceTo();

  /**
   * Set member AcMeasurementType.
   * @param c_acMeasurementType Value to set
   */
  void setAcMeasurementType(
      const ElectricalConnectionAcMeasurementType &c_acMeasurementType);

  /**
   * Returns const reference to member AcMeasurementType.
   * @return const reference to member acMeasurementType
   */
  const ElectricalConnectionAcMeasurementType &getAcMeasurementType() const;

  /**
   * Returns if member AcMeasurementType is set.
   * @retval true member AcMeasurementType is set
   * @retval false member AcMeasurementType is not set
   */
  bool getAcMeasurementTypeIsSet() const;

  /**
   * Unsets member AcMeasurementType
   */
  void cleanAcMeasurementType();

  /**
   * Set member AcMeasurementVariant.
   * @param c_acMeasurementVariant Value to set
   */
  void setAcMeasurementVariant(
      const ElectricalConnectionMeasurandVariant &c_acMeasurementVariant);

  /**
   * Returns const reference to member AcMeasurementVariant.
   * @return const reference to member acMeasurementVariant
   */
  const ElectricalConnectionMeasurandVariant &getAcMeasurementVariant() const;

  /**
   * Returns if member AcMeasurementVariant is set.
   * @retval true member AcMeasurementVariant is set
   * @retval false member AcMeasurementVariant is not set
   */
  bool getAcMeasurementVariantIsSet() const;

  /**
   * Unsets member AcMeasurementVariant
   */
  void cleanAcMeasurementVariant();

  /**
   * Set member AcMeasuredHarmonic.
   * @param c_acMeasuredHarmonic Value to set
   */
  void setAcMeasuredHarmonic(const xs_unsignedByte &c_acMeasuredHarmonic);

  /**
   * Returns const reference to member AcMeasuredHarmonic.
   * @return const reference to member acMeasuredHarmonic
   */
  const xs_unsignedByte &getAcMeasuredHarmonic() const;

  /**
   * Returns if member AcMeasuredHarmonic is set.
   * @retval true member AcMeasuredHarmonic is set
   * @retval false member AcMeasuredHarmonic is not set
   */
  bool getAcMeasuredHarmonicIsSet() const;

  /**
   * Unsets member AcMeasuredHarmonic
   */
  void cleanAcMeasuredHarmonic();

  /**
   * Set member ScopeType.
   * @param c_scopeType Value to set
   */
  void setScopeType(const ScopeType &c_scopeType);

  /**
   * Returns const reference to member ScopeType.
   * @return const reference to member scopeType
   */
  const ScopeType &getScopeType() const;

  /**
   * Returns if member ScopeType is set.
   * @retval true member ScopeType is set
   * @retval false member ScopeType is not set
   */
  bool getScopeTypeIsSet() const;

  /**
   * Unsets member ScopeType
   */
  void cleanScopeType();

  /**
   * Set member Label.
   * @param c_label Value to set
   */
  void setLabel(const xs_string &c_label);

  /**
   * Returns const reference to member Label.
   * @return const reference to member label
   */
  const xs_string &getLabel() const;

  /**
   * Returns if member Label is set.
   * @retval true member Label is set
   * @retval false member Label is not set
   */
  bool getLabelIsSet() const;

  /**
   * Unsets member Label
   */
  void cleanLabel();

  /**
   * Set member Description.
   * @param c_description Value to set
   */
  void setDescription(const xs_string &c_description);

  /**
   * Returns const reference to member Description.
   * @return const reference to member description
   */
  const xs_string &getDescription() const;

  /**
   * Returns if member Description is set.
   * @retval true member Description is set
   * @retval false member Description is not set
   */
  bool getDescriptionIsSet() const;

  /**
   * Unsets member Description
   */
  void cleanDescription();

  /**
   * @copydoc CmdData::reduce()
   */
  ElectricalConnectionParameterDescriptionData
  reduce(const ElectricalConnectionParameterDescriptionDataElements &elements)
      const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_electricalConnectionIdIsSet;
  xs_unsignedInt m_electricalConnectionId;

  bool m_parameterIdIsSet;
  xs_unsignedInt m_parameterId;

  bool m_measurementIdIsSet;
  xs_unsignedInt m_measurementId;

  bool m_voltageTypeIsSet;
  ElectricalConnectionVoltageType m_voltageType;

  bool m_acMeasuredPhasesIsSet;
  ElectricalConnectionPhaseName m_acMeasuredPhases;

  bool m_acMeasuredInReferenceToIsSet;
  ElectricalConnectionPhaseName m_acMeasuredInReferenceTo;

  bool m_acMeasurementTypeIsSet;
  ElectricalConnectionAcMeasurementType m_acMeasurementType;

  bool m_acMeasurementVariantIsSet;
  ElectricalConnectionMeasurandVariant m_acMeasurementVariant;

  bool m_acMeasuredHarmonicIsSet;
  xs_unsignedByte m_acMeasuredHarmonic;

  bool m_scopeTypeIsSet;
  ScopeType m_scopeType;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type
//! ElectricalConnectionParameterDescriptionData
using ElectricalConnectionParameterDescriptionDataPtr =
    std::shared_ptr<ElectricalConnectionParameterDescriptionData>;

//! typedef for const type ElectricalConnectionParameterDescriptionData
using ElectricalConnectionParameterDescriptionDataConst =
    const ElectricalConnectionParameterDescriptionData;

//! typedef for const type ElectricalConnectionParameterDescriptionData
using ElectricalConnectionParameterDescriptionDataConstPtr =
    std::shared_ptr<ElectricalConnectionParameterDescriptionDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPARAMETERDESCRIPTIONDATA_H_