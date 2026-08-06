/**
 * @file usage_example.cpp
 * @brief Usage example for the SPINE Event Handler Interface
 * 
 * This example demonstrates how to integrate the iSpineEventHandler interface
 * into a SPINE-based application for unified event handling.
 * 
 * Copyright KEO GmbH 2025 - All rights reserved!
 */

#include <keo_spine/ExampleSpineEventHandler.h>
#include <keo_spine/SmartDevice.h>
#include <keo_spine/SpineLink.h>
#include <keo_datagram/measurement/MeasurementListData.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

using namespace keo_spine;
using namespace keo_datagram;

/**
 * @brief Application class demonstrating SPINE event handler usage
 */
class HemsApplication
{
public:
    HemsApplication() 
        : m_eventHandler(std::make_shared<ExampleSpineEventHandler>("HEMS_Handler"))
    {
        setupEventHandler();
    }

    ~HemsApplication() 
    {
        shutdown();
    }

    /**
     * @brief Initialize the HEMS application
     */
    bool initialize()
    {
        std::cout << "Initializing HEMS Application..." << std::endl;

        try {
            // Create SPINE link and main device
            m_spineLink = std::make_shared<SpineLink>();
            m_mainDevice = std::make_shared<SmartDevice>("HEMS_Manager");

            // Set up the device with our event handler
            // Note: In a real implementation, you would need to integrate
            // the event handler with the existing DeviceCallbackInterface
            // by creating an adapter class

            // Initialize the main device
            if (!m_mainDevice->initialize()) {
                std::cerr << "Failed to initialize main device" << std::endl;
                return false;
            }

            // Set the main device in SPINE link
            m_spineLink->setMainDevice(m_mainDevice);

            // Trigger system initialization event
            EventContext initContext(SpineEventType::LIFECYCLE, EventPriority::HIGH);
            m_eventHandler->onSystemInitializing(initContext);

            std::cout << "HEMS Application initialized successfully" << std::endl;

            // Trigger system ready event
            EventContext readyContext(SpineEventType::LIFECYCLE, EventPriority::HIGH);
            m_eventHandler->onSystemReady(readyContext);

            return true;

        } catch (const std::exception& e) {
            std::cerr << "Initialization failed: " << e.what() << std::endl;
            return false;
        }
    }

    /**
     * @brief Run the main application loop
     */
    void run()
    {
        std::cout << "Starting HEMS Application main loop..." << std::endl;

        // Simulate device discovery and events
        simulateDeviceEvents();

        // Main application loop
        bool running = true;
        int eventCounter = 0;
        
        while (running && eventCounter < 50) { // Limit for demo
            // Simulate various SPINE events
            simulateSpineEvents();
            
            // Print statistics every 10 iterations
            if (++eventCounter % 10 == 0) {
                printStatistics();
            }

            // Sleep to simulate real-time operation
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            // Stop after a while for demo purposes
            if (eventCounter >= 50) {
                running = false;
            }
        }

        std::cout << "HEMS Application main loop finished" << std::endl;
    }

    /**
     * @brief Shutdown the application
     */
    void shutdown()
    {
        std::cout << "Shutting down HEMS Application..." << std::endl;

        if (m_eventHandler) {
            EventContext shutdownContext(SpineEventType::LIFECYCLE, EventPriority::CRITICAL);
            m_eventHandler->onSystemShutdown(shutdownContext);
        }

        if (m_mainDevice) {
            m_mainDevice->close();
        }

        std::cout << "HEMS Application shutdown complete" << std::endl;
    }

private:
    std::shared_ptr<ExampleSpineEventHandler> m_eventHandler;
    std::shared_ptr<SpineLink> m_spineLink;
    std::shared_ptr<SmartDevice> m_mainDevice;

