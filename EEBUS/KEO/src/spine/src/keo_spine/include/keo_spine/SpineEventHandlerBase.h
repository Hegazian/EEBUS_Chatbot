/**
 * @file SpineEventHandlerBase.h
 * @brief Base implementation for SPINE Event Handler Interface
 * 
 * This class provides a default implementation of the iSpineEventHandler interface
 * with common functionality and utility methods. Applications can inherit from this
 * class and override only the methods they need.
 * 
 * Copyright KEO GmbH 2025 - All rights reserved!
 */

#ifndef KEO_SPINE_SPINE_EVENT_HANDLER_BASE_H_
#define KEO_SPINE_SPINE_EVENT_HANDLER_BASE_H_

#include <keo_spine/iSpineEventHandler.h>
#include <map>
#include <set>
#include <mutex>
#include <chrono>

namespace keo_spine
{

/**
 * @class SpineEventHandlerBase
 * @brief Base implementation providing default behavior for SPINE event handling
 * 
 * This class provides sensible defaults for all iSpineEventHandler methods and
 * includes utility functionality for event filtering, logging, and statistics.
 * Derived classes can override specific methods as needed.
 */
class SpineEventHandlerBase : public iSpineEventHandler
{
public:
    /**
     * @brief Constructor
     * @param handlerName Name identifier for this handler
     */
    explicit SpineEventHandlerBase(const std::string& handlerName = "BaseEventHandler");

    /**
     * @brief Virtual destructor
     */
    virtual ~SpineEventHandlerBase();

    // ========================================================================
    // CONNECTION AND TRANSPORT EVENTS (Default implementations)
    // ========================================================================

    EventResult onConnectionEstablished(
        const std::string& transportId,
        const EventContext& context = EventContext(SpineEventType::CONNECTION)) override;

    EventResult onConnectionLost(
        const std::string& transportId,
        const std::string& reason = "",
        const EventContext& context = EventContext(SpineEventType::CONNECTION)) override;

    EventResult onConnectionAuthenticationFailed(
        const std::string& transportId,
        const std::string& errorDetails,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) override;

    // ========================================================================
    // DEVICE DISCOVERY AND LIFECYCLE EVENTS (Default implementations)
    // ========================================================================

