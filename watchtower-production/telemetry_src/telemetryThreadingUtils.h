/*
-----------------------------------

Header file for the high-level communication utilities of the Telemetry module

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef TELEMETRY_THREADING_UTILS_H
#define TELEMETRY_THREADING_UTILS_H

// Include C++ libraries
#include <iostream>

// Include custom libraries
#include "watchtowerThreadingUtils.h"
#include "watchtowerCommunicationUtils.h"

namespace watchtowerTelemetry {
    // Define type aliases -----------------------------------

    // Define Telemetry scope variables -----------------------------------

    // Define classes derived from the libraries ---------------------------
    // Class for command processor singleton thread
    class CommandProcessor : public watchtower::ThreadSingleton {
    private:
        // Declare the command queue
        watchtower::StringQueue commandQueue;

        void run() override {
            while (running) {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&] {return !commandQueue.empty();});
                std::string command = commandQueue.front();
                commandQueue.pop();
                lock.unlock();
                // Process the command
                std::cout << "Processing command: " << command << std::endl;
            }
        }; // Command processor thread function

        // Constructor
        CommandProcessor(
            std::string name, std::mutex& mtx, std::condition_variable& cv,
            watchtower::StringQueue& buffer
        ) : ThreadSingleton(name, mtx, cv), commandQueue(buffer) {}

    public:
        static CommandProcessor* getInstance( // Get the singleton instance
            std::string name, std::mutex& mtx, std::condition_variable& cv,
            watchtower::StringQueue& buffer
        ) {
            static std::unique_ptr<CommandProcessor> instance; // Instance
            if (!instance) {
                instance.reset(new CommandProcessor(name, mtx, cv, buffer));
            }
            return instance.get();
        }
    };

    // Singleton class for status reporting
    class StatusReporter {
    private:
        // Constructor
        StatusReporter() {}

    public:
        static StatusReporter* getInstance() { // Get the singleton instance
            static std::unique_ptr<StatusReporter> instance; // Instance
            if (!instance) {
                instance.reset(new StatusReporter());
            }
            return instance.get();
        }

        // Send status over IPC
        void reportStatus(std::string message) {
            std::cout << "Status reported: " << message << std::endl;
        }
    };
}

#endif // TELEMETRY_THREADING_UTILS_H