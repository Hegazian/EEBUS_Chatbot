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

#ifndef KEO_DATAGRAM_CORE_NETWORKMANAGEMENTREPORTCANDIDATEDATA_H_
#define KEO_DATAGRAM_CORE_NETWORKMANAGEMENTREPORTCANDIDATEDATA_H_

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
 * Declaration NetworkManagementReportCandidateData
 */
class NetworkManagementReportCandidateData : public CmdData {
public:
  /**
   * Construct an empty instance.
   */
  NetworkManagementReportCandidateData();

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
  bool
  operator==(const NetworkManagementReportCandidateData &c_classObject) const;

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
  bool
  operator!=(const NetworkManagementReportCandidateData &c_classObject) const;

  bool isEmpty() const override;

  CmdData::Type getDataType() const override;
  CmdDataPtr clone() const override;

  /**
   * Set member CandidateSetup.
   * @param c_candidateSetup Value to set
   */
  void setCandidateSetup(const xs_string &c_candidateSetup);

  /**
   * Returns const reference to member CandidateSetup.
   * @return const reference to member candidateSetup
   */
  const xs_string &getCandidateSetup() const;

  /**
   * Returns if member CandidateSetup is set.
   * @retval true member CandidateSetup is set
   * @retval false member CandidateSetup is not set
   */
  bool getCandidateSetupIsSet() const;

  /**
   * Unsets member CandidateSetup
   */
  void cleanCandidateSetup();

  /**
   * Set member SetupUsableForAdd.
   * @param c_setupUsableForAdd Value to set
   */
  void setSetupUsableForAdd(const xs_boolean &c_setupUsableForAdd);

  /**
   * Returns const reference to member SetupUsableForAdd.
   * @return const reference to member setupUsableForAdd
   */
  const xs_boolean &getSetupUsableForAdd() const;

  /**
   * Returns if member SetupUsableForAdd is set.
   * @retval true member SetupUsableForAdd is set
   * @retval false member SetupUsableForAdd is not set
   */
  bool getSetupUsableForAddIsSet() const;

  /**
   * Unsets member SetupUsableForAdd
   */
  void cleanSetupUsableForAdd();

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

  CmdDataPtr reduce(const std::vector<Filter> &filters) const override;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_candidateSetupIsSet;
  xs_string m_candidateSetup;

  bool m_setupUsableForAddIsSet;
  xs_boolean m_setupUsableForAdd;

  bool m_labelIsSet;
  xs_string m_label;

  bool m_descriptionIsSet;
  xs_string m_description;
};

//! typedef for non-const smart pointer type
//! NetworkManagementReportCandidateData
using NetworkManagementReportCandidateDataPtr =
    std::shared_ptr<NetworkManagementReportCandidateData>;

//! typedef for const type NetworkManagementReportCandidateData
using NetworkManagementReportCandidateDataConst =
    const NetworkManagementReportCandidateData;

//! typedef for const type NetworkManagementReportCandidateData
using NetworkManagementReportCandidateDataConstPtr =
    std::shared_ptr<NetworkManagementReportCandidateDataConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_NETWORKMANAGEMENTREPORTCANDIDATEDATA_H_