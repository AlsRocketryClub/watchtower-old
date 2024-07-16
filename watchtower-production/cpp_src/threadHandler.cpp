/*
-----------------------------------

Source file for the threading functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include "threadHandler.h"
#include <iostream>
#include <thread>

// Define the global variables -----------------------------------
std::mutex threadHandler::mtx; // Mutex for protecting the message queue
std::condition_variable threadHandler::cv; // Condition for notifying threads
std::queue<std::string> threadHandler::messageQueue; // Queue for storing messages

// Implement the ThreadClass functions -----------------------------------
// Thread constructor
ThreadClass::ThreadClass(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv
    ) : name(name), mtx(mtx), cv(cv), running(false) {}

// Thread destructor
ThreadClass::~ThreadClass() {
    if (th.joinable()) {th.join();}
}

// Start the thread
void ThreadClass::start() {
    th = std::thread(&ThreadClass::run, this);

    // If there is no error, set the running flag to true
    if (th.joinable()) {running = true;}
}

// Stop the thread
void ThreadClass::stop() {
    if (th.joinable()) {th.join();}
    running = false;
}

// Check if the thread is running
bool ThreadClass::isRunning() {
    return running;
}

// Implement the CommunicationThread functions --------------------------------
// Constructor
CommunicationThread::CommunicationThread(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv,
    std::queue<std::string>& messageQueue
    ) : ThreadClass(name, mtx, cv), messageQueue(messageQueue) {}

// Push a message to the queue
void CommunicationThread::pushMessage(std::string& message) {
    std::lock_guard<std::mutex> locker(mtx);
    messageQueue.push(message);
    cv.notify_one();
}

// Pop a message from the queue
std::string CommunicationThread::popMessage() {
    std::string message;
    std::lock_guard<std::mutex> locker(mtx);
    if (!messageQueue.empty()) {
        message = messageQueue.front();
        messageQueue.pop();
    }
    return message;
}

// Implement the CommandReceiverThread functions --------------------------------
// Constructor
CommandReceiverThread::CommandReceiverThread(
    std::string name,
    std::mutex& mtx,
    std::condition_variable& cv,
    std::queue<std::string>& messageQueue
    ) : CommunicationThread(name, mtx, cv, messageQueue) {}