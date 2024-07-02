/*
-----------------------------------

Source code for handling user input / output

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Import header file and other libraries
#include "userInterfaceLayer.h"
#include <iostream>

// Class for handling user input / output from the terminal
class TerminalInterface {
public:
    static std::string getInput(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    };
};