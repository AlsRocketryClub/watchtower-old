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

#ifndef COMMAND_LAYER_H
#define COMMAND_LAYER_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <string>

class CommandLayer {
public:
    CommandLayer(); // Constructor
    ~CommandLayer(); // Destructor

    void createPipe(); // Create the pipe
    void waitForClient(); // Wait for a client to connect
    void sendMessage(const char* message); // Send a message to the pipe
    void receiveMessage(char* buffer, unsigned int size); // Receive a message 
    void closePipe(); // Close the pipe

private:
    #ifdef _WIN32
    HANDLE pipe;
    LPCWSTR pipeName;
    #else
    int pipe_fd; // File descriptors for the pipe on Unix/Linux
    char* pipePath;
    #endif
};

#endif // COMMAND_LAYER_H