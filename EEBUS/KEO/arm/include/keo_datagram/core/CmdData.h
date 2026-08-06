/*
 *     Copyright KEO GmbH  - All rights reserved!
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

#ifndef KEO_DATAGRAM_CORE_CMDDATA_H_
#define KEO_DATAGRAM_CORE_CMDDATA_H_

#include <map>
#include <memory>
#include <string>

#include <keo_datagram/core/KeoJsonTransformable.h>
#include <keo_datagram/core/xs_types.h>

#include <keo_datagram/core/Filter.h>
#include <keo_datagram/core/Function.h>

namespace keo_datagram {

/** @addtogroup SpineDatagramCore
 * @{
 */

class CmdData;

//! typedef for non-const smart pointer type CmdData
using CmdDataPtr = std::shared_ptr<CmdData>;

//! typedef for const type CmdData
using CmdDataConst = const CmdData;

//! typedef for const type CmdData
using CmdDataConstPtr = std::shared_ptr<CmdDataConst>;

/**
 * Abstract base class for all CmdData.
 */
class CmdData : public KeoJsonTransformable {
public:
  //! Enumeration CmdData::Type
  enum class Type {
    UNDEFINED,
    ACTUATOR_LEVEL_DATA_TYPE,
    ACTUATOR_LEVEL_DESCRIPTION_DATA_TYPE,
    ACTUATOR_SWITCH_DATA_TYPE,
    ACTUATOR_SWITCH_DESCRIPTION_DATA_TYPE,
    ALARM_LIST_DATA_TYPE,
    BILL_CONSTRAINTS_LIST_DATA_TYPE,
    BILL_DESCRIPTION_LIST_DATA_TYPE,
    BILL_LIST_DATA_TYPE,
    BINDING_MANAGEMENT_DELETE_CALL_TYPE,
    BINDING_MANAGEMENT_ENTRY_LIST_DATA_TYPE,
    BINDING_MANAGEMENT_REQUEST_CALL_TYPE,
    COMMODITY_LIST_DATA_TYPE,
    DATA_TUNNELING_CALL_TYPE,
    DEVICE_CLASSIFICATION_MANUFACTURER_DATA_TYPE,
    DEVICE_CLASSIFICATION_USER_DATA_TYPE,
    DEVICE_CONFIGURATION_KEY_VALUE_CONSTRAINTS_LIST_DATA_TYPE,
    DEVICE_CONFIGURATION_KEY_VALUE_DESCRIPTION_LIST_DATA_TYPE,
    DEVICE_CONFIGURATION_KEY_VALUE_LIST_DATA_TYPE,
    DEVICE_DIAGNOSIS_HEARTBEAT_DATA_TYPE,
    DEVICE_DIAGNOSIS_SERVICE_DATA_TYPE,
    DEVICE_DIAGNOSIS_STATE_DATA_TYPE,
    DIRECT_CONTROL_ACTIVITY_LIST_DATA_TYPE,
    DIRECT_CONTROL_DESCRIPTION_DATA_TYPE,
    ELECTRICAL_CONNECTION_DESCRIPTION_LIST_DATA_TYPE,
    ELECTRICAL_CONNECTION_PARAMETER_DESCRIPTION_LIST_DATA_TYPE,
    ELECTRICAL_CONNECTION_PERMITTED_VALUE_SET_LIST_DATA_TYPE,
    ELECTRICAL_CONNECTION_STATE_LIST_DATA_TYPE,
    HVAC_OPERATION_MODE_DESCRIPTION_LIST_DATA_TYPE,
    HVAC_OVERRUN_DESCRIPTION_LIST_DATA_TYPE,
    HVAC_OVERRUN_LIST_DATA_TYPE,
    HVAC_SYSTEM_FUNCTION_DESCRIPTION_LIST_DATA_TYPE,
    HVAC_SYSTEM_FUNCTION_LIST_DATA_TYPE,
    HVAC_SYSTEM_FUNCTION_OPERATION_MODE_RELATION_LIST_DATA_TYPE,
    HVAC_SYSTEM_FUNCTION_POWER_SEQUENCE_RELATION_LIST_DATA_TYPE,
    HVAC_SYSTEM_FUNCTION_SETPOINT_RELATION_LIST_DATA_TYPE,
    IDENTIFICATION_LIST_DATA_TYPE,
    INCENTIVE_DESCRIPTION_LIST_DATA_TYPE,
    INCENTIVE_LIST_DATA_TYPE,
    INCENTIVE_TABLE_CONSTRAINTS_DATA_TYPE,
    INCENTIVE_TABLE_DATA_TYPE,
    INCENTIVE_TABLE_DESCRIPTION_DATA_TYPE,
    LOAD_CONTROL_EVENT_LIST_DATA_TYPE,
    LOAD_CONTROL_LIMIT_CONSTRAINTS_LIST_DATA_TYPE,
    LOAD_CONTROL_LIMIT_DESCRIPTION_LIST_DATA_TYPE,
    LOAD_CONTROL_LIMIT_LIST_DATA_TYPE,
    LOAD_CONTROL_NODE_DATA_TYPE,
    LOAD_CONTROL_STATE_LIST_DATA_TYPE,
    MEASUREMENT_CONSTRAINTS_LIST_DATA_TYPE,
    MEASUREMENT_DESCRIPTION_LIST_DATA_TYPE,
    MEASUREMENT_LIST_DATA_TYPE,
    MEASUREMENT_THRESHOLD_RELATION_LIST_DATA_TYPE,
    MESSAGING_LIST_DATA_TYPE,
    NETWORK_MANAGEMENT_ABORT_CALL_TYPE,
    NETWORK_MANAGEMENT_ADD_NODE_CALL_TYPE,
    NETWORK_MANAGEMENT_DEVICE_DESCRIPTION_LIST_DATA_TYPE,
    NETWORK_MANAGEMENT_DISCOVER_CALL_TYPE,
    NETWORK_MANAGEMENT_ENTITY_DESCRIPTION_LIST_DATA_TYPE,
    NETWORK_MANAGEMENT_FEATURE_DESCRIPTION_LIST_DATA_TYPE,
    NETWORK_MANAGEMENT_JOINING_MODE_DATA_TYPE,
    NETWORK_MANAGEMENT_MODIFY_NODE_CALL_TYPE,
    NETWORK_MANAGEMENT_PROCESS_STATE_DATA_TYPE,
    NETWORK_MANAGEMENT_REMOVE_NODE_CALL_TYPE,
    NETWORK_MANAGEMENT_REPORT_CANDIDATE_DATA_TYPE,
    NETWORK_MANAGEMENT_SCAN_NETWORK_CALL_TYPE,
    NODE_MANAGEMENT_BINDING_DATA_TYPE,
    NODE_MANAGEMENT_BINDING_DELETE_CALL_TYPE,
    NODE_MANAGEMENT_BINDING_REQUEST_CALL_TYPE,
    NODE_MANAGEMENT_DESTINATION_LIST_DATA_TYPE,
    NODE_MANAGEMENT_DETAILED_DISCOVERY_DATA_TYPE,
    NODE_MANAGEMENT_SUBSCRIPTION_DATA_TYPE,
    NODE_MANAGEMENT_SUBSCRIPTION_DELETE_CALL_TYPE,
    NODE_MANAGEMENT_SUBSCRIPTION_REQUEST_CALL_TYPE,
    NODE_MANAGEMENT_USE_CASE_DATA_TYPE,
    OPERATING_CONSTRAINTS_DURATION_LIST_DATA_TYPE,
    OPERATING_CONSTRAINTS_INTERRUPT_LIST_DATA_TYPE,
    OPERATING_CONSTRAINTS_POWER_DESCRIPTION_LIST_DATA_TYPE,
    OPERATING_CONSTRAINTS_POWER_LEVEL_LIST_DATA_TYPE,
    OPERATING_CONSTRAINTS_POWER_RANGE_LIST_DATA_TYPE,
    OPERATING_CONSTRAINTS_RESUME_IMPLICATION_LIST_DATA_TYPE,
    POWER_SEQUENCE_ALTERNATIVES_RELATION_LIST_DATA_TYPE,
    POWER_SEQUENCE_DESCRIPTION_LIST_DATA_TYPE,
    POWER_SEQUENCE_NODE_SCHEDULE_INFORMATION_DATA_TYPE,
    POWER_SEQUENCE_PRICE_CALCULATION_REQUEST_CALL_TYPE,
    POWER_SEQUENCE_PRICE_LIST_DATA_TYPE,
    POWER_SEQUENCE_SCHEDULE_CONFIGURATION_REQUEST_CALL_TYPE,
    POWER_SEQUENCE_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE,
    POWER_SEQUENCE_SCHEDULE_LIST_DATA_TYPE,
    POWER_SEQUENCE_SCHEDULE_PREFERENCE_LIST_DATA_TYPE,
    POWER_SEQUENCE_STATE_LIST_DATA_TYPE,
    POWER_TIME_SLOT_SCHEDULE_CONSTRAINTS_LIST_DATA_TYPE,
    POWER_TIME_SLOT_SCHEDULE_LIST_DATA_TYPE,
    POWER_TIME_SLOT_VALUE_LIST_DATA_TYPE,
    RESULT_DATA_TYPE,
    SENSING_DESCRIPTION_DATA_TYPE,
    SENSING_LIST_DATA_TYPE,
    SETPOINT_CONSTRAINTS_LIST_DATA_TYPE,
    SETPOINT_DESCRIPTION_LIST_DATA_TYPE,
    SETPOINT_LIST_DATA_TYPE,
    SMART_ENERGY_MANAGEMENT_PS_CONFIGURATION_REQUEST_CALL_TYPE,
    SMART_ENERGY_MANAGEMENT_PS_DATA_TYPE,
    SMART_ENERGY_MANAGEMENT_PS_PRICE_CALCULATION_REQUEST_CALL_TYPE,
    SMART_ENERGY_MANAGEMENT_PS_PRICE_DATA_TYPE,
    SPECIFICATION_VERSION_LIST_DATA_TYPE,
    SUBSCRIPTION_MANAGEMENT_DELETE_CALL_TYPE,
    SUBSCRIPTION_MANAGEMENT_ENTRY_LIST_DATA_TYPE,
    SUBSCRIPTION_MANAGEMENT_REQUEST_CALL_TYPE,
    SUPPLY_CONDITION_DESCRIPTION_LIST_DATA_TYPE,
    SUPPLY_CONDITION_LIST_DATA_TYPE,
    SUPPLY_CONDITION_THRESHOLD_RELATION_LIST_DATA_TYPE,
    TARIFF_BOUNDARY_RELATION_LIST_DATA_TYPE,
    TARIFF_DESCRIPTION_LIST_DATA_TYPE,
    TARIFF_LIST_DATA_TYPE,
    TARIFF_OVERALL_CONSTRAINTS_DATA_TYPE,
    TARIFF_TIER_RELATION_LIST_DATA_TYPE,
    TASK_MANAGEMENT_JOB_DESCRIPTION_LIST_DATA_TYPE,
    TASK_MANAGEMENT_JOB_LIST_DATA_TYPE,
    TASK_MANAGEMENT_JOB_RELATION_LIST_DATA_TYPE,
    TASK_MANAGEMENT_OVERVIEW_DATA_TYPE,
    THRESHOLD_CONSTRAINTS_LIST_DATA_TYPE,
    THRESHOLD_DESCRIPTION_LIST_DATA_TYPE,
    THRESHOLD_LIST_DATA_TYPE,
    TIER_BOUNDARY_DESCRIPTION_LIST_DATA_TYPE,
    TIER_BOUNDARY_LIST_DATA_TYPE,
    TIER_DESCRIPTION_LIST_DATA_TYPE,
    TIER_INCENTIVE_RELATION_LIST_DATA_TYPE,
    TIER_LIST_DATA_TYPE,
    TIME_DISTRIBUTOR_DATA_TYPE,
    TIME_DISTRIBUTOR_ENQUIRY_CALL_TYPE,
    TIME_INFORMATION_DATA_TYPE,
    TIME_PRECISION_DATA_TYPE,
    TIME_SERIES_CONSTRAINTS_LIST_DATA_TYPE,
    TIME_SERIES_DESCRIPTION_LIST_DATA_TYPE,
    TIME_SERIES_LIST_DATA_TYPE,
    TIME_TABLE_CONSTRAINTS_LIST_DATA_TYPE,
    TIME_TABLE_DESCRIPTION_LIST_DATA_TYPE,
    TIME_TABLE_LIST_DATA_TYPE,
    USE_CASE_INFORMATION_LIST_DATA_TYPE

  };

