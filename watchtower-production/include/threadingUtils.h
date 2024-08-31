/*
-----------------------------------

Header file for the threading utilities of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans, Avi
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef WATCHTOWER_THREADING_UTILS_H
#define WATCHTOWER_THREADING_UTILS_H

// Include C++ libraries
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>

// Include custom libraries
#include "communicationUtils.h"

namespace watchtower {
    // Class for basic threading -----------------------------------
    class Thread {
    protected:
        std::string name; // Name of the thread
        std::thread th; // Thread object
        std::mutex& mtx; // Mutex for protecting variables
        std::condition_variable& cv; // Condition for notifying threads

        std::atomic<bool> running; // Thread-safe shutdown flag

    public:
        Thread( // Constructor
            std::string name,
            std::mutex& mtx,
            std::condition_variable& cv
            ) : name(name), mtx(mtx), cv(cv), running(false) {}

        ~Thread() { // Destructor
            if (th.joinable()) {th.join();}
        }

        void start() { // Start the thread
            th = std::thread(&Thread::run, this);
        }

        void stop() { // Stop the thread
            //if (th.joinable()) {th.join();}
            running.store(false);
            // Stop the thread
        }

        bool isRunning() { // Check if the thread is running
            return running;
        }

        virtual void run() = 0; // Virtual function for running the thread
    };

    // Class for listener thread -----------------------------------
    class LoraListener : public Thread {
    private:
        watchtower::TelemetryVector& bufferToPush; // Reference to the buffer
        bool isConnected; // Connection status

    public:
        LoraListener( // Constructor
            std::string name, 
            std::mutex& threadMtx, std::condition_variable& threadCv,
            watchtower::TelemetryVector& buffer
            ) : Thread(name, threadMtx, threadCv), bufferToPush(buffer),
                isConnected(false) {running.store(true);}

        ~LoraListener() { // Destructor
            if (isConnected && th.joinable()) {
                watchtower::closeMessageLoRa();
                th.join();
            }
        }

        void setup() { // Setup LoRa communication
            startMessageLoRa();
            isConnected = true;
        }

        void run() override { // Run the listener
            setup(); // Setup the listener
            while (running.load()) { // While running
                watchtower::telemetryPacket packet = watchtower::getMessageLoRa();

                // ** TODO: If condition to check if packet is corrupted **

                // **
                std::lock_guard<std::mutex> lock(mtx);
                bufferToPush.push_back(packet);
                cv.notify_all();
            }
            
            std::cout << "Listener thread '" << name << "' shutting down..." << std::endl;

            if (th.joinable()) { // Shutdown LoRa communication
                watchtower::closeMessageLoRa();
                th.join();
            } // If running is false, join the thread
        }
    };

    // ** TODO: Class for data processing thread ----------------------------
    // Process data from the buffer < dataProcessingUtils.h
    // run() -> filter data if needed < dataProcessingUtils.h
    // run() -> log data to a CSV file < dataProcessingUtils.h
    // **

    // ** TODO: Class for status reporting thread (needed?) ----------------------------
    // Print software and rocket status if needed
    // **

    // Add more thread classes to instantiate here
}

#endif // WATCHTOWER_THREADING_UTILS_H