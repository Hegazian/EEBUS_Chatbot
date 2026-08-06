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

#ifndef KEO_DATAGRAM_CORE_RESULTDATA_H_
#define KEO_DATAGRAM_CORE_RESULTDATA_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/CmdData.h>
#include <keo_datagram/core/xs_types.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

/**
 * Declaration ResultData
 */
class ResultData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  ResultData();

  /**
   * Construct an instance of this class and set its member.
   * @param c_errorNumber the member to set
   * @param c_description the member to set
   */
  ResultData(const xs_unsignedInt &c_errorNumber,
             const xs_string &c_description);

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
  bool operator==(const ResultData &c_classObject) const;

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
  bool operator!=(const ResultData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member ErrorNumber.
   * @param c_errorNumber Value to set
   */
  void setErrorNumber(const xs_unsignedInt &c_errorNumber);

  /**
   * Returns const reference to member ErrorNumber.
   * @return const reference to member errorNumber
   */
  const xs_unsignedInt &getErrorNumber() const;

  /**
   * Returns if member ErrorNumber is set.
   * @retval true member ErrorNumber is set
   * @retval false member ErrorNumber is not set
   */
  bool getErrorNumberIsSet() const;

  /**
   * Unsets member ErrorNumber
   */
  void cleanErrorNumber();

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_errorNumberIsSet;
  xs_unsignedInt m_errorNumber;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type ResultData
using ResultDataPtr = std::shared_ptr<ResultData>;

//! typedef for const type ResultData
using ResultDataConst = const ResultData;

//! typedef for const type ResultData
using ResultDataConstPtr = std::shared_ptr<ResultDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_RESULTDATA_H_