    /**
     * @brief Set up the event handler with callbacks and configuration
     */
    void setupEventHandler()
    {
        // Configure measurement callback
        m_eventHandler->setMeasurementCallback(
            [this](const std::string& deviceName, const MeasurementListData& data) {
                handleMeasurementData(deviceName, data);
            });

        // Configure device callback
        m_eventHandler->setDeviceCallback(
            [this](const std::string& deviceName, bool connected) {
                handleDeviceConnectionChange(deviceName, connected);
            });

        // Enable auto-subscription to measurements
        m_eventHandler->setAutoSubscribeToMeasurements(true);

        // Add specific devices to auto-subscribe list
        m_eventHandler->addDeviceToAutoSubscribe("SolarInverter_01");
        m_eventHandler->addDeviceToAutoSubscribe("BatterySystem_01");
        m_eventHandler->addDeviceToAutoSubscribe("HeatPump_01");

        // Configure event filtering
        m_eventHandler->addDeviceFilter("SolarInverter_01");
        m_eventHandler->addDeviceFilter("BatterySystem_01");
        m_eventHandler->addDeviceFilter("HeatPump_01");

        std::cout << "Event handler configured for HEMS application" << std::endl;
    }

    /**
     * @brief Simulate device discovery events
     */
    void simulateDeviceEvents()
    {
        std::cout << "Simulating device discovery..." << std::endl;

        // Simulate discovery of various HEMS devices
        std::vector<std::string> discoveredDevices = {
            "SolarInverter_01",
            "BatterySystem_01", 
            "HeatPump_01",
            "SmartMeter_01"
        };

        EventContext discoveryContext(SpineEventType::DEVICE_DISCOVERY, EventPriority::NORMAL);
        discoveryContext.source = "NetworkDiscovery";
        discoveryContext.transportId = "TCP_192.168.1.0";

        m_eventHandler->onDevicesDiscovered(discoveredDevices, discoveryContext);

        // Simulate connection events
        for (const auto& device : discoveredDevices) {
            EventContext connContext(SpineEventType::CONNECTION, EventPriority::NORMAL);
            connContext.source = device;
            connContext.transportId = "TCP_192.168.1." + std::to_string(100 + rand() % 50);
            
            m_eventHandler->onConnectionEstablished(connContext.transportId, connContext);
        }
    }

    /**
     * @brief Simulate various SPINE events during operation
     */
    void simulateSpineEvents()
    {
        static int eventCount = 0;
        eventCount++;

        // Simulate different types of events based on counter
        switch (eventCount % 5) {
            case 0:
                simulateMeasurementEvent();
                break;
            case 1:
                simulateSubscriptionEvent();
                break;
            case 2:
                simulateDatagramEvent();
                break;
            case 3:
                simulateBindingEvent();
                break;
            case 4:
                simulateErrorEvent();
                break;
        }
    }

    /**
     * @brief Simulate measurement datagram events
     */
    void simulateMeasurementEvent()
    {
        std::vector<std::string> devices = {"SolarInverter_01", "BatterySystem_01", "HeatPump_01"};
        std::string device = devices[rand() % devices.size()];

        // Create a dummy datagram record for measurement data
        DatagramRecord datagramRecord;
        // In a real implementation, you would populate this with actual measurement data
        
        EventContext context(SpineEventType::DATAGRAM, EventPriority::NORMAL);
        context.source = device;
        context.transportId = "TCP_192.168.1.100";

        m_eventHandler->onDatagramNotification(datagramRecord, context);
    }

    /**
     * @brief Simulate subscription management events
     */
    void simulateSubscriptionEvent()
    {
        static unsigned int subscriptionId = 1000;
        
        SubscriptionManagementRequestCall subscriptionRequest;
        // In a real implementation, you would populate this properly
        
        EventContext context(SpineEventType::SUBSCRIPTION, EventPriority::NORMAL);
        context.source = "SolarInverter_01";
        
        m_eventHandler->onSubscriptionRequested(subscriptionId++, subscriptionRequest, context);
    }

    /**
     * @brief Simulate datagram call events
     */
    void simulateDatagramEvent()
    {
        DatagramRecord datagramRecord;
        // In a real implementation, you would populate this with actual datagram data
        
        EventContext context(SpineEventType::DATAGRAM, EventPriority::NORMAL);
        context.source = "BatterySystem_01";
        context.transportId = "TCP_192.168.1.101";
        
        m_eventHandler->onDatagramCall(datagramRecord, context);
    }

