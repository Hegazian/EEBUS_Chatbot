/**
 * @file ExampleSpineEventHandler.cpp
 * @brief Implementation of the example SPINE event handler
 * 
 * Copyright KEO GmbH 2025 - All rights reserved!
 */

#include <keo_spine/ExampleSpineEventHandler.h>
#include <keo_datagram/measurement/MeasurementListData.h>
#include <iostream>
#include <algorithm>

namespace keo_spine
{

ExampleSpineEventHandler::ExampleSpineEventHandler(const std::string& handlerName)
    : SpineEventHandlerBase(handlerName)
    , m_autoSubscribeToMeasurements(true)
{
    // Enable specific event types we're interested in
    setEventTypeEnabled(SpineEventType::DEVICE_DISCOVERY, true);
    setEventTypeEnabled(SpineEventType::DATAGRAM, true);
    setEventTypeEnabled(SpineEventType::SUBSCRIPTION, true);
    setEventTypeEnabled(SpineEventType::CONNECTION, true);
    
    // Set higher priority for error events
    setEventTypePriority(SpineEventType::ERROR, EventPriority::CRITICAL);
}

ExampleSpineEventHandler::~ExampleSpineEventHandler()
{
    // Cleanup if needed
}

// ========================================================================
// CUSTOMIZED EVENT HANDLING
// ========================================================================

EventResult ExampleSpineEventHandler::onDevicesDiscovered(
    const std::vector<std::string>& deviceNames, const EventContext& context)
{
    // Call base implementation first
    EventResult baseResult = SpineEventHandlerBase::onDevicesDiscovered(deviceNames, context);
    
    std::lock_guard<std::mutex> lock(m_stateMutex);
    
    // Track newly discovered devices
    for (const auto& deviceName : deviceNames) {
        m_knownDevices.insert(deviceName);
        updateDeviceStatus(deviceName, true);
        
        // Initialize measurement counter
        m_measurementCounts[deviceName] = 0;
        
        logEvent(SpineEventType::DEVICE_DISCOVERY, 
                "Tracking new device: " + deviceName, EventPriority::NORMAL);
    }
    
    return baseResult;
}

EventResult ExampleSpineEventHandler::onDevicesRemoved(
    const std::vector<std::string>& deviceNames, const EventContext& context)
{
    // Call base implementation first
    EventResult baseResult = SpineEventHandlerBase::onDevicesRemoved(deviceNames, context);
    
    std::lock_guard<std::mutex> lock(m_stateMutex);
    
    // Clean up tracking for removed devices
    for (const auto& deviceName : deviceNames) {
        m_knownDevices.erase(deviceName);
        updateDeviceStatus(deviceName, false);
        
        // Keep measurement statistics but mark device as disconnected
        logEvent(SpineEventType::DEVICE_DISCOVERY, 
                "Stopped tracking device: " + deviceName, EventPriority::NORMAL);
    }
    
    return baseResult;
}

EventResult ExampleSpineEventHandler::onDatagramCall(
    const DatagramRecord& datagramRecord, const EventContext& context)
{
    // Check if this is a measurement-related datagram
    if (processMeasurementData(datagramRecord, context.source)) {
        return EventResult::HANDLED;
    }
    
    // Fall back to base implementation for other datagrams
    return SpineEventHandlerBase::onDatagramCall(datagramRecord, context);
}

EventResult ExampleSpineEventHandler::onDatagramNotification(
    const DatagramRecord& datagramRecord, const EventContext& context)
{
    // Process measurement notifications (subscription data)
    if (processMeasurementData(datagramRecord, context.source)) {
        return EventResult::HANDLED;
    }
    
    // Fall back to base implementation
    return SpineEventHandlerBase::onDatagramNotification(datagramRecord, context);
}

EventResult ExampleSpineEventHandler::onSubscriptionRequested(
    unsigned int subscriptionId, 
    const keo_datagram::SubscriptionManagementRequestCall& subscriptionRequest,
    const EventContext& context)
{
    // Custom subscription logic - only accept subscriptions from known devices
    std::lock_guard<std::mutex> lock(m_stateMutex);
    
    // Check if we should auto-accept this subscription
    bool shouldAccept = shouldAutoSubscribe(context.source);
    
    if (shouldAccept) {
        logEvent(SpineEventType::SUBSCRIPTION, 
                "Accepting subscription request from " + context.source + 
                " (ID: " + std::to_string(subscriptionId) + ")", EventPriority::NORMAL);
        return EventResult::SUCCESS;
    } else {
        logEvent(SpineEventType::SUBSCRIPTION, 
                "Rejecting subscription request from " + context.source + 
                " (ID: " + std::to_string(subscriptionId) + ")", EventPriority::NORMAL);
        return EventResult::ERROR;
    }
}

// ========================================================================
// APPLICATION-SPECIFIC FUNCTIONALITY
// ========================================================================

void ExampleSpineEventHandler::setMeasurementCallback(const MeasurementCallback& callback)
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    m_measurementCallback = callback;
}

