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

#ifndef KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPARAMETERDESCRIPTIONDATAELEMENTS_H_
#define KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPARAMETERDESCRIPTIONDATAELEMENTS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataElements.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramElectricalConnection
 * @{
 */

/**
 * Declaration ElectricalConnectionParameterDescriptionDataElements
 */
class ElectricalConnectionParameterDescriptionDataElements
    : public DataElements {
public:
  /**
   * Construct an empty instance.
   */
  ElectricalConnectionParameterDescriptionDataElements();

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
  bool operator==(const ElectricalConnectionParameterDescriptionDataElements
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
  bool operator!=(const ElectricalConnectionParameterDescriptionDataElements
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
   * Set member MeasurementId.
   */
  void setMeasurementId();

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
   */
  void setVoltageType();

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
   */
  void setAcMeasuredPhases();

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
   */
  void setAcMeasuredInReferenceTo();

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
   */
  void setAcMeasurementType();

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
   */
  void setAcMeasurementVariant();

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
   */
  void setAcMeasuredHarmonic();

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
   */
  void setScopeType();

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
   */
  void setLabel();

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
   */
  void setDescription();

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

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  // ElementTag
  bool m_electricalConnectionIdIsSet;

  // ElementTag
  bool m_parameterIdIsSet;

  // ElementTag
  bool m_measurementIdIsSet;

  // ElementTag
  bool m_voltageTypeIsSet;

  // ElementTag
  bool m_acMeasuredPhasesIsSet;

  // ElementTag
  bool m_acMeasuredInReferenceToIsSet;

  // ElementTag
  bool m_acMeasurementTypeIsSet;

  // ElementTag
  bool m_acMeasurementVariantIsSet;

  // ElementTag
  bool m_acMeasuredHarmonicIsSet;

  // ElementTag
  bool m_scopeTypeIsSet;

  // ElementTag
  bool m_labelIsSet;

  // ElementTag
  bool m_descriptionIsSet;
};

//! typedef for non-const smart pointer type
//! ElectricalConnectionParameterDescriptionDataElements
using ElectricalConnectionParameterDescriptionDataElementsPtr =
    std::shared_ptr<ElectricalConnectionParameterDescriptionDataElements>;

//! typedef for const type ElectricalConnectionParameterDescriptionDataElements
using ElectricalConnectionParameterDescriptionDataElementsConst =
    const ElectricalConnectionParameterDescriptionDataElements;

//! typedef for const type ElectricalConnectionParameterDescriptionDataElements
using ElectricalConnectionParameterDescriptionDataElementsConstPtr =
    std::shared_ptr<ElectricalConnectionParameterDescriptionDataElementsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_ELECTRICALCONNECTION_ELECTRICALCONNECTIONPARAMETERDESCRIPTIONDATAELEMENTS_H_