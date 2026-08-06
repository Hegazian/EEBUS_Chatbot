/**
 * @file iSpineEventHandler.h
 * @brief Unified SPINE Event Handler Interface
 * 
 * This interface provides a comprehensive event handling mechanism for SPINE-based applications.
 * It unifies device-level, feature-level, and transport-level events into a single cohesive interface.
 * 
 * Copyright KEO GmbH 2025 - All rights reserved!
 */

#ifndef KEO_SPINE_ISPINE_EVENT_HANDLER_H_
#define KEO_SPINE_ISPINE_EVENT_HANDLER_H_

#include <keo_datagram/core/Datagram.h>
#include <keo_datagram/core/DetailedDiscovery.h>
#include <keo_datagram/core/DetailedDiscoveryPartial.h>
#include <keo_datagram/core/UseCaseDiscovery.h>
#include <keo_datagram/core/FeatureAddress.h>
#include <keo_datagram/core/SubscriptionManagementRequestCall.h>
#include <keo_datagram/core/SubscriptionManagementDeleteCall.h>
#include <keo_datagram/core/BindingManagementRequestCall.h>
#include <keo_datagram/core/BindingManagementDeleteCall.h>
#include <keo_spine/DatagramRecord.h>

#include <string>
#include <vector>
#include <memory>

namespace keo_spine
{

/**
 * @brief Enumeration of SPINE event types for categorization
 */
enum class SpineEventType
{
    CONNECTION,       ///< Connection/disconnection events
    DEVICE_DISCOVERY, ///< Device discovery and lifecycle events
    DATAGRAM,        ///< Datagram processing events
    SUBSCRIPTION,    ///< Subscription management events
    BINDING,         ///< Binding management events
    ERROR,           ///< Error and exception events
    LIFECYCLE        ///< Component lifecycle events
};

/**
 * @brief Event priority levels for processing order
 */
enum class EventPriority
{
    LOW = 0,
    NORMAL = 1,
    HIGH = 2,
    CRITICAL = 3
};

/**
 * @brief Result codes for event processing
 */
enum class EventResult
{
    SUCCESS,          ///< Event processed successfully
    HANDLED,          ///< Event handled, no further processing needed
    NOT_HANDLED,      ///< Event not handled, continue processing
    ERROR,            ///< Error occurred during processing
    ASYNC_PENDING     ///< Asynchronous processing started
};

/**
 * @brief Context information for events
 */
struct EventContext
{
    SpineEventType type;
    EventPriority priority;
    std::string source;          ///< Source identifier (device, feature, etc.)
    std::string transportId;     ///< Transport connection identifier
    uint64_t timestamp;          ///< Event timestamp
    std::string sessionId;       ///< Optional session identifier
    
    EventContext(SpineEventType t = SpineEventType::DATAGRAM, 
                EventPriority p = EventPriority::NORMAL)
        : type(t), priority(p), timestamp(0) {}
};

/**
 * @interface iSpineEventHandler
 * @brief Unified interface for handling all SPINE-related events
 * 
 * This interface provides a comprehensive event handling mechanism that consolidates
 * device callbacks, feature events, and transport events into a single unified interface.
 * Applications can implement this interface to handle all SPINE events in a consistent manner.
 */
class iSpineEventHandler
{
public:
    virtual ~iSpineEventHandler() = default;

    // ========================================================================
    // CONNECTION AND TRANSPORT EVENTS
    // ========================================================================

