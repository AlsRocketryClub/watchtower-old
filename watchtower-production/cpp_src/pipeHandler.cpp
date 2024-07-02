/*
-----------------------------------

Source file for handling inter-process communication and 
user commands to the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Import header file and other libraries
#include "pipeHandler.h"
#include <iostream>
#include <cstring>

// Pipe handling methods -----------------------------------
// Constructor
PipeHandler::PipeHandler() {
#ifdef _WIN32
    pipeName = L"\\\\.\\pipe\\WatchtowerPipe";
#else
    pipePath = "/tmp/WatchtowerPipe";
#endif
    createPipe();
}

// Destructor
PipeHandler::~PipeHandler() {
    closePipe();
}

// Create the pipe
void PipeHandler::createPipe() {
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

// Wait for a client to connect
void PipeHandler::waitForClient() {
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

// Send a message to the pipe
void PipeHandler::sendMessage(const char* message) {
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
#endif
    PipeHandler::closePipe();
}

// Receive a message from the pipe (edits the buffer variable in place)
void PipeHandler::receiveMessage(char* buffer, unsigned int size) {
#ifdef _WIN32
    DWORD bytesRead;
    BOOL success = ReadFile(
        pipe,    // Pipe handle
        buffer,  // Buffer to receive message
        size,    // Size of buffer
        &bytesRead, // Number of bytes read
        NULL     // Not overlapped
    );
    if (!success) {
        std::cerr << "Error reading from pipe." << std::endl;
        exit(1);
    }
#else
    ssize_t bytesRead = read(pipe_fd, buffer, size);
    if (bytesRead == -1) {
        std::cerr << "Error reading from pipe." << std::endl;
        exit(1);
    }
#endif
    std::cout << "Received message: " << buffer << std::endl;
    PipeHandler::closePipe();
}

// Close the pipe
void PipeHandler::closePipe() {
#ifdef _WIN32
    CloseHandle(pipe);
#else
    close(pipe_fd);
    unlink(pipePath);
#endif
}

// Status return methods -----------------------------------
// Check if the pipe is created
bool PipeHandler::isPipeCreated() {
#ifdef _WIN32
    return pipe != INVALID_HANDLE_VALUE;
#else
    return pipe_fd >= 0;
#endif
}

// Get the read handle
auto PipeHandler::getReadHandle() {
#ifdef _WIN32
    return pipe;
#else  
    return read(pipePath, O_RDONLY);
#endif
}

// Get the write handle
auto PipeHandler::getWriteHandle() {
#ifdef _WIN32
    return pipe;
#else
    return open(pipePath, O_WRONLY);
#endif