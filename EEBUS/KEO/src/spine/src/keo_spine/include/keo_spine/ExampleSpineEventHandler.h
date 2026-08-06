/**
 * @file ExampleSpineEventHandler.h
 * @brief Example implementation of the SPINE Event Handler Interface
 * 
 * This example demonstrates how to implement a custom SPINE event handler
 * for a specific application use case.
 * 
 * Copyright KEO GmbH 2025 - All rights reserved!
 */

#ifndef KEO_SPINE_EXAMPLE_SPINE_EVENT_HANDLER_H_
#define KEO_SPINE_EXAMPLE_SPINE_EVENT_HANDLER_H_

#include <keo_spine/SpineEventHandlerBase.h>
#include <keo_datagram/core/MeasurementListData.h>
#include <functional>
#include <map>

namespace keo_spine
{

/**
 * @class ExampleSpineEventHandler
 * @brief Example implementation showing typical SPINE event handling patterns
 * 
 * This class demonstrates how to:
 * - Handle specific datagram types (e.g., measurements)
 * - Manage device discovery and lifecycle
 * - Implement custom subscription logic
 * - Provide application-specific event processing
 */
class ExampleSpineEventHandler : public SpineEventHandlerBase
{
public:
    /**
     * @brief Callback function type for measurement data
     */
    using MeasurementCallback = std::function<void(const std::string& deviceName, 
                                                  const keo_datagram::MeasurementListData& data)>;

    /**
     * @brief Callback function type for device events
     */
    using DeviceCallback = std::function<void(const std::string& deviceName, bool connected)>;

    /**
     * @brief Constructor
     * @param handlerName Name for this event handler instance
     */
    explicit ExampleSpineEventHandler(const std::string& handlerName = "ExampleHandler");

    /**
     * @brief Virtual destructor
     */
    virtual ~ExampleSpineEventHandler();

    // ========================================================================
    // CUSTOMIZED EVENT HANDLING
    // ========================================================================

    /**
     * @brief Override device discovery to track known devices
     */
    EventResult onDevicesDiscovered(
        const std::vector<std::string>& deviceNames,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    /**
     * @brief Override device removal to clean up tracking
     */
    EventResult onDevicesRemoved(
        const std::vector<std::string>& deviceNames,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    /**
     * @brief Override datagram call handling to process specific message types
     */
    EventResult onDatagramCall(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) override;

    /**
     * @brief Override datagram notification handling for subscription data
     */
    EventResult onDatagramNotification(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) override;

    /**
     * @brief Override subscription request handling with custom logic
     */
    EventResult onSubscriptionRequested(
        unsigned int subscriptionId,
        const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) override;

    // ========================================================================
    // APPLICATION-SPECIFIC FUNCTIONALITY
    // ========================================================================

    /**
     * @brief Set callback for measurement data reception
     * @param callback Function to call when measurement data is received
     */
    void setMeasurementCallback(const MeasurementCallback& callback);

    /**
     * @brief Set callback for device connection events
     * @param callback Function to call when devices connect/disconnect
     */
    void setDeviceCallback(const DeviceCallback& callback);

    /**
     * @brief Enable automatic subscription to measurement features
     * @param enabled Whether to auto-subscribe to measurement features
     */
    void setAutoSubscribeToMeasurements(bool enabled);

    /**
     * @brief Add a device to the whitelist for automatic subscription
     * @param deviceName Name of the device to whitelist
     */
    void addDeviceToAutoSubscribe(const std::string& deviceName);

    /**
     * @brief Remove a device from the auto-subscription whitelist
     * @param deviceName Name of the device to remove
     */
    void removeDeviceFromAutoSubscribe(const std::string& deviceName);

    /**
     * @brief Get list of currently known devices
     * @return Vector of device names
     */
    std::vector<std::string> getKnownDevices() const;

    /**
     * @brief Check if a device is currently connected
     * @param deviceName Name of the device to check
     * @return true if device is connected
     */
    bool isDeviceConnected(const std::string& deviceName) const;

    /**
     * @brief Get statistics about processed measurements
     * @return Map of device name to measurement count
     */
    std::map<std::string, uint64_t> getMeasurementStatistics() const;

protected:
    /**
     * @brief Process measurement data from a datagram
     * @param datagramRecord The datagram containing measurement data
     * @param deviceName Name of the source device
     * @return true if measurement data was successfully processed
     */
    bool processMeasurementData(const DatagramRecord& datagramRecord, const std::string& deviceName);

    /**
     * @brief Check if we should auto-subscribe to a device's features
     * @param deviceName Name of the device
     * @return true if we should auto-subscribe
     */
    bool shouldAutoSubscribe(const std::string& deviceName) const;

    /**
     * @brief Custom logging with application context
     */
    void logEvent(SpineEventType eventType, const std::string& message, 
                 EventPriority priority = EventPriority::NORMAL) override;

private:
    // Configuration
    bool m_autoSubscribeToMeasurements;
    std::set<std::string> m_autoSubscribeDevices;
    
    // State tracking
    std::set<std::string> m_knownDevices;
    std::map<std::string, bool> m_deviceConnectionStatus;
    std::map<std::string, uint64_t> m_measurementCounts;
    
    // Callbacks
    MeasurementCallback m_measurementCallback;
    DeviceCallback m_deviceCallback;
    
    // Thread safety
    mutable std::mutex m_stateMutex;
    
    /**
     * @brief Update device connection status
     * @param deviceName Name of the device
     * @param connected Connection status
     */
    void updateDeviceStatus(const std::string& deviceName, bool connected);
};

// Type definitions for convenience
using ExampleSpineEventHandlerPtr = std::shared_ptr<ExampleSpineEventHandler>;
using ExampleSpineEventHandlerConstPtr = std::shared_ptr<const ExampleSpineEventHandler>;

} // namespace keo_spine

#endif // KEO_SPINE_EXAMPLE_SPINE_EVENT_HANDLER_H_