    /**
     * @brief Called when a new transport connection is established
     * @param transportId Identifier of the transport connection
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onConnectionEstablished(
        const std::string& transportId,
        const EventContext& context = EventContext(SpineEventType::CONNECTION)) = 0;

    /**
     * @brief Called when a transport connection is lost
     * @param transportId Identifier of the transport connection
     * @param reason Optional reason for disconnection
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onConnectionLost(
        const std::string& transportId,
        const std::string& reason = "",
        const EventContext& context = EventContext(SpineEventType::CONNECTION)) = 0;

    /**
     * @brief Called when connection authentication fails
     * @param transportId Identifier of the transport connection
     * @param errorDetails Error details
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onConnectionAuthenticationFailed(
        const std::string& transportId,
        const std::string& errorDetails,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) = 0;

    // ========================================================================
    // DEVICE DISCOVERY AND LIFECYCLE EVENTS
    // ========================================================================

    /**
     * @brief Called when new devices are discovered on the network
     * @param deviceNames List of newly discovered device names
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDevicesDiscovered(
        const std::vector<std::string>& deviceNames,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) = 0;

    /**
     * @brief Called when devices are removed from the network
     * @param deviceNames List of removed device names
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDevicesRemoved(
        const std::vector<std::string>& deviceNames,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) = 0;

    /**
     * @brief Called when detailed discovery information is received for a device
     * @param deviceName Name of the device
     * @param detailedDiscovery Detailed discovery information
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDetailedDiscovery(
        const std::string& deviceName,
        const keo_datagram::DetailedDiscovery& detailedDiscovery,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) = 0;

    /**
     * @brief Called when partial detailed discovery information is received
     * @param deviceName Name of the device
     * @param partialDiscovery Partial detailed discovery information
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onPartialDetailedDiscovery(
        const std::string& deviceName,
        const keo_datagram::DetailedDiscoveryPartial& partialDiscovery,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) = 0;

    /**
     * @brief Called when use case discovery information is received
     * @param deviceName Name of the device
     * @param useCaseDiscovery Use case discovery information
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onUseCaseDiscovery(
        const std::string& deviceName,
        const keo_datagram::UseCaseDiscovery& useCaseDiscovery,
        const EventContext& context = EventContext(SpineEventType::DEVICE_DISCOVERY)) = 0;

    // ========================================================================
    // DATAGRAM PROCESSING EVENTS
    // ========================================================================

    /**
     * @brief Called when a datagram call is received
     * @param datagramRecord The received datagram record
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDatagramCall(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) = 0;

    /**
     * @brief Called when a datagram reply is received
     * @param datagramRecord The received datagram record
     * @param originalCall Optional reference to the original call
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDatagramReply(
        const DatagramRecord& datagramRecord,
        const DatagramRecord* originalCall = nullptr,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) = 0;

    /**
     * @brief Called when a datagram notification is received
     * @param datagramRecord The received datagram record
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDatagramNotification(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) = 0;

    /**
     * @brief Called when a datagram result is received
     * @param datagramRecord The received datagram record
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDatagramResult(
        const DatagramRecord& datagramRecord,
        const EventContext& context = EventContext(SpineEventType::DATAGRAM)) = 0;

    /**
     * @brief Called when datagram processing times out
     * @param originalDatagram The original datagram that timed out
     * @param timeoutMs Timeout duration in milliseconds
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDatagramTimeout(
        const DatagramRecord& originalDatagram,
        long timeoutMs,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) = 0;

    // ========================================================================
    // SUBSCRIPTION MANAGEMENT EVENTS
    // ========================================================================

    /**
     * @brief Called when a subscription request is received
     * @param subscriptionId Unique identifier for the subscription
     * @param subscriptionRequest The subscription request details
     * @param context Event context information
     * @return Event processing result (SUCCESS to accept, ERROR to reject)
     */
    virtual EventResult onSubscriptionRequested(
        unsigned int subscriptionId,
        const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) = 0;

    /**
     * @brief Called when a subscription is successfully established
     * @param subscriptionId Unique identifier for the subscription
     * @param clientAddress Address of the subscribing client
     * @param serverAddress Address of the subscribed server
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onSubscriptionEstablished(
        unsigned int subscriptionId,
        const keo_datagram::FeatureAddress& clientAddress,
        const keo_datagram::FeatureAddress& serverAddress,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) = 0;

    /**
     * @brief Called when a subscription deletion request is received
     * @param deleteRequest The subscription deletion request
     * @param context Event context information
     * @return Event processing result (SUCCESS to accept, ERROR to reject)
     */
    virtual EventResult onSubscriptionDeleteRequested(
        const keo_datagram::SubscriptionManagementDeleteCall& deleteRequest,
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) = 0;

    /**
     * @brief Called when a subscription is removed
     * @param subscriptionId Unique identifier for the subscription
     * @param reason Reason for subscription removal
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onSubscriptionRemoved(
        unsigned int subscriptionId,
        const std::string& reason = "",
        const EventContext& context = EventContext(SpineEventType::SUBSCRIPTION)) = 0;

    // ========================================================================
    // BINDING MANAGEMENT EVENTS
    // ========================================================================

    /**
     * @brief Called when a binding request is received
     * @param bindingId Unique identifier for the binding
     * @param bindingRequest The binding request details
     * @param context Event context information
     * @return Event processing result (SUCCESS to accept, ERROR to reject)
     */
    virtual EventResult onBindingRequested(
        unsigned int bindingId,
        const keo_datagram::BindingManagementRequestCall& bindingRequest,
        const EventContext& context = EventContext(SpineEventType::BINDING)) = 0;

