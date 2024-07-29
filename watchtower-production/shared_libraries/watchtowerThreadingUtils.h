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

    // Function pointers
    SetupFunctionType setupFunction = nullptr; // Function pointer for port setup
    RunFunctionType runFunction = nullptr; // Function pointer for run
    ShutdownFunctionType shutdownFunction = nullptr; // Function pointer for shutdown

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
            if (th.joinable()) {th.join();}
            running.store(false);
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
        ~ThreadSingleton() {} // Destructor

        static ThreadSingleton* getInstance( // Get the singleton instance
            std::string name,
            std::mutex& mtx,
            std::condition_variable& cv
            ) {
            static ThreadSingleton instance(name, mtx, cv);
            return &instance;
        }
    };

    // Class for listener thread -----------------------------------
    class ListenerThread : public Thread {
    private:
        std::queue<std::string>& bufferToPush; // Reference to the command buffer
        SetupFunctionType setupFunction; // Setup function
        RunFunctionType runFunction; // Run function
        ShutdownFunctionType shutdownFunction; // Shutdown function

        bool isConnected; // Connection status

    public:
        ListenerThread( // Constructor
            std::string name,
            std::mutex& mtx,
            std::condition_variable& cv,
            std::queue<std::string>& buffer,
            SetupFunctionType setupFunction,
            RunFunctionType runFunction,
            ShutdownFunctionType shutdownFunction
            ) : Thread(name, mtx, cv), 
                bufferToPush(buffer),
                setupFunction(setupFunction), runFunction(runFunction), 
                shutdownFunction(shutdownFunction), isConnected(false) {
            running.store(true);
                }

        ~ListenerThread() { // Destructor
            if (isConnected) {shutdownFunction();}
        }

        void setup() { // Setup the listener
            setupFunction();
            isConnected = true;
        }

        void run() override { // Run the listener
            setup();
            while (running.load()) {
                std::string command = runFunction();
                
                // Push the command to the buffer
                std::unique_lock<std::mutex> lock(mtx);
                bufferToPush.push(command);
                lock.unlock();
                cv.notify_one();
            }
        }
    };

    // Class for command processor thread -----------------------------------
    //class CommandProcessor : public Thread, public Singleton {

    
}


#endif // WATCHTOWER_THREADING_UTILS_H