  /**
   * Get the type of this instance.
   * @return the type of this instance or UNDEFINED
   */
  virtual CmdData::Type getDataType() const = 0;

  /**
   * Checks if this instance is empty.
   * @return true, if no member is set
   */
  virtual bool isEmpty() const = 0;

  /**
   * Returns a copy of this instance.
   */
  virtual CmdDataPtr clone() const = 0;

  /**
   * Convert a CmdData::Type to a string.
   * @param type a type
   * @return the corresponding type or UNDEFINED
   */
  static std::string getStringFromType(CmdData::Type type);

  /**
   * Convert a string to a CmdData::Type.
   * @param type a string representing a type
   * @return the corresponding type or UNDEFINED
   */
  static CmdData::Type getTypeFromString(const std::string &type);

  /**
   * Create a reduced copy of this instance.
   *
   * The filters are applied to this data instance with "READ" semantics,
   * meaning that
   * only those list entries that are selected by the corresponding selectors
   * class
   * and only those members that are selected by the corresponding elements
   * class are
   * returned.
   *
   * If the Filter is in any form malformed (e.g. too many filters or wrong
   * cmdControl) this
   * method will return a full copy of this instance. Filters should be check
   * for correctness
   * before calling this method.
   *
   * For complex SPINE classes (e.g. NodeManagement) this method will return a
   * full copy even
   * if the Filter is correct, because the matching of filters in these classes
   * is very
   * complex. This however, is in accordance with EEBus SPINE 1.0.0 and EEBus
   * SPINE 1.1.0 when
   * this method is used for answering a READ datagram.
   *
   * @param filters the filters to apply
   * @return a reduced instance
   */
  virtual std::shared_ptr<CmdData>
  reduce(const std::vector<Filter> &filters) const = 0;

  /**
   * Create a and cast reduced copy of this instance.
   * @param filters the filters to apply
   * @return a reduced instance
   */
  template <typename T,
            typename std::enable_if<std::is_base_of<CmdData, T>::value>::type
                * = nullptr>
  static T reduce(const T &data, const std::vector<Filter> &filters) {
    return *(std::static_pointer_cast<T>(data.reduce(filters)).get());
  }

  /**
   * Converts a CmdData::Type to a Function, if possible.
   * See @see Function for possible type conversion.
   * @param type the CmdData type
   * @return the Function
   */
  static Function::Value getFunctionFromType(CmdData::Type type);

  /**
   * Converts a CmdData::Type to a Function, if possible.
   * @param value the Function
   * @return the CmdData type
   */
  static CmdData::Type getTypeFromFunction(Function::Value value);

private:
  static std::map<std::string, CmdData::Type> STRING_TO_TYPE;
};

/** @}
 */

} // namespace keo_datagram

#endif // KEO_DATAGRAM_CORE_CMDDATA_H_