    /**
     * @brief Called when a binding is successfully established
     * @param bindingId Unique identifier for the binding
     * @param clientAddress Address of the binding client
     * @param serverAddress Address of the binding server
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onBindingEstablished(
        unsigned int bindingId,
        const keo_datagram::FeatureAddress& clientAddress,
        const keo_datagram::FeatureAddress& serverAddress,
        const EventContext& context = EventContext(SpineEventType::BINDING)) = 0;

    /**
     * @brief Called when a binding deletion request is received
     * @param deleteRequest The binding deletion request
     * @param context Event context information
     * @return Event processing result (SUCCESS to accept, ERROR to reject)
     */
    virtual EventResult onBindingDeleteRequested(
        const keo_datagram::BindingManagementDeleteCall& deleteRequest,
        const EventContext& context = EventContext(SpineEventType::BINDING)) = 0;

    /**
     * @brief Called when a binding is removed
     * @param bindingId Unique identifier for the binding
     * @param reason Reason for binding removal
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onBindingRemoved(
        unsigned int bindingId,
        const std::string& reason = "",
        const EventContext& context = EventContext(SpineEventType::BINDING)) = 0;

    // ========================================================================
    // ERROR AND EXCEPTION EVENTS
    // ========================================================================

    /**
     * @brief Called when a datagram parsing error occurs
     * @param rawData The raw data that could not be parsed
     * @param errorMessage Error description
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onDatagramParsingError(
        const std::string& rawData,
        const std::string& errorMessage,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) = 0;

    /**
     * @brief Called when a feature operation fails
     * @param featureAddress Address of the feature
     * @param operation Operation that failed
     * @param errorMessage Error description
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onFeatureOperationError(
        const keo_datagram::FeatureAddress& featureAddress,
        const std::string& operation,
        const std::string& errorMessage,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) = 0;

    /**
     * @brief Called when a transport error occurs
     * @param transportId Transport connection identifier
     * @param errorCode Error code
     * @param errorMessage Error description
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onTransportError(
        const std::string& transportId,
        int errorCode,
        const std::string& errorMessage,
        const EventContext& context = EventContext(SpineEventType::ERROR, EventPriority::HIGH)) = 0;

    // ========================================================================
    // LIFECYCLE EVENTS
    // ========================================================================

    /**
     * @brief Called when the SPINE system is initializing
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onSystemInitializing(
        const EventContext& context = EventContext(SpineEventType::LIFECYCLE, EventPriority::HIGH)) = 0;

    /**
     * @brief Called when the SPINE system initialization is complete
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onSystemReady(
        const EventContext& context = EventContext(SpineEventType::LIFECYCLE, EventPriority::HIGH)) = 0;

    /**
     * @brief Called when the SPINE system is shutting down
     * @param context Event context information
     * @return Event processing result
     */
    virtual EventResult onSystemShutdown(
        const EventContext& context = EventContext(SpineEventType::LIFECYCLE, EventPriority::CRITICAL)) = 0;

    // ========================================================================
    // UTILITY METHODS
    // ========================================================================

    /**
     * @brief Get the handler name/identifier
     * @return Handler identifier string
     */
    virtual std::string getHandlerName() const = 0;

    /**
     * @brief Check if the handler can process events of a specific type
     * @param eventType The event type to check
     * @return true if the handler can process this event type
     */
    virtual bool canHandleEventType(SpineEventType eventType) const = 0;

    /**
     * @brief Get the priority level for processing events of a specific type
     * @param eventType The event type
     * @return Priority level for this event type
     */
    virtual EventPriority getEventPriority(SpineEventType eventType) const = 0;
};

// Type definitions for convenience
using SpineEventHandlerPtr = std::shared_ptr<iSpineEventHandler>;
using SpineEventHandlerConstPtr = std::shared_ptr<const iSpineEventHandler>;

} // namespace keo_spine

#endif // KEO_SPINE_ISPINE_EVENT_HANDLER_H_