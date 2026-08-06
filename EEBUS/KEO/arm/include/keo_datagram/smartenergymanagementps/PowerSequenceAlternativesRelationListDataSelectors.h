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

#ifndef KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEALTERNATIVESRELATIONLISTDATASELECTORS_H_
#define KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEALTERNATIVESRELATIONLISTDATASELECTORS_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <keo_datagram/core/DataSelectors.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/smartenergymanagementps/PowerSequenceAlternativesRelationData.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramSmartEnergyManagementPs
 * @{
 */

/**
 * Declaration PowerSequenceAlternativesRelationListDataSelectors
 */
class PowerSequenceAlternativesRelationListDataSelectors
    : public DataSelectors {
public:
  /**
   * Construct an empty instance.
   */
  PowerSequenceAlternativesRelationListDataSelectors();

  /**
   * Construct an instance of this class and set its member.
   * @param c_alternativesId the member to set
   * @param c_sequenceId the member to set
   */
  PowerSequenceAlternativesRelationListDataSelectors(
      const xs_unsignedInt &c_alternativesId,
      const xs_unsignedInt &c_sequenceId);

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
  bool operator==(const PowerSequenceAlternativesRelationListDataSelectors
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
  bool operator!=(const PowerSequenceAlternativesRelationListDataSelectors
                      &c_classObject) const;

  bool isEmpty() const override;

  DataSelectors::Type getDataType() const override;
  DataSelectorsPtr clone() const override;

  /**
   * Set member AlternativesId.
   * @param c_alternativesId Value to set
   */
  void setAlternativesId(const xs_unsignedInt &c_alternativesId);

  /**
   * Returns const reference to member AlternativesId.
   * @return const reference to member alternativesId
   */
  const xs_unsignedInt &getAlternativesId() const;

  /**
   * Returns if member AlternativesId is set.
   * @retval true member AlternativesId is set
   * @retval false member AlternativesId is not set
   */
  bool getAlternativesIdIsSet() const;

  /**
   * Unsets member AlternativesId
   */
  void cleanAlternativesId();

  /**
   * Set member SequenceId.
   * @param c_sequenceId Value to set
   */
  void setSequenceId(const xs_unsignedInt &c_sequenceId);

  /**
   * Returns const reference to member SequenceId.
   * @return const reference to member sequenceId
   */
  const xs_unsignedInt &getSequenceId() const;

  /**
   * Returns if member SequenceId is set.
   * @retval true member SequenceId is set
   * @retval false member SequenceId is not set
   */
  bool getSequenceIdIsSet() const;

  /**
   * Unsets member SequenceId
   */
  void cleanSequenceId();

  /**
   * Checks whether this selectors instance matches a given data instance.
   * @param data the data instance to match
   * @return true if this instance selects
   */
  bool selects(const PowerSequenceAlternativesRelationData &data) const;

private:
  bool fromJson(KeoJsonValue *json) override;

  std::string toJson() const override;

  bool m_alternativesIdIsSet;
  xs_unsignedInt m_alternativesId;

  bool m_sequenceIdIsSet;
  xs_unsignedInt m_sequenceId;
};

//! typedef for non-const smart pointer type
//! PowerSequenceAlternativesRelationListDataSelectors
using PowerSequenceAlternativesRelationListDataSelectorsPtr =
    std::shared_ptr<PowerSequenceAlternativesRelationListDataSelectors>;

//! typedef for const type PowerSequenceAlternativesRelationListDataSelectors
using PowerSequenceAlternativesRelationListDataSelectorsConst =
    const PowerSequenceAlternativesRelationListDataSelectors;

//! typedef for const type PowerSequenceAlternativesRelationListDataSelectors
using PowerSequenceAlternativesRelationListDataSelectorsConstPtr =
    std::shared_ptr<PowerSequenceAlternativesRelationListDataSelectorsConst>;

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_SMARTENERGYMANAGEMENTPS_POWERSEQUENCEALTERNATIVESRELATIONLISTDATASELECTORS_H_