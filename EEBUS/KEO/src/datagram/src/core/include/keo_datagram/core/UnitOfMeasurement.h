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

#ifndef KEO_DATAGRAM_CORE_UNITOFMEASUREMENT_H_
#define KEO_DATAGRAM_CORE_UNITOFMEASUREMENT_H_

#include <cstdint>
#include <string>

#include <keo_datagram/core/SpineEnumClass.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration UnitOfMeasurement
 */
class UnitOfMeasurement : public ExtendableSpineEnum {
public:
  //! Number of possible enumeration values
  const static std::size_t MAX_ENUM = 94;

  //! Enumeration UnitOfMeasurement::Value
  enum class Value {
    UNDEFINED__ = -1,
    unknown,   // unknown
    _1,        // 1
    m,         // m
    kg,        // kg
    s,         // s
    A,         // A
    K,         // K
    mol,       // mol
    cd,        // cd
    V,         // V
    W,         // W
    Wh,        // Wh
    VA,        // VA
    VAh,       // VAh
    var,       // var
    varh,      // varh
    degC,      // degC
    degF,      // degF
    Lm,        // Lm
    lx,        // lx
    Ohm,       // Ohm
    Hz,        // Hz
    dB,        // dB
    dBm,       // dBm
    pct,       // pct
    ppm,       // ppm
    l,         // l
    ls,        // l/s
    lh,        // l/h
    deg,       // deg
    rad,       // rad
    rads,      // rad/s
    sr,        // sr
    Gy,        // Gy
    Bq,        // Bq
    Bqm3,      // Bq/m^3
    Sv,        // Sv
    Rd,        // Rd
    C,         // C
    F,         // F
    H,         // H
    J,         // J
    N,         // N
    Nm,        // N_m
    Ns,        // N_s
    Wb,        // Wb
    T,         // T
    Pa,        // Pa
    bar,       // bar
    atm,       // atm
    psi,       // psi
    mmHg,      // mmHg
    m2,        // m^2
    m3,        // m^3
    m3h,       // m^3/h
    ms,        // m/s
    ms2,       // m/s^2
    m3s,       // m^3/s
    mm3,       // m/m^3
    kgm3,      // kg/m^3
    kgm,       // kg_m
    m2s,       // m^2/s
    WmK,       // W/m_K
    JK,        // J/K
    _1s,       // 1/s
    Wm2,       // W/m^2
    Jm2,       // J/m^2
    S,         // S
    Sm,        // S/m
    Ks,        // K/s
    Pas,       // Pa/s
    JkgK,      // J/kg_K
    Vs,        // Vs
    Vm,        // V/m
    VHz,       // V/Hz
    As,        // As
    Am,        // A/m
    Hzs,       // Hz/s
    kgs,       // kg/s
    kgm2,      // kg_m^2
    JWh,       // J/Wh
    Ws,        // W/s
    ft3,       // ft^3
    ft3h,      // ft^3/h
    ccf,       // ccf
    ccfh,      // ccf/h
    USliqgal,  // US.liq.gal
    USliqgalh, // US.liq.gal/h
    Impgal,    // Imp.gal
    Impgalh,   // Imp.gal/h
    Btu,       // Btu
    Btuh,      // Btu/h
    Ah,        // Ah
    kgWh       // kg/Wh

  };

  /**
   * Constructs an instance with the value "undefined".
   */
  UnitOfMeasurement();

  /**
   * Constructs an instance and sets its value from enum value.
   * @param value the value of the new instance
   */
  UnitOfMeasurement(UnitOfMeasurement::Value value);

  /**
   * Constructs an instance and sets its value from string.
   * @param value the value of the new instance
   */
  UnitOfMeasurement(const std::string &value);

  /**
   * Constructs the enumeration value from string.
   * @returns An enumeration object created from the string
   */
  static UnitOfMeasurement fromString(const std::string &c_text);

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
  UnitOfMeasurement::Value getValue() const;

  /**
   * Return the value of this enumeration object.
   * \deprecated Use getValue() instead.
   * @return enumeration value
   */
  UnitOfMeasurement::Value getData() const;

  /**
   * Comparison operator ==
   * @param other object to compare
   */
  bool operator==(const UnitOfMeasurement &other) const;

  /**
   * Comparison operator !=
   * @param other object to compare
   */
  bool operator!=(const UnitOfMeasurement &other) const;

private:
  std::size_t toNumber() const;

  bool setFromNumber(std::size_t c_number);

  UnitOfMeasurement::Value m_data;

  // Human-readable strings of the enum data type
  static const std::string enumToString[MAX_ENUM];
};

/**
 * \deprecated Use UnitOfMeasurement instead.
 */
using UnitOfMeasurementStruct = UnitOfMeasurement;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_UNITOFMEASUREMENT_H_