/*
-----------------------------------

Header file for the high-level threading utilities of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
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
#include "watchtowerCommunicationUtils.h"

namespace watchtower {
    // Define type aliases -----------------------------------
    // Function pointer types
    typedef void (*SetupFunctionType)();
    typedef std::string (*RunFunctionType)();
    typedef void (*ShutdownFunctionType)();
    // typedef void (*SendMessageFunctionType)(std::string);

    // Function pointers
    SetupFunctionType setupFunction = nullptr; // Function pointer for thread port setup
    RunFunctionType runFunction = nullptr; // Function pointer for thread run
    ShutdownFunctionType shutdownFunction = nullptr; // Function pointer for thread shutdown

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

    // Class for singleton-based thread ------------------------
    class ThreadSingleton : public Thread {
    protected:
        ThreadSingleton( // Constructor
            std::string name,
            std::mutex& mtx,
            std::condition_variable& cv
            ) : Thread(name, mtx, cv) {}

        void run() override { // Run function virtual bypass, to be overridden
            assert(false && "run() should be overridden in further derived classes");
        }

    public:
        static ThreadSingleton* getInstance( // Get the singleton instance
            std::string name,
            std::mutex& mtx,
            std::condition_variable& cv
            ) {
            static std::unique_ptr<ThreadSingleton> instance; // Instance
            static std::once_flag onceFlag; // Flag for singleton creation
            std::call_once(onceFlag, [&] {
                instance.reset(new ThreadSingleton(name, mtx, cv));
            });
            return instance.get();
        }
    };

    // Class for listener thread -----------------------------------
    class ListenerThread : public Thread {
    private:
        std::queue<std::string>& bufferToPush; // Reference to the command buffer
        SetupFunctionType setupFunction; // Setup function
        RunFunctionType runFunction; // Run function
        ShutdownFunctionType shutdownFunction; // Shutdown function

        //std::mutex& listenMtx = 
        // Mutex for the listener thread
        //std::condition_variable& listenCv; // Condition for the listener thread

        bool isConnected; // Connection status

    public:
        ListenerThread( // Constructor
            std::string name, 
            std::mutex& threadMtx, std::condition_variable& threadCv,
            std::queue<std::string>& buffer, 
            SetupFunctionType setupFunction,
            RunFunctionType runFunction,
            ShutdownFunctionType shutdownFunction
            ) : Thread(name, threadMtx, threadCv), bufferToPush(buffer),
                setupFunction(setupFunction), runFunction(runFunction), 
                shutdownFunction(shutdownFunction), isConnected(false) {
            running.store(true);
                }

        ~ListenerThread() { // Destructor
            if (isConnected && th.joinable()) {
                shutdownFunction();
                th.join();
            }
        }

        void setup() { // Setup the listener
            setupFunction();
            isConnected = true;
        }

        void run() override { // Run the listener
            setup(); // Setup the listener
            while (running.load()) { // While running
                std::string command = runFunction();

                // Push the command to the buffer
                std::cout << "Received command: " << command << std::endl;
                if (command != "") {
                    std::unique_lock<std::mutex> lock(mtx);
                    bufferToPush.push(command);
                    lock.unlock();
                    cv.notify_one();
                }
            }
            
            std::cout << "Listener thread shutting down..." << std::endl;

            if (th.joinable()) {
                shutdownFunction();
                th.join();
            } // If running is false, join the thread
        }
    };

    // Class for status reporting thread ---------------------------
    class StatusReporter : public Thread {
    private:
        SetupFunctionType setupFunction; // Setup function
        RunFunctionType runFunction; // Run function
        ShutdownFunctionType shutdownFunction; // Shutdown function

    public:
        StatusReporter( // Constructor
            std::string name, std::mutex& mtx, std::condition_variable& cv,
            SetupFunctionType setupFunction,
            RunFunctionType runFunction,
            ShutdownFunctionType shutdownFunction
            ) : Thread(name, mtx, cv),
                setupFunction(setupFunction), runFunction(runFunction),
                shutdownFunction(shutdownFunction) {
            running.store(true);
                }

        ~StatusReporter() { // Destructor
            if (th.joinable()) {
                shutdownFunction();
                th.join();
            }
        }

        void setup() { // Setup the status reporter
            setupFunction();
        }

        void run() override { // Run the status reporter
            setup();
            while (running.load()) {
                runFunction();
            }

            if (th.joinable()) {
                shutdownFunction();
                th.join();
            } // If running is false, join the thread
        }
    };
}


#endif // WATCHTOWER_THREADING_UTILS_H