void ExampleSpineEventHandler::setDeviceCallback(const DeviceCallback& callback)
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    m_deviceCallback = callback;
}

void ExampleSpineEventHandler::setAutoSubscribeToMeasurements(bool enabled)
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    m_autoSubscribeToMeasurements = enabled;
}

void ExampleSpineEventHandler::addDeviceToAutoSubscribe(const std::string& deviceName)
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    m_autoSubscribeDevices.insert(deviceName);
}

void ExampleSpineEventHandler::removeDeviceFromAutoSubscribe(const std::string& deviceName)
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    m_autoSubscribeDevices.erase(deviceName);
}

std::vector<std::string> ExampleSpineEventHandler::getKnownDevices() const
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    return std::vector<std::string>(m_knownDevices.begin(), m_knownDevices.end());
}

bool ExampleSpineEventHandler::isDeviceConnected(const std::string& deviceName) const
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    auto it = m_deviceConnectionStatus.find(deviceName);
    return it != m_deviceConnectionStatus.end() && it->second;
}

std::map<std::string, uint64_t> ExampleSpineEventHandler::getMeasurementStatistics() const
{
    std::lock_guard<std::mutex> lock(m_stateMutex);
    return m_measurementCounts;
}

// ========================================================================
// PROTECTED HELPER METHODS
// ========================================================================

bool ExampleSpineEventHandler::processMeasurementData(const DatagramRecord& datagramRecord, 
                                                      const std::string& deviceName)
{
    // This is a simplified example - in a real implementation, you would
    // properly parse the datagram to extract measurement data
    
    try {
        // Check if this datagram contains measurement data
        // (This would involve proper datagram parsing in a real implementation)
        
        std::lock_guard<std::mutex> lock(m_stateMutex);
        
        // Increment measurement counter for this device
        m_measurementCounts[deviceName]++;
        
        // Call application callback if set
        if (m_measurementCallback) {
            // In a real implementation, you would extract the actual measurement data
            keo_datagram::MeasurementListData measurementData;
            m_measurementCallback(deviceName, measurementData);
        }
        
        logEvent(SpineEventType::DATAGRAM, 
                "Processed measurement data from " + deviceName + 
                " (total: " + std::to_string(m_measurementCounts[deviceName]) + ")", 
                EventPriority::NORMAL);
        
        return true;
    } catch (...) {
        logEvent(SpineEventType::ERROR, 
                "Failed to process measurement data from " + deviceName, 
                EventPriority::HIGH);
        return false;
    }
}

bool ExampleSpineEventHandler::shouldAutoSubscribe(const std::string& deviceName) const
{
    if (!m_autoSubscribeToMeasurements) {
        return false;
    }
    
    // If auto-subscribe list is empty, accept all known devices
    if (m_autoSubscribeDevices.empty()) {
        return m_knownDevices.find(deviceName) != m_knownDevices.end();
    }
    
    // Otherwise, only accept devices in the whitelist
    return m_autoSubscribeDevices.find(deviceName) != m_autoSubscribeDevices.end();
}

void ExampleSpineEventHandler::logEvent(SpineEventType eventType, const std::string& message, 
                                       EventPriority priority)
{
    // Add application-specific context to logging
    std::string contextualMessage = "[" + getHandlerName() + "] " + message;
    
    // Call base implementation
    SpineEventHandlerBase::logEvent(eventType, contextualMessage, priority);
}

void ExampleSpineEventHandler::updateDeviceStatus(const std::string& deviceName, bool connected)
{
    bool wasConnected = m_deviceConnectionStatus[deviceName];
    m_deviceConnectionStatus[deviceName] = connected;
    
    // Call application callback if status changed
    if (m_deviceCallback && wasConnected != connected) {
        m_deviceCallback(deviceName, connected);
    }
}

} // namespace keo_spine