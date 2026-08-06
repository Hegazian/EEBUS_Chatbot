/**
 * @file SpineEventHandlerBase.cpp
 * @brief Implementation of the base SPINE event handler
 * 
 * Copyright KEO GmbH 2025 - All rights reserved!
 */

#include <keo_spine/SpineEventHandlerBase.h>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace keo_spine
{

SpineEventHandlerBase::SpineEventHandlerBase(const std::string& handlerName)
    : m_handlerName(handlerName)
    , m_useDeviceFilters(false)
    , m_startTime(std::chrono::steady_clock::now())
{
    initializeDefaults();
}

SpineEventHandlerBase::~SpineEventHandlerBase()
{
    // Cleanup if needed
}

void SpineEventHandlerBase::initializeDefaults()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    // Enable all event types by default
    m_enabledEventTypes[SpineEventType::CONNECTION] = true;
    m_enabledEventTypes[SpineEventType::DEVICE_DISCOVERY] = true;
    m_enabledEventTypes[SpineEventType::DATAGRAM] = true;
    m_enabledEventTypes[SpineEventType::SUBSCRIPTION] = true;
    m_enabledEventTypes[SpineEventType::BINDING] = true;
    m_enabledEventTypes[SpineEventType::ERROR] = true;
    m_enabledEventTypes[SpineEventType::LIFECYCLE] = true;
    
    // Set default priorities
    m_eventPriorities[SpineEventType::CONNECTION] = EventPriority::NORMAL;
    m_eventPriorities[SpineEventType::DEVICE_DISCOVERY] = EventPriority::NORMAL;
    m_eventPriorities[SpineEventType::DATAGRAM] = EventPriority::NORMAL;
    m_eventPriorities[SpineEventType::SUBSCRIPTION] = EventPriority::NORMAL;
    m_eventPriorities[SpineEventType::BINDING] = EventPriority::NORMAL;
    m_eventPriorities[SpineEventType::ERROR] = EventPriority::HIGH;
    m_eventPriorities[SpineEventType::LIFECYCLE] = EventPriority::HIGH;
    
    // Initialize event counters
    for (auto eventType : {SpineEventType::CONNECTION, SpineEventType::DEVICE_DISCOVERY, 
                          SpineEventType::DATAGRAM, SpineEventType::SUBSCRIPTION,
                          SpineEventType::BINDING, SpineEventType::ERROR, SpineEventType::LIFECYCLE})
    {
        m_eventCounts[eventType] = 0;
    }
}

