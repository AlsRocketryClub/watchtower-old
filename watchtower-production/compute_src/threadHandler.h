/*
-----------------------------------

Header file for the threading functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

// Include user libraries
#include "watchtowerThreadingUtils.h" // High-level classes
#include "communicationLayer.h" // Communication layer functions

// Include C++ libraries
#include <atomic>
#include <memory>
#include <string>
#include <vector>
#include <thread>
// #include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

// Define the global variables -----------------------------------
// Declare type aliases
using StringQueue = std::queue<std::string>; // Queue of strings
using FloatQueue = std::queue<float>; // Queue of floats

// Define the static variables
namespace threadHandler {
    // Communication variables
    extern std::mutex commandMtx; // Mutex for the command queue
    extern std::condition_variable commandCv; // Command condition variable

    //extern std::mutex telemetryMtx; // Mutex for the telemetry queue

    // Actuator variables
    extern std::mutex azimuthMtx; // Mutex for azimuth motor control
    extern std::mutex elevationMtx; // Mutex for elevation motor control
    extern std::condition_variable actuatorCv; // Actuator condition variable
}

// Subclass for listening to commands -----------------------------------
// Instantiate listeners for each unique port (protocol or terminal) connected
//   to the same mtx, cv and commandBuffer
// Includes message queue, setup, run and shutdown functions
class ListenerThread : public watchtower::Thread {
private:
    // Attributes
    StringQueue& commandBuffer; // Reference to the command buffer
    //int portType; // Communication port type
    bool isConnected = false; // Flag if the port is connected

    // Function pointer types
    typedef void (*SetupFunctionType)();
    typedef std::string (*RunFunctionType)();
    typedef void (*ShutdownFunctionType)();

    // Function pointers
    SetupFunctionType setupFunction = nullptr; // Function pointer for port setup
    RunFunctionType runFunction = nullptr; // Function pointer for run
    ShutdownFunctionType shutdownFunction = nullptr; // Function pointer for shutdown

    //std::function<void()> setupFunction; // Function pointer for port setup
    //std::function<void(StringQueue&)> runFunction; // Function pointer for run
    //std::function<void()> shutdownFunction; // Function pointer for shutdown

    // Private methods
    void run(); // Main run function, to be privately called via start()

public:
    ListenerThread( // Constructor
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& buffer, //int portType,
        SetupFunctionType setupFunction,
        RunFunctionType runFunction,
        ShutdownFunctionType shutdownFunction
        ); 
    ~ListenerThread(); // Destructor
    void setup(); // Setup the listener
    void shutdown(); // Shutdown the listener
};

// Subclass for listening to telemetry -----------------------------------

// Subclass for sending telemetry commands -----------------------------------

// Subclass for processing commands (Thread-safe Singleton pattern) ----------
class CommandProcessor : public watchtower::Thread {
private:
    // Singleton instance
    static std::unique_ptr<CommandProcessor> instance;
    static std::once_flag onceFlag;

    // Attributes
    std::queue<std::string>& commandBuffer; // Reference to the command buffer

    // Private constructor
    CommandProcessor( // Constructor
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& commandBuffer
        );
    

    // Private methods
    void run(); // Main run function, to be privately called via start()

    // Deleted copy constructor and assignment operator
    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor& operator=(const CommandProcessor&) = delete;

public:
    // Destructor
    ~CommandProcessor();

    // Public method to get the instance
    static CommandProcessor* getInstance(
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& commandBuffer
        );
};

// Subclass for reporting statuses (Thread-safe Singleton pattern) ----------
class StatusReporter : public watchtower::Thread {
private:
    // Singleton instance
    static std::unique_ptr<StatusReporter> instance;
    static std::once_flag onceFlag;

    // Attributes
    std::queue<std::string>& statusBuffer; // Reference to the status buffer

    // Private constructor
    StatusReporter( // Constructor
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& statusBuffer
        );

    // Private methods
    void run(); // Main run function, to be privately called via start()

    // Deleted copy constructor and assignment operator
    StatusReporter(const StatusReporter&) = delete;
    StatusReporter& operator=(const StatusReporter&) = delete;

public:
    // Destructor
    ~StatusReporter();

    // Public method to get the instance
    static StatusReporter* getInstance(
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& statusBuffer
        );
};

// Subclass for rocket tracking -----------------------------------
// class RocketTracker : public ThreadClass {
// private:
//     // Attributes
//     std::atomic<float> azimuthAngle; // Thread-safe azimuth angle of the rocket
//     std::atomic<float> elevationAngle; // Thread-safe elevation angle of the rocket
//     std::vector<float>& azimuthAngleBuffer; // Buffer for target angle values
//     std::vector<float>& elevationAngleBuffer; // Buffer for target angle values

//     // Private methods
//     void run(); // Main run function, to be privately called via start()

// // Subclass for actuator handling -----------------------------------
// class ActuatorHandler : public ThreadClass {
// private:
//     // Attributes
//     std::string motorName; // Name of the antenna motor
//     std::vector<float>& targetAngleBuffer; // Buffer for target angle values

//     // Private methods
//     void run(); // Main run function, to be privately called via start()

// public:
//     ActuatorHandler( // Constructor
//         std::string threadName,
//         std::string motorName,
//         std::mutex& mtx,
//         std::condition_variable& cv
//         );
//     ~ActuatorHandler(); // Destructor
// };

// // Subclass for actuator control -----------------------------------
// class ActuatorController : public ThreadClass {
// private:
//     // Attributes
//     std::atomic<float> targetValue; // Thread-safe target value for the actuator control
    
//     // Private methods
//     void run(); // Main run function, to be privately called via start()

// public:
//     ActuatorController( // Constructor
//         std::string name,
//         std::mutex& mtx,
//         std::condition_variable& cv
//         );
//     ~ActuatorController(); // Destructor
//     void setTargetValue(float value); // Set the target value
// };


#endif // THREAD_HANDLER_H