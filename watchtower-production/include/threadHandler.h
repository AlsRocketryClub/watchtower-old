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

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

// Declare functions and any external variables
namespace threadHandler {
    void startThreads();
    void stopThreads();
    extern std::mutex mtx;
    extern std::condition_variable cv;
    extern std::queue<std::string> messages;
}

#endif // THREAD_HANDLER_H