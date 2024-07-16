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
#include "communicationLayer.h" // Communication layer functions

// Include C++ libraries
#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

// External variables
namespace threadHandler {
    // Mutexes
    extern std::mutex commandMtx; // Mutex for the command queue
    extern std::mutex telemetryMtx; // Mutex for the telemetry queue
    extern std::condition_variable cv; // Condition for notifying threads

    // Ring buffers
    extern std::queue<std::string> commandBuffer; // Ring buffer for commands
    extern std::vector<telemetryPacket> telemetryBuffer; // Ring buffer for telemetry
}

// Superclass for thread handling
class ThreadClass {
protected:
    std::string name; // Name of the thread

    std::thread th; // Thread object
    std::mutex& mtx; // Mutex for protecting variables
    std::condition_variable& cv; // Condition for notifying threads

    bool running; // Flag if the thread is running

public:
    ThreadClass(
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv
        ); // Constructor
    virtual ~ThreadClass(); // Destructor
    void start(); // Start the thread
    void stop(); // Stop the thread
    bool isRunning(); // Check if the thread is running
    virtual void run() = 0; // Pure virtual function
};

// Intermediate class for handling communications
class CommunicationThread : public ThreadClass {
protected:
    std::queue<std::string>& messageQueue; // Queue for storing messages

public:
    CommunicationThread(
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& messageQueue
        ); // Constructor 
    void pushMessage(std::string& message); // Push a message to the queue
    std::string popMessage(); // Pop a message from the queue
};

// Subclass for receiving commands
class CommandReceiverThread : public CommunicationThread {
public:
    CommandReceiverThread(
        std::string name,
        std::mutex& mtx,
        std::condition_variable& cv,
        std::queue<std::string>& messageQueue
        ); // Constructor 
    void run(); // Implementation of the pure virtual function
};

// Subclass for receiving telemetry
class TelemetryReceiverThread : public CommunicationThread {
public:
    TelemetryReceiverThread(int protocolType); // Constructor with protocol type
    void run(); // Implementation of the pure virtual function
};

#endif // THREAD_HANDLER_H