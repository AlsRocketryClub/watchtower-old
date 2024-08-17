/*
-----------------------------------

Header file for the high-level communication utilities of the Console module

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef CONSOLE_COMMUNICATION_UTILS_H
#define CONSOLE_COMMUNICATION_UTILS_H

// Include C++ libraries
#include <iostream>
#include <atomic>

// Include custom libraries
#include "watchtowerThreadingUtils.h"
#include "watchtowerCommunicationUtils.h"

namespace watchtowerConsole {
    // Define type aliases -----------------------------------

    // Define Console scope variables -----------------------------------
    void blankFunction() {} // Blank function
    std::vector<std::thread> threads; // Vector of threads
    std::atomic<bool> stopFlag(false); // Flag for the shutdown of the console
    std::atomic<bool> stopMain(true); // Flag for the shutdown of the main loop

    // Define global variables -----------------------------------
    // Threading variables for listener state
    // std::atomic<bool> consoleShutdown(false); // Shutdown flag for the console
    // // false = listener is running, true = listener is shutting down

    // Threading variables for command processing
    std::mutex commandMtx; // Mutex for protecting the command buffer
    std::condition_variable commandCv; // Command condition variable
    watchtower::StringQueue commandBuffer; // Command buffer

    // Threading variables for incoming statuses
    std::string statusAppID = "CONSOLE"; // Application ID for status messages
    // No mutex or condition variable needed for incoming status messages

    // Function to shut down the ground station
    void initiateShutdown() {
        // Stop the Compute module
        // Stop the Telemetry module
        // Stop the Console module (set the shutdown flag to true)
        std::cout << "Shutting down the ground station..." << std::endl;
        stopFlag.store(true);
    }

    // Class for command processor singleton thread ---------------------------
    class CommandProcessor : public watchtower::ThreadSingleton {
    private:
        // Declare the command queue
        watchtower::StringQueue& commandQueue;

        void run() override { // Command processor thread function
            while (running.load()) {
                std::string command;
                std::cout << "Waiting for command..." << std::endl;
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&] {return !commandQueue.empty();});
                command = commandQueue.front();
                commandQueue.pop();
                lock.unlock();
                
                std::cout << "Processing command: " << command << std::endl;

                // Stop all Watchtower systems
                if (command == "shutdown" || command == "exit" || command == "stop") {
                    // Confirm the shutdown
                    // std::unique_lock<std::mutex> lock(mtx);
                    // std::cout << "Are you sure you want to shut down the system? (y/n)" << std::endl;
                    // std::string response;
                    // std::cin >> response;
                    // if (response == "y" || response == "Y") {
                    //     initiateShutdown();
                    //     break;
                    // };
                    // lock.unlock();
                    initiateShutdown();
                    break;
                }
                
                // Postprocess (switch case of responsibility)
                // Internal command processing

                // Delegating to other modules (sole responsibility of Console)
            }

            // Stop the thread if the loop is broken
            running.store(false);

            if (th.joinable()) {
                th.join();
            } 
        }; 

        // Constructor
        CommandProcessor(
            std::string name, std::mutex& mtx, std::condition_variable& cv,
            watchtower::StringQueue& buffer
        ) : ThreadSingleton(name, mtx, cv), commandQueue(buffer) {running.store(true);}

    public:
        static CommandProcessor* getInstance( // Get the singleton instance
            std::string name,
            std::mutex& mtx,
            std::condition_variable& cv,
            watchtower::StringQueue& buffer
        ) {
            static CommandProcessor instance(name, mtx, cv, buffer);
            return &instance;
        }
    };

    // Class for status reporting
    // class StatusReporter : public watchtower::ThreadSingleton {
    // private:
    //     void run() override { // Status reporter thread function
    //         while (running) {
    //             // Wait for a module message 
                
    //             // Send the status message to the Watchtower
    //             watchtower::sendStatus(statusAppID, status);
    //         }
    //     }; 

    //     // Constructor
    //     StatusReporter(
    //         std::string name, std::mutex& mtx, std::condition_variable& cv,
    //         watchtower::StringQueue& buffer
    //     ) : ThreadSingleton(name, mtx, cv), statusQueue(buffer) {}
    // };

    // Define threading routines -----------------------------------
    // Function to initialize Console threads
    CommandProcessor* commandProcessor = CommandProcessor::getInstance(
        "CommandProcessor", commandMtx, commandCv, commandBuffer
    ); // Initialize the command processor singleton thread

    watchtower::ListenerThread TerminalListener(
        "TerminalListener", commandMtx, commandCv, commandBuffer,
        blankFunction, // No setup function needed
        watchtower::getMessageTerminal, // Run function
        blankFunction // No shutdown function needed
    ); // Initialize the terminal listener thread

    // Function to start Console threads
    void startThreads() {
        // Start the threads
        TerminalListener.start();
        commandProcessor->start();
        // statusReporter->start();
        stopMain.store(false);
    }

    // Function to stop Console threads
    void stopThreads() {
        // Stop the threads
        std::cout << "Stopping console threads..." << std::endl;
        TerminalListener.stop();
        // Check if terminal listener thread is running
        commandProcessor->stop();
        // Check if command processor thread still exists
        //std::cout << "Console threads stopped." << std::endl;
        // statusReporter->stop();
        stopMain.store(true);
    }


}

#endif // CONSOLE_COMMUNICATION_UTILS_H