// ========================================================================
// CONNECTION AND TRANSPORT EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onConnectionEstablished(
    const std::string& transportId, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::CONNECTION);
    logEvent(SpineEventType::CONNECTION, "Connection established: " + transportId, context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onConnectionLost(
    const std::string& transportId, const std::string& reason, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::CONNECTION);
    std::string message = "Connection lost: " + transportId;
    if (!reason.empty()) {
        message += " (reason: " + reason + ")";
    }
    logEvent(SpineEventType::CONNECTION, message, context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onConnectionAuthenticationFailed(
    const std::string& transportId, const std::string& errorDetails, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::ERROR);
    logEvent(SpineEventType::ERROR, "Authentication failed for " + transportId + ": " + errorDetails, context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// DEVICE DISCOVERY AND LIFECYCLE EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onDevicesDiscovered(
    const std::vector<std::string>& deviceNames, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DEVICE_DISCOVERY);
    std::ostringstream oss;
    oss << "Devices discovered: ";
    for (size_t i = 0; i < deviceNames.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << deviceNames[i];
    }
    logEvent(SpineEventType::DEVICE_DISCOVERY, oss.str(), context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onDevicesRemoved(
    const std::vector<std::string>& deviceNames, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DEVICE_DISCOVERY);
    std::ostringstream oss;
    oss << "Devices removed: ";
    for (size_t i = 0; i < deviceNames.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << deviceNames[i];
    }
    logEvent(SpineEventType::DEVICE_DISCOVERY, oss.str(), context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscovery& detailedDiscovery, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context) || !passesDeviceFilter(deviceName)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DEVICE_DISCOVERY);
    logEvent(SpineEventType::DEVICE_DISCOVERY, "Detailed discovery for device: " + deviceName, context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onPartialDetailedDiscovery(
    const std::string& deviceName, const keo_datagram::DetailedDiscoveryPartial& partialDiscovery, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context) || !passesDeviceFilter(deviceName)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DEVICE_DISCOVERY);
    logEvent(SpineEventType::DEVICE_DISCOVERY, "Partial detailed discovery for device: " + deviceName, context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onUseCaseDiscovery(
    const std::string& deviceName, const keo_datagram::UseCaseDiscovery& useCaseDiscovery, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context) || !passesDeviceFilter(deviceName)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DEVICE_DISCOVERY);
    logEvent(SpineEventType::DEVICE_DISCOVERY, "Use case discovery for device: " + deviceName, context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// DATAGRAM PROCESSING EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onDatagramCall(
    const DatagramRecord& datagramRecord, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DATAGRAM);
    logEvent(SpineEventType::DATAGRAM, "Datagram call received", context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onDatagramReply(
    const DatagramRecord& datagramRecord, const DatagramRecord* originalCall, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DATAGRAM);
    logEvent(SpineEventType::DATAGRAM, "Datagram reply received", context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onDatagramNotification(
    const DatagramRecord& datagramRecord, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DATAGRAM);
    logEvent(SpineEventType::DATAGRAM, "Datagram notification received", context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onDatagramResult(
    const DatagramRecord& datagramRecord, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::DATAGRAM);
    logEvent(SpineEventType::DATAGRAM, "Datagram result received", context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onDatagramTimeout(
    const DatagramRecord& originalDatagram, long timeoutMs, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::ERROR);
    std::ostringstream oss;
    oss << "Datagram timeout after " << timeoutMs << "ms";
    logEvent(SpineEventType::ERROR, oss.str(), context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// SUBSCRIPTION MANAGEMENT EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onSubscriptionRequested(
    unsigned int subscriptionId, const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::SUBSCRIPTION);
    std::ostringstream oss;
    oss << "Subscription requested (ID: " << subscriptionId << ")";
    logEvent(SpineEventType::SUBSCRIPTION, oss.str(), context.priority);
    return EventResult::SUCCESS; // Accept by default
}

EventResult SpineEventHandlerBase::onSubscriptionEstablished(
    unsigned int subscriptionId, const keo_datagram::FeatureAddress& clientAddress, 
    const keo_datagram::FeatureAddress& serverAddress, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::SUBSCRIPTION);
    std::ostringstream oss;
    oss << "Subscription established (ID: " << subscriptionId << ")";
    logEvent(SpineEventType::SUBSCRIPTION, oss.str(), context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onSubscriptionDeleteRequested(
    const keo_datagram::SubscriptionManagementDeleteCall& deleteRequest, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::SUBSCRIPTION);
    logEvent(SpineEventType::SUBSCRIPTION, "Subscription delete requested", context.priority);
    return EventResult::SUCCESS; // Accept by default
}

EventResult SpineEventHandlerBase::onSubscriptionRemoved(
    unsigned int subscriptionId, const std::string& reason, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::SUBSCRIPTION);
    std::ostringstream oss;
    oss << "Subscription removed (ID: " << subscriptionId << ")";
    if (!reason.empty()) {
        oss << " - " << reason;
    }
    logEvent(SpineEventType::SUBSCRIPTION, oss.str(), context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// BINDING MANAGEMENT EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onBindingRequested(
    unsigned int bindingId, const keo_datagram::BindingManagementRequestCall& bindingRequest, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::BINDING);
    std::ostringstream oss;
    oss << "Binding requested (ID: " << bindingId << ")";
    logEvent(SpineEventType::BINDING, oss.str(), context.priority);
    return EventResult::SUCCESS; // Accept by default
}

EventResult SpineEventHandlerBase::onBindingEstablished(
    unsigned int bindingId, const keo_datagram::FeatureAddress& clientAddress, 
    const keo_datagram::FeatureAddress& serverAddress, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::BINDING);
    std::ostringstream oss;
    oss << "Binding established (ID: " << bindingId << ")";
    logEvent(SpineEventType::BINDING, oss.str(), context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onBindingDeleteRequested(
    const keo_datagram::BindingManagementDeleteCall& deleteRequest, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::BINDING);
    logEvent(SpineEventType::BINDING, "Binding delete requested", context.priority);
    return EventResult::SUCCESS; // Accept by default
}

EventResult SpineEventHandlerBase::onBindingRemoved(
    unsigned int bindingId, const std::string& reason, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::BINDING);
    std::ostringstream oss;
    oss << "Binding removed (ID: " << bindingId << ")";
    if (!reason.empty()) {
        oss << " - " << reason;
    }
    logEvent(SpineEventType::BINDING, oss.str(), context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// ERROR AND EXCEPTION EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onDatagramParsingError(
    const std::string& rawData, const std::string& errorMessage, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::ERROR);
    logEvent(SpineEventType::ERROR, "Datagram parsing error: " + errorMessage, context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onFeatureOperationError(
    const keo_datagram::FeatureAddress& featureAddress, const std::string& operation, 
    const std::string& errorMessage, const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::ERROR);
    std::ostringstream oss;
    oss << "Feature operation error (" << operation << "): " << errorMessage;
    logEvent(SpineEventType::ERROR, oss.str(), context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onTransportError(
    const std::string& transportId, int errorCode, const std::string& errorMessage, 
    const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::ERROR);
    std::ostringstream oss;
    oss << "Transport error [" << errorCode << "] on " << transportId << ": " << errorMessage;
    logEvent(SpineEventType::ERROR, oss.str(), context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// LIFECYCLE EVENTS
// ========================================================================

EventResult SpineEventHandlerBase::onSystemInitializing(const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::LIFECYCLE);
    logEvent(SpineEventType::LIFECYCLE, "System initializing", context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onSystemReady(const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::LIFECYCLE);
    logEvent(SpineEventType::LIFECYCLE, "System ready", context.priority);
    return EventResult::HANDLED;
}

EventResult SpineEventHandlerBase::onSystemShutdown(const EventContext& context)
{
    if (!shouldProcessEvent(context)) {
        return EventResult::NOT_HANDLED;
    }
    
    incrementEventCounter(SpineEventType::LIFECYCLE);
    logEvent(SpineEventType::LIFECYCLE, "System shutting down", context.priority);
    return EventResult::HANDLED;
}

// ========================================================================
// UTILITY METHODS
// ========================================================================

std::string SpineEventHandlerBase::getHandlerName() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_handlerName;
}

bool SpineEventHandlerBase::canHandleEventType(SpineEventType eventType) const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_enabledEventTypes.find(eventType);
    return it != m_enabledEventTypes.end() && it->second;
}

EventPriority SpineEventHandlerBase::getEventPriority(SpineEventType eventType) const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_eventPriorities.find(eventType);
    return it != m_eventPriorities.end() ? it->second : EventPriority::NORMAL;
}

// ========================================================================
// CONFIGURATION AND FILTERING METHODS
// ========================================================================

void SpineEventHandlerBase::setEventTypeEnabled(SpineEventType eventType, bool enabled)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_enabledEventTypes[eventType] = enabled;
}

bool SpineEventHandlerBase::isEventTypeEnabled(SpineEventType eventType) const
{
    return canHandleEventType(eventType);
}

void SpineEventHandlerBase::setEventTypePriority(SpineEventType eventType, EventPriority priority)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_eventPriorities[eventType] = priority;
}

void SpineEventHandlerBase::addDeviceFilter(const std::string& deviceName)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceFilters.insert(deviceName);
    m_useDeviceFilters = !m_deviceFilters.empty();
}

void SpineEventHandlerBase::removeDeviceFilter(const std::string& deviceName)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceFilters.erase(deviceName);
    m_useDeviceFilters = !m_deviceFilters.empty();
}