    /**
     * @brief Simulate binding management events
     */
    void simulateBindingEvent()
    {
        static unsigned int bindingId = 2000;
        
        BindingManagementRequestCall bindingRequest;
        // In a real implementation, you would populate this properly
        
        EventContext context(SpineEventType::BINDING, EventPriority::NORMAL);
        context.source = "HeatPump_01";
        
        m_eventHandler->onBindingRequested(bindingId++, bindingRequest, context);
    }

    /**
     * @brief Simulate error events
     */
    void simulateErrorEvent()
    {
        // Occasionally simulate various error conditions
        int errorType = rand() % 3;
        
        EventContext context(SpineEventType::ERROR, EventPriority::HIGH);
        
        switch (errorType) {
            case 0:
                context.source = "SolarInverter_01";
                m_eventHandler->onDatagramParsingError("invalid_data", "Malformed XML", context);
                break;
            case 1:
                context.source = "BatterySystem_01";
                m_eventHandler->onTransportError("TCP_192.168.1.101", 1001, "Connection timeout", context);
                break;
            case 2:
                {
                    FeatureAddress featureAddr;
                    context.source = "HeatPump_01";
                    m_eventHandler->onFeatureOperationError(featureAddr, "read_measurement", "Device not responding", context);
                }
                break;
        }
    }

    /**
     * @brief Handle measurement data received from devices
     */
    void handleMeasurementData(const std::string& deviceName, const MeasurementListData& data)
    {
        std::cout << "HEMS: Received measurement data from " << deviceName << std::endl;
        
        // In a real HEMS application, you would:
        // 1. Store the measurement data in a database
        // 2. Update energy management algorithms
        // 3. Trigger control actions if needed
        // 4. Update user interfaces
    }

    /**
     * @brief Handle device connection status changes
     */
    void handleDeviceConnectionChange(const std::string& deviceName, bool connected)
    {
        std::cout << "HEMS: Device " << deviceName << " is now " 
                  << (connected ? "CONNECTED" : "DISCONNECTED") << std::endl;
        
        if (!connected) {
            // In a real HEMS application, you would:
            // 1. Mark device as offline in the system
            // 2. Trigger alarms if critical device
            // 3. Switch to backup systems if available
            // 4. Notify operators
        }
    }

    /**
     * @brief Print current event handler statistics
     */
    void printStatistics()
    {
        std::cout << "\n" << m_eventHandler->getStatisticsString() << std::endl;
        
        // Print device-specific statistics
        auto measurementStats = m_eventHandler->getMeasurementStatistics();
        if (!measurementStats.empty()) {
            std::cout << "Measurement Statistics:" << std::endl;
            for (const auto& pair : measurementStats) {
                std::cout << "  " << pair.first << ": " << pair.second << " measurements" << std::endl;
            }
        }
        
        // Print known devices
        auto knownDevices = m_eventHandler->getKnownDevices();
        std::cout << "Known Devices (" << knownDevices.size() << "):" << std::endl;
        for (const auto& device : knownDevices) {
            bool connected = m_eventHandler->isDeviceConnected(device);
            std::cout << "  " << device << " [" << (connected ? "ONLINE" : "OFFLINE") << "]" << std::endl;
        }
        std::cout << std::endl;
    }
};

/**
 * @brief Main entry point demonstrating SPINE event handler usage
 */
int main()
{
    std::cout << "=== SPINE Event Handler Usage Example ===" << std::endl;
    std::cout << "This example demonstrates the iSpineEventHandler interface" << std::endl;
    std::cout << "in the context of a Home Energy Management System (HEMS)" << std::endl;
    std::cout << std::endl;

    try {
        // Create and run the HEMS application
        HemsApplication app;
        
        if (app.initialize()) {
            app.run();
        } else {
            std::cerr << "Failed to initialize HEMS application" << std::endl;
            return 1;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "=== Example completed successfully ===" << std::endl;
    return 0;
}

/* 
 * To compile and run this example:
 * 
 * g++ -std=c++14 \
 *     -I/path/to/KEO/include \
 *     -L/path/to/KEO/lib \
 *     usage_example.cpp \
 *     -lkeo_spine -lkeo_datagram_core -lkeo_datagram_measurement \
 *     -o spine_event_handler_example
 * 
 * ./spine_event_handler_example
 */