/*
-----------------------------------

Header file for handling inter-process communication and 
user commands to the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#pragma once

#ifndef PIPE_HANDLER_H
#define PIPE_HANDLER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <string>

class PipeHandler {
public:
    PipeHandler(); // Constructor
    ~PipeHandler(); // Destructor

    // Pipe handling methods
    void createPipe(); // Create the pipe
    void waitForClient(); // Wait for a client to connect
    void sendMessage(const char* message); // Send a message to the pipe
    void receiveMessage(char* buffer, unsigned int size); // Receive a message 
    void closePipe(); // Close the pipe

    // Status return methods
    bool isPipeCreated(); // Check if the pipe is created
    auto getReadHandle(); // Get the read handle
    auto getWriteHandle(); // Get the write handle

private:
    #ifdef _WIN32
    HANDLE pipe;
    LPCWSTR pipeName;
    #else
    int pipe_fd; // File descriptors for the pipe on Unix/Linux
    char* pipePath;
    #endif
};

#endif // PIPE_HANDLER_H