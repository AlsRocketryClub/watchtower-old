/*
-----------------------------------

Source file for handling inter-process communication and 
user commands to the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include "CommandLayer.h"
#include <iostream>
#include <cstring>

CommandLayer::CommandLayer() {
    // Constructor implementation
#ifdef _WIN32
    pipeName = L"\\\\.\\pipe\\WatchtowerPipe";
#else
    pipePath = "/tmp/watchtower_pipe";
#endif
    createPipe();
}

CommandLayer::~CommandLayer() {
    closePipe();
}

void CommandLayer::createPipe() {
#ifdef _WIN32
    pipe = CreateNamedPipe(
        pipeName,           // Pipe name
        PIPE_ACCESS_DUPLEX, // Read/write access
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,                  // Number of instances
        1024,               // Output buffer size
        1024,               // Input buffer size
        0,                  // Time-out
        NULL                // Default security attributes
    );

    if (pipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Error creating pipe." << std::endl;
        exit(1);
    }
#else
    if (mkfifo(pipePath, 0666) == -1) {
        if (errno != EEXIST) {
            std::cerr << "Error creating FFIFO: " << strerror(errno) << std::endl;
            exit(1);
        }
    }
#endif
}

void CommandLayer::waitForClient() {
#ifdef _WIN32
    std::cout << "Waiting for client to connect..." << std::endl;
    BOOL connected = ConnectNamedPipe(pipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
    if (!connected) {
        std::cerr << "Error connecting to client" << std::endl;
        CloseHandle(pipe);
        exit(1);
    }
    std::cout << "Client connected" << std::endl;
#else
    std::cout << "Opening pipe for reading..." << std::endl;
    pipe_fd = open(pipePath, O_RDONLY);
    if (pipe_fd == -1) {
        std::cerr << "Error opening pipe for reading..." << std::endl;
        exit(1);
    }
    std::cout << "Pipe opened for reading." << std::endl;
#endif
}

void CommandLayer::sendMessage(const char* message) {
#ifdef _WIN32
    HANDLE writeHandle = CreateFile(
        pipeName,           // Pipe name
        GENERIC_WRITE,      // Write access
        0,                  // No sharing
        NULL,               // Default security attributes
        OPEN_EXISTING,      // Opens existing pipe
        0,                  // Default attributes
        NULL                // No template file
    );
    if (writeHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening pipe for writing." << std::endl;
        exit(1);
    }

    DWORD bytesWritten;
    BOOL success = WriteFile(
        writeHandle,         // Pipe handle
        message,             // Message to send
        strlen(message) + 1, // Size of message
        &bytesWritten,       // Number of bytes written
        NULL                 // Not overlapped
    );
    if (!success) {
        std::cerr << "Error writing to pipe." << std::endl;
        exit(1);
    } else {
        std::cout << "Message sent to client." << std::endl;
    }
    CloseHandle(writeHandle);
#else
    int write_fd = open(pipePath, O_WRONLY);
    if (write_fd == -1) {
        std::cerr << "Error opening pipe for writing." << std::endl;
        exit(1);
    }

    ssize_t bytesWritten = write(write_fd, message, strlen(message) + 1);
    if (bytesWritten == -1) {
        std::cerr << "Error writing to pipe." << std::endl;
        exit(1);
    } else {
        std::cout << "Message sent to client." << std::endl;
    }
    close(write_fd);
#endif
}