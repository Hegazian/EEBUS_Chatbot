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

/* ******************************************************************************
 * *
 *  standard header files *
 * ******************************************************************************
 */
#include <climits>
#include <cmath>
#include <sstream>
#include <stdlib.h>

/* ******************************************************************************
 * *
 *  project header files *
 * ******************************************************************************
 */
#include <keo_datagram/core/KeoScaledNumber.h>

/* ******************************************************************************
 * *
 *  defines *
 * ******************************************************************************
 */
#ifndef __cplusplus
#error C++ is required
#elif __cplusplus < 201103L
double trunc(double d) { return (d > 0) ? floor(d) : ceil(d); }
#endif

/* ******************************************************************************
 * *
 *  types *
 * ******************************************************************************
 */

/* ******************************************************************************
 * *
 *  definition *
 * ******************************************************************************
 */
namespace keo_datagram {

size_t const KeoScaledNumber::MaxNumberOfDigitsAfterComma = 12;

KeoScaledNumber::KeoScaledNumber() : m_numberType(0), m_scaleType(0) {}

KeoScaledNumber::KeoScaledNumber(KeoScaledNumber::NumberTypeType numberType,
                                 KeoScaledNumber::ScaleTypeType scaleType)
    : m_numberType(numberType), m_scaleType(scaleType) {}

KeoScaledNumber::KeoScaledNumber(KeoScaledNumber const &rhs)
    : m_numberType(rhs.m_numberType), m_scaleType(rhs.m_scaleType) {}

KeoScaledNumber::~KeoScaledNumber() {}

KeoScaledNumber::NumberTypeType KeoScaledNumber::getNumberType() const {
  return (m_numberType);
}

KeoScaledNumber::ScaleTypeType KeoScaledNumber::getScaleType() const {
  return (m_scaleType);
}

void KeoScaledNumber::setNumberType(const NumberTypeType &numberType) {
  m_numberType = numberType;
}

void KeoScaledNumber::setScaleType(const ScaleTypeType &scaleType) {
  m_scaleType = scaleType;
}

KeoScaledNumber &KeoScaledNumber::operator=(const KeoScaledNumber &rhs) {
  m_numberType = rhs.getNumberType();
  m_scaleType = rhs.getScaleType();
  return (*this);
}

KeoScaledNumber &KeoScaledNumber::operator=(double rhs) {
  *this = fromDouble(rhs, MaxNumberOfDigitsAfterComma);
  return (*this);
}

KeoScaledNumber::operator double() const {
  double ret = toDouble();
  return (ret);
}

bool KeoScaledNumber::operator==(KeoScaledNumber const &rhs) const {
  return (KeoScaledNumber::EQ == compare(rhs));
}

bool KeoScaledNumber::operator!=(KeoScaledNumber const &rhs) const {
  bool ret = !(*this == rhs);
  return (ret);
}

bool KeoScaledNumber::operator>(KeoScaledNumber const &rhs) const {
  return (KeoScaledNumber::GT == compare(rhs));
}

bool KeoScaledNumber::operator<(KeoScaledNumber const &rhs) const {
  return (KeoScaledNumber::LT == compare(rhs));
}

bool KeoScaledNumber::operator>=(KeoScaledNumber const &rhs) const {
  bool ret = ((*this > rhs) || (*this == rhs));
  return (ret);
}

bool KeoScaledNumber::operator<=(KeoScaledNumber const &rhs) const {
  bool ret = ((*this < rhs) || (*this == rhs));
  return (ret);
}

bool KeoScaledNumber::isNegative() const { return (m_numberType < 0); }

int KeoScaledNumber::compare(const KeoScaledNumber &b) const {
  KeoScaledNumber an = normalize(*this);
  KeoScaledNumber bn = normalize(b);

  if (an.getScaleType() == bn.getScaleType()) {
    if (an.getNumberType() > bn.getNumberType()) {
      return KeoScaledNumber::GT;
    }
    if (an.getNumberType() < bn.getNumberType()) {
      return KeoScaledNumber::LT;
    }
  } else {
    if (an.isNegative() && !bn.isNegative()) {
      return KeoScaledNumber::LT;
    }
    if (bn.isNegative() && !an.isNegative()) {
      return KeoScaledNumber::GT;
    }

    double da = an.toDouble();
    double db = bn.toDouble();

    if (da < db) {
      return KeoScaledNumber::LT;
    }
    if (da > db) {
      return KeoScaledNumber::GT;
    }
  }
  return KeoScaledNumber::EQ;
}

KeoScaledNumber KeoScaledNumber::fromDouble(double value,
                                            size_t digitsAfterComma) {
  KeoScaledNumber ret;
  if (value != 0) {
    if (value == trunc(value)) {
      ret.m_scaleType = 0;
      ret.m_numberType = static_cast<NumberTypeType>(value);
    } else {
      NumberTypeType tvalue = trunc(value);
      ret.m_scaleType = 0;

      // limit to a reasonable number of digits after comma
      if (digitsAfterComma > MaxNumberOfDigitsAfterComma) {
        digitsAfterComma = MaxNumberOfDigitsAfterComma;
      }

      // it might be, that the value after calculation of
      // r=value*10^digitsAfterComma is not valid with
      // the amount of 'digitsAfterComma'
      // Means:
      // The result 'r' does not fit in a long data type.
      // please be aware that on amd64 a long is 64bit but on raspi only 32bit
      while (digitsAfterComma > 0) {
        NumberTypeType cvalue;
        cvalue = tvalue * pow(10.0, digitsAfterComma);
        cvalue = cvalue / pow(10.0, digitsAfterComma);
        if (cvalue != tvalue) {
          --digitsAfterComma;
          continue;
        }
        break;
      }
      ret.m_scaleType = -digitsAfterComma;

      // shift the comma to the right
      value *= pow(10.0, digitsAfterComma);

      // use integer of value
      ret.m_numberType = static_cast<NumberTypeType>(value);

      if (ret.m_numberType == 0) {
        // the given precision (digitsAfterComma) is not sufficient to get a
        // resulting
        // number that does not equal 0. Hence, start a loop that shifts the
        // comma one
        // position to the right, until the resulting number is not equal to 0
        for (; ret.m_scaleType > SHRT_MIN; ret.m_scaleType--) {
          value *= 10;
          ret.m_numberType = static_cast<NumberTypeType>(value);
          if (ret.m_numberType != 0) {
            break;
          }
        }
      }
    }
  } else {
    ret.m_numberType = 0;
    ret.m_scaleType = 0;
  }
  return (ret);
}

std::string KeoScaledNumber::toString() const {
  std::string ret;
  if (m_scaleType >= 0) {
    ret = static_cast<std::ostringstream *>(
              &(std::ostringstream() << abs(m_numberType)))
              ->str();
    for (short i = 0; i < m_scaleType; i++) {
      ret.append("0");
    }
  } else {
    ret = static_cast<std::ostringstream *>(
              &(std::ostringstream() << abs(m_numberType)))
              ->str();
    if (ret.size() == static_cast<size_t>(abs(m_scaleType))) {
      ret.insert(0, "0.");
    } else if (ret.size() > static_cast<size_t>(abs(m_scaleType))) {
      ret.insert(ret.size() - abs(m_scaleType), ".");
    } else {
      ret.insert(0, abs(m_scaleType) - ret.size(), '0');
      ret.insert(0, "0.");
    }
  }
  if (isNegative()) {
    ret.insert(0, "-");
  }
  return (ret);
}

KeoScaledNumber KeoScaledNumber::fromString(std::string const &value,
                                            size_t digitsAfterComma) {
  KeoScaledNumber ret;
  if (!value.empty()) {

    std::stringstream ss(value);
    double temp;
    ss >> temp;
    ret = fromDouble(temp, digitsAfterComma);
  }
  return (ret);
}

double KeoScaledNumber::toDouble() const {
  double ret = getNumberType();
  if (ret != 0) {
    if (getScaleType() < 0) {
      ret /= pow(10.0, abs(m_scaleType));
    } else {
      ret *= pow(10.0, m_scaleType);
    }
  }
  return (ret);
}

KeoScaledNumber
KeoScaledNumber::normalize(const KeoScaledNumber &scaledNumber) {
  KeoScaledNumber ret(scaledNumber);

  if (ret.m_numberType == 0) {
    ret.m_scaleType = 0;
  } else {
    while ((ret.m_numberType % 10) == 0) {
      ret.m_scaleType++;
      ret.m_numberType /= 10;
    }
  }
  return (ret);
}

void KeoScaledNumber::equalizeScale(const KeoScaledNumber &snt1,
                                    const KeoScaledNumber &snt2,
                                    KeoScaledNumber &equalizedSnt1,
                                    KeoScaledNumber &equalizedSnt2) {
  KeoScaledNumber sntScaled;
  if (snt1.getScaleType() != snt2.getScaleType()) {
    const KeoScaledNumber *sntSmallerScale;
    const KeoScaledNumber *sntBiggerScale;
    if (snt1.getScaleType() < snt2.getScaleType()) {
      sntSmallerScale = &snt1;
      sntBiggerScale = &snt2;
    } else {
      sntSmallerScale = &snt2;
      sntBiggerScale = &snt1;
    }

    sntScaled.setNumberType(sntBiggerScale->getNumberType() *
                            pow(10, sntBiggerScale->getScaleType() -
                                        sntSmallerScale->getScaleType()));
    sntScaled.setScaleType(sntSmallerScale->getScaleType());

    if (sntSmallerScale == &snt1) {
      equalizedSnt1 = snt1;
      equalizedSnt2 = sntScaled;
    } else {
      equalizedSnt1 = sntScaled;
      equalizedSnt2 = snt2;
    }
  } else {
    equalizedSnt1 = snt1;
    equalizedSnt2 = snt2;
  }
}

KeoScaledNumber KeoScaledNumber::add(const KeoScaledNumber &summand1,
                                     const KeoScaledNumber &summand2) {
  KeoScaledNumber eqSummand1;
  KeoScaledNumber eqSummand2;

  equalizeScale(summand1, summand2, eqSummand1, eqSummand2);

  KeoScaledNumber sum;
  sum.setNumberType(eqSummand1.getNumberType() + eqSummand2.getNumberType());
  sum.setScaleType(eqSummand1.getScaleType());
  return normalize(sum);
}

KeoScaledNumber KeoScaledNumber::subtract(const KeoScaledNumber &minuend,
                                          const KeoScaledNumber &subtrahend) {
  return add(minuend, KeoScaledNumber(subtrahend.getNumberType() * (-1),
                                      subtrahend.getScaleType()));
}

KeoScaledNumber KeoScaledNumber::multiply(const KeoScaledNumber &factor1,
                                          const KeoScaledNumber &factor2) {
  return normalize(
      KeoScaledNumber(factor1.getNumberType() * factor2.getNumberType(),
                      factor1.getScaleType() + factor2.getScaleType()));
}
}