    EventResult onDevicesDiscovered(
        const std::vector<std::string>& deviceNames,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    EventResult onDevicesRemoved(
        const std::vector<std::string>& deviceNames,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    EventResult onDetailedDiscovery(
        const std::string& deviceName,
        const keo_datagram::DetailedDiscovery& detailedDiscovery,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    EventResult onPartialDetailedDiscovery(
        const std::string& deviceName,
        const keo_datagram::DetailedDiscoveryPartial& partialDiscovery,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    EventResult onUseCaseDiscovery(
        const std::string& deviceName,
        const keo_datagram::UseCaseDiscovery& useCaseDiscovery,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) override;

    // ========================================================================
    // DATAGRAM PROCESSING EVENTS (Default implementations)
    // ========================================================================

    EventResult onDatagramCall(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) override;

    EventResult onDatagramReply(
        const DatagramRecord& datagramRecord,
        const DatagramRecord* originalCall = nullptr,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) override;

    EventResult onDatagramNotification(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) override;

    EventResult onDatagramResult(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) override;

    EventResult onDatagramTimeout(
        const DatagramRecord& originalDatagram,
        long timeoutMs,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) override;

    // ========================================================================
    // SUBSCRIPTION MANAGEMENT EVENTS (Default implementations)
    // ========================================================================

    EventResult onSubscriptionRequested(
        unsigned int subscriptionId,
        const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) override;

    EventResult onSubscriptionEstablished(
        unsigned int subscriptionId,
        const keo_datagram::FeatureAddress& clientAddress,
        const keo_datagram::FeatureAddress& serverAddress,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) override;

    EventResult onSubscriptionDeleteRequested(
        const keo_datagram::SubscriptionManagementDeleteCall& deleteRequest,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) override;

    EventResult onSubscriptionRemoved(
        unsigned int subscriptionId,
        const std::string& reason = "",
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) override;

    // ========================================================================
    // BINDING MANAGEMENT EVENTS (Default implementations)
    // ========================================================================

    EventResult onBindingRequested(
        unsigned int bindingId,
        const keo_datagram::BindingManagementRequestCall& bindingRequest,
        const EventContext& context = EventContext(SpineEventType::BINDING)) override;

    EventResult onBindingEstablished(
        unsigned int bindingId,
        const keo_datagram::FeatureAddress& clientAddress,
        const keo_datagram::FeatureAddress& serverAddress,
        const EventContext& context = EventContext(SpineEventType::BINDING)) override;

    EventResult onBindingDeleteRequested(
        const keo_datagram::BindingManagementDeleteCall& deleteRequest,
        const EventContext& context = EventContext(SpineEventType::BINDING)) override;

    EventResult onBindingRemoved(
        unsigned int bindingId,
        const std::string& reason = "",
        const EventContext& context = EventContext(SpineEventType::BINDING)) override;

    // ========================================================================
    // ERROR AND EXCEPTION EVENTS (Default implementations)
    // ========================================================================

    EventResult onDatagramParsingError(
        const std::string& rawData,
        const std::string& errorMessage,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) override;

    EventResult onFeatureOperationError(
        const keo_datagram::FeatureAddress& featureAddress,
        const std::string& operation,
        const std::string& errorMessage,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) override;

    EventResult onTransportError(
        const std::string& transportId,
        int errorCode,
        const std::string& errorMessage,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) override;

    // ========================================================================
    // LIFECYCLE EVENTS (Default implementations)
    // ========================================================================

    EventResult onSystemInitializing(
        const EventContext& context = EventContext(SpineEventType::LIFECYCLE, EventPriority::HIGH)) override;

    EventResult onSystemReady(
        const EventContext& context = EventContext(SpineEventType::LIFECYCLE, EventPriority::HIGH)) override;

    EventResult onSystemShutdown(
        const EventContext& context = EventContext(SpineEventType::LIFECYCLE, EventPriority::CRITICAL)) override;

    // ========================================================================
    // UTILITY METHODS (Implementations)
    // ========================================================================

    std::string getHandlerName() const override;
    bool canHandleEventType(SpineEventType eventType) const override;
    EventPriority getEventPriority(SpineEventType eventType) const override;

    // ========================================================================
    // CONFIGURATION AND FILTERING METHODS
    // ========================================================================

    /**
     * @brief Enable or disable handling of specific event types
     * @param eventType The event type to configure
     * @param enabled Whether to handle this event type
     */
    virtual void setEventTypeEnabled(SpineEventType eventType, bool enabled);

    /**
     * @brief Check if an event type is enabled for handling
     * @param eventType The event type to check
     * @return true if the event type is enabled
     */
    virtual bool isEventTypeEnabled(SpineEventType eventType) const;

    /**
     * @brief Set the priority for a specific event type
     * @param eventType The event type
     * @param priority The priority level
     */
    virtual void setEventTypePriority(SpineEventType eventType, EventPriority priority);

    /**
     * @brief Add a device filter - only events from these devices will be processed
     * @param deviceName Device name to filter for
     */
    virtual void addDeviceFilter(const std::string& deviceName);

    /**
     * @brief Remove a device filter
     * @param deviceName Device name to remove from filter
     */
    virtual void removeDeviceFilter(const std::string& deviceName);

    /**
     * @brief Clear all device filters
     */
    virtual void clearDeviceFilters();

    /**
     * @brief Check if a device passes the current filters
     * @param deviceName Device name to check
     * @return true if the device should be processed
     */
    virtual bool passesDeviceFilter(const std::string& deviceName) const;

    // ========================================================================
    // STATISTICS AND MONITORING
    // ========================================================================

    /**
     * @brief Get the number of events processed for a specific type
     * @param eventType The event type
     * @return Number of events processed
     */
    virtual uint64_t getEventCount(SpineEventType eventType) const;

    /**
     * @brief Get total number of events processed
     * @return Total event count
     */
    virtual uint64_t getTotalEventCount() const;

    /**
     * @brief Reset event statistics
     */
    virtual void resetStatistics();

    /**
     * @brief Get statistics as a formatted string
     * @return Statistics string
     */
    virtual std::string getStatisticsString() const;

protected:
    /**
     * @brief Log an event (can be overridden for custom logging)
     * @param eventType Type of event
     * @param message Log message
     * @param priority Event priority
     */
    virtual void logEvent(SpineEventType eventType, const std::string& message, 
                         EventPriority priority = EventPriority::NORMAL);

    /**
     * @brief Increment event counter for statistics
     * @param eventType The event type that was processed
     */
    virtual void incrementEventCounter(SpineEventType eventType);

    /**
     * @brief Check if event should be processed based on filters and settings
     * @param context Event context
     * @return true if event should be processed
     */
    virtual bool shouldProcessEvent(const EventContext& context) const;

    /**
     * @brief Create event context with current timestamp
     * @param type Event type
     * @param priority Event priority
     * @param source Source identifier
     * @return Populated event context
     */
    virtual EventContext createEventContext(SpineEventType type, EventPriority priority = EventPriority::NORMAL,
                                           const std::string& source = "") const;

private:
    std::string m_handlerName;
    mutable std::mutex m_mutex;
    
    // Configuration
    std::map<SpineEventType, bool> m_enabledEventTypes;
    std::map<SpineEventType, EventPriority> m_eventPriorities;
    std::set<std::string> m_deviceFilters;
    bool m_useDeviceFilters;
    
    // Statistics
    std::map<SpineEventType, uint64_t> m_eventCounts;
    std::chrono::steady_clock::time_point m_startTime;
    
    /**
     * @brief Initialize default settings
     */
    void initializeDefaults();
};

// Type definitions for convenience
using SpineEventHandlerBasePtr = std::shared_ptr<SpineEventHandlerBase>;
using SpineEventHandlerBaseConstPtr = std::shared_ptr<const SpineEventHandlerBase>;

} // namespace keo_spine

#endif // KEO_SPINE_SPINE_EVENT_HANDLER_BASE_H_