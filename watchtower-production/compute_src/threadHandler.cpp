/*
-----------------------------------

Source file for the threading functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include "threadHandler.h"
#include "communicationLayer.h"
#include <iostream>
#include <thread>
#include <atomic>

// Define the global variables -----------------------------------
// Declare type aliases
using StringQueue = std::queue<std::string>; // Queue of strings

// Define the static variables
std::mutex threadHandler::commandMtx; // Mutex for protecting the command queue
std::condition_variable threadHandler::commandCv; // Command condition variable

// Implement the ThreadClass functions -----------------------------------
// Thread constructor
ThreadClass::ThreadClass(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv
    ) : name(name), mtx(mtx), cv(cv), running(false) {}

// Thread destructor
ThreadClass::~ThreadClass() {
    if (th.joinable()) {th.join();}
}

// Start the thread
void ThreadClass::start() {
    th = std::thread(&ThreadClass::run, this);
}

// Stop the thread
void ThreadClass::stop() {
    if (th.joinable()) {th.join();}
    running.store(false);
}

// Check if the thread is running
bool ThreadClass::isRunning() {
    return running;
}

// Implement the ListenerThread functions --------------------------------
// Constructor
ListenerThread::ListenerThread(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv,
    std::queue<std::string>& buffer, //int portTypeArg
    SetupFunctionType setupFunction,
    RunFunctionType runFunction,
    ShutdownFunctionType shutdownFunction
    ) : ThreadClass(name, mtx, cv), 
        commandBuffer(buffer), //portType(portTypeArg),
        setupFunction(setupFunction), runFunction(runFunction), 
        shutdownFunction(shutdownFunction) {
        // Set the running flag
        running.store(true);
    }

// Destructor
ListenerThread::~ListenerThread() {
    // Shut down the communication port if applicable
    if (isConnected) {shutdownFunction();}
}

// Setup the listener
void ListenerThread::setup() {
    // Implement the setup procedure for the communication port
    setupFunction();
    isConnected = true;
}

// Run the listener (called by ThreadClass::start())
void ListenerThread::run() {
    // Setup the listener
    setup();

    // Run the listener
    while (running.load()) {
        std::string command = runFunction(); // Get the command from the port
        
        // Push the command to the buffer
        std::unique_lock<std::mutex> lck(mtx);
        commandBuffer.push(command);
        //std::cout << "Pushed command: " << command << std::endl; // Debugging
        lck.unlock();
        cv.notify_one();
    }

    // Shutdown the listener after the loop
    shutdownFunction();
    isConnected = false;
}

// Shutdown the listener
void ListenerThread::shutdown() {
    // Set the flag for shutdown
    running.store(false);
}

// Implement the CommandProcessor functions --------------------------------
// Private constructor
CommandProcessor::CommandProcessor(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv,
    std::queue<std::string>& buffer
    ) : ThreadClass(name, threadHandler::commandMtx, threadHandler::commandCv), 
                    commandBuffer(buffer) {
    // Set the running flag
    running.store(true);
}

// Destructor
CommandProcessor::~CommandProcessor() {
    // Stop the command processor
    stop();
}

// Get the singleton instance
CommandProcessor* CommandProcessor::getInstance(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv,
    std::queue<std::string>& commandBuffer
    ) {
    std::call_once(onceFlag, [&] { // Thread-safe call once
        instance.reset(new CommandProcessor(name, mtx, cv, commandBuffer));
    });
    return instance.get();
}

// Initialize the singleton instance
std::unique_ptr<CommandProcessor> CommandProcessor::instance = nullptr;
std::once_flag CommandProcessor::onceFlag;

// Run the command processor (called by ThreadClass::start())
void CommandProcessor::run() {
    // Run the command processor
    while (running.load()) {
        // Process the command buffer
        std::cout << "Waiting for command..." << std::endl;
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [&] {return !commandBuffer.empty();});
        std::string command = commandBuffer.front();
        commandBuffer.pop();
        lck.unlock();
        std::cout << "Processing command: " << command << std::endl;
    }
}

// Implement the ActuatorController functions --------------------------------
// // Constructor
// ActuatorController::ActuatorController(
//     std::string name,
//     std::mutex& mtx,
//     std::condition_variable& cv
//     ) : ThreadClass(name, mtx, cv) {
//     // Set the running flag
//     running.store(true);
// }

// // Destructor
// ActuatorController::~ActuatorController() {
//     // Stop the actuator controller
//     stop();
// }

// // Run the actuator controller (called by ThreadClass::start())
// void ActuatorController::run() {
//     // Run the actuator controller
//     while (running.load()) {
//         // Implement the actuator control logic
//         std::cout << "Actuator controller running..." << std::endl;
//         std::this_thread::sleep_for(std::chrono::seconds(1));

        
//     }
// }

