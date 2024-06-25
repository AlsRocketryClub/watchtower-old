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
#include "command_layer.h"

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
