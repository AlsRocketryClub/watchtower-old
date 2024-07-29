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
    // Function declarations
    void startThreads(int protocolType);
    void stopThreads();
    void pushMessage(std::string& message);
    std::string popMessage();

    // External variables
    extern std::mutex mtx; // Mutex for protecting the message queue
    extern std::condition_variable cv; // Condition for notifying threads
    extern std::queue<std::string> messages; // Queue for storing messages
}

#endif // THREAD_HANDLER_H