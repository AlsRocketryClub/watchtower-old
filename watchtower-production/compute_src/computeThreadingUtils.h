/*
-----------------------------------

Header file for the high-level communication utilities of the Compute module

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef COMPUTE_THREADING_UTILS_H
#define COMPUTE_THREADING_UTILS_H

// Include C++ libraries
#include <iostream>

// Include custom libraries
#include "watchtowerThreadingUtils.h"
#include "watchtowerCommunicationUtils.h"

namespace watchtowerCompute {
    // Define type aliases -----------------------------------

    // Define Compute scope variables -----------------------------------

    // Define classes derived from the libraries ---------------------------
    // Class for command processor singleton thread
    class CommandProcessor : public watchtower::ThreadSingleton {
    private:
        // Declare the command queue
        watchtower::StringQueue& commandQueue;

        void run() override {
            while (running.load()) {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&] {return !commandQueue.empty();});
                std::string command = commandQueue.front();
                commandQueue.pop();
                lock.unlock();
                // Process the command
                std::cout << "Processing command: " << command << std::endl;
            }
            std::cout << "Command processor thread shutting down..." << std::endl;

            if (th.joinable()) {th.join();} // If running is false, join the thread
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
            static std::once_flag onceFlag; // Flag for singleton creation
            std::call_once(onceFlag, [&] {
                instance.reset(new CommandProcessor(name, mtx, cv, buffer));
            });
            return instance.get();
        }
    };
}

#endif // COMPUTE_THREADING_UTILS_H