void SpineEventHandlerBase::clearDeviceFilters()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deviceFilters.clear();
    m_useDeviceFilters = false;
}

bool SpineEventHandlerBase::passesDeviceFilter(const std::string& deviceName) const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_useDeviceFilters) {
        return true;
    }
    return m_deviceFilters.find(deviceName) != m_deviceFilters.end();
}

// ========================================================================
// STATISTICS AND MONITORING
// ========================================================================

uint64_t SpineEventHandlerBase::getEventCount(SpineEventType eventType) const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_eventCounts.find(eventType);
    return it != m_eventCounts.end() ? it->second : 0;
}

uint64_t SpineEventHandlerBase::getTotalEventCount() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    uint64_t total = 0;
    for (const auto& pair : m_eventCounts) {
        total += pair.second;
    }
    return total;
}

void SpineEventHandlerBase::resetStatistics()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& pair : m_eventCounts) {
        pair.second = 0;
    }
    m_startTime = std::chrono::steady_clock::now();
}

std::string SpineEventHandlerBase::getStatisticsString() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - m_startTime);
    
    std::ostringstream oss;
    oss << "Event Handler Statistics for '" << m_handlerName << "':\n";
    oss << "  Running time: " << duration.count() << " seconds\n";
    oss << "  Total events: " << getTotalEventCount() << "\n";
    oss << "  Event breakdown:\n";
    
    const char* eventTypeNames[] = {
        "Connection", "Device Discovery", "Datagram", "Subscription", 
        "Binding", "Error", "Lifecycle"
    };
    
    int index = 0;
    for (auto eventType : {SpineEventType::CONNECTION, SpineEventType::DEVICE_DISCOVERY, 
                          SpineEventType::DATAGRAM, SpineEventType::SUBSCRIPTION,
                          SpineEventType::BINDING, SpineEventType::ERROR, SpineEventType::LIFECYCLE}) {
        uint64_t count = getEventCount(eventType);
        oss << "    " << std::setw(16) << std::left << eventTypeNames[index++] << ": " << count << "\n";
    }
    
    return oss.str();
}

