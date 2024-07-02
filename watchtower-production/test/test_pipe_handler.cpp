/*
-----------------------------------

Code testing for the main functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include "gtest/gtest.h"

// Include header files for testing
// #include "main.cpp" // bad idea
#include "pipeHandler.h"

// Include standard libraries
#include <iostream>

TEST(ProcessListenTest, RespondstoCommandX) {
    // Setup: Launch the C++ process to listen for commands
    // Action: Send the 'CommandX' to the process
    // Assert: Check if the process responds to the command

    //char result = processListen('X');
    //std::cout << "processListen('X') returned: " << static_cast<int>(result) << std::endl;
    //EXPECT_EQ('Y', result); // Check alphanumeric input
    //ASSERT_TRUE(true);
    //EXPECT_EQ(3, add(1, 2));
}

TEST(PipeSetupTest, CreatesPipe) {
    // Setup: Create a pipe for inter-process communication
    PipeHandler pipeHandler;

    // Assert: Check if the pipe is created successfully
    ASSERT_TRUE(pipeHandler.isPipeCreated());

    // Assert: Pipe handle validity
    auto readHandle = pipeHandler.getReadHandle();
    auto writeHandle = pipeHandler.getWriteHandle();

    #ifdef _WIN32 // Windows
    ASSERT_NE(readHandle, INVALID_HANDLE_VALUE);
    ASSERT_NE(writeHandle, INVALID_HANDLE_VALUE);
    #else // Unix/Linux
    ASSERT_TRUE(readHandle >= 0);
    ASSERT_TRUE(writeHandle >= 0);
    #endif
}
