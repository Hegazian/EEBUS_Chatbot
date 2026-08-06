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

#ifndef KEO_DATAGRAM_MEASUREMENT_MEASUREMENTTYPE_H_
#define KEO_DATAGRAM_MEASUREMENT_MEASUREMENTTYPE_H_

#include <cstdint>
#include <string>

#include <keo_datagram/core/SpineEnumClass.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramMeasurement
 * @{
 */

/**
 * Declaration MeasurementType
 */
class MeasurementType : public ExtendableSpineEnum {
public:
  //! Number of possible enumeration values
  const static std::size_t MAX_ENUM = 42;

  //! Enumeration MeasurementType::Value
  enum class Value {
    UNDEFINED__ = -1,
    ACCELERATION,
    ANGLE,
    ANGULAR_VELOCITY,
    AREA,
    ATMOSPHERIC_PRESSURE,
    CAPACITY,
    CONCENTRATION,
    COUNT,
    CURRENT,
    DENSITY,
    DISTANCE,
    ELECTRIC_FIELD,
    ENERGY,
    FORCE,
    FREQUENCY,
    HARMONIC_DISTORTION,
    HEAT,
    HEAT_FLUX,
    ILLUMINANCE,
    IMPULSE,
    LEVEL,
    MAGNETIC_FIELD,
    MASS,
    MASS_FLOW,
    PARTICLES,
    PERCENTAGE,
    POWER,
    POWER_FACTOR,
    PRESSURE,
    RADON_ACTIVITY,
    RELATIVE_HUMIDITY,
    RESISTANCE,
    SOLAR_RADIATION,
    SPEED,
    TEMPERATURE,
    TIME,
    TORQUE,
    UNKNOWN,
    VELOCITY,
    VOLTAGE,
    VOLUME,
    VOLUMETRIC_FLOW
  };

  /**
   * Constructs an instance with the value "undefined".
   */
  MeasurementType();

  /**
   * Constructs an instance and sets its value from enum value.
   * @param value the value of the new instance
   */
  MeasurementType(MeasurementType::Value value);

  /**
   * Constructs an instance and sets its value from string.
   * @param value the value of the new instance
   */
  MeasurementType(const std::string &value);

  /**
   * Constructs the enumeration value from string.
   * @returns An enumeration object created from the string
   */
  static MeasurementType fromString(const std::string &c_text);

  /**
   * Return struct object as string
   * @return enumeration object as string
   */
  std::string toString() const;

  /**
   * Set this enum object from string
   * @param c_text the string to set
   */
  bool setFromString(const std::string &c_text);

  /**
   * Return the value of this enumeration object.
   * @return enumeration value
   */
  MeasurementType::Value getValue() const;

  /**
   * Return the value of this enumeration object.
   * \deprecated Use getValue() instead.
   * @return enumeration value
   */
  MeasurementType::Value getData() const;

  /**
   * Comparison operator ==
   * @param other object to compare
   */
  bool operator==(const MeasurementType &other) const;

  /**
   * Comparison operator !=
   * @param other object to compare
   */
  bool operator!=(const MeasurementType &other) const;

private:
  std::size_t toNumber() const;

  bool setFromNumber(std::size_t c_number);

  MeasurementType::Value m_data;

  // Human-readable strings of the enum data type
  static const std::string enumToString[MAX_ENUM];
};

/**
 * \deprecated Use MeasurementType instead.
 */
using MeasurementTypeStruct = MeasurementType;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_MEASUREMENT_MEASUREMENTTYPE_H_