// ========================================================================
// PROTECTED HELPER METHODS
// ========================================================================

void SpineEventHandlerBase::logEvent(SpineEventType eventType, const std::string& message, EventPriority priority)
{
    // Basic console logging - can be overridden for custom logging
    const char* priorityStr = "NORMAL";
    switch (priority) {
        case EventPriority::LOW: priorityStr = "LOW"; break;
        case EventPriority::NORMAL: priorityStr = "NORMAL"; break;
        case EventPriority::HIGH: priorityStr = "HIGH"; break;
        case EventPriority::CRITICAL: priorityStr = "CRITICAL"; break;
    }
    
    std::cout << "[" << m_handlerName << "] [" << priorityStr << "] " << message << std::endl;
}

void SpineEventHandlerBase::incrementEventCounter(SpineEventType eventType)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_eventCounts[eventType]++;
}

bool SpineEventHandlerBase::shouldProcessEvent(const EventContext& context) const
{
    if (!canHandleEventType(context.type)) {
        return false;
    }
    
    // Check device filter if applicable
    if (!context.source.empty() && !passesDeviceFilter(context.source)) {
        return false;
    }
    
    return true;
}

EventContext SpineEventHandlerBase::createEventContext(SpineEventType type, EventPriority priority, 
                                                      const std::string& source) const
{
    EventContext context(type, priority);
    context.source = source;
    context.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    return context;
}

} // namespace keo_spine