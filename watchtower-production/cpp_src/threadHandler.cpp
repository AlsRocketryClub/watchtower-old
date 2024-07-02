/*
-----------------------------------

Source code for the threading functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include "threadHandler.h"
#include <iostream>
#include <thread>

// Define global variables
std::mutex threadHandler::mtx;
std::condition_variable threadHandler::cv;
std::queue<std::string> threadHandler::messages;

namespace threadHandler{
    bool finished = false; // Flag to indicate when the threads should stop

    void inputThread() {
        std::string input;
        while (true) {
            std::getline(std::cin, input);
            if (input == "exit") {
                finished = true;
                cv.notify_one();
                break;
            }
            {
                std::lock_guard<std::mutex> locker(mtx);
                messages.push(input); // Protected code block {}
            } // Guard goes out of scope and mtx is released
            cv.notify_one();
        }
    }

    void statusThread() {
        while (!finished) {
            std::unique_lock<std::mutex> locker(mtx);
            cv.wait(locker, [] { return !messages.empty() || finished;});
            while (!messages.empty()) {
                std::cout << "Received: " << messages.front() << std::endl;
                messages.pop();
            }

            locker.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Status thread running..." << std::endl;
        }
    } 

    void startThreads() {
        std::thread input(inputThread);
        std::thread status(statusThread);

        input.join();
        status.join();
    }

    void stopThreads() {
        // Implement if needed, for a graceful shutdown 
        finished = true;
        cv.notify_all